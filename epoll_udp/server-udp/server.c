#if 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>

#define LINUX

#include "server.h"

peer_info peer[MAXCONNECTD];
//sys_info sys[MAXCONNECTD];

pthread_mutex_t pack_mutex;
pthread_cond_t pack_cond;


need_snd n_snd[MAX_QUEUE_LEN];
int n_snd_write;
int n_snd_read;

int java_fd;

pack_info pack;
//need_snd n_recv[MAX_QUEUE_LEN];
//int n_recv_write;
//int n_recv_read;



active_node a_node;

#if 0

int msqid;
typedef struct
{
	int sock_index;
	int len;
}msg_con;


void do_recv_msg_loop()
{
	int i;
	msg_con msg;
	peer_info *l_peer;
	while(1)
	{
		msgrcv(msqid, &msg, sizeof(msg), 0, 0);
		l_peer = &peer[msg.sock_index];
		for(i=0; i<msg.len; i++)
		{
			if(l_peer->recv_buf[l_peer->recv_read] == NET_FRAME_HEAD || 
				l_peer->recv_buf[l_peer->recv_read] == GSM_FRAME_HEAD)
			{
				recv_read_pos_forward();
			}
		}
		
	}
	
}


void recv_write_pos_backward(peer_info* l_peer)
{
	if (l_peer.recv_write == 0)
		l_peer.recv_write = 511;
	else
		l_peer.recv_write--;

}


void recv_write_pos_forward(peer_info* l_peer)
{
	if (l_peer.recv_write == 511)
		l_peer.recv_write = 0;
	else
		l_peer.recv_write++;
}

void recv_read_pos_backward(peer_info* l_peer)
{
	if (l_peer.recv_read== 0)
		l_peer.recv_read = 511;
	else
		l_peer.recv_read--;
}

void recv_read_pos_forward(peer_info* l_peer)
{
	if (l_peer.recv_read == 511)
		l_peer.recv_read = 0;
	else
		l_peer.recv_read++;
}

