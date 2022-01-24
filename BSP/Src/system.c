#include "system.h"

uint16_t bh1750_lux = {0};
float bmp280_pressure,bmp280_temperature,bmp280_humidity={0};
//double mpu6050_x,mpu6050_y,mpu6050_z={0};

void update_sensor_value()
{
	bh1750_read_lux(&bh1750_lux);
	bmp280_read_float(&bmp280_temperature, &bmp280_pressure, &bmp280_humidity);
	printf("Pressure: %.2f Pa, Temperature: %.2f C\r\n",bmp280_pressure, bmp280_temperature);
	printf("lux: %.2d\r\n",bh1750_lux);
}




