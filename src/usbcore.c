#include "HID.h"
#include "usbcore.h"
#include "c51type.h"
#include <intrins.h>

u8	bmRequestType;
u8	bRequest;
u16 wValue;
u16 wIndex;
u16 wLength;

u8 *pEp0ReadData;
u8 *pEp0SendData;
u8 *pEp1SendData;
u8 *pEp2SendData;
u8 Ep0_rxcnt=0;
u16 Ep0SendLen=0;
u16 Ep1SendLen=0;
u16 Ep2SendLen=0;
u8 Ep0ReadData[EP0_RD_LEN];
u8 Get_DevRiptor_st;

/****************************************
Tx FIFO length is 8 bytes
TX Operating Model:
        set TxFULL = 0
        Firmware Process
      Set TXDATx = TX data 
     set TXCNTx = bytes count 
         set TxFULL = 1
****************************************/
void Ep0SendData(void)
{    
    u8 T0_FULL;
    u8 reg_flg;
    
    reg_flg = TXFLG0 ;
    T0_FULL = reg_flg & 0x01;
    if(!T0_FULL)
    {
        if(Ep0SendLen > DeviceDescriptor[7])
        {
            // send data
            TXDAT0 = pEp0SendData;
            TXCNT0 = DeviceDescriptor[7];
            TXFLG0 = reg_flg | 0x01;  // set Full = 1;
                
            Ep0SendLen -= DeviceDescriptor[7];
            pEp0SendData += DeviceDescriptor[7];
        }
        else
        {
            if(Ep0SendLen != 0)
            {
                // send data
                TXDAT0 = pEp0SendData;
                TXCNT0 = Ep0SendLen;
                TXFLG0 = reg_flg | 0x01;  // set Full = 1;

                Ep0SendLen = 0;
            }
            else
            {
                TXCNT0 = 0;
                TXFLG0 = reg_flg | 0x01;  // set Full = 1;
            }
        }
    }
}


static void Ep1SendData(void)
{
    u8 T1_FULL;
    u8 reg_flg;
    
    reg_flg = TXFLG1;
    T1_FULL = reg_flg & 0x01;
    if(!T1_FULL)
    {
        if(Ep1SendLen > DeviceDescriptor[7])
        {
            // send data
            TXDAT1 = pEp1SendData;
            TXCNT1 = DeviceDescriptor[7];
            TXFLG1 = reg_flg | 0x01;  // set Full = 1;
                
            Ep1SendLen -= DeviceDescriptor[7];
            pEp1SendData += DeviceDescriptor[7];
        }
        else
        {
            if(Ep1SendLen != 0)
            {
                // send data
                TXDAT1 = pEp1SendData;
				TXCNT1 = Ep1SendLen;
				TXFLG1 = reg_flg | 0x01;  // set Full = 1;

                Ep1SendLen = 0;
            }
            else
            {
                TXCNT1 = 0;
				TXFLG1 = reg_flg | 0x01;  // set Full = 1;
            }
        }
    }
}

static void Ep2SendData(void)
{
    u8 T2_FULL;
    u8 reg_flg;
    
    reg_flg = TXFLG2;
    T2_FULL = reg_flg & 0x01;
    if(!T2_FULL)
    {
        if(Ep2SendLen > DeviceDescriptor[7])
        {
            // send data
            TXDAT2 = pEp2SendData;
			TXCNT2 = DeviceDescriptor[7];
			TXFLG2 = reg_flg | 0x01;  // set Full = 1;
                
            Ep2SendLen -= DeviceDescriptor[7];
            pEp2SendData += DeviceDescriptor[7];
        }
        else
        {
            if(Ep2SendLen != 0)
            {
                // send data
                TXDAT2 = pEp2SendData;
				TXCNT2 = Ep2SendLen;
				TXFLG2 = reg_flg | 0x01;  // set Full = 1;

                Ep2SendLen = 0;
            }
            else
            {
                TXCNT2 = 0;
				TXFLG2 = reg_flg | 0x01;  // set Full = 1;
            }
        }
    }
}

static void UsbEp0ReceiveData(void)
{
    u8 T0_FULL;
    u8 reg_flg;
    u8 i = 0;
    reg_flg = RXFLG0 ;
    T0_FULL = reg_flg & 0x01;
    if(T0_FULL)
    {
        Ep0_rxcnt = RXCNT0;

        pEp0ReadData += Ep0_rxcnt;
        if((pEp0ReadData - Ep0ReadData) > EP0_RD_LEN)
        {
            pEp0ReadData = Ep0ReadData;
        }
        RXDAT0 = pEp0ReadData;
        TXFLG0 = reg_flg & 0xFE;  // set Full = 0; Read data
    }
}

static void UsbEp0SendData(u8 *pSendData,u16 len)
{
    pEp0SendData = pSendData;
    Ep0SendLen = len;
    Ep0SendData();
}

