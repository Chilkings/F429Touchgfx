#ifndef _MYBm280_Bh1750_H
#define	_MYBm280_Bh1750_H

#include "delay.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// #include "sys.h"


//注释：调试的时候使用画板的24c02的iIC接口 PA1(SCL)、PC1(SDA)
#define	BIIC_SCL(state)	{if(state == 0)				HAL_GPIO_WritePin(IIC_SCL_GPIO_Port, IIC_SCL_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(IIC_SCL_GPIO_Port, IIC_SCL_Pin, GPIO_PIN_SET);	}
									
#define	BIIC_SDA(state)	{if(state == 0)				HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_PIN_RESET);\
												 else if(state == 1)	HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_PIN_SET);	}												
//IO方向设置
#define BSDA_IN()  {GPIOI->MODER&=~(3<<(8*2));GPIOI->MODER|=0<<8*2;}		//PC1输入模式
#define BSDA_OUT() {GPIOI->MODER&=~(3<<(8*2));GPIOI->MODER|=1<<8*2;} 		//PC1输出模式

#define BREAD_SDA   HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port, IIC_SDA_Pin)  //输入SDA 

/*************************************************************/
 
#define BHAddWrite     0x46      //从机地址+最后写方向位
#define BHAddRead      0x47      //从机地址+最后读方向位
#define BHPowDown      0x00      //关闭模块
#define BHPowOn        0x01      //打开模块等待测量指令
#define BHReset        0x07      //重置数据寄存器值在PowerOn模式下有效
#define BHModeH1       0x10      //高分辨率 单位1lx 测量时间120ms
#define BHModeH2       0x11      //高分辨率模式2 单位0.5lx 测量时间120ms
#define BHModeL        0x13      //低分辨率 单位4lx 测量时间16ms
#define BHSigModeH     0x20      //一次高分辨率 测量 测量后模块转到 PowerDown模式
#define BHSigModeH2    0x21      //同上类似
#define BHSigModeL     0x23      // 上类似
/*************************************************************/

#define BMP280_SlaveAddr 		0x76    	//BMP280的器件地址
#define BMP280_ADDRESS 			0xEC  
#define BMP280_RESET_VALUE 	0xB6  

#define BMP280_DIG_T1_LSB_REG                0x88  
#define BMP280_DIG_T1_MSB_REG                0x89  
#define BMP280_DIG_T2_LSB_REG                0x8A  
#define BMP280_DIG_T2_MSB_REG                0x8B  
#define BMP280_DIG_T3_LSB_REG                0x8C  
#define BMP280_DIG_T3_MSB_REG                0x8D  
#define BMP280_DIG_P1_LSB_REG                0x8E  
#define BMP280_DIG_P1_MSB_REG                0x8F  
#define BMP280_DIG_P2_LSB_REG                0x90  
#define BMP280_DIG_P2_MSB_REG                0x91  
#define BMP280_DIG_P3_LSB_REG                0x92  
#define BMP280_DIG_P3_MSB_REG                0x93  
#define BMP280_DIG_P4_LSB_REG                0x94  
#define BMP280_DIG_P4_MSB_REG                0x95  
#define BMP280_DIG_P5_LSB_REG                0x96  
#define BMP280_DIG_P5_MSB_REG                0x97  
#define BMP280_DIG_P6_LSB_REG                0x98  
#define BMP280_DIG_P6_MSB_REG                0x99  
#define BMP280_DIG_P7_LSB_REG                0x9A  
#define BMP280_DIG_P7_MSB_REG                0x9B  
#define BMP280_DIG_P8_LSB_REG                0x9C  
#define BMP280_DIG_P8_MSB_REG                0x9D  
#define BMP280_DIG_P9_LSB_REG                0x9E  
#define BMP280_DIG_P9_MSB_REG                0x9F  
  
