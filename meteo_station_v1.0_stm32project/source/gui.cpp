#include <leguan.h>
#include "gui.h"
#include <stdio.h>

// =====================================================================
// Bildschirm-Konstanten
// =====================================================================
static const uint16_t SCREEN_W = 800;
static const uint16_t SCREEN_H = 480;
// =====================================================================
// Time Buffer
// =====================================================================
static char g_timeBuf[16] = "--:--:--";
// =====================================================================
// Farben – alle vom Typ color_t (nicht uint32_t!)
// =====================================================================
static const color_t COL_BG         = ColorBlack;
static const color_t COL_HEADER_BG  = ColorBlue;
static const color_t COL_HEADER_FG  = ColorWhite;   // falls ColorWhite nicht existiert: ColorBlue
static const color_t COL_BOX_BG     = ColorBlack;
static const color_t COL_BOX_BORDER = ColorBlue;
static const color_t COL_TEXT       = ColorWhite;   // falls ColorWhite nicht existiert: ColorBlue
static const color_t COL_VALUE      = ColorRed;     // falls ColorYellow existiert: ColorYellow
static const color_t COL_BTN_BG     = ColorBlue;
static const color_t COL_BTN_FG     = ColorWhite;
static const color_t COL_BTN_PRESS  = ColorGreen;

// =====================================================================
// Widget (Basisklasse)
// =====================================================================
class Widget {
public:
    Widget(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
        : m_x(x), m_y(y), m_w(w), m_h(h), m_visible(true) {}
    virtual ~Widget() {}

    virtual void draw() = 0;
    virtual bool handleTouch(uint16_t tx, uint16_t ty) { (void)tx; (void)ty; return false; }

    bool contains(uint16_t tx, uint16_t ty) const {
        return tx >= m_x && tx < m_x + m_w &&
               ty >= m_y && ty < m_y + m_h;
    }
    void setVisible(bool v) { m_visible = v; }
    bool isVisible() const { return m_visible; }

protected:
    uint16_t m_x, m_y, m_w, m_h;
    bool m_visible;
};

// =====================================================================
// Label
// =====================================================================
class Label : public Widget {
public:
    Label(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
          const char* text, color_t color)
        : Widget(x, y, w, h), m_text(text), m_color(color) {}

    void setText(const char* text) { m_text = text; }
    void setColor(color_t c) { m_color = c; }

    void draw() override {
        if (!m_visible) return;
        LCD_SetForegroundColor(m_color);
        LCD_String(m_x, m_y, const_cast<char*>(m_text));
    }

private:
    const char* m_text;
    color_t m_color;
};

// =====================================================================
// ValueDisplay
// =====================================================================
class ValueDisplay : public Widget {
public:
    ValueDisplay(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                 const char* title, const char* unit)
        : Widget(x, y, w, h), m_title(title), m_unit(unit), m_value(0.0f) {}

    void setValue(float v) { m_value = v; }

    void draw() override {
        if (!m_visible) return;

        // Äußerer Rand
        LCD_SetForegroundColor(COL_BOX_BORDER);
        LCD_Rect(m_x, m_y, m_w, m_h);
        // Innenbereich
        LCD_SetForegroundColor(COL_BOX_BG);
        LCD_Rect(m_x + 2, m_y + 2, m_w - 4, m_h - 4);

        // Titel
        LCD_SetForegroundColor(COL_TEXT);
        LCD_String(m_x + 10, m_y + 10, const_cast<char*>(m_title));

        // Wert
        snprintf(m_buf, sizeof(m_buf), "%.1f", m_value);
        LCD_SetForegroundColor(COL_VALUE);
        LCD_String(m_x + 10, m_y + 50, m_buf);

        // Einheit
        LCD_SetForegroundColor(COL_TEXT);
        LCD_String(m_x + 10, m_y + 90, const_cast<char*>(m_unit));
    }

private:
    const char* m_title;
    const char* m_unit;
    float m_value;
    char m_buf[16];
};

// =====================================================================
// Button
// =====================================================================
class Button : public Widget {
public:
    typedef void (*Callback)(void);

    Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
           const char* text, Callback cb)
        : Widget(x, y, w, h), m_text(text), m_cb(cb), m_pressed(false) {}

    void draw() override {
        if (!m_visible) return;
        LCD_SetForegroundColor(m_pressed ? COL_BTN_PRESS : COL_BTN_BG);
        LCD_Rect(m_x, m_y, m_w, m_h);
        LCD_SetForegroundColor(COL_BTN_FG);
        LCD_String(m_x + 10, m_y + 20, const_cast<char*>(m_text));
    }

    bool handleTouch(uint16_t tx, uint16_t ty) override {
        if (!m_visible) return false;
        if (!contains(tx, ty)) return false;

        m_pressed = true;
        draw();
        if (m_cb) m_cb();
        CORE_Delay(150);
        m_pressed = false;
        draw();
        return true;
    }

private:
    const char* m_text;
    Callback m_cb;
    bool m_pressed;
};

// =====================================================================
// Page
// =====================================================================
class Page {
public:
    static const uint8_t MAX_WIDGETS = 16;

    Page() : m_count(0) {}

