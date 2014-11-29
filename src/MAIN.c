#include <sh68f83.h>
#include "keyboard.h"

unsigned char usbkeydat[8];
unsigned char temp=0;

void main(void)
{

    readscan();
    temp = usbkeydat[2];
    if(temp)
        usbkeydat[0] = 0xFF;
}
