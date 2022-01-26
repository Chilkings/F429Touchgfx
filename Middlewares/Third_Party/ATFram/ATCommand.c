#include "ATCommand.h"
#include "AT.h"
#include "string.h"
#include "log.h"
#include "stdio.h"
#include "cmsis_os.h"

typedef struct 
{
	char* RxBuff;
	int   len;
}RxStrInfo;

char DateHandleBuff[512];
RxStrInfo RxHandleInfo;

/* AT指令返回OK后，可能还会发送额外的信息，使用此函数设定超时时间接收并清除 */
void Clear_RxData(uint32_t ms)  
{
	BaseType_t xResult;
	//等待中断接收完数据
	xResult=xSemaphoreTake(ATRXCplSemaphore,pdMS_TO_TICKS(ms));
	if(xResult != pdPASS)
	{	//等待数据超时，说明没有垃圾数据，直接返回
		return;
	}
	else
	{
		__HAL_DMA_DISABLE(&_UART_DMA_HANDLE); //重启dma接收，清空无关数据，保证缓冲区干净
	}
}


ATStatus AT_Callback(char * str)
{
	__LOG("M5311 init ok!\r\n");
	return ATSUCCESS;
}


ATStatus CCLK_Callback(char * str)
{	
	return ATSUCCESS;
}

ATStatus MQTTCFG_Callback(char *str)
{	
	__LOG("M5311 MQTTCFG OK!\r\n");
	return ATSUCCESS;
}

ATStatus MQTTOPEN_Callback(char *str)
{
	__LOG("M5311 OPEN OK!\r\n");
	Clear_RxData(5000);
	return ATSUCCESS;
}

ATStatus MQTTSUB_Calback(char *str)
{
	return ATSUCCESS;
}
ATStatus MQTTPUB_Callback(char *str)
{
	HAL_Delay(1000); //使用此延时不会进行调度
	Clear_RxData(3000);	
	__LOG("M5311 PUB OK!\r\n");
	return ATSUCCESS;
}
ATStatus NSOSD_Callback(char *str)
{
	return ATSUCCESS;
}
ATStatus NSORF_Callback(char *str)
{
	return ATSUCCESS;
}


