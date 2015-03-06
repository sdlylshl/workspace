
#ifndef _WAV_H_
#define _WAV_H_

#include "stdint.h"

#pragma pack(1)

typedef struct RIFF_HEADER {
//	uint8_t szRiffID[4];  // 'R','I','F','F'
	uint32_t szRiffID;
	uint32_t dwRiffSize;
//	uint8_t szRiffFormat[4]; // 'W','A','V','E'
	uint32_t szRiffFormat;
}RIFF_HEADER_t;

typedef struct FMT_BLOCK {
//	uint8_t szFmtID[4]; // 'f','m','t',' '
	uint32_t szFmtID;
	uint32_t dwFmtSize;
//	WAVE_FORMAT_t wavFormat;
}FMT_BLOCK_t;

typedef struct WAVE_FORMAT {
	uint16_t wFormatTag;		//编码格式 [1].PCM/uncompressed [2].Microsoft ADPCM [6].ITU G.711 a-law [7].ITU G.711 Âµ-law 17.IMA ADPCM [20]. ITU G.723 ADPCM (Yamaha) [49].GSM 6.10 [64].ITU G.721 ADPCM [80].MPEG
	uint16_t wChannels;			//声道
	uint32_t dwSamplesPerSec;	//采样频率
								//比特率=播放速率*8/1000(kbs)
	uint32_t dwAvgBytesPerSec;	//播放速率B/s = 采样频率 *声道数*采样位数/8 = 采样频率 *采样字节数
	uint16_t wBlockAlign;		//采样字节数  = 声道数*采样位数/8
	uint16_t wBitsPerSample;	//采样位数
	uint16_t pack;		//附加信息
}WAVE_FORMAT_t;


typedef struct FACT_BLOCK {
//	uint8_t szFactID[4]; // 'f','a','c','t'
	uint32_t szFactID;
	uint32_t dwFactSize;
//	uint8_t factdata[dwFactSize];
}FACT_BLOCK_t;

typedef struct DATA_BLOCK {
//	uint8_t szDataID[4]; // 'd','a','t','a'
	uint32_t szDataID;
	uint32_t dwDataSize;
}DATA_BLOCK_t;
typedef struct WAVE{
    FILE         	*fp;
    RIFF_HEADER_t   riff;
    FMT_BLOCK_t 	fmt;
    WAVE_FORMAT_t 	wave;
    FACT_BLOCK_t	fact;
    DATA_BLOCK_t	data;
    uint32_t	bit_rate;
    uint32_t    file_size;
    uint32_t    data_offset;
}WAVE_t;

WAVE_t *wav_open(char *file_name);

#endif
