
#include "ModifyCode.h" 

void set_idle()
{
  	    ucIdleTime = wValueH; //obtain idle time
//  	  	if(ucIdleTime){FlagBit.TimerOnOff=1;count=ucIdleTime;}
 //       else {FlagBit.TimerOnOff=0;FlagBit.TimeOut=0;} 
} 
  
void set_protocol()
{
  	if(wValueL)  ReportProtocol=1;
  	else ReportProtocol=0;
}
  
void get_idle()
{
   Request_buffer[0] = ucIdleTime;  //depend on set_idle
   SendLength=1;
   pSendDescriptor=Request_buffer;
}
  
void get_protocol()
{ 	
  	Request_buffer[0] = ReportProtocol;  //depend on set_protocol
    SendLength=1;
    pSendDescriptor=Request_buffer;
}
void get_report()
{
	uchar8 i;
  	if(wValueL!=FeatureReportID)  bstli0=1;  //wValue---report type & ID
  	else
  	{
	  	 if(wValueH==0x01)     //get (input) report
	  	 {
	  	 	
	  	 }
	  	 else if(wValueH==0x03)  //get feature report
	  	 {
		  	SendLength=wLength;
		  	if(FeatureReportID) {i=1;Request_buffer[0]=FeatureReportID;}
		  	else i=0;
		  	Request_buffer[i]= 0;
		  	Request_buffer[i+1]= !BootloaderFeature;
		  	Request_buffer[i+2]= 0x69;
		  	Request_buffer[i+3]= 0x61;
		  	Request_buffer[i+4]= 0x70;
		  	Request_buffer[i+5]= 0x2d;
		  	Request_buffer[i+6]= 0x68;
		  	Request_buffer[i+7]= 0x77;
		  	if(FlagBit.BootloaderSuccess)  //if jump to bootloader code successfully
		  	{
		//  		Request_buffer[0]= FeatureReportID;
		  		Request_buffer[i]= RptID;
		  		Request_buffer[i+1]= BootloaderFeature;
		  	}
		  	pSendDescriptor=Request_buffer;
	  	 }
	  	 else bstli0=1; 
  	}
}

void set_report()
{
  	if(wValueL!=FeatureReportID)  bstlo0=1;  //wValue---report type & ID
  	else
  	{
  		if(wValueH==0x02)    //set output feature
        {
        	SendLength=wLength;
		  	pSendData=Request_buffer;
		  	FlagBit.Output=1; 
        }
  		else if(wValueH==0x03)  //set_feature
  		{
		  	SendLength=wLength;
		  	pSendData=Request_buffer;
		  	FlagBit.OutFeature=1; 
  		}
  		else bstli0=1;
  	}
}












