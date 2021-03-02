section .asm

extern int21h_handler
extern no_interrupt_handler

global int21h
global no_interrupt
global enable_interrupts
global disable_interrupts

enable_interrupts:
	sti
	ret

disable__interrupts:
	cli
	ret


global idt_load
idt_load:
	push ebp
	mov ebp, esp

	mov ebx, [ebp + 8] ; access point to first func argument	

	lidt [ebx]
	pop ebp
	ret

int21h:
	cli
	pushad
	call int21h_handler
	popad
	sti
	iret

no_interrupt:
	cli
	pushad
	call no_interrupt_handler 
	popad
	sti
	iret

