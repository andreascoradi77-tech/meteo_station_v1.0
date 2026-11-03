#include <leguan.h>
#include <cube.h>
#include "gui.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"

// ============ Button-Callbacks (C++-kompatibel via extern "C") ============
// Diese werden in gui.cpp als Funktionspointer genutzt.

// Vorwärtsdeklaration der Page-Umschaltfunktionen
void showPage0(void);
void showPage1(void);
static void verarbeite_zeit_antwort(char* antwort);
static void requestTimeFromESP(void); 
static void update_lokale_uhr(void);


// Zustand für die lokale Uhr
static uint32_t basis_sekunden = 0;      // Sekunden seit Mitternacht (vom ESP32)
static uint32_t letzter_sync_tick = 0;   // Wann wir das letzte Mal synchronisiert haben
static int letzte_angezeigte_sekunde = -1; // Um unnötiges Neuzeichnen zu verhindern

// ============ Main ============
int main() {
    CUBEMX_Init();
    LEGUAN_Init();

    // GUI aufbauen
    gui_init();

    // Dummy-Werte setzen (später: aus Sensoren lesen)
    gui_setTemperature(23.4f);
    gui_setHumidity(56.2f);
    gui_setPressure(1013.2f);

    uint16_t x_old = 0, y_old = 0;

    //int tab = 250;

        float temperature = 0;
    //    float temperature_old = temperature;
        result_t testtemp;
        int temperr = 0;
        uint16_t temp_x_beg = 20;
//        uint16_t temp_x_tab = temp_x_beg + tab;
        uint16_t temp_y_beg = 20;
   //     char* temp_text[20];
     //   const char temp_error_text[] = 'ERROR: Temperature reading failed!';

        float humidity = 0;
    //    float humidity_old = humidity;
        result_t testhumi;
        int humierr = 0;
        uint16_t humi_x_beg = 20;
  //      uint16_t humi_x_tab = humi_x_beg + tab;
        uint16_t humi_y_beg = 50;
  //      char* humi_text[20];
    //    const char humi_error_text[] = 'ERROR: Humidity reading failed!';

        float pressure = 0;
    //    float pressure_old = pressure;
        result_t testpres;
        int preserr = 0;
        uint16_t pres_x_beg = 20;
     //   uint16_t pres_x_tab = pres_x_beg + tab;
        uint16_t pres_y_beg = 80;

        //char* pres_text[20];

		uint32_t letzteZeitAbfrage = 0;
		const uint32_t ZEIT_INTERVALL = 60000; // alle 5 Sekunden




        while(true) {

            // Temperature:
            testtemp = SENSOR_GetTemperature(&temperature);
            if(testtemp == RESULT_SUCCESS){
        //        temperature_old = temperature;
            } else ++temperr;
            // Temperature error:
            if(temperr > 5){
                    LCD_SetBackgroundColor(ColorRed);
                    LCD_String(temp_x_beg, temp_y_beg, "ERROR: Temperature reading failed");
                    CORE_Delay(1000);
                    temperr = 0;
            }
            // Humidity:
            testhumi = SENSOR_GetHumidity(&humidity);
            if(testhumi == RESULT_SUCCESS){
         //       humidity_old = humidity;
            } else ++humierr;
            // Humidity error:
            if(humierr > 5){
                    LCD_SetBackgroundColor(ColorRed);
                    LCD_String(humi_x_beg, humi_y_beg, "ERROR: Humidity reading failed");
                    CORE_Delay(1000);
                    humierr = 0;
            }


            // Pressure:
            testpres = SENSOR_GetPressure(&pressure);
            if(testpres == RESULT_SUCCESS){
         //       pressure_old = pressure;
            } else ++preserr;
            // Pressure error:
            if(preserr > 5){
                    LCD_SetBackgroundColor(ColorRed);
                    LCD_String(pres_x_beg, pres_y_beg, "ERROR: Pressure reading failed");
                    CORE_Delay(1000);
                    preserr = 0;
            }
            gui_setTemperature(temperature);
            gui_setHumidity(humidity);
            gui_setPressure(pressure);

        // Touch abfragen
        LCD_TouchPosition_t touchPosition = {0, 0};
        if (R_SUCCESS(LCD_TouchGetPosition(&touchPosition))) {
            uint16_t x_new = touchPosition.x;
            uint16_t y_new = touchPosition.y;

            if (x_new != 0 || y_new != 480) {
                // Alten Cursor löschen
                LCD_SetForegroundColor(ColorBlack);
                LCD_Rect(x_old - 5, y_old - 5, 30, 30);

                // GUI informieren
                gui_touch(x_new, y_new);

                // Roten Punkt zeichnen (Touch-Visualisierung)
                LCD_SetForegroundColor(ColorRed);
                LCD_Rect(x_new, y_new, 5, 5);

                x_old = x_new;
                y_old = y_new;
            }
        }
        
        if (HAL_GetTick() - letzteZeitAbfrage > ZEIT_INTERVALL) {
    		letzteZeitAbfrage = HAL_GetTick();
    		requestTimeFromESP();
		}
       
        update_lokale_uhr();
        gui_update();
        CORE_Delay(20);   // 20 Hz reicht völlig
    }
return 0 ;}