static int write_to_buf(int fd, char* buf, int len)
{
	int i;
	peer_info *local_peer;

	for(i=0; i<MAXCONNECTD; i++)
	{
		if(fd == peer[i].sock_fd)
		{
			local_peer = &peer[i];
			break;
		}
	}

	for(i=0; i<len; i++)
	{
		local_peer->recv_buf[local_peer->recv_write] = buf[i];
		recv_write_pos_forward();
	}
	
	msgsnd(msqid, &sock_index, sizeof(sock_index), 0);
#if 0
	if(local_peer.recv_write + len > 511)
	{
		memcpy(local_peer.recv_buf+local_peer.recv_write, buf, 511-local_peer.recv_write);
		memcpy(local_peer.recv_buf, buf+511-local_peer.recv_write, len-(511-local_peer.recv_write); 
	}
	else
		memcpy(local_peer.recv_buf+local_peer.recv_write, buf, len);
#endif
}



#endif




int debug_msg(const char *fmt, ...)
{
    int ret;
    va_list args;
    struct tm *tstruct ;
    static unsigned int log_count;

    time_t tsec ;


    tsec = time(NULL);
    tstruct = localtime( &tsec );

#if 0
    printf("[%d %04d-%02d-%02d %02d:%02d:%02d %5d] ",log_count++, tstruct->tm_year + 1900, tstruct->tm_mon + 1,
        tstruct->tm_mday,tstruct->tm_hour ,tstruct->tm_min,tstruct->tm_sec,
        getpid());
#endif
#if 1
    va_start(args,fmt);
    ret = vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
#endif	
    return ret;
}



int log_msg(int module, const char *fmt, ...)
{
	if(module & MODULE_SWITCH)
		debug_msg(fmt);
}


void n_snd_write_pos_backward()
{
	if (n_snd_write == 0)
		n_snd_write = MAX_QUEUE_LEN-1;
	else
		n_snd_write--;

}


void n_snd_write_pos_forward()
{
	if (n_snd_write == MAX_QUEUE_LEN-1)
		n_snd_write = 0;
	else
		n_snd_write++;
}

void n_snd_read_pos_backward()
{
	if (n_snd_read== 0)
		n_snd_read = MAX_QUEUE_LEN-1;
	else
		n_snd_read--;
}

void n_snd_read_pos_forward()
{
	if (n_snd_read == MAX_QUEUE_LEN-1)
		n_snd_read = 0;
	else
		n_snd_read++;
}


void n_recv_write_pos_forward(int index)
{
	if (peer[index].need_recv_write == MAX_NEED_RECV-1)
		peer[index].need_recv_write = 0;
	else
		peer[index].need_recv_write++;
}

void n_recv_read_pos_forward(int index)
{
	if (peer[index].need_recv_read== MAX_NEED_RECV-1)
			peer[index].need_recv_read = 0;
		else
			peer[index].need_recv_read++;

}



void GetCrc32Long(const char *ptr, int len, char *out) 
{ 
	static unsigned int Crc32Table[256]={ 
	0x00000000,0x77073096,0xEE0E612C,0x990951BA, 
	0x076DC419,0x706AF48F,0xE963A535,0x9E6495A3, 
	0x0EDB8832,0x79DCB8A4,0xE0D5E91E,0x97D2D988, 
	0x09B64C2B,0x7EB17CBD,0xE7B82D07,0x90BF1D91, 
	0x1DB71064,0x6AB020F2,0xF3B97148,0x84BE41DE, 
	0x1ADAD47D,0x6DDDE4EB,0xF4D4B551,0x83D385C7, 
	0x136C9856,0x646BA8C0,0xFD62F97A,0x8A65C9EC, 
	0x14015C4F,0x63066CD9,0xFA0F3D63,0x8D080DF5, 
	0x3B6E20C8,0x4C69105E,0xD56041E4,0xA2677172, 
	0x3C03E4D1,0x4B04D447,0xD20D85FD,0xA50AB56B, 
	0x35B5A8FA,0x42B2986C,0xDBBBC9D6,0xACBCF940, 
	0x32D86CE3,0x45DF5C75,0xDCD60DCF,0xABD13D59, 
	0x26D930AC,0x51DE003A,0xC8D75180,0xBFD06116, 
	0x21B4F4B5,0x56B3C423,0xCFBA9599,0xB8BDA50F, 
	0x2802B89E,0x5F058808,0xC60CD9B2,0xB10BE924, 
	0x2F6F7C87,0x58684C11,0xC1611DAB,0xB6662D3D, 
	0x76DC4190,0x01DB7106,0x98D220BC,0xEFD5102A, 
	0x71B18589,0x06B6B51F,0x9FBFE4A5,0xE8B8D433, 
	0x7807C9A2,0x0F00F934,0x9609A88E,0xE10E9818, 
	0x7F6A0DBB,0x086D3D2D,0x91646C97,0xE6635C01, 
	0x6B6B51F4,0x1C6C6162,0x856530D8,0xF262004E, 
	0x6C0695ED,0x1B01A57B,0x8208F4C1,0xF50FC457, 
	0x65B0D9C6,0x12B7E950,0x8BBEB8EA,0xFCB9887C, 
	0x4DB26158,0x3AB551CE,0xA3BC0074,0xD4BB30E2, 
	0x4ADFA541,0x3DD895D7,0xA4D1C46D,0xD3D6F4FB, 
	0x4369E96A,0x346ED9FC,0xAD678846,0xDA60B8D0, 
	0x44042D73,0x33031DE5,0xAA0A4C5F,0xDD0D7CC9, 
	0x5005713C,0x270241AA,0xBE0B1010,0xC90C2086, 
	0x5768B525,0x206F85B3,0xB966D409,0xCE61E49F, 
	0x5EDEF90E,0x29D9C998,0xB0D09822,0xC7D7A8B4, 
	0x59B33D17,0x2EB40D81,0xB7BD5C3B,0xC0BA6CAD, 
	0xEDB88320,0x9ABFB3B6,0x03B6E20C,0x74B1D29A, 
	0xEAD54739,0x9DD277AF,0x04DB2615,0x73DC1683, 
	0xE3630B12,0x94643B84,0x0D6D6A3E,0x7A6A5AA8, 
	0xE40ECF0B,0x9309FF9D,0x0A00AE27,0x7D079EB1, 
	0xF00F9344,0x8708A3D2,0x1E01F268,0x6906C2FE, 
	0xF762575D,0x806567CB,0x196C3671,0x6E6B06E7, 
	0xFED41B76,0x89D32BE0,0x10DA7A5A,0x67DD4ACC, 
	0xF9B9DF6F,0x8EBEEFF9,0x17B7BE43,0x60B08ED5, 
	0xD6D6A3E8,0xA1D1937E,0x38D8C2C4,0x4FDFF252, 
	0xD1BB67F1,0xA6BC5767,0x3FB506DD,0x48B2364B, 
	0xD80D2BDA,0xAF0A1B4C,0x36034AF6,0x41047A60, 
	0xDF60EFC3,0xA867DF55,0x316E8EEF,0x4669BE79, 
	0xCB61B38C,0xBC66831A,0x256FD2A0,0x5268E236, 
	0xCC0C7795,0xBB0B4703,0x220216B9,0x5505262F, 
	0xC5BA3BBE,0xB2BD0B28,0x2BB45A92,0x5CB36A04, 
	0xC2D7FFA7,0xB5D0CF31,0x2CD99E8B,0x5BDEAE1D, 
	0x9B64C2B0,0xEC63F226,0x756AA39C,0x026D930A, 
	0x9C0906A9,0xEB0E363F,0x72076785,0x05005713, 
	0x95BF4A82,0xE2B87A14,0x7BB12BAE,0x0CB61B38, 
	0x92D28E9B,0xE5D5BE0D,0x7CDCEFB7,0x0BDBDF21, 
	0x86D3D2D4,0xF1D4E242,0x68DDB3F8,0x1FDA836E, 
	0x81BE16CD,0xF6B9265B,0x6FB077E1,0x18B74777, 
	0x88085AE6,0xFF0F6A70,0x66063BCA,0x11010B5C, 
	0x8F659EFF,0xF862AE69,0x616BFFD3,0x166CCF45, 
	0xA00AE278,0xD70DD2EE,0x4E048354,0x3903B3C2, 
	0xA7672661,0xD06016F7,0x4969474D,0x3E6E77DB, 
	0xAED16A4A,0xD9D65ADC,0x40DF0B66,0x37D83BF0, 
	0xA9BCAE53,0xDEBB9EC5,0x47B2CF7F,0x30B5FFE9, 
	0xBDBDF21C,0xCABAC28A,0x53B39330,0x24B4A3A6, 
	0xBAD03605,0xCDD70693,0x54DE5729,0x23D967BF, 
	0xB3667A2E,0xC4614AB8,0x5D681B02,0x2A6F2B94, 
	0xB40BBE37,0xC30C8EA1,0x5A05DF1B,0x2D02EF8D 
	}; 

	unsigned long crc = 0xFFFFFFFF; 
	char crcStr[64];  

	while(len > 0) 
	{ 
		crc = ((crc >> 8) & 0x00FFFFFF) ^ Crc32Table[(crc ^ *ptr) & 0xFF]; 
		ptr++; 
		len--; 
	} 

	sprintf(crcStr,"%ld",crc^0xffffffff); 
	strcpy(out, crcStr); 
}

void GetCrc32(const char *ptr, int len, char *out) 
{ 
	char crcStr[32]; 
	int i,j; 
	int crcInt = 0; 


	GetCrc32Long(ptr, len, out); 
	crcInt = atoi(out); 
	sprintf(crcStr,"%x",crcInt); 
	for(i=0;i<strlen(crcStr);i++) 
	{ 
		crcStr[i]=toupper(crcStr[i]); 
	} 

	strcpy(out,""); 

	if (strlen(crcStr)<8) 
	{ 
		for (j=0;j<8-strlen(crcStr);j++) 
		{ 
		strcat(out, "0"); 
		}  
	} 

	strcat(out, crcStr); 
} 



static int make_socket_non_blocking (int sfd)
{
	int flags, s;

	flags = fcntl (sfd, F_GETFL, 0);
	if (flags == -1)
	{
		perror ("fcntl");
		return -1;
	}

	flags |= O_NONBLOCK;
	s = fcntl (sfd, F_SETFL, flags);
	if (s == -1)
	{
		perror ("fcntl");
		return -1;
	}

	return 0;
}

static int do_accept_utils(peer_info* peer, int infd, int efd, struct sockaddr* in_addr, socklen_t* in_len)
{
	int i, s;
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
	struct epoll_event event;


	for(i=0; i<MAXCONNECTD; i++)
	{
		if(peer[i].sock_fd_used == UNUNSED)
		{
			peer[i].sock_fd = infd;
			debug_msg("i: %d, infd: %d\n", i, infd);
			peer[i].sock_fd_used = USED;
			insert_active_list(i);
			break;
		}
	}

#if 1
	s = getnameinfo(in_addr, *in_len, hbuf, sizeof(hbuf),
	               sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
	if (s == 0)
	{
	  debug_msg("Accepted connection on descriptor %d "
	         "(host=%s, port=%s)\n", infd, hbuf, sbuf);
	}
#endif
	/* Make the incoming socket non-blocking and add it to the
	 list of fds to monitor. */
	s = make_socket_non_blocking(infd);
	if (s == -1)
		abort();

	event.data.fd = infd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
	if (s == -1)
	{
	  perror("epoll_ctl");
	  abort();
	}
	n_snd[n_snd_write].i = i;
	n_snd[n_snd_write].sock_fd = infd;
	n_snd[n_snd_write].bit_cmd = NEED_GET_STAT;
	n_snd_write_pos_forward();
}

static int do_close_utils()
{
	
}

static int create_and_bind (char *port)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
	hints.ai_flags = AI_PASSIVE;     /* All interfaces */

	s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror (s));
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0)
		{
		  /* We managed to bind successfully! */
		  break;
		}

		close (sfd);
	}

	if (rp == NULL)
	{
		fprintf (stderr, "Could not bind\n");
		return -1;
	}

	freeaddrinfo (result);

	return sfd;
}


