/*
 * dingshifasong.c
 *
 *  Created on: 2014年11月22日
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




	printf("\n 请输入发送间隔 默认10S（单位秒）\n :");
	err = scanf("%d",&timeout);
	printf("%d\n", err);
	//printf("%d s\n", timeout);
	if(timeout > 600 || timeout <1)
		timeout = 10;
	printf(" 发送间隔为 %d 秒\n\n ",timeout);

	while(++sendnum){

	shuapiao();
	printf("第 %d 次...\n",sendnum);

	Sleep(timeout*1000);
	}

	return 0;
}



