
#ifndef   _VARIABLE_H
#define   _VARIABLE_H

#include    "ModifyRegister.h"
#include    "Keyboard.h"

typedef      unsigned char     uchar8;  //8 bits 
typedef      unsigned int      uint16;  //16 bits

#define      STATE_DEFAULT    0
#define      STATE_ADDR       1
#define      STATE_CONFIG     2

//declare   descriptor  array
extern        const       uchar8       DeviceDescriptor[];
extern        const       uchar8       ConDesCollection[];
extern        const       uchar8       LanguageID[];
extern        const       uchar8       ManuString[];
extern        const       uchar8       ProString[];
extern        const       uchar8       KeyboardReptDesc[];
extern        const       uchar8       HotkeyReptDesc[];
extern        const       uchar8       SerialString[];
extern        const       uchar8       OSString[];
extern        const       uchar8       OSFeatureDescriptor[];

extern        const       uint16       KeyMatrix[];
//extern        const       uint16       IO_address[];
extern        const       uint16       Fn_mode_key[];
extern        const       uchar8       scan_line_tab[];
extern        const       uchar8       scan_out[];
extern        const       uchar8       macro_key_matrix[];

extern        volatile    const        uchar8      *pSendDescriptor;//pointer for Descriptor
extern        volatile    uchar8       *pSendData;  //pointer for endpoint
extern        volatile    uint16       SendLength;
extern        volatile    uchar8       count;
extern        volatile    uchar8       ReportProtocol;

extern        volatile    uchar8       ucIdleTime;  
extern        volatile    uchar8       ucUSBState;
extern        volatile    uchar8       Ep2BuffSize;

extern        volatile    uchar8       bmRequestType;
extern        volatile    uchar8       bRequest;
extern        volatile    uchar8       wValueH;
extern        volatile    uchar8       wValueL;
extern        volatile    uchar8       wIndexH;
extern        volatile    uchar8       wIndexL;
extern        volatile    uint16       wLength;

extern        volatile    uchar8            scanlineno;
extern        volatile    uchar8            KeyNo;
extern        volatile    uchar8            IndexBuf;
extern        volatile    uchar8            Buff_Index;
extern        volatile    uchar8            GKEYCT;
extern        volatile    uchar8            GPHONT;
extern        volatile    uchar8            GREPCT;
extern        volatile    uchar8            int_temp1;
//volatile      extern      uchar8            int_temp2;
extern        volatile    uchar8            temp1_matrix;
extern        volatile    uchar8            comkeys;
extern        volatile    uchar8            CurrentState;
extern        volatile    uchar8            fn_key_code;
extern        volatile    uchar8            normal_buff;
extern        volatile    uchar8            keycode;

extern        volatile    uchar8            *IO_address[8];
//volatile      extern      uchar8       Ep1_Buff[16];
//volatile      extern      uchar8       Ep2_Buff[1];
DEFINE_SFR(uchar8, Request_buffer[9],          0x180);
DEFINE_SFR(uchar8, GOLDKY[total_scanline],     0x1a0);
DEFINE_SFR(uchar8, GNEWKY[total_scanline],     0x18a);
DEFINE_SFR(uchar8, key_code_buff[KEY_BUF_END], 0x1b8);
DEFINE_SFR(uchar8, Fn_key_break_state[7],      0x1C0);
DEFINE_SFR(uchar8, fifo_out[8],                0x1d0);
DEFINE_SFR(uchar8, key_byte[8],                0x1d8);
//volatile           uchar8            multi_key_byte1;
//volatile           uchar8            multi_key_byte2;
//volatile           uchar8            multi_key_byte3;
//volatile           uchar8            acpi_key_byte;
//volatile           uchar8            Mdif_key_byte;
//volatile           uchar8            hot_key_byte1;
//volatile           uchar8            hot_key_byte2;

typedef   volatile    struct  {
	uchar8   TimeOut             : 1;
	uchar8   OSString            : 1;
	uchar8   BootloaderSuccess   : 1;
	uchar8   ReadWrite_complete  : 1;
	uchar8   NeedZeroPacket      : 1;
	uchar8   ToBootloader        : 1;
	uchar8   OutFeature          : 1;
	uchar8   Output              : 1;	
	uchar8   tx                  : 1;
	uchar8   StallFlag           : 1;
	uchar8   GetEp0Data          : 1;
	uchar8   Ep1Busy             : 1;
	uchar8   Ep2Busy             : 1;
	uchar8   :0;//Reserved;
}StructType ;

typedef  volatile   union {
	StructType  Flag_bit;
	uchar8      Flag_byte;
}Flag_union;
extern      volatile      Flag_union   Flagb;
extern      volatile      Flag_union   FlagB;

#define       FlagBit     Flagb.Flag_bit
#define       FlagByte    FlagB.Flag_byte

typedef     volatile      struct  {
	uchar8   has_change          : 1;
	uchar8   has_key_change      : 1;	
	uchar8   FPHNCK              : 1;
	uchar8   FPHONK              : 1;
	uchar8   thefirstPHout       : 1;
	uchar8   KB_KeyUpt           : 1;
	uchar8   buffull             : 1;	
	uchar8   hotkeyset           : 1;
	uchar8   combinekey          : 1;
	uchar8   fn_key_break        : 1;
	uchar8   f2_f1               : 1;
	uchar8   has_usb_fn          : 1;	
	uchar8   fn_mode_now         : 1;
	uchar8   always_fn           : 1;
	uchar8   multi_key_chg       : 1;
	uchar8   acpi_key_chg        : 1;
	uchar8   hot_key_chg         : 1;
	uchar8   Fn_mode        	 : 1;
	uchar8   chk_key_change 	 : 1;
	uchar8   return_value        : 1;	
	uchar8   NumLockStatus       : 1;
	uchar8   CapsLockStatus      : 1;
	uchar8   ScrollLockStatus    : 1;
	uchar8   wakeup              : 1;
	uchar8   wakeupbreak         : 1;
	uchar8   :0;//Reserved;
}KeyStructType;
typedef    volatile       union {
	KeyStructType  KeyFlag_bit;
	uchar8         KeyFlag_byte;
}KeyFlag_union;
extern     volatile       KeyFlag_union   KeyFlagb;
extern     volatile       KeyFlag_union   KeyFlagB;

#define       KeyFlag        KeyFlagb.KeyFlag_bit
#define       KeyFlagByte    KeyFlagB.KeyFlag_byte

#endif