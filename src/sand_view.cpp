#include "sand_view.h"
#include "config.h"
#include <math.h>

#define GRID_W 60
#define GRID_H 60
#define SCALE 4

static uint8_t grid[GRID_W][GRID_H];
static uint8_t next_grid[GRID_W][GRID_H];
static uint32_t t_last = 0;

static void clear_all()
{
    for (int x = 0; x < GRID_W; x++)
    {
        for (int y = 0; y < GRID_H; y++)
        {
            grid[x][y] = 0;
            next_grid[x][y] = 0;
        }
    }
}

void sand_init(Adafruit_ST7789 *d)
{
    d->fillScreen(c_black);
    clear_all();

    // Sanduhr-Kontur zeichnen (Sandglas-Kammer)
    d->drawRect(0, 0, DISP_W, DISP_H, c_gold);

    // Initialer Sandblock in der oberen Hälfte (ca. 400 Körner)
    for (int x = 20; x < 40; x++)
    {
        for (int y = 10; y < 30; y++)
        {
            grid[x][y] = 1;
            d->fillRect(x * SCALE, y * SCALE, SCALE, SCALE, c_yellow);
        }
    }
    t_last = millis();
}

uint8_t sand_run(Adafruit_ST7789 *d, float ax, float ay)
{
    // Starkes Schütteln / Überkopf-Kippen beendet den Modus
    if (fabs(ax) > 2.2f || fabs(ay) > 2.2f)
    {
        return 1;
    }

    if (millis() - t_last < 25)
    {
        return 0;
    }
    t_last = millis();

    // Gravitationsrichtung quantisieren
    int8_t gx = 0;
    int8_t gy = 0;
    if (ax > 0.25f)
        gx = 1;
    else if (ax < -0.25f)
        gx = -1;

    if (ay > 0.25f)
        gy = 1;
    else if (ay < -0.25f)
        gy = -1;

    if (gx == 0 && gy == 0)
        gy = 1; // Standard-Gravitation nach unten

    for (int x = 0; x < GRID_W; x++)
    {
        for (int y = 0; y < GRID_H; y++)
        {
            next_grid[x][y] = grid[x][y];
        }
    }

    // Partikelbewegung mit Richtungs-Scan
    int y_start = (gy >= 0) ? GRID_H - 1 : 0;
    int y_end = (gy >= 0) ? -1 : GRID_H;
    int y_step = (gy >= 0) ? -1 : 1;

    for (int y = y_start; y != y_end; y += y_step)
    {
        for (int x = 0; x < GRID_W; x++)
        {
            if (grid[x][y] == 1)
            {
                int nx = x + gx;
                int ny = y + gy;

                // 1. Direkt in Richtung Schwerkraft
                if (nx >= 0 && nx < GRID_W && ny >= 0 && ny < GRID_H && next_grid[nx][ny] == 0)
                {
                    next_grid[x][y] = 0;
                    next_grid[nx][ny] = 1;
                }
                // 2. Seitliches Abrutschen bei Hindernissen (natürlicher Schüttwinkel)
                else
                {
                    int alt_x1 = x + gy;
                    int alt_y1 = y + gx;
                    int alt_x2 = x - gy;
                    int alt_y2 = y - gx;

                    if (alt_x1 >= 0 && alt_x1 < GRID_W && alt_y1 >= 0 && alt_y1 < GRID_H && next_grid[alt_x1][alt_y1] == 0)
                    {
                        next_grid[x][y] = 0;
                        next_grid[alt_x1][alt_y1] = 1;
                    }
                    else if (alt_x2 >= 0 && alt_x2 < GRID_W && alt_y2 >= 0 && alt_y2 < GRID_H && next_grid[alt_x2][alt_y2] == 0)
                    {
                        next_grid[x][y] = 0;
                        next_grid[alt_x2][alt_y2] = 1;
                    }
                }
            }
        }
    }

    // Display-Update (nur veränderte Körner neu zeichnen)
    for (int x = 0; x < GRID_W; x++)
    {
        for (int y = 0; y < GRID_H; y++)
        {
            if (grid[x][y] != next_grid[x][y])
            {
                uint16_t c = (next_grid[x][y] == 1) ? c_yellow : c_black;
                d->fillRect(x * SCALE, y * SCALE, SCALE, SCALE, c);
                grid[x][y] = next_grid[x][y];
            }
        }
    }

    return 0;
}