#define BMP280_CHIPID_REG                    0xD0  /*Chip ID Register */  
#define BMP280_RESET_REG                     0xE0  /*Softreset Register */  
#define BMP280_STATUS_REG                    0xF3  /*Status Register */  
#define BMP280_CTRLMEAS_REG                  0xF4  /*Ctrl Measure Register */  
#define BMP280_CONFIG_REG                    0xF5  /*Configuration Register */  
#define BMP280_PRESSURE_MSB_REG              0xF7  /*Pressure MSB Register */  
#define BMP280_PRESSURE_LSB_REG              0xF8  /*Pressure LSB Register */  
#define BMP280_PRESSURE_XLSB_REG             0xF9  /*Pressure XLSB Register */  
#define BMP280_TEMPERATURE_MSB_REG           0xFA  /*Temperature MSB Reg */  
#define BMP280_TEMPERATURE_LSB_REG           0xFB  /*Temperature LSB Reg */  
#define BMP280_TEMPERATURE_XLSB_REG          0xFC  /*Temperature XLSB Reg */  
  
/* 在foreced mode下，1s的采样周期，温度和气压使用最低的精度采集并且使用最小的滤波器系数, 
 * 数据的采集时间大概在6ms，平均功率为3.27uA。 
 * */  
  
/* 在foreced mode下，1s的采样周期, 温度和气压使用最高的精度采集并且使用最大的滤波器系数， 
 * 数据的采集时间大概在70ms，平均功率为30uA。 
 * */  
  
typedef enum {  
    BMP280_T_MODE_SKIP = 0x0,   /*skipped*/  
    BMP280_T_MODE_1,            /*x1*/  
    BMP280_T_MODE_2,            /*x2*/  
    BMP280_T_MODE_3,            /*x4*/  
    BMP280_T_MODE_4,            /*x8*/  
    BMP280_T_MODE_5             /*x16*/  
} BMP280_T_OVERSAMPLING;  //过采样
  
typedef enum {  
    BMP280_SLEEP_MODE = 	0x00,  
    BMP280_FORCED_MODE = 	0x01,  
    BMP280_NORMAL_MODE=		0x03  
} BMP280_WORK_MODE;  
  
typedef enum {  
    BMP280_P_MODE_SKIP = 0x0,   	/*skipped*/  
    BMP280_P_MODE_x1,            	/*x1*/  
    BMP280_P_MODE_x2,            	/*x2*/  
    BMP280_P_MODE_x4,            	/*x4*/  
    BMP280_P_MODE_x8,            	/*x8*/  
    BMP280_P_MODE_x16             /*x16*/  
} BMP280_P_OVERSAMPLING;  
/************************************************/
/**@name	          工作模式定义                 */
/************************************************/
typedef enum
{
	BMP280_ULTRA_LOW_POWER_MODE = 0x00,
	BMP280_LOW_POWER_MODE = 0x01,
	BMP280_STANDARD_RESOLUTION_MODE = 0x02,
	BMP280_HIGH_RESOLUTION_MODE = 0x03,
	BMP280_ULTRA_HIGH_RESOLUTION_MODE = 0x04
}WORKING_MODE;

typedef enum {  
    BMP280_FILTER_OFF = 0x0,    /*filter off*/  
    BMP280_FILTER_MODE_1,       /*0.223*ODR*/  
    BMP280_FILTER_MODE_2,       /*0.092*ODR*/  
    BMP280_FILTER_MODE_3,       /*0.042*ODR*/  
    BMP280_FILTER_MODE_4        /*0.021*ODR*/  
} BMP280_FILTER_COEFFICIENT;  
  
typedef enum {  
    BMP280_T_SB_0_5MS = 0x00,      /*0.5ms */  
    BMP280_T_SB_62_5MS= 0x01,      /*62.5ms*/  
    BMP280_T_SB_125MS = 0x02,      /*125ms */  
    BMP280_T_SB_250MS = 0x03,      /*250ms */  
    BMP280_T_SB_500MS = 0x04,      /*500ms */  
    BMP280_T_SB_1000MS= 0x05,      /*1000ms*/  
    BMP280_T_SB_2000MS= 0x06,      /*2000ms*/  
    BMP280_T_SB_4000MS= 0x07,      /*4000ms*/  
} BMP280_T_SB;  

