Oveview of x86 Memory Model
===========================

o Real-Address Mode 
'''''''''''''''''''
    - Only 1MB of memory can be addressed 
    - From 00000 to FFFFF
    - Processor can run only one program at a time
    - Application programs can access any memory location

o Protected Mode 
''''''''''''''''
    - Processor can run multiple programs at a time
    - Each running program is assigned 4GB of memory
    - Programs cannot access each other's code and data.

o Virtual - 8086 Mode
'''''''''''''''''''''
    - Processor create a virtual 8086 machine with its own 1MB address space

Example:
ds = 0x700

mov [0xff], 0x30

Output:
    reg 0x700:0x00ff = 0x30

*Linear address: base * 16 + offset = 0x700 * 16 + 00ff = 0x70ff*

Example:
ds = 0x700

mov ax, 0x300
mov ds, ax
mov [0xff], 0x30

Output:
    reg 0x300:0x00ff = 0x30

Example:
jmp 0x7c0:0xff ; change value of CS (=0x7c0) and IP (=0xff) 

Stack, Subroutines
''''''''''''''''''

org 100h
    
_main:
    call _test
    mov ah, 0x20

_test:
    mov ah, 0x10
    ret
