#ifndef GUI_H
#define GUI_H

#include <stdint.h>

/* ============================================================
 *  Öffentliche C-Schnittstelle zur GUI
 *  (diese Datei kann gefahrlos aus C-Code (main.c) inkludiert werden)
 * ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* GUI initialisieren – einmal in main() aufrufen */
void gui_init(void);

/* GUI-Update – in jeder main-Loop-Iteration aufrufen */
void gui_update(void);

/* Touch-Event an GUI weitergeben */
void gui_touch(uint16_t x, uint16_t y);

/* Werte setzen (später mit echten Sensordaten) */
void gui_setTemperature(float t);
void gui_setHumidity(float h);
void gui_setPressure(float p);
void gui_setTime(const char* timeStr);

#ifdef __cplusplus
}
#endif

#endif /* GUI_H */
