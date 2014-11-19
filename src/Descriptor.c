
#include "ModifyCode.h" 
//#define   ConfigValue    1;
const uchar8 DeviceDescriptor[0x12]={
    	0x12,//0x12,//descriptor length
    	0x01,//descriptor type
    	0x00,
    	0x02,//USB version,LSB first
    	0x00,//device class
    	0x00,//device subclass
    	0x00,//device protocol
    	Ep0MaxPackage,//max packet size
    	0xd9,
    	0x04,//vender ID 
    	0x33,
    	0x11,//product ID 
    	0x00,
    	0x01,//device version
    	0x01,//manufacturer index
    	0x02,//0x02,//product index
    	0x00,//0x03,//serial number index
    	0x01 //configurations number	
    };
const uchar8 ConDesCollection[59]={
    /******************Configuration descriptor*********************/
    	0x09,//length
    	0x02,//type
    	59,
    	0x00,//total length of configuration collection information
    	0x02,//interface number
    	0x01,//configuration number
    	0x00,//configuration index
    	0xa0,//configuration properties:power & remote wakeup
    	0x32,//max consumption current 50*2mA
    	
    /******************interface descriptor*********************/
        0x09,//length
        0x04,//type
        0x00,//interface number
        0x00,//Replacement set
        EpNumber0,//endpoint number
        0x03,//interface class:HID
        0x01,//0x00,//interface subclass
        0x01,//0x00,//interface protocol code
        0x00,//interface name index
    /*********************HID descriptor*********************/
        0X09,//length
        0x21,//type
        0x11,
        0x01,//HID protocol version
        0x00,//country code
        0x01,//descriptor number afterware
        0x22,//descriptor type afterware
        ReportLengthL0,
        ReportLengthH0,//report descriptor length
    /*********************endpoint1 descriptor*********************/
        0x07,//length
        0x05,//type
        0x81,//endpoint number
        0x03,//properties:interrupt transformer
        0x08,
        0x00,//max packet
        0x0a,//host polling time:10ms
    /*********************endpoint2 descriptor*********************/
//        0x07,//length
//        0x05,//type
//        0x02,//endpoint number
//        0x03,//properties:interrupt transformer
//        0x08,
//        0x00,//max packet
//        0x14,//host polling time:20ms
        
    /******************interface descriptor*********************/
        0x09,//length
        0x04,//type
        0x01,//interface number
        0x00,//Replacement set
        EpNumber1,//endpoint number
        0x03,//interface class:HID
        0x00,//0x00,//interface subclass
        0x00,//0x00,//interface protocol code
        0x00,//interface name index
    /*********************HID descriptor*********************/
        0X09,//length
        0x21,//type
        0x11,
        0x01,//HID protocol version
        0x00,//country code
        0x01,//descriptor number afterware
        0x22,//descriptor type afterware
        ReportLengthL1,
        ReportLengthH1,//report descriptor length
    /*********************endpoint3 descriptor*********************/
        0x07,//length
        0x05,//type
        0x82,//endpoint number
        0x03,//properties:interrupt transformer
        0x08,
        0x00,//max packet
        0x0a //host polling time:15ms      
    } ;
 const uchar8 LanguageID[4]={
 	    0x04,
 	    0x03,
 	    0x09,
 	    0x04
    };
 const uchar8 ManuString[16]={
 	    0x10,
 	    0x03,
 	    0x43,0x00,  //C
 	    0x68,0x00,  //h
 	    0x69,0x00,  //i
 	    0x63,0x00,  //c
 	    0x6f,0x00,  //o
 	    0x6e,0x00,  //n
 	    0x79,0x00   //y
// 	    0x48,0x00,  //H
// 	    0x4f,0x00,  //O
// 	    0x4c,0x00,  //L
// 	    0x54,0x00,  //T
// 	    0x45,0x00,  //E
// 	    0x4b,0x00   //K
 	};
 const uchar8 ProString[26]={
 	    0x1a,
 	    0x03,
 	    0x55,0x00,  //U
 	    0x53,0x00,  //S
 	    0x42,0x00,  //B
 	    0x20,0x00,  // 
 	    0x4b,0x00,  //K
 	    0x65,0x00,  //e
 	    0x79,0x00,  //y
 	    0x62,0x00,  //b
 	    0x6f,0x00,  //o
 	    0x61,0x00,  //a
 	    0x72,0x00,  //r
 	    0x64,0x00   //d
// 	    0x48,0x00,  //H
// 	    0x49,0x00,  //I
// 	    0x44,0x00,  //D
// 	    0x20,0x00,  // 
// 	    0x44,0x00,  //D
// 	    0x65,0x00,  //e
// 	    0x76,0x00,  //v
// 	    0x69,0x00,  //i
// 	    0x63,0x00,  //c
// 	    0x65,0x00   //e       
 	};
  const uchar8 SerialString[22]={
        0x16,
        0x03,
        0x32,0x00,  //2
        0x30,0x00,  //0
        0x31,0x00,  //1
        0x33,0x00,  //3
        0x2d,0x00,  //-
        0x30,0x00,  //0
        0x34,0x00,  //4
        0x2d,0x00,  //-
        0x31,0x00,  //1
        0x32,0x00   //2
    };	
 const uchar8 KeyboardReptDesc[ReportLengthL0]={     //default ReportLengthH=0
		 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
		 0x09, 0x06, // USAGE (Keyboard)
		 0xa1, 0x01, // COLLECTION (Application)
		 0x05, 0x07, //     USAGE_PAGE (Keyboard/Keypad)
		 0x19, 0xe0, //     USAGE_MINIMUM (Keyboard LeftControl)
		 0x29, 0xe7, //     USAGE_MAXIMUM (Keyboard Right GUI)
		 0x15, 0x00, //     LOGICAL_MINIMUM (0)
		 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
		 0x95, 0x08, //     REPORT_COUNT (8)
		 0x75, 0x01, //     REPORT_SIZE (1)
		 0x81, 0x02, //     INPUT (Data,Var,Abs)
		
		 0x95, 0x01, //     REPORT_COUNT (1)
		 0x75, 0x08, //     REPORT_SIZE (8)
		 0x81, 0x03, //     INPUT (Cnst,Var,Abs)
		 
		 0x95, 0x06, //   REPORT_COUNT (6)
		 0x75, 0x08, //   REPORT_SIZE (8)
		 0x15, 0x00, //   LOGICAL_MINIMUM (0)
		 0x26, 0xff, 0x00, //   LOGICAL_MAXIMUM (255)
		 0x05, 0x07, //   USAGE_PAGE (Keyboard/Keypad)
		 0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
		 0x2a, 0xff, 0x00, //   USAGE_MAXIMUM (Keyboard Application)
		 0x81, 0x00, //     INPUT (Data,Ary,Abs)
		 
		 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
		 0x95, 0x05, //   REPORT_COUNT (5)
		 0x75, 0x01, //   REPORT_SIZE (1)
		 0x05, 0x08, //   USAGE_PAGE (LEDs)
		 0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
		 0x29, 0x05, //   USAGE_MAXIMUM (Kana)
		 0x91, 0x02, //   OUTPUT (Data,Var,Abs)
		 0x95, 0x01, //   REPORT_COUNT (1)
		 0x75, 0x03, //   REPORT_SIZE (3)
		 0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)
		 
		 0x26,0xff,0x00,	//Logical Maximum (255) 