int show_delay(int num)
{
	struct timeval tv_s;
	struct timezone tz_s;
	static long old_sec;
	static long old_mil;
	static int i=0;

	gettimeofday(&tv_s, &tz_s);

	i++;
	if(i == 500)
	{	
		i = 0;
		printf("diff usec: %ld, num: %d, connected: %d\n", (tv_s.tv_sec-old_sec)*1000000+tv_s.tv_usec-old_mil, num, a_node.size);
	}
	old_sec = tv_s.tv_sec;
	old_mil = tv_s.tv_usec;
}

int init_active_list()
{
	a_node.size = 0;
}
int insert_active_list(int index)
{
	int i;
	a_node.index[a_node.size] = index;
	a_node.size++;
}
int delete_active_list(int index)
{
	int i;
	char* dst, *src, *ptr;
	for(i=0; i<a_node.size; i++)
	{
		if(a_node.index[i] == index)
		{	
			*ptr = a_node.index;
			src = ptr+i+1;
			dst = ptr+i;
			memcpy(src, dst, a_node.size-i-1);
		}
	}
}



int init_sys_para()
{
	int i, j;

	memset((void*)peer, 0, sizeof(peer));
	debug_msg("sizeof(peer): %d, peer[0].index %d\n", sizeof(peer), peer[0].index);

	memset((void*)n_snd, 0, sizeof(n_snd));
	
	
	pthread_mutex_init(&pack_mutex, NULL);
	pthread_cond_init(&pack_cond, NULL);

	init_active_list();
	
#if 0
	gettimeofday(&tv_s, &tz_s);
	for(j=0; j<MAXCONNECTD; j++)
	{
		for(i=0; i<MAXCONNECTD; i++)
			;
	}
	gettimeofday(&tv_e, &tz_e);
	debug_msg("tv_s.s: %d, tv_s.u: %d, \n", tv_e.tv_sec-tv_s.tv_sec, tv_e.tv_usec-tv_s.tv_usec);
#endif
	#if 0
	struct msgstru msgs;  
	int msg_type;  
	char str[256];  
	int ret_value;  
	

	msqid = msgget(MSGKEY,IPC_EXCL);  /*检查消息队列是否存在*/  
	if(msqid < 0)
	{  
		msqid = msgget(MSGKEY,IPC_CREAT|0666);/*创建消息队列*/  
		if(msqid <0)
		{  
			debug_msg("failed to create msq | errno=%d [%s]\n",errno,strerror(errno));  
			exit(-1);  
		}  
	}   

	msgsnd(msqid,&msgs,sizeof(struct msgstru),IPC_NOWAIT);  
	#endif
}

