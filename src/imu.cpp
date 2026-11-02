#include "imu.h"
#include <Wire.h>
#include "config.h"

#define MPU_ADDR 0x68

void imu_init() {
    Wire.begin(PIN_SDA, PIN_SCL, 400000);
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); //Power Managment Register (PMR)
    Wire.write(0x00); //https://www.youtube.com/watch?v=rX_boXaztmE&t=8s
                      //https://tinyurl.com/GUUTENMORGEN
    Wire.endTransmission(true);
}

void imu_read(float* ax, float* ay, float* az) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom((uint16_t)MPU_ADDR, (uint8_t)6, true);

    if (Wire.available() >= 6) {
        int16_t raw_x = (Wire.read() << 8) | Wire.read();
        int16_t raw_y = (Wire.read() << 8) | Wire.read();
        int16_t raw_z = (Wire.read() << 8) | Wire.read();

        *ax = (float)raw_x / 16384.0f;
        *ax = (float)raw_y / 16384.0f;
        *az = (float)raw_z / 16384.0f;
    }
}