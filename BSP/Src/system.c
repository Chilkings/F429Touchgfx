#include "system.h"
#include "bh1750.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "mk_dht11.h"

extern TIM_HandleTypeDef htim1;

uint16_t bh1750_lux = {0};
float bmp280_pressure,bmp280_temperature,bmp280_humidity={0};
MPU6050_t MPU6050;
int time_hours=12,time_minutes=0,time_seconds=0,time_years=2022,time_mouths=1,time_days =1;
int isConnectNetwork=0;
int dht_temperature,dht_humidty;
dht11_t dht={
	GPIOC,
	GPIO_PIN_4,
	&htim1
};


void update_sensor_value()
{
	bh1750_read_lux(&bh1750_lux);
	bmp280_read_float(&bmp280_temperature, &bmp280_pressure, &bmp280_humidity);
//	MPU6050_Read_All(&MPU6050_I2C_HANDLE, &MPU6050);
//	MPU6050_Read_Gyro(&MPU6050_I2C_HANDLE, &MPU6050);
//	printf("lux: %.2d\r\n",bh1750_lux);
//	printf("Pressure: %.2f Pa, Temperature: %.2f C\r\n",bmp280_pressure, bmp280_temperature);
//	printf("MPU6050 X:%f Y:%f Z:%f\r\n",MPU6050.Gyro_X_RAW,MPU6050.Accel_Y_RAW,MPU6050.Gyro_Z_RAW);
	readDHT11(&dht);
	dht_temperature = dht.temperature;
	dht_humidty = dht.humidty;
  
}

//	mpu6050_start();
//	while(1)
//	{
//		  uint8_t dat=0;
//		  SFIIC_Mem_Read(&MPU6050_I2C_HANDLE, 0xD0, 0x75, 1, &dat, 1, 0xFFFF);
//			printf("mpu6050 ID:0x%x\r\n",dat);
//			HAL_Delay(100);
//	}


