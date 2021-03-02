/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01.03.2021 23:04:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "string.h"

int strlen(const char *ptr)
{
	int i = 0;
	while(*ptr != 0)
	{
		i++;
		ptr += 1;
	}
	return i;
}

int strnlen(const char *ptr, int max)
{
	int i = 0;
	for(i = 0; i < max; i++)
	{
		if (ptr[i] == 0)
		{
			break;
		}
	}
	return i;
}

bool isdigit(char c)
{
	return c >= 48 && c <=57;
}

int tonumericdigit(char c)
{
	return c - 48;
}




