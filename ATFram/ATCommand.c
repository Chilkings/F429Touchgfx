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

/* ATָ���OK�󣬿��ܻ��ᷢ�Ͷ������Ϣ��ʹ�ô˺����趨��ʱʱ����ղ���� */
void Clear_RxData(uint32_t ms)  
{
	BaseType_t xResult;
	//�ȴ��жϽ���������
	xResult=xSemaphoreTake(ATRXCplSemaphore,pdMS_TO_TICKS(ms));
	if(xResult != pdPASS)
	{	//�ȴ����ݳ�ʱ��˵��û���������ݣ�ֱ�ӷ���
		return;
	}
	else
	{
		__HAL_DMA_DISABLE(&_UART_DMA_HANDLE); //����dma���գ�����޹����ݣ���֤�������ɾ�
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
	HAL_Delay(1000); //ʹ�ô���ʱ������е���
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


