/*
 * =====================================================================================
 *
 *       Filename:  kernel.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.02.2021 01:27:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "string/string.h"
#include "disk/disk.h"
#include "disk/streamer.h"
#include "fs/pparser.h"

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t
terminal_make_char(char c, char colour)
{
	return (colour << 8) | c;
}

void
terminal_putchar(int x, int y, char c, char colour)
{
	 video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void
terminal_writechar(char c, char colour)
{
	if (c == '\n') {
		terminal_row += 1;
		terminal_col = 0;
		return;
	}
	terminal_putchar(terminal_col, terminal_row, c, colour);
	terminal_col += 1;
	if (terminal_col >= VGA_WIDTH)
	{
		terminal_col = 0;
		terminal_row += 1;
	}
	
}


void
terminal_initialize()
{
	video_mem = (uint16_t *)(0xB8000);
	for (int y = 0; y < VGA_HEIGHT; y++)
	{
		for (int x = 0; x < VGA_WIDTH; x++)
		{
			terminal_putchar(x, y, ' ', 0);
		}
	} 
}

void
print(const char* str)
{
	size_t len = strlen(str);
	for (int i = 0; i<len; i++) {
		terminal_writechar(str[i], 15);
	}
}

extern void test_problem();

static struct paging_4gb_chunk *kernel_chunk = 0;

void kernel_main()
{
	terminal_initialize();
	print("hello worlld!\ntest");
	// init heap
	kheap_init();	
	
	//search and init the disks
	disk_search_and_init();
	

	idt_init();

	kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

	//switch to kernel paging chunk
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

	enable_paging();

	enable_interrupts();

	//struct path_root *root_path = pathparser_parse("0:/bin/shell.exe", NULL);
	
	struct disk_stream *stream = diskstreamer_new(0);
	diskstreamer_seek(stream, 0x201);
	unsigned char c = 0;
	diskstreamer_read(stream, &c, 1);
	while(1) {}

}
