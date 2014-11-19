
#include "Enumerate_data.h"

void UsbEpSendData(uchar8 Enpoint,uchar8 MaxPackage)
 {		
	 	if(SendLength>MaxPackage)
	 	{
            ReadWriteFIFO(Enpoint,MaxPackage);
	 		if(FlagBit.ReadWrite_complete)
	 		{
//	 		    FlagBit.ReadWrite_complete=0;			 	
		 		SendLength-=MaxPackage;
		 		pSendData+=MaxPackage;
		 		if(FlagBit.GetEp0Data) pSendDescriptor+=MaxPackage;
	 		}
	 	}
	 	else if(SendLength!=0)
	 	{
            ReadWriteFIFO(Enpoint,SendLength);
	 		if(FlagBit.ReadWrite_complete)
	 		{
//		 		FlagBit.ReadWrite_complete=0;
                FlagBit.GetEp0Data=0;
		 		SendLength=0;
	 		}
	 	}
 	    else if(FlagBit.NeedZeroPacket==1) 
 	    {
 	    	FlagBit.NeedZeroPacket=0;
 	    	ReadWriteFIFO(Enpoint,0);
 	    }
 	    FlagBit.ReadWrite_complete=0;
 }  
void ProcesRecivData()    //analyze setup token 
 {
	   bmRequestType=Request_buffer[0];
	   bRequest=Request_buffer[1];	   
	   wValueL=Request_buffer[2];
	   wValueH=Request_buffer[3];
	   wIndexL=Request_buffer[4];
	   wIndexH=Request_buffer[5];
	   wLength=Request_buffer[7];
	      wLength=(wLength<<8)|Request_buffer[6];
     
      if((bmRequestType&0x80)==0x80)     //input request
      {
      	FlagBit.GetEp0Data=1;
    	switch(bmRequestType&0x60) //D6~5 bits present for request type
    	{
    		case 0:                              //standard request
    		switch(bRequest)
    		{
    			case 8:   get_configuration();   break;     //GET_CONFIGURATION
    			case 6:   get_descriptor();      break;     //GET_DESCRIPTOR
    		//	case 10:  GET_INTERFACE();       break;     //
    			case 0:   get_status();          break;     //GET_STATUS
    		//	case 12:  SYNCH_FRAME();         break;     //
    			default:  bstli0=1;              break;     //un-support
    		}break;    		
    		case 0x20:                              //class request
    		switch(bRequest)
    		{
    			case 1:  get_report();           break;
    			case 2:  get_idle();             break;
    			case 3:  get_protocol();         break;
    			default: bstli0=1;               break;
    		}break;
    	    case 0x40:                           //vendor request 
    		switch(bRequest)
    		{
    			case VendorDefined:  get_OSFeature();    break;//VendorDefined
    			default: bstli0=1;
    		}break;	
    	    default:     bstli0=1;               break;   		
    	}
      }
      else                              //output request
      {
        switch(bmRequestType&0x60) //D6~5 bits present for request type
    	{
    		
    		case 0:                             //standard request
    		switch(bRequest)
    		{
    			case 1: clear_feature();        break; //clear feature
    			case 5: set_address();          break; //Set address
    			case 9: set_configuration();    break; //set configuration
    		//	case 7: set descriptor();       break; //
    			case 3: set_feature();          break; //set feature 
    		//	case 11: set interface();       break; //
    			default: bstli0=1;             break; //un-support
    		}break;    		   		
    		case 0x20:                            //Class request
    		switch(bRequest)
    		{
    			case 9:    set_report();       break;
    			case 10:   set_idle();         break;
    			case 11:   set_protocol();     break;
    			default:   bstlo0=1;          break;
    		}break;   
    	    default: bstlo0=1;                break;   		 		
    	}
    	if(!bstlo0) FlagBit.NeedZeroPacket=1;	
      }
 }
void AccessFIFO0()
 {
 	bep0f=0;
 	if(bsetcmd)         //setup token
 	  {
// 	  	FlagBit.SetupToken=1;  //indicate the IN token is for setup or normal used
 	  	pSendData=Request_buffer;
 	  	FlagBit.tx=0;          //read FIFO
 		ReadWriteFIFO(0,8);    //read request
 		if(FlagBit.ReadWrite_complete) 
 		{
 			FlagBit.ReadWrite_complete=0;
 			ProcesRecivData();
 		}
 	  }
 	else //in token and out token
 	  {
 	    if(wLength>SendLength)   //need length bigger than actual data length
		 {
			if(SendLength%Ep0MaxPackage==0) FlagBit.NeedZeroPacket=1;
		 }
		else SendLength=wLength;
		
		if(bin)
		{
			FlagBit.tx=1;
			UsbEpSendData(0,Ep0MaxPackage);
		}
		else if(FlagBit.Output)
		{
			FlagBit.tx=0;
			UsbEpSendData(0,Ep0MaxPackage);
			if(!SendLength)
			{
				FlagBit.Output=0;
				if(Request_buffer[0]&0x01) KeyFlag.NumLockStatus=1;
				else KeyFlag.NumLockStatus=0;
				if(Request_buffer[0]&0x02) KeyFlag.CapsLockStatus=1;
				else KeyFlag.CapsLockStatus=0;   
				if(Request_buffer[0]&0x04) KeyFlag.ScrollLockStatus=1;
				else KeyFlag.ScrollLockStatus=0;  
			}	
		} 
		else if(FlagBit.OutFeature)
		{
			FlagBit.tx=0;
			UsbEpSendData(0,Ep0MaxPackage);
			if(!SendLength)
			{
				FlagBit.OutFeature=0;
				if(FeatureReportID==0)
				{
					if(Request_buffer[0]==RptID 
					&& Request_buffer[1]==BootloaderFeature)
				    FlagBit.ToBootloader=1;
				}
				else if(Request_buffer[0]==FeatureReportID  
				     && Request_buffer[1]==RptID  
				     && Request_buffer[2]==BootloaderFeature)
		    	FlagBit.ToBootloader=1;
			}	
		} 
 	  }
 }







