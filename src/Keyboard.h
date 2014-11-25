#ifndef  __KEYBOARD_H
#define  __KEYBOARD_H

#include <sh68F83.h>
#include <intrins.h>

sbit   R0 = P;
sbit   R1 = P;    
sbit   R2 = P;
sbit   R3 = P;
sbit   R4 = P;
sbit   R5 = P;
sbit   R6 = P;
sbit   R7 = P;

sbit   C0 = p;
sbit   C1 = p;
sbit   C2 = p;
sbit   C3 = p;
sbit   C4 = p;
sbit   C5 = p;
sbit   C6 = p;
sbit   C7 = p;
sbit   C8 = p;
sbit   C9 = p;
sbit   C10 = p;
sbit   C11 = p;
sbit   C12 = p;
sbit   C13 = p;
sbit   C14 = p;
sbit   C15 = p;
sbit   C16 = p;

#defind GPIO_ALL_HIGH()    P0=0xFF;P1=0xFF;P2=0xFF
#define GPIO_COL           P2
#define GOPI_ROW1          P1
#define GPIO_ROW2          P3
#define GPIO_ROW3          P0&0x40

#define   KEY_BUF_END         0x06
#define   FnKeyIndex          0x61     
                            
                            
#define   KEY_A               0x04
#define   KEY_B               0x05
#define   KEY_C               0x06
#define   KEY_D               0x07
#define   KEY_E               0x08
#define   KEY_F               0x09
#define   KEY_G               0x0a
#define   KEY_H               0x0b
#define   KEY_I               0x0c
#define   KEY_J               0x0d
#define   KEY_K               0x0e
#define   KEY_L               0x0f
#define   KEY_M               0x10
#define   KEY_N               0x11
#define   KEY_O               0x12
#define   KEY_P               0x13
#define   KEY_Q               0x14
#define   KEY_R               0x15
#define   KEY_S               0x16
#define   KEY_T               0x17
#define   KEY_U               0x18
#define   KEY_V               0x19
#define   KEY_W               0x1a
#define   KEY_X               0x1b
#define   KEY_Y               0x1c
#define   KEY_Z               0x1d
                            
#define   KEY_ESCAPE          0x29       
#define   KEY_Tab             0x2b
#define   KEY_CAPSLOCK        0x39
#define   KEY_Backspace       0x2a
#define   KEY_ENTER           0x28
#define   KEY_SPACEBAR        0x2c
                            
#define   KEY_L_CTRL          0x01//0xA0
#define   KEY_L_SHIFT         0x02//0xA1
#define   KEY_L_ALT           0x04//0xA2
#define   KEY_L_GUI           0x08//0xA3
#define   KEY_R_CTRL          0x10//0xA4
#define   KEY_R_SHIFT         0x20//0xA5
#define   KEY_R_ALT           0x40//0xA6
#define   KEY_R_GUI           0x80//0xA7

#define   KEY_TILDE           0x35   //bo lang
#define   KEY_Underscore      0x2d   //xia hua xian
#define   KEY_EqualSign       0x2e   //deng hao
#define   KEY_L_Brackets      0x2f   //zuo zhong kuo hao
#define   KEY_R_Brackets      0x30   //you zhong kuo hao
#define   KEY_Slash           0x31   //xie gang      //shu xian
#define   KEY_Semicolon       0x33   //fen hao
#define   KEY_Quotation       0x34   //yin hao
#define   KEY_COMMA           0x36   //dou hao
#define   KEY_PERIOD          0x37   //ju hao
#define   KEY_Interrogation   0x38   //dun hao

#define   KEY_1               0x1e
#define   KEY_2               0x1f
#define   KEY_3               0x20
#define   KEY_4               0x21
#define   KEY_5               0x22
#define   KEY_6               0x23
#define   KEY_7               0x24
#define   KEY_8               0x25
#define   KEY_9               0x26
#define   KEY_0               0x27
                              
#define   KEY_F1              0x3a
#define   KEY_F2              0x3b
#define   KEY_F3              0x3c
#define   KEY_F4              0x3d
#define   KEY_F5              0x3e
#define   KEY_F6              0x3f
#define   KEY_F7              0x40
#define   KEY_F8              0x41
#define   KEY_F9              0x42
#define   KEY_F10             0x43
#define   KEY_F11             0x44
#define   KEY_F12             0x45

         
#define   KEY_PrintScreen      0x46
#define   KEY_ScrollLock       0x47
#define   KEY_Pause            0x48
#define   KEY_Insert           0x49
#define   KEY_Home             0x4a
#define   KEY_PageUp           0x4b
#define   KEY_Delete           0x4c
#define   KEY_End              0x4d
#define   KEY_PageDown         0x4e

#define   KEY_RightArrow       0x4f
#define   KEY_LeftArrow        0x50
#define   KEY_DownArrow        0x51
#define   KEY_UpArrow          0x52

#define   KEY_NUMLOCK          0x53
#define   KEY_NUM_DIV          0x54
#define   KEY_NUM_MUL          0x55
#define   KEY_NUM_MINUS        0x56        
#define   KEY_NUM_PLUS         0x57
#define   KEY_NUM_ENTER        0x58
#define   KEY_NUM_DOT          0x63

#define   KEY_NUM_1            0x59
#define   KEY_NUM_2            0x5a
#define   KEY_NUM_3            0x5b
#define   KEY_NUM_4            0x5c            
#define   KEY_NUM_5            0x5d
#define   KEY_NUM_6            0x5e
#define   KEY_NUM_7            0x5f
#define   KEY_NUM_8            0x60
#define   KEY_NUM_9            0x61
#define   KEY_NUM_0            0x62
                             
#define   KEY_CODE29           0x31
#define   KEY_CODE42           0x32
#define   KEY_CODE45           0x64
#define   KEY_APPS             0x65
#define   KEY_CODE107          0x1085
#define   KEY_CODE56           0x1087
#define   KEY_CODE133          0x1088
#define   KEY_CODE14           0x1089
#define   KEY_CODE132          0x108a
#define   KEY_CODE131          0x108b
#define   KEY_CODE151          0x2090   //key_Hangul
#define   KEY_CODE150          0x2091   //Key_Hanja


const unsigned char kyb_code[8][17]={
    {0x00,0x00,0x00,'16','17','5' ,'20','23','10','11','12','13','1 ',0x00,0x00},
    {0x00,0x00,'44','30','18','19','21','7' ,'24','25','26','27','28',0x00,'29'},
    {'59',0x00,0x00,'46','31','33','34','37','38','39','40','41','43',0x00,'129'},
    {0x00,'127',0x00,0x00,'32','48','49','51','52','53','54','55',0x00,0x00,0x00},
    {0x00,0x00,0x00,'36',0x00,0x00,'22','50',0x00,0x00,'79','57','84','62','89'},
    {0x00,0x00,0x00,'58','47',0x00,'115','35',0x00,0x00,'61',0x00,0x00,'60','15'},
    {0x00,0x00,'83','2' ,'3' ,'4' ,'6' ,'8' ,'9','119','121','123','124',0x00,'76'},
    {'64',0x00,0x00,'110','112','113','114','116','117','118','120','122','126',0x00,'75'}
};

void readscan(void);

#endif
