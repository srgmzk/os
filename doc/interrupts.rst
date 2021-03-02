o Interrupts are like subroutines, but you don't need to know the memory address to invoke them
o Interrupts are called through the use of interrupt numbers rather than memory address
o Interrupts can be setup by the programmer. For example you could set up interrupt "0x32" and have
    it point to you code. Then when someone does "int 0x32" it will invoke your code

What happens when you invoke an interrupt?
- Process is interrupted 
- Old state saved (pushed) on the stack
- Interrupt executed

Interrupt Vector Table Explained

- Table describes 256 interrupt handlers
- Entries contain 4 bytes (offset:segment)
- Interrupts are in numerical order in the table

offset | segment | offset | segment | 
-------+---------+--------+---------+
 0x00  | 0x7c0   | 0x8d00 | 0x00    |
2bytes | 2bytes  | 2bytes | 2bytes  | ...

int 0 = address 0x00
int 1 = address 0x04
int 2 = address 0x08

...

int 0x13 = 0x46 ( 76 dec )

int 0x13 -> processor look at offset 76 in RAM

76 - 77 = Offset
78 - 79 = Segment

Interrup Descriptor Table (IDT)
'''''''''''''''''''''''''''''''

- Describes how interrupts are invoked in protected mode
    - Similarly to the interrupt vector table the interrupt descriptor table describes how interrupts are
        setup in the CPU so that if someone causes an "int 5" it will invoke the code for interrupt 5 as 
        described by the interrupt descriptor table.
- Can be mappend anywhere in memory
- Different from the interrupt vector table

*Interrupt descriptor*

    31                                                                               0
    [                             HAlways 0 (reserved)                               ]

    31                                                                               0
    [                             Handler Address bits 63:32                         ]

    31                                      16 15 14 13 12 11       8  7        2   0
    [       handler address bits  31:16       ][P][DPL][0][   Type   ][ 00000 ][ IST ]

    31                                      16  15                                   0
    [   segment selector                      ][        handler address bits 15:0    ]


- DPL - Descriptor Privelege Level - The ring level the processor requires to call this interruot
- Type - The type of gate this interrupt is treated as. 
  Вентиль - это адрресс защищенного режима x86, состоящий из селектора, отступа и уровня доступа 
    Вентиль предназначен для передачи программного управления. Три типа вентилей в IDT включают:
        o System - когда управление передается другой задаче
        o Interrupt - управление передается в обработчик прерывания с отключенными прерываниями.
        o Trap - управление передается в обработчик прерывания без выключения прерываний.

Interrupt Description Structure

..code ::
    struct idt_desc
    {
        uint16_t offset_1; // offset bits 0..15
        uint16_t selector;  // a code segment selector in GDT or LDT
        uint8_t zerol       // unused, set to 0
        uint8_t type_attr;  // type and attributes, see below
        uint16_t offset_2;  // offset bits 16..31
    } __attributes__((packed));


Interrupt Descriptor Array
--------------------------

    [int desc 0][int desc 1][int desc 2][...]

    struct idt_desc idt_desc[COS32_MAX_INTERRUPTS];

    Interrupt descriptor are stored in an array with index 0 defining interrupt zero "int 0".
    Index 1 defining interrupt one "int 1" and so on.

IDTR
----

    Limit   0-15    The length of the descriptor table - 1
    Base    16-47   The address of the Interrupt Descriptor Table

    struct idtr_desc
    {
        uint16_t limit;
        uint32_t base;
    }__attribute__((packed));
