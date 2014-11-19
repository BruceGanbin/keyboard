
#include "Variable.h" 

//volatile           uchar8            wakeupflag; 
//volatile           uchar8            uc_buffer;

volatile           const             uchar8              *pSendDescriptor;
volatile           uchar8            *pSendData;  //pointer for endpoint
volatile           uint16            SendLength;   //for actual send length
volatile           uchar8            count;        //for timer delay
volatile           uchar8            ReportProtocol; //for set_protocol and get_protocol

volatile           uchar8            ucIdleTime;  //for set_idle
volatile       	   uchar8            ucUSBState;
volatile       	   uchar8            Ep2BuffSize;

volatile           uchar8            bmRequestType;
volatile           uchar8            bRequest;
volatile           uchar8            wValueH;
volatile           uchar8            wValueL;
volatile           uchar8            wIndexH;
volatile           uchar8            wIndexL;
volatile           uint16            wLength;

volatile           uchar8            scanlineno;
volatile           uchar8            KeyNo;
volatile           uchar8            IndexBuf;
volatile           uchar8            Buff_Index;
volatile           uchar8            GKEYCT;
volatile           uchar8            GPHONT;
volatile           uchar8            GREPCT;
volatile           uchar8            int_temp1;
//volatile           uchar8            int_temp2;
volatile           uchar8            temp1_matrix;
volatile           uchar8            comkeys;
volatile           uchar8            CurrentState;
volatile           uchar8            fn_key_code;
volatile           uchar8            normal_buff;
volatile           uchar8            keycode;

//volatile           uchar8            Ep1_Buff[16];
//volatile           uchar8            Ep2_Buff[1];
volatile           uchar8            *IO_address[8];
//const uint16 IO_address[8]={
//	     0x25,       //_pcc
//	     0x24,       //_pc	,scan in address
//
//	     0x23,       //_pbc
//	     0x22,       //_pb	     
//	     0x1b,       //_pac
//	     0x1a,       //_pa
//	     0x27,       //_pdc
//	     0x26        //_pd
//     };
volatile           Flag_union        Flagb;    //flag bits
volatile           Flag_union        FlagB;    //flag byte

volatile           KeyFlag_union     KeyFlagb;    //flag bits
volatile           KeyFlag_union     KeyFlagB;    //flag byte


const uchar8 scan_out[8]={
    0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f
     };
const uint16 Fn_mode_key[58]={
	 KEY_User5,      KEY_Fn,
	 KEY_ScrollLock, KEY_NUMLOCK,
     KEY_7,          KEY_NUM_7,
     KEY_8,          KEY_NUM_8,
     KEY_9,          KEY_NUM_9,
     KEY_0,          KEY_NUM_DIV,
     KEY_U,          KEY_NUM_4,
     KEY_I,          KEY_NUM_5,
     KEY_O,          KEY_NUM_6,
     KEY_P,          KEY_NUM_MUL,
     KEY_J,          KEY_NUM_1,
     KEY_K,          KEY_NUM_2,
     KEY_L,          KEY_NUM_3,
     KEY_Semicolon,  KEY_NUM_MINUS,
     KEY_M,          KEY_NUM_0,
     KEY_COMMA,      KEY_NUM_DOT,
     KEY_PERIOD,     KEY_NUM_PLUS,	
     
	 KEY_F1,         KEY_Sleep,     //Fn+Fx
	 KEY_F2,         KEY_Email,
	 KEY_F3,         KEY_WWW,
	 KEY_F4,         KEY_Refresh,
	 KEY_F5,         KEY_Back,
	 KEY_F6,         KEY_Forward,
	 KEY_F7,         KEY_Favorites,
	 KEY_F8,         KEY_Search,
	 KEY_F9,         KEY_PrevTr,
	 KEY_F10,        KEY_Stop,
	 KEY_F11,        KEY_PlayPause,
	 KEY_F12,        KEY_NextTr
     };
const uchar8 macro_key_matrix[12]={
  	 0x00, 0x06, 0x00, 0x00,	//ctrl_C
     0x00, 0x1b, 0x00, 0x00,	//ctrl_X   
     0x00, 0x19, 0x00, 0x00		//CTRL_V
     };
