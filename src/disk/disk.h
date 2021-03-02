/*
 * =====================================================================================
 *
 *       Filename:  disk.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27.02.2021 16:58:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef DISK_H
#define DISK_H

typedef unsigned int OS_DISK_TYPE;

//Represent a real physical hard disk
#define OS_DISK_TYPE_REAL 0

struct disk 
{
	OS_DISK_TYPE type;
	int sector_size;
};

void disk_search_and_init();
struct disk *disk_get(int index);
int disk_read_block(struct disk *idisk, unsigned int lba, int total, void *buf);
  
#endif
