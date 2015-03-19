/*
 * adsl.c
 *
 *  Created on: 2014年11月22日
 *      Author: Administrator
 */
/*
 ============================================================================
 Name        : adsl.c
 Author      : http://zfz0701.blog.163.com/blog/static/58212760201042074827643/
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
//#include <Winsock2.h>
//#include <Iphlpapi.h>
//#include <Wininet.h>
#include <winsock2.h>
#include <ras.h>
// char * RASCS_OpenPort             = "Opening Port";                 //打开端口
// char * RASCS_PortOpened           = "Port Opened";                  //端口已打开
// char * RASCS_ConnectDevice        = "Connecting Device";            //连接设备
// char * RASCS_DeviceConnected      = "Device Connected";             //设备已连接
// char * RASCS_AllDevicesConnected  = "All Devices Connected";        //连接所有设备
// char * RASCS_Authenticate         = "Starting Authentication";      //开始验证
// char * RASCS_AuthNotify           = "Authentication Notify";        //验证通知
// char * RASCS_AuthRetry            = "Authentication Retry";         //验证重试
// char * RASCS_AuthCallback         = "Callback Requested";           //请求回叫
// char * RASCS_AuthChangePassword   = "Change Password Requested";    //请求修改密码
// char * RASCS_AuthProject          = "Projection Phase Started";     //发送帧开始
// char * RASCS_AuthLinkSpeed        = "Link Speed Calculation";       //计算连接速度
// char * RASCS_AuthAck              = "Authentication Acknowledged";  //验证公匙？
// char * RASCS_ReAuthenticate       = "Reauthentication Started";     //开始重新验证
// char * RASCS_Authenticated        = "Authenticated";                //验证
// char * RASCS_PrepareForCallback   = "Preparation For Callback";     //准备回呼
// char * RASCS_WaitForModemReset    = "Waiting For Modem Reset";      //等待Medom复位
// char * RASCS_WaitForCallback      = "Waiting For Callback";         //等待回呼
// char * RASCS_Projected            = "Projected";                    //发送
// char * RASCS_StartAuthentication  = "Start Authentication";         //开始验证
// char * RASCS_CallbackComplete     = "Callback Complete";            //回呼完成
// char * RASCS_LogonNetwork         = "Logon Network";                //登录网络
// char * RASCS_SubEntryConnected    = "";
// char * RASCS_SubEntryDisconnected = "";
// char * RASCS_Interactive          = "Interactive";                  //交互
// char * RASCS_RetryAuthentication  = "Retry Authentication";         //重新验证
// char * RASCS_CallbackSetByCaller  = "Callback Set By Caller";       //设置回呼
// char * RASCS_PasswordExpired      = "Password Expired";             //密码到期
// char * RASCS_Connected            = "Connected";                    //已连接
// char * RASCS_Disconnected         = "Disconnected";                 //已断开

HRASCONN hRasConn = NULL;
RASENTRYNAME Entries[15];
RASDIALPARAMS rdParams;
DWORD Ret;
//AutoDial
int GetDialInfo()
{


	DWORD cb, cEntries;

	BOOL f_get_password = TRUE;
	//BOOL IS_DEL_PASSWORD = TRUE;

	//RASENTRYNAME Entries[15];
	memset(Entries, 0, sizeof(Entries));
	Entries[0].dwSize = sizeof(RASENTRYNAME);
	cb = sizeof(Entries);
	cEntries = 0;

	//RASDIALPARAMS rdParams;
	memset(&rdParams, 0, sizeof(rdParams));
	rdParams.dwSize = sizeof(RASDIALPARAMS);

	//1. 自动获取 "宽带连接" 名称
	//cb 宽带连接名称占用字符数  cEntries：宽带连接数量
	Ret = RasEnumEntries(NULL, NULL, Entries, &cb, &cEntries); // 如果函数成功，则返回0
	if (Ret == 0) {
		printf("获取宽带连接名:%s",Entries[0].szEntryName);
		//设置拨号参数 在此表示	f_del_password是否删除用户密码，为TRUE时将原来的用户密码删除．
		strcpy(rdParams.szEntryName, Entries[0].szEntryName);
		//CHAR szRasEntryName[RAS_MaxEntryName + 1] = { 0 };
		//for (i = 0 ;i < cEntries;i++ )
		//strcpy(szRasEntryName,Entries[i].szEntryName);
		//rdParams.dwSize = sizeof (RASDIALPARAMS);
		//strcpy(rdParams.szEntryName,szRasEntryName);
		//strcpy(rdParams.szPhoneNumber, " #777 " ); // 我用的3G卡，拨#777号码
		//strcpy(rdParams.szUserName, " 用户名 " );
		//strcpy(rdParams.szPassword, " 密码 " );
		//strcpy(rdParams.szDomain,"");//这个也很重要，指定域，如果不指定这个的话下面注释的两句一定要加上，下边两句的意思是获取最后一次连接成功时的参数信息，如果用下边两句的话连同这行和这行上面的三行都可以省略
		// BOOL fPass;

	} else {
		//手动输入
		strcpy(rdParams.szEntryName, "宽带连接");
		//strcpy(rdParams.szPhoneNumber, " #777 " ); // 我用的3G卡，拨#777号码
		//strcpy(rdParams.szUserName, " 用户名 " );
		//strcpy(rdParams.szPassword, " 密码 " );
		//strcpy(rdParams.szDomain,"");//这个也很重要，指定域，如果不指定这个的话下面注释的两句一定要加上，下边两句的意思是获取最后一次连接成功时的参数信息，如果用下边两句的话连同这行和这行上面的三行都可以省略

	}
	//dwSize 			//该结构所占内存的大小(Bytes),一般设置为SizeOf(RASDIALPARAMS)
	//szEntryName 		//拨号连接名称
	//szPhoneNumber 	//拨号号码
	//szCallbackNumber 	//回叫号码
	//szUserName 		//用户名称
	//szPassword 		//用户密码
	//szDomain 			//域名
	//获取拨号连接的拨号参数 f_get_password是否需要用户密码
	if (RasGetEntryDialParams(NULL, &rdParams, &f_get_password) != 0) {
		//SetDlgItemText(IDC_IP, "Dial Failed, get entry adsl failed!");
		printf("无法获取拨号参数");
		return -1;
	}

	if (f_get_password == FALSE) {
		printf("密码错误");
		//SetDlgItemText(IDC_IP, "Dial Failed: get password failed!");
		return -1;
	}

	if ((Ret = RasDial(NULL, NULL, &rdParams, 0L, NULL, &hRasConn)) != 0) {
			//SetDlgItemText(IDC_IP, "Dial Failed!");
			printf("拨号失败");
			return -1;
		}

	//获取当前活动的连接 RasEnumConnections()
	// var lprasconn : RASCONN ;//接收活动连接的缓冲区的指针
	//	var lpcb: DWORD;//缓冲区大小
	//	var lpcConnections : DWORD//实际的活动连接数目
	//(1)RASCONN = record
	//dwSize : DWORD;//该结构所占内存的大小(Bytes),一般设置为	SizeOf(RASCONN)
	//hrasconn : HRASCONN;//活动连接的句柄
	//szEntryName : array[0..RAS_MaxEntryName] of char;//活动连接	的名称
	//szDeviceType : array[0..RAS_MaxDeviceType] of char;//活动连	接的所用的设备类型
	//szDeviceName : array[0..RAS_MaxDeviceName] of char;//活动连	接的所用的设备名称

	//获取指定连接的连接状态 RasGetConnectStatus()
	//hrasconn : HRASCONN; //指定活动连接的句柄
	//lprasconnstatus : LPRASCONNSTATUS//连接状态参数

	//char tstr[40], temp[200];
	//wsprintf(temp, "Dial OK! %s", _strtime(tstr));
	//SetDlgItemText(IDC_IP, temp);
	// 删除cookie
	//remove("Q:\\Documents and Settings\\Administrator.PUDN\\Cookies\\administrator@news.survey.sina.com[1].txt");
	//remove("Q:\\Documents and Settings\\Administrator.PUDN\\Cookies\\administrator@sina.com[1].txt");
	//remove("Q:\\Documents and Settings\\Administrator.PUDN\\Cookies\\administrator@38.adsina.allyes[2].txt");
	//DeleteUrlCacheEntry("Cookie:administrator@news.survey.sina.com.cn/");
	// 刷新IE
	/*
	 if (RasSetEntryDialParams(NULL, &rdParams, IS_DEL_PASSWORD)) {
	 //SetDlgItemText(IDC_IP, "Dial Failed, get entry adsl failed!");
	 printf("设置失败");
	 //return -1;
	 }
	 */
	return 0;
}

int DialConnect()
{

	if ((Ret = RasDial(NULL, NULL, &rdParams, 0L, NULL, &hRasConn)) != 0) {
			//SetDlgItemText(IDC_IP, "Dial Failed!");
			printf("拨号失败");
			return -1;
		}
	return 0;
}

int DialDisConnect()
{
	// 重新拨号
	if (hRasConn) {
		RasHangUp(hRasConn);
		hRasConn = NULL;
	}
	return 0;
}
int ReDial()
{
	printf("ReDial");
	DialDisConnect();
	Sleep(1000);
	if ((Ret = RasDial(NULL, NULL, &rdParams, 0L, NULL, &hRasConn)) != 0) {
			//SetDlgItemText(IDC_IP, "Dial Failed!");
			printf("拨号失败");
			return -1;
		}
	return 0;
}


