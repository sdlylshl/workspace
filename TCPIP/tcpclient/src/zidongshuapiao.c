//============================================================================
// Name        : tcpclient.cpp
// Author      : elines
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "stdio.h"
#include <Winsock2.h>

//using namespace std;
extern char * getwanip();
extern int shuapiao();
extern int ReDial();
extern BOOL GET_INFO ;
int zidongshuapiao()
{
	char tmpip[16]={0};
	char *newip=tmpip;
while(GET_INFO){
	newip=getwanip();

	if(strcmp(tmpip,newip))
	{
		printf("\nÐÂµÄIPµØÖ·:%s\n",newip);
		//
		strcpy(tmpip,newip);

		shuapiao();

	}
	ReDial();
	Sleep(1000);
}
	return 0;
}

