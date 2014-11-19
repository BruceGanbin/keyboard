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
public _main_startup
@start   .SECTION 'CODE'
_main_startup:
 ;;	CLR WDT2    ;;PD,TO flag will be clear. This line can be removed if a small number of global variables in C program are used.
	Mov a, offset __initial_value_end
	dec acc
	MOV mp,A
	clr c
	Sub a, offset __initial_value_begin
	snz c
	jmp startupend1
L0004:
	mov ra,a
	CALL romdata_base1
	MOV iar,A
	dec mp
  ;;	CLR WDT   ;;PD,TO flag will be clear. This line can be removed if a small number of global variables in C program are used.
	deca ra
	sz ra
	jmp L0004 
startupend1:
  ;;	CLR WDT2  ;;PD,TO flag will be clear. This line can be removed if a small number of global variables in C program are used.
ROMBANK 0 @ROMDATA_BASE 
@ROMDATA_BASE .SECTION  inpage com_l 'CODE'
romdata_base1:
	ADDM A,[06H]

@HCCINIT   .SECTION  COM_L 'DATA'
__initial_value_begin:
@HCCINIT  .SECTION COM_E 'DATA'
__initial_value_end:
extern ra:byte
