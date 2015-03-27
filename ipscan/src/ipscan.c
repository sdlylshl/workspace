/*
 ============================================================================
 Name        : ipscan.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "iphlpapi.h"

#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "Iphlpapi.lib" )

void main( int argc, char **argv )
{
	int i;
    int numberOfHost = 1;
    struct hostent *remoteHostent;

    //处理命令行参数
    if( 3 == argc )
    {
        numberOfHost = atoi( argv[2] );
    }
    if( ( 3 < argc ) || ( 2 > argc ) )
    {
        printf( "RmtHost v0.2 - Get remote HostName /MacAddress\n" );
        printf( "Usage:\n/tRmtHost.exe [RemoteIP]\n\n" );
        printf( "Example:\n/tRmtHost.exe 192.168.0.3\n" );
        printf( "/tRmtHost.exe 192.168.0.3 255\n\n" );
        exit( 0 );
    }

    //初始化SOCKET
    WSADATA wsaData;
    int iRet = WSAStartup( MAKEWORD(2,1), &wsaData );
    if ( 0 != iRet )
    {
        printf( "WSAStartup   Error:%d\n", GetLastError() );
        exit( 0 );
    }

    int nRemoteAddr = inet_addr( argv[1] );
    remoteHostent = (struct hostent*)malloc( sizeof(struct hostent ));
    struct in_addr sa;
    for( i = 0; i < numberOfHost; i++ )
    {
        //获取远程机器名
        sa.s_addr =  nRemoteAddr;
        printf( "\nIpAddress   :   %s\n", inet_ntoa( sa ) );
        remoteHostent = gethostbyaddr( (char*)&nRemoteAddr, 4, AF_INET );
        if( remoteHostent )
        {
            printf( "HostName　:   %s\n", remoteHostent->h_name );
        }
        else
        {
            printf( "gethostbyaddr   Error:%d\n", GetLastError() );
        }
        //发送ARP查询包获得远程MAC地址

        unsigned char macAddress[6];
        ULONG macAddLen  = 6;
        iRet = SendARP( nRemoteAddr, (unsigned long)NULL,(PULONG)&macAddress, &macAddLen );
        if( NO_ERROR == iRet )
        {
            printf( "MacAddress:   " );
            for(  i =0; i < 6; i++ )
            {
                printf( "%.2x", macAddress[i] );
                if( i < 5 )
                {
                    printf( "-" );
                }
            }
            printf( "\n" );
        }
        else
        {
            printf( "SendARP   Error:%d\n", GetLastError() );
        }
        nRemoteAddr = htonl( ntohl( nRemoteAddr ) + 1 );
    }
}
