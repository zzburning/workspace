/***********************************************************************************
 * 					Filename: exclog_sysklogd.c
 ***********************************************************************************
 * Description:
 * 		implement syslogd and klogd.
 * Copyright:
 * 		 HISOME <http://www.hisome.com>
 * Author: 
 * 		 renhw <renhw@hisome.com>
 ***********************************************************************************/
#include "exclog_sysklogd.h"

#define EXCLOG_SYSLOG_FILE		"/dev/log"	/*socket file for syslog*/
#define EXCLOG_SYSLOG_PRI_SYN_LEN	(2)/*<>*/
#define EXCLOG_SYSLOG_PRI_LEN_MIN	(3)/*<facility*8+level>*/
#define EXCLOG_SYSLOG_PRI_LEN_MAX	(5)/*<facility*8+level>*/
#define EXCLOG_SYSLOG_HEAD_LEN		(16)/*May 26 14:00:00 */
#define EXCLOG_SYSLOG_TAG_LEN_MAX	(64)/*file name[line]*/
#define EXCLOG_SYSLOG_LEN_MIN		(EXCLOG_SYSLOG_PRI_LEN_MIN+EXCLOG_SYSLOG_HEAD_LEN)

#define EXCLOG_KLOG_PKT_NUM		(10)/*max klog packet num in buffer*/
#define EXCLOG_KLOG_LEN_MIN		(4)

int syslogd_switch = 0;/*receive syslog or not*/
int klogd_switch = 0;/*receive klog or not*/

static int syslog_sockfd = -1;

/**
 *klog_buf:used to save incomplete(which have no '\n') content for next store.
 *klog_buf_used: account current used num of klog_buf for next read
 **/
static char klog_buf[EXCLOG_LOG_LEN_MAX] = { '\0' };
static int 	klog_buf_used = 0;

static exclog_packet_t klog_pkt[EXCLOG_KLOG_PKT_NUM];
static int klog_head = 0;
static int klog_tail = 0;
static int klog_num = 0;

static int __exclog_klog_read(void);
static int __exclog_klog_put_queue(const char *klog, int len);
static int __exclog_klog_get_queue(exclog_packet_t *pkt);

static int __exclog_syslog_time_2_timeval(const char *datetime, struct timeval *tv);
static int __exclog_syslog_process(const char *syslog, int len, exclog_packet_t *pkt);
/********************************************************************************************
 * Function: _exclog_syslogd_init()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: initialize syslogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ be_syslog:IN,enable or disable syslogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_syslogd_init(int be_syslog)
{
	if (1 == be_syslog)
	{
		syslog_sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
		if (-1 == syslog_sockfd)
		{
			DEBUG_SELF("create socket for syslogd fail,%s.", strerror(errno));
			return -1;
		}

		unlink(EXCLOG_SYSLOG_FILE);

		struct sockaddr_un addr;
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, EXCLOG_SYSLOG_FILE, sizeof(addr.sun_path) - 1);

		socklen_t len = sizeof(struct sockaddr);

		if (bind(syslog_sockfd, (struct sockaddr *) &addr, len) < 0)
		{
			DEBUG_SELF("bind %s for syslogd fail,%s.", EXCLOG_SYSLOG_FILE, strerror(errno));
			close(syslog_sockfd);
			unlink(EXCLOG_SYSLOG_FILE);
			return -1;
		}

		syslogd_switch = 1;

		DEBUG_SELF("libexcLOG-syslogd startup.");
	}
	else
	{
		DEBUG_SELF("libexcLOG-syslogd closed.");
	}

	return 0;
}
/********************************************************************************************
 * Function: _exclog_syslogd_get()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: get syslog and format it to exclog_packet_t.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt:IN&OUT,result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success,receive syslog.
 * 		-1:system call fail or receive nothing.
 ********************************************************************************************/
