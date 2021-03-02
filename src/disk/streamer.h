/*
 * =====================================================================================
 *
 *       Filename:  streamer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02.03.2021 22:35:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef DISKSTREAMER_H
#define DISKSTREAMER_H

#include "disk.h"

struct disk_stream
{
	int pos;
	struct disk *disk;
};

struct disk_stream *diskstreamer_new(int disk_int);
int diskstreamer_seek(struct disk_stream *stream, int pos);
int diskstreamer_read(struct disk_stream *stream, void *out, int total);
void diskstreamer_close(struct disk_stream *stream);

#endif
