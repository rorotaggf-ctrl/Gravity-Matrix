#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>

#include "config.h"
#include "imu.h"
#include "clock_view.h"

Adafruit_ST7789 tft = Adafruit_ST7789(PIN_CS, PIN_DC, PIN_MOSI, PIN_SCLK, PIN_RST);

void setup() {
    Serial.begin(115200);

    tft.init(DISP_W, DISP_H, SPI_MODE3);
    tft.setRotation(2);
    tft.fillScreen(c_black);

    imu_init();
    clock_init(&tft);
}

void loop() {
    float ax = 0, ay = 0, az = 0;
    imu_read(&ax, &ay, &az);

    if (clock_run(&tft, ax, ay) == 1) {
        clock_init(&tft);
        delay(200);
    }

    delay(20);
}