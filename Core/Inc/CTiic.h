#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "main.h"

/**
电容触摸屏-IIC 驱动代码	   
SCL -----> PH5
SDA -----> PH4
**/

//IO方向设置
#define CT_SDA_IN()  {GPIOH->MODER&=~(3<<(6*2));GPIOH->MODER|=0<<6*2;}		//PH5输入模式
#define CT_SDA_OUT() {GPIOH->MODER&=~(3<<(6*2));GPIOH->MODER|=1<<6*2;} 		//PH5输出模式
//IO操作函数	 
#define	CT_IIC_SCL(state)	{if(state == 0)				HAL_GPIO_WritePin(TFT_I2C_SCL_GPIO_Port, TFT_I2C_SCL_Pin, GPIO_PIN_RESET);				\
												 else if(state == 1)	HAL_GPIO_WritePin(TFT_I2C_SCL_GPIO_Port, TFT_I2C_SCL_Pin, GPIO_PIN_SET);	}
									
#define	CT_IIC_SDA(state)	{if(state == 0)				HAL_GPIO_WritePin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin, GPIO_PIN_SET);	} 
#define CT_READ_SDA   HAL_GPIO_ReadPin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin)  //读入一位


//IIC所有操作函数
void CT_IIC_Init(void);                				//初始化IIC的IO口				 
void CT_IIC_Start(void);											//发送IIC开始信号
void CT_IIC_Stop(void);	  										//发送IIC停止信号
void CT_IIC_Send_Byte(uint8_t txd);						//IIC发送一个字节
uint8_t CT_IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
uint8_t CT_IIC_Wait_Ack(void); 								//IIC等待ACK信号
void CT_IIC_Ack(void);												//IIC发送ACK信号
void CT_IIC_NAck(void);												//IIC不发送ACK信号

#endif







