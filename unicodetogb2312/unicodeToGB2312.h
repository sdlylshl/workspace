#ifndef _GB2312ToUnicode_H_BAB
#define _GB2312ToUnicode_H_BAB

/* Includes ------------------------------------------------------------------*/
typedef unsigned char uint8_t; 
typedef unsigned short uint16_t; 
typedef unsigned int u32; 	
typedef char s8; 
typedef short s16; 
typedef int s32; 	


uint16_t UnicodeToGB2312(uint16_t unicode);
uint16_t GB2312ToUnicode(uint16_t data);
void GB2312ToUnicode_Str(uint16_t * const pOutUnicodeStr,uint8_t * const pGB2312Str);
s16 NetworkByteOrder(uint8_t * const pOut,uint16_t * const pIn,uint16_t  const nByte);
#endif
