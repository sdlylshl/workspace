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

//	const char * serverip = "192.168.2.102";	//本机
//	const int serverport = 51388;

	const char * sendpost = shuapiaostr;
	const char * sendid = "59";
	// 创建socket操作，建立流式套接字，返回套接字号sockClient
	// SOCKET socket(int af, int type, int protocol);
	// 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET)
	// 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）

	SOCKET sockClient;

	// 将套接字sockClient与远程主机相连
	// int connect( SOCKET s,  const struct sockaddr* name,  int namelen);
	// 第一个参数：需要进行连接操作的套接字
	// 第二个参数：设定所需要连接的地址信息
	// 第三个参数：地址的长度
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(serverip);  // 本地回路地址是127.0.0.1;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(serverport);

	printf("服务器的IP: %s 端口: %d ID: %s \n",serverip,serverport,sendid);
	//1.创建socket
	if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Error opening socket!!!\n");
		//exit(1);
	}
	//2.建立连接
		//connect(sockClient, (SOCKADDR*) &addrSrv, sizeof(SOCKADDR));
	///connect to the webserver,send the header,and receive the web sourcecode
	if (connect(sockClient, (SOCKADDR*) &addrSrv, sizeof(addrSrv)) == -1)
		printf("error connect to socket\n");



	//3.发送
	if (send(sockClient, sendpost, strlen(sendpost), 0) == -1) {
		perror("error in send \n");
		//exit(1);
	}
	if (send(sockClient, sendid, strlen(sendid), 0) == -1) {
		perror("error in send \n");
		//exit(1);
	}
	//4.接收
	//char recvBuf[100];
	//recv(sockClient, recvBuf, 100, 0);
	//printf("%s\n", recvBuf);


	/*
	printf("我们可以聊五句话");
	int n = 5;
	do {
		printf("\n还剩%d次：", n);
		char talk[100];
		printf("\nPlease enter what you want to say next(\"quit\"to exit):");
		gets(talk);
		send(sockClient, talk, strlen(talk) + 1, 0);          // 发送信息

		char recvBuf[100];
		recv(sockClient, recvBuf, 100, 0);
		printf("%s Says: %s\n", "Server", recvBuf);     // 接收信息
	} while (--n);

	printf("End linking...\n");
	*/

	//5.关闭socket
	closesocket(sockClient);

	return 0;
}
