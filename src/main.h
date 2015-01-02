#ifndef __MAIN_H
#define __MAIN_H

typedef unsigned char   u8;
typedef unsigned int    u16;
typedef unsigned long   u32;

typedef unsigned char   uint8;
typedef unsigned int    uint16;
typedef unsigned long   uint32;

#define WDT_OPNE()          PRCON|=0x40

void set_idlemode(void);

#endif
