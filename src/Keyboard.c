
#include "keyboard.h"

//static unsigned char keynum_dat[2][8];
static unsigned int  keynum_dat[8];

static void scan_out_high(void)
{
    PGIO_ALL_HIGH();
}

static void keyscan(void)
{
    unsigned char i,j;
    unsigned char cycle_ctr=OxFE;
    unsigned int ret;
    unsigned char keynum[2];
    unsigned char temp[2];
    
    scan_out_high();
    GPIO_COL = cycle_ctr;
    for(i=0;i<8;i++)
    {
        temp[0] = GPIO_ROW1;
        temp[1] = GPIO_ROW2;
        delay(20);
        keynum[0] = GPIO_ROW1;
        keynum[1] = GPIO_ROW2;
        if(keynum[0]!=temp[0] || keynum[1]!=temp[1]) 
        {
            keynum_dat[0][i] = 0xFF;
            keynum_dat[1][i] = 0xFF;
            continue;
        }
        //        keynum_dat[0][i] = keynum[0];
        //        keynum_dat[1][i] = keynum[1];
        keynum_dat[i] = (keynum[0]<<8) & keynum[1];
        
        cycle_ctr = _crol_(cycle_ctr,1);
        GPIO_COL = cycle_ctr;
    }

}

extern usbkeydat[8];
void readscan(void);
{

    unsigned char i,j,k;
    unsigned char usb_c = 0;
    unsigned char press_count = 2;
    unsigned char key_value = 0;
    unsigned char circbit = 0;
    unsigned char keybit = 0;
    
    for(i=0;i<8;i++)
        usbkeydat[i] = 0;
    
    keyscan();
    
    for(i=0;i<8;i++)
    {
        
        if(keynum[i] == 0xFFFF)  // no key press down
            continue;

        
        circbit = 0x80;
        for(k=0;k<16;k++)
        {
            keybit = keynum[i] & circbit;
            circbit = _cror_(circbit,1);

            if(keybit != 0 )
                continue;

            key_value = kyb_code[i][j];
                
            switch(key_value)
            {
            case PRESS_L_CTRL:  usbkeydat[0] = usbkeydat[0] | KEY_L_CTRL;
                break;
            case PRESS_L_SHIFT: usbkeydat[0] = usbkeydat[0] | KEY_L_SHIFT;
                break;
            case PRESS_L_ALT:   usbkeydat[0] = usbkeydat[0] | KEY_L_ALT;
                break;
            case PRESS_L_GUI:   usbkeydat[0] = usbkeydat[0] | KEY_L_GUI ;
                break;
            case PRESS_R_CTRL:  usbkeydat[0] = usbkeydat[0] | KEY_R_CTRL;
                break;
            case PRESS_R_SHIFT: usbkeydat[0] = usbkeydat[0] | KEY_R_SHIFT;
                break;
            case PRESS_R_ALT:   usbkeydat[0] = usbkeydat[0] | KEY_R_ALT;
                break;
            case PRESS_R_GUI:   usbkeydat[0] = usbkeydat[0] | KEY_R_GUI ;
                break;
            default:
                usbkeydat[press_count] = key_value;
                break;
            }

            if(key_value == FnKeyIndex)
            {
                
                usbkeydat[press_count] = Fnkey_list[];
            }
            
            press_count++;
            if(press_count > 7)
            {
                for(k=0;k<8;k++)
                    usbkeydat[i] = 0;
                return;
            }

        }
    }
}

