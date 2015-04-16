#ifndef _SERVER_H_
#define _SERVER_H_

#define NET_TCP_ALIVE 							0x0
#define NET_TCP_ALIVE_RSP 						0x1
#define NET_TCP_RSP_OK 							0x2
#define NET_TCP_RSP_ERROR 						0x3


#define NET_TCP_INPUT_ALARM_STAT 				0x4
#define NET_TCP_DETECTOR_LOSS 					0x5
#define NET_TCP_ALARM_BATTERY_LOW_POWER 		0x6
#define NET_TCP_ALARM_NET_LOSS					0x7
#define NET_TCP_ALARM_POWEROFF					0x8
#define NET_TCP_LINK_SET						0x9
#define NET_TCP_ARMING      					0xA
#define NET_TCP_DISARMING						0xB
#define NET_TCP_SET_TIME						0xC
#define NET_TCP_GET_TIME						0xD
#define NET_TCP_STAT_GET						0xE
#define NET_TCP_SET_CELL_NUM					0xF
#define NET_TCP_SET_TEXT_NUM					0x10
#define NET_TCP_SET_DETECTOR_SENS				0x11
#define NET_TCP_GET_ARM_STAT					0x12
#define NET_TCP_GET_LINK_STAT					0x13
#define NET_TCP_GET_DETECTOR_SENS				0x14
#define NET_TCP_UPLOAD_ARM_STAT					0x15
#define NET_TCP_GET_BALANCE						0x16
#define NET_TCP_CANCEL_TEXT_ALARM				0x17
#define NET_TCP_CANCEL_CELL_ALARM				0x18
#define NET_TCP_DEVICE_REBOOT					0x19
#define NET_TCP_REMOTE_UPGRADE					0x20



#define NET_TCP_INPUT_ALARM_STAT_RSP				0x54
#define NET_TCP_DETECTOR_LOSS_RSP 					0x55
#define NET_TCP_ALARM_BATTERY_LOW_POWER_RSP 		0x56
#define NET_TCP_ALARM_NET_LOSS_RSP					0x57
#define NET_TCP_ALARM_POWEROFF_RSP					0x58
#define NET_TCP_LINK_SET_RSP						0x59
#define NET_TCP_ARMING_RSP      					0x5A
#define NET_TCP_DISARMING_RSP						0x5B
#define NET_TCP_SET_TIME_RSP						0x5C
#define NET_TCP_GET_TIME_RSP						0x5D
#define NET_TCP_STAT_GET_RSP						0x5E
#define NET_TCP_SET_CELL_NUM_RSP					0x5F
#define NET_TCP_SET_TEXT_NUM_RSP					0x60
#define NET_TCP_SET_DETECTOR_SENS_RSP				0x61
#define NET_TCP_GET_ARM_STAT_RSP					0x62
#define NET_TCP_GET_LINK_STAT_RSP					0x63
#define NET_TCP_GET_DETECTOR_SENS_RSP				0x64
#define NET_TCP_UPLOAD_ARM_STAT_RSP					0x65
#define NET_TCP_GET_BALANCE_RSP						0x66
#define NET_TCP_CANCEL_TEXT_ALARM_RSP				0x67
#define NET_TCP_CANCEL_CELL_ALARM_RSP				0x68
#define NET_TCP_DEVICE_REBOOT_RSP					0x69
#define NET_TCP_REMOTE_UPGRADE_RSP					0x70






#define MAXCONNECTD 100000

#define UNUNSED 0
#define USED 	1
#define MSGKEY 1024 

#define NET_FRAME_HEAD 0xFE
#define GSM_FRAME_HEAD 0xFD

typedef struct   
{  
    int fd; 
}msg_con; 

#define MAX_NEED_RECV 64

typedef struct
{
	int sock_fd;
	int sock_fd_used;
	int id;
	unsigned int ip;
	unsigned short port;
	int mode; //0 gprs 1 tcp
	int armed;
	char recv_buf[64];
	int recv_read;
	int recv_write;
	int index;
	char need_recv[MAX_NEED_RECV];
	int need_recv_read;
	int need_recv_write;
}peer_info;

typedef struct
{
	int peer_index;
	int sock_fd;
	int sys_id;
}sys_info;


#define MAX_QUEUE_LEN 1024

#define NEED_GET_STAT (1<<0)

typedef struct
{
	int i;
	int sock_fd;
	int bit_cmd;
}need_snd;

typedef struct
{
	int sock_fd;
	int bit_cmd;
}need_recv;


#define  MODULE_A 0x1
#define  MODULE_B 0x2
#define  MODULE_SWITCH 0xffff


#define UP_LOAD_THRESHHOLD 1024

typedef struct
{
	unsigned char package_buf[UP_LOAD_THRESHHOLD];
	int write;
	int pack_done;
}pack_info;


typedef struct
{	
	char head;
	short len;
	char num;
	char len_1;
	int id;
	int ip;
	char cmd;
	char xor;
	int crc;
}java_live_info;


typedef struct
{
	short size;
	short index[MAXCONNECTD];
}active_node;


#define MAX_SEND_LIVE_INTERVAL 10*1000

#endif
