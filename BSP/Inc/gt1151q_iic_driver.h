#ifndef __GT1151q_IIC_DRIVER_H
#define __GT1151q_IIC_DRIVER_H

#include "main.h"
#include "delay.h"
#include <stdio.h>
#include "string.h" 


//IO操作函数	 
#define	GT_RST(state)	{if(state == 0)				HAL_GPIO_WritePin(T_RSTH8_GPIO_Port, T_RSTH8_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(T_RSTH8_GPIO_Port, T_RSTH8_Pin, GPIO_PIN_SET);	} 
													//GT1151复位引脚
#define	GT_INT(state)	{if(state == 0)				HAL_GPIO_WritePin(T_INT_GPIO_Port, T_INT_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(T_INT_GPIO_Port, T_INT_Pin, GPIO_PIN_SET);	} 
													//GT1151中断引脚			
//I2C读写命令	
#define GT_CMD_WR 		0X28     	//写命令
#define GT_CMD_RD 		0X29		  //读命令


//GT1151 部分寄存器定义 
#define GT_CTRL_REG 	0X8040   	//GT1151控制寄存器
#define GT_CFGS_REG 	0X8050   	//GT1151配置起始地址寄存器
#define GT_CHECK_REG 	0X813C   	//GT1151校验和寄存器
#define GT_PID_REG 		0X8140   	//GT1151产品ID寄存器
#define GT_FW_REG 		0X8145   	//GT1151 IC FW寄存器

#define GT_GSTID_REG 	0X814E   	//GT1151当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址 



uint8_t Touch_Poll(int32_t *x,int32_t *y);
uint8_t GT1151_Send_Cfg(uint8_t mode);
uint8_t GT1151_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void GT1151_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len); 
uint8_t GT1151_Init(void);
uint8_t GT1151_Scan(uint8_t mode); 
void checksum(void);


#endif