/*
 * crc-ccitt.h
 *
 *  Created on: 2011-9-6
 *      Author: Administrator
 */
#include "..\def.h"
#ifndef CRC_CCITT_H_
#define CRC_CCITT_H_

extern u16 const crc_ccitt_table[256];

extern u16 crc_ccitt(u32 crc, const u8 *buffer, int len);

static inline u16 crc_ccitt_byte(u16 crc, const u8 c)
{
	return (crc >> 8) ^ crc_ccitt_table[(crc ^ c) & 0xff];
}
#endif /* CRC_CCITT_H_ */
