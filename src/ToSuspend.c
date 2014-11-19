#include  "Variable.h"

void tosuspend()
{
	uchar8 temp;
 	timer1_on=0;
//tosuspend_again :
 	bwdt_timeout=0;
// 	a=168;
 	detect_usb_signal_with_acc(168);
 	while (suspend_line!=0 && resume_line==0) 	//goto exit_of_suspend;
 //	if (bhas_error_chk!=0) 	goto watchdog_timout;
	{
		if(bhas_error_chk!=0) 
		{
			goto watchdog_timout;
			return;
		}
		else if(bcfgvalue==0 && cmd_addr==0)
		{
			if(error_cnt!=0)
			{
				goto watchdog_timout;
				return;
			}
		}
		if(suspend_line==0) break;
		bwdt_timeout=0;
	 	bnowakeup=0;
	 	if (brmtwakeup!=0)  	//goto has_wakeup_now;
	 	{
	 		kb_suspend();
	 	}
	 	else
	 	{
		 	bnowakeup=1;
		 	kb_suspend_in_led();
	 	}
		if (suspend_line!=0 && resume_line==0) 
		{
		 	clk_adj_dis=1;
		 	halt();
		//watch_wake :
		 	clk_adj_dis=0;
		//wait_debounce :
			for(temp=0;temp<50 && suspend_line!=0;temp++)
			{
				while(suspend_line!=0 && resume_line!=0)	wdt=0;			
				if(bnowakeup!=0)
				{
					goto watchdog_timout;
					return;
				}
		//		if (bnowakeup!=0)  		goto watchdog_timout;		
			}
			if(suspend_line==0) break;
		 	temp2=0xff;
		 	if (scan_in7==0)  	temp2.7=0;
		 	if (scan_in6==0)  	temp2.6=0;
		 	if (scan_in5==0)  	temp2.5=0;
		 	if (scan_in4==0)  	temp2.4=0;
		 	if (scan_in3==0)  	temp2.3=0;
		 	if (scan_in2==0)  	temp2.2=0;
		 	if (scan_in1==0)  	temp2.1=0;
		 	if (scan_in0==0)  	temp2.0=0;
		 	if(temp2!=0xff) 	//goto wait_reseume_out;
		 	{	
			 	if (brmtwakeup!=0)  //	goto tosuspend_again;
			 	{
				 	wakeup_line=1;
				 	wait_4us();
				 	wakeup_line=0;
				 	bwakeup_now=1;
				 	bacpi_key_chg=1;
				 	temp=100;
					while(--temp) GCCCLRWDT();
					while(resume_line) GCCCLRWDT();
			 	}			 	
		 	}
		 	else
		 	{
			 	while(resume_line) GCCCLRWDT();
		 	}
		}
		else break;
	}
//exit_of_suspend :
 	kb_io_config();
 	setled(kb_led);
 	timer1_on=1;
}
void detect_usb_signal(uchar8 count)
{
	uchar8 temp;
 	bhas_error_chk=0;
 	berror_cnt=0;
	for(temp=0;temp<count;temp++)
	{
	 	wdt=0;
	 	//check_00_11();
	 	if(usc & 0b00110000==0b00110000) 	berror_cnt++;//UDP/UDN¦P¬°high
	 	if(usc & 0b00110000==0b00110000) 	berror_cnt++;// 	check_00_11();
	 	if(usc & 0b00110000==0b00110000) 	berror_cnt++;
	 	if(usc & 0b00110000==0b00110000) 	berror_cnt++;
	 	if (bwdt_timeout==0)  
	 	{
		 	if (berror_cnt!=0)  	
		 	{
			 	bhas_error_chk=1;
			 	return ; 		
		 	}
		 	else if (suspend_line==0)  return;
	 	}
	}
}