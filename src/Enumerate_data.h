
#ifndef  _ENUMERATE_DATA_H
#define  _ENUMERATE_DATA_H

#include "ModifyCode.h" 

extern    void     ReadWriteFIFO(uchar8 endpoint,uchar8 length);
//extern    void     Ep0NormalUsed();

extern    void     get_configuration(); 
extern    void     get_descriptor();
extern    void     get_status();
extern    void     get_report(); 
extern    void     get_idle(); 
extern    void     get_protocol(); 

extern    void     clear_feature();
extern    void     set_address(); 
extern    void     set_configuration();
extern    void     set_feature();
extern    void     set_idle(); 
extern    void     set_protocol();
extern    void     set_report();

extern    void     get_OSFeature();

#endif





