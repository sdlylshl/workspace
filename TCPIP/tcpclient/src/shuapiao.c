#include "stdio.h"
#include <Winsock2.h>

//extern char * post1;
//extern char * cookie1;
//extern char * nid1;
//extern char * num1;
extern char * shuapiaostr;
int shuapiao() {
	const char * serverip = "202.136.60.55";	//zyzs.01china.com
	const int serverport = 80;

//	const char * serverip = "192.168.2.102";	//����
//	const int serverport = 51388;

	const char * sendpost = shuapiaostr;
	const char * sendid = "59";
	// ����socket������������ʽ�׽��֣������׽��ֺ�sockClient
	// SOCKET socket(int af, int type, int protocol);
	// ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)
	// �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���

	SOCKET sockClient;

	// ���׽���sockClient��Զ����������
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);
	// ��һ����������Ҫ�������Ӳ������׽���
	// �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ
	// ��������������ַ�ĳ���
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(serverip);  // ���ػ�·��ַ��127.0.0.1;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(serverport);

	printf("��������IP: %s �˿�: %d ID: %s \n",serverip,serverport,sendid);
	//1.����socket
	if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Error opening socket!!!\n");
		//exit(1);
	}
	//2.��������
		//connect(sockClient, (SOCKADDR*) &addrSrv, sizeof(SOCKADDR));
	///connect to the webserver,send the header,and receive the web sourcecode
	if (connect(sockClient, (SOCKADDR*) &addrSrv, sizeof(addrSrv)) == -1)
		printf("error connect to socket\n");



	//3.����
	if (send(sockClient, sendpost, strlen(sendpost), 0) == -1) {
		perror("error in send \n");
		//exit(1);
	}
	if (send(sockClient, sendid, strlen(sendid), 0) == -1) {
		perror("error in send \n");
		//exit(1);
	}
	//4.����
	//char recvBuf[100];
	//recv(sockClient, recvBuf, 100, 0);
	//printf("%s\n", recvBuf);


	/*
	printf("���ǿ�������仰");
	int n = 5;
	do {
		printf("\n��ʣ%d�Σ�", n);
		char talk[100];
		printf("\nPlease enter what you want to say next(\"quit\"to exit):");
		gets(talk);
		send(sockClient, talk, strlen(talk) + 1, 0);          // ������Ϣ

		char recvBuf[100];
		recv(sockClient, recvBuf, 100, 0);
		printf("%s Says: %s\n", "Server", recvBuf);     // ������Ϣ
	} while (--n);

	printf("End linking...\n");
	*/

	//5.�ر�socket
	closesocket(sockClient);

	return 0;
}
