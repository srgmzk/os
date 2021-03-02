/*
 * =====================================================================================
 *
 *       Filename:  string.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01.03.2021 23:05:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
int strlen(const char *ptr);
int strnlen(const char *ptr, int max);
bool isdigit(char c);
int tonumericdigit(char c); 

#endif
