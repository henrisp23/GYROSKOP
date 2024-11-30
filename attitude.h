#ifndef GYRO_ATTITUDE_H
#define GYRO_ATTITUDE_H

#include "MPU6050.h"

#if DEBUG == 1
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

typedef struct _quaternion {
  float w;
  float x;
  float y;
  float z;
} GYRO_QUATERNION;

typedef struct _ahrs_data {
  float roll; // -180 - 180 derajat
  float pitch; // -90 - 90 derajat
  float direction; // 0 - 360 derajat
} GYRO_AHRS;


GYRO_AHRS ahrs = {0.0, 0.0, 0.0};

void gyro_ahrs_init();

void gyro_ahrs_compute();

void gyro_ahrs_print();

void gyro_ahrs_init() {
  gyro_mpu6050_init();
}

void gyro_ahrs_compute() {
  
  gyro_mpu6050_read();
  gyro_mpu6050_print();
  ahrs.roll = atan2(RAW_DATA.accel_y, RAW_DATA.accel_z) * 180 / M_PI;
  ahrs.pitch = -atan2(-RAW_DATA.accel_x, RAW_DATA.accel_z) * 180 / M_PI;
}

// cetak AHRS
void gyro_ahrs_print() {
  DEBUG_PRINT("Roll: ");
  DEBUG_PRINT(ahrs.roll);
  DEBUG_PRINT(" Pitch: ");
  DEBUG_PRINT(ahrs.pitch);
  DEBUG_PRINT(" Direction: ");
  DEBUG_PRINT(ahrs.direction);
  DEBUG_PRINTLN("");
}


#endif