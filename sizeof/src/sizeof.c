/*
 ============================================================================
 Name        : Sizeof.c
 Author      : star
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


#define	DEFAULT_USER_PARAMS	" user is pow                       "
char * S1="1234567890";
char s[]={1,2,3,4,5,6,7};
typedef struct {
	char flags[12];
	unsigned int val;
} ParamItem; //每个ParamItem占用16字节
typedef struct {
	ParamItem start;
	//ParamItem cpu_clk;
	ParamItem boot_delay;

	ParamItem serial_sel;
	ParamItem AppRun_addr;
	ParamItem serial_baud;

	ParamItem machine;
	ParamItem run_addr;
	ParamItem root_sel;
	ParamItem tty_sel;
	ParamItem display_sel;
	ParamItem display_mode;
	ParamItem initrd_addr;
	ParamItem initrd_len;
	ParamItem mem_cfg;
	//ParamItem devfs_sel;
	//ParamItem osstor;
	ParamItem Lightlev;	//NEW ADD FOR V3
	ParamItem myappsize;	//NEW ADD FOR V3
	ParamItem debug;	//NEW ADD FOR V3
	ParamItem debug2;	//NEW ADD FOR V3
	ParamItem user_params;
	char string[128];
	unsigned int bpage[50];
} BootParams;
BootParams boot_params = {
	//启动设置
	{"auto-run", 3},	//0=boot without parameters,1=boot with parameters
	//{"cpuclk",   2},	//0=200M, 1=300M, 2=400M, 3=440M
	{"rundelay", 0},	//0 seconds
	// 串口设置
	{"serial",   0},	//0=serial port 0, 1=serial port 1
	{"AppRunAddr",   0x32000000},
	{"baudrate", 115200},
	//机器信息设置 for Linux
	{"machine",  913},
	{"runAddr",  0x30201000},
	{"rootfs",   3},
	{"tty",      0},

	{"displayS",  1},	//0=320*240  1=640*480	2 = 800*600
	{"displayM",  0},	//0= lcd	1=vga	2=tv
	{"initrdA",  0x30200000},	//RAM 初始化地址
	{"initrdL",  0x02000000},	//初始化RAM长度
	{"memsize",  0x04000000},	//RAM存储器大小 64M

	//2440V3

	{"Lightlev", 100},			//NEW ADD FOR V3 背光灯亮度
	{"Appsize", 0},			//NEW ADD FOR V3 应用程序实际大小
	{"Debug",   0},			//NEW ADD FOR V3 是否打印调试信息
	{"Debug",   0},			//NEW ADD FOR V3 是否打印调试信息
	//{"devfs",1},
	//{"ostore", 0},	//0=nand, 1=nor
	{"userpara", sizeof(DEFAULT_USER_PARAMS)},
	DEFAULT_USER_PARAMS,
	{0}

};
int main(void) {
	printf("* = %d\n",	sizeof(char *));
	printf("S1 = %d\n",	sizeof(S1));
	printf("s = %d\n",	sizeof(s));
	//printf("Sizeof \"\"%d",sizeof(boot_params)); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