int match_id(int fd, peer_info** l_peer)
{
	int i;

	for(i=0; i<MAXCONNECTD; i++)
	{
		if(peer[i].sock_fd == fd)
		{	
			*l_peer = &peer[i];
			
			//debug_msg("*l_peer: %d, i : %d, peer[i].sockfd: %d, l_peer.index: %d\n", *l_peer, i, peer[i].sock_fd, (*l_peer)->index);
			break;
		}
	}
}

unsigned char calcfcs(unsigned char *pmsg, unsigned char len)
{
	unsigned char result = 0;
	while (len--)
	{
		result ^= *pmsg++;
	}
	return result;
}

int tcp_live_rsp(peer_info* l_peer, char* cmd)
{	
	int ret;
	char frame[4];
	frame[0] = cmd[0];
	frame[1] = 0;
	frame[2] = NET_TCP_ALIVE_RSP;
	frame[3] = calcfcs(frame+1,frame[1]+2);
	
	ret = send(l_peer->sock_fd, &frame, sizeof(frame), 0);
	//debug_msg("l_peer->sock_fd: %d ret: %d\n", l_peer->sock_fd, ret);
}
int deal_recv_one_cmd(peer_info* l_peer, char* cmd)
{
	int len;
	int ret;
	int index;
	int l_id;
	int l_ip;
	len = cmd[1];

	debug_msg("recv one cmd\n");
	if(calcfcs(cmd+1, len+2) != cmd[len+3])
		goto error;
	switch(cmd[2])
	{
		case NET_TCP_ALIVE:
			debug_msg("recv live\n");
			tcp_live_rsp(l_peer, cmd);
			break;
		case NET_TCP_LINK_SET_RSP:						
 		case NET_TCP_ARMING_RSP:      					
 		case NET_TCP_DISARMING_RSP:						
 		case NET_TCP_SET_TIME_RSP:
 		case NET_TCP_SET_CELL_NUM_RSP:					
 		case NET_TCP_SET_TEXT_NUM_RSP:					
 		case NET_TCP_SET_DETECTOR_SENS_RSP:
		case NET_TCP_INPUT_ALARM_STAT:
		case NET_TCP_DETECTOR_LOSS:
		case NET_TCP_ALARM_BATTERY_LOW_POWER:
		case NET_TCP_ALARM_NET_LOSS:
		case NET_TCP_ALARM_POWEROFF:
		case NET_TCP_GET_TIME_RSP:
		case NET_TCP_STAT_GET_RSP:
		case NET_TCP_GET_ARM_STAT_RSP:
		case NET_TCP_GET_LINK_STAT_RSP:
		case NET_TCP_GET_DETECTOR_SENS_RSP:
		case NET_TCP_UPLOAD_ARM_STAT:
			if((pack.pack_done == 0) && UP_LOAD_THRESHHOLD - pack.write > len+11)
			{
				index = pack.write;
				pack.package_buf[pack.write++] = len+4;
				l_id = htonl(l_peer->id);
				l_ip = htonl(l_peer->ip);
				memcpy((pack.package_buf)+pack.write, &l_id, sizeof(l_peer->id));
				memcpy((pack.package_buf)+pack.write, &l_ip, sizeof(l_peer->id));
				pack.write += 8;
				pack.package_buf[pack.write++] = cmd[2];
				memcpy((pack.package_buf)+pack.write, cmd+3, len); 
				pack.write += len;
				pack.package_buf[pack.write++] = calcfcs((pack.package_buf)+index,len+10);
				*(short*)(pack.package_buf+1) += len+11;
				pack.package_buf[3] += 1;
			}
			else
			{	
				pthread_mutex_lock(&pack_mutex);
				pack.pack_done = 1;
				pthread_mutex_unlock(&pack_mutex);
				while(pack.pack_done == 1)
					sleep(1);
				index = pack.write;
				pack.package_buf[pack.write++] = len+4;
				l_id = htonl(l_peer->id);
				l_ip = htonl(l_peer->ip);
				memcpy((pack.package_buf)+pack.write, &l_id, sizeof(l_peer->id));
				memcpy((pack.package_buf)+pack.write, &l_ip, sizeof(l_peer->id));
				pack.write += 8;
				pack.package_buf[pack.write++] = cmd[2];
				memcpy((pack.package_buf)+pack.write, cmd+3, len); 
				pack.write += len;
				pack.package_buf[pack.write++] = calcfcs((pack.package_buf)+index,len+10);
				*(short*)(pack.package_buf+1) += len+11;
				pack.package_buf[3] += 1;
				
			}
			break;
	

			
	
		default:
			break;
	}
		
error:
	return ret;
}

