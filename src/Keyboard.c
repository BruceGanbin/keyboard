/*******************************************
PC0-8: scan in
PB0-8: scan out
*******************************************/
#include "ModifyCode.h"

void usb_key_examine();


void always_no_fn_mode_now()
{
	uchar8 R0,temp,bitbuff,int_temp2;
	R0=Fn_key_break_state[int_temp1>>3]; //int_temp1/8
	int_temp2=scan_out[int_temp1&0x07]; //int_temp1%8
	temp=~int_temp2;
	if(KeyFlag.fn_key_break==0)
	{
		if(KeyFlag.f2_f1)  //Fn+Fx
		{
			if(KeyFlag.Fn_mode) R0&=int_temp2;  //normal key
			else R0|=temp; //function key
		}
		else //small num
		{
			if(KeyFlag.Fn_mode^KeyFlag.NumLockStatus) R0&=int_temp2;
			else R0|=temp;
		}
		Fn_key_break_state[int_temp1>>3]=R0;
//		int_temp1=0;
//		_acc=0;
//		if(KeyFlag.NumLock)int_temp1=0xff;
//		if(KeyFlag.Fn_mode==0) _acc=0xff;
//		if(KeyFlag.f2_f1==0) _acc^=int_temp1;
//		if(_acc&0xff) R0|=int_temp2;
//		else R0&=(~int_temp2);		  
	}
	int_temp1=KeyMatrix[IndexBuf]&0xff;
	int_temp2=Fn_mode_key[int_temp1<<1]&0xff;
	temp1_matrix=(Fn_mode_key[int_temp1<<1]>>8)&0xff;
	if(KeyFlag.fn_mode_now) //1:F2---have function key,then judge Fn make or break
	{
		if((KeyFlag.always_fn)||((KeyFlag.always_fn==0)&&(R0&temp)))
		{
		temp=(int_temp1<<1)+1;
		int_temp2=Fn_mode_key[temp];  //get function key code
	    temp1_matrix=(Fn_mode_key[temp]>>8)&0xff;	
		}
	}
//	exit_of_fn_key();
    fn_key_code=int_temp2;
    if(KeyFlag.has_usb_fn) 
    {
    KeyFlag.fn_key_break=0;
    //usb_key_examine()
	switch(temp1_matrix&0x0f)
	{
		case 0: keycode=fn_key_code;
		        KeyFlag.return_value=0;break;
//		case 3: if(CurrentState&0x01) KeyFlag.hotkeyset=1;
//		        else KeyFlag.combinekey=1;
//		        KeyFlag.return_value=0;break;
		case 0x0c: KeyFlag.hotkeyset=1;
		        if(CurrentState&0x01) KeyFlag.Fn_mode=1;
		        else KeyFlag.Fn_mode=0;
		        KeyFlag.return_value=1;break;
		default:
		{ 	
			//bit_map_key()
			KeyFlag.hotkeyset=1;
			if(KeyFlag.has_usb_fn) int_temp1=fn_key_code;
		    switch(temp1_matrix&0x0f)
			{
				case 0x04: KeyFlag.multi_key_chg=1;break; 
				case 0x05: KeyFlag.multi_key_chg=1;break; 
				case 0x06: KeyFlag.multi_key_chg=1;break;
				case 0x07: KeyFlag.acpi_key_chg=1; break;
				case 0x08: KeyFlag.KB_KeyUpt=1;    break;
				case 0x09: KeyFlag.hot_key_chg=1;  break;
			}
			bitbuff=(temp1_matrix&0x0f)-4;
		    if(CurrentState&0x01) key_byte[bitbuff]&=(~int_temp1);
		    else key_byte[bitbuff]|=int_temp1;	
		    KeyFlag.return_value=1;		
		}break;		
	}
    }
 //   else ps2_key_examine(); 
}
void has_fn1_key()
{
	uint16 temp;
	KeyFlag.fn_key_break=0;
	if(CurrentState&0x01) KeyFlag.fn_key_break=1;
	KeyFlag.has_usb_fn=1;
	//examine_function_key
	KeyFlag.f2_f1=0;
	int_temp1=KeyMatrix[IndexBuf]&0xff;
//	int_temp2=int_temp1;
	//ps2_key_examine();
	switch(temp1_matrix&0x0f)
	{
		case 1: KeyFlag.always_fn=0;
		        KeyFlag.fn_mode_now=1; 
		        always_no_fn_mode_now();break;//small num area  
		case 2: KeyFlag.always_fn=0;
		        KeyFlag.fn_mode_now=1;
		        KeyFlag.f2_f1=1;
		        always_no_fn_mode_now();break;//Fn+Fx
	}	
}    

