#include "ATCommand.h"
#include "AT.h"
#include "string.h"
#include "log.h"
#include "stdio.h"
#include "cmsis_os.h"

#include "system.h"
#include "time.h"

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
	//+CCLK: 22/01/28,03:04:54+32
//	time_years = ( (*(str+7)-'0')*10 + (*(str+8)-'0') + 2000);
//	time_hours   = ( (*(str+16)-'0')*10 + (*(str+17)-'0') + 8) %24;
//	time_minutes = (*(str+19)-'0')*10 + (*(str+20)-'0');
//	time_seconds = (*(str+22)-'0')*10 + (*(str+23)-'0');
	
//	struct tm t; //��׼ʱ��
//  struct tm *t2;//������ʱ��
//	
//	t.tm_year = ( (*(str+7)-'0')*10 + (*(str+8)-'0') + 2000)-1900; 
//	t.tm_mon =  (*(str+10)-'0')*10 + (*(str+11)-'0')-1;
//	t.tm_mday = (*(str+13)-'0')*10 + (*(str+14)-'0');
//	t.tm_hour = (*(str+16)-'0')*10 + (*(str+17)-'0');
//	t.tm_min =  (*(str+19)-'0')*10 + (*(str+20)-'0');
//	t.tm_sec =  (*(str+22)-'0')*10 + (*(str+23)-'0');
//	
//	time_t tt = mktime(&t);
//	printf("tt value %d\r\n",tt);
//	*t2 = *gmtime(&tt);
//	
//	time_years  =  t2->tm_year+1900;
//	time_mouths =  t2->tm_mon+1;
//	time_days   =  t2->tm_mday;
//	time_hours   = t2->tm_hour;
//	time_minutes = t2->tm_min;
//	time_seconds = t2->tm_sec;	
//	printf("%.4d-%.2d-%.2d %.2d:%.2d:%.2d", t2->tm_year + 1900,
//    t2->tm_mon + 1, t2->tm_mday, t2->tm_hour, t2->tm_min,
//    t2->tm_sec);
//	printf("TIME is: %d:%d:%d:%d:%d:%d\r\n",time_years,time_mouths,time_days,time_hours,time_minutes,time_seconds);
	
	time_years = ( (*(str+7)-'0')*10 + (*(str+8)-'0') + 2000); 
	time_mouths =  (*(str+10)-'0')*10 + (*(str+11)-'0');
	time_days = (*(str+13)-'0')*10 + (*(str+14)-'0');
	time_hours = ( (*(str+16)-'0')*10 + (*(str+17)-'0') + 8) %24;
	time_minutes =  (*(str+19)-'0')*10 + (*(str+20)-'0');
	time_seconds =  (*(str+22)-'0')*10 + (*(str+23)-'0');
	
//  printf("TIME is: %d:%d:%d:%d:%d:%d\r\n",time_years,time_mouths,time_days,time_hours,time_minutes,time_seconds);
	isConnectNetwork = 1 ; //��ȡ��ʱ�䣬˵�������ɹ�
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


