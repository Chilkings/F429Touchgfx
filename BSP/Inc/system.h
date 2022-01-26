#ifndef SYSTEM_H
#define SYSTEM_H
#include "stm32f4xx_hal.h"
#include "stdio.h"



//extern uint16_t bh1750_lux;

//int MPU6050_start(void); //-1Ê§°Ü 1³É¹¦
//void mpu6050_read_data(double *KalmanAngleX,double *KalmanAngleY,double *Gz);

void update_sensor_value(void);
#endif