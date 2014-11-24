
#include "keyboard.h"

static unsigned char keynum_dat[3][8];

static void scan_out_high(void)
{
    PGIO_ALL_HIGH();
}

static void keyscan(void)
{
    unsigned char i,j;
    unsigned char cycle_ctr=OxFE;
    unsigned int ret;
    unsigned char keynum[3];
    unsigned char temp[3];
    
    scan_out_high();
    GPIO_COL = cycle_ctr;
    for(i=0;i<8;i++)
    {
        temp[0] = GPIO_ROW1;
        temp[1] = GPIO_ROW2;
        temp[2] = GPIO_ROW3;
        delay(20);
        keynum[0] = GPIO_ROW1;
        keynum[1] = GPIO_ROW2;
        keynum[3] = GPIO_ROW3;
        if(keynum[0]!=temp[0] || keynum[1]!=temp[1] || keynum[2]!=temp[2]) 
        {
            keynum_dat[0][i] = 0xFF;
            keynum_dat[1][i] = 0xFF;
            keynum_dat[2][i] = 0xFF;
            continue;
        }
        keynum_dat[0][i] = keynum[0];
        keynum_dat[1][i] = keynum[1];
        keynum_dat[3][i] = keynum[2];
        
        cycle_ctr = _crol_(cycle_ctr,1);
        GPIO_COL = cycle_ctr;
    }

}

extern usbkeydat[8];
void readscan(void);
{

    unsigned char i,j,k;
    unsigned char press_key = 2;
    unsigned char key_value = 0;
    for(i=0;i<8;i++)
        usbkeydat[i] = 0;
    
    keyscan();
    
    for(i=0;i<3;i++)
    {
        for(j=0;j<8;j++)
        {
            if(keynum[i][j] == 0xFF)  // no key press down
                continue;

            for(k=0;k<8;k++)
            {
                
            }
            
            switch(keynum[i][j])
            {
            case PRESS_L_CTRL: usbkeydat[0] = usbkeydat[0] | KEY_L_CTRL;
                break;
            case PRESS_L_SHIFT: usbkeydat[0] = usbkeydat[0] | KEY_L_SHIFT;
                break;
            case PRESS_L_ALT: usbkeydat[0] = usbkeydat[0] | KEY_L_ALT;
                break;
            case PRESS_L_GUI:usbkeydat[0] = usbkeydat[0] | KEY_L_GUI ;
                break;
            case PRESS_R_CTRL: usbkeydat[0] = usbkeydat[0] | KEY_R_CTRL;
                break;
            case PRESS_R_SHIFT: usbkeydat[0] = usbkeydat[0] | KEY_R_SHIFT;
                break;
            case PRESS_R_ALT: usbkeydat[0] = usbkeydat[0] | KEY_R_ALT;
                break;
            case PRESS_R_GUI:usbkeydat[0] = usbkeydat[0] | KEY_R_GUI ;
                break;
            default:
                usbkeydat[press_key] = key_value;
                break;
            }
            
            press_key++;
            if(press_key > 7)
            {
                for(k=0;k<8;k++)
                    usbkeydat[i] = 0;
                return;
            }
        }
    }
}

