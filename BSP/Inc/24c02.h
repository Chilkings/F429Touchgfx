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

//Mini STM32������ʹ�õ���24c02�����Զ���EE_TYPEΪAT24C02
#define EE_TYPE AT24C02

#define	AIIC_SCL(state)	{if(state == 0)				HAL_GPIO_WritePin(AIIC_SCL_GPIO_Port, AIIC_SCL_Pin, GPIO_PIN_RESET);				\
												 else if(state == 1)	HAL_GPIO_WritePin(AIIC_SCL_GPIO_Port, AIIC_SCL_Pin, GPIO_PIN_SET);	}
									
#define	AIIC_SDA(state)	{if(state == 0)				HAL_GPIO_WritePin(AIIC_SDA_GPIO_Port, AIIC_SDA_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(AIIC_SDA_GPIO_Port, AIIC_SDA_Pin, GPIO_PIN_SET);	}												
//IO��������
#define ASDA_IN()  {GPIOB->MODER&=~(3<<(15*2));GPIOB->MODER|=0<<15*2;}		//PB15����ģʽ
#define ASDA_OUT() {GPIOB->MODER&=~(3<<(15*2));GPIOB->MODER|=1<<15*2;} 		//PB15���ģʽ

#define AREAD_SDA   HAL_GPIO_ReadPin(AIIC_SDA_GPIO_Port, AIIC_SDA_Pin)  //����SDA 

void AIIC_Init(void);
void AIIC_Start(void);
void AIIC_Stop(void);
uint8_t AIIC_Wait_Ack(void);
void AIIC_Ack(void);
void AIIC_NAck(void);
void AIIC_Send_Byte(uint8_t txd);
uint8_t AIIC_Read_Byte(unsigned char ack);

		  
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//ָ����ַд��һ���ֽ�
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

uint8_t AT24CXX_Check(void);  //�������
void AT24CXX_Init(void); //��ʼ��IIC


#endif

