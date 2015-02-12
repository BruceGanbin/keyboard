#include <sh68f83.h>
#include "keyboard.h"
#include "usbcore.h"
#include "main.h"

unsigned char usbkeydat[8];
unsigned char temp=0;



void system_init(void);
void delay(u16 Count);

void main(void)
{
    //    system_init();
    //    usbinit();
    while(1)
    {
//        readscan();
//        temp = usbkeydat[2];
//        if(temp)
//            usbkeydat[0] = 0xFF;
        LED1 = 1;
        LED2 = 1;
        LED3 = 1;
        LED4 = 1;
        delay(50);
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        LED4 = 0;
        delay(50);
    }
}

void delay(u16 Count)
{
    int i;
    for(i=0;i<1000;i++)
        while(Count--);
}

void IN0_interrupt(void) interrupt 10 // or 11
{
    u8 reg = 0;
    UsbEp0In();
    reg = IF2 & (~IF_IN0);
    IF2 = reg;
}

void OUT0_interrupt(void) interrupt 11 // or 12
{
    u8 reg = 0;
    UsbEp0Out();
    reg = IF2 & (~IF_OUT0);
    IF2 = reg;
}

void SIE_interrupt(void) interrupt 12  // or 13 ?
{
    u8 reg = 0;
    UsbHandler();
    reg = IF2 & (~IF_SIE);
    IF2 = reg;
}

void SETUP_interrupt(void) interrupt 8 // or 9
{
    u8 reg = 0;
    UsbSetup();
    reg = IF2 & (~IF_STUP);
    IF2 = reg;
}

void clear_wdt(void)
{
    CLRWDT = 0x55;
}

void power_init(void)
{
    SUSLO = 0x00;
    PCON = 0x00;  
}

void set_idlemode(void)
{
    SUSLO = 0x55;
    PCON = 0x02;
}

void system_init(void)
{
//    u8 i,j;

    power_init();
    usbreset();
    
    // PREWDT = 0x03;  //set watch dot timer
}
