/*
 ============================================================================
 Name        : HexToDec.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define  U32 unsigned long

void HexToDec( unsigned char*ps,unsigned long src) {
	//��λ�ڸ߶ˣ���λ�ڵ͵�ַ�� С��ģʽ
	char *s = ps;
	while(src>0){
		*s++=src%10;
		src/=10;
		printf("%d\n",*(s-1));
	}
}
//
U32 HexToBCDL(U32 src) {
	//��λ�ڵͶˣ�С��ģʽ
	//src=0x81
	//ת����ʮ����129
	//ת��BCD�� 0x129
	U32 tmp=0;
	char i=0;
	for(;src>0;i+=4){
		tmp|=(src% 10)<<i;
		src/=10;
	}
	return tmp;
}

U32 HexToBCD(U32 src) {
	//��λ�ڸ߶� �����ģʽ
	//src=0x81
	//ת����ʮ����129
	//ת��BCD�� 0x921
	U32 tmp=0;
	while(src>0){
		tmp|=(src% 10);
		if(src>10)
			tmp<<=4;
		src/=10;
	}
	return tmp;
}
//printf("%d\n",i);
//	printf("%d\n",tmp);

int main(void) {
//	char *dec;
//	HexToDec(dec,999999);
 U32 sd,sd1;

	sd1=HexToBCDL(0x81);
	sd=HexToBCD(0x81);
	printf("%d\n",sd1);
	printf("%d\n",sd);
//	printf("%d\n",1<<4);
//	printf("%d\n",(4)<<4);
//	printf("%d\n",(1<<4)<<4);
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
