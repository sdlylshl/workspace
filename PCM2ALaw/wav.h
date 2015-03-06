/*******************************************************
*	��������ҵĲ��͡�JRTPLIB@Conference DIY��Ƶ����ϵͳ��
*	��д��һ���׶���ʵ�顣
*	���ߣ��븻�� tinnal
*	���䣺tinnal@163.com
*	���ͣ�www.cnitblog.com/tinnal/
*	Ŀ�ڣ�2009-01-03
*	�汾��1.00
*********************************************************/

#ifndef _WAV_H_
#define _WAV_H_

#include "types.h"

#pragma pack(1)

struct RIFF_HEADER
{
	U8		szRiffID[4];  // 'R','I','F','F'
	U32		dwRiffSize;
	U8		szRiffFormat[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT
{
	U16		wFormatTag;
	U16		wChannels;
	U32		dwSamplesPerSec;
	U32		dwAvgBytesPerSec;
	U16		wBlockAlign;
	U16		wBitsPerSample;
	U16		pack;		//������Ϣ
};
struct FMT_BLOCK
{
	U8		szFmtID[4]; // 'f','m','t',' '
	U32		dwFmtSize;
	struct	WAVE_FORMAT wavFormat;
};

struct FACT_BLOCK
{
	U8		szFactID[4]; // 'f','a','c','t'
	U32		dwFactSize;
};

struct DATA_BLOCK
{
	U8		szDataID[4]; // 'd','a','t','a'
	U32		dwDataSize;
};


#endif