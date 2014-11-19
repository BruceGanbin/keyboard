;;--------------------------------------------------------------;;
;;    This file is part of the Holtek C Compiler V3 package     ;;
;;    For the initialization of static linkage variables        ;;
;;    Copyright (C) 2013 Holtek Semiconductor Inc.              ;;
;;    Version: 1.01 (Above IDE3000 V7.72)                       ;;
;;    Date:    2013/10/24                                        ;;
;;--------------------------------------------------------------;;

acc equ [05h]
mp equ [01h]
iar equ [00h]
bp equ [04h]
z equ [0ah].2
c equ [0ah].0
public _main_initial0
@start   .SECTION 'CODE'
_main_initial0:
	mov a, offset __initial0_value_end 
	mov mp, a
	dec mp
	clr z
	Sub a, offset __initial0_value_begin
	sz z
	jmp startupend
L0003:
	  clr iar
	  dec mp
;;	  CLR WDT  ;;PD,TO flag will be clear. This line can be removed if a small number of global variables in C program are used.
	  sdz acc
	  jmp L0003
startupend:
;;	CLR WDT2    ;;PD,TO flag will be clear. This line can be removed if a small number of global variables in C program are used.

@HCCINIT0   .SECTION  COM_L 'DATA'
__initial0_value_begin:
@HCCINIT0  .SECTION COM_E 'DATA'
__initial0_value_end:
