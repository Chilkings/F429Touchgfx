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
	/**将指令添加到上面**/
	MAXCMDNUM
}ATCommand;

typedef struct
{		
	ATCommand	ATCommandName;
	char * 		ATStr;				//发送的AT指令
	uint16_t  	MaxResponseTime;	//发送后查询返回信息的延时，ms为单位。可设为指令最大响应时间。
	uint8_t   	MaxTryCount; 		//最大重试次数
	uint8_t   	MaxResetCount; 		//最大重启次数
	pFuncCallback		ATRxCpltCallback;	//AT指令接收完成，指令处理回调函数
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
