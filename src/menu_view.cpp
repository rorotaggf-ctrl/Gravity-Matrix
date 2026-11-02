#include "menu_view.h"
#include "config.h"
#include <math.h>

static uint8_t sel = 0; // 0 = Sanduhr, 1 = Analoge Uhr
static bool redraw = true;
static uint32_t t_tilt = 0;

void menu_init(Adafruit_ST7789 *d)
{
    sel = 0;
    redraw = true;
    t_tilt = millis();
}

static void draw_ui(Adafruit_ST7789 *d)
{
    d->fillScreen(c_black);

    d->setTextSize(2);
    d->setTextColor(c_gold);
    d->setCursor(35, 15);
    d->print("GRAVITY MATRIX");

    // Kachel 1: Sanduhr
    uint16_t b1 = (sel == 0) ? c_green : c_gray;
    d->drawRoundRect(20, 50, 200, 65, 8, b1);
    if (sel == 0)
        d->drawRoundRect(21, 51, 198, 63, 7, b1);
    d->setTextColor(sel == 0 ? c_green : c_white);
    d->setCursor(40, 72);
    d->print("1. SANDUHR");

    // Kachel 2: Analoge Uhr
    uint16_t b2 = (sel == 1) ? c_green : c_gray;
    d->drawRoundRect(20, 130, 200, 65, 8, b2);
    if (sel == 1)
        d->drawRoundRect(21, 131, 198, 63, 7, b2);
    d->setTextColor(sel == 1 ? c_green : c_white);
    d->setCursor(40, 152);
    d->print("2. ANALOG CLOCK");

    d->setTextSize(1);
    d->setTextColor(c_cyan);
    d->setCursor(25, 215);
    d->print("KIPPEN: WAHL | SCHUETTELN: START");
}

int8_t menu_run(Adafruit_ST7789 *d, float ax, float ay, float az)
{
    if (redraw)
    {
        draw_ui(d);
        redraw = false;
    }

    // Navigation per Neigung (Y-Achse)
    if (millis() - t_tilt > 280)
    {
        if (ay > 0.45f && sel != 1)
        {
            sel = 1;
            redraw = true;
            t_tilt = millis();
        }
        else if (ay < -0.45f && sel != 0)
        {
            sel = 0;
            redraw = true;
            t_tilt = millis();
        }
    }

    // Auswahl bestätigen durch Vorneigen (Z-Achse) oder Stoß
    if (fabs(ax) > 1.35f || az < -0.6f)
    {
        delay(150);
        return sel + 1; // 1 = Sanduhr, 2 = Analoge Uhr
    }

    return 0;
}