#include "keyboard.h"

unsigned char code kyb_map[8][17]={
    {0x00,0x00,0x00,KEY_Tab,KEY_Q,KEY_4,KEY_R,KEY_U,KEY_9,KEY_0,KEY_Underscore,KEY_EqualSign,KEY_TILDE,0x00,0x00},
    {0x00,0x00,KEY_L_SHIFT,KEY_CAPSLOCK,KEY_W,KEY_E,KEY_T,KEY_6,KEY_I,KEY_O,KEY_P,KEY_L_Brackets,KEY_R_Brackets,0x00,KEY_Slash},
    {FnKeyIndex,0x00,0x00,KEY_Z,KEY_A,KEY_D,KEY_F,KEY_J,KEY_K,KEY_L,KEY_Semicolon,KEY_Quotation,KEY_ENTER,0x00,KEY_R_CTRL},
    {0x00,KEY_L_CTRL,0x00,0x00,KEY_S,KEY_C,KEY_V,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_Interrogation,0x00,0x00,0x00},
    {0x00,0x00,0x00,KEY_H,0x00,0x00,KEY_Y,KEY_B,0x00,0x00,KEY_LeftArrow,KEY_UpArrow,KEY_DownArrow,KEY_R_ALT,KEY_RightArrow},
    {0x00,0x00,0x00,KEY_R_GUI,KEY_X,0x00,KEY_F4,KEY_G,0x00,0x00,KEY_SPACEBAR,0x00,0x00,KEY_L_ALT,KEY_Backspace},
    {0x00,0x00,KEY_R_SHIFT,KEY_1,KEY_2,KEY_3,KEY_5,KEY_7,KEY_8,KEY_F8,KEY_F10,KEY_F12,'-',0x00,'/'},
    {KEY_Delete,0x00,0x00,KEY_ESCAPE,KEY_F1,KEY_F2,KEY_F3,KEY_F5,KEY_F6,KEY_F7,KEY_F9,KEY_F11,'+',0x00,'*'}
 };

unsigned char Fn_map[12]={};
//static unsigned char keynum_dat[2][8];
static unsigned int  keynum_dat[8];

void delay(unsigned int count)
{
    unsigned char i;
    while(count--)
    {
        for(i=0;i<100;i++);
    };
}


static void scan_out_high(void)
{
    GPIO_ALL_HIGH();
}

static void keyscan(void)
{
    unsigned char i;
    unsigned char cycle_ctr = 0xFE;
    unsigned char keynum[2];
    unsigned char temp[2];
    

    GPIO_COL = cycle_ctr;
    for(i=0;i<8;i++)
    {
        scan_out_high();
        temp[0] = GPIO_ROW1;
        temp[1] = GPIO_ROW2;
        delay(20);
        scan_out_high();
        keynum[0] = GPIO_ROW1;
        keynum[1] = GPIO_ROW2;
        if(keynum[0]!=temp[0] || keynum[1]!=temp[1]) 
        {
            keynum_dat[i] = 0xFF;
            //            keynum_dat[1][i] = 0xFF;
            continue;
        }
        //        keynum_dat[0][i] = keynum[0];
        //        keynum_dat[1][i] = keynum[1];
        keynum_dat[i] = (keynum[0]<<8) | keynum[1];
        
        cycle_ctr = _crol_(cycle_ctr,1);
        GPIO_COL = cycle_ctr;
    }

}

extern unsigned char usbkeydat[8];
void readscan(void)
{

    unsigned char i,k;
    unsigned char usb_c = 0;
    unsigned char press_count = 2;
    unsigned char key_value = 0;
    unsigned int circbit = 0;
    unsigned int keybit = 0;
    unsigned char Fn_st = 0;
    
    for(i=0;i<8;i++)
        {usbkeydat[i] = 0;}

    keyscan();
    
    for(i=0;i<8;i++)
    {
        
        if(keynum_dat[i] == 0xFFFF)  // no key press down
            continue;

        
        circbit = 0x8000;
        for(k=0;k<16;k++)
        {
            keybit = keynum_dat[i] & circbit;
            circbit = _iror_(circbit,1);

            if(keybit != 0 )
                continue;

            key_value = kyb_map[i][k];
                
            switch(key_value)
            {
            case KEY_L_CTRL:  usbkeydat[0] = usbkeydat[0] | KEY_L_CTRL_BIT;
                break;
            case KEY_L_SHIFT: usbkeydat[0] = usbkeydat[0] | KEY_L_SHIFT_BIT;
                break;
            case KEY_L_ALT:   usbkeydat[0] = usbkeydat[0] | KEY_L_ALT_BIT;
                break;
            case KEY_L_GUI:   usbkeydat[0] = usbkeydat[0] | KEY_L_GUI_BIT;
                break;
            case KEY_R_CTRL:  usbkeydat[0] = usbkeydat[0] | KEY_R_CTRL_BIT;
                break;
            case KEY_R_SHIFT: usbkeydat[0] = usbkeydat[0] | KEY_R_SHIFT_BIT;
                break;
            case KEY_R_ALT:   usbkeydat[0] = usbkeydat[0] | KEY_R_ALT_BIT;
                break;
            case KEY_R_GUI:   usbkeydat[0] = usbkeydat[0] | KEY_R_GUI_BIT;
                break;
            default:
                usbkeydat[press_count] = key_value;
                break;
            }

            if(key_value == FnKeyIndex)  Fn_st = 1;
            else    press_count++;

            if(press_count > 7)
            {
                for(k=0;k<8;k++)
                    {usbkeydat[i] = 0;}
                return;
            }

        }
    }
    //if press Fn key down  
    if(Fn_st)
    {
        for(i=2;i<8;i++)
        {
            if(usbkeydat[i] >= 0x3a && usbkeydat[i] <= 0x45)
            {
                usbkeydat[i] = Fn_map[i-2];
            }
        }
    }
        
}



