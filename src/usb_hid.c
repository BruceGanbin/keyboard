#include "usb_hid.h"

u8 code DeviceDescriptor[DEVICE_DESCRIPTOR_SIZE]=  
{
    0x12,//bLength
    0x01,//bDescriptorType
    0x10,//bcdUSB
    0x01,
    0x00,//bDeviceClass
    0x00,//bDeviceSubClass
    0x00,//bDeviceProtocol
    0x08,//bMaxPacketSize0
    0x8A,//idVender
    0x25,
    0x00,//idProduct
    0x40,
    0x00,//bcdDevice
    0x01,
    0x01,//iManufacturer
    0x02,//iProduct
    0x03,//iSerialNumber
    0x01 //bNumConfigurations
};

U8 code ConfigurationDescriptor[CONFIGURATION_DESCRIPTOR_SIZE]=
{
    0x09,//bLength
    0x02,//bDescriptorType
    //wTotalLength
    sizeof(ConfigurationDescriptor)&0xFF, 
    (sizeof(ConfigurationDescriptor)>>8)&0xFF, 
    0x01,//bNumInterfaces
    0x01,//bConfiguration
    0x00,//iConfiguration
    0x80,//bmAttributes
    0x32,//bMaxPower
    
    0x09,//bLength
    0x04,//bDescriptorType
    0x00,//bInterfaceNumber
    0x00,//bAlternateSetting
    0x01,//bNumEndpoints
    0x03,//bInterfaceClass
    0x01,//bInterfaceSubClass
    0x02,//bInterfaceProtocol
    0x00,//iInterface
    
    0x09,//bLength
    0x21,//bDescriptorType
    0x10,//bcdHID
    0x01,
    0x21,//bCountyCode
    0x01,//bNumDescriptors
    0x22,//bDescriptorType
    //bDescriptorLength
    sizeof(KeyboardReportDescriptor)&0xFF,
    (sizeof(KeyboardReportDescriptor)>>8)&0xFF,
    
    0x07,//bLength
    0x05,//bDescriptorType
    0x81,//bEndpointAddress
    0x03,//bmAttributes
    0x10,//wMaxPacketSize
    0x00,
    0x0A//bInterval
};



