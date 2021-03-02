[BITS 32]

global _start
global test_problem

extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov ebp, 0x00200000
	mov esp, ebp
	
	; Fast A20 gate
	in al, 0x92 		; Fast switch A20 mode through I/O port 0x92 ( in matherboard )
	or al, 2
	out 0x92, al

	; Remap  the master PIC
	mov al, 00010001b ; b4=1: Init; b3=0: Edge; b1=0: Cascade; b0=1: Need 4th init step
    out 0x20, al      ; Tell master

    mov al, 0x20      ; Tell IRQ0 should be on INT 0x20 (Just after Intel exception)
    out 0x21, al      ;

    mov al, 00000001b ; b4=0: FNM; b3-2=00: Master/Slave set by hw; b1=0: Not AEOI; b0=1: x86 mode
    out 0x21, al      ;

	; end of remap master PIC

	; Enable interrupts 
	call kernel_main
	
	jmp $ 



test_problem: 
;	mov eax, 0
;	div eax
	int 0

times 512-($-$$) db 0
