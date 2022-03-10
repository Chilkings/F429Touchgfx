#include "Hardware.h"
#include "stdarg.h"
#include "stdio.h"
char UartRXBuff[_UART_RXBUFFSIZE];

void UartInit(void)
{
	__HAL_UART_ENABLE_IT(&_ATUART_HANDLE, UART_IT_IDLE);  					//使能串口空闲中断
	HAL_UART_Receive_DMA(&_ATUART_HANDLE, (uint8_t*)UartRXBuff, _UART_RXBUFFSIZE);     	//开启DMA传输
//__HAL_DMA_DISABLE_IT(&_UART_DMA_HANDLE,DMA_IT_TC);				//关闭DMA中断
	
	__LOG("size: %d",sizeof(ATCommandConfig));
	
}

void SendString(char * str)
{
	HAL_UART_Transmit(& _ATUART_HANDLE,(uint8_t *)str,strlen(str),_UART_TIMEOUT);
}

void USER_UART3_IDLECallback(UART_HandleTypeDef *huart)
{
	if(RESET == __HAL_UART_GET_FLAG(& _ATUART_HANDLE, UART_FLAG_IDLE))   
	{	 // 判断是否是空闲中断
		return;			 
	} 

	// 清除空闲中断标志（否则会一直不断进入中断）
	__HAL_UART_CLEAR_IDLEFLAG(& _ATUART_HANDLE); 
	                                                  
		
	//定义信号量，在接收完一帧数据后发布信号量
	BaseType_t xHightPriorityTaskWoken=pdFALSE;
	xSemaphoreGiveFromISR(ATRXCplSemaphore,&xHightPriorityTaskWoken);
    //退出中断后执行最高优先级任务
	portYIELD_FROM_ISR(xHightPriorityTaskWoken);

	
	// 重启开始DMA传输 每次255字节数据
  // HAL_UART_Receive_DMA(&_ATUART_HANDLE, (uint8_t*)UartRXBuff, _UART_RXBUFFSIZE);  

}

void SendMultiStr(int n,...)
{

    char *str;
    va_list v1;
	va_start(v1,n);

	for (size_t i = 0; i < n; i++)
	{
		str=va_arg(v1,char*);
		HAL_UART_Transmit(& _ATUART_HANDLE,(uint8_t *)str,strlen(str),_UART_TIMEOUT);
		HAL_UART_Transmit(& huart1,(uint8_t *)str,strlen(str),_UART_TIMEOUT);
	}
    va_end(v1);
}

void PrintIotRxData(void)
{
	BaseType_t xResult;
	uint32_t RXDataLength=0;
	xResult=xSemaphoreTake(ATRXCplSemaphore,pdMS_TO_TICKS(1000));
	if(xResult != pdPASS)
	{	
		return;
	}
	else 
	{
		printf("接收到数据\r\n");
	}
	RXDataLength=0;
	RXDataLength  = _UART_RXBUFFSIZE - __HAL_DMA_GET_COUNTER(&_UART_DMA_HANDLE); 
	UartRXBuff[RXDataLength]='\0';
	__LOG("Receive Data(length = %d):%s\r\n",RXDataLength,UartRXBuff);
	
	
	__HAL_DMA_DISABLE(&_UART_DMA_HANDLE);

}




void MoudleResst(void)
{
	osDelay(3000);
}

