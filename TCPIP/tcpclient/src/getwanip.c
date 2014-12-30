/*
 * getwanip.c
 *
 *  Created on: 2014年11月21日
 *      Author: Administrator
 */

#include "stdio.h"
#include <string.h>
#include <Winsock2.h>

#define BUF_SIZE   512

int webport = 80;

char mywanip[16] = { 0 };

char * getwanip(void) {
	//char *url = "www.3322.org/dyndns/getip";
	const char * wanip = "118.184.176.15";	//www.3322.org [203]
	//const char * hostmane = "www.3322.org";
	const char * sendHeader =
			"GET /dyndns/getip HTTP/1.1\r\nHOST:www.3322.org\r\nACCEPT:*/*\r\nConnection: close\r\n\r\n\r\n";
	struct sockaddr_in sockAddr;
	//struct hostent *nlp_host;
	int i;
	int sd = 0;
	int len = 0;

	char buf[BUF_SIZE] = { 0 };

	///setting socket param
//	if ((nlp_host = gethostbyname(hostname)) == 0) {
//		perror("error get host\n");
//		//exit(1);
//	}

	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//sockAddr.sin_addr.s_addr = ((struct in_addr *) (nlp_host->h_addr))->s_addr;
	//sockAddr.sin_addr.s_addr=inet_addr("219.153.18.104");
	sockAddr.sin_addr.s_addr = inet_addr(wanip);
	sockAddr.sin_port = htons(webport);

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Error opening socket!!!\n");
		//exit(1);
	}

	///connect to the webserver,send the header,and receive the web sourcecode
	if (connect(sd, (void *) &sockAddr, sizeof(sockAddr)) == -1)
		printf("error connect to socket\n");

//	if (send(sd, header, strlen(header), 0) == -1) {
//		perror("error in send \n");
	//exit(1);
//	}

	if (send(sd, sendHeader, strlen(sendHeader), 0) == -1) {
		perror("error in send \n");
		//exit(1);
	}

	///send the message and wait the response!!!
	len = recv(sd, buf, BUF_SIZE, 0);
	if (len < 0)
		printf("receive data error!!!\n");
	else {
		for (i = 0;; i++) {
			mywanip[i] = buf[203 + i];
			//printf("%d ", (buf[203 + i]));
			//printf("%d", len);
			//分割符 \r \n ]
			//www.3322.org
			if (buf[203 + i] == 0x0A)
				break;
		}
		//printf("%s", buf);
		mywanip[i] = 0;
		printf("我的外网IP: %s\n", mywanip);
	}
	closesocket(sd);

	return mywanip;
}

