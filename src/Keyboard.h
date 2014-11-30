#ifndef  __KEY_BOARD_H
#define  __KEY_BOARD_H

#include <sh68F83.h>
#include <intrins.h>

// sbit   R0 = P;
// sbit   R1 = P;    
// sbit   R2 = P;
// sbit   R3 = P;
// sbit   R4 = P;
// sbit   R5 = P;
// sbit   R6 = P;
// sbit   R7 = P;
//  
// sbit   C0 = p;
// sbit   C1 = p;
// sbit   C2 = p;
// sbit   C3 = p;
// sbit   C4 = p;
// sbit   C5 = p;
// sbit   C6 = p;
// sbit   C7 = p;
// sbit   C8 = p;
// sbit   C9 = p;
// sbit   C10 = p;
// sbit   C11 = p;
// sbit   C12 = p;
// sbit   C13 = p;
// sbit   C14 = p;
// sbit   C15 = p;
// sbit   C16 = p;

#define GPIO_ALL_HIGH()    P0=0xFF;P1=0xFF;P2=0xFF
#define GPIO_COL           P2
#define GPIO_ROW1          P1
#define GPIO_ROW2          P3


// keyboard scan code specificationsp
#define   KEY_BUF_END          0x06 
#define   FnKeyIndex           0xB0    
                               
#define   KEY_A                0x04
#define   KEY_B                0x05
#define   KEY_C                0x06
#define   KEY_D                0x07
#define   KEY_E                0x08
#define   KEY_F                0x09
#define   KEY_G                0x0a
#define   KEY_H                0x0b
#define   KEY_I                0x0c
#define   KEY_J                0x0d
#define   KEY_K                0x0e
#define   KEY_L                0x0f
#define   KEY_M                0x10
#define   KEY_N                0x11
#define   KEY_O                0x12
#define   KEY_P                0x13
#define   KEY_Q                0x14
#define   KEY_R                0x15
#define   KEY_S                0x16
#define   KEY_T                0x17
#define   KEY_U                0x18
#define   KEY_V                0x19
#define   KEY_W                0x1a
#define   KEY_X                0x1b
#define   KEY_Y                0x1c
#define   KEY_Z                0x1d
                               
#define   KEY_1                0x1e
#define   KEY_2                0x1f
#define   KEY_3                0x20
#define   KEY_4                0x21
#define   KEY_5                0x22
#define   KEY_6                0x23
#define   KEY_7                0x24
#define   KEY_8                0x25
#define   KEY_9                0x26
#define   KEY_0                0x27
                               
#define   KEY_ENTER            0x28
#define   KEY_ESCAPE           0x29
#define   KEY_Backspace        0x2a
#define   KEY_Tab              0x2b
#define   KEY_SPACEBAR         0x2c
                               
#define   KEY_Underscore       0x2d   //'_' xia hua xiann
#define   KEY_EqualSign        0x2e   //'=' deng hao
#define   KEY_L_Brackets       0x2f   //'[' zuo zhong kuo hao
#define   KEY_R_Brackets       0x30   //']' you zhong kuo hao
#define   KEY_Slash            0x31   //'\' xie gang
#define   KEY_Semicolon        0x33   //';' fen hao
#define   KEY_Quotation        0x34   //'"' yin hao
#define   KEY_TILDE            0x35   //'~' bo lang
#define   KEY_COMMA            0x36   //',' dou hao
#define   KEY_PERIOD           0x37   //'.' ju hao
#define   KEY_Interrogation    0x38   //'/' dun hao
                               
#define   KEY_CAPSLOCK         0x39   
                               
#define   KEY_F1               0x3a
#define   KEY_F2               0x3b
#define   KEY_F3               0x3c
#define   KEY_F4               0x3d
#define   KEY_F5               0x3e
#define   KEY_F6               0x3f
#define   KEY_F7               0x40
#define   KEY_F8               0x41
#define   KEY_F9               0x42
#define   KEY_F10              0x43
#define   KEY_F11              0x44
#define   KEY_F12              0x45

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

// Number keyboard 
#define   KEY_NUMLOCK          0x53
#define   KEY_NUM_DIV          0x54    // '/'
#define   KEY_NUM_MUL          0x55    // '*'
#define   KEY_NUM_MINUS        0x56    // '-'
#define   KEY_NUM_PLUS         0x57    // '+'
#define   KEY_NUM_ENTER        0x58

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
#define   KEY_NUM_DOT          0x63



#define   KEY_L_CTRL           0xA0
#define   KEY_L_SHIFT          0xA1
#define   KEY_L_ALT            0xA2
#define   KEY_L_GUI            0xA3
#define   KEY_R_CTRL           0xA4
#define   KEY_R_SHIFT          0xA5
#define   KEY_R_ALT            0xA6
#define   KEY_R_GUI            0xA7

#define   KEY_L_CTRL_BIT           0x01  //bit0
#define   KEY_L_SHIFT_BIT          0x02  //bit1
#define   KEY_L_ALT_BIT            0x04  //bit2
#define   KEY_L_GUI_BIT            0x08  //bit3
#define   KEY_R_CTRL_BIT           0x10  //bit4
#define   KEY_R_SHIFT_BIT          0x20  //bit5
#define   KEY_R_ALT_BIT            0x40  //bit6
#define   KEY_R_GUI_BIT            0x80  //bit7

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


#define   KEY_NextTr      0x4401//0xE8
#define   KEY_PrevTr      0x4402//0xE9
#define   KEY_Stop        0x4404//0xEA
#define   KEY_Eject       0x4408//0xEB
#define   KEY_PlayPause   0x4410//0xEC
#define   KEY_Mute        0x4420//0xED
#define   KEY_VolumI      0x0440//0xEE  //+
#define   KEY_VolumD      0x0480//0xEF  //-

