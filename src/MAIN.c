#include <sh68f83.h>
#include "keyboard.h"
#include "usbcore.h"

unsigned char usbkeydat[8];
unsigned char temp=0;

void system_init(void);

void main(void)
{

    usbinit();
    while(1)
    {
        readscan();
        temp = usbkeydat[2];
        if(temp)
            usbkeydat[0] = 0xFF;
    }
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


void system_init(void)
{

}
