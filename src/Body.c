
#include "ModifyCode.h"

void delay_us()   //12 us for ISR function
{
	GCC_CLRWDT();
	GCC_CLRWDT();
	GCC_CLRWDT();
	GCC_CLRWDT();
}
void delayM_us()  //12 us for main function
{
	GCC_CLRWDT();
	GCC_CLRWDT();
	GCC_CLRWDT();
	GCC_CLRWDT();
}

void sys_initial()
{
 	_wdtc=0xa8;	
 	_hlclk=1;
 		
 //	_cp0c=0;
//	_cp1c=0;
//	_acer0=0;
//	_acer1=0;
	
	_papu=0xff;
    _pxpu=0x3f;
	_pchwu=1;
	_pclwu=1;//pc wakeup
	   
	_pcc=0xff;
	_pac=0xff;
	_pbc=0xff;
	_pdc=0xff;
	NumLockC=0;
	CapsLockC=0;
	ScrollLockC=0;
	NumLock=1;
	CapsLock=1;
	ScrollLock=1;
	
    FlagByte=0;
	ucUSBState=0;
	ucIdleTime=125;  //default idle time for normal key
//	FlagBit.TimeOut=1;
	count=0;		  	
}
 
void timer2_initial()
 {
	_mf2e=1;
	_tm2al=0xee;
	_tm2ah=0x02;
	_tm2c0=0x30;             //fH/64,TMR2 off
	_tm2c1=0xc3;
	_t2ae=1;
 }
void usb_initial()
 {
 	_usbcken=1;	
 	_usbdis=0;
 	_usc&=0b10010000;	
 	_usr=0;
 	_urd=1;
 	_ufc0=0;
 	_ufc1=0;
 	_ufien=0x06;
 	_ufoen=0x00;
 	 busbe=1;
 	_fifo_def=1;
 	_uint=0x07;
 	 bv33c=1;
//    Bucc=0x28;      //_Fsys16MHz 
//_fsys16mhz=1;
//_usbcken=1;		
//  	Bsysc=0x80;	 //_clk_adj 
//    Busr=0x00;
//    Bstlo=0;
//    Bstli=0;
//    Bsies=0X00;     //_nmi
//    Bmisc=0;
//    Bufc0=0;
//    Bufc1=0;
//
//    Bufien=0x06;    //ep1,ep2 input,_seti1,_seti2
//    Bufoen=0x00;    //
//    Buint=0x07;     //ep0en/ep1en/ep2en/
//       
//    bwken=0;   
//    busbcken=1;
//    bfifo_def=1;
//    busbe=1;
//    _urd=1;
//    bv33c=1;
//    Busc=0x90;     
//    bv33c=1; 	
// 	Bsysc=0x80;	 //_clk_adj 
//    Busr=0x00;
//    Bucc=0x20;      //_Fsys16MHz
//    Bstlo=0;
//    Bstli=0;
//    Bsies=0X80;     //_nmi
//    Bmisc=0;
//    Bufc0=0;
//    Bufc1=0;
//    Busc=0x00;
//    Bufien=0x06;    //ep1,ep2 input,_seti1,_seti2
//    Bufoen=0x00;    //
//    Buint=0x07;     //ep0en/ep1en/ep2en/
//       
//    bwken=0;   
//    busbcken=1;
//    bfifo_def=1;
//    busbe=1;
//    bv33c=1; 
 }
 
void FIFO_Ready_Check(uchar8 endpoint)  //FIFO ready check
 {
 	GCC_CLRWDT();
    Bucc&=0xf8;    
    Bucc+=endpoint;       //select endpoint
    Bmisc=0x00;
 	btx=FlagBit.tx;       //write or read,1--read(input),0--write(output)
 	brequest=1; 	
 	delay_us();            //delay 4us	
 }   
 
void ReadWriteFIFO(uchar8 endpoint,uchar8 length)//,uchar8 FIFO)  //write and read FIFO
 {	
 	uchar8 i,FIFO;
 	FIFO_Ready_Check(endpoint);    //endpoint ready check
 	for(i=0;i<length && bready;i++)      //IF ready,begin to write/read
	{
	 	switch (endpoint)
		{
	        case 0 :  //for endpoint0 write and read
	        if(FlagBit.tx)  FIFO0=*(pSendDescriptor+i);              //const pointer,for descriptors
	        else            *(pSendData+i)=FIFO0;  	 break;   
	        case 1 :  //for endpoint1 write and read
	        if(FlagBit.tx)  FIFO1=*(pSendData+i);
	        else            *(pSendData+i)=FIFO1;    break;
	        case 2:   //for endpoint2 write and read
	        if(FlagBit.tx)  FIFO2=*(pSendData+i);
	        else            *(pSendData+i)=FIFO2;    break;	 
//	        case 3:   //for endpoint3 write and read
//	        if(FlagBit.tx)  FIFO3=*(pSendData+i);
//	        else            *(pSendData+i)=FIFO3;    break;			
		}
		delay_us();   //delay 4us
	}
	if(i==length) 
		FlagBit.ReadWrite_complete=1;     //whether executing is completed
    if(btx)btx=0;
    else btx=1;
// 	b_tx=!FlagBit.tx;
 	blen0=0;
 	brequest=0;
 }