    void addWidget(Widget* w) {
        if (m_count < MAX_WIDGETS) m_widgets[m_count++] = w;
    }
    void drawAll() {
        for (uint8_t i = 0; i < m_count; ++i) m_widgets[i]->draw();
    }
    bool handleTouch(uint16_t tx, uint16_t ty) {
        for (int i = m_count - 1; i >= 0; --i)
            if (m_widgets[i]->handleTouch(tx, ty)) return true;
        return false;
    }
    void setVisible(bool v) {
        for (uint8_t i = 0; i < m_count; ++i) m_widgets[i]->setVisible(v);
    }

private:
    Widget* m_widgets[MAX_WIDGETS];
    uint8_t m_count;
};

// =====================================================================
// Gui
// =====================================================================
class Gui {
public:
    static const uint8_t MAX_PAGES = 4;

    Gui() : m_count(0), m_active(0) {}

    void addPage(Page* p) {
        if (m_count < MAX_PAGES) m_pages[m_count++] = p;
    }
    uint8_t activePage() const { return m_active; }

    void setActivePage(uint8_t idx) {
        if (idx >= m_count) return;
        if (m_pages[m_active]) m_pages[m_active]->setVisible(false);
        m_active = idx;
        if (m_pages[m_active]) {
            LCD_SetForegroundColor(COL_BG);
            LCD_Rect(0, 0, SCREEN_W, SCREEN_H);
            m_pages[m_active]->setVisible(true);
            m_pages[m_active]->drawAll();
        }
    }
    void update() {}
    void handleTouch(uint16_t x, uint16_t y) {
        if (m_active < m_count) m_pages[m_active]->handleTouch(x, y);
    }

private:
    Page* m_pages[MAX_PAGES];
    uint8_t m_count;
    uint8_t m_active;
};

// =====================================================================
// Konkrete Instanzen und Buttons
// =====================================================================
static Gui    g_gui;
static Page   g_page0;
static Page   g_page1;

// Page 0 – Hauptseite
static Label   lbl_title0(20, 10, 400, 30, "WETTERSTATION", COL_HEADER_FG);
static Label   lbl_time(660, 15, 130, 30, g_timeBuf, COL_HEADER_FG);
static ValueDisplay vd_temp( 20,  80, 240, 130, "Temperatur",  "C");
static ValueDisplay vd_hum (280,  80, 240, 130, "Luftfeuchte", "%");
static ValueDisplay vd_pres(540,  80, 240, 130, "Luftdruck",   "hPa");

static void onNav1() { g_gui.setActivePage(1); }
static void onNav0() { g_gui.setActivePage(0); }

static Button btn_toP1(20, 380, 220, 70, "Details",       onNav1);
static Button btn_dummy(280, 380, 220, 70, "Seite 3",     NULL);
static Button btn_dummy2(540, 380, 220, 70, "Einstellungen", NULL);

// Page 1 – Detailseite
static Label  lbl_title1(20, 10, 400, 30, "DETAILS", COL_HEADER_FG);
static Label  lbl_info  (40, 100, 700, 30, "Details kommen spaeter hierhin.", COL_TEXT);

static Button btn_back  (20, 380, 220, 70, "< Zurueck", onNav0);

// =====================================================================
// C-Schnittstelle
// =====================================================================
extern "C" void gui_init(void) {
    LCD_SetForegroundColor(COL_BG);
    LCD_Rect(0, 0, SCREEN_W, SCREEN_H);

    LCD_SetForegroundColor(COL_HEADER_BG);
    LCD_Rect(0, 0, SCREEN_W, 50);

    g_page0.addWidget(&lbl_title0);
    g_page0.addWidget(&vd_temp);
    g_page0.addWidget(&vd_hum);
    g_page0.addWidget(&vd_pres);
    g_page0.addWidget(&btn_toP1);
    g_page0.addWidget(&btn_dummy);
    g_page0.addWidget(&btn_dummy2);
    g_page0.addWidget(&lbl_time); 

    g_page1.addWidget(&lbl_title1);
    g_page1.addWidget(&lbl_info);
    g_page1.addWidget(&btn_back);
    g_page1.addWidget(&lbl_time); 

    g_gui.addPage(&g_page0);
    g_gui.addPage(&g_page1);

    g_gui.setActivePage(0);
}

extern "C" void gui_update(void) { g_gui.update(); }
extern "C" void gui_touch(uint16_t x, uint16_t y) { g_gui.handleTouch(x, y); }

extern "C" void gui_setTemperature(float t) {
    vd_temp.setValue(t);
    if (g_gui.activePage() == 0) vd_temp.draw();
}
extern "C" void gui_setHumidity(float h) {
    vd_hum.setValue(h);
    if (g_gui.activePage() == 0) vd_hum.draw();
}
extern "C" void gui_setPressure(float p) {
    vd_pres.setValue(p);
    if (g_gui.activePage() == 0) vd_pres.draw();
}
extern "C" void gui_setTime(const char* timeStr) {
    snprintf(g_timeBuf, sizeof(g_timeBuf), "%s", timeStr);
    lbl_time.draw();   // ? immer zeichnen, da auf beiden Pages
}