static void UsbEp1SendData(u8 *pSendData,u16 len)
{
    pEp1SendData = pSendData;
    Ep1SendLen = len;
    Ep1SendData();
}

static void UsbEp2SendData(u8 *pSendData,u16 len)
{
    pEp2SendData = pSendData;
    Ep2SendLen = len;
    Ep2SendData();
}

//  
void Usbep0out(void)
{
    UsbEp0ReceiveData();
}

void UsbEp0In(void)
{
    Ep0SendData();
}

void UsbEp1In(void)
{
	Ep1SendData();
}

void UsbEp2In(void)
{
	Ep2SendData();
}

static void usbget_descriptor(u16 wValue,u16 wIndex,u16 wLength)
{
    u8 descRiptr;
    u16 SendLen = 0;
    u8 pSendData;

    descRiptr = (wValue >> 8) & 0xFF;
    switch(descRiptr)
    {
    case DEVICE_DESCRIPTOR:

        pSendData = DeviceDescriptor;

        if(Get_DevRiptor_st == 0)
        {
            Get_DevRiptor_st = 1;
            SendLen = 8;
        }
        else
        {
            if(wLength > DeviceDescriptor[0])
            {
                SendLen = DeviceDescriptor[0];
                
            }
            else
            {
                SendLen = wLength;
            }
        }
        UsbEp0SendData(pSendData,SendLen);
        break;
        
    case CONFIGURATION_DESCRIPTOR:

        pSendData = ConfigurationDescriptor;
        SendLen = ConfigurationDescriptor[3]<<8;
        SendLen |= ConfigurationDescriptor[2];

        UsbEp0SendData(pSendData,SendLen);
        break;
        
    case STRING_DESCRIPTOR:
        break;
    case INTERFACE_DESCRIPTOR:
        break;
    case ENDPOINT_DESCRIPTORE:
        break;
        //  HID Request
        
    default:
        break;
    }
}


void UsbSetup(void)
{
    u8 usbaddress = 0;
    u8 temp = 0;
    u8 bmRequestType;
    u8 bRequest;
    u16 wValue;
    u16 wIndex;
    u16 wLength;
    
	bmRequestType = Ep0ReadData[0];
	bRequest = Ep0ReadData[1];
	wValue = Ep0ReadData[2] + (((u16)Ep0ReadData[3])<<8);
	wIndex = Ep0ReadData[4] + (((u16)Ep0ReadData[5])<<8);
	wLength = Ep0ReadData[6] + (((u16)Ep0ReadData[7])<<8);

    if((bmRequestType & 0x80) == 0x80)// master <= device
    {
        switch((bmRequestType>>5)&0x03)
        {
        case 0:
            switch(bRequest)
                {
                case GET_CONFIGURATION:
                    break;
                    
                case GET_DESCRIPTOR:
                    usbget_descriptor(wValue,wIndex,wLength);
                    break;
                    
                case GET_INTERFACE:
                    break;
                case GET_STATUS:
                    break;
                case SYNCH_FRAME:
                    break;
                }
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }
    }
    else  // master => device
    {
        switch((bmRequestType>>5)&0x03)
        {
        case 0:
            switch(bRequest)
                {
                case CLEAR_FEATURE:
                    break;
                case SET_ADDRESS:
                    usbaddress = wValue 0xEF;
                    temp = 0 ;
                    UsbEp0SendData(&temp,0);
                    DADDR = usbaddress;
                    break;
                case SET_CONFIGURATION:
                    break;
                case SET_DESCRIPTOR:
                    break;
                case SET_FEATURE:
                    break;
                case SET_INTERFACE:
                    break;
                default:
                    break;
                }
            break;
    }
        
    // reset Ep0 Rx FIFO point 
    pEp0ReadData = Ep0ReadData;
    RXDAT0 = pEp0ReadData;
}

//
void UsbHandler(void)
{
    u8 usb_token;

    usb_token = IRQFG;
	if(USBRSTIF){USBRSTIF = 0;UsbBusReset();}
    //	if(SETUPIF){SETUPIF = 0;UsbSetup();}
    
   	if(usb_token & IRQF_IN1)
    {
        UsbEp1In();
        usb_token &= (~IRQF_IN1);
        IRQFG = usb_token;
    }
    if(usb_token & IRQF_IN2)
    {
        UsbEp2In();
        usb_token &= (~IRQF_IN2);
        IRQFG = usb_token;
    }
    //	if(SUSPIF){SUSPIF = 0;UsbBusSuspend();}
}

void usbinit(void)
{
    DFC = PULL_UP | USB_CON | USB_EN | VPCON | FW_K ;
    IE2 = IE_EIN0 | IE_EOUT0 | IE_ESIE ;
    IRQEN = IRQE_EIN1 | IRQE_EIN2 ;
    Get_DevRiptor_st = 0;
}