//       0x15,0x00,  //   Logical Minimum (0) 
         0x75,0x08,  //   Report size (8)
         0x95,0x08,  //   Report Count (8) 
         0x06,0x99,0xFF,  //Usage Page (User defined)
         0x09,0x03,  //   Usage(User defined)
         0xb1,0x02,  //   feature (Data, Variable, Absolute)
         
		 0xc0        //   END_COLLECTION
    };
    
const uchar8 HotkeyReptDesc[ReportLengthL1]={ 

	    0x06, 0x01, 0x00,  //Usage Page (Generic Desktop)
		0x09, 0x80,  //Usage (System control)
		0xa1, 0x01,  //Collection (Application)
		0x85, 0x01,  //Report ID (1)
		0x19, 0x81,  //Usage Min (Power)
		0x29, 0x83,  //Usage Max (WakeUp)
		0x15, 0x00,  //Logical Minimum (0)
		0x25, 0x01,  //Logical Maximum (1)
		0x95, 0x03,  //Report Count (3)
		0x75, 0x01,  //Report Size (1)
		0x81, 0x02,  //Input (Dat, Var, Abs)
		
		0x95, 0x01,  //Report Count (1)
		0x75, 0x05,  //Report Size (5)
		0x81, 0x01,  //Input (constant)
		0xc0,  //End Collection
//*************************************************************************

		0x05, 0x0c,  //usage_page (Consumer Devices)
		0x09, 0x01,  //Usage (Consumer Control)
		0xa1, 0x01,  //Collection (Application)
		0x85, 0x03,  //Report_ID (3)		
		0x15, 0x00,  // Logical_minimum (0)
		0x25, 0x01,  // Logical Maximun (1)		
		0x19, 0xb5,  // usage minimun (next track, prev track, cd_stop, eject)
		0x29, 0xb8,  // Usage_Maximun
		0x09, 0xcd,  // Usage (play/pause)
		0x09, 0xe2,  // Usage (Mute)
		0x09, 0xe9,  // Usage (V+)		
		0x09, 0xea,  // Usage (V-)
		0x75, 0x01,  // Report_size (1)
		0x95, 0x08,  // Report_count (8)		
		0x81, 0x02,  //Input: (Data, Variable, Absolute)
		
		0x0a, 0x83, 0x01,  // usage media
		0x0a, 0x8a, 0x01,  // Usage (Email)
		0x0a, 0x92, 0x01,  // Usage (Calculator)
		0x0a, 0x94, 0x01,  // Usage (My Computer)
		0x0a, 0x21, 0x02,  // Usage (WWW Searc)
		0x1a, 0x23, 0x02,  // usage minimun (WWW ome Back, forward)
		0x2a, 0x25, 0x02,  // Usage_Maximun		
		0x81, 0x02,  //Input: (Data, Variable, Absolute)
		
		0x0a, 0x26, 0x02,  // usage www_stop
		0x0a, 0x27, 0x02,  // Usage_Maximun (WWW Refresh)
		0x0a, 0x2a, 0x02,  // Usage (WWW Favorite)
		0x95, 0x03,  // Report_count (3)
		0x81, 0x02,  // Input: (Data, Variable, Absolute)
		
		0x95, 0x05,  // Report_count (5)
		0x81, 0x01,  // Input: (Constant)
		0xc0,  // End Collection
//*************************************************************************

		0x06, 0x00, 0xff,  // Usage Page (User define)
		0x09, 0x01,  // Usage (Consumer Control)
		0xa1, 0x01,  // Collection (Application)
		0x85, 0x02,  // Report ID (2)		
		0x25, 0x01,  // Logical Maximum (1)
		0x15, 0x00,  // Logical Minimum (0)
		0x1a, 0xf1, 0x00,  // Usage Minimum
		0x2a, 0xf8, 0x00,  // Usage Maximum		
		0x75, 0x01,  // Report size (1)
		0x95, 0x08,  // Report Count (8)
		0x81, 0x02,  // Input (Data, Variable, Absolute)
		
//Below purple color is existed in KU-0833 mode 4 only 
//for (Russian/English Russian/EnglishRussian/EnglishRussian/
//English Russian/EnglishRussian/EnglishRussian/English Russian/
//English Russian/English) LedLed on/off on/off 
//control channel control channel control channel control 
//channel control channel control channel, 
//other Mode 1, 2, 3 haven¡¦t purple descriptor under.
//		0x09, 0x51,  // Usage
//		0x95, 0x01,  //Report count (1)
//		0xb1, 0x02,  //Feature (data,variable,absolute)
//		0x95, 0x07,  //Report count (7)		ƒnƒnƒnƒ§
//		0xb1, 0x01,  //Feature (constant)
		
		0xc0  // End Collection
    };

 /********************Selective Suspend***********************/

