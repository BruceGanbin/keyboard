
#include "ModifyCode.h" 

extern   void   ModifyGetHaltStatus(); 
extern   void   ModifySetFeature();
extern   void   ModifyClearFeature();

void gt_string()
 {
 	if(!wValueL)   //send LanguageID
 	{
 		if(wIndexH || wIndexL) bstli0=1;   //wIndex should be 0
 		else  
 		{
	 		SendLength=LanguageID[0];
	 		pSendDescriptor=LanguageID;
 		}
 	}
 	else if(!wIndexH && !wIndexL &&(wValueL==0xee)&&_SelectiveSuspend) //send OSString,for selective suspend
 	{		
 		SendLength=OSString[0];
		pSendDescriptor=OSString;
		FlagBit.OSString=1; 
	}
 	else 
 	{
 	    if(wIndexH!=LanguageID[3] || wIndexL!=LanguageID[2]) bstli0=1;   //wIndex should be LanguageID	           
 	    else if((wIndexH==LanguageID[3])&&(wIndexL==LanguageID[2])) 
 	    switch(wValueL)
 	    {
	 		case 1:                         //DeviceDescriptor[14],manufacturer index
	 		SendLength=ManuString[0];
	 		pSendDescriptor=ManuString;    	break;	
	 		case 2:                         //DeviceDescriptor[15],product index  
	 		SendLength=ProString[0];
	 		pSendDescriptor=ProString;        break;
	//		case DeviceDescriptor[16]:      //serial number index
	//		SendLength=SerialString[0];
	//		pSendDescriptor=SerialString;break;
	 		default: bstli0=1;         break; //not defined index number
 	    }
 	}
 }
 
void get_OSFeature()  //OSFeature index=5
  {
  	if(FlagBit.OSString==0||wValueL||wValueH||wIndexH||(wIndexL!=0x05)||!_SelectiveSuspend) bstli0=1;
  	else
  	{
  	SendLength=OSFeatureDescriptor[0];
  	pSendDescriptor=OSFeatureDescriptor;
  	}
  } 
  
void get_descriptor()             
  {	
	if(wValueH==0x21)   //HID descriptor
	{
		if(!wIndexL)    //interface 0
		{
			SendLength=ConDesCollection[18];         
            pSendDescriptor=&ConDesCollection[18];
		}
		else if(wIndexL==1)  //interface 1
		{
			SendLength=ConDesCollection[43];         
            pSendDescriptor=&ConDesCollection[43];
		}
	}
    else if(wValueH==0x22)   //report descriptor
    {
		if(!wIndexL)  //interface 0 
		{
			SendLength=ReportLengthH0;
            SendLength=(ReportLengthH0<<8)|ReportLengthL0;
            pSendDescriptor=KeyboardReptDesc; 
		}
		else if(wIndexL==1) //interface 1
		{
			SendLength=ReportLengthH1;
            SendLength=(ReportLengthH1<<8)|ReportLengthL1;
            pSendDescriptor=HotkeyReptDesc;
		}
    } 	
  	else 
  	{
  	if(wValueH!=3 && (wIndexH || wIndexL) ) bstli0=1;
 	switch(wValueH)   //LSB:Index number ,HSB:type number
 	{
 		case 1: SendLength=DeviceDescriptor[0];
	            pSendDescriptor=DeviceDescriptor;          break;   //device descriptor		
 		case 2: SendLength=ConDesCollection[3];
 		        SendLength=(SendLength<<8)|ConDesCollection[2];
 	            pSendDescriptor=ConDesCollection;          break;   //configuration descriptor
 		case 3: gt_string();                               break;   //string descriptor
 		default:     bstli0=1;             break;    //other descriptor
 	}
  	}
  } 

void set_address()
 {
 	if( wValueH ||(wValueL>127)|| wIndexH || wIndexL || wLength ) bstlo0=1;
 	else
 	{
	    baset=1;             
	    Bawr=wValueL<<1;  //set device address 
	    ucUSBState=STATE_ADDR;  //address state
 	}
 }
 
void get_status()
  {
  	if(wValueH || wValueL ||wIndexH) bstli0=1;  
  	switch(bmRequestType&0x0f)
  	{
  		case 0: Request_buffer[0]=(Bawr<<1)&0x02; break;//request object:device
  		case 1: Request_buffer[0]=0;              break;//request object:interface
// 		case 2: Request_buffer[0]=stl0flag;   break;
        case 2: ModifyGetHaltStatus(); break; //Halt bit,request object:endpoint
  		default:bstli0=1;    
  	}
  	Request_buffer[1]=0;
  	SendLength=2;
  	pSendDescriptor=Request_buffer;
  }
  
void set_configuration()
  {
  	bdatatg=1; 	 	
  	if(wValueL>1||wIndexH||wIndexL||wLength) bstlo0=1;
  	else if(wValueL)  ucUSBState=STATE_CONFIG;  //configuration state
  	else if(!wValueL) ucUSBState=STATE_ADDR;
  }
  
void get_configuration()
  {
  	 if(ucUSBState==STATE_CONFIG) 
        Request_buffer[0] = 1;  
     else if(ucUSBState==STATE_ADDR) 
        Request_buffer[0] = 0;
     SendLength=1;
     pSendDescriptor=Request_buffer;
  }










