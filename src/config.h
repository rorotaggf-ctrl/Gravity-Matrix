#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Display Pins (ST7789 SPI)
#define PIN_MOSI 23
#define PIN_SCLK 18
#define PIN_CS   -1
#define PIN_DC   2
#define PIN_RST  4

// Sensor Pins (MPU-6050 I2C)
#define PIN_SDA  21
#define PIN_SCL  22

// Bildschirm-Maße
#define DISP_W 240
#define DISP_H 240

// Farben
//RGB565
#define c_black   0x0000
#define c_white   0xFFFF
#define c_red     0xF800
#define c_green   0x07E0
#define c_blue    0x001F
#define c_yellow  0xFFE0
#define c_cyan    0x07FF
#define c_gray    0x39E7
#define c_dark    0x18C3
#define c_gold    0xFEA0

#endif