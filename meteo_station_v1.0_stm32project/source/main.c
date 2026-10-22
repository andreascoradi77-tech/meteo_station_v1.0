#include <leguan.h>
#include <cube.h>
#include "gui.h"

#include <stdio.h>

// ============ Button-Callbacks (C++-kompatibel via extern "C") ============
// Diese werden in gui.cpp als Funktionspointer genutzt.

// Vorwärtsdeklaration der Page-Umschaltfunktionen
void showPage0(void);
void showPage1(void);

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

        gui_update();
        CORE_Delay(20);   // 20 Hz reicht völlig
    }
return 0 ;}