#define   KEY_Media       0x4501//F0
#define   KEY_Email       0x4502//F1
#define   KEY_Calculator  0x4504//F2
#define   KEY_MyComputer  0x4508//F3
#define   KEY_Search      0x4510//F4
#define   KEY_WWW         0x4520//F5
#define   KEY_Back        0x4540//F6
#define   KEY_Forward     0x4580//F7

#define   KEY_iStop       0x4601//0xF8
#define   KEY_Refresh     0x4602//0xF9
#define   KEY_Favorites   0x4604//0xFA

#define   KEY_Power       0x0701//0xA8
#define   KEY_Sleep       0x0702//0xA9
#define   KEY_WakeUp      0x0704//0xAA

#define   KEY_User1       0x4901//0xC8
#define   KEY_User2       0x4902//0xC9
#define   KEY_User3       0x4904//0xCA
#define   KEY_User4       0x4908//0xCB
#define   KEY_User5       0x4910//0xCC
#define   KEY_User6       0x4920//0xCD
#define   KEY_User7       0x4940//0xCE
#define   KEY_User8       0x4980//0xCF

#define   KEY_Fn          0x0c00

#define   KEY_User5_Fn         0x0200
#define   KEY_Scr_Num          0x0101
#define   KEY_mode1_7          0x0102
#define   KEY_mode1_8          0x0103
#define   KEY_mode1_9          0x0104
#define   KEY_mode1_0          0x0105
#define   KEY_mode1_U          0x0106
#define   KEY_mode1_I          0x0107
#define   KEY_mode1_O          0x0108
#define   KEY_mode1_P          0x0109
#define   KEY_mode1_J          0x010A
#define   KEY_mode1_K          0x010B
#define   KEY_mode1_L          0x010C
#define   KEY_mode1_Semicolon  0x010D
#define   KEY_mode1_M          0x010E
#define   KEY_mode1_COMMA      0x010F
#define   KEY_mode1_PERIOD     0x0110

#define   KEY_mode2_F1         0x0211
#define   KEY_mode2_F2         0x0212
#define   KEY_mode2_F3         0x0213
#define   KEY_mode2_F4         0x0214
#define   KEY_mode2_F5         0x0215
#define   KEY_mode2_F6         0x0216
#define   KEY_mode2_F7         0x0217
#define   KEY_mode2_F8         0x0218
#define   KEY_mode2_F9         0x0219
#define   KEY_mode2_F10        0x021a
#define   KEY_mode2_F11        0x021b
#define   KEY_mode2_F12        0x021c

// const unsigned char kyb_code[8][17]={
//     {0x00,0x00,0x00,'16','17','5' ,'20','23','10','11','12','13','1 ',0x00,0x00},
//     {0x00,0x00,'44','30','18','19','21','7' ,'24','25','26','27','28',0x00,'29'},
//     {'59',0x00,0x00,'46','31','33','34','37','38','39','40','41','43',0x00,'129'},
//     {0x00,'127',0x00,0x00,'32','48','49','51','52','53','54','55',0x00,0x00,0x00},
//     {0x00,0x00,0x00,'36',0x00,0x00,'22','50',0x00,0x00,'79','57','84','62','89'},
//     {0x00,0x00,0x00,'58','47',0x00,'115','35',0x00,0x00,'61',0x00,0x00,'60','15'},
//     {0x00,0x00,'83','2' ,'3' ,'4' ,'6' ,'8' ,'9','119','121','123','124',0x00,'76'},
//     {'64',0x00,0x00,'110','112','113','114','116','117','118','120','122','126',0x00,'75'}
// };

// uonst unsigned char code kyb_code[8][17]={
//     {0x00,0x00,0x00,KEY_Tab,KEY_Q,KEY_4,KEY_R,KEY_U,KEY_9,KEY_0,KEY_Underscore,KEY_EqualSign,KEY_TILDE,0x00,0x00},
//     {0x00,0x00,KEY_L_SHIFT,KEY_CAPSLOCK,KEY_W,KEY_E,KEY_T,KEY_6,KEY_I,KEY_O,KEY_P,KEY_L_Brackets,KEY_R_Brackets,0x00,KEY_Slash},
//     {FnKeyIndex,0x00,0x00,KEY_Z,KEY_A,KEY_D,KEY_F,KEY_J,KEY_K,KEY_L,KEY_Semicolon,KEY_Quotation,KEY_ENTER,0x00,KEY_R_CTRL},
//     {0x00,KEY_L_CTRL,0x00,0x00,KEY_S,KEY_C,KEY_V,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_Interrogation,0x00,0x00,0x00},
//     {0x00,0x00,0x00,KEY_H,0x00,0x00,KEY_Y,KEY_B,0x00,0x00,KEY_LeftArrow,KEY_UpArrow,KEY_DownArrow,KEY_R_ALT,KEY_RightArrow},
//     {0x00,0x00,0x00,KEY_R_GUI,KEY_X,0x00,KEY_F4,KEY_G,0x00,0x00,KEY_SPACEBAR,0x00,0x00,KEY_L_ALT,KEY_Backspace},
//     {0x00,0x00,KEY_R_SHIFT,KEY_1,KEY_2,KEY_3,KEY_5,KEY_7,KEY_8,KEY_F8,KEY_F10,KEY_F12,'-',0x00,'/'},
//     {KEY_Delete,0x00,0x00,KEY_ESCAPE,KEY_F1,KEY_F2,KEY_F3,KEY_F5,KEY_F6,KEY_F7,KEY_F9,KEY_F11,'+',0x00,'*'}
//  };

void readscan(void);

#endif

