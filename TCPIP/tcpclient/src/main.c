/*
 * main.c
 *
 *  Created on: 2014��11��22��
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
	// ����socket��̬���ӿ�(dll)
	WORD wVersionRequested;
	WSADATA wsaData;    // ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
	int err;

	wVersionRequested = MAKEWORD(1, 1);   // ����1.1�汾��WinSock��

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;          // ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾
		// ����Ļ�������WSACleanup()�����Ϣ����������
		WSACleanup();
		return -1;
	}

	if(GetDialInfo() == 0)
		GET_INFO = TRUE;
	printf("GET_INFO :%d",GET_INFO);
	  //dingshifasong();

	  zidongshuapiao();



	WSACleanup();   // ��ֹ���׽��ֿ��ʹ��
	//system("pause");
	return 0;
}




