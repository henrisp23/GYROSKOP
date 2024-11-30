#ifndef GYRO_H
#define GYRO_H

#include <Wire.h>

#define GYRO_ADDR 0x68

#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B

#if DEBUG == 1
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

typedef struct _mpu6050_data {
  int16_t accel_x;
  int16_t accel_y;
  int16_t accel_z;
  int16_t temp;
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
} mpu6050_data;

mpu6050_data RAW_DATA       = {0, 0, 0, 0, 0, 0, 0};
mpu6050_data OFFSET_DATA    = {0, 0, 0, 0, 0, 0, 0};


void gyro_mpu6050_init();

void gyro_mpu6050_read();

void gyro_mpu6050_print();

void gyro_mpu6050_set_offset(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz);

void gyro_mpu6050_init() {
    Wire.begin();
    Wire.beginTransmission(GYRO_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission(true);
}

void gyro_mpu6050_read() {
    Wire.beginTransmission(GYRO_ADDR);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission(false);
    Wire.requestFrom( (uint8_t)GYRO_ADDR, (size_t)14);

    RAW_DATA.accel_x    = ((Wire.read() << 8) | Wire.read()) + OFFSET_DATA.accel_x;
    RAW_DATA.accel_y    = ((Wire.read() << 8) | Wire.read()) + OFFSET_DATA.accel_y;
    RAW_DATA.accel_z    = ((Wire.read() << 8) | Wire.read()) + OFFSET_DATA.accel_z;

    RAW_DATA.temp       = (Wire.read() << 8) | Wire.read();

    RAW_DATA.gyro_x     = ((Wire.read() << 8) | Wire.read()) + OFFSET_DATA.gyro_x;
    RAW_DATA.gyro_y     = ((Wire.read() << 8) | Wire.read()) + OFFSET_DATA.gyro_y;
    RAW_DATA.gyro_z     = ((Wire.read() << 8) | Wire.read()) + OFFSET_DATA.gyro_z;
}

// set offset MPU6050
void gyro_mpu6050_set_offset(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz) {
    OFFSET_DATA.accel_x     = ax;
    OFFSET_DATA.accel_y     = ay;
    OFFSET_DATA.accel_z     = az;
    OFFSET_DATA.gyro_x      = gx;
    OFFSET_DATA.gyro_y      = gy;
    OFFSET_DATA.gyro_z      = gz;
    
}

void gyro_mpu6050_print() {
    Serial.print("Accel X: ");
    Serial.print(RAW_DATA.accel_x);
    Serial.print(" | Accel Y: ");
    Serial.print(RAW_DATA.accel_y);
    Serial.print(" | Accel Z: ");
    Serial.print(RAW_DATA.accel_z);
    Serial.print(" | Gyro X: ");
    Serial.print(RAW_DATA.gyro_x);
    Serial.print(" | Gyro Y: ");
    Serial.print(RAW_DATA.gyro_y);
    Serial.print(" | Gyro Z: ");
    Serial.println(RAW_DATA.gyro_z);
}



#endif