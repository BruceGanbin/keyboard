
#ifndef   _MODIFYCODE_H
#define   _MODIFYCODE_H

#include  "Variable.h"

asm("extern ENABLE_BL:near");   //extern funtion         
asm("extern B_ENABLE_BL_OK : bit");  

#define      NumLockC              _pdc2
#define      NumLock               _pd2
#define      CapsLockC             _pdc3
#define      CapsLock              _pd3
#define      ScrollLockC           _pdc4
#define      ScrollLock            _pd4

#define      ReportLengthL0        81
#define      ReportLengthH0        0x00    
#define      EpNumber0             0x01//0x01//  //for interface 0
#define      ReportLengthL1        127//137
#define      ReportLengthH1        0x00
#define      EpNumber1             0x01          //for interface 1

#define      Ep0MaxPackage         0x08
#define      Ep1MaxPackage         0x08
#define      Ep2MaxPackage         0x08
//#define      Ep3MaxPackage         0x08

#define      Ep1BuffSize           8
//#define      Ep2BuffSize           4
//#define      Ep3BuffSize           4

#define      VendorDefined         0x04      //for selective suspend
#define      _SelectiveSuspend     1           //enable selective suspend

#define      FeatureReportID       0x00//0x00//      //set feature report,get feature report  
#define      RptID                 0x06
#define      BootloaderFeature     0x01    



#endif
