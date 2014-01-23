/**********************************************************************************
 * 					Filename: exclog_local.c
 ***********************************************************************************
 * Description:
 * 		this is an implement file of EXCLOG_2_LOCAL. 
 * Copyright:
 * Author: 
 ***********************************************************************************/
#include "exclog.h"
#include "exclog_public.h"
#include "exclog_local.h"
#include "exclog_sysklogd.h"
#include "exclog_store.h"
#include "exclog_query.h"

/*test variable*/
static int store_total_local = 0;
static int store_total_remote = 0;

static exclog_packet_t pkt_queue[EXCLOG_QUEUE_SIZE];/*buffer to store local log*/
static int head = 0;/*head of pkt_queue*/
static int tail = 0;/*tail of pkt_queue*/

static int remote_switch = 0; /*enable or disable receive remote log*/
static int remote_sockfd = -1;/*socket for receive remote log*/

static int exclog_thread_switch = 0;
static int exclog_thread_num = 0;

static int __exclog_local_init_region_list(const char *path, int num, int size);
static int __exclog_local_init_remote(int local_port);

static void __exclog_local_poll_thread(void);
static void __exclog_local_poll_queue(void);
static void __exclog_local_poll_remote(void);
static void __exclog_local_poll_syslogd(void);
static void __exclog_local_poll_klogd(void);

static void __exclog_local_store_pkt(exclog_packet_t *pkt);

#ifdef EXCLOG_QUERY_SWITCH
static int query_sockfd = -1; /*socket for receive query request*/

static void __exclog_local_query_thread(void);
static int __exclog_local_query_init(void);
static int __exclog_local_query_req_recv(char *remoteIP, exclog_query_req_t *req);
static int __exclog_local_query_req_process(char *remoteIP, exclog_query_req_t *req);
#endif

/********************************************************************************************
 * Function: _exclog_local_init()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: initialize local region list,remote log,syslogd and klogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ ixp:IN,initialize structure.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_local_init(const init_exclog_local_t *ix_p)
{
	if (ix_p == NULL)
	{
		DEBUG_SELF("Invalid init_exclog_local_t.");
		return -1;
	}

	log_level = ix_p->log_level;
	if (log_level < 0 || log_level > 7)
	{
		log_level = EXCLOG_LEVEL_DEFAULT;
	}

	if ((__exclog_local_init_region_list(ix_p->path, ix_p->num, ix_p->size) != 0)\
			|| (__exclog_local_init_remote(ix_p->local_port) != 0)\
			|| (_exclog_syslogd_init(ix_p->be_syslog) != 0)\
			|| (_exclog_klogd_init(ix_p->be_klog) != 0))
	{
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: _exclog_local_startup()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: startup local process main thread.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:NULL.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_local_startup(void)
{
	exclog_thread_switch = 1;

	pthread_t pid;
	if (pthread_create(&pid, NULL, (void *) &__exclog_local_poll_thread, NULL) < 0)
	{
		DEBUG_SELF("pthread_create fail,%s.", strerror(errno));
		return -1;
	}

	if (1 == remote_switch)
	{
#ifdef EXCLOG_QUERY_SWITCH
		pthread_t pid2;
		if (pthread_create(&pid2, NULL, (void *)&__exclog_local_query_thread, NULL)<0)
		{
			DEBUG_SELF("pthread_create __exclog_local_query_thread fail,%s.",strerror(errno));
			return -1;
		}
#endif
	}
	return 0;
}
/********************************************************************************************
 * Function: _exclog_local_deinit()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: free all source,stop syslogd,klogd and poll thread.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:NULL.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
void _exclog_local_deinit(void)
{
	//stop receive syslog and klog
	if (1 == syslogd_switch)
	{
		_exclog_syslogd_deinit();
	}
	if (1 == klogd_switch)
	{
		_exclog_klogd_deinit();
	}

	//store all logs in queue before exit
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
	remote_switch = 0;

	if(remote_sockfd!=-1)
	{
		close(remote_sockfd);
	}

	while (0x20100827)
	{
		if (0 == exclog_thread_num)
		{
			break;
		}
	}

	DEBUG_SELF("store_total_local=%d,store_total_remote=%d.",store_total_local,store_total_remote);
	return;
}
/********************************************************************************************
 * Function: _exclog_local_put_queue()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: put local log to ring buffer.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ sbuf:IN,local log.
 *  @ slen:IN,local log length.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_local_put_queue(char *sbuf, int slen)
{
	if (0 == pkt_queue[tail].status)
	{
		pkt_queue[tail].status = 1;
		pkt_queue[tail].len = (slen > (sizeof(pkt_queue[tail]) - 1)) ? sizeof(pkt_queue[tail]) - 1 : slen;
		strncpy(pkt_queue[tail].message, sbuf, pkt_queue[tail].len);
		gettimeofday(&pkt_queue[tail].tv, NULL);

		tail = ((tail + 1) >= EXCLOG_QUEUE_SIZE ? 0 : tail + 1);
	}
	else
	{
		DEBUG_SELF("local queue is full(%d).",EXCLOG_QUEUE_SIZE);
	}
	return 0;
}
/********************************************************************************************
 * Function: __exclog_local_poll_thread()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:local main thread,poll and store local log,remote log,syslog and klog.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_local_poll_thread(void)
{
#if (!defined(WIN32) && !defined(_WIN32_WCE))
	pthread_detach(pthread_self());
#endif

	DEBUG_SELF("local mode,main thread startup.");

	exclog_thread_num++;

	while (exclog_thread_switch)
	{
		__exclog_local_poll_queue();

		if (1 == remote_switch)
		{
			__exclog_local_poll_remote();
		}

		if (1 == syslogd_switch)
		{
			__exclog_local_poll_syslogd();
		}

		if (1 == klogd_switch)
		{
			__exclog_local_poll_klogd();
		}
		usleep(3000);
	}

	exclog_thread_num--;

	return;
}
/********************************************************************************************
 * Function: __exclog_local_init_region_list()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:initialize local region list.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ path:IN,log file path or device name.
 *  @ num :IN,log file num.
 *  @ size:IN,log file size.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_local_init_region_list(const char *path, int num, int size)
{
#ifdef EXCLOG_2_FILE
	/*step 1: check parameters*/
	if (path == NULL)
	{
		strncpy(EXCLOG_PATH, EXCLOG_STDOUT_MAGIK_STR, sizeof(EXCLOG_PATH) - 1);
		EXCLOG_PATH[sizeof(EXCLOG_PATH) - 1] = '\0';
		return 0;
	}
	else
	{
		strncpy(EXCLOG_PATH, path, sizeof(EXCLOG_PATH) - 1);
		EXCLOG_PATH[sizeof(EXCLOG_PATH) - 1] = '\0';
	}

	if (num < EXCLOG_FILE_NUM_MIN || num > EXCLOG_FILE_NUM_MAX)
	{
		DEBUG_SELF("Invalid log file num,must be [%d,%d],set to default(%d).",EXCLOG_FILE_NUM_MIN,EXCLOG_FILE_NUM_MAX,EXCLOG_FILE_NUM_DEFAULT);
		num=EXCLOG_FILE_NUM_DEFAULT;
	}

	if (size < EXCLOG_FILE_SIZE_MIN || size > EXCLOG_FILE_SIZE_MAX)
	{
		DEBUG_SELF("Invalid log file size,must be [%d,%d] (Byte),set to default(%d).",EXCLOG_FILE_SIZE_MIN,EXCLOG_FILE_SIZE_MAX,EXCLOG_FILE_SIZE_DEFAULT);
		size=EXCLOG_FILE_SIZE_DEFAULT;
	}

	/*step 2: get latest region index to write(region_cur)*/
	int i = 0;
	int ret = 0;
	int fid = 0;
	FILE *fd = NULL;
	FILE *stream = NULL;
	struct stat status;
	char fname[EXCLOG_FILE_NAME_LEN] = { '\0' };

	char cmd[256] = { '\0' };
	char *check_file = "/tmp/libexcLOG_check";
	snprintf(cmd, sizeof(cmd) - 1, "ls %s -t > %s", path, check_file);

	stream = popen(cmd, "r");
	if (stream)
	{
		pclose(stream);

		fd = fopen(check_file, "r");
		if (fd)
		{
			char *ret2 = NULL;
			ret2 = fgets(fname, EXCLOG_FILE_NAME_LEN, fd);
			if (ret2)
			{
				char *split = "\n";
				char *pos = strtok(fname, split);
				if (pos)
				{
					fid = atoi(pos + strlen(EXCLOG_FILE_PREFIX));
				}
			}
			else
			{
				DBG_SELF("log messages are not exist.");
			}
			fclose(fd);

			snprintf(cmd, sizeof(cmd) - 1, "rm -rf %s", check_file);
			stream = popen(cmd, "r");
			if (stream)
			{
				pclose(stream);
			}
			else
			{
				DEBUG_SELF("%s fail,%s.",cmd,strerror(errno));
				return -1;
			}
		}
		else
		{
			DEBUG_SELF("fopen %s fail,%s.",check_file,strerror(errno));
			return -1;
		}
	}
	else
	{
		DEBUG_SELF("%s fail,%s.",cmd,strerror(errno));
		return -1;
	}

	region_cur = fid;
	region_num = num;
	DBG_SELF("region_num=%d,region_cur=%d.", region_num, region_cur);

	/*initialize region_list[]*/
	for (i = 0; i < num; i++)
	{
		memset(&region_list[i], 0, sizeof(exclog_flash_info_t));
		snprintf(fname, sizeof(fname) - 1, "%s/%s%d", EXCLOG_PATH, EXCLOG_FILE_PREFIX, i);

		fd = fopen(fname, "r");
		if (fd == NULL)
		{
			if (errno == 2)
			{
				fd = fopen(fname, "w");
				if (fd == NULL)
				{
					DEBUG_SELF("fopen %s fail,%s.",fname,strerror(errno));
					return -1;
				}
				else
				{
					fclose(fd);
					region_list[i].size = size;
					region_list[i].left = size;

					DBG_SELF("create and initialize %s.",fname);
				}
			}
			else
			{
				DEBUG_SELF("fopen %s fail,%s.",fname,strerror(errno));
				return -1;
			}
		}
		else
		{
			fclose(fd);

			memset(&status, 0, sizeof(status));
			ret = stat(fname, &status);
			if (-1 == ret)
			{
				DEBUG_SELF("stat %s fail,%s",fname,strerror(errno));
				return -1;
			}

			region_list[i].size = size;
			if (size <= status.st_size)
			{
				region_list[i].left = 0;
				region_list[i].status = 1;
			}
			else
			{
				region_list[i].left = size - status.st_size;
			}
		}//end else

		DBG_SELF("region %d:size=%d,left=%d,status=%d.",
				i,region_list[i].size,region_list[i].left,region_list[i].status);
	}//end for
#endif
#ifdef EXCLOG_2_FLASH
	if((path==NULL) || (access(path,F_OK && R_OK && W_OK)!=0))
	{
		DEBUG_SELF("Invalid device name.");
		return -1;
	}

	int fd=open(path, O_RDONLY);
	if (-1==fd)
	{
		DEBUG_SELF("open %s fail,%s.", path, strerror(errno));
		return -1;
	}

	struct mtd_info_user mtd;
	memset(&mtd,0,sizeof(mtd));
	if(ioctl(fd,MEMGETINFO,&mtd)!=0)
	{
		DEBUG_SELF("get memory info fail,%s.",strerror(errno));
		close(fd);
		return -1;
	}
	DBG_SELF("flash INFO:name=%s,total_size=%d,erasesize=%d,type=%d.",path,mtd.size,mtd.erasesize,mtd.type);

	int region_count=mtd.size/mtd.erasesize;

	int i;
	for (i=0; i<region_count; i++)
	{
		region_list[i].offset=i*mtd.erasesize;
		region_list[i].size=mtd.erasesize;
		region_list[i].left=mtd.erasesize;
		region_list[i].pos=0;
		region_list[i].status=0;
		DBG_SELF("region[%d]:offset=%d,size=%d.",i, region_list[i].offset, region_list[i].size);
	}
	region_cur=0;
	region_num=num;
	strncpy(EXCLOG_PATH,path,sizeof(EXCLOG_PATH)-1);
	EXCLOG_PATH[sizeof(EXCLOG_PATH)-1]='\0';

	close(fd);
#endif

	return 0;
}
/********************************************************************************************
 * Function: __exclog_local_init_remote()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:initialize for receive remote log.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ local_port:IN,receive on which port.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success;
 * 		  -1:fail.
 ********************************************************************************************/
static int __exclog_local_init_remote(int local_port)
{
	if (0 == local_port)
	{
		DEBUG_SELF("libexcLOG-remote-receive closed.");
	}
	else
	{
		remote_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (-1 == remote_sockfd)
		{
			DEBUG_SELF("create socket for remote fail,%s.", strerror(errno));
			return -1;
		}

		struct sockaddr_in local;
		memset(&local, 0, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		local.sin_port = htons(local_port);

		socklen_t socklen = sizeof(struct sockaddr_in);

		if ((bind(remote_sockfd, (struct sockaddr *) &local, socklen)) == -1)
		{
			DEBUG_SELF("bind socket fail,%s.", strerror(errno));
			close(remote_sockfd);
			return -1;
		}

		remote_switch = 1;

		DEBUG_SELF("libexcLOG-remote-receive startup.");
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_local_poll_queue()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:pop log from local ring buffer and store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_local_poll_queue(void)
{
	int i = 0;
	for (i = 0; i <= EXCLOG_POOL_SIZE; i++)
	{
		if (1 == pkt_queue[head].status)
		{
			__exclog_local_store_pkt(&pkt_queue[head]);

			memset(&pkt_queue[head], 0, sizeof(exclog_packet_t));
			head = ((head + 1) >= EXCLOG_QUEUE_SIZE ? 0 : head + 1);

			store_total_local++;
		}
		else
		{
			break;
		}
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_local_poll_remote()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:receive remote log and store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_local_poll_remote(void)
{
	int ret = 0;

	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));

	fd_set readfd;
	FD_ZERO(&readfd);
	FD_SET(remote_sockfd, &readfd);
	struct timeval tv = { 0, 0 };

	ret = select(remote_sockfd + 1, &readfd, NULL, NULL, &tv);
	if (ret < 0)
	{
		if (errno != EINTR)
		{
			DEBUG_SELF("select fail,%s.", strerror(errno));
		}
	}
	else if (ret > 0)
	{
		socklen_t socklen = sizeof(struct sockaddr_in);

		exclog_packet_t pkt;
		memset(&pkt,0,sizeof(pkt));

		ret = recvfrom(remote_sockfd, (char *)&pkt, sizeof(exclog_packet_t), 0, (struct sockaddr *) &client, &socklen);
		if (ret < 0)
		{
			DEBUG_SELF("recvfrom fail,%s.", strerror(errno));
		}
		else if (ret > 0)
		{
			_exclog_store(&pkt);
			store_total_remote++;
		}
		else
		{
			/*receive nothing*/
		}
	}//end select>0	
	else
	{
		/*select time out*/
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_local_poll_syslogd()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:read syslog and store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_local_poll_syslogd(void)
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
		__exclog_local_store_pkt(&pkt);
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_local_poll_klogd()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:read klog and store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
static void __exclog_local_poll_klogd(void)
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
		__exclog_local_store_pkt(&pkt);
	}

	return;
}
/********************************************************************************************
 * Function: __exclog_local_store_pkt()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: compare with last message and store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt: IN, packet to store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_local_store_pkt(exclog_packet_t *pkt)
{
	static char last_message[EXCLOG_MSG_LEN_MAX] = { '\0' };
	static int  repeat_num = 0;/*last message repeat num*/

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
		gettimeofday(&repeat_pkt.tv, NULL);
		repeat_pkt.len = snprintf(repeat_pkt.message, sizeof(repeat_pkt.message) - 1,
				"<%s>%s(%s.%d):last message repeat %d times.\n", last_level, last_module, __FILE__,
				__LINE__, repeat_num);

		_exclog_store(&repeat_pkt);
		repeat_num = 0;
	}

	if (1 == send_pkt)
	{
		_exclog_store(pkt);
		strncpy(last_message, pkt->message, sizeof(last_message) - 1);
		last_message[sizeof(last_message) - 1] = '\0';
	}

	return;
}

#ifdef EXCLOG_QUERY_SWITCH
/********************************************************************************************
 * Function: __exclog_local_query_thread()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:query thread,receive remote query request,query and send result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_local_query_thread(void)
{
#if (!defined(WIN32) && !defined(_WIN32_WCE))
	pthread_detach(pthread_self());
#endif
	exclog_thread_num++;

	DBG_SELF("remote query thread startup.");

	int ret = 0;
	ret = __exclog_local_query_init();
	if (ret != 0)
	{
		DEBUG_SELF("__exclog_local_query_init fail.");
		exclog_thread_num--;
		return;
	}

	exclog_query_req_t req;
	memset(&req,0,sizeof(exclog_query_req_t));

	char remoteIP[32] = { '\0' };

	while (exclog_thread_switch)
	{
		ret = __exclog_local_query_req_recv(remoteIP, &req);
		switch (ret)
		{
		case -1:
			DEBUG_SELF("__exclog_local_query_req_recv fail.");
			break;
		case 0:
			break;
		case 1:
			ret = __exclog_local_query_req_process(remoteIP, req);
			if (ret != 0)
			{
				DEBUG_SELF("__exclog_local_query_process fail.");
				break;
			}
		default:
			break;
		}//end switch
	}//end while

	if (query_sockfd != -1)
	{
		close(query_sockfd);
	}

	exclog_thread_num--;

	return;
}
/********************************************************************************************
 * Function: __exclog_local_query_init()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: initialize socket for receive remote query request.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:NULL.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 *			0:success.
 * 	   	  -1:fail.
 ********************************************************************************************/
static int __exclog_local_query_init(void)
{
	query_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == query_sockfd)
	{
		DEBUG_SELF("create socket fail,%s.", strerror(errno));
		return -1;
	}

	struct sockaddr_in local;
	memset(&local, 0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(EXCLOG_QUERY_REQ_PORT);

	socklen_t socklen = sizeof(struct sockaddr_in);

	if (bind(query_sockfd, (struct sockaddr *) &local, socklen) == -1)
	{
		DEBUG_SELF("bind socket fail,%s.", strerror(errno));
		close(query_sockfd);
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_local_query_req_recv()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: receive remote query request.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 *  @ remoteIP:OUT,IP address of query request.
 *  @ req:OUT,query request.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 			1:success,receive request.
 *			0:timeout.
 * 	   	  -1:fail.
 ********************************************************************************************/
static int __exclog_local_query_req_recv(char *remoteIP, exclog_query_req_t *req)
{
	remoteIP = NULL;

	struct sockaddr_in remote;
	memset(&remote, 0, sizeof(remote));

	socklen_t socklen = sizeof(struct sockaddr_in);

	fd_set readfd;
	FD_ZERO(&readfd);
	FD_SET(query_sockfd, &readfd);

	struct timeval tv = { EXCLOG_QUERY_TIME_OUT, 0 };

	int ret = select(query_sockfd, &readfd, NULL, NULL, &tv);
	if (-1 == ret && errno == EINTR)
	{
		DEBUG_SELF("select fail,%s.", strerror(errno));
		return -1;
	}
	else if (ret > 0)
	{
		ret = recvfrom(query_sockfd, (char *) req, sizeof(exclog_query_req_t), 0,
				(struct sockaddr *) &remote, &socklen);
		if (-1 == ret)
		{
			DEBUG_SELF("select fail,%s.", strerror(errno));
			return -1;
		}
		else if (ret > 0)
		{
			strncpy(remoteIP, inet_ntoa(remote.sin_addr), sizeof(remoteIP) - 1);
			remoteIP[sizeof(remoteIP) - 1] = '\0';
			return 1;
		}
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_local_query_req_process()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: query log for remote.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 *	@req:IN,query request.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 *			0:success.
 * 	   	  -1:fail.
 ********************************************************************************************/
static int __exclog_local_query_req_process(char *remoteIP, exclog_query_req_t *req)
{
	exclog_query_remote_rps_t remote_rps;
	exclog_query_rps_t rps, *rps_ptr = NULL, *tmp = NULL;
	memset(&rps, 0, sizeof(rps));
	rps_ptr = &rps;

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		DEBUG_SELF("create socket fail,%s.", strerror(errno));
		return -1;
	}
	struct sockaddr_in remote;
	memset(&remote, 0, sizeof(remote));
	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = inet_addr(remoteIP);
	remote.sin_port = htons(EXCLOG_QUERY_RPS_PORT);

	socklen_t socklen = sizeof(struct sockaddr_in);

	int query_result = 0;
	int ret = _exclog_query_startup(remoteIP, &rps_ptr);
	if (0 == ret && rps_ptr)
	{
		query_result = 1;

		int stop_send = 0;
		tmp = rps_ptr;
		while (tmp)
		{
			if (0 == stop_send)
			{
				memset(&remote_rps, 0, sizeof(remote_rps));
				remote_rps.tick = tmp->tick;
				remote_rps.level = tmp->level;
				remote_rps.module = tmp->module;
				strncpy(remote_rps.data, tmp->data, sizeof(remote_rps.data) - 1);

				ret = sendto(sockfd, (char *) &remote_rps, sizeof(exclog_query_remote_rps_t), 0,
						(struct sockaddr *) &remote, socklen);
				if (-1 == ret)
				{
					DEBUG_SELF("sendto query result fail,%s.", strerror(errno));
					stop_send = 1;
				}
			}
			rps_ptr = rps_ptr->next;
			free(tmp);
			tmp = rps_ptr;
		}
	}

	//send finish signal
	memset(&remote_rps, 0, sizeof(remote_rps));
	if (0 == query_result)
	{
		strncpy(remote_rps.data, "fail", sizeof(remote_rps.data) - 1);
	}
	else if (1 == query_result)
	{
		strncpy(remote_rps.data, "finish", sizeof(remote_rps.data) - 1);
	}
	remote_rps.data[sizeof(remote_rps.data) - 1] = '\0';

	ret = sendto(sockfd, (char *) &remote_rps, sizeof(exclog_query_remote_rps_t), 0,
			(struct sockaddr *) &remote, socklen);
	if (-1 == ret)
	{
		DEBUG_SELF("sendto fail,%s.", strerror(errno));
	}

	close(sockfd);

	return 0;
}
#endif
