/*
 * =====================================================================================
 *
 *       Filename:  kernel.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.02.2021 01:28:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef KERNEL_H
#define KERNEL_H



#define VGA_WIDTH 80
#define VGA_HEIGHT 20

#define OS_MAX_PATH 108

void kernel_start();
void print(const char* str);

#endif
