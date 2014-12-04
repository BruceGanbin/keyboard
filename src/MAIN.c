#include <sh68f83.h>
#include "keyboard.h"
#include "HID.h"

unsigned char usbkeydat[8];
unsigned char temp=0;

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


void SIE_interrupt(void) interrupt 12  // or 13 ?
{
    UsbHandler();
}
