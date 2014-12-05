#ifndef __HID_H
#define __HID_H
#include <sh68F83.h>


// USB Feature Contorl
#define PULL_UP           0x80// USB D- pad 1.5k ohm pull-up resisor
#define USB_CON           0x40// Enable USB Mode or GPIO mode
#define FW_K              0x20// FW start to issue K-start 
#define RSU_SEL           0x10// Disable RESUME by issuing K-start
#define USB_EN            0x08// Enable USB functons 
#define ERW_UP            0x02// Enable remote wake-up
#define VPCON             0x01// USB pseudo plug-off

#define USB_BUF_LEN          8

void usbinit(void);
void UsbHandler(void);

#endif