const uchar8 OSString[0x12]={
	    0x12,
	    0x03,
	    0x4d,0x00,   //M
	    0x53,0x00,   //S
	    0x46,0x00,   //F
	    0x54,0x00,   //T
	    0x31,0x00,   //1
	    0x30,0x00,   //0
	    0x30,0x00,   //0
	    VendorDefined,       //Vendor defined 
	    0x00
    };
const uchar8 OSFeatureDescriptor[0x4c]={
	 	0x4c,0x00,0x00,0x00,  //dwLength
	 	0x00,0x01,           //bcdVersion
	 	0x05,0x00,	         //wIndex
	 	0x01,0x00,           //wCount
	 	
	 	0x42,0x00,0x00,0x00, //dwSize	 	
	 	0x04,0x00,0x00,0x00, //dwPropertyDataType
	    0x30,0x00,           //wPropertyNameLength	    
//	    0x48,0x00,           //H
//	    0x63,0x00,           //c
//	    0x44,0x00,           //D
//	    0x69,0x00,           //i
//	    0x73,0x00,           //s
//	    0x61,0x00,           //a
//	    0x62,0x00,           //b
//	    0x6c,0x00,           //l
//	    0x65,0x00,           //e
	    
	    0x53,0x00,           //S
	    0x65,0x00,           //e
	    0x6c,0x00,           //l
	    0x65,0x00,           //e
	    0x63,0x00,           //c
	    0x74,0x00,           //t
	    0x69,0x00,           //i
	    0x76,0x00,           //v
	    0x65,0x00,           //e
	    0x53,0x00,           //S
	    0x75,0x00,           //u
	    0x73,0x00,           //s
	    0x70,0x00,           //p
	    0x65,0x00,           //e
	    0x6e,0x00,           //n
	    0x64,0x00,           //d
	    0x45,0x00,           //E
	    0x6e,0x00,           //n
	    0x61,0x00,           //a
	    0x62,0x00,           //b
	    0x6c,0x00,           //l
	    0x65,0x00,           //e
	    0x64,0x00,           //d   
	    0x00,0x00,           //    //bPropertyName 
	    0x04,0x00,0x00,0x00, //dwPropertyDataLength
	    0x01,0x00,0x00,0x00  //bPropertyData
    };	













