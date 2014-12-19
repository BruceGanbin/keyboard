#ifndef __51_IIC_H
#define __51_IIC_H
#include <sh68F83.h>
#include <intrins.h>


void iic_send(u8 *data,u8 addr,u8 len);
void iic_read(u8 *data,u8 addr,u8 len);

#endif