void WakeupIO()
{
	_pcc=0xff;
	_pc=0xff;
	
	_pac=0x00;
	_pa=0x00;
	_pbc=0x00;
	_pb=0x00;
	_pdc=0xfc;
	_pd=0xfc;
	_pec=0xff;
	_pe=0xff;
	
	NumLockC=1;
	CapsLockC=1;
	ScrollLockC=1;
} 
void suspend_wakeup()
 {
	uchar8 temp;
 	bt2on=0;
 	while (bsusp!=0 && bresume==0) 	//goto exit_of_suspend;
 //	if (bhas_error_chk!=0) 	goto watchdog_timout;
	{
	 	KeyFlag.wakeup=0;
	 	WakeupIO();
//	 	if (bwken!=0)  	//goto has_wakeup_now;
//	 	{
////	 		kb_suspend();
//			
//	 	}
//	 	else
//	 	{
//		 	KeyFlag.wakeup=1;
////		 	kb_suspend_in_led();
//	 	}
		if (bsusp!=0 && bresume==0) 
		{
//		 	clk_adj_dis=1;
		 	GCC_HALT();
		//watch_wake :
//		 	clk_adj_dis=0;
		//wait_debounce :
			for(temp=0;temp<50 && bsusp!=0;temp++)
			{
				while(bsusp!=0 && bresume!=0)	GCC_CLRWDT();			
		//		if (bnowakeup!=0)  		goto watchdog_timout;		
			}
		 	if(_pc!=0xff) 	//goto wait_reseume_out;
		 	{	
			 	if (bwken!=0)  //	goto tosuspend_again;
			 	{
				 	brmwk=1;
				 	delayM_us();
				 	brmwk=0;
			  	  	KeyFlag.wakeup=1;
			  	  	KeyFlag.acpi_key_chg=1;
				 	temp=100;
					while(--temp) GCC_CLRWDT();
					while(bresume) GCC_CLRWDT();
			 	}			 	
		 	}
		 	else
		 	{
			 	while(bresume) GCC_CLRWDT();
		 	}
		}
		else break;
	}
//exit_of_suspend :
// 	kb_io_config();
// 	setled(kb_led);
 	bt2on=1;
}
//void suspend_wakeup()
// {
////    delay_ms(5);   //for 5*4=20ms
//	bt2on=0;
//	while(bsusp&&!bresume)
//	  {
////		_susp2=1;
//        WakeupIO();
////	  	busbcken=1;       //close USB clock
//	  	GCC_HALT();
//	  	busbcken=1;       //enable USB clock
////		_susp2=0;
////        delay_ms(3);       // 3*4=12ms ,for KEY1 debounce
//	  	if(bsusp&&!bresume)     //!KEY1 KEY1  remo-wakeup
//	  	  {
//	  	  	if(bwken)      //Whether remote-wakeup is enable      
//	  	  	{
//	  	  	 brmwk=1;
//	  	  	 delayM_us();   // 4us
//	  	  	 brmwk=0;       //send remote-wakeup pulse
////	  	  	 KeyFlag.wakeup=1;
////	  	  	 KeyFlag.acpi_key_chg=1;
//	  	  	 while(bsusp) GCC_CLRWDT();	 //wait for resume
//	  	  	 break;
//            }
//	  	  }
//	  	else break;
//	  }
//	  bt2on=1;
// }
//  
void  ModifyGetHaltStatus()  //get_status--------get endpoint stall status
{
	if(wIndexL&0x80)               //input endpoint
    {
       if(Bstli&=(1<<(wIndexL&0x0f))) Request_buffer[0]=1;   
       else   Request_buffer[0]=0;  
    }
    else                           //output endpoint
    {
       if(Bstlo&=(1<<wIndexL)) Request_buffer[0]=1;      
       else   Request_buffer[0]=0;
    }
}

void set_feature()       //set_feature
{
	if(wLength!=0||wValueH||wIndexH||ucUSBState!=STATE_CONFIG) bstlo0=1;
	else
	{
	    if(bmRequestType==2 && !wValueL && !wValueH)    //endpoint type and endpoint halt feature,wValue should be 0
		{ 
		  if(wIndexL&0x80)   //input endpoint,left by 'wIndexL&0x0f' bits
		  Bstli|=1<<(wIndexL&0x0f);
		  else   Bstlo |=(1<<wIndexL);       //output endpoint           	  		 
		}
		else if(!bmRequestType && (wValueL==1) && (!wValueH))    //device type and remote-wakeup feature                
		{
			if(wIndexL) bstli0=1;     //wIndexL should be 0
			else   bwken=1;      
		}
		else bstli0=1;
	}
}

void clear_feature()   //clear_feature
{
	if(wLength!=0||wValueH||wIndexH||ucUSBState!=STATE_CONFIG) bstlo0=1;
	else
	{
		if(bmRequestType==2 && !wValueL && !wValueH) 
		{
	  	    if(wIndexL&0x80) Bstli&= ~(1<<(wIndexL&0x0f));   
			else   Bstlo &=~(1<<wIndexL); 
		}
		else if(!bmRequestType && wValueL==1 && !wValueH) //clear remote-wakeup feature
		{
			if(wIndexL) bstli0=1;
			else   bwken=0;  
		}
		else bstli0=1;	
	}
}

void UserToBootloader()     //setting ISP mode(user code to bootloader code)
{
	busbe=0;	                  //avoid stack overflow
    asm("call  ENABLE_BL");      
    asm("snz   B_ENABLE_BL_OK");     //whether jump to bootloader code is successful
    asm("jmp   asmend");
    FlagBit.BootloaderSuccess=1;  //success one time
    FlagBit.ToBootloader=0;       //clear set ISP mode flag
//    asm("set   [24H].7");           //If PC7 is high, set successfully.
//  asm("jmp   $");                 //wait for resetting MCU
    asm("asmend:");
    busbe=1;
}
  