typedef struct{
	uint16_t dig_T1;/*校准T1数据*/
	int16_t dig_T2;/*校准T2数据*/
	int16_t dig_T3;/*校准T3数据*/
	uint16_t dig_P1;/*校准P1数据*/
	int16_t dig_P2;/*校准P2数据*/
	int16_t dig_P3;/*校准P3数据*/
	int16_t dig_P4;/*校准P4数据*/
	int16_t dig_P5;/*校准P5数据*/
	int16_t dig_P6;/*校准P6数据*/
	int16_t dig_P7;/*校准P7数据*/
	int16_t dig_P8;/*校准P8数据*/
	int16_t dig_P9;/*校准P9数据*/
	int32_t t_fine;/*校准t_fine数据*/
}bmp280_calib_param_t;

typedef struct  {
	bmp280_calib_param_t calib_param;/*校准数据*/
	uint8_t chip_id;                      /*传感器ID*/
	uint8_t dev_addr;                     /*传感器IIC地址*/
	uint8_t oversamp_temperature;         /*温度采样*/
	uint8_t oversamp_pressure;            /*气压采样*/
}bmp280_t;


void BIIC_Init(void);
void BIIC_Start(void);
void BIIC_Stop(void);
uint8_t BIIC_Wait_Ack(void);
void BIIC_Ack(void);
void BIIC_NAck(void);
uint8_t Bh1750_IIC_Read_Byte(void);
//static void BMP280_Write_Byte(uint8_t reg,uint8_t data);
uint8_t BIIC_Read_Byte(unsigned char ack);
uint8_t IIC_Read_Byte_nask(unsigned char ack);
void BIIC_Send_Byte(uint8_t txd);
/*函数*/
extern uint8_t  BMP280_Init(void);
extern uint8_t  BMP280_GetMode(void);
extern uint8_t  BMP280_SetMode(BMP280_WORK_MODE mode);
extern uint8_t  BMP280_SetPowerMode(uint8_t mode);
extern uint8_t  BMP280_SetWorkMode(WORKING_MODE mode);
extern uint8_t  BMP280_SetStandbyDurn(BMP280_T_SB v_standby_durn_uint8_t);
extern uint8_t  BMP280_GetStandbyDurn(uint8_t* v_standby_durn_uint8_t);
extern uint8_t  BMP280_ReadUncompTemperature(int32_t* un_temp);
extern uint8_t  BMP280_ReadUncompPressuree(int32_t *un_press);
extern uint8_t  BMP280_ReadUncompPressureTemperature(int32_t *un_press, int32_t *un_temp);
extern int32_t BMP280_CompensateTemperatureInt32(int32_t un_temp);
extern uint32_t BMP280_CompensatePressureInt32(int32_t un_press);
extern uint8_t  BMP280_ReadPressureTemperature(uint32_t *press, int32_t *temp);
uint8_t BMP280_Read_Byte(uint8_t reg);
uint8_t BMP280_Write_Byte(uint8_t reg,uint8_t data);
uint8_t BMP280_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf);
uint8_t BMP280_ReadID(void);
void BMP280_Test(void);
uint8_t Bh1750_IIC_Read_Byte(void);
void Multiple_read_BH1750(void);
void Test_Bh1750(void);
uint8_t BH1750_Write(uint8_t I_SlaveAddress, uint8_t REG_Address);

void Bh1750_data_send(uint8_t command);
uint16_t Bh1750_data_read(void);
void Bh1750_Init(void);
void Bh1750_Test(void);

void PCF8591_Write_Command(unsigned char Addr,unsigned char Command);
unsigned char ADC_PCF8591(void);
void PCF8591_Init(void);
void PCF8591_Test(void);


uint8_t BMP280_Bh1750_Init(void);

#endif





