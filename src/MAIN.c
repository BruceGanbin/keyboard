
#include "ModifyCode.h"

extern    void       sys_initial();
extern    void       timer2_initial();
extern    void       usb_initial();
extern    void       UserToBootloader();
extern    void       suspend_wakeup(); 
extern    void       MKYSCN();
extern    void       UsbEpSendData(uchar8 Enpoint,uchar8 EpMaxPackage);
extern    void       AccessFIFO0();


void Ep1SendData(volatile uchar8 *p)
{
		if(!SendLength) 
	 	{
	 		FlagBit.Ep1Busy=1;
	 		SendLength=Ep1BuffSize; 
	 		pSendData=p;
	 	}	
	 	FlagBit.tx=1;      //input endpoint
	 	UsbEpSendData(1,Ep1MaxPackage);
	 	if(!SendLength)	FlagBit.Ep1Busy=0;
}
void Ep2SendData(volatile uchar8 *p)
{
		if(!SendLength) 
	 	{
	 		FlagBit.Ep2Busy=1;
	 		SendLength=Ep2BuffSize; 
	 		pSendData=p;
	 	}	
	 	FlagBit.tx=1;      //input endpoint
	 	UsbEpSendData(2,Ep2MaxPackage);
	 	if(!SendLength)	FlagBit.Ep2Busy=0;	
}
void AccessFIFO1()   //endpoint1 for input
{	 		
// 	char Ep1_Buff[Ep1BuffSize]={0};      //data for sent to host       	
 	uchar8 i;
 	uint16 temp;
 	bep1f=0;
	if(KeyFlag.KB_KeyUpt && ucUSBState==STATE_CONFIG && !FlagBit.Ep2Busy)
 //    if(0)
 	{
 		if(KeyFlag.FPHONK||KeyFlag.buffull)
 		{
 			for(i=2;i<8;i++)
 			fifo_out[i]=0x01;
 		}
 		else if(KeyFlag.combinekey)
 		{
 			temp=macro_key_matrix[(int_temp1<<2)+comkeys];
            key_byte[4]=0x01;       //default:ctrl+
		    fifo_out[2]=temp&0xff;
		    if(++comkeys==4)
		    {	
		    	key_byte[4]=0x00;	    	
	        	comkeys=0;
	        	KeyFlag.combinekey=0;
	        	KeyFlag.KB_KeyUpt=0;
		    }		    
 		}	 		
 		else 
 		{			
			for(i=0;i<Buff_Index;i++)
 			fifo_out[i+2]=key_code_buff[i];
 			for(i=Buff_Index;i<KEY_BUF_END;i++)
            fifo_out[i+2]=0;
 		}	
 		fifo_out[0]=key_byte[4];
 	    fifo_out[1]=0x00;
        Ep1SendData(fifo_out); 
 		if(!SendLength && !KeyFlag.combinekey)	KeyFlag.KB_KeyUpt=0;
 	}
}

void AccessFIFO2()   //endpoint3 for input
{	 
// 	char Ep2_Buff[Ep2BuffSize]={0};      //data for sent to host     	
// 	uchar8 i;
 	bep2f=0;
	if(ucUSBState==STATE_CONFIG && !FlagBit.Ep1Busy)
  //	if(0)
 	{
        if(KeyFlag.multi_key_chg)
        {
        	KeyFlag.multi_key_chg=0;
        	Ep2BuffSize=4;
        	fifo_out[0]=3;
//        	for(i=0;i<3;i++)
//        	fifo_out[i+1]=key_byte[i];
            fifo_out[1]=key_byte[0];
            fifo_out[2]=key_byte[1];
            fifo_out[3]=key_byte[2];
            Ep2SendData(fifo_out);
        }
        else if(KeyFlag.acpi_key_chg)  
        {   
//        	if(KeyFlag.wakeupbreak)
//        	{
//        		KeyFlag.wakeupbreak=0;
//        		key_byte[3]&=0xfb;
//        	}     	
//        	if(KeyFlag.wakeup)
//        	{
//        		KeyFlag.wakeup=0;
//        		key_byte[3]|=0x04;
//        		KeyFlag.wakeupbreak=1;
//        	}
//        	else 
        	KeyFlag.acpi_key_chg=0;
        	Ep2BuffSize=2;
        	fifo_out[0]=1;
            fifo_out[1]=key_byte[3];
            Ep2SendData(fifo_out);
        }
        else if(KeyFlag.hot_key_chg)
        {
        	KeyFlag.hot_key_chg=0;
        	Ep2BuffSize=2;
        	fifo_out[0]=2;
            fifo_out[1]=key_byte[5];
            Ep2SendData(fifo_out);
        }				
 	}
}
void main()
{ 
	uchar8 shift,i;
//	GCC_CLRWDT();
    sys_initial();
    timer2_initial();
    usb_initial();   
//    KeyFlagByte=0;
		
 	for(i=0x80;i<0xff;i++)
	{
		_mp1=i;
		_bp=0x00;
		_iar1=0;   //initial RAM0
		_bp=0x01;
		_iar1=0;   //initial RAM1
		if(i==0)i=_mp1;
	} 
	for(i=0xa0;i<0xb2;i++)
	{
		_mp1=i;
		_iar1=0xff;    //GOLDKY[]=0xff; 
		if(i==0xff)i=_mp1;
	} 
	_bp=0x00;	
	_mp0=0xff;
	_iar0=0;    	
	
	KeyFlag.Fn_mode=1;  //default:Fn break
	
	KeyFlag.KB_KeyUpt=1;
	KeyFlag.multi_key_chg=1;
	KeyFlag.acpi_key_chg=1;
	KeyFlag.hot_key_chg=1;  //PC initial key buffer
	
	IO_address[0]=&_pcc;
	IO_address[1]=&_pc;    //_pc,scan in address
    IO_address[2]=&_pbc;
	IO_address[3]=&_pb;  
	IO_address[4]=&_pac;
	IO_address[5]=&_pa;	
	IO_address[6]=&_pdc;
	IO_address[7]=&_pd;	
	
//    scanlineno=0;
    bt2on=1;
	_emi=1;   	
	while(1)  
	{
	if(FlagBit.TimeOut)
	{
	FlagBit.TimeOut=0;	
	busbe=0; 	
	MKYSCN();
	busbe=1;
	} 
//	if(KeyFlag.chk_key_change) chk_key_change();
	if(FlagBit.ToBootloader)   UserToBootloader();
	if(bsusp)  suspend_wakeup();  //GCC_CLRWDT();
	}
}

void __attribute((interrupt(0x0c))) USB_ISR()
{
	busbcken=1;
	if(bsusp)
	{
		bep0f=0;
		bep1f=0;
		bep2f=0;		
	}
	else 
	{
		busbcken=1;
		if(bep0f) 
			AccessFIFO0();
		else if(bep1f) 
			AccessFIFO1();
	    else if(bep2f)
	        AccessFIFO2();
	}
	
}

void __attribute((interrupt(0x20))) TMR2_ISR()   //4ms interrupt,for set_idle
{
	if(_t2af)
	{
		_t2af=0;
        FlagBit.TimeOut=1;
        if(ucIdleTime && ucUSBState==STATE_CONFIG)
        {
        	if((count++)==ucIdleTime) 
        	{
        		count=0;
        	    KeyFlag.KB_KeyUpt=1;	
        	}
        }
	}
}   
    
    
    
    
    
    
    
    
    
    
    
    
    




















