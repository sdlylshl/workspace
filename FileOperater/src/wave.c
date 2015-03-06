/*
 * wave.c
 *
 *  Created on: 2015年3月6日
 *      Author: star
 */
#include "stddef.h"
#include <stdint.h>
#include "stdio.h"
#include <stdlib.h>
#include "wave.h"
const uint8_t CHWAV_RIFF[4] = { 0x52, 0x49, 0x46, 0x46 };
const uint8_t CHWAV_WAVE[4] = { 0x57, 0x41, 0x56, 0x45 };
const uint8_t CHWAV_FMT[4] = { 0x66, 0x6D, 0x74, 0x20 };
const uint8_t CHWAV_FACT[4] = { 0x66, 0x61, 0x63, 0x74 };
const uint8_t CHWAV_DATA[4] = { 0x64, 0x61, 0x74, 0x61 };

#if Big-Endian
// 大端模式
const uint32_t DWWAV_RIFF = 0x52494646;
const uint32_t DWWAV_WAVE = 0x57415645;
const uint32_t DWWAV_FMT = 0x666D7420;
const uint32_t DWWAV_FACT = 0x66616374;
const uint32_t DWWAV_DATA = 0x64617461;

#else
// 小端模式 Windows ARM 默认模式
const uint32_t DWWAV_RIFF = 0x46464952;
const uint32_t DWWAV_WAVE = 0x45564157;
const uint32_t DWWAV_FMT = 0x20746D66;
const uint32_t DWWAV_FACT = 0x74636166;
const uint32_t DWWAV_DATA = 0x61746164;
#endif

