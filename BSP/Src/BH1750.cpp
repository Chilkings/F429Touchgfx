#include "BH1750.hpp"
#include "main.h"
#include "stdio.h"

I2C SensorI2C(IIC_SDA_GPIO_Port,IIC_SDA_Pin,IIC_SCL_GPIO_Port,IIC_SCL_Pin);

//static void bh1750_i2c_init(void)
//{
//}

static int bh1750_send_cmd(uint8_t cmd)
{
    return SensorI2C.I2C_Write_Noreg(BH1750_ADDR, &cmd, 1, 500);
}

static int bh1750_read_dat(uint8_t* dat)
{
    return SensorI2C.I2C_Read_Noreg(BH1750_ADDR, dat, 2, 500);
}



static uint16_t bh1750_dat2lux(uint8_t* dat)
{
    uint16_t lux = 0;
    
    lux = dat[0];
    lux <<= 8;
    lux += dat[1];
    lux = (int)(lux / 1.2);
	
    return lux;
}

//int bh1750_init(void)
//{
//    bh1750_i2c_init();
//    return 0;
//}

int bh1750_start()
{
		bh1750_send_cmd(POWER_ON_CMD);
		bh1750_send_cmd(RESET_REGISTER);
		return bh1750_send_cmd(CONT_H_MODE2);
}

int bh1750_read_lux(uint16_t *lux)
{
    uint8_t dat[2] = {0};
    bh1750_read_dat(dat);
    if (bh1750_read_dat(dat) != true) {
        return -1;  //读取失败，返回-1
    }

    *lux = bh1750_dat2lux(dat);
    
    return 1;  //读取成功，返回1
} 

