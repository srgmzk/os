/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.02.2021 15:14:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08 // CODE_SEG
#define KERNEL_DATA_SELECTOR 0x10 // DATA_SEG
#define OS_TOTAL_INTERRUPTS 512 //0x200

//100MB heap size
#define OS_HEAP_SIZE_BYTES 104857600
#define OS_HEAP_BLOCK_SIZE 4096
#define OS_HEAP_ADDRESS 0x01000000
#define OS_HEAP_TABLE_ADDRESS 0x00007E00

#define OS_SECTOR_SIZE 512 

#endif
