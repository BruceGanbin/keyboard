#ifndef __USB_HID_H
#define __USB_HID_H
#include <sh68F83.h>
#include "main.h"

#define DEVICE_DESCRIPTOR_SIZE                  18
#define CONFIGURATION_DESCRIPTOR_SIZE           34
#define JOYSTICK_SIZ_CONFIG_DESC                66
#define KBD_REPORTDESCRIPTOR_SIZE               63
#define MOUSE_REPORTDESCRIPTS_SIZE              54
#define KBD_OFF_HID_DESC                        18
#define Mouse_OFF_HID_DESC                      50
#define LANGUAGE_ID_SIZE                        4
#define MANUFACTUREER_SIZE                      20
#define PRODUCT_SIZE                            20
#define SERIAL_NUM_SIZE                         20



extern u8 code DeviceDescriptor[DEVICE_DESCRIPTOR_SIZE];
extern u8 code ConfigurationDescriptor[CONFIGURATION_DESCRIPTOR_SIZE];
extern u8 code Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC];
extern u8 code KeyboardReportDescriptor[KBD_REPORTDESCRIPTOR_SIZE];
extern u8 code MouseReportDescriptor[MOUSE_REPORTDESCRIPTS_SIZE];

extern u8 code LanguageId[1];//[LANGUAGE_ID_SIZE];
extern u8 code ManufacturerStringDescriptor[1];//[MANUFACTUREER_SIZE];
extern u8 code ProductStringDescriptor[1];//[PRODUCT_SIZE];
extern u8 code SerialNumberStringDescriptor[1];//[SERIAL_NUM_SIZE];

#endif


