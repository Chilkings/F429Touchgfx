#ifndef __HARDWARE_H_
#define __HARDWARE_H_

#include "FreeRTOS.h"
#include "string.h"
#include "AT.h"

#include "usart.h"


#define _UART_DMA_HANDLE hdma_usart3_rx
#define _ATUART_HANDLE huart3

#define _UART_TIMEOUT 1000
#define _UART_RXBUFFSIZE 512


extern DMA_HandleTypeDef _UART_DMA_HANDLE;
extern char UartRXBuff[_UART_RXBUFFSIZE];

#define IOT_printf(...) HAL_UART_Transmit(&_ATUART_HANDLE,(uint8_t *)UartRXBuff,sprintf((char*)UartRXBuff,__VA_ARGS__),_UART_TIMEOUT)


void UartInit(void);
void SendString(char * str);
void SendMultiStr(int n,...);
void MoudleResst(void);
void USER_UART3_IDLECallback(UART_HandleTypeDef *huart);
void PrintIotRxData(void);
#endif