int recv_message(int fd)
{
	int i, a, b;
	int ret;
	peer_info* l_peer;
	char* ptr;
	int len;
	int availble_recv_len;
	int parse_len;
	int one_command = 0;
	unsigned char one_cmd[64]={};
	unsigned char buf[512]= {};
	match_id(fd, &l_peer);
	ptr = l_peer->recv_buf;

	
	while(1)
	{
		ret = recv(fd, buf, sizeof(buf), 0);
		debug_msg("recv len: %d\n", ret);
		for(i=0; i<ret; i++)
			debug_msg("buf[%d]: %c ", i, buf[i]);
		debug_msg("\n");
		if(ret <= 0)
			goto error;
		parse_len = ret;
		b = parse_len;
		
		debug_msg("line: %d\n", __LINE__);
		while(parse_len > 0)
		{
			if(l_peer->index != 0)
			{
				debug_msg("line: %d, l_peer->index: %d\n", __LINE__, l_peer->index);
				memcpy(one_cmd, ptr, l_peer->index);
				if(l_peer->index == 1)
				{
					len = buf[0];
					if(parse_len >= len+3)
					{
						debug_msg("line: %d, l_peer->index: %d\n", __LINE__, l_peer->index);
						memcpy(one_cmd+l_peer->index, buf, len+3);
						parse_len -= (len+3);
						deal_recv_one_cmd(l_peer, one_cmd);
						l_peer->index = 0;
					}
					else
					{
						memcpy(one_cmd+l_peer->index, buf, parse_len);
						memcpy(ptr, one_cmd, parse_len+l_peer->index);
						l_peer->index = parse_len+l_peer->index;
						parse_len -= parse_len;
						debug_msg("line: %d, l_peer->index: %d\n", __LINE__, l_peer->index);
					}
				}
				else
				{
					len = one_cmd[1];
					a = len+4-l_peer->index;
					if(parse_len >= a)
					{	
						debug_msg("line: %d, l_peer->index: %d\n", __LINE__, l_peer->index);
						memcpy(one_cmd+l_peer->index, buf, a);
						parse_len -= a;
						deal_recv_one_cmd(l_peer, one_cmd);
						l_peer->index = 0;
					}
					else
					{
						memcpy(one_cmd+l_peer->index, buf, parse_len);
						memcpy(ptr, one_cmd, parse_len+l_peer->index);
						l_peer->index = parse_len+l_peer->index;
						parse_len -= parse_len;
						debug_msg("line: %d, l_peer->index: %d\n", __LINE__, l_peer->index);
					}	
				}
			}
			else
			{	
				/*
				while((buf[b-parse_len] != 0xFD) && (buf[b-parse_len] != 0xFE))
					parse_len--;
				*/
				
				debug_msg("line: %d, b: %d, parse_len: %d\n", __LINE__, b, parse_len);
				if((buf[b-parse_len] == 0xFD) || (buf[b-parse_len] == 0xFE))
				{	
					//memcpy(one_cmd, buf+(b-parse_len), 1);
					one_cmd[0] = buf[b-parse_len];
					parse_len--;
					debug_msg("line: %d\n", __LINE__);
					if(parse_len > 0)
					{	
						//memcpy(one_cmd+1, buf+(b-parse_len), 1);
						one_cmd[1] = buf[b-parse_len];
						parse_len--;
						len = one_cmd[1];
						debug_msg("line: %d, len: %d, \n", __LINE__, len);
						if(parse_len < len+2)
						{
							debug_msg("line: %d\n", __LINE__);
							l_peer->index = 2+parse_len;
							if(parse_len != 0)
							{
								memcpy(ptr, one_cmd, 2);
								memcpy(ptr+2, buf+(b-parse_len), parse_len);
								parse_len -= parse_len;
							}
						}
						else
						{
						debug_msg("line: %d\n", __LINE__);
							memcpy(one_cmd+2, buf+(b-parse_len), len+2);
							parse_len -= len+2;
							deal_recv_one_cmd(l_peer, one_cmd);
						}
					}
					else
					{
						l_peer->index = 1;
						*ptr = buf[b-parse_len-1];
					}
				}
				else
					parse_len--;
			}
		}
	}

error:
	return ret;
}