uint8_t IsBigEndian(void) {
	uint16_t BigEndian = 0x0100;
	return (*(uint8_t *) (&BigEndian));
}
void wav_close(WAVE_t **wav) {
	WAVE_t *tmp_wav;
	if (NULL == wav) {
		return;
	}

	tmp_wav = *wav;
	if (NULL == tmp_wav) {
		return;
	}

	if (NULL != tmp_wav->fp) {
		fclose(tmp_wav->fp);
	}
	free(tmp_wav);

	*wav = NULL;
}
WAVE_t *wav_open(char *file_name) {
	WAVE_t *wav = NULL;
	uint32_t read_len = 0;
	uint8_t buffer[256];
	uint32_t *bufid;
	uint8_t endian;
	uint8_t isfact = 0;
	if (NULL == file_name) {
		printf("file_name is NULL\n");
		return NULL;
	}

	wav = (WAVE_t *) malloc(sizeof(WAVE_t));

	if (NULL == wav) {
		printf("malloc wav failed\n");
		return NULL;
	}

	//    memset(wav, sizeof(WAVE_t));

	wav->fp = fopen(file_name, "rb+");
	if (NULL == wav->fp) {
		printf("fopen %s failed\n", file_name);
		free(wav);
		return NULL;
	}
	endian = IsBigEndian();
	//成功获取文件 wav解析

	//1. RIFF WAVE chunk
	read_len = fread(buffer, 1, sizeof(RIFF_HEADER_t), wav->fp);
//	printf(" sizeof(RIFF_HEADER_t) %d\n", sizeof(RIFF_HEADER_t));	printf(" read_len %d\n", read_len);
	if (read_len == sizeof(RIFF_HEADER_t)) {
		//RIFF
		if (*(uint32_t *) buffer == DWWAV_RIFF) {
			wav->riff.szRiffID = DWWAV_RIFF;
			wav->riff.dwRiffSize = *(uint32_t *) (buffer + 4);
			wav->file_size = wav->riff.dwRiffSize + 8;
			printf("文件大小: %d\n", wav->file_size);
		} else {
			printf("RIFF标志错误\n");
			return NULL;
		}
		if (*(uint32_t *) (buffer + 8) == DWWAV_WAVE) {
			wav->riff.szRiffFormat = DWWAV_WAVE;
		} else {
			printf("WAVE标志错误\n");
			return NULL;
		}
		wav->data_offset = sizeof(RIFF_HEADER_t);
	} else {
		printf("error wav file\n");
		wav_close(&wav);
		return NULL;
	}

	//2. FMT chunk
	read_len = fread(buffer, 1, sizeof(FMT_BLOCK_t), wav->fp);
	if (read_len == sizeof(FMT_BLOCK_t)) {
		if (*(uint32_t *) buffer == DWWAV_FMT) {
			wav->fmt.szFmtID = DWWAV_FMT;
			wav->fmt.dwFmtSize = *(uint32_t *) (buffer + 4);
		} else {
			printf("FMT标志错误\n");
			return NULL;
		}
		wav->data_offset += sizeof(FMT_BLOCK_t);
	} else {
		printf("read file FMT erro \n");
		wav_close(&wav);
		return NULL;
	}

	//3. WAVE FORMAT chunk
	read_len = fread(buffer, 1, wav->fmt.dwFmtSize, wav->fp);

	if (read_len == wav->fmt.dwFmtSize) {
		wav->wave.wFormatTag = *(uint16_t *) (buffer);
		wav->wave.wChannels = *(uint16_t *) (buffer + 2);
		wav->wave.dwSamplesPerSec = *(uint32_t *) (buffer + 4);
		wav->wave.dwAvgBytesPerSec = *(uint32_t *) (buffer + 8);
		wav->wave.wBlockAlign = *(uint16_t *) (buffer + 12);
		wav->wave.wBitsPerSample = *(uint16_t *) (buffer + 14);
		if (isfact) {
			wav->wave.pack = *(uint16_t *) (buffer + 18);
		} else {
			wav->wave.pack = 0;
		}
		wav->bit_rate = wav->wave.dwAvgBytesPerSec * 8 / 1000;
		printf("比特率: %d kps\n", wav->bit_rate);

		printf("声道Channels: %d\n",wav->wave.wChannels);
		printf("采样频率Samples: %d Hz\n",wav->wave.dwSamplesPerSec);
		printf("采样速率BytesPerSec: %d kB/s\n",wav->wave.dwAvgBytesPerSec/1000 );
		printf("采样字节BlockAlign: %d Byte\n",wav->wave.wBlockAlign);
		printf("采样位数BitsPerSample: %d Bits\n",wav->wave.wBitsPerSample);


		wav->data_offset += wav->fmt.dwFmtSize;
	} else {
		printf("read file WAVE FORMAT erro \n");
		wav_close(&wav);
		return NULL;
	}

	//4. FACT chunk
	if (wav->fmt.dwFmtSize > 0x10) {
		isfact = 1;
	}
	if (isfact) {
		read_len = fread(buffer, 1, sizeof(FACT_BLOCK_t), wav->fp);

		if (read_len == sizeof(FACT_BLOCK_t)) {
			if (*(uint32_t *) buffer == DWWAV_FACT) {
				wav->fact.szFactID = DWWAV_FACT;
				wav->fact.dwFactSize = *(uint32_t *) (buffer + 4);
				printf("fact size %d\n", wav->fact.dwFactSize);
			} else {
				printf("FACT标志错误\n");
				return NULL;
			}

			wav->data_offset += sizeof(FACT_BLOCK_t);
		} else {
			printf("read FACT erro \n");
			wav_close(&wav);
			return NULL;
		}
		//5. FACT DATA chunk
		read_len = fread(buffer, 1, wav->fact.dwFactSize, wav->fp);
		if (read_len ==  wav->fact.dwFactSize) {

			wav->data_offset += wav->fact.dwFactSize;
		} else {
			printf("read fact data erro \n");
			wav_close(&wav);
			return NULL;
		}

	}
	//6. DATA chunk
	read_len = fread(buffer, 1, sizeof(DATA_BLOCK_t), wav->fp);
	if (read_len == sizeof(DATA_BLOCK_t)) {
		if (*(uint32_t *) buffer == DWWAV_DATA) {
			wav->data.szDataID = DWWAV_DATA;
			wav->data.dwDataSize = *(uint32_t *) (buffer + 4);
		} else {
			printf("DATA标志错误\n");
			return NULL;		}
		wav->data_offset +=sizeof(DATA_BLOCK_t);
	} else {
		printf("read  DATA erro \n");
		wav_close(&wav);
		return NULL;
	}

	printf("数据大小:%d 0x%x\n",wav->data.dwDataSize,wav->data.dwDataSize);
	printf("数据偏移:%d 0x%x\n",wav->data_offset,wav->data_offset);
	printf("解析完成");
	return wav;
}

