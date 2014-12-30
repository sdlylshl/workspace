/*
 ============================================================================
 Name        : arry.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
unsigned long GPS_ID = 0x12345600;
char  GPS_CMD0;
unsigned char GPS_CMD1 = 0xB2;
unsigned long GPS_HeartIndex = 0x00000001;
unsigned char GPS_SendBuff[100];

unsigned char * arry;
char * arr;
int i = 0;
int main(void) {


	arry = GPS_SendBuff;
	arr=(char*)&GPS_ID;
    for(i=0;i<4;i++){
    	GPS_SendBuff[9-i] =(char)(GPS_ID>>(8*i)&0xFF);
    }
	for(i=0;i<12;i++)
				printf("%x \n",GPS_SendBuff[i]);
	printf("%d \n",sizeof(GPS_SendBuff));
	return EXIT_SUCCESS;
while(1);
	GPS_CMD0=0x4;
	arry = (unsigned char *)&GPS_CMD0;
//	printf("%d \n",arry);
	printf("%d \n",(*arry));
	*arry = 74;
	printf("%d \n",(GPS_CMD0));
	//GPS_SendBuff++;
	//unsigned char * GPS_SendBuff = GPS_CMD0;
	//unsigned char * GPS_SendBuff = GPS_CMD1;
	//unsigned long * GPS_SendBuff = GPS_HearIndex;

	arry = GPS_SendBuff;
	for(i=0;i<50;i++)
		arry[i]=i;

	for(i=0;i<60;i++)
		printf("%d \n",GPS_SendBuff[i]);

	//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
