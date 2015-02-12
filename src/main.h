#ifndef __MAIN_H
#define __MAIN_H

typedef unsigned char   u8;
typedef unsigned int    u16;
typedef unsigned long   u32;

typedef unsigned char   uint8;
typedef unsigned int    uint16;
typedef unsigned long   uint32;

#define LED1          P1_3
#define LED2          P3_4
#define LED3          P0_7
#define LED4          P4_0

#define WDT_OPNE()          PRCON|=0x40

void set_idlemode(void);

#endif
