#ifndef __USB_HID_H
#define __USB_HID_H
#include <sh68F83.h>

#define DEVICE_DESCRIPTOR_SIZE                  18
#define CONFIGURATION_DESCRIPTOR_SIZE           34
#define JOYSTICK_SIZ_CONFIG_DESC                66
#define KBD_REPORTDESCRIPTOR_SIZE               63
#define MOUSE_REPORTDESCRIPTS_SIZE              54
#define KBD_OFF_HID_DESC                        18
#define Mouse_OFF_HID_DESC                      50

extern u8 DeviceDescriptor[DEVICE_DESCRIPTOR_SIZE];
extern u8 ConfigurationDescriptor[CONFIGURATION_DESCRIPTOR_SIZE];
extern u8 Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC];
extern u8 KeyboardReportDescriptor[KBD_REPORTDESCRIPTOR_SIZE];
extern u8 MouseReportDescriptor[MOUSE_REPORTDESCRIPTS_SIZE];

#endif


