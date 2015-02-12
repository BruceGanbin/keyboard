#include "gsl1688.h"

static u8 gsl_read_interface(u8 reg,u8 *buf,u16 num)
{
    iic_read(reg,buf,num);
    return 1;
}

static u8 gsl_write_interface(u8 reg,u8 *buf,u16 num)
{
    iic_write(reg,buf,num);
    return 1;
}

static void gsl_load_fw(fw_data *GSL_FW_DATA,u32 len)
{
	u8 buf[4] = {0};
    u8 addr;
    u32 source_line = 0;
	u32 source_len = data_len;//ARRAY_SIZE(GSL_DOWNLOAD_DATA);
    for (source_line = 0; source_line < source_len; source_line++)
    {
        addr = GSL_FW_DATA[source_line].addr;
        memcpy(buf,&GSL_DOWNLOAD_DATA[source_line].val,4);
        gsl_write_interface(addr,buf,4);
    }
}

static void gsl_start_core(void)
{
    u8 buf[4] = {0};
    gsl_write_interface(0xe0,buf,4);
}

static void gsl_reset_core(void)
{
	u8 buf[4] = {0x00};
	
	buf[0] = 0x88;
	gsl_write_interface(0xe0,buf,4);
    delay_ms(5);

	buf[0] = 0x04;
	gsl_write_interface(0xe4,buf,4);
    delay_ms(5);
	
	buf[0] = 0;
	gsl_write_interface(0xbc,buf,4);
    delay_ms(5);
}

static void gsl_clear_reg(void)
{
	u8 buf[4]={0};
	//clear reg
	buf[0]=0x88;
	gsl_write_interface(0xe0,buf,4);
    delay_ms(5);
	buf[0]=0x1;
	gsl_write_interface(0x80,buf,4);
    delay_ms(5);
	buf[0]=0x4;
	gsl_write_interface(0xe4,buf,4);
    delay_ms(5);
	buf[0]=0x0;
	gsl_write_interface(0xe0,buf,4);
    delay_ms(5);
	//clear reg
}

/**
static u8 gsl_compatible_id(void)
{
	u8 buf[4];
	int i,err;
	for(i=0;i<5;i++)
	{
		gsl_read_interface(0xfc,buf,4);
		printk("[tp-gsl] 0xfc = {0x%02x%02x%02x%02x}\n",buf[3],buf[2],
			buf[1],buf[0]);
    }
	return 1;	
}
**/

static void gsl_hw_init(void)
{
    iic_init();
}

static void gsl_sw_init(void)
{
	gsl_clear_reg();
	gsl_reset_core();
    gsl_load_fw(GSLX68X_FW,val_len);
}

static void check_mem_data(void)
{
    u8 buf[4] = {0};
    delay_ms(30);
    gsl_read_interface(0xb0,read_buf,4);
}

static u8 gsl_ts_probe(void)
{

}

void  gsl_ts_init(void)
{

}

void gsl_report_point(void)
{

}










