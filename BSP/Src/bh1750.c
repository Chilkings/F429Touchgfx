#include "bh1750.h"
#include "softI2c.h"
#include "main.h"

SFIIC_HandleTypeDef BH1750_I2C_HANDLE;

static void bh1750_i2c_init(void)
{
	BH1750_I2C_HANDLE.SDAPort = IIC_SDA_GPIO_Port;
	BH1750_I2C_HANDLE.SDAPin = IIC_SDA_Pin;
	BH1750_I2C_HANDLE.SCLPort = IIC_SCL_GPIO_Port;
	BH1750_I2C_HANDLE.SCLPin = IIC_SCL_Pin;

	BH1750_I2C_HANDLE.Init = softI2cInit; 
	
	BH1750_I2C_HANDLE.Init(&BH1750_I2C_HANDLE);
}

static int bh1750_send_cmd(uint8_t cmd)
{
    return BH1750_I2C_HANDLE.Master_Transmit(&BH1750_I2C_HANDLE, BH1750_ADDR_WRITE, &cmd, 1, 0xFFFF);
}

static int bh1750_read_dat(uint8_t* dat)
{
    return BH1750_I2C_HANDLE.Master_Receive(&BH1750_I2C_HANDLE, BH1750_ADDR_READ, dat, 2, 0xFFFF);
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

int bh1750_init(void)
{
    bh1750_i2c_init();
    return 0;
}

void bh1750_start()
{
		bh1750_i2c_init();
		bh1750_send_cmd(POWER_ON_CMD);	//发送启动命令
	  bh1750_send_cmd(RESET_REGISTER);	//清除寄存器内容
	  bh1750_send_cmd(CONT_H_MODE); //设置高精度为模式2
}


int bh1750_read_lux(uint16_t *lux)
{
    uint8_t dat[2] = {0};
    
    if (bh1750_read_dat(dat) != 0) {
        return -1;
    }
    
    *lux = bh1750_dat2lux(dat);
    
    return 0;
}