int _exclog_syslogd_get(exclog_packet_t *pkt)
{
	fd_set readfd;
	FD_ZERO(&readfd);
	FD_SET(syslog_sockfd, &readfd);

	struct timeval tv = { 0, 0 };
	socklen_t socklen = sizeof(struct sockaddr_in);

	char recvbuf[EXCLOG_LOG_LEN_MAX] = { '\0' };

	int ret = select(syslog_sockfd + 1, &readfd, NULL, NULL, &tv);
	switch (ret)
	{
	case -1:
		DEBUG_SELF("select fail,%s.", strerror(errno));
		return -1;
	case 0:
		/*select time out*/
		return -1;
	default:
		ret = recvfrom(syslog_sockfd, recvbuf, sizeof(recvbuf) - 1, 0, NULL, &socklen);
		if (ret < 0)
		{
			DEBUG_SELF("recvfrom syslog fail,%s.", strerror(errno));
			return -1;
		}
		else if (ret > 0)
		{
			ret=__exclog_syslog_process(recvbuf, ret, pkt);
		}
		else
		{
			/*receive nothing*/
			return -1;
		}
		break;
	}

	return ret;
}
/********************************************************************************************
 * Function: _exclog_syslogd_deinit()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: stop syslogd,close socket and unlink file name.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:NULL.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
void _exclog_syslogd_deinit()
{
	syslogd_switch = 0;

	if (syslog_sockfd != -1)
	{
		close(syslog_sockfd);
	}
	unlink(EXCLOG_SYSLOG_FILE);

	DEBUG_SELF("libexcLOG-syslogd closed.");
	return;
}
/********************************************************************************************
 * Function: _exclog_klogd_init()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: initialize klogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ be_klog:IN,enable or disable klogd.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_klogd_init(int be_klog)
{
	if (1 == be_klog)
	{
		DEBUG_SELF("libexcLOG-klogd startup.");
		klogd_switch = 1;
	}
	else
	{
		DEBUG_SELF("libexcLOG-klogd closed.");
	}
	return 0;
}
/********************************************************************************************
 * Function: _exclog_klogd_get()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: get klog and format it to exclog_packet_t.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt:IN&OUT,result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success,get kernel log.
 * 		-1:fail or get nothing.
 ********************************************************************************************/
