#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <Adafruit_ST7789.h>

void menu_init(Adafruit_ST7789 *d);
int8_t menu_run(Adafruit_ST7789 *d, float ax, float ay, float az);

#endif