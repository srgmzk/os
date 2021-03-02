/*
 * =====================================================================================
 *
 *       Filename:  io_req.c
 *
 *    Description:  
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
#include <linux/ioport.h>
#include <asm/io.h>

#define MY_BASEPORT 0x0059
#define NUMBER_PORTS 2

MODULE_LICENSE("GPL");

static int mod_init(void)
{
	if (!request_region(MY_BASEPORT, NUMBER_PORTS, "myports")) {
		pr_info("request region  failed for myports\n");
			
	} else {
		
		pr_info("request region  success for myports\n");
		outb(0xa, MY_BASEPORT);
	}
	return 0;
}

static void mod_exit(void)
{
	unsigned int a;
	a = inb(MY_BASEPORT);
	pr_info("Value at %02x is %02x\n", MY_BASEPORT, a);
	release_region(MY_BASEPORT, NUMBER_PORTS);
}

module_init(mod_init);
module_exit(mod_exit);
/*Module information*/
#define AUTHOR_NAME "MOS"
#define MODULE_DESC "HELLOWORLD"

MODULE_AUTHOR(AUTHOR_NAME);
MODULE_DESCRIPTION(MODULE_DESC);
MODULE_LICENSE("GPL");
