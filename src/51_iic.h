#ifndef __51_IIC_H
#define __51_IIC_H
#include <sh68F83.h>
#include "main.h"

#define DEV_ADDR               0xA0

void iic_init(void);
void iic_write(u8 reg,u8 *dat,u8 len);
void iic_read(u8 reg,u8 *dat,u8 len);

#endif
