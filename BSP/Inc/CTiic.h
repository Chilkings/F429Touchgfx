#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "main.h"

/**
���ݴ�����-IIC ��������	   
SCL -----> PH5
SDA -----> PH4
**/

//IO��������
#define CT_SDA_IN()  {GPIOH->MODER&=~(3<<(6*2));GPIOH->MODER|=0<<6*2;}		//PH5����ģʽ
#define CT_SDA_OUT() {GPIOH->MODER&=~(3<<(6*2));GPIOH->MODER|=1<<6*2;} 		//PH5���ģʽ
//IO��������	 
#define	CT_IIC_SCL(state)	{if(state == 0)				HAL_GPIO_WritePin(TFT_I2C_SCL_GPIO_Port, TFT_I2C_SCL_Pin, GPIO_PIN_RESET);				\
												 else if(state == 1)	HAL_GPIO_WritePin(TFT_I2C_SCL_GPIO_Port, TFT_I2C_SCL_Pin, GPIO_PIN_SET);	}
									
#define	CT_IIC_SDA(state)	{if(state == 0)				HAL_GPIO_WritePin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin, GPIO_PIN_SET);	} 
#define CT_READ_SDA   HAL_GPIO_ReadPin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin)  //����һλ


//IIC���в�������
void CT_IIC_Init(void);                				//��ʼ��IIC��IO��				 
void CT_IIC_Start(void);											//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  										//����IICֹͣ�ź�
void CT_IIC_Send_Byte(uint8_t txd);						//IIC����һ���ֽ�
uint8_t CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
uint8_t CT_IIC_Wait_Ack(void); 								//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);												//IIC����ACK�ź�
void CT_IIC_NAck(void);												//IIC������ACK�ź�

#endif







