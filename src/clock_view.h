#ifndef CLOCK_VIEW_H
#define CLOCK_VIEW_H

#include <Adafruit_ST7789.h>

void clock_init(Adafruit_ST7789* d);
uint8_t clock_run(Adafruit_ST7789* d, float ax, float ay);

#endif