u8 code Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
{
    /***************ÅäÖÃÃèÊö·û***********************/
    0x09,  //bLength×Ö¶Î
    USB_CONFIGURATION_DESCRIPTOR_TYPE,  //bDescriptorType×Ö¶Î
    //wTotalLength×Ö¶Î
    JOYSTICK_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
  
    0x02, //bNumInterfaces×Ö¶Î
    0x01, //bConfiguration×Ö¶Î
    0x00, //iConfigurationz×Ö¶Î
    0x80, //bmAttributes×Ö¶Î
    0x32, //bMaxPower×Ö¶Î
  
    /*******************µÚÒ»¸ö½Ó¿ÚÃèÊö·û*********************/
    0x09, //bLength×Ö¶Î
    0x04, //bDescriptorType×Ö¶Î
    0x00, //bInterfaceNumber×Ö¶Î
    0x00, //bAlternateSetting×Ö¶Î
    0x02, //bNumEndpoints×Ö¶Î
    0x03, //bInterfaceClass×Ö¶Î
    0x01, //bInterfaceSubClass×Ö¶Î
    0x01, //bInterfaceProtocol×Ö¶Î
    0x00, //iConfiguration×Ö¶Î
  
    /******************HIDÃèÊö·û************************/
    0x09, //bLength×Ö¶Î
    0x21, //bDescriptorType×Ö¶Î
    0x10, //bcdHID×Ö¶Î
    0x01,
    0x21, //bCountyCode×Ö¶Î
    0x01, //bNumDescriptors×Ö¶Î
    0x22, //bDescriptorType×Ö¶Î
  
    //bDescriptorLength×Ö¶Î¡£
    //ÏÂ¼¶ÃèÊö·ûµÄ³¤¶È¡£ÏÂ¼¶ÃèÊö·ûÎª¼üÅÌ±¨¸æÃèÊö·û¡£
    sizeof(KeyboardReportDescriptor)&0xFF,
    (sizeof(KeyboardReportDescriptor)>>8)&0xFF,
  
    /**********************ÊäÈë¶ËµãÃèÊö·û***********************/
    0x07, //bLength×Ö¶Î
    0x05, //bDescriptorType×Ö¶Î
    0x81, //bEndpointAddress×Ö¶Î
    0x03, //bmAttributes×Ö¶Î
    0x10, //wMaxPacketSize×Ö¶Î
    0x00,
    0x0A, //bInterval×Ö¶Î
  
    /**********************Êä³ö¶ËµãÃèÊö·û***********************/
    0x07, //bLength×Ö¶Î
    0x05, //bDescriptorType×Ö¶Î
    0x01, //bEndpointAddress×Ö¶Î
    0x03, //bmAttributes×Ö¶Î
    0x10, //wMaxPacketSize×Ö¶Î
    0x00,
    0x0A, //bInterval×Ö¶Î
  
    /*******************µÚ¶þ¸ö½Ó¿ÚÃèÊö·û*********************/
    0x09, //bLength×Ö¶Î
    0x04, //bDescriptorType×Ö¶Î
    0x01, //bInterfaceNumber×Ö¶Î
    0x00, //bAlternateSetting×Ö¶Î
    0x01, //bNumEndpoints×Ö¶Î
    0x03, //bInterfaceClass×Ö¶Î
    0x01, //bInterfaceSubClass×Ö¶Î
    0x02, //bInterfaceProtocol×Ö¶Î
    0x00, //iConfiguration×Ö¶Î
  
    /******************HIDÃèÊö·û************************/
    0x09, //bLength×Ö¶Î
    0x21, //bDescriptorType×Ö¶Î
    0x10, //bcdHID×Ö¶Î
    0x01,
    0x21, //bCountyCode×Ö¶Î
    0x01, //bNumDescriptors×Ö¶Î
    0x22, //bDescriptorType×Ö¶Î
    sizeof(MouseReportDescriptor)&0xFF,  //bDescriptorLength×Ö¶Î
    (sizeof(MouseReportDescriptor)>>8)&0xFF,
  
    /**********************ÊäÈë¶ËµãÃèÊö·û***********************/
    0x07, //bLength×Ö¶Î
    0x05, //bDescriptorType×Ö¶Î
    0x82, //bEndpointAddress×Ö¶Î
    0x03, //bmAttributes×Ö¶Î¡£D1~D0Îª¶Ëµã´«ÊäÀàÐÍÑ¡Ôñ
    0x40, //wMaxPacketSize×Ö¶Î
    0x00,
    0x0A  //bInterval×Ö¶Î
};

u8 code KeyboardReportDescriptor[KP_ReportDescriptor_Size]=
{
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop) //63
    0x09, 0x06,                    //   USAGE (Keyboard)
    0xa1, 0x01,                    //   COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,                    //   REPORT_COUNT (5)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x03,                    //   REPORT_SIZE (3)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          //   END_COLLECTION
//0xc0,
  }; /* Joystick_ReportDescriptor */


u8 code MouseReportDescriptor[Mouse_ReportDescriptor_Size]=
{
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    //   USAGE (Mouse)
    0xa1, 0x01,                    //   COLLECTION (Application)
    0x85, 0x01,                    //   Report ID (1)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //   USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //   REPORT_COUNT (3)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x05,                    //   REPORT_SIZE (5)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //   USAGE (X)
    0x09, 0x31,                    //   USAGE (Y)
    0x09, 0x38,                    //   USAGE (Wheel)
    0x15, 0x81,                    //   LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //   LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x03,                    //   REPORT_COUNT (3)
    0x81, 0x06,                    //   INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0                           //   END_COLLECTION
};

