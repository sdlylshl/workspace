/*
 ============================================================================
 Name        : Unicode2GB2312.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "GB2312_UNICODE.h"
uint16_t sz;

uint8_t IsBigEndian(void) {
	uint16_t BigEndian = 0x0100;
	return (*(uint8_t *) (&BigEndian));
}

//大端存储  10 00
//大端存储  00 01
//value= 0x0100
static inline wchar_t get_16(const unsigned char *s, int isbigendian)
{
	isbigendian &= 1;
	return s[isbigendian^1]<<8 | s[isbigendian];
}

static inline void put_16(unsigned char *s, wchar_t c, int isbigendian)
{
	isbigendian &= 1;
	s[isbigendian^1] = c>>8;
	s[isbigendian] = c;
}
/*******************************************************************************
 * Function Name  : UnicodeToGB2312
 * Description    : This function convert unicode to gb2312 code
 * Input          : unicode--the unicode value
 * Output         : None
 * Return         : gb2312 code value
 *******************************************************************************/
uint16_t UnicodeToGB2312_BinarySearch(uint16_t unicode) //用二分查找算法
{
	uint32_t mid, low, high, len;
	len = sizeof(UnicodeToGB2312_Tab) / sizeof(UnicodeToGB2312_Tab[0]);
	low = 0;
	high = len - 1;
	if (unicode < 0xA4)
		return unicode;
	while (low <= high) {
		mid = (low + high) / 2;
		if (UnicodeToGB2312_Tab[mid][0] > unicode)
			high = mid - 1;
		else if (UnicodeToGB2312_Tab[mid][0] < unicode)
			low = mid + 1;
		else
			return UnicodeToGB2312_Tab[mid][1];
	}
	return 0; //没找到
}
uint16_t GB2312ToUnicode_BinarySearch(uint16_t gb2312) //用二分查找算法
{
	uint32_t mid, low, high, len;
	len = sizeof(GB2312ToUnicode_Tab) / sizeof(GB2312ToUnicode_Tab[0]);
	low = 0;
	high = len - 1;
	if (gb2312 < 0xA4)
		return gb2312;
	while (low <= high) {
		mid = (low + high) / 2;
		if (GB2312ToUnicode_Tab[mid][0] > gb2312) {
			high = mid - 1;
		} else if (GB2312ToUnicode_Tab[mid][0] < gb2312) {
			low = mid + 1;
		} else{
			return GB2312ToUnicode_Tab[mid][1];
		}
	}
	return 0; //没找到
}
uint16_t GB2312ToUnicode(uint16_t gbk) {
	uint32_t low, high, len;
	len = sizeof(UnicodeToGB2312_Tab) / sizeof(UnicodeToGB2312_Tab[0]);
	low = 0;
	high = len - 1;

	while (low <= high) {
		if (UnicodeToGB2312_Tab[low][1] == gbk) {
			return UnicodeToGB2312_Tab[low][0];
		}
		low++;
	}
	return 0; //没找到
}

/**
 对GB2312编码
 */
void GB2312ToUnicode_Str(uint16_t * const pOutUnicodeStr, uint8_t * const pGB2312Str) {

	uint8_t *pChar;
	uint16_t *pGb2312;
	uint16_t *pUnicode;
	uint16_t temp;
	pChar = pGB2312Str;
	pUnicode = pOutUnicodeStr;

	if (IsBigEndian()) {
		while (*pChar) {
			pGb2312 = (uint16_t *) pChar;
			*pUnicode = GB2312ToUnicode(*pGb2312);
			pUnicode++;
			pChar += 2;
		}
		pUnicode = 0;
	} else {
		while (*pChar) {
			temp = *pChar++ << 8;
			temp |= *pChar;
			*pUnicode = GB2312ToUnicode(temp);
			pUnicode++;
			pChar++;
		}
		pUnicode = 0;
	}
}

/**
 对16位的数组转换成网络字节顺序大端模式（即高字节在低地址）
 */
int16_t NetworkByteOrder(uint8_t * const pOut, uint16_t * const pIn,
		uint16_t const nByte) {
	uint8_t *pChar;
	uint16_t i;
	uint16_t j = 0;
	if (nByte % 2 != 0)
		return -1;  //字节数必须是2的倍数

	if (IsBigEndian()) {
		pChar = (uint8_t *) pIn;
		for (i = 0; i < nByte; i++) {
			pOut[i] = *pChar++;
		}
	} else {
		for (i = 0; i < (nByte / 2); i++) {
			pOut[j++] = pIn[i] >> 8;
			pOut[j++] = pIn[i] & 0x00FF;
		}

	}

	return nByte;
}





char * str = "你好";
int main(void) {
	sz = GB2312ToUnicode_Tab[500][1];
	printf("%x\n", str[0]);
	printf("%x\n", str[1]);
	printf("%x\n", str[2]);
	printf("%x\n", str[3]);
	printf("%x\n", str[4]);
	printf("%x\n", str[5]);
	printf("%x\n", str[6]);
	printf("大端模式 %x\n", IsBigEndian());
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
