/*
 ============================================================================
 Name        : FileOperater.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style

r  �� ֻ���ļ������ļ�������ڡ�
r+ �򿪿ɶ�д���ļ������ļ�������ڡ�
w ��   ֻд�ļ������ļ��������ļ�������Ϊ0�������ļ����ݻ���ʧ�����ļ��������������ļ���
w+ �򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
a �Ը��ӵķ�ʽ��ֻд�ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�����ļ�ԭ�ȵ����ݻᱻ������
a+ �Ը��ӷ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ������

��������̬�ַ����������ټ�һ��b�ַ�����rb��w+b��ab������ϣ�����b �ַ��������ߺ�����򿪵��ļ�Ϊ�������ļ������Ǵ������ļ���
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
   short i,j;    //����ΪBYTE, ��������ѭ��.
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
		   //s ��д�����ݵ�ָ��
		   //sizeof(s) ÿ��д�����ݵĴ�С
		   //10 д�����ݵ��ܴ�С 10*sizeof(s)
		   //Ҫд���ļ���ָ��
	   fclose(fp);
}*/
int main2() {
	FILE *fp = NULL;
	//  char s11[1024]={0x31,32,33,34,35,36,37,38,39};
	unsigned char s[1024] = { 0 };
	// short i,j;    //����ΪBYTE, ��������ѭ��.
	unsigned int i,j,compare;
	unsigned int total, adds, min;

	puts("����˵��\n\n");
	puts("1.��ͨ����¼����Ҫͳ�Ƶ����ݵ���!\n");
	puts("2.ÿ����¼ʱ���ÿո���и���!\n");
	puts("3.ע�����һ����¼����һ��Ҫ�ӿո��س�Ŷ!");
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
				printf("\n��%d��ͨ����¼%d����\n",j,min);
				}

		//		printf("total=%d\n", total);
			}
			adds = 0;
			i++;
		}
		//			printf("0x%x\n",s[i]);

		// printf("%d\n",total);
	}
	printf("\n��%d��ͨ����¼\n\n",j);
	printf("\n����ͨ��ʱ��Ϊ%d����\n\n", total);
	// if(NULL == (fp = fopen("b.txt","w+")))return;
	//  fputs(s1,fp);
	// fclose(fp);
	puts("\nPress Twice Time Enter To Exit!");
	while(!fgetc(stdin));
	while(!fgetc(stdin));
	return 0;
 }
