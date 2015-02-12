#include "51_iic.h"

sbit iic_clk = P2^1;
sbit iic_dat = P2^2;

void delay()
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

void delay_ms(uint32 z)
{
    uint32 x,y;
    for(x=z;x>0;x--)
        for(y=110;y>0;y--);
}

void start()
{
    SDA=1;
    delay();
    SCL=1;
    delay();
    SDA=0;
    delay();
    SCL=0;
}

void stop()
{
    SDA=0;
    delay();
    SCL=1;
    delay();
    SDA=1;
    delay();
}

void ack()
{
    u8 i;
    SCL=1;
    delay();
    while((SDA==1)); //&&(i<250))i++;
    SCL=0;
    delay();
}

void send_ack(void)
{
    SCL = 0;  
    delay();
    SDA = 0;
    delay();
    SCL = 1;  
    delay();
    SCL = 0;
    delay();
    SDA = 1;  
    delay();
}

u8 rec_ack(void)
{
    SCL = 1;  
    delay();
    if(SDA == 1)  
    {  
        SCL = 0;  
        delay();  
        SCL = 1;  
        if(SDA == 1)  
            return 1;  
    }  
    else  
        return 0;  
}

void write_byte(uchar dat)
{
    u8 i;
    for(i=0;i<8;i++)
    {
        SCL=0;
        delay();
        if((dat&0x80)!=0) SDA=1;
        //        SDA=dat&0x80;
        else SDA=0;
        SCL=1;
        delay();
        temp<<=1;
    }
    SCL=0;
    delay();
    SDA=1;
    delay();
}

uchar read_byte(void)
{
    u8 i,dat;
    
    SCL = 0;  
    delay();
    SDA = 1;  
    delay();
    for(i=0;i<8;i++)  
    {  
        SCL = 1;  
        delay();
        dat = (dat<<1)|SDA;  
        SCL = 0;  
        delay();
    }  
    return dat;
}

void iic_init(void)
{
    SCL=1;
    delay();
    SDA=1;
    delay();
}

void iic_write(u8 reg,u8 *dat,u8 len)
{
    u8 i;  
    start();
    write_byte(DEV_ADDR);
    if(rec_ack() == 0)
    {
        write_byte(reg);
        if(rec_ack() == 0)
        {
            for(i=0;i<len;i++)
            {
                write_byte(dat[i]);
                if(rec_ack() == 1)
                {
                    i = 0;
                    break;
                }
            }
        }
    }
    stop();
}

void iic_read(u8 reg,u8 *dat,u8 len)
{
    u8 i;
    start();
    write_byte(DEV_ADDR);
    if(rec_ack() == 0)
    {  
        write_byte(reg);  
        if(rec_ack() == 0)  
        {  
            start();  
            write_byte(DEV_ADDR+1);
            if(rec_ack() == 0)
            {
                for(i=0;i<len;i++)
                {
                    dat[i] = read_byte();
                    send_ack(0);
                }
                send_ack(1);
                somenop();
            }
        }
    }
    stop();
}

