/*
 * dingshifasong.c
 *
 *  Created on: 2014��11��22��
 *      Author: Administrator
 */

//============================================================================
// Name        : tcpclient.cpp
// Author      : elines
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <stdio.h>
//#include <winbase.h>
#include <Winsock2.h>

extern int shuapiao();

int dingshifasong()
{

	int err;
	int timeout = 0;
	unsigned int sendnum=0;




	printf("\n �����뷢�ͼ�� Ĭ��10S����λ�룩\n :");
	err = scanf("%d",&timeout);
	printf("%d\n", err);
	//printf("%d s\n", timeout);
	if(timeout > 600 || timeout <1)
		timeout = 10;
	printf(" ���ͼ��Ϊ %d ��\n\n ",timeout);

	while(++sendnum){

	shuapiao();
	printf("�� %d ��...\n",sendnum);

	Sleep(timeout*1000);
	}

	return 0;
}