// Wandelt einen Unix-Timestamp (z.B. 1761573785) in "HH:MM:SS" um
static void verarbeite_zeit_antwort(char* antwort) {
    if (antwort[0] == 'E') return; // "ERR NO_TIME" ignorieren

    long ts = atol(antwort);
    if (ts < 1000000000) return; // Unplausibler Wert

    // NEU: Sekunden seit Mitternacht (UTC) und den aktuellen Tick speichern
    basis_sekunden = ts % 86400;
    letzter_sync_tick = HAL_GetTick();

    // Sofort einmal updaten, damit die neue Zeit ohne Verzögerung erscheint
    letzte_angezeigte_sekunde = -1;
    update_lokale_uhr();
}

// Fragt den ESP32 nach der Zeit
static void requestTimeFromESP(void) {
    // 1. ALTEN MÜLL AUS DEM PUFFER WERFEN (Wichtig!)
    uint8_t dummy;
    // Lese so lange, bis nichts mehr da ist (Timeout auf 1 ms)
    while (HAL_UART_Receive(&huart1, &dummy, 1, 1) == HAL_OK) { }
    // Fehler-Flag vom STM32 löschen (verhindert Blockade)
    __HAL_UART_CLEAR_OREFLAG(&huart1);

    // 2. Befehl senden
    const char* cmd = "get time\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)cmd, strlen(cmd), 100);

    // 3. Antwort empfangen
    char rxBuf[32];
    int idx = 0;
    uint8_t c;

    while (idx < sizeof(rxBuf) - 1) {
        if (HAL_UART_Receive(&huart1, &c, 1, 50) == HAL_OK) {
            // Nur auf \n reagieren. \r wird ignoriert!
            if (c == '\n') {
                break; // Zeilenende erreicht, Schleife verlassen
            }
            if (c != '\r') {
                rxBuf[idx++] = (char)c; // Zeichen speichern
            }
        } else {
            break; // Timeout
        }
    }
    rxBuf[idx] = '\0'; // String terminieren

    // 4. Wenn Daten da sind, umrechnen und an GUI geben
    if (idx > 0) {
        verarbeite_zeit_antwort(rxBuf);
    }
}
// Lässt die Uhr zwischen den ESP32-Updates lokal weiterlaufen
static void update_lokale_uhr(void) {
    // Wenn wir noch keine Zeit vom ESP32 haben, machen wir nichts
    if (basis_sekunden == 0) return;

    // Wie viele Sekunden sind seit dem letzten Sync vergangen?
    uint32_t vergangene_ms = HAL_GetTick() - letzter_sync_tick;
    uint32_t vergangene_sekunden = vergangene_ms / 1000;

    // Aktuelle Uhrzeit berechnen (modulo 86400 verhindert Überlauf nach 24h)
    uint32_t aktuelle_sekunde = (basis_sekunden + vergangene_sekunden) % 86400;

    // Nur neu zeichnen, wenn sich die Sekunde auch wirklich geändert hat!
    if (aktuelle_sekunde != letzte_angezeigte_sekunde) {
        letzte_angezeigte_sekunde = aktuelle_sekunde;

        int h = aktuelle_sekunde / 3600;
        int m = (aktuelle_sekunde % 3600) / 60;
        int s = aktuelle_sekunde % 60;

        char timeStr[16];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", h, m, s);
        gui_setTime(timeStr);
    }
}
