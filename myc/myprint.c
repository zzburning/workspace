/*
 * myprint.c
 *
 *  Created on: 2011-4-1
 *      Author: root
 */

#include "myprint.h"

int myprintf(char *fmt,...)
{
	va_list ap;
	char string[256];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	printf("\033[0;31m");
	printf(string);
	printf("\033[0m\n");
	va_end(ap);
	return 0;
}