int _exclog_klogd_get(exclog_packet_t *pkt)
{
	int ret = 0;

	ret = __exclog_klog_get_queue(pkt);
	if (0 == ret)
	{
		DBG_SELF("get kernel log success.");
	}
	else
	{
		ret = __exclog_klog_read();
		if (-1 == ret)
		{
			DBG_SELF("get kernel log,nothing read from ring buffer.");
		}
		else
		{
			ret = __exclog_klog_get_queue(pkt);
		}
	}

	return ret;
}
/********************************************************************************************
 * Function: _exclog_klogd_deinit()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: stop klogd.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:NULL.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
void _exclog_klogd_deinit()
{
	klogd_switch = 0;

	DBG_SELF("libexcLOG-klogd closed.");

	return;
}
/********************************************************************************************
 * Function: __exclog_klog_read()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: read log from kernel ring buffer,transfer to exclog_packet_t.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ pkt:OUT,result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_klog_read(void)
{
	if (-1 == klogctl(1, NULL, 0))
	{
		DEBUG_SELF("open kernel log fail,%s.", strerror(errno));
		return -1;
	}

	//if ring buffer has no data,return
	if (klogctl(9, NULL, 0) <= 0)
	{
		klogctl(0, NULL, 0);
		return -1;
	}

	int ret = 0;
	int stop = 0;
	int klog_buf_len = 0;

	char *start = klog_buf + klog_buf_used;

	//read ring buffer
	ret = klogctl(2, start, sizeof(klog_buf) - 1 - klog_buf_used);
	if (-1 == ret)
	{
		DEBUG_SELF("read kernel log fail,%s.", strerror(errno));
		klogctl(0, NULL, 0);
		return -1;
	}

	start[ret] = '\0';
	klog_buf_len = ret + klog_buf_used;

	//parse and store every line
	start = klog_buf;
	char *endpos = NULL;
	while (1)
	{
		endpos = strchrnul(start, '\n');
		if ((*endpos == '\0') || (1 == stop))
		{
			//incomplete line,move it to the front of klog_buf */
			if (start != klog_buf)
			{
				char *tmp1 = klog_buf;
				char *tmp2 = start;

				while ((*tmp1 = *tmp2) != '\0')
				{
					tmp1++;
					tmp2++;
				}
				klog_buf_used = endpos - start;
			}
			else
			{
				klog_buf_used = klog_buf_len;
			}
			break;
		}//end incomplete process
		else
		{
			//complete line,store it
			*endpos++ = '\0';

			ret = __exclog_klog_put_queue(start, endpos - start);
			if (-1 == ret)
			{
				stop = 1;
				DBG_SELF("put queue fail,stop read.");
			}
			else
			{
				start = endpos;
				DBG_SELF("put queue success,continue read.");
			}
		}
	}//end while(1)

	if ((klog_buf_len == sizeof(klog_buf)) && (0 == stop))
	{
		klog_buf_used = 0;
		memset(klog_buf, 0, sizeof(klog_buf));
	}

	if (-1 == klogctl(0, NULL, 0))
	{
		DEBUG_SELF("close kernel log fail,%s.", strerror(errno));
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_klog_put_queue()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: put kernel log to exclog_packet_t queue.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ klog:IN,kernel log.
 * @ len: klog length.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success,throw it away when length < EXCLOG_KLOG_LEN_MIN or can not find '<''>'.
 * 		-1:fail，klog_pkt buffer is full.
 ********************************************************************************************/
static int __exclog_klog_put_queue(const char *klog, int len)
{
	if (len <= EXCLOG_KLOG_LEN_MIN)
	{
		DBG_SELF("Invalid kernel log,length<%d,throw it away->%s.",EXCLOG_KLOG_LEN_MIN,klog);
		return 0;
	}

	char log_buf[EXCLOG_LOG_LEN_MAX] = { '\0' };
	strncpy(log_buf, klog, len - 1);
	log_buf[len - 1] = '\n';

	int level = LOG_NOTICE; /*default log level=6*/
	char tag[EXCLOG_LOG_LEN_MAX] = { '\0' };
	char content[EXCLOG_LOG_LEN_MAX] = { '\0' };

	char *pos1 = NULL;
	char *pos2 = NULL;

	/*get log level*/
	if (!(log_buf[0] == '<' && log_buf[2] == '>'))
	{
		DBG_SELF("Invalid content,not find '<' or '>',throw it away->%s.",log_buf);
		return 0;
	}
	level = log_buf[1] - '0';

	/*get log tag*/
	pos1 = strchr(log_buf, '[');
	pos2 = strchr(log_buf, ']');

	if (pos1 == NULL || pos2 == NULL)
	{
		DBG_SELF("not find [] in kernel log.");
		strncpy(tag, "kernel", sizeof(tag));
		strncpy(content, log_buf + 3, sizeof(content));
	}
	else
	{
		pos1++;
		strncpy(tag, pos1, pos2 - pos1);

		pos2++;
		strncpy(content, pos2, sizeof(content));
	}

	if ((klog_num >= EXCLOG_KLOG_PKT_NUM) || (1 == klog_pkt[klog_tail].status))
	{
		DBG_SELF("kernel log packet buffer is full(%d).",EXCLOG_KLOG_PKT_NUM);
		return -1;
	}

	memset(&klog_pkt[klog_tail], 0, sizeof(exclog_packet_t));
	klog_pkt[klog_tail].status = 1;
	klog_pkt[klog_tail].len = sprintf(klog_pkt[klog_tail].message, "<%d>kernel(%s)%s", level, tag, content);
	gettimeofday(&klog_pkt[klog_tail].tv, NULL);

	DBG_SELF("put klog len=%d,msg=%s.", klog_pkt[klog_tail].len,klog_pkt[klog_tail].message);

	klog_num++;
	klog_tail = (klog_tail + 1) >= EXCLOG_KLOG_PKT_NUM ? 0 : klog_tail + 1;

	return 0;
}
/********************************************************************************************
 * Function: __exclog_klog_get_queue()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: get exclog_packet_t from queue.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ pkt:IN&OUT,result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_klog_get_queue(exclog_packet_t *pkt)
{
	if ((0 == klog_num) || (0 == klog_pkt[klog_head].status))
	{
		return -1;
	}

	memcpy(pkt, &klog_pkt[klog_head], sizeof(exclog_packet_t));
	memset(&klog_pkt[klog_head], 0, sizeof(exclog_packet_t));

	DBG_SELF("get klog len=%d,msg=%s.", pkt->len,pkt->message);

	klog_num--;
	klog_head = (klog_head + 1) >= EXCLOG_KLOG_PKT_NUM ? 0 : klog_head + 1;

	return 0;
}
/********************************************************************************************
 * Function: __exclog_syslog_2_pkt()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:format syslog string to exclog_packet_t.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ syslog:IN,syslog string.
 *  @ len:IN,syslog length.
 *  @ pkt:IN&OUT,result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *		   0:success;
 * 		  -1:fail.
 ********************************************************************************************/
static int __exclog_syslog_process(const char *syslog, int len, exclog_packet_t *pkt)
{
	if (len <= EXCLOG_SYSLOG_LEN_MIN)
	{
		DBG_SELF("Invalid syslog,total_length<%d,throw it away->%s",EXCLOG_SYSLOG_LEN_MIN,syslog);
		return -1;
	}

	const char *tmp = syslog;
	char *pos1 = NULL;
	char *pos2 = NULL;

	/*length of PRI,HEAD,TAG,CONTENT*/
	int plen = 0;
	int hlen = 0;
	int tlen = 0;
	int clen = 0;

	char pri[EXCLOG_SYSLOG_PRI_LEN_MAX] = { '\0' };
	char head[EXCLOG_SYSLOG_HEAD_LEN] = { '\0' };
	char tag[EXCLOG_SYSLOG_TAG_LEN_MAX] = { '\0' };
	char content[EXCLOG_LOG_LEN_MAX] = { '\0' };

	/*PRI:get log level and module*/
	int digit = 0;
	int level = 0;
	int module = 0;
	char module_str[8] = { '\0' };

	pos1 = strchr(tmp, '<');
	if (pos1 == NULL)
	{
		DBG_SELF("Invalid syslog PRI,not found '<',throw it away->%s",syslog);
		return -1;
	}
	pos1++;

	pos2 = strchr(tmp, '>');
	if (pos2 == NULL)
	{
		DBG_SELF("Invalid syslog PRI,not found '>',throw it away->%s",syslog);
		return -1;
	}

	plen = pos2 - pos1;
	if ((plen < EXCLOG_SYSLOG_PRI_LEN_MIN - EXCLOG_SYSLOG_PRI_SYN_LEN) || (plen > EXCLOG_SYSLOG_PRI_LEN_MAX - EXCLOG_SYSLOG_PRI_SYN_LEN))
	{
		DBG_SELF("Invalid syslog PRI,length=%d,throw it away->%s",plen,syslog);
		return -1;
	}

	strncpy(pri, pos1, plen);
	pri[plen] = '\0';
	digit = atoi(pri);

	level = digit & LOG_PRIMASK;
	module = (digit & LOG_FACMASK) >> 3;
	if (module == LOG_KERN)
	{
		strncpy(module_str, "kernel", sizeof(module_str) - 1);
	}
	else
	{
		strncpy(module_str, "sys", sizeof(module_str) - 1);
	}

	/*HEAD:get date and time*/
	if ((len - plen) < EXCLOG_SYSLOG_HEAD_LEN)
	{
		DBG_SELF("Invalid syslog HEAD,length<%d,throw it away->%s",EXCLOG_SYSLOG_HEAD_LEN,syslog);
		return -1;
	}

	struct timeval tv;
	memset(&tv, 0, sizeof(tv));

	pos2++;
	if ((*(pos2 + 3) == ' ') && (*(pos2 + 6) == ' ') && (*(pos2 + 9) == ':') && (*(pos2 + 12)== ':') && (*(pos2 + 15) == ' '))
	{
		hlen = 16;
		pos1 = pos2 + hlen;

		strncpy(head, pos2, hlen - 1);
		head[hlen - 1] = '\0';

		if(__exclog_syslog_time_2_timeval(head, &tv)==-1)
		{
			DBG_SELF("Invalid syslog HEAD,unknown month or time,throw it away->%s",syslog);
			return -1;
		}
	}
	else
	{
		DBG_SELF("Invalid syslog HEAD,unknown date and time format,throw it away->%s",syslog);
		return -1;
	}

	/*TAG:get file name and line number*/
	pos2 = strchr(pos1, ':');
	if (pos2 == NULL)
	{
		DBG_SELF("Invalid syslog TAG,not found ':',throw it away->%s",syslog);
		return -1;
	}

	tlen = pos2 - pos1;
	if (tlen <= 0 || tlen > EXCLOG_SYSLOG_TAG_LEN_MAX)
	{
		DBG_SELF("Invalid syslog TAG,file name is too long(>%d),throw it away->%s",EXCLOG_SYSLOG_TAG_LEN_MAX,syslog);
		return -1;
	}

	strncpy(tag, pos1, tlen);
	tag[tlen] = '\0';

	/*CONTENT*/
	clen = len - plen - hlen - tlen - EXCLOG_SYSLOG_PRI_SYN_LEN -1;
	if (clen <= 0 || clen > EXCLOG_LOG_LEN_MAX-1)
	{
		DBG_SELF("Invalid syslog CONTENT,length=%d,throw it away->%s",clen,syslog);
		return -1;
	}

	pos2++;
	strncpy(content, pos2, clen);
	content[clen] = '\n';

	/*create exclog_packet_t*/
	pkt->tv = tv;
	pkt->len = snprintf(pkt->message, sizeof(pkt->message) - 1, "<%d>%s(%s)%s", level, module_str, tag, content);
	pkt->status = 1;

	return 0;
}
/********************************************************************************************
 * Function: __exclog_syslog_time_2_timeval()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:transfer datetime string to struct timeval. * 
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ datetime:IN,date and time string.
 *  @ tv:OUT,result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *		 0:success;
 *		-1:fail.
 ********************************************************************************************/
static int __exclog_syslog_time_2_timeval(const char *datetime, struct timeval *tv)
{
	char *key[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char buf[EXCLOG_SYSLOG_HEAD_LEN] = { '\0' };

	int mon = 0;
	int day = 0;
	int hour = 0;
	int min = 0;
	int sec = 0;

	int i = 0;
	int ret = 0;

	//get month
	strncpy(buf, datetime, 3);
	buf[3] = '\0';

	for (i = 0; key[i]; i++)
	{
		if (strcmp(buf, key[i]) == 0)
		{
			mon = i;
			break;
		}
		else if (key[i + 1] == NULL)
		{
			DBG_SELF("process syslog,invalid month.");
			return -1;
		}
	}

	//get day    
	if (*(datetime + 4) == ' ')
	{
		strncpy(buf, datetime + 5, 1);
		buf[1] = '\0';
	}
	else
	{
		strncpy(buf, datetime + 4, 2);
		buf[2] = '\0';
	}
	day = atoi(buf);

	//get time
	memset(buf,0,sizeof(buf));
	strncpy(buf, datetime + 7, sizeof(buf) - 1);

	ret = sscanf(buf, "%02d:%02d:%02d", &hour, &min, &sec);
	if (ret != 3)
	{
		DBG_SELF("process syslog,invalid time.");
		return -1;
	}

	//create struct timeval tv
	gettimeofday(tv, NULL);

	struct tm tm;
	memset(&tm, 0, sizeof(tm));
	localtime_r(&tv->tv_sec, &tm);

	tm.tm_mon = mon;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = min;
	tm.tm_sec = sec;

	tv->tv_sec = mktime(&tm);

	return 0;
}
