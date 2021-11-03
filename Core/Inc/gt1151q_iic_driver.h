#ifndef __GT1151q_IIC_DRIVER_H
#define __GT1151q_IIC_DRIVER_H

#include "main.h"
#include "delay.h"
#include <stdio.h>
#include "string.h" 


//IO��������	 
#define	GT_RST(state)	{if(state == 0)				HAL_GPIO_WritePin(T_RSTH8_GPIO_Port, T_RSTH8_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(T_RSTH8_GPIO_Port, T_RSTH8_Pin, GPIO_PIN_SET);	} 
													//GT1151��λ����
#define	GT_INT(state)	{if(state == 0)				HAL_GPIO_WritePin(T_INT_GPIO_Port, T_INT_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(T_INT_GPIO_Port, T_INT_Pin, GPIO_PIN_SET);	} 
													//GT1151�ж�����			
//I2C��д����	
#define GT_CMD_WR 		0X28     	//д����
#define GT_CMD_RD 		0X29		  //������


//GT1151 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT1151���ƼĴ���
#define GT_CFGS_REG 	0X8050   	//GT1151������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X813C   	//GT1151У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT1151��ƷID�Ĵ���
#define GT_FW_REG 		0X8145   	//GT1151 IC FW�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT1151��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ 



uint8_t Touch_Poll(int32_t *x,int32_t *y);
uint8_t GT1151_Send_Cfg(uint8_t mode);
uint8_t GT1151_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void GT1151_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len); 
uint8_t GT1151_Init(void);
uint8_t GT1151_Scan(uint8_t mode); 
void checksum(void);


#endif