/*
 * =====================================================================================
 *
 *       Filename:  io_req.c
 *
 *    Description: port 0x61 - speaaker. 
		Enable speaker : switch on bit 0 and 1 on port 0x61
		Disable speaker: write 0x00 on port 0x61
 *
 *        Version:  1.0
 *        Created:  25.02.2021 20:46:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h> // outb, inb
#include <linux/delay.h>


static int mod_init(void)
{
	printk("speaker mod\n");
	outb(0x03, 0x0061);
	ssleep(3);
	outb(0x00, 0x0061);
	return 0;
}

static void mod_exit(void)
{
}

module_init(mod_init);
module_exit(mod_exit);
/*Module information*/
#define AUTHOR_NAME "MOS"
#define MODULE_DESC "HELLOWORLD"

MODULE_AUTHOR(AUTHOR_NAME);
MODULE_DESCRIPTION(MODULE_DESC);
MODULE_LICENSE("GPL");
