#ifndef SYSTEM_H
#define SYSTEM_H
#include "stm32f4xx_hal.h"
#include "stdio.h"

int bh1750_init(void);
int bh1750_start(void);
int bh1750_read_lux(uint16_t *lux); //-1失败 1成功
//extern uint16_t bh1750_lux;

int bmp280_start(void); //-1失败 1成功
int bmp280_read_float(float *temperature,float *pressure, float *humidity);
//extern float bmp280_pressure,bmp280_temperature,bmp280_humidity;

//int MPU6050_start(void); //-1失败 1成功
//void mpu6050_read_data(double *KalmanAngleX,double *KalmanAngleY,double *Gz);

//void update_sensor_value(void);
#endif