#ifndef __USBCORE_H
#define __USBCORE_H
#include <sh68F83.h>


// USB Feature Contorl
#define PULL_UP                0x80// USB D- pad 1.5k ohm pull-up resisor
#define USB_CON                0x40// Enable USB Mode or GPIO mode
#define FW_K                   0x20// FW start to issue K-start 
#define RSU_SEL                0x10// Disable RESUME by issuing K-start
#define USB_EN                 0x08// Enable USB functons 
#define ERW_UP                 0x02// Enable remote wake-up
#define VPCON                  0x01// USB pseudo plug-off
// IE2 Register
#define IE_ESTUP               0x01
#define IE_EOWSTUP             0x02
#define IE_EOT0ERR             0x04
#define IE_EIN0                0x08
#define IE_EOUT0               0x10
#define IE_ESIE                0x20
#define IE_EFUN                0x40
// IRQEN
#define IRQE_ENAKT0            0x01
#define IRQE_ENAKR0            0x02
#define IRQE_ENAK1             0x04
#define IRQE_ENAK2             0x08
#define IRQE_ET0STL            0x10
#define IRQE_ER0STL            0x20
#define IRQE_EIN1              0x40
#define IRQE_EIN2              0x80
// IF2
#define IF_STUP                0x01
#define IF_OWSTUP              0x02
#define IF_OT0ERR              0x04
#define IF_IN0                 0x08
#define IF_OUT0                0x10
#define IF_SIE                 0x20
#define IF_FUN                 0x40
// IRQFG
#define IRQF_NAKT0             0x01
#define IRQF_NAKR0             0x02
#define IRQF_NAK1              0x04
#define IRQF_NAK2              0x08
#define IRQF_T0STL             0x10
#define IRQF_R0STL             0x20
#define IRQF_IN1               0x40
#define IRQF_IN2               0x80


//SETUP token                 
#define GET_STATUS             0
#define CLEAR_FEATURE          1
#define SET_FEATURE            3
#define SET_ADDRESS            5
#define GET_DESCRIPTOR         6
#define SET_DESCRIPTOR         7
#define GET_CONFIGURATION      8
#define SET_CONFIGURATION      9
#define GET_INTERFACE          10
#define SET_INTERFACE          11
#define SYNCH_FRAME            12

#define DEVICE_DESCRIPTOR         1
#define CONFIGURATION_DESCRIPTOR  2
#define STRING_DESCRIPTOR         3
#define INTERFACE_DESCRIPTOR      4
#define ENDPOINT_DESCRIPTOR       5

#define USB_BUF_LEN            8
#define EP0_RD_LEN             18

void UsbEp0Out(void);
void UsbEp0In(void);
void UsbEp1In(void);
void UsbEp2In(void);

void usbinit(void);
void UsbHandler(void);
void UsbSetup(void);

#endif

