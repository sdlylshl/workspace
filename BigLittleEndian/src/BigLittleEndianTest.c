/*
 ============================================================================
 Name        : BigLittleEndian.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
unsigned int  OSEndiannessTest    = 0x12345678;               /* Variable to test CPU endianness     */
//大端：(Big-Endian)       就是把数值的高位字节放在内存的低位地址上
//小端：(Little-Endian)    就是把数值的高位字节放在内存的高位地址上
//地址:   0x0000    0x0001    0x0002    0x0003
//大端:   0x12       0x34      0x56      0x78
//小端:   0x78       0x56      0x34      0x12
int main(void) {
	 unsigned char * pch;
	 pch = (unsigned char *)&OSEndiannessTest;
//	 pch+=3;
	printf("0x%x\n",OSEndiannessTest);
	printf("0x%x\n",*pch);
    
    if(*pch == 0x12)
        puts("!!!Big-Endian!!!\n");
    else
        puts("!!!Little-Endian!!!");
        
//	puts("!!!Test End!!!"); /* prints !!!Hello World!!! */

	return EXIT_SUCCESS;
}
