/*
 ============================================================================
 Name        : Bytes2String.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//ps[11]=4294967295 4�ֽ����ֵ
void DecToANS( unsigned char*ps,unsigned long src) {
	//��λ�ڸ߶ˣ���λ�ڵ͵�ַ�� С��ģʽ

        char *s = ps+9;
	while(src>0){
		*s-- = src%10 + '0';
		src/=10;

//		printf("%d\n",*(s-1));
	}
}

int main(void) {
int hex =12345;
char a[11]={0};
DecToANS(a,6784);
printf("%x\n",a[6]);
printf("%x\n",a[7]);
printf("%x\n",a[8]);
printf("%x\n",a[9]);
printf("%x\n",a[10]);
	return EXIT_SUCCESS;
}
