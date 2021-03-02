/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description: simple kernel module 
 *
 *        Version:  1.0
 *        Created:  09.02.2021 23:24:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/module.h>

/* This func shall be invoked as soon as this LKM is loaded. Note the func prototype */
int hello_world_init_module(void) {
	printk(KERN_INFO "Hello world Module Loaded Successfully\n");
	/* 
	 * A non 0 return means init_module failed; module can't be loaded
	*/
	return 0;
}

/*	
	This function shall be invoked as soon as this LKM is unloaded.
	Note the function prototype 
*/
void hello_world_cleanup_module(void) {
	printk(KERN_INFO "Goodbye hello world LKM\n");
}

/* 
	Tell the kernel which are init and cleanup function for this module. If you do not do this module. 
	If you do not do this registration, kernel would try to use 'init_module' and 'cleanup_module' instead 
*/

module_init(hello_world_init_module);
module_exit(hello_world_cleanup_module);

/*Module information*/
#define AUTHOR_NAME "MOS"
#define MODULE_DESC "HELLOWORLD"

MODULE_AUTHOR(AUTHOR_NAME);
MODULE_DESCRIPTION(MODULE_DESC);
MODULE_LICENSE("GPL");
