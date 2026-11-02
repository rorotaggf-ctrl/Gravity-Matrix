#include "clock_view.h"
#include "config.h"
#include <math.h>

static const int16_t cx = 120;
static const int16_t cy = 120;
static const int16_t r = 105;

static uint8_t sec = 0;
static uint8_t min = 42;
static uint8_t std = 10;
static uint32_t last_tick = 0;

static int16_t old_hx = cx, old_hy = cy;
static int16_t old_mx = cx, old_my = cy;
static int16_t old_sx = cx, old_sy = cy;

static void draw_face(Adafruit_ST7789 *d)
{
    d->fillScreen(c_black);
    d->drawCircle(cx, cy, r, c_gold);
    d->drawCircle(cx, cy, r - 1, c_gold);
    d->drawCircle(cx, cy, r - 6, c_dark);

    for (int i = 0; i < 12; i++)
    {
        float angle = i * (PI / 6.0f);
        int16_t x1 = cx + (int16_t)(sin(angle) * (r - 12));
        int16_t y1 = cy - (int16_t)(cos(angle) * (r - 12));
        int16_t x2 = cx + (int16_t)(sin(angle) * (r - 3));
        int16_t y2 = cy - (int16_t)(cos(angle) * (r - 3));
        d->drawLine(x1, y1, x2, y2, c_white);
    }
}

void clock_init(Adafruit_ST7789 *d)
{
    draw_face(d);
    last_tick = millis();
    old_hx = cx;
    old_hy = cy;
    old_mx = cx;
    old_my = cy;
    old_sx = cx;
    old_sy = cy;
}

uint8_t clock_run(Adafruit_ST7789 *d, float ax, float ay)
{
    //stark schütteln/neigen = abbruch
    if (fabs(ax) > 1.7f || fabs(ay) > 1.7f)
    {
        return 1;
    }

    if (millis() - last_tick >= 1000)
    {
        last_tick += 1000;
        sec++;
        if (sec >= 60)
        {
            sec = 0;
            min++;
            if (min >= 60)
            {
                min = 0;
                std = (std + 1) % 12;
            }
        }

        //alte Zeiger löschen
        d->drawLine(cx, cy, old_hx, old_hy, c_black);
        d->drawLine(cx, cy, old_mx, old_my, c_black);
        d->drawLine(cx, cy, old_sx, old_sy, c_black);

        //winkel berechnen
        float s_ang = sec * (PI / 30.0f);
        float m_ang = (min + sec / 60.0f) * (PI / 30.0f);
        float h_ang = ((std % 12) + min / 60.0f) * (PI / 6.0f);

        // 3. Neue Endpunkte berechnen
        old_sx = cx + (int16_t)(sin(s_ang) * (r - 18));
        old_sy = cy - (int16_t)(cos(s_ang) * (r - 18));

        old_mx = cx + (int16_t)(sin(m_ang) * (r - 28));
        old_my = cy - (int16_t)(cos(m_ang) * (r - 28));

        old_hx = cx + (int16_t)(sin(h_ang) * (r - 50));
        old_hy = cy - (int16_t)(cos(h_ang) * (r - 50));

        //neue Zeiger 
        d->drawLine(cx, cy, old_hx, old_hy, c_cyan);
        d->drawLine(cx, cy, old_mx, old_my, c_white);
        d->drawLine(cx, cy, old_sx, old_sy, c_red);

        // Mittelpunkt
        d->fillCircle(cx, cy, 3, c_gold);
    }
    return 0;
}