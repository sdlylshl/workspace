/*
 ============================================================================
 Name        : aa.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MIN(A,B) ((A)<(B)?(A):(B))

int main(void) {
	char b = 5;
	char * a = &b;
	char d= 10;
	char c = MIN((*a)++,d);

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
