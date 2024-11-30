#include "MPU6050.h"
#include "attitude.h"

#define DEBUG 1



#if DEBUG == 1
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif


uint32_t last_time = 0;
uint32_t interval_set = 1000/1;
void setup() {
  Serial.begin(115200);
  henry_ahrs_init();
  // accel x, y, z, gyro x, y, z
  henry_mpu6050_set_offset(-708, -28, 0, 476, 144, 7);
  last_time = millis();
}



void loop() {
  uint32_t current_time = millis();
  if(current_time - last_time > interval_set) {
    henry_ahrs_compute();
    // cetak AHRS
    henry_ahrs_print();
    last_time = current_time;
    return;
  }
  
  

}
