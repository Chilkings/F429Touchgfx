#ifndef SYSTEM_H
#define SYSTEM_H
#include "stm32f4xx_hal.h"
#include "stdio.h"

#define	LED2(state)	{if(state == 0)					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);	}
#define LED2_T		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)						

#define	LED3(state)	{if(state == 0)					HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);	}
#define LED3_T		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin)	

#define	LED4(state)	{if(state == 0)					HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);	}
#define LED4_T		HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin)	

#define	LED5(state)	{if(state == 0)					HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);\
												 else if(state == 1)	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);	}
#define LED5_T		HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin)					

#define	RELAY1(state)	{if(state == 0)					HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_SET);\
												 else if(state == 1)	HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_RESET);	}
#define	RELAY2(state)	{if(state == 0)					HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_SET);\
												 else if(state == 1)	HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_RESET);	}


extern uint16_t bh1750_lux ;
extern float bmp280_pressure,bmp280_temperature,bmp280_humidity;

extern int time_hours,time_minutes,time_seconds,time_years,time_mouths,time_days;
extern int isConnectNetwork;
extern int dht_temperature,dht_humidty;

//extern uint16_t bh1750_lux;


void update_sensor_value(void);
void alarm_led_buzzer(void);
void CJSON_analysis(char * str);
#endif