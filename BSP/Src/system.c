#include "system.h"
#include "bh1750.h"
#include "bmp280.h"
#include "mpu6050.h"
#include "mk_dht11.h"
#include "cJSON.h"


extern TIM_HandleTypeDef htim14;

uint16_t bh1750_lux = {0};
float bmp280_pressure,bmp280_temperature,bmp280_humidity={0};
MPU6050_t MPU6050;
int time_hours=12,time_minutes=0,time_seconds=0,time_years=2022,time_mouths=1,time_days =1;
int isConnectNetwork=0;
int dht_temperature,dht_humidty;
dht11_t dht={
	GPIOC,
	GPIO_PIN_7,
	&htim14
};


void update_sensor_value()
{
	bh1750_read_lux(&bh1750_lux);
	bmp280_read_float(&bmp280_temperature, &bmp280_pressure, &bmp280_humidity);
	HAL_Delay(100);//±ÜÃâÊ±ÐòÎÊÌâ
//	MPU6050_Read_All(&MPU6050_I2C_HANDLE, &MPU6050);
//	MPU6050_Read_Gyro(&MPU6050_I2C_HANDLE, &MPU6050);
//	printf("lux: %.2d\r\n",bh1750_lux);
//	printf("Pressure: %.2f Pa, Temperature: %.2f C\r\n",bmp280_pressure, bmp280_temperature);
//	printf("MPU6050 X:%f Y:%f Z:%f\r\n",MPU6050.Gx,MPU6050.Gy,MPU6050.Gz);
	readDHT11(&dht);
	dht_temperature = dht.temperature;
	dht_humidty = dht.humidty;
}

void alarm_led_buzzer()
{
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
		osDelay(1000);
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
}

void CJSON_analysis(char * str)
{
	uint8_t Relay1=0;
	cJSON* cjson_all = NULL;
	cJSON* cjson_Relay1_all = NULL;
	cJSON* cjson_Relay1_value = NULL;
	cjson_all = cJSON_Parse(str);
	if(cjson_all == NULL)
	{
		printf("\r\nparse fail.\n");
		return ;
	}
	else 
		printf("\r\nparse success\r\n");
	
	cjson_Relay1_all = cJSON_GetObjectItem(cjson_all,"Relay1");
	if(cjson_Relay1_all!=NULL)
	{
			cjson_Relay1_value = cJSON_GetObjectItem(cjson_Relay1_all,"value");
	    Relay1 = cjson_Relay1_value->valueint;
		  LED5(Relay1);
	    printf("RELAY1: %d\r\n",Relay1);
	}

	
	cJSON_Delete(cjson_all);
}
