
#ifndef  _KEYBOARD_H
#define  _KEYBOARD_H

#define   total_scanline   18
#define   KEY_BUF_END      0x06
#define   FnKeyIndex       0x61     

#define   s0_scan_out      0x40
#define   s1_scan_out      0x41
#define   s2_scan_out      0x42
#define   s3_scan_out      0x43
#define   s4_scan_out      0x44
#define   s5_scan_out      0x45
#define   s6_scan_out      0x46
#define   s7_scan_out      0x47
#define   s8_scan_out      0x20
#define   s9_scan_out      0x21
#define   s10_scan_out     0x22
#define   s11_scan_out     0x23
#define   s12_scan_out     0x24
#define   s13_scan_out     0x25
#define   s14_scan_out     0x26
#define   s15_scan_out     0x27
#define   s16_scan_out     0x60
#define   s17_scan_out     0x61

#define   key_error        0x01
#define   key_undefine     0x03

#define   KEY_A            0x04
#define   KEY_B            0x05
#define   KEY_C            0x06
#define   KEY_D            0x07
#define   KEY_E            0x08
#define   KEY_F            0x09
#define   KEY_G            0x0a
#define   KEY_H            0x0b
#define   KEY_I            0x0c
#define   KEY_J            0x0d
#define   KEY_K            0x0e
#define   KEY_L            0x0f
#define   KEY_M            0x10
#define   KEY_N            0x11
#define   KEY_O            0x12
#define   KEY_P            0x13
#define   KEY_Q            0x14
#define   KEY_R            0x15
#define   KEY_S            0x16
#define   KEY_T            0x17
#define   KEY_U            0x18
#define   KEY_V            0x19
#define   KEY_W            0x1a
#define   KEY_X            0x1b
#define   KEY_Y            0x1c
#define   KEY_Z            0x1d

#define   KEY_ESCAPE       0x29       
#define   KEY_Tab          0x2b
#define   KEY_CAPSLOCK     0x39
#define   KEY_Backspace    0x2a
#define   KEY_ENTER        0x28
#define   KEY_SPACEBAR     0x2c

#define   KEY_L_CTRL       0x0801//0xA0
#define   KEY_L_SHIFT      0x0802//0xA1
#define   KEY_L_ALT        0x0804//0xA2
#define   KEY_L_GUI        0x0808//0xA3
#define   KEY_R_CTRL       0x0810//0xA4
#define   KEY_R_SHIFT      0x0820//0xA5
#define   KEY_R_ALT        0x0840//0xA6
#define   KEY_R_GUI        0x0880//0xA7

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

#define   KEY_1          0x1e
#define   KEY_2          0x1f
#define   KEY_3          0x20
#define   KEY_4          0x21
#define   KEY_5          0x22
#define   KEY_6          0x23
#define   KEY_7          0x24
#define   KEY_8          0x25
#define   KEY_9          0x26
#define   KEY_0          0x27

#define   KEY_F1         0x3a
#define   KEY_F2         0x3b
#define   KEY_F3         0x3c
#define   KEY_F4         0x3d
#define   KEY_F5         0x3e
#define   KEY_F6         0x3f
#define   KEY_F7         0x40
#define   KEY_F8         0x41
#define   KEY_F9         0x42
#define   KEY_F10        0x43
#define   KEY_F11        0x44
#define   KEY_F12        0x45
         
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

#define   KEY_NUM_1       0x59
#define   KEY_NUM_2       0x5a
#define   KEY_NUM_3       0x5b
#define   KEY_NUM_4       0x5c            
#define   KEY_NUM_5       0x5d
#define   KEY_NUM_6       0x5e
#define   KEY_NUM_7       0x5f
#define   KEY_NUM_8       0x60
#define   KEY_NUM_9       0x61
#define   KEY_NUM_0       0x62

#define   KEY_CODE29      0x31
#define   KEY_CODE42      0x32
#define   KEY_CODE45      0x64
#define   KEY_APPS        0x65
#define   KEY_CODE107     0x1085
#define   KEY_CODE56      0x1087
#define   KEY_CODE133     0x1088
#define   KEY_CODE14      0x1089
#define   KEY_CODE132     0x108a
#define   KEY_CODE131     0x108b
#define   KEY_CODE151     0x2090   //key_Hangul
#define   KEY_CODE150     0x2091   //Key_Hanja

//#define   KEY_FALSE       0x00     //for hot key

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

//for combine key
#define   key_ctrl_c	  0x4300
#define   key_ctrl_x	  0x4301
#define   key_ctrl_v	  0x4302

//#define   Fn_mode         key_undefine

#endif







