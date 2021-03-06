;----------------------------------------------------------------------------
; 描述符类型值说明
; 其中:
;       DA_  : Descriptor Attribute
;       D    : 数据段
;       C    : 代码段
;       S    : 系统段
;       R    : 只读
;       RW   : 读写
;       A    : 已访问
;       其它 : 可按照字面意思理解
;----------------------------------------------------------------------------
DA_32				EQU		4000h	; 32 位段
DA_LIMIT_4K	EQU		8000h	; 段界限粒度为 4K 字节

DA_DPL0			EQU	  	00h		; DPL = 0
DA_DPL1			EQU	  	20h		; DPL = 1
DA_DPL2			EQU	  	40h		; DPL = 2
DA_DPL3			EQU	  	60h		; DPL = 3
;----------------------------------------------------------------------------
; 存储段描述符类型值说明
;----------------------------------------------------------------------------
DA_DR				EQU		90h		; 存在的只读数据段类型值
DA_DRW			EQU		92h		; 存在的可读写数据段属性值
DA_DRWA		EQU		93h		; 存在的已访问可读写数据段类型值
DA_C				EQU		98h		; 存在的只执行代码段属性值
DA_CR				EQU		9Ah		; 存在的可执行可读代码段属性值
DA_CCO			EQU		9Ch		; 存在的只执行一致代码段属性值
DA_CCOR			EQU		9Eh		; 存在的可执行可读一致代码段属性值
;----------------------------------------------------------------------------


; 宏 ------------------------------------------------------------------------------------------------------
;
; 描述符
; usage: Descriptor Base, Limit, Attr
;        Base:  dd
;        Limit: dd (low 20 bits available)
;        Attr:  dw (lower 4 bits of higher byte are always 0)
%macro 	Descriptor 	3
	dw	%2 & 0xFFFF											; 段界限 1								(2 字节)
	dw	%1 & 0xFFFF											; 段基址 1								(2 字节)
	db	(%1 >> 16) & 0xFF									; 段基址 2								(1 字节)
	dw	((%2 >> 8) & 0xF00) | (%3 & 0xF0FF)		; 属性 1 + 段界限 2 + 属性 2	(2 字节)
	db	(%1 >> 24) & 0xFF									; 段基址 3								(1 字节)
%endmacro 														; 											共 8 字节
;

; Trun on protect-mode
%macro 	TurnOnPM 	0
	mov			eax, cr0 
	or			eax, 1 					; Set PE bit
	mov			cr0, eax
%endmacro

; Trun off protect-mode
%macro 	TurnOffPM 	0
	mov			eax, cr0 
		and 		al, 11111110b 		; Clear PE bit
	mov			cr0, eax
%endmacro

; Trun on A20 Gate
%macro 	TurnOnA20 	0
	in			al, 0x92
	or		al, 00000010b
	out		0x92, al
%endmacro

; Trun on A20 Gate
%macro 	TurnOffA20 	0
	in			al, 0x92
	and		al, 11111101b
	out		0x92, al
%endmacro
; ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