void* do_snd_msg(void* arg)
{
	int i;
	int index;
	

	//server end initiative snd msg
	while(n_snd_read != n_snd_write)
	{
		for(i=0; i<sizeof(int); i++)
		{	
			index = n_snd[n_snd_read].i;
			switch (n_snd[n_snd_read].bit_cmd & (1<<i))
			{
				case NEED_GET_STAT:
					
					//do snd msg;
					//peer[index].need_recv[peer[index].need_recv_write] = 
					break;
				default:
					break;
			}
			n_snd[n_snd_read].bit_cmd = 0;
			n_snd_read_pos_forward();
		}
	}

	
	
	

	
}


int send_java_live()
{	
	java_live_info java;
	unsigned char java_live[18];

	java.head = 0xfe;
	java.len = 14;
	java.num = 1;
	java.len_1 = 10;
	java.cmd = NET_TCP_ALIVE;
	java.xor = calcfcs((((char*)&java)+1),10);
	GetCrc32((((char*)&java)+1), 11, (char*)&(java.crc));
		
}


void* do_upload_msg(void* arg)
{
	struct timeval tv_s;
	struct timezone tz_s;
	static long old_sec;
	static long old_mil;
	long diff;

	gettimeofday(&tv_s, &tz_s);
	
	//printf("diff usec: %ld,\n", (tv_s.tv_sec-old_sec)*1000000+tv_s.tv_usec-old_mil);
	diff = (tv_s.tv_sec-old_sec)*1000000+tv_s.tv_usec-old_mil;
	old_sec = tv_s.tv_sec;
	old_mil = tv_s.tv_usec;

	if(diff > 1000*1000*10)
		send_java_live();

	if(diff > 5000)
	{
		pthread_mutex_lock(&pack_mutex);
		pack.pack_done = 1;
		pthread_mutex_unlock(&pack_mutex);
	}
	if(pack.pack_done)
	{
	 	GetCrc32(pack.package_buf+1, *(short*)(pack.package_buf+1), (pack.package_buf+pack.write));
		send(java_fd, pack.package_buf, (*(short*)(pack.package_buf+1))+1, 0);
		pthread_mutex_lock(&pack_mutex);
		pack.pack_done = 0;
		pthread_mutex_unlock(&pack_mutex);
	}
	
}

int get_msg_loop(int sock_fd)
{
	
}
void* do_get_msg(void* arg)
{
	int cfd;
	int recbytes;
	int sin_size;
	char buffer[1024]={0};	 
	struct sockaddr_in s_add,c_add;
	unsigned short portnum=0x8888; 
	
	printf("Hello,welcome to client !\r\n");
	
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == cfd)
	{
		printf("socket fail ! \r\n");
		
	}
	printf("socket ok !\r\n");
	
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr("192.168.1.2");
	s_add.sin_port=htons(portnum);
	printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);
	
	
	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("connect fail !\r\n");
	}
	printf("connect ok !\r\n");

	get_msg_loop(cfd);
}



