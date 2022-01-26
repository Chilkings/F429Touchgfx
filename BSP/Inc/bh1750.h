#ifndef	_BH1750_I2C_DRV_H_
#define	_BH1750_I2C_DRV_H_

#include "stm32f4xx_hal.h"

// address(7 bit) + read or write(1 bit)
#define	BH1750_ADDR_WRITE	0x46
#define	BH1750_ADDR_READ	0x47


typedef enum
{
    POWER_OFF_CMD	=	0x00,	// Power off
    POWER_ON_CMD	=	0x01,	// Power on
    RESET_REGISTER	=	0x07,	// Reset digital register
    CONT_H_MODE		=	0x10,	// Continuous high resolution mode, measurement time 120ms
    CONT_H_MODE2	=	0x11,	// Continuous high resolution mode2, measurement time 120ms
    CONT_L_MODE		=	0x13,	// Continuous low resolution mode, measurement time 16ms
    ONCE_H_MODE		=	0x20,	// Once high resolution mode, measurement time 120ms
    ONCE_H_MODE2	=	0x21,	// Once high resolution mode2, measurement time 120ms
    ONCE_L_MODE		=	0x23	// Once low resolution mode2, measurement time 120ms
} bh1750_mode_t;

int bh1750_init(void);
void bh1750_start(void);
int bh1750_read_lux(uint16_t *lux);

#endif