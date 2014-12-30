/*
 ============================================================================
 Name        : union.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct param_struct {
	char first;
	union {
		struct {
			unsigned long page_size; /*  0 */ //页大小
			unsigned long nr_pages; /*  4 */
			unsigned long ramdisk_size; /*  8 */
			unsigned long flags; /* 12 */
#define FLAG_READONLY	1
#define FLAG_RDLOAD		4
#define FLAG_RDPROMPT	8
			unsigned long rootdev; /* 16 */
			unsigned long video_num_cols; /* 20 */
			unsigned long video_num_rows; /* 24 */
			unsigned long video_x; /* 28 */
			unsigned long video_y; /* 32 */
			unsigned long memc_control_reg; /* 36 */
			unsigned char sounddefault; /* 40 */
			unsigned char adfsdrives; /* 41 */
			unsigned char bytes_per_char_h; /* 42 */
			unsigned char bytes_per_char_v; /* 43 */
			unsigned long pages_in_bank[4]; /* 44 */
			unsigned long pages_in_vram; /* 60 */
			unsigned long initrd_start; /* 64 */
			unsigned long initrd_size; /* 68 */
			unsigned long rd_start; /* 72 */
			unsigned long system_rev; /* 76 */
			unsigned long system_serial_low; /* 80 */
			unsigned long system_serial_high; /* 84 */
			unsigned long mem_fclk_21285; /* 88 */
		} s;

		char unused[256];
	} u1;
	//256字节

	union {
		char paths[8][128];

		struct {
			unsigned long magic;
			char n[1024 - sizeof(unsigned long)];
		} s;
	} u2;
	//1024字节

	char commandline[1024];
//1024字节
};
char *str = "hello";
int stringlen(const char *str) {
	int i;
	do {
		i++;
	} while (*str++);
	return i;
}
//time();
time_t ls;
struct tm *lss;

void HexToDec(char*ps, unsigned long src) {
	char *s = ps;
//	U32 j=1000000000;
	while (src > 0) {
		*s++ = src % 10;
		src /= 10;
		printf("%d\n", *s);
	}

}

int main_param(void) {
	int i;
	char *dec;
	char buff[0x1000] = { 0 };
	struct param_struct st;
	struct param_struct *stt = &st;
	//char *pointer;
//	char *pointer = &st.first;
	ls = time(NULL);
	lss = gmtime(&ls);
//	HexToDec(dec, 10000);
	printf("hello");
//	st.first=55;
//	st.u1.s.page_size=258;
//	st.u1.s.nr_pages=25;
//	memcpy(&st.first,0,sizeof(st));
	printf("%d\n", st.first);
//	printf("%d\n\n", &st.first);
//	printf("%d\n",st.u1.s.page_size);
//	char *pointer=&st.first;
//char *pointer2 =&st.u1.s.page_size;
//char *pointer3 =&st.u1.s.nr_pages;
//	printf("%d\n",buff[1]);

	st.first = 55;
	st.u1.s.page_size = 258;
	st.u1.s.nr_pages = 25;
	{
		char *pointer = &st.first;

		{
			//可选
			//结构体清零
			printf("%d\n", *pointer);
			printf("%d\n", *(pointer + 1));
			for (i = 0; i < sizeof(st); i++) {
				*pointer++ = 1;
			}
			pointer = &st.first;
			printf("%d\n", *pointer);
			printf("%d\n", *(pointer + 1));
		}

		{
			//对结构体赋值
			stt->first = 55;
			st.u1.s.page_size = 258;
			st.u1.s.nr_pages = 25;
		}
		//取得结构体的首指针
		pointer = &st.first;
		for (i = 0; i < sizeof(st); i++) {

			buff[i] = *pointer++;
			//	pointer++;

//		printf("%d\n",pointer);
//		printf("%d\n",pointer2);
//		printf("%d\n",pointer3);
//		printf("%d\n",buff[i]);

		}
	}
	printf("%d\n", 0x1000);
	printf("%d\n", sizeof(st));
//	struct param_struct st;
//	printf("%d\n",sizeof(struct param_struct));
//	printf("%d\n",lss->tm_hour);
//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
