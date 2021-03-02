o Allows hardware to interrupt the processor state
    - The programmable interrupt controller allows different types of hardware to interrupt the processor such
        as the hard disk, keyboard and more
o Programmable
o Requires interrupt acknowledges

- IRQ's are mapped to a starting interrupt for example lets choose 0x20
- IRQ 0 would be interrupt 0x20
- IRQ 1 would be interrupt 0x21
- IRQ 2 would be interrupt 0x22

By default some of the IRQ's are mapped to interrupts 8-15 this is a problem as these interrupts are reserved
in protected mode for exceptions so we are required to remap the PIC (Programmable Interrupt Controller)

o The system has two PIC one for master ports and the other for slave ports
o The master hadnles IRQ 0-7
o The slave handles IRQ 8-15

PIC Control Ports:
o 0x20 and 0x21 = Master IRQ's
o 0xA0 and 0xA1 = Slave IRQ's

Remapping the Master PIC
-------------------------

o You must let the PIC controller know when you have handled the interrupt


..code ::
    
    setup_pic:
        ; Initialze some flags in the PIC's
        mov al, 00010001b ; b4=1: Init; b3=0: Edge; b1=0: Cascade; b0=1: Need 4th init step
        out 0x20, al      ; Tell master

        mov al, 0x20      ; Tell IRQ0 should be on INT 0x20 (Just after Intel exception)
        out 0x21, al      ;

        mov al, 00000001b ; b4=0: FNM; b3-2=00: Master/Slave set by hw; b1=0: Not AEOI; b0=1: x86 mode
        out 0x21, al      ;

        ret

