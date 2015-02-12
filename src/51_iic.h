#ifndef __51_IIC_H
#define __51_IIC_H
#include <sh68F83.h>
#include "main.h"

#define GSL_TS_ADDR 				0x40
#define DEV_ADDR                    GSL_TS_ADDR

void iic_init(void);
void iic_write(u8 reg,u8 *dat,u8 len);
void iic_read(u8 reg,u8 *dat,u8 len);

#endif
