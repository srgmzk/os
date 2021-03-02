/*
 * =====================================================================================
 *
 *       Filename:  memory.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.02.2021 15:18:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
void *memset(void *ptr, int c, size_t size);
int memcmp(void *s1, void *s2, int count);

#endif
