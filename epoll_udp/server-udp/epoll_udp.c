#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>
#include <sys/sysinfo.h>


#include "server.h"

peer_info peer[MAXCONNECTD];
//sys_info sys[MAXCONNECTD];

pthread_mutex_t pack_mutex;
pthread_cond_t pack_cond;

int listener;

need_snd n_snd[MAX_QUEUE_LEN];
int n_snd_write;
int n_snd_read;
int java_fd;
pack_info pack;
active_node a_node;




#define MAXBUF 1024
#define MAXEPOLLSIZE 100000


unsigned char calcfcs(unsigned char *pmsg, unsigned char len)
{
	unsigned char result = 0;
	while (len--)
	{
		result ^= *pmsg++;
	}
	return result;
}

unsigned int dot_ip_to_u32(char* str)
{
    int a, b, c, d;

    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    return ((a&0xff)<<24)|((b&0xff)<<16)|((c&0xff)<<8)|(d&0xff);
}


int dot_ip_modify(char* str)
{
    int a, b, c, d;

    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    sprintf(str, "%03d.%03d.%03d.%03d", a, b, c, d);
    return 0;
}


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
#if 0
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


int setnonblocking(int sockfd)
{
  if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1)
  {
    return -1;
  }
  return 0;
}


int tcp_live_rsp(peer_info* l_peer, char* cmd)
{	
	int ret;
	char frame[4];
	struct sockaddr_in addr;  
    int addr_len =sizeof(struct sockaddr_in); 
	char buf[5]={};

	bzero(&addr,sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(l_peer->port);  
    addr.sin_addr.s_addr = htonl(l_peer->ip);  
	
	frame[0] = cmd[0];
	frame[1] = 0;
	frame[2] = NET_TCP_ALIVE_RSP;
	frame[3] = calcfcs(frame+1,frame[1]+2);
	
	debug_msg("sendto: %s,port:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	ret = sendto(listener, &frame, sizeof(frame), 0, (struct sockaddr *)&addr, addr_len);
	//debug_msg("l_peer->sock_fd: %d ret: %d\n", l_peer->sock_fd, ret);
	debug_msg("ret: %d\n", ret);
}


/*
 pthread_handle_message – 线程处理 socket 上的消息收发
 */
void* pthread_handle_message(int* sock_fd)
{
  char recvbuf[MAXBUF + 1];
  char sendbuf[MAXBUF+1];
  int  ret;
  int  new_fd;
  struct sockaddr_in client_addr;
  socklen_t cli_len=sizeof(client_addr);


  new_fd=*sock_fd; 


  /* 开始处理每个新连接上的数据收发 */
  bzero(recvbuf, MAXBUF + 1);
  bzero(sendbuf, MAXBUF + 1);


  /* 接收客户端的消息 */
  ret = recvfrom(new_fd, recvbuf, MAXBUF, 0, (struct sockaddr *)&client_addr, &cli_len);
  if (ret > 0){
    printf("socket %d recv from : %s : %d message: %s ，%d bytes/n",
           new_fd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), recvbuf, ret);
 
  }
  else
  {
    printf("received failed! error code %d，message : %s /n",
      errno, strerror(errno));    
  }
  /* 处理每个新连接上的数据收发结束 */ 
  //printf("pthread exit!");
  fflush(stdout); 
  pthread_exit(NULL);
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

int deal_message(int index, unsigned char* buf, int ret)
{
	int i, a, b;
	peer_info* l_peer;
	char* ptr;
	int len;
	int availble_recv_len;
	int parse_len;
	int one_command = 0;
	unsigned char one_cmd[64]={};
	l_peer = &peer[index];
	ptr = l_peer->recv_buf;

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

error:
	return ret;
}


int insert_node(unsigned int ip, unsigned short port)
{
	int i;

	for(i=0; i<MAXCONNECTD;i++)
	{
		if(peer[i].sock_fd_used == 1)
		{
			if(peer[i].ip == ip)
			{
				return i;
			}
		}
	}

	for(i=0; i<MAXCONNECTD; i++)
	{
		if(peer[i].sock_fd_used == 0)
		{
			peer[i].ip = ip;
			peer[i].port = port;
			return i;
		}
	}
}


int main(int argc, char **argv)
{
	int i, ret, index;
	socklen_t len;
	struct sockaddr_in my_addr;
	unsigned int myport=8081;
	unsigned char buf[1024]={};
	struct sockaddr_in client_addr;
  	socklen_t cli_len=sizeof(client_addr);

	pthread_t thread;
	pthread_attr_t attr;


	if ((listener = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket create failed ！");
		exit(1);
	}
	else
	{
		printf("socket create  success /n");
	}


	/*设置socket属性，端口可以重用*/
	int opt=SO_REUSEADDR;
	setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));


	setnonblocking(listener);
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = PF_INET;
	my_addr.sin_port = htons(myport);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(listener, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("bind");
		exit(1);
	} 
	else
	{
		printf("IP and port bind success \n");
	}

	while (1) 
	{
		ret = recvfrom(listener, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &cli_len);
		if(ret > 0)
		{
			debug_msg("recv %d bytes from: %s,port:%d\n", ret, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			for(i=0; i<ret; i++)
				debug_msg("buf[%d]: %c ", i, buf[i]);
			debug_msg("\n");
			index = insert_node(dot_ip_to_u32(inet_ntoa(client_addr.sin_addr)), ntohs(client_addr.sin_port));
			deal_message(index, buf, ret);
			
		}
	}
	
	return 0;
	}

