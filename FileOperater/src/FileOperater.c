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
#include <stdlib.h>
#include <string.h>
int main(void) {
//	puts("!!!Hello World!!!"); // prints !!!Hello World!!!

FILE *fp2;
int c;
fp2=fopen("a.txt","r");
while((c=fgetc(stdin))!=EOF)
  printf("0X%x\n",c);
fclose(fp2);
return EXIT_SUCCESS;
}

//#include <stdio.h>
// #include <windows.h>
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
	unsigned int i,j,compare;
	unsigned int total, adds, min;

	puts("操作说明\n\n");
	puts("1.把通话记录中需要统计的内容导出!\n");
	puts("2.每条记录时间用空格或换行隔开!\n");
	puts("3.注意最后一条记录后面一定要加空格或回车哦!");
	puts("\nPress Enter To GO!");
	while(!fgetc(stdin));

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
	j=0;
	compare=0;
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
				if(!(total==compare)){
					j++;
					compare=total;
				printf("\n第%d条通话记录%d分钟\n",j,min);
				}

		//		printf("total=%d\n", total);
			}
			adds = 0;
			i++;
		}
		//			printf("0x%x\n",s[i]);

		// printf("%d\n",total);
	}
	printf("\n共%d条通话记录\n\n",j);
	printf("\n您的通话时间为%d分钟\n\n", total);
	// if(NULL == (fp = fopen("b.txt","w+")))return;
	//  fputs(s1,fp);
	// fclose(fp);
	puts("\nPress Twice Time Enter To Exit!");
	while(!fgetc(stdin));
	while(!fgetc(stdin));
	return 0;
 }