const uchar8 scan_line_tab[total_scanline]={
         s0_scan_out,		//s0
         s1_scan_out,		//s1
         s2_scan_out,		//s2
         s3_scan_out,		//s3
         s4_scan_out,		//s4
         s5_scan_out,		//s5
         s6_scan_out,		//s6
         s7_scan_out,		//s7
		 s8_scan_out,		//s8
		 s9_scan_out,		//s9
		 s10_scan_out,		//s10
		 s11_scan_out,		//s11
		 s12_scan_out,		//s12
		 s13_scan_out,		//s13
		 s14_scan_out,		//s14
		 s15_scan_out,		//s15
		 s16_scan_out,		//s16
		 s17_scan_out,		//s17	
    }; 
//const uint16 KeyMatrix2[144]={
//	
//	    KEY_CAPSLOCK,    KEY_NUMLOCK,     KEY_Backspace,   KEY_NUM_8,  
//	        KEY_NUM_9,       KEY_ENTER,       KEY_VolumI,    KEY_NextTr,
//	    KEY_NUM_0,       KEY_NUM_1,       KEY_NUM_2,       KEY_NUM_3,
//	        KEY_NUM_4,       KEY_NUM_5,       KEY_NUM_6,     KEY_NUM_7,
//	    KEY_A,           KEY_B,           KEY_C,           KEY_D,
//	        KEY_E,           KEY_F,           KEY_G,         KEY_Sleep,
//	    KEY_H,           KEY_mode1_I,     KEY_mode1_J,     KEY_mode1_K,
//	        KEY_mode1_L,     KEY_mode1_M,     KEY_N,         KEY_Forward,
//	    KEY_mode1_O,     KEY_mode1_P,     KEY_Q,           KEY_R,
//	        KEY_S,           KEY_T,           KEY_mode1_Semicolon,   KEY_Slash,
//	    KEY_mode1_U,     KEY_V,           KEY_W,           KEY_X,
//	        KEY_Y,           KEY_Z,           KEY_R_SHIFT,     KEY_mode1_PERIOD,
//	    KEY_End,         KEY_Home,        KEY_LeftArrow,   KEY_CODE14,         
//	    KEY_NUM_DOT,     KEY_SPACEBAR,     KEY_mode1_7,     KEY_mode1_COMMA,
//	    KEY_Delete,      KEY_Insert,      KEY_L_SHIFT,   KEY_UpArrow,  
//	    KEY_6,           KEY_PageDown,     KEY_APPS,     KEY_CODE151,
//	    KEY_R_GUI,           KEY_CODE107,           KEY_5,           KEY_mode1_8,        
//	    KEY_mode1_0,     KEY_Underscore,  KEY_L_Brackets,  KEY_Quotation,
//	    KEY_CODE131,     KEY_NUM_DIV,           KEY_PageUp,           KEY_4,
//	    KEY_EqualSign,   KEY_R_Brackets,  KEY_CODE42,      KEY_CODE56,
//	    KEY_DownArrow,           KEY_NUM_MUL,           KEY_NUM_PLUS,           KEY_3,
//	    KEY_mode2_F12,   KEY_PrintScreen, KEY_ScrollLock,  KEY_Pause,
//	    KEY_CODE150,     KEY_NUM_MINUS,   KEY_Interrogation,           KEY_2,
//	    KEY_mode2_F11,   KEY_mode2_F10,   KEY_mode2_F9,    KEY_mode2_F8,
//	   KEY_CODE133 ,           KEY_User5_Fn,    KEY_PlayPause,           KEY_1,
//	    KEY_mode2_F4,    KEY_mode2_F5,    KEY_mode2_F6,    KEY_mode2_F7,
//	    KEY_RightArrow,           KEY_CODE45,      KEY_CODE132,           KEY_Search,
//	    KEY_mode2_F3,    KEY_mode2_F2,    KEY_Tab,         KEY_mode2_F1,
//	    KEY_Refresh,     KEY_L_GUI,       KEY_WakeUp,      KEY_mode1_9,
//	    KEY_MyComputer,  KEY_Email,       KEY_Mute,        KEY_TILDE,
//	    KEY_L_ALT,       KEY_iStop,       KEY_WWW,         KEY_NUM_ENTER,
//	    KEY_Calculator,  KEY_Media,       KEY_R_ALT,       KEY_ESCAPE,
//	    KEY_Favorites,   KEY_Back,        KEY_L_CTRL,      KEY_Power,
//	    KEY_R_CTRL,      KEY_Stop,        KEY_VolumD,      KEY_PrevTr,
//	    key_ctrl_c,      KEY_User7,       KEY_User6,       KEY_Eject,
//	    KEY_User4,       KEY_User3,       KEY_User2,       KEY_User1
//    };
const uint16 KeyMatrix[144]={
	
	    KEY_Search,      KEY_Forward,     KEY_L_SHIFT,     KEY_Sleep,  
	    KEY_R_SHIFT,     KEY_PlayPause,   KEY_VolumI,      KEY_NextTr,
	    KEY_CODE131,     KEY_CODE150,     KEY_CODE151,     KEY_APPS,
	    KEY_CODE133,     KEY_R_GUI,       KEY_CODE132,     KEY_SPACEBAR,
	    KEY_NUM_ENTER ,  KEY_NUM_0,       KEY_NUM_MINUS,   KEY_NUM_1,
	    KEY_NUM_PLUS,    KEY_NUM_MUL,     KEY_NUM_DIV,     KEY_NUM_8,
	    KEY_CODE107,     KEY_NUM_DOT,     KEY_NUM_3,       KEY_NUM_7,
	    KEY_NUM_9,       KEY_NUM_2,       KEY_NUM_5,       KEY_NUMLOCK,
	    KEY_RightArrow,  KEY_PageUp,      KEY_NUM_6,       KEY_Interrogation,
	    KEY_mode1_9,     KEY_mode1_P,     KEY_mode1_Semicolon,   KEY_Slash,
	    KEY_PageDown,    KEY_DownArrow,   KEY_ENTER,       KEY_NUM_4,
	    KEY_mode1_8,     KEY_mode1_O,     KEY_mode1_L,     KEY_mode1_PERIOD,
	    KEY_End,         KEY_Home,        KEY_LeftArrow,   KEY_CODE14,         
	    KEY_mode1_I,     KEY_mode1_K,     KEY_mode1_7,     KEY_mode1_COMMA,
	    KEY_Delete,      KEY_Insert,      KEY_Backspace,   KEY_UpArrow,  
	    KEY_6,           KEY_mode1_U,     KEY_mode1_J,     KEY_mode1_M,
	    KEY_N,           KEY_H,           KEY_5,           KEY_Y,        
	    KEY_mode1_0,     KEY_Underscore,  KEY_L_Brackets,  KEY_Quotation,
	    KEY_B,           KEY_G,           KEY_T,           KEY_4,
	    KEY_EqualSign,   KEY_R_Brackets,  KEY_CODE42,      KEY_CODE56,
	    KEY_V,           KEY_F,           KEY_E,           KEY_3,
	    KEY_mode2_F12,   KEY_PrintScreen, KEY_ScrollLock,  KEY_Pause,
	    KEY_D,           KEY_C,           KEY_R,           KEY_2,
	    KEY_mode2_F11,   KEY_mode2_F10,   KEY_mode2_F9,    KEY_mode2_F8,
	    KEY_X,           KEY_User5_Fn,    KEY_W,           KEY_1,
	    KEY_mode2_F4,    KEY_mode2_F5,    KEY_mode2_F6,    KEY_mode2_F7,
	    KEY_Z,           KEY_CODE45,      KEY_Q,           KEY_CAPSLOCK,
	    KEY_mode2_F3,    KEY_mode2_F2,    KEY_Tab,         KEY_mode2_F1,
	    KEY_Refresh,     KEY_L_GUI,       KEY_WakeUp,      KEY_S,
	    KEY_MyComputer,  KEY_Email,       KEY_Mute,        KEY_TILDE,
	    KEY_L_ALT,       KEY_iStop,       KEY_WWW,         KEY_A,
	    KEY_Calculator,  KEY_Media,       KEY_R_ALT,       KEY_ESCAPE,
	    KEY_Favorites,   KEY_Back,        KEY_L_CTRL,      KEY_Power,
	    KEY_R_CTRL,      KEY_Stop,        KEY_VolumD,      KEY_PrevTr,
	    key_ctrl_c,      KEY_User7,       KEY_User6,       KEY_Eject,
	    KEY_User4,       KEY_User3,       KEY_User2,       KEY_User1
    };