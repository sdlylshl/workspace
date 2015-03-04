#include "stdio.h"
#include "unicodeToGB2312.h"

char Zn[]="֣����ѧ";

uint16_t UnicodeTemp[10];
uint8_t Buf[20];

void main(void)
{ 
	uint16_t *pZn;
	uint16_t unicode_temp;
	pZn=(uint16_t *)Zn;

	GB2312ToUnicode_Str(UnicodeTemp,"֣����ѧ");
	NetworkByteOrder(Buf,UnicodeTemp,sizeof("³����ѧ")-1);

	unicode_temp=GB2312ToUnicode(*pZn);	//֣��GB2312����0xD6A3  unicode��0x90D1
	printf("Unicode:%02X\t\t",unicode_temp);

	unicode_temp=UnicodeToGB2312(unicode_temp);
	printf("GB2312:%02X\n",unicode_temp);

}