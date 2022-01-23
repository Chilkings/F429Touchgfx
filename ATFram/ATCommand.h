#ifndef _ATCOMMAND_H_
#define _ATCOMMAND_H_

#include "log.h"

typedef enum 
{
	ATERROR = 0, 
	ATSUCCESS ,
	ATERRORCODE1,
}ATStatus;

typedef enum 
{
	EXEXCMD,
	TESTCMD,
	READCMD,
	WRITECMD,
}CmdType;

typedef ATStatus (*pFuncCallback)(char* str);

typedef enum 
{
	AT=0,
	CCLK	,MQTTCFG	,MQTTOPEN,	
	MQTTSUB	,MQTTPUB	,NSOSD,	
	NSORF	,
	/**��ָ����ӵ�����**/
	MAXCMDNUM
}ATCommand;

typedef struct
{		
	ATCommand	ATCommandName;
	char * 		ATStr;				//���͵�ATָ��
	uint16_t  	MaxResponseTime;	//���ͺ��ѯ������Ϣ����ʱ��msΪ��λ������Ϊָ�������Ӧʱ�䡣
	uint8_t   	MaxTryCount; 		//������Դ���
	uint8_t   	MaxResetCount; 		//�����������
	pFuncCallback		ATRxCpltCallback;	//ATָ�������ɣ�ָ���ص�����
} ATCommandConfig;


ATStatus AT_Callback(char * str);
ATStatus CCLK_Callback(char * str);
ATStatus MQTTCFG_Callback(char *str);
ATStatus MQTTOPEN_Callback(char *str);
ATStatus MQTTSUB_Calback(char *str);
ATStatus MQTTPUB_Callback(char *str);
ATStatus NSOSD_Callback(char *str);
ATStatus NSORF_Callback(char *str);

static const ATCommandConfig ATCommandList[]=
{
	{AT,	"AT"		,500,5,3,	AT_Callback		},
	{CCLK,	"AT+CCLK"	,500,5,3,CCLK_Callback	},
	{MQTTCFG,"AT+MQTTCFG",1000,1,1,MQTTCFG_Callback	},
	{MQTTOPEN,"AT+MQTTOPEN",500,1,1,MQTTOPEN_Callback	},
	{MQTTSUB,"AT+MQTTSUB",500,5,3,MQTTSUB_Calback},
	{MQTTPUB,	"AT+MQTTPUB"	,500,1,1,MQTTPUB_Callback},
	{NSOSD,	"AT+NSOSD"	,500,5,3,NSOSD_Callback},
	{NSORF,	"AT+NSORF"	,500,5,3,NSORF_Callback},

};

#endif
