#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

void imu_init();
void imu_read(float* ax, float* ay, float* az);

#endif