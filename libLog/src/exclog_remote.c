/**********************************************************************************
 * 					Filename: exclog_remote.c
 ***********************************************************************************
 * Description:
 * 		 this is an implement file of EXCLOG_2_REMOTE.
 * Copyright:
 * Author: 
 ***********************************************************************************/
#include "exclog.h"
#include "exclog_public.h"
#include "exclog_sysklogd.h"

char SERVER_IP[EXCLOG_IPADDRESS_LEN] = { '\0' };/*IP address of log receiver*/
static char host_ip[EXCLOG_IPADDRESS_LEN] = { '\0' };/*host IP address*/

static int isInit = 0;
static int isInitSelf = 0;

static int sockfd = -1;/*socket for send log in EXCLOG_2_REMOTE model*/
static struct sockaddr_in exclog_server;

static int exclog_thread_switch = 0;
static int exclog_thread_num = 0;

/*queue to store log*/
static exclog_packet_t pkt_queue[EXCLOG_QUEUE_SIZE];
static int head = 0;
static int tail = 0;

static int __exclog_remote_init_socket(char *remoteIP, int remotePort);
static void __exclog_remote_send(exclog_packet_t *pkt);
static void __exclog_remote_send_pkt(exclog_packet_t *pkt);
static void __exclog_remote_init_self();

static void __exclog_remote_poll_thread(void);
static void __exclog_remote_poll_queue(void);
static void __exclog_remote_poll_syslogd(void);
static void __exclog_remote_poll_klogd(void);

/********************************************************************************************
 * Function: __exclog_remote_init_self()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: initialize remote send socket,syslogd and klogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ ixp:IN,initialize structure.
 ********************************************************************************************/
static void __exclog_remote_init_self()
{
	init_exclog_remote_t init;
	memset(&init, 0, sizeof(init));
	init.remotePort = 514;
	init.be_syslog = 0;
	init.be_klog = 0;
	strncpy(init.remoteIP, "127.0.0.1",sizeof(init.remoteIP)-1);
	strncpy(SERVER_IP, "127.0.0.1",sizeof(SERVER_IP)-1);

	isInitSelf = 1;

	int ret = init_exclog_network(&init);
	if (ret == -1)
	{
		DEBUG_SELF("Invalid init_exclog_remote_t fail.");
		return;
	}
	return;
}

/********************************************************************************************
 * Function: _exclog_remote_init()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: initialize remote send socket,syslogd and klogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ ixp:IN,initialize structure.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_remote_init(const init_exclog_remote_t *ix_p)
{
	if (ix_p == NULL)
	{
		DEBUG_SELF("Invalid init_exclog_remote_t.");
		return -1;
	}

	if (ix_p->remoteIP == NULL)
	{
		log_level = 0;
		DEBUG_SELF("Invalid remoteIP.");
		return -1;
	}
	strncpy(SERVER_IP, ix_p->remoteIP,EXCLOG_IPADDRESS_LEN);

	if ((__exclog_remote_init_socket((char *)ix_p->remoteIP, ix_p->remotePort) != 0)\
			|| (_exclog_syslogd_init(ix_p->be_syslog) != 0)\
			|| (_exclog_klogd_init(ix_p->be_klog) != 0))
	{
		DEBUG_SELF("_exclog_remote_init fail.");
		return -1;
	}

	if (0 == isInitSelf)
	{
		log_level = ix_p->log_level;
	}

	if (log_level < 0 || log_level > 7)
	{
		log_level = EXCLOG_LEVEL_DEFAULT;
	}

	if (_exclog_public_get_ipaddr(host_ip) != 0)
	{
		DEBUG_SELF("get local ip fail.");
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: _exclog_remote_startup()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: startup remote process main thread.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:NULL.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_remote_startup(void)
{
	exclog_thread_switch = 1;

	pthread_t pid;
	if (pthread_create(&pid, NULL, (void *) &__exclog_remote_poll_thread, NULL) < 0)
	{
		DEBUG_SELF("pthread_create fail,%s.", strerror(errno));
		return -1;
	}

	isInit = 1;

	return 0;
}
/********************************************************************************************
 * Function: _exclog_remote_deinit()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: free all source,stop thread.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:NULL.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
void _exclog_remote_deinit(void)
{
	if (1 == syslogd_switch)
		_exclog_syslogd_deinit();
	if (1 == klogd_switch)
		_exclog_klogd_deinit();

	//store all log in queue before exit
	while (0x20110415)
	{
		if (1 == pkt_queue[head].status)
		{
			DBG_SELF("waiting to store logs in buffer.");
			usleep(10000);
		}
		else
		{
			break;
		}
	}

	exclog_thread_switch = 0;

	if (sockfd != -1)
	{
		close(sockfd);
	}

	while (0x20100827)
	{
		if (0 == exclog_thread_num)
		{
			break;
		}
	}

	return;
}
/********************************************************************************************
 * Function: _exclog_remote_put_queue()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: put remote log to ring buffer.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ sbuf:IN,remote log.
 *  @ slen:IN,remote log length.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_remote_put_queue(char *sbuf, int slen)
{
	if (isInit == 0)
	{
		__exclog_remote_init_self();
	}

	if (0 == pkt_queue[tail].status)
	{
		pkt_queue[tail].status = 1;
		pkt_queue[tail].len = (slen > (sizeof(pkt_queue[tail]) - 1)) ? sizeof(pkt_queue[tail]) - 1 : slen;
		strncpy(pkt_queue[tail].message, sbuf, pkt_queue[tail].len);
		gettimeofday(&pkt_queue[tail].tv, NULL);

		if (0 == isInitSelf)
		{
			_exclog_add_ipaddr_2_pkt(&pkt_queue[tail], host_ip);
		}
		tail = ((tail + 1) >= EXCLOG_QUEUE_SIZE ? 0 : tail + 1);
	}
	else
	{
		DEBUG_SELF("remote queue is full(%d).",EXCLOG_QUEUE_SIZE);
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_remote_init_socket()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:initialize socket for send log to remote.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters: 
 *  @ remoteIP:IN, log receiver's IP address.
 *  @ remotePort:IN,log receiver's receive port.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success;
 * 		  -1:fail.
 ********************************************************************************************/
static int __exclog_remote_init_socket(char *remoteIP, int remotePort)
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		DEBUG_SELF("create socket fail,%s.", strerror(errno));
		return -1;
	}

	memset(&exclog_server, 0, sizeof(exclog_server));
	exclog_server.sin_family = AF_INET;
	exclog_server.sin_addr.s_addr = inet_addr(remoteIP);
	exclog_server.sin_port = htons(remotePort);

	return 0;
}
/********************************************************************************************
 * Function: __exclog_remote_send()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: send log to remote.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt: IN, packet to send.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static void __exclog_remote_send(exclog_packet_t *pkt)
{
	socklen_t socklen = sizeof(struct sockaddr);

	int ret = 0;
	ret = sendto(sockfd, (char *) pkt, sizeof(exclog_packet_t), 0, (struct sockaddr *) &exclog_server, socklen);
	if (ret < 0)
	{
		DEBUG_SELF("send fail,%s.", strerror(errno));
	}
	else
	{
		DBG_SELF("send success:%s", pkt->message);
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_remote_send_pkt()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: compare with last message and send.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt: IN, packet to send.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_remote_send_pkt(exclog_packet_t *pkt)
{
	static char last_message[EXCLOG_MSG_LEN_MAX] = { '\0' };
	static int repeat_num = 0;/*last message repeat num*/

	int ret = 0;
	int send_pkt = 0;
	int send_repeat = 0;

	ret = _exclog_check_last_message(pkt, last_message);
	if (-1 == ret)
	{
		++repeat_num;
		if (0 == repeat_num % EXCLOG_REPEAT_NUM_MAX)
		{
			send_repeat = 1;
		}
	}
	else
	{
		send_pkt = 1;

		if (strlen(last_message) != 0)
		{
			send_repeat = 1;
		}
	}

	if ((1 == send_repeat) && (repeat_num > 0))
	{
		char last_level[16] = { '\0' };
		char last_module[16] = { '\0' };
		_exclog_get_last_level_module(last_message, last_level, last_module);

		exclog_packet_t repeat_pkt;
		memset(&repeat_pkt, 0, sizeof(repeat_pkt));
		gettimeofday(&repeat_pkt.tv, NULL);
		repeat_pkt.len = snprintf(repeat_pkt.message,sizeof(repeat_pkt.message)-1, "<%s>%s(%s.%d):last message repeat %d times.\n", last_level,
				last_module, __FILE__, __LINE__, repeat_num);

		_exclog_add_ipaddr_2_pkt(&repeat_pkt, host_ip);
		__exclog_remote_send(&repeat_pkt);

		repeat_num = 0;
	}

	if (1 == send_pkt)
	{
		__exclog_remote_send(pkt);
		strncpy(last_message, pkt->message,sizeof(last_message)-1);
		last_message[sizeof(last_message)-1]='\0';
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_remote_poll_thread()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:remote main thread,poll lib/app log,syslog and klog.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_remote_poll_thread(void)
{
#if (!defined(WIN32) && !defined(_WIN32_WCE))
	pthread_detach(pthread_self());
#endif

	DEBUG_SELF("remote mode,main thread startup.");

	exclog_thread_num++;

	while (exclog_thread_switch)
	{
		__exclog_remote_poll_queue();

		if (1 == syslogd_switch)
		{
			__exclog_remote_poll_syslogd();
		}

		if (1 == klogd_switch)
		{
			__exclog_remote_poll_klogd();
		}

		usleep(1000);
	}

	exclog_thread_num--;

	return;
}
/********************************************************************************************
 * Function: __exclog_remote_poll_queue()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:pop log from ring buffer and store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_remote_poll_queue(void)
{
	int i = 0;
	for (i = 0; i <= EXCLOG_POOL_SIZE; i++)
	{
		if (1 == pkt_queue[head].status)
		{
			__exclog_remote_send_pkt(&pkt_queue[head]);

			memset(&pkt_queue[head], 0, sizeof(exclog_packet_t));
			head = ((head + 1) >= EXCLOG_QUEUE_SIZE ? 0 : head + 1);
		}
		else
		{
			break;
		}
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_remote_poll_syslogd()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:read syslog and send.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_remote_poll_syslogd(void)
{
	exclog_packet_t pkt;
	memset(&pkt, 0, sizeof(pkt));

	int ret = _exclog_syslogd_get(&pkt);
	if (-1 == ret)
	{
		DBG_SELF("get syslog,no message.");
	}
	else
	{
		_exclog_add_ipaddr_2_pkt(&pkt, host_ip);
		__exclog_remote_send_pkt(&pkt);
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_remote_poll_klogd()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:read klog and send.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_remote_poll_klogd(void)
{
	exclog_packet_t pkt;
	memset(&pkt, 0, sizeof(pkt));

	int ret = _exclog_klogd_get(&pkt);
	if (-1 == ret)
	{
		DBG_SELF("get kernel log,no message.");
	}
	else
	{
		_exclog_add_ipaddr_2_pkt(&pkt, host_ip);
		__exclog_remote_send_pkt(&pkt);
	}

	return;
}

