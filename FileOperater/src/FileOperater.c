/*
 ============================================================================
 Name        : FileOperater.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style

 r  打开 只读文件，该文件必须存在。
 r+ 打开可读写的文件，该文件必须存在。
 w 打开   只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
 w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
 a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。
 a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。

 上述的形态字符串都可以再加一个b字符，如rb、w+b或ab＋等组合，加入b 字符用来告诉函数库打开的文件为二进制文件，而非纯文字文件。
 ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

const uint8_t CHWAV_RIFF[4] = { 0x52, 0x49, 0x46, 0x46 };
const uint8_t CHWAV_WAVE[4] = { 0x57, 0x41, 0x56, 0x45 };
const uint8_t CHWAV_FMT[4] = { 0x66, 0x6D, 0x74, 0x20 };
const uint8_t CHWAV_DATA[4] = { 0x64, 0x61, 0x74, 0x61 };
// 小端模式
const uint32_t DWWAV_RIFF = 0x46464952;
const uint32_t DWWAV_WAVE = 0x45564157;
const uint32_t DWWAV_FMT =  0x20746D66;
const uint32_t DWWAV_DATA = 0x61746164;
typedef struct {
	//	 RIFF_HEADER

	//uint8_t chRIFF[4];	//00H 	4byte 52 49 46 46   RIFF，资源交换文件标志。
	uint32_t chriff;
	uint32_t wavlen;		//04H	4byte 从下一个地址开始到文件尾的总字节数。高位字节在后面，这里就是001437ECH，换成十进制是1325036byte，算上这之前的8byte就正好1325044byte了。
	//uint8_t chWAV[4];		//08H	4byte 57 41 56 45  	WAVE，代表wav文件格式。
	uint32_t chwav;
	//uint8_t chFMT[4];		//0CH	4byte 66 6D 74 20	FMT ，波形格式标志
	uint32_t chfmt;
	uint32_t PcmSize;		//10H	4byte	00000010H，16PCM，这个对应定义中的PCMWAVEFORMAT部分的大小，可以看到后面的这个段内容正好是16个字节。当为16时，最后是没有附加信息的，当为数字18时，最后多了两个字节的附加信息
	//	PCMWAVEFORMAT
	//formart;
	uint16_t FormatTag;		//14H	2byte	为1时表示线性PCM编码，大于1时表示有压缩的编码。这里是0001H。
	//CHnum;
	uint16_t Channels;		//16H	2byte	1为单声道，2为双声道，这里是0001H。
	//SampleRate;
	uint32_t SamplesPerSec;	//18H	4byte	采样频率，这里是00002B11H，也就是11025Hz。
	//speed;
	uint32_t AvgBytesPerSec;//1CH	4byte	Byte率=采样频率*音频通道数*每次采样得到的样本位数/8，00005622H，也就是22050Byte/s=11025*1*16/2。
	//ajust;
	uint16_t BlockAlign;	//20H	2byte	块对齐=通道数*每次采样得到的样本位数/8，0002H，也就是2=1*16/8。
	//SampleBits;
	uint16_t BitsPerSample;	//22H	2byte	样本数据位数，0010H即16，一个量化样本占2byte。

	//uint8_t chDATA[4];	//24H	4byte	data，一个标志而已。
	uint32_t chdata;
	uint32_t DATAlen;		//28H	4byte	Wav文件实际音频数据所占的大小，这里是001437C8H即1325000，再加上2CH就正好是1325044，整个文件的大小。
} WAV_head_t;
typedef union {
	WAV_head_t wavhead;
	uint8_t wavbuf[0x30];
} WAVE_info_u;
WAV_head_t wav1;
uint8_t CHanalnum;
uint8_t Bitnum;
uint8_t DACdone;
WAVE_info_u wavinfo;

uint8_t Check_Ifo(uint8_t* pbuf1, uint8_t* pbuf2) {
	uint8_t i;
	for (i = 0; i < 4; i++)
		if (pbuf1[i] != pbuf2[i])
			return 1;
	return 0;
}
uint32_t Get_num(uint8_t* pbuf, uint8_t len) {
	uint32_t num;
	if (len == 2)
		num = (pbuf[1] << 8) | pbuf[0];
	else if (len == 4)
		num = (pbuf[3] << 24) | (pbuf[2] << 16) | (pbuf[1] << 8) | pbuf[0];
	return num;
}
uint8_t WAV_Init(uint8_t* pbuf) //初始化并显示文件信息
{
	int i;
	uint8_t *pbuf0=pbuf;
	for(i=0;i<0x30;i++)
	wavinfo.wavbuf[i] = *(pbuf0++);
	if (wavinfo.wavhead.chriff != DWWAV_RIFF)
		return 1;	//RIFF标志错误
	//wav1.wavlen = Get_num(pbuf + 4, 4);		//文件长度，数据偏移4byte
	if (wavinfo.wavhead.chwav != DWWAV_WAVE)
		return 2;		//WAVE标志错误
	if (wavinfo.wavhead.chfmt !=DWWAV_FMT)
		return 3;		//fmt标志错误
	if (wavinfo.wavhead.chdata != DWWAV_DATA)
		return 4;		//data标志错误
	printf("headlen: %x\n",wavinfo.wavhead.wavlen-wavinfo.wavhead.DATAlen-1+8);
	printf("wavlen: %d\n",wavinfo.wavhead.wavlen);
	printf("DATAlen: %d\n",wavinfo.wavhead.DATAlen);
	printf("文件大小: %d\n",wavinfo.wavhead.wavlen+8);
	printf("声道Channels: %d\n",wavinfo.wavhead.Channels);
	printf("样本位数BitsPerSample: %d\n",wavinfo.wavhead.BitsPerSample);
	printf("采样频率SamplesPerSec: %d\n",wavinfo.wavhead.SamplesPerSec);
	printf("比特率AvgBytesPerSec: %d\n",wavinfo.wavhead.AvgBytesPerSec);
	printf("BlockAlign: %d\n",wavinfo.wavhead.BlockAlign);

	wav1.FormatTag = Get_num(pbuf + 20, 2);		//格式类别
	wav1.Channels = Get_num(pbuf + 22, 2);		//通道数
	CHanalnum = wav1.Channels;
	wav1.SamplesPerSec = Get_num(pbuf + 24, 4);		//采样率
	wav1.AvgBytesPerSec = Get_num(pbuf + 28, 4);		//音频传送速率
	wav1.BlockAlign = Get_num(pbuf + 32, 2);		//数据块调速数
	wav1.BitsPerSample = Get_num(pbuf + 34, 2);		//样本数据位数
	Bitnum = wav1.BitsPerSample;
	wav1.DATAlen = Get_num(pbuf + 40, 4);		//数据长度
	///////////////////////////////////////////////
//	if (wav1.wavlen < 0x100000) {
//		LCD_ShowNum(170, 30, (wav1.wavlen) >> 10, 3, 16);	//文件长度
//		LCD_ShowString(200, 30, "Kb");
//	} else {
//		LCD_ShowNum(170, 30, (wav1.wavlen) >> 20, 3, 16);	//文件长度
//		LCD_ShowString(200, 30, "Mb");
//	}
//	if (wav1.FormatTag == 1)
//		LCD_ShowString(170, 50, "WAV PCM");
//	if (wav1.Channels == 1)
//		LCD_ShowString(170, 70, "single");
//	else
//		LCD_ShowString(170, 70, "stereo");
//	LCD_ShowNum(170, 90, (wav1.SamplesPerSec) / 1000, 3, 16);	//采样率
//	LCD_ShowString(200, 90, "KHz");
//	LCD_ShowNum(170, 110, (wav1.AvgBytesPerSec) / 1000, 3, 16);	//传送速度
//	LCD_ShowString(200, 110, "bps");
//	LCD_ShowNum(177, 130, wav1.BitsPerSample, 2, 16);	//样本数据位数
//	LCD_ShowString(200, 130, "bit");
	return 0;
}

int main0(void) {
//	puts("!!!Hello World!!!"); // prints !!!Hello World!!!

	FILE *fp2;
	int c;
	fp2 = fopen("a.txt", "r");
	while ((c = fgetc(stdin)) != EOF)
		printf("0X%x\n", c);
	fclose(fp2);
	return EXIT_SUCCESS;
}
int main() {
	int i;
	unsigned char s[1024] = { 0 };
	FILE *fp = NULL;
	printf("open 000.wav");
	if (NULL == (fp = fopen("C:\\Windows\\000.wav", "rb+")))
		return 0;
//	参数：第一个参数为接收数据的指针(buff),也即数据存储的地址
//	第二个参数为单个元素的大小，即由指针写入地址的数据大小，注意单位是字节
//	第三个参数为元素个数，即要读取的数据大小为size的元素个素
//	第四个参数为提供数据的文件指针，该指针指向文件内部数据
//	返回值：读取的总数据元素个数
	printf("opened 000.wav\n");

	fread(s, 256, 1, fp);
	WAV_Init(s);
	for (i = 0; i < 0x2C; i++) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%02x ", s[i]);

	}
}
/* void main2()
 {
 FILE *fp = NULL;
 short i,j;    //勿定义为BYTE, 否则无限循环.
 if(NULL == (fp = fopen("a.bin","ab+")))
 return;
 // for(i=0;i<=0xFF;++i)
 for(j=0;j<=0xFF;++j)
 {
 //   fputc(0x20,fp);
 //   fputc(0x20,fp);
 fputc(j,fp);
 }
 fclose(fp);
 if(NULL == (fp = fopen("*.txt","ab+")))

 puts("!!!Hello World!!!");
 }


 int FileWrite(char* s,FILE *fp){
 if(NULL == (fp = fopen("a.txt","w+b")))
 return;
 printf("%d\n", fwrite(s,sizeof(s),10,fp));
 //s 待写入数据的指针
 //sizeof(s) 每次写入数据的大小
 //10 写入数据的总大小 10*sizeof(s)
 //要写入文件的指针
 fclose(fp);
 }*/
