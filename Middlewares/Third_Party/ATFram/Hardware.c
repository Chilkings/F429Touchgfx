#include "Hardware.h"
#include "stdarg.h"
#include "stdio.h"
char UartRXBuff[_UART_RXBUFFSIZE];

void UartInit(void)
{
	__HAL_UART_ENABLE_IT(&_ATUART_HANDLE, UART_IT_IDLE);  					//ʹ�ܴ��ڿ����ж�
	HAL_UART_Receive_DMA(&_ATUART_HANDLE, (uint8_t*)UartRXBuff, _UART_RXBUFFSIZE);     	//����DMA����
//__HAL_DMA_DISABLE_IT(&_UART_DMA_HANDLE,DMA_IT_TC);				//�ر�DMA�ж�
	
	__LOG("size: %d",sizeof(ATCommandConfig));
	
}

void SendString(char * str)
{
	HAL_UART_Transmit(& _ATUART_HANDLE,(uint8_t *)str,strlen(str),_UART_TIMEOUT);
}

void USER_UART3_IDLECallback(UART_HandleTypeDef *huart)
{
	if(RESET == __HAL_UART_GET_FLAG(& _ATUART_HANDLE, UART_FLAG_IDLE))   
	{	 // �ж��Ƿ��ǿ����ж�
		return;			 
	} 

	// ��������жϱ�־�������һֱ���Ͻ����жϣ�
	__HAL_UART_CLEAR_IDLEFLAG(& _ATUART_HANDLE); 
	                                                  
		
	//�����ź������ڽ�����һ֡���ݺ󷢲��ź���
	BaseType_t xHightPriorityTaskWoken=pdFALSE;
	xSemaphoreGiveFromISR(ATRXCplSemaphore,&xHightPriorityTaskWoken);
    //�˳��жϺ�ִ��������ȼ�����
	portYIELD_FROM_ISR(xHightPriorityTaskWoken);

	
	// ������ʼDMA���� ÿ��255�ֽ�����
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
		printf("���յ�����\r\n");
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

