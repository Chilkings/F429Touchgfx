#ifndef _24c02_H_
#define _24c02_H_

#include "main.h"

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	  8191
#define AT24C128	16383
#define AT24C256	32767  

//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C02

#define	AIIC_SCL(state)	{if(state == 0)				HAL_GPIO_WritePin(AIIC_SCL_GPIO_Port, AIIC_SCL_Pin, GPIO_PIN_RESET);				\
												 else if(state == 1)	HAL_GPIO_WritePin(AIIC_SCL_GPIO_Port, AIIC_SCL_Pin, GPIO_PIN_SET);	}
									
#define	AIIC_SDA(state)	{if(state == 0)				HAL_GPIO_WritePin(AIIC_SDA_GPIO_Port, AIIC_SDA_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(AIIC_SDA_GPIO_Port, AIIC_SDA_Pin, GPIO_PIN_SET);	}												
//IO方向设置
#define ASDA_IN()  {GPIOB->MODER&=~(3<<(15*2));GPIOB->MODER|=0<<15*2;}		//PB15输入模式
#define ASDA_OUT() {GPIOB->MODER&=~(3<<(15*2));GPIOB->MODER|=1<<15*2;} 		//PB15输出模式

#define AREAD_SDA   HAL_GPIO_ReadPin(AIIC_SDA_GPIO_Port, AIIC_SDA_Pin)  //输入SDA 

void AIIC_Init(void);
void AIIC_Start(void);
void AIIC_Stop(void);
uint8_t AIIC_Wait_Ack(void);
void AIIC_Ack(void);
void AIIC_NAck(void);
void AIIC_Send_Byte(uint8_t txd);
uint8_t AIIC_Read_Byte(unsigned char ack);

		  
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//指定地址读取一个字节
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//指定地址写入一个字节
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//指定地址开始写入指定长度的数据
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//指定地址开始读取指定长度数据
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//从指定地址开始写入指定长度的数据
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//从指定地址开始读出指定长度的数据

uint8_t AT24CXX_Check(void);  //检查器件
void AT24CXX_Init(void); //初始化IIC


#endif

