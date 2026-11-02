#ifndef SAND_VIEW_H
#define SAND_VIEW_H

#include <Adafruit_ST7789.h>

void sand_init(Adafruit_ST7789* d);
uint8_t sand_run(Adafruit_ST7789* d, float ax, float ay);

#endif