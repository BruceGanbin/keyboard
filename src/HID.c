#include "HID.h"
#include "c51type.h"
#include <intrins.h>

u8 code DeviceDescriptor[0x12]=  
{
    0x12,//bLength
    0x01,//bDescriptorType
    //bcdUSB
    0x10,
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

U8 code ConfigurationDescriptor[9+9+9+7]=
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
    sizeof(ReportDescriptor)&0xFF,
    (sizeof(ReportDescriptor)>>8)&0xFF,
    
    0x07,//bLength
    0x05,//bDescriptorType
    0x81,//bEndpointAddress
    0x03,//bmAttributes
    0x10,//wMaxPacketSize
    0x00,
    0x0A//bInterval
};

char Ep0ReceiveData[8];
char Ep0SendData[8];
char Ep1SendData[8];
char Ep2SendData[8];
unsigned char Ep0_rxcnt=0;
unsigned char Ep0_txcnt=0;
unsigned char Ep1_txcnt=0;
unsigned char Ep2_txcnt=0;


static void UsbEp0ReceiveData(void)
{
    u8 T0_FULL;
    u8 reg_flg;
    u8 i = 0;
    reg_flg = RXFLG0 ;
    T0_FULL = reg_flg & 0x01;
    Ep0_rxcnt = RXCNT0;
    if(T0_FULL)
    {
        for(i=0;i<Ep0_rxcnt;i++)
        {
            Ep0ReceiveData[i] = RXDAT0;
        }
        TXFLG0 = reg_flg & 0xFE;  // set Full = 0; Read data
    }
}

static void UsbEp0SendData(void)
{
    u8 T0_FULL;
    u8 reg_flg;
    u8 i = 0;
    reg_flg = TXFLG0 ;
    T0_FULL = reg_flg & 0x01;
    if(!T0_FULL)
    {

        TXDAT0 = Ep0SendData;
        TXCNT0 = Ep0_rxcnt;
        TXFLG0 = reg_flg | 0x01;  // set Full = 1;
    }
}

static void UsbEp0SendData(void)
{
    u8 T1_FULL;
    u8 reg_flg;
    u8 i = 0;
    reg_flg = TXFLG1;
    T1_FULL = reg_flg & 0x01;
    if(!T1_FULL)
    {

        TXDAT1 = Ep1SendData;
        TXCNT1 = Ep1_rxcnt;
        TXFLG1 = reg_flg | 0x01;  // set Full = 1;
    }
}

static void UsbEp0SendData(void)
{
    u8 T2_FULL;
    u8 reg_flg;
    u8 i = 0;
    reg_flg = TXFLG2;
    T2_FULL = reg_flg & 0x01;
    if(!T2_FULL)
    {

        TXDAT2 = Ep2SendData;
		TXCNT2 = Ep2_rxcnt;
		TXFLG2 = reg_flg | 0x01;  // set Full = 1;
    }
}

//  
static void UsbEp0Out(void)
{
	OEP0RDY = 1;
}

static void UsbEp0In(void)
{
	UsbEp0SendData();	
}

static void UsbEp1Out(void)
{
	
}

static void UsbEp1In(void)
{

}

static void UsbEp2Out(void)
{

}

static void UsbEp2In(void)
{

}

//
void UsbHandler(void)
{
	SETBANK0;
	RSET_WATCHDOG;
	SETBANK1;
	if(PUPIF){PUPIF = 0;UsbPulg();}
	if(USBRSTIF){USBRSTIF = 0;UsbBusReset();}
	if(SETUPIF){SETUPIF = 0;UsbSetup();}
    
	if(IEP0IF){IEP0IF = 0;UsbEp0In();}
	if(OEP0IF){OEP0IF = 0;UsbEp0Out();}
    //	if(IEP1IF){IEP1IF = 0;UsbEp1In();}
	if(OEP1IF){OEP1IF = 0;UsbEp1Out();}
    //	if(IEP2IF){IEP2IF = 0;UsbEp2In();}
	if(OEP2IF){OEP2IF = 0;UsbEp2Out();}
	if(SUSPIF){SUSPIF = 0;UsbBusSuspend();}
}

void usbinit(void)
{
    DFC = PULL_UP | USB_CON | USB_EN | VPCON | FW_K ;
}