int init_sys_thread()
{
	int err;
    pthread_t snd_tid;
	pthread_t upload_tid;
	pthread_t get_tid;
	
    err = pthread_create(&snd_tid, NULL, do_snd_msg, NULL);
    if (err != 0)
        debug_msg("can't create thread: %s\n", strerror(err));

	//snd msg to java end
	err = pthread_create(&upload_tid, NULL, do_upload_msg, NULL);
    if (err != 0)
        debug_msg("can't create thread: %s\n", strerror(err));

	err = pthread_create(&get_tid, NULL, do_get_msg, NULL);
    if (err != 0)
        debug_msg("can't create thread: %s\n", strerror(err));
    
    pthread_join(snd_tid, NULL);
	pthread_join(upload_tid, NULL);
	pthread_join(get_tid, NULL);
}




int main_l (int argc, char *argv[])
{
	int sfd, s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;
	
	

	if (argc != 2)
	{
		fprintf (stderr, "Usage: %s [port]\n", argv[0]);
		exit (EXIT_FAILURE);
	}

	init_sys_para();
	//init_sys_thread();

	sfd = create_and_bind(argv[1]);
	if(sfd == -1)
		abort();

	s = make_socket_non_blocking(sfd);
	if(s == -1)
		abort();

	s = listen(sfd, SOMAXCONN);
	if (s == -1)
	{
	  perror("listen");
	  abort();
	}

	efd = epoll_create1(0);
	if (efd == -1)
	{
	  perror ("epoll_create");
	  abort ();
	}

	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
	if (s == -1)
	{
	  perror ("epoll_ctl");
	  abort();
	}

	/* Buffer where events are returned */
	events = calloc(MAXCONNECTD+1, sizeof(event));
	
	/* The event loop */
	while (1)
	{
		int n, i;

		n = epoll_wait(efd, events, MAXCONNECTD+1, -1);
		show_delay(n);
		for (i = 0; i < n; i++)
		{
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) ||
			      (!(events[i].events & EPOLLIN)))
			{
			      /* An error has occured on this fd, or the socket is not
			         ready for reading (why were we notified then?) */
			  fprintf (stderr, "epoll error\n");
			  //do_close_utils(events[i].data.fd);
			  close (events[i].data.fd);
			  continue;
			}

			else if (sfd == events[i].data.fd)
			{
				/* We have a notification on the listening socket, which
				 means one or more incoming connections. */
				while (1)
				{
					int infd;
					struct sockaddr in_addr;
					socklen_t in_len;

					in_len = sizeof(in_addr);
					infd = accept (sfd, &in_addr, &in_len);
					if (infd == -1)
		            {
						if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
						{
						  /* We have processed all incoming
						     connections. */
						  break;
						}
						else
						{
						  perror ("accept");
						  break;
						}
		            }
					do_accept_utils(peer, infd, efd, &in_addr, &in_len);
					
		        }
				continue;
			 }
			 else
			 {
				/* We have data on the fd waiting to be read. Read and
				display it. We must read whatever data is available
				completely, as we are running in edge-triggered mode
				and won't get a notification again for the same
				data. */
				int done = 0;

				while (1)
				{
					ssize_t count;
					char buf[512];

					//count = recv (events[i].data.fd, buf, sizeof(buf), 0);
					count = recv_message(events[i].data.fd);
					if (count == -1)
					{
						/* If errno == EAGAIN, that means we have read all
						 data. So go back to the main loop. */
						if (errno != EAGAIN)
						{
							  perror ("read");
							  done = 1;
						}
						break;
					}
					else if (count == 0)
					{
						/* End of file. The remote has closed the
						 connection. */
						done = 1;
						break;
					}
					//write_to_buf(events[i].data.fd, buf, count);
				}

				if (done)
				{
					debug_msg ("Closed connection on descriptor %d\n",
					      events[i].data.fd);

					/* Closing the descriptor will make epoll remove it
					 from the set of descriptors which are monitored. */
					close (events[i].data.fd);
			     }
			   }
			}
	}

	free(events);
	close(sfd);
	close(efd);

	return EXIT_SUCCESS;
}



#if 0
#define MAXEVENTS 64

static int make_socket_non_blocking (int sfd)
{
	int flags, s;

	flags = fcntl (sfd, F_GETFL, 0);
	if (flags == -1)
	{
		perror ("fcntl");
		return -1;
	}

	flags |= O_NONBLOCK;
	s = fcntl (sfd, F_SETFL, flags);
	if (s == -1)
	{
		perror ("fcntl");
		return -1;
	}

	return 0;
}

