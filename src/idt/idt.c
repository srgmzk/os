/*
 * =====================================================================================
 *
 *       Filename:  idt.c
 *
 *    Description Interrupt Description Table implementation
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "idt.h"
#include "config.h"
#include "memory/memory.h"
#include "kernel.h"
#include "io/io.h"

struct idt_desc idt_descriptors[OS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc *ptr);
extern void int21h();
extern void no_interrupt();

void
int21h_handler()
{
	print("Keyboard pressed\n");
	outb(0x20, 0x20);
}

void
no_interrupt_handler()
{
	//print("no interrupt\n");
	outb(0x20, 0x20);
}


void
idt_zero()
{
	print("Divide by zero error\n");
}

/*
	IDT Entr, Interrupt Gates
 													 1    1 1 	  0        1 1 1 0
	+------------+-------+---------------------+     |  DPL = 3   |		Gate Type (0xE)	
	| Name		 | Bit 	 | Full Name		   |     | (UserRing) +		80386 32 bit interrupt gate
	+------------+-------+---------------------+     +     		 /			   +
	|   Offset   | 48-63 | Offset 2			   |    /      		/			  /	
	+------------+-------+---------------------+   /      	   /			 /
	|	  P		 |   47	 | Present			   | -+	     +----+	  			/	
	+------------+-------+---------------------+        / S must be 0	   /
	|	 DPL	 | 45,46 | Descriptor Priv Lvl |       /  for int and	  /
	+------------+-------+---------------------+      /	  traps			 /
	|	  S		 |  44	 | Storage Segment	   | ----+					/
	+------------+-------+---------------------+					   /
	|	Type	 | 40-43 | Gate tipes	  	   | ---------------------+
	+------------+-------+---------------------+
	| 	 0       | 32-39 | Unused			   |
	+------------+-------+---------------------+
	|  Selector	 | 16-31 | Selector			   |
	+------------+-------+---------------------+
	|   Offset	 |  0-15 | Offset 1			   |
	+------------+-------+---------------------+
*/

void
idt_set(int interrupt_no, void *address)
{
	struct idt_desc *desc = &idt_descriptors[interrupt_no];
	desc->offset_1 = (uint32_t)address & 0x0000ffff;
	desc->selector = KERNEL_CODE_SELECTOR;
	desc->zero = 0x00;
	desc->type = 0xEE; // 11101110  - see example ^
	desc->offset_2 =(uint32_t)address >> 16; // higher part of the offset
}



void 
idt_init()
{
	memset(idt_descriptors, 0, sizeof(idt_descriptors));	 
	idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
	idtr_descriptor.base = (uint32_t)idt_descriptors;

	for (int i=0; i < OS_TOTAL_INTERRUPTS; i++)
	{
		idt_set(i, no_interrupt);
	}

	idt_set(0, idt_zero);	
	idt_set(0x21, int21h);

	// Load the interrupt descriptor table
	idt_load(&idtr_descriptor);
}
