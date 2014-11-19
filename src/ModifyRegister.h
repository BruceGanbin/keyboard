
#ifndef     _MODIFYREGISTER_H
#define     _MODIFYREGISTER_H

//#include    "HT68FB560.h"
#include    "SH68F83.h"

#define     Bsysc          _sysc
/*_sysc
# b7_clk_adj:PLL related control bit
# b6_usbdis:0-enable USB SIE 
# b5_rubus:0-enable UBUS pin pull low
# b4~0:Unimplemented*/

#define     Buint          _uint
/*_uint
# b3~0_ep3en~_ep0en:Enable USB endpoint n interrupt  */ 
   
#define     Busr           _usr
#define     bep0f          _ep0f
#define     bep1f          _ep1f
#define     bep2f          _ep2f
#define     bep3f          _ep3f
/*_usr
# b3~0_ep3f~_ep0f: USB endpoint n interrupt flag */

#define     Bucc           _ucc
#define     busbcken       _usbcken
/*_ucc
# b7_rctrl:     1-7.5k resistor between UDP and Ubus
# b6_sysclk:    0-12MHz 
# b5_Fsys16MHz: 0-system clock source from OSC
# b4_susp2:     1-in halt mode,
# b3_usbcken:   1-enable USB clock
# b2~0_eps2~0:  000-select endpoint 0 FIFO;
                001 select endpoint 1 FIFO;
                010-select endpoint 2 FIFO;
                011 select endpoint 3 FIFO;
                100-select endpoint 4 FIFO;
                101~111- select endpoint 5 FIFO;  */

#define	    Bawr           _awr
#define     bwken          _wken
/*_awr
# b7~1_ad6~_ad0:USB device address
# b0_wken:1-Enable remote wake-up*/

#define     Bstlo          _stlo
#define     bstlo0         _stlo0
/*_stlo
# b5~0_stlo5~_stlo0:1-FIFO OUT stall endpoints indication  */

#define     Bstli          _stli
#define     bstli0         _stli0
/*_stli
# b5~0_stli5~_stli0:1-FIFO IN stall endpoints indication  */

#define     Bsies          _sies
#define     baset	        _aset
#define     bout           _out
#define     bin            _in
/*_sies
# b7_nmi:1-NAK token interrupt disable
# b6_crcf:1-CRC error
# b4_nak:1-ACK error
# b3_in:1-USB IN token
# b2_out:1-USB OUT token
# b1_err:1-FIFO accessed error
# b0_aset:0-Update address after an written address to the AWR register
          1-Update address after PC host read out data  */

#define     Busc           _usc
#define     bsusp          _susp
#define     brmwk          _rmwk
#define     bresume        _resume
#define     bv33c          _selusb
/*_usc
# b7_urd:   1-USB reset will reset MCU
# b6_selps2:1-PS2 mode
# b5_pll:   0-Turn on PLL
# b4_selusb:1-USB mode,Turn on V33O
# b3_resume:1-leave the suspend mode
# b2_urst:  1-USB reset occurred
# b1_rmwk:  1-remote wake-up
# b0_susp:  1-enter the suspend mode  */

#define     Bmisc          _misc
#define     brequest       _request
#define     btx            _tx
#define     bsetcmd        _setcmd
#define     bready         _ready
#define     blen0          _len0
/*_misc
# b7_len0:1-zero sized packet
# b6_ready:1-desired FIFO ready
# b5_setcmd:1-setup command       
# b4_e4odf:endpoint 4 output FIFO selection,0-single buffer,1-double buffer                  
# b3_e3idf:endpoint 3  input FIFO selection,0-single buffer,1-double buffer                    
# b2_clear:1-enable clear FIFO                   
# b1_tx:0-data writing finished,1-data writing to FIFO                   
# b0_request:1-desired FIFO request indication   */ 

#define     Bufoen         _ufoen
#define     bdatatg        _datatg
/*_ufoen
# b5~1_seto5~_seto1:1-enable EPn output FIFO 
# b0_datatg:1-data token toggle*/

#define     Bufien         _ufien
#define     bfifo_def      _fifo_def
/*_ufien=0x02;
# b5~1_seti5~_seti1:1-enable EPn input FIFO 
# b0_fifo_def:1-SIE redefine the FIFO configuration  */

#define     Bufc0          _ufc0
/*_ufc0
# b7,6_e3fs1,e3fs0:00-endpoint 3 FIFO size 8-byte
                01-endpoint 3 FIFO size 16-byte
                10-endpoint 3 FIFO size 32-byte
                11-endpoint 3 FIFO size 64-byte
# b5,4_e2fs1,e2fs0:00-endpoint 2 FIFO size 8-byte
                01-endpoint 2 FIFO size 16-byte
                10-endpoint 2 FIFO size 32-byte
                11-endpoint 2 FIFO size 64-byte
# b3,2_e1fs1,e1fs0:00-endpoint 1 FIFO size 8-byte
                01-endpoint 1 FIFO size 16-byte
                10-endpoint 1 FIFO size 32-byte
                11-endpoint 1 FIFO size 64-byte  */

#define    Bufc1           _ufc1
/*_ufc1
# b3,2_e5fs1,e5fs0:00-endpoint 5 FIFO size 8-byte
                01-endpoint 5 FIFO size 16-byte
                10-endpoint 5 FIFO size 32-byte
                11-endpoint 5 FIFO size 64-byte    
# b1,0_e4fs1,e4fs0:00-endpoint 4 FIFO size 8-byte
                01-endpoint 4 FIFO size 16-byte
                10-endpoint 4 FIFO size 32-byte
                11-endpoint 4 FIFO size 64-byte  */

#define     FIFO0           _fifo0
#define     FIFO1           _fifo1
#define     FIFO2           _fifo2
#define     FIFO3           _fifo3
#define     busbe          _usbe
#define     bt2on          _t2on



#endif






