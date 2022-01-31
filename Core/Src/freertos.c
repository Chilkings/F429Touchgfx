/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "AT.h"
//#include "MY_Bm280_Bh1750.h"
#include "cJSON.h"
#include "system.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId ATParseHandle;
osThreadId ATFramHandle;
osThreadId ATSendHandle;
osThreadId SensorCollectHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartATParse(void const * argument);
void StartATFram(void const * argument);
void StartATSend(void const * argument);
void StartSensorCollect(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 2048);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of ATParse */
  osThreadDef(ATParse, StartATParse, osPriorityLow, 0, 512);
  ATParseHandle = osThreadCreate(osThread(ATParse), NULL);

  /* definition and creation of ATFram */
  osThreadDef(ATFram, StartATFram, osPriorityNormal, 0, 256);
  ATFramHandle = osThreadCreate(osThread(ATFram), NULL);

  /* definition and creation of ATSend */
  osThreadDef(ATSend, StartATSend, osPriorityLow, 0, 256);
  ATSendHandle = osThreadCreate(osThread(ATSend), NULL);

  /* definition and creation of SensorCollect */
  osThreadDef(SensorCollect, StartSensorCollect, osPriorityLow, 0, 128);
  SensorCollectHandle = osThreadCreate(osThread(SensorCollect), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	MX_TouchGFX_Process();
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartATParse */
/**
* @brief Function implementing the ATParse thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartATParse */
void StartATParse(void const * argument)
{
  /* USER CODE BEGIN StartATParse */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
		if(uxQueueSpacesAvailable(ATcmdQueue)==10)//队列为空
		{
			if(xSemaphoreTake(ATSchRunSemaphore,( TickType_t ) 10)==pdTRUE) //获得互斥量:上锁 
			{
				PrintIotRxData();
				xSemaphoreGive(ATSchRunSemaphore);/* 释放互斥量: 开锁 */
			}
		}
  }
  /* USER CODE END StartATParse */
}

/* USER CODE BEGIN Header_StartATFram */
/**
* @brief Function implementing the ATFram thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartATFram */
void StartATFram(void const * argument)
{
  /* USER CODE BEGIN StartATFram */
	HAL_GPIO_WritePin(Iot_Reset_GPIO_Port,Iot_Reset_Pin,GPIO_PIN_RESET);		//复位
	osDelay(500);
	HAL_GPIO_WritePin(Iot_Reset_GPIO_Port,Iot_Reset_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(IOTpower_GPIO_Port,IOTpower_Pin,GPIO_PIN_RESET);      //开机
	osDelay(2200);
	HAL_GPIO_WritePin(IOTpower_GPIO_Port,IOTpower_Pin,GPIO_PIN_SET);
  
	printf("联网中...");
	while(strstr(UartRXBuff,"IP")==NULL)//等待设备联网
	{
		printf(".");
		osDelay(1000);
	}
	printf("\r\n联网成功!");
	PrintIotRxData();
  /* Infinite loop */
  for(;;)
  {
    ATCommandSendScheduler();
  }
  /* USER CODE END StartATFram */
}

/* USER CODE BEGIN Header_StartATSend */
/**
* @brief Function implementing the ATSend thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartATSend */
void StartATSend(void const * argument)
{
  /* USER CODE BEGIN StartATSend */
	static char PubParam[400];
	char * jsonRes;
	
	ATCommandRegister(AT,EXEXCMD,NULL);
	ATCommandRegister(MQTTCFG,WRITECMD,"\"a1wocurZ0R0.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,\"711382|securemode=3,signmethod=hmacsha1|\",\"60\",\"M5311_1382&a1wocurZ0R0\",\"A40C776AD48B66A8DB8A5EEE517625E2DB4501B4\",1");
	ATCommandRegister(MQTTOPEN,WRITECMD,"1,1,0,0,0");
	ATCommandRegister(MQTTSUB,WRITECMD,"/sys/a1wocurZ0R0/M5311_1382/thing/service/property/set");
	ATCommandRegister(CCLK,READCMD,NULL);
  /* Infinite loop */
  for(;;)
  {
		osDelay(10000);
//		osDelay(10000);
		while(uxQueueSpacesAvailable(ATcmdQueue)!=10)//等待队列为空
		{
			osDelay(100);
		}
		cJSON* cjson_root = NULL;
		cJSON* cjson_params = NULL;
		cjson_root =  cJSON_CreateObject();
		cjson_params  =  cJSON_CreateObject();
		cJSON_AddNumberToObject(cjson_params,"CurrentTemperature",bmp280_temperature);
		cJSON_AddNumberToObject(cjson_params,"CurrentHumidity",(uint32_t)12);
		cJSON_AddNumberToObject(cjson_params,"LightLux",(uint32_t)bh1750_lux);
		cJSON_AddNumberToObject(cjson_params,"Atmosphere",(uint32_t)bmp280_pressure);
		cJSON_AddNumberToObject(cjson_params,"lie",34);
		cJSON_AddItemToObject(cjson_root,"params",cjson_params);
		jsonRes = cJSON_Print(cjson_root);
		sprintf(PubParam,"\"/sys/a1wocurZ0R0/M5311_1382/thing/event/property/post\",1,1,0,0,\"%s\"",jsonRes);
//			printf("上报数据：%s\n\r",jsonRes);
//			printf("AT+MQTTPUB=\"/sys/a1wocurZ0R0/M5311_1382/thing/event/property/post\",1,1,0,0,\"%s\"\r\n",jsonRes);
		cJSON_Delete(cjson_root);				//删除Json数组
		vPortFree(jsonRes);							//释放内存不释放就会出错

//		__LOG("上报数据：%s\r\n",PubParam);
//			IOT_printf("%s\r\n",PubParam);
		ATCommandRegister(MQTTPUB,WRITECMD,PubParam);

  }
  /* USER CODE END StartATSend */
}

/* USER CODE BEGIN Header_StartSensorCollect */
/**
* @brief Function implementing the SensorCollect thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorCollect */
void StartSensorCollect(void const * argument)
{
  /* USER CODE BEGIN StartSensorCollect */
  /* Infinite loop */
  for(;;)
  {
		update_sensor_value();
    osDelay(1000);
  }
  /* USER CODE END StartSensorCollect */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
