; add reading from hw disk 

ORG 0
BITS 16

_start:
	jmp short start
	nop

times 33 db 0

start:
	jmp 0x7c0:step2

step2:
								; ds * 16 + 0x7c00
								; ds = 0x7c0
								; 0x7c00 + 0x7c00

	cli 						; Clear Interrupts
	mov ax, 0x7c0
	mov ds, ax
	mov es, ax
	mov ax, 0x00
	mov ss, ax
	mov sp, 0x7c00
	sti 						; Enable Interrupts

	mov ah, 0x02	; read sector command 		
	mov al, 1 		; one sector to read
	mov ch, 0		; cylinder low eight bits
	mov cl, 2 		; read sector two 
	mov dh, 0		; head number
	mov bx, buffer
	int 0x13
	jc error
	
	mov si, buffer
	call print
	jmp $

error:
	mov si, error_message
	call print 
	jmp $

print:
	mov bx, 0
.loop:
	lodsb
	cmp al, 0
	je .done
	call print_char
	jmp .loop
.done:
	ret

print_char:
	mov ah, 0eh
	int 0x10
	ret

error_message: db 'Failed to load sector', 0

times 510-($-$$) db 0			;fill zero up to 512 bytes
dw 0xAA55

;buffer: db 'AAAAAAAAAAAAAaa', 0
buffer:
