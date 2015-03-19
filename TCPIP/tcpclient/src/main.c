/*
 * main.c
 *
 *  Created on: 2014年11月22日
 *      Author: Administrator
 */

#include "stdio.h"
#include <Winsock2.h>

//using namespace std;
extern int dingshifasong();
extern int zidongshuapiao();

extern int GetDialInfo();

BOOL GET_INFO = FALSE;
int main()
{
	// 加载socket动态链接库(dll)
	WORD wVersionRequested;
	WSADATA wsaData;    // 这结构是用于接收Wjndows Socket的结构信息的
	int err;

	wVersionRequested = MAKEWORD(1, 1);   // 请求1.1版本的WinSock库

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;          // 返回值为零的时候是表示成功申请WSAStartup
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本
		// 否则的话，调用WSACleanup()清除信息，结束函数
		WSACleanup();
		return -1;
	}

	if(GetDialInfo() == 0)
		GET_INFO = TRUE;
	printf("GET_INFO :%d",GET_INFO);
	  //dingshifasong();

	  zidongshuapiao();



	WSACleanup();   // 终止对套接字库的使用
	//system("pause");
	return 0;
}