void UpdateState(uchar8 Key_No)
{
	if(CurrentState&0x01)
    {
    	GOLDKY[scanlineno]|=~scan_out[Key_No];
    	if(KeyFlag.hotkeyset==0) 
    	KeyFlag.KB_KeyUpt=1; 
    }
    else 
    {
    	GOLDKY[scanlineno]&=scan_out[Key_No];
    	if(KeyFlag.hotkeyset==0) 
    	KeyFlag.KB_KeyUpt=1;
    }
}    
void chk_key_change()
{
	uchar8 i,temp,ChangeKeyMap,KeyNo,bitbuff;
	 KeyFlag.chk_key_change=0;
    for(scanlineno=0;scanlineno<total_scanline;scanlineno++)
    {
	CurrentState=GNEWKY[scanlineno];//makecode or breakcode
	ChangeKeyMap=GNEWKY[scanlineno]^GOLDKY[scanlineno];
	for(KeyNo=0;KeyNo<8;KeyNo++)
	{	
		if(ChangeKeyMap&0x01)
		{
			KeyFlag.has_key_change=1;
			IndexBuf=(scanlineno<<3)+KeyNo;
		    //translate_to_key_code();
		    KeyFlag.hotkeyset=0; //hotkeyset:whether send data,0:send
			KeyFlag.f2_f1=0;
			KeyFlag.has_usb_fn=0;
			KeyFlag.fn_key_break=0;
			if(IndexBuf==FnKeyIndex)
			{
			if(CurrentState&0x01) KeyFlag.Fn_mode=1;
		    else KeyFlag.Fn_mode=0;
			}
			
			int_temp1=KeyMatrix[IndexBuf]&0xff;
			temp1_matrix=(KeyMatrix[IndexBuf]>>8)&0xff;
			//usb_key_examine()
			switch(temp1_matrix&0x0f)
			{
				case 0: keycode=int_temp1;
				        KeyFlag.return_value=0;break;
				case 1:               //function key,Fn key
				case 2: has_fn1_key();break; //Fn+Fx
				case 3: KeyFlag.hotkeyset=1;
				        if(Buff_Index==0)
				        {
				        if(CurrentState&0x01) KeyFlag.combinekey=0;
				        else {KeyFlag.combinekey=1;KeyFlag.KB_KeyUpt=1;}
				        comkeys=0;
				        }
				        KeyFlag.return_value=1;break;
				case 0x0c: KeyFlag.hotkeyset=1;
				           KeyFlag.return_value=1;break;
				default:
				{ 	
					//bit_map_key()
					KeyFlag.hotkeyset=1;
					if(KeyFlag.has_usb_fn) int_temp1=fn_key_code;
				    switch(temp1_matrix&0x0f)
					{
						case 0x04: KeyFlag.multi_key_chg=1;break; 
						case 0x05: KeyFlag.multi_key_chg=1;break; 
						case 0x06: KeyFlag.multi_key_chg=1;break;
						case 0x07: KeyFlag.acpi_key_chg=1; break;
						case 0x08: KeyFlag.KB_KeyUpt=1;    break;
						case 0x09: KeyFlag.hot_key_chg=1;  break;
					}
					bitbuff=(temp1_matrix&0x0f)-4;
				    if(CurrentState&0x01) key_byte[bitbuff]&=(~int_temp1);
				    else key_byte[bitbuff]|=int_temp1;	
				    KeyFlag.return_value=1;		
				}break;		
			}	
			
			if(KeyFlag.return_value) 
			{
                UpdateState(KeyNo);
			}
			else    //0:normal key,reordering buffer
			{
				if(CurrentState&0x01)
				{
				    //user_remove_sort();
                    for(i=0;i<Buff_Index;i++)
                    {
                    	if(key_code_buff[i]==keycode)
                    	{
                    		key_code_buff[i]=key_code_buff[i+1];
                    		key_code_buff[i+1]=keycode;
                    	}
                    }
                    key_code_buff[Buff_Index]=0;
                    Buff_Index--;
				    KeyFlag.buffull=0;
//				    _usbe=1;
				    UpdateState(KeyNo);	
				}
			    else
			    {			    	
			    	if(Buff_Index==KEY_BUF_END)
			    	{
//			    		_usbe=1;
			    		if(KeyFlag.buffull==0)  
			    		{
			    			KeyFlag.buffull=1;
			    			KeyFlag.KB_KeyUpt=1;			    		
			    		}
			    	}
			    	else 
			    	{		    		
			    		key_code_buff[Buff_Index]=keycode;
			    		Buff_Index++;
			    		KeyFlag.buffull=0;
//			    		_usbe=1;
			    		UpdateState(KeyNo);
			    	}
			    } 
			}			
		}
		CurrentState>>=1;
		ChangeKeyMap>>=1;
	}
    }
    if(KeyFlag.has_change)
    {
    	KeyFlag.has_change=0;
    	if(KeyFlag.buffull && KeyFlag.has_key_change==0)
    	{
    		KeyFlag.buffull=0;
    		KeyFlag.KB_KeyUpt=1;
    	}
    }
}
void scan_out_high()
{
	_pcc|=0xff;
	_pc |=0xff;	   //scan in
	
	_pac|=0xff;
	_pa |=0xff;
	_pbc|=0xff;  
	_pb |=0xff;
	_pdc|=0xe3;    //pd2\3\4 for num\cap\scr
	_pd |=0xe3;    //scan out
	
	_pec|=0xff;
	_pe |=0xff;	
}
void set_led()
{
	if(KeyFlag.NumLockStatus)
	{
		NumLockC=0;
		NumLock=0;
	}
	if(KeyFlag.CapsLockStatus)
	{
		CapsLockC=0;
		CapsLock=0;
	}
	if(KeyFlag.ScrollLockStatus)
	{
		ScrollLockC=0;
		ScrollLock=0;
	}
}
void MKYSCN()
{
//	const uchar8 *p_scan;//
    volatile uchar8 *p_scan;
    uchar8 i,scanout,temp,ChgKeyState,bitcnt;
	for(scanlineno=0;scanlineno<total_scanline;scanlineno++)
	{
		_usbe=0;
		scan_out_high();
		scanout=scan_line_tab[scanlineno];
		temp=(scanout&0xf0)>>4;   //get IO_address offset
		p_scan=IO_address[temp];
		*(p_scan)=scan_out[scanout&0x0f];   //for scan out control
		temp++;
		p_scan=IO_address[temp];
		*(p_scan)=scan_out[scanout&0x0f];   //for scan out
//		_usbe=1;
		GCC_CLRWDT();   //delay us;
		p_scan=IO_address[1];  //scan in
		temp=*(p_scan);
		if(temp!=GNEWKY[scanlineno])
		{
            GKEYCT=0;
	//		temp=*p_scan;
			GNEWKY[scanlineno]=temp;
			KeyFlag.has_change=1;
		}
		scan_out_high();
		set_led();	
		if(scanlineno==0) GPHONT=~GNEWKY[0];
		else 
		{
			temp=~GNEWKY[scanlineno];
			ChgKeyState=temp&GPHONT;
			GPHONT|=temp;	
		}
		bitcnt=0;
		for(i=0;i<8;i++)
		{
		    if(ChgKeyState&0x01) bitcnt++;
		    ChgKeyState>>=1;
		}
		if(bitcnt>=2)
		{
			KeyFlag.FPHNCK=1;
			if(KeyFlag.FPHONK==0)
			{
				KeyFlag.FPHONK=1;
				GREPCT=45;
			}
		}
	}
	if(KeyFlag.FPHNCK==0)
	{
		if(KeyFlag.FPHONK)
		{
			KeyFlag.FPHONK=0;           //phantom key relieve
			if(KeyFlag.thefirstPHout)
			KeyFlag.KB_KeyUpt=1;               
			KeyFlag.thefirstPHout=0;
		}			
	}
	KeyFlag.FPHNCK=0;
	GPHONT=0;
	if(++GKEYCT==4)
	{
		GKEYCT=0;		
		KeyFlag.has_key_change=0;
		if(KeyFlag.FPHONK)
		{
			if(--GREPCT==0)
			{
				GREPCT=45;
				if(KeyFlag.thefirstPHout==0) 
				KeyFlag.KB_KeyUpt=1;           //have phantom key
				KeyFlag.thefirstPHout=1;
			}
		}
//		else KeyFlag.chk_key_change=1;
        else chk_key_change();
	}	
}

    
    
    
    
    
    
    
    
    
    
    
    
    




















