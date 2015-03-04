#include "stdio.h"
#include "unicodeToGB2312.h"

char Zn[]="郑东大学";

uint16_t UnicodeTemp[10];
uint8_t Buf[20];

void main(void)
{ 
	uint16_t *pZn;
	uint16_t unicode_temp;
	pZn=(uint16_t *)Zn;

	GB2312ToUnicode_Str(UnicodeTemp,"郑东大学");
	NetworkByteOrder(Buf,UnicodeTemp,sizeof("鲁东大学")-1);

	unicode_temp=GB2312ToUnicode(*pZn);	//郑的GB2312吗是0xD6A3  unicode是0x90D1
	printf("Unicode:%02X\t\t",unicode_temp);

	unicode_temp=UnicodeToGB2312(unicode_temp);
	printf("GB2312:%02X\n",unicode_temp);

}