/*
 ============================================================================
 Name        : CRC.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/*
 *==========================================================================
 *
 *      crc16.c
 *
 *      16 bit CRC with polynomial x^16+x^12+x^5+1
 *
 *==========================================================================
 *####ECOSGPLCOPYRIGHTBEGIN####
 * -------------------------------------------
 * This file is part of eCos, the Embedded Configurable Operating System.
 * Copyright (C) 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.
 * Copyright (C) 2002 Gary Thomas
 *
 * eCos is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 or (at your option) any later version.
 *
 * eCos is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with eCos; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * As a special exception, if other files instantiate templates or use macros
 * or inline functions from this file, or you compile this file and link it
 * with other works to produce a work based on this file, this file does not
 * by itself cause the resulting work to be covered by the GNU General Public
 * License. However the source code for this file must still be made available
 * in accordance with section (3) of the GNU General Public License.
 *
 * This exception does not invalidate any other reasons why a work based on
 * this file might be covered by the GNU General Public License.
 *
 * Alternative licenses for eCos may be arranged by contacting Red Hat, Inc.
 * at http: *sources.redhat.com/ecos/ecos-license/
 * -------------------------------------------
 *####ECOSGPLCOPYRIGHTEND####
 *==========================================================================
 *#####DESCRIPTIONBEGIN####
 *
 * Author(s):    gthomas
 * Contributors: gthomas,asl
 * Date:         2001-01-31
 * Purpose:
 * Description:
 *
 * This code is part of eCos (tm).
 *
 *####DESCRIPTIONEND####
 *
 *==========================================================================
 */

//#include "crc.h"
//typedef unsigned short int U16;

#define U16 unsigned short
#define U32 unsigned int

//****************************************************************



#include <stdio.h>
#include <stdlib.h>
char bude[10]={0x1,0x3,0x00,0x0,0x0,0x64,0x44,0x21};
char bude1[10]={0x1,0x4,0x00,0x0,0x0,0x1e,0x70,0x02};
//char *budes=0x14;
int main(void) {
	U32 a,b,b2,b3,c,d,e,f;
	U32 i;
	i=~0;
	printf("cyg_crc16  is a 0x%x\n",i);
//crc_modbus1 为变频器自带的CRC校验程序。多项式 0xa001 反向多项式8005 高位在前，低位在后。
//crc_modbus2 来自于PIC485 我的毕业设计,高底位与另两个相反 。多项式为 0xa001
//crc_modbus2 来自于Uboot 同crc_modbus1
	b=crc_modbus1(0xffff,bude,6);
	b2=crc_modbus2(bude,6);
	b3=crc_modbus3(0xFFFF,bude,6);

	a=cyg_crc16(bude,1);
	c=calcrc16(bude,1);
	//d=crc16_(bude,1);
	e=crc_ccitt(0,bude,1);
	f=crc_itu_t(0,bude,1);
	printf("modbus     is 1 0x%x\n",b);
	printf("modbus2    is 2 0x%x\n",b2);
	printf("modbus3    is 3 0x%x\n",b3);

	printf("cyg_crc16  is a 0x%x\n",a);
	printf("calcrc16   is c 0x%x\n",c);
	printf("crc_itu_t  is f 0x%x\n",f);

	printf("crc_ccitt  is e 0x%x\n",e);
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	return EXIT_SUCCESS;
}