static int create_and_bind (char *port)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
	hints.ai_flags = AI_PASSIVE;     /* All interfaces */

	s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror (s));
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0)
		{
		  /* We managed to bind successfully! */
		  break;
		}

		close (sfd);
	}

	if (rp == NULL)
	{
		fprintf (stderr, "Could not bind\n");
		return -1;
	}

	freeaddrinfo (result);

	return sfd;
}

int main (int argc, char *argv[])
{
	int sfd, s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;

	if (argc != 2)
	{
		fprintf (stderr, "Usage: %s [port]\n", argv[0]);
		exit (EXIT_FAILURE);
	}

	sfd = create_and_bind(argv[1]);
	if(sfd == -1)
		abort();

	s = make_socket_non_blocking(sfd);
	if(s == -1)
		abort();

	s = listen(sfd, SOMAXCONN);
	if (s == -1)
	{
	  perror("listen");
	  abort();
	}

	efd = epoll_create1(0);
	if (efd == -1)
	{
	  perror ("epoll_create");
	  abort ();
	}

	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
	if (s == -1)
	{
	  perror ("epoll_ctl");
	  abort();
	}

	/* Buffer where events are returned */
	events = calloc(MAXEVENTS, sizeof(event));

	/* The event loop */
	while (1)
	{
		int n, i;

		n = epoll_wait(efd, events, MAXEVENTS, -1);
		for (i = 0; i < n; i++)
		{
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) ||
			      (!(events[i].events & EPOLLIN)))
			{
			      /* An error has occured on this fd, or the socket is not
			         ready for reading (why were we notified then?) */
			  fprintf (stderr, "epoll error\n");
			  close (events[i].data.fd);
			  continue;
			}

			else if (sfd == events[i].data.fd)
			{
				/* We have a notification on the listening socket, which
				 means one or more incoming connections. */
				while (1)
				{
					struct sockaddr in_addr;
					socklen_t in_len;
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					in_len = sizeof(in_addr);
					infd = accept (sfd, &in_addr, &in_len);
					if (infd == -1)
		            {
						if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
						{
						  /* We have processed all incoming
						     connections. */
						  break;
						}
						else
						{
						  perror ("accept");
						  break;
						}
		            }

					s = getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf),
					               sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
					if (s == 0)
					{
					  debug_msg("Accepted connection on descriptor %d "
					         "(host=%s, port=%s)\n", infd, hbuf, sbuf);
					}

					/* Make the incoming socket non-blocking and add it to the
					 list of fds to monitor. */
					s = make_socket_non_blocking(infd);
					if (s == -1)
						abort();

					event.data.fd = infd;
					event.events = EPOLLIN | EPOLLET;
					s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
					if (s == -1)
					{
					  perror("epoll_ctl");
					  abort();
					}
		        }
				continue;
			 }
			 else
			 {
				/* We have data on the fd waiting to be read. Read and
				display it. We must read whatever data is available
				completely, as we are running in edge-triggered mode
				and won't get a notification again for the same
				data. */
				int done = 0;

				while (1)
				{
					ssize_t count;
					char buf[512];

					count = read (events[i].data.fd, buf, sizeof(buf));
					if (count == -1)
					{
						/* If errno == EAGAIN, that means we have read all
						 data. So go back to the main loop. */
						if (errno != EAGAIN)
						{
							  perror ("read");
							  done = 1;
						}
						break;
					}
					else if (count == 0)
					{
						/* End of file. The remote has closed the
						 connection. */
						done = 1;
						break;
					}

					/* Write the buffer to standard output */
					s = write (1, buf, count);
					if (s == -1)
					{
						  perror ("write");
						  abort ();
					}
				}

				if (done)
				{
					debug_msg ("Closed connection on descriptor %d\n",
					      events[i].data.fd);

					/* Closing the descriptor will make epoll remove it
					 from the set of descriptors which are monitored. */
					close (events[i].data.fd);
			     }
			   }
			}
	}

	free(events);
	close(sfd);
	close(efd);

	return EXIT_SUCCESS;
}
#endif

int get_cpu_core_num( )  
{  
#if defined(WIN32)	
	SYSTEM_INFO info;  
	GetSystemInfo(&info);  
	return info.dwNumberOfProcessors;  
#elif defined(LINUX) || defined(SOLARIS) || defined(AIX)  
	return get_nprocs();   //GNU fuction  
#else  
#error	did not support system
#endif	
}  

int main (int argc, char *argv[])
{	
	int core_num;

	core_num = get_cpu_core_num(); 
	debug_msg("core_num: %d\n", core_num);
	
	return 0;
}
#endif