int main2() {
	FILE *fp = NULL;
	//  char s11[1024]={0x31,32,33,34,35,36,37,38,39};
	unsigned char s[1024] = { 0 };
	// short i,j;    //勿定义为BYTE, 否则无限循环.
	unsigned int i, j, compare;
	unsigned int total, adds, min;

	puts("操作说明\n\n");
	puts("1.把通话记录中需要统计的内容导出!\n");
	puts("2.每条记录时间用空格或换行隔开!\n");
	puts("3.注意最后一条记录后面一定要加空格或回车哦!");
	puts("\nPress Enter To GO!");
	while (!fgetc(stdin))
		;

	if (NULL == (fp = fopen("recoder.txt", "a+")))
		return 0;
	/* // for(i=0;i<=0xFF;++i)
	 for(j=0;j<=0xFF;++j)
	 {

	 //   fputc(0x20,fp);

	 //   fputc(0x20,fp);
	 fputc(j,fp);
	 fputc(0x0a,fp);
	 //printf("%d\n",ftell(fp));
	 }
	 //   fread();
	 fclose(fp);

	 if(NULL == (fp = fopen("a.txt","ab+")))
	 return;

	 //    printf("%d\n",s[2]);
	 fclose(fp);
	 */

	//fputs(fgets(s,80,stdin),stdout);
	fread(s, 256, 1, fp);
	//fgets(s,100,fp);
	fclose(fp);

	/*i=0;
	 while(s[i]){
	 printf("%x\n",s[i]);
	 i++;
	 }*/

	i = 0;
	j = 0;
	compare = 0;
	adds = 0;
	min = 0;
	total = 0;
	//printf("adds=%d\n",adds);
	while (s[i]) {
		if ((s[i] > 0x29) && (s[i] < 0x40)) {
			adds *= 10;
			adds += s[i] - 0x30;
			//	 printf("s[%d]=%x\n",i,s[i]);

		}
		i++;
		//	 printf("adds=%d\n",adds);

		if ((s[i] == 0x0a) || (s[i] == 0x0d) || (s[i] == 0x20)) {
			//	printf("adds2=%d\n", adds);
			if (adds) {
				if (adds % 60)
					min = adds / 60 + 1;
				else
					min = adds / 60;
				//	printf("min=%d\n", min);
				total += min;
				if (!(total == compare)) {
					j++;
					compare = total;
					printf("\n第%d条通话记录%d分钟\n", j, min);
				}

				//		printf("total=%d\n", total);
			}
			adds = 0;
			i++;
		}
		//			printf("0x%x\n",s[i]);

		// printf("%d\n",total);
	}
	printf("\n共%d条通话记录\n\n", j);
	printf("\n您的通话时间为%d分钟\n\n", total);
	// if(NULL == (fp = fopen("b.txt","w+")))return;
	//  fputs(s1,fp);
	// fclose(fp);
	puts("\nPress Twice Time Enter To Exit!");
	while (!fgetc(stdin))
		;
	while (!fgetc(stdin))
		;
	return 0;
}
