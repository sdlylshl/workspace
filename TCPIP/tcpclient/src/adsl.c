/*
 * adsl.c
 *
 *  Created on: 2014��11��22��
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
// char * RASCS_OpenPort             = "Opening Port";                 //�򿪶˿�
// char * RASCS_PortOpened           = "Port Opened";                  //�˿��Ѵ�
// char * RASCS_ConnectDevice        = "Connecting Device";            //�����豸
// char * RASCS_DeviceConnected      = "Device Connected";             //�豸������
// char * RASCS_AllDevicesConnected  = "All Devices Connected";        //���������豸
// char * RASCS_Authenticate         = "Starting Authentication";      //��ʼ��֤
// char * RASCS_AuthNotify           = "Authentication Notify";        //��֤֪ͨ
// char * RASCS_AuthRetry            = "Authentication Retry";         //��֤����
// char * RASCS_AuthCallback         = "Callback Requested";           //����ؽ�
// char * RASCS_AuthChangePassword   = "Change Password Requested";    //�����޸�����
// char * RASCS_AuthProject          = "Projection Phase Started";     //����֡��ʼ
// char * RASCS_AuthLinkSpeed        = "Link Speed Calculation";       //���������ٶ�
// char * RASCS_AuthAck              = "Authentication Acknowledged";  //��֤���ף�
// char * RASCS_ReAuthenticate       = "Reauthentication Started";     //��ʼ������֤
// char * RASCS_Authenticated        = "Authenticated";                //��֤
// char * RASCS_PrepareForCallback   = "Preparation For Callback";     //׼���غ�
// char * RASCS_WaitForModemReset    = "Waiting For Modem Reset";      //�ȴ�Medom��λ
// char * RASCS_WaitForCallback      = "Waiting For Callback";         //�ȴ��غ�
// char * RASCS_Projected            = "Projected";                    //����
// char * RASCS_StartAuthentication  = "Start Authentication";         //��ʼ��֤
// char * RASCS_CallbackComplete     = "Callback Complete";            //�غ����
// char * RASCS_LogonNetwork         = "Logon Network";                //��¼����
// char * RASCS_SubEntryConnected    = "";
// char * RASCS_SubEntryDisconnected = "";
// char * RASCS_Interactive          = "Interactive";                  //����
// char * RASCS_RetryAuthentication  = "Retry Authentication";         //������֤
// char * RASCS_CallbackSetByCaller  = "Callback Set By Caller";       //���ûغ�
// char * RASCS_PasswordExpired      = "Password Expired";             //���뵽��
// char * RASCS_Connected            = "Connected";                    //������
// char * RASCS_Disconnected         = "Disconnected";                 //�ѶϿ�

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

	//1. �Զ���ȡ "�������" ����
	//cb �����������ռ���ַ���  cEntries�������������
	Ret = RasEnumEntries(NULL, NULL, Entries, &cb, &cEntries); // ��������ɹ����򷵻�0
	if (Ret == 0) {
		printf("��ȡ���������:%s",Entries[0].szEntryName);
		//���ò��Ų��� �ڴ˱�ʾ	f_del_password�Ƿ�ɾ���û����룬ΪTRUEʱ��ԭ�����û�����ɾ����
		strcpy(rdParams.szEntryName, Entries[0].szEntryName);
		//CHAR szRasEntryName[RAS_MaxEntryName + 1] = { 0 };
		//for (i = 0 ;i < cEntries;i++ )
		//strcpy(szRasEntryName,Entries[i].szEntryName);
		//rdParams.dwSize = sizeof (RASDIALPARAMS);
		//strcpy(rdParams.szEntryName,szRasEntryName);
		//strcpy(rdParams.szPhoneNumber, " #777 " ); // ���õ�3G������#777����
		//strcpy(rdParams.szUserName, " �û��� " );
		//strcpy(rdParams.szPassword, " ���� " );
		//strcpy(rdParams.szDomain,"");//���Ҳ����Ҫ��ָ���������ָ������Ļ�����ע�͵�����һ��Ҫ���ϣ��±��������˼�ǻ�ȡ���һ�����ӳɹ�ʱ�Ĳ�����Ϣ��������±�����Ļ���ͬ���к�������������ж�����ʡ��
		// BOOL fPass;

	} else {
		//�ֶ�����
		strcpy(rdParams.szEntryName, "�������");
		//strcpy(rdParams.szPhoneNumber, " #777 " ); // ���õ�3G������#777����
		//strcpy(rdParams.szUserName, " �û��� " );
		//strcpy(rdParams.szPassword, " ���� " );
		//strcpy(rdParams.szDomain,"");//���Ҳ����Ҫ��ָ���������ָ������Ļ�����ע�͵�����һ��Ҫ���ϣ��±��������˼�ǻ�ȡ���һ�����ӳɹ�ʱ�Ĳ�����Ϣ��������±�����Ļ���ͬ���к�������������ж�����ʡ��

	}
	//dwSize 			//�ýṹ��ռ�ڴ�Ĵ�С(Bytes),һ������ΪSizeOf(RASDIALPARAMS)
	//szEntryName 		//������������
	//szPhoneNumber 	//���ź���
	//szCallbackNumber 	//�ؽк���
	//szUserName 		//�û�����
	//szPassword 		//�û�����
	//szDomain 			//����
	//��ȡ�������ӵĲ��Ų��� f_get_password�Ƿ���Ҫ�û�����
	if (RasGetEntryDialParams(NULL, &rdParams, &f_get_password) != 0) {
		//SetDlgItemText(IDC_IP, "Dial Failed, get entry adsl failed!");
		printf("�޷���ȡ���Ų���");
		return -1;
	}

	if (f_get_password == FALSE) {
		printf("�������");
		//SetDlgItemText(IDC_IP, "Dial Failed: get password failed!");
		return -1;
	}

	if ((Ret = RasDial(NULL, NULL, &rdParams, 0L, NULL, &hRasConn)) != 0) {
			//SetDlgItemText(IDC_IP, "Dial Failed!");
			printf("����ʧ��");
			return -1;
		}

	//��ȡ��ǰ������� RasEnumConnections()
	// var lprasconn : RASCONN ;//���ջ���ӵĻ�������ָ��
	//	var lpcb: DWORD;//��������С
	//	var lpcConnections : DWORD//ʵ�ʵĻ������Ŀ
	//(1)RASCONN = record
	//dwSize : DWORD;//�ýṹ��ռ�ڴ�Ĵ�С(Bytes),һ������Ϊ	SizeOf(RASCONN)
	//hrasconn : HRASCONN;//����ӵľ��
	//szEntryName : array[0..RAS_MaxEntryName] of char;//�����	������
	//szDeviceType : array[0..RAS_MaxDeviceType] of char;//���	�ӵ����õ��豸����
	//szDeviceName : array[0..RAS_MaxDeviceName] of char;//���	�ӵ����õ��豸����

	//��ȡָ�����ӵ�����״̬ RasGetConnectStatus()
	//hrasconn : HRASCONN; //ָ������ӵľ��
	//lprasconnstatus : LPRASCONNSTATUS//����״̬����

	//char tstr[40], temp[200];
	//wsprintf(temp, "Dial OK! %s", _strtime(tstr));
	//SetDlgItemText(IDC_IP, temp);
	// ɾ��cookie
	//remove("Q:\\Documents and Settings\\Administrator.PUDN\\Cookies\\administrator@news.survey.sina.com[1].txt");
	//remove("Q:\\Documents and Settings\\Administrator.PUDN\\Cookies\\administrator@sina.com[1].txt");
	//remove("Q:\\Documents and Settings\\Administrator.PUDN\\Cookies\\administrator@38.adsina.allyes[2].txt");
	//DeleteUrlCacheEntry("Cookie:administrator@news.survey.sina.com.cn/");
	// ˢ��IE
	/*
	 if (RasSetEntryDialParams(NULL, &rdParams, IS_DEL_PASSWORD)) {
	 //SetDlgItemText(IDC_IP, "Dial Failed, get entry adsl failed!");
	 printf("����ʧ��");
	 //return -1;
	 }
	 */
	return 0;
}

int DialConnect()
{

	if ((Ret = RasDial(NULL, NULL, &rdParams, 0L, NULL, &hRasConn)) != 0) {
			//SetDlgItemText(IDC_IP, "Dial Failed!");
			printf("����ʧ��");
			return -1;
		}
	return 0;
}

int DialDisConnect()
{
	// ���²���
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
			printf("����ʧ��");
			return -1;
		}
	return 0;
}


