/*
 * =====================================================================================
 *
 *       Filename:  disk.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27.02.2021 16:58:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "disk.h"
#include "io/io.h"
#include "config.h"
#include "status.h"
#include "memory/memory.h"

struct disk disk;




int disk_read_sector(int lba, int total, void *buf)
{
	outb(0x1F6, (lba >> 24) | 0xE0);            // Select master drive and pass pasrt of the LBA
	outb(0x1F2, total);                         // Send the total number of sectors we want to read

	outb(0x1F3, (unsigned char)(lba & 0xff));   // 
	outb(0x1F4, (unsigned char)(lba >> 8));     //  Send more of the LBA
	outb(0x1F5, (unsigned char)(lba >> 16));    //

	outb(0x1F7, 0x20);                          // 0x20 = Read command

	unsigned short *ptr = (unsigned short *)buf;
	for (int b = 0; b < total; b++)
	{
		// Wait until buffer is ready
		char c = insb(0x1F7);                   //  
		while (!(c & 0x08))                     // Poll until we are ready to read.
		{                                       // You can also use interrupts if you perfer
			c = insb(0x1F7);                    //
		}

		// Copy from hard disk to memory two bytes at a time
		for (int i = 0; i < 256; i++)           // Read two bytes at a time
		{                                       // into the buffer from the 
			*ptr = insw(0x1F0);                 // ATA controller.
			ptr++;
		}

	}
	return 0;
}


void 
disk_search_and_init()
{
	memset(&disk, 0, sizeof(disk));
	disk.type = OS_DISK_TYPE_REAL;
	disk.sector_size = OS_SECTOR_SIZE;
}

struct disk *
disk_get(int index)
{
	if (index != 0)
		return 0;

	return &disk;
}

int
disk_read_block(struct disk *idisk, unsigned int lba, int total, void *buf)
{
	if (idisk != &disk)
	{
		return -EIO;
	}
	
	return disk_read_sector(lba, total, buf);
}



