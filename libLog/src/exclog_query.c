/*******************************************************************************************
 * 					Filename: exclog_query.c
 ********************************************************************************************
 * Description:
 * 		 log query for libexcLOG.
 * Copyright:
 * Author: 
 *******************************************************************************************/
#include "exclog_public.h"
#include "exclog_query.h"
#include "exclog_store.h"

static exclog_query_rps_t *rps_head=NULL;
static exclog_query_rps_t *rps_tail=NULL;
static int exclog_query_switch=0;
static int exclog_query_state=0;

#ifdef EXCLOG_2_FILE
static int __exclog_query_file(char *ip, exclog_query_rps_t **rps);
#endif

#ifdef EXCLOG_2_FLASH
static int __exclog_query_flash(char *ip, const exclog_query_req_t *req, exclog_query_rps_t **rps);
static int __exclog_query_check_flash(char *ip, const exclog_query_req_t *req, exclog_record_t *record,exclog_query_rps_t **rps);
static int __exclog_query_check_head(const exclog_query_req_t *req, exclog_head_t *head, char *time);
static int __exclog_query_check_message(char *ip, const exclog_query_req_t *req, char *message, char *time,exclog_query_rps_t **rps);
#endif

static int __exclog_query_create_rps(unsigned long level, unsigned long module, char *time, char *data,exclog_query_rps_t **rps);
static int __exclog_query_check_record(char *ip, const exclog_query_req_t *req, char *record, exclog_query_rps_t **rps);
static int __exclog_query_check_time(const exclog_query_req_t *req, const char *time);
static unsigned long __exclog_query_check_level(const exclog_query_req_t *req, char *level);
static unsigned long __exclog_query_check_module(const exclog_query_req_t *req, char *module);

static void __exclog_datetime_2_time_t(const exclog_datetime_t *src, time_t *dst);
static void __exclog_str_2_datetime(const char *src, exclog_datetime_t *dst);

#if defined(EXCLOG_2_REMOTE)
static int __exclog_query_req_send(exclog_query_req_t *req);
static int __exclog_query_rps_recv(exclog_query_rps_t **req);
#endif

/********************************************************************************************
 * Function: _exclog_query_check_req()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: check validity of query request.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN, req to check.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:valid.
 * 		 1:start time invalid.
 * 		 2:end time invalid.
 * 		 3:start time > end time
 * 		 4:level invalid.
 * 		 5:module invalid.
 * 		 6:empty request.
 ********************************************************************************************/
int _exclog_query_check_req(const exclog_query_req_t *req)
{
	if (req==NULL)
	{
		return 6;
	}

	/*------------check datatime---------------*/
	exclog_datetime_t stime, etime;
	stime = req->stime;
	etime = req->etime;

	if (!((stime.year >= 1900) && (stime.year <= 2030)\
			&& (stime.month >= 1) && (stime.month <= 12)\
			&& (stime.day >= 0) && (stime.day <= 31)\
			&& (stime.hour >= 0) && (stime.hour <= 23)\
			&& (stime.minute >= 0) && (stime.minute <= 59)\
			&& (stime.second >= 0) && (stime.second	<= 59)))
	{
		return 1;
	}

	if (!((etime.year >= 1900) && (etime.year <= 2030)\
			&& (etime.month >= 1) && (etime.month <= 12)\
			&& (etime.day >= 0) && (etime.day <= 31)\
			&& (etime.hour >= 0) && (etime.hour <= 23)\
			&& (etime.minute >= 0) && (etime.minute <= 59)\
			&& (etime.second >= 0) && (etime.second	<= 59)))
	{
		return 2;
	}

	time_t st, et;
	__exclog_datetime_2_time_t(&stime, &st);
	__exclog_datetime_2_time_t(&etime, &et);
	if (st>et)
	{
		return 3;
	}

	/*------------check log level---------------*/
	if (!((req->level & EXCLOG_LEVEL_EMERG) \
			|| (req->level & EXCLOG_LEVEL_CRIT) \
			|| (req->level & EXCLOG_LEVEL_ALERT)\
			|| (req->level & EXCLOG_LEVEL_ERR)\
			|| (req->level & EXCLOG_LEVEL_WARNING)\
			|| (req->level & EXCLOG_LEVEL_NOTICE)\
			|| (req->level & EXCLOG_LEVEL_INFO)\
			|| (req->level & EXCLOG_LEVEL_DEBUG)))
	{
		return 4;
	}

	/*------------check module------------------*/
	if (!((req->module & EXCLOG_MODULE_KERNEL)\
			|| (req->module & EXCLOG_MODULE_SYSLOG)\
			|| (req->module & EXCLOG_MODULE_HXSDK)\
			|| (req->module & EXCLOG_MODULE_LIB_CEO)\
			|| (req->module & EXCLOG_MODULE_LIB_AA)\
			|| (req->module & EXCLOG_MODULE_LIB_SOE)\
			|| (req->module	& EXCLOG_MODULE_LIB_SAP)\
			|| (req->module & EXCLOG_MODULE_LIB_PTZ)\
			|| (req->module & EXCLOG_MODULE_LIB_LOG)\
			|| (req->module & EXCLOG_MODULE_LIB_PM)\
			|| (req->module	& EXCLOG_MODULE_LIB_SIS)\
			|| (req->module & EXCLOG_MODULE_LIB_DAVINCI)\
			|| (req->module & EXCLOG_MODULE_CORE_OTHER)\
			|| (req->module	& EXCLOG_MODULE_APP_S2506A)\
			|| (req->module & EXCLOG_MODULE_APP_SIPUA)\
			|| (req->module	& EXCLOG_MODULE_APP_HXWEB)\
			|| (req->module & EXCLOG_MODULE_APP_HXGUI)\
			|| (req->module	& EXCLOG_MODULE_APP_OTHER)))
	{
		return 5;
	}

	return 0;
}
/********************************************************************************************
 * Function: _exclog_query_startup()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: start to query log from local,free last query results first if it's not freed by user.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ ip: IN,IP address of query request.
 * @ rps: OUT,query result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 *   	-1:fail.
 ********************************************************************************************/
int _exclog_query_startup(char *ip, exclog_query_rps_t **rps)
{
	_exclog_query_free(*rps);

	exclog_query_switch=1;
	exclog_query_state=1;

	int ret=0;

#ifdef EXCLOG_2_FILE
	ret=__exclog_query_file(ip,rps);
#endif

#ifdef EXCLOG_2_FLASH
	ret=__exclog_query_flash(ip,req,rps);
#endif

	exclog_query_state=0;

	return ret;
}
/********************************************************************************************
 * Function: _exclog_query_stop()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: stop query,free log in rps list which is not read by user yet.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
void _exclog_query_stop(void)
{
	exclog_query_switch = 0;

	while(exclog_query_state)
	{
		usleep(1000);
	}

	_exclog_query_free(NULL);

	return;
}
/********************************************************************************************
 * Function: _exclog_query_free()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: free query result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ rps: IN,query result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
void _exclog_query_free(exclog_query_rps_t *rps)
{
	exclog_query_rps_t *tmp = rps_head;
	while (tmp)
	{
		rps_head = rps_head->next;
		free(tmp);
		tmp = rps_head;
	}

	if(rps)
	{
		rps=NULL;
	}
	return;
}

#ifdef EXCLOG_2_FILE
/********************************************************************************************
 * Function: __exclog_query_file()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: query log from file.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @  ip: IN,IP address of query request.
 * @ rps: OUT,query result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 	  >=0:num of query result.
 *   		-1:fail.
 ********************************************************************************************/
static int __exclog_query_file(char *ip, exclog_query_rps_t **rps)
{
	query_info.rps_num=0;

	int i=0;
	int ret=0;
	int stop=0;
	int start=query_info.region_index;

	char devname[EXCLOG_FILE_NAME_LEN]= { '\0' };
	char record[EXCLOG_RECORD_LEN_MAX]= { '\0' };
	FILE *fd=NULL;

	for (i = start; i < EXCLOG_FILE_NUM_MAX; i++)
	{
		if (exclog_query_switch)
		{
			memset(devname, 0, sizeof(devname));
			snprintf(devname, sizeof(devname) - 1, "%s/%s%d", EXCLOG_PATH, EXCLOG_FILE_PREFIX, i);
			fd = fopen(devname, "r");
			if (fd == NULL)
			{
				if (errno == 2)
				{
					/*devname is not exist*/
					continue;
				}
				DEBUG_SELF("fopen %s.", strerror(errno));
				goto err;
			}
			DBG_SELF("open %s success.", devname);

			if (i == query_info.region_index)
			{
				fseek(fd, query_info.region_pos, SEEK_SET);
			}

			stop = 0;
			while (!stop && exclog_query_switch)
			{
				if (query_info.rps_num >= EXCLOG_RESPONSE_NUM_MAX)
				{
					DBG_SELF("read %d log.", EXCLOG_RESPONSE_NUM_MAX);
					fclose(fd);
					return query_info.rps_num;
				}

				memset(&record, 0, sizeof(record));
				if (fgets(record, EXCLOG_RECORD_LEN_MAX, fd) == NULL)
				{
					/*read end of file*/
					stop = 1;
					query_info.region_pos = 0;
				}
				else
				{
					DBG_SELF("fgets record len=%d.",strlen(record));
					/*if record is matched with req,add it to rps_list;if not,ignore it.*/
					ret = __exclog_query_check_record(ip, &query_info.req, record, rps);
					if (0 == ret)
					{
						query_info.rps_num++;
					}
					query_info.region_pos += strlen(record);
				}
			}
			fclose(fd);

			query_info.region_index++;
		}
		else
		{
			break;//stop query
		}
	}//end for

	return query_info.rps_num;

err: if (fd)
	{
		fclose(fd);
	}
	return -1;
}
#endif

#ifdef EXCLOG_2_FLASH
/********************************************************************************************
 * Function: __exclog_query_flash()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: query log from flash.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @  ip: IN,IP address of query request.
 * @ req: IN,query request.
 * @ rps: OUT,query result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 *    -1:fail.
 ********************************************************************************************/
static int __exclog_query_flash(char *ip, const exclog_query_req_t *req, exclog_query_rps_t **rps)
{
	DBG_SELF("query %s.", EXCLOG_PATH);

	FILE *fd=fopen(EXCLOG_PATH, "rb");
	if (fd==NULL)
	{
		DEBUG_SELF("fopen %s.", strerror(errno));
		return -1;
	}

	int i=0;
	int ret=0;
	int start=0;
	int read_size=0;
	exclog_record_t record;

	for (i=0; i<EXCLOG_FILE_NUM_MAX; i++)
	{
		DBG_SELF("read flash region[%d].", i+1);

		read_size=0;
		start=region_list[i].offset;

		if (fseek(fd, start, SEEK_SET)!=0)
		{
			fclose(fd);
			DEBUG_SELF("fseek to 0x%x fail,%s.", start, strerror(errno));
			return -1;
		}

		while (read_size<region_list[i].size)
		{
			memset(&record, 0, sizeof(record));
			ret=fread(&record, sizeof(record), 1, fd);
			if (ret<=0)
			{
				break;//read end of file or error
			}
			read_size+=ret*sizeof(record);
			DBG_SELF("read_size=%d,total_size=%d.", read_size, region_list[i].size);
			break;
			__exclog_query_check_flash(ip, req, &record, rps);
		}//end while
	}//end for(i<EXCLOG_FILE_NUM_MAX)

	DBG_SELF("Finish.");

	fclose(fd);

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_check_flash()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:	judge if record is matched with request,
 * 					add to rps_list if it's matched.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,request to check.
 * @ record:IN,record to check.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success,matched;
 * 		  -1:fail, not matched.
 ********************************************************************************************/
static int __exclog_query_check_flash(char *ip, const exclog_query_req_t *req, exclog_record_t *record,
		exclog_query_rps_t **rps)
{
	int ret=0;
	char time[64]= { '\0' };
	ret=__exclog_query_check_head(req, &(record->head), time);
	if (-1==ret || time==NULL)
	{
		DEBUG_SELF("Invalid head.");
		return -1;
	}

	ret=__exclog_query_check_message(ip, req, record->message, time, rps);
	if (-1==ret)
	{
		DBG_SELF("message is not matched.");
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_check_head()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:	check record head,get time and log length.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,request to check.
 * @ head:IN,head to check.
 * @ time:OUT,log time string.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success,matched;
 * 		  -1:fail, not matched.
 ********************************************************************************************/
static int __exclog_query_check_head(const exclog_query_req_t *req, exclog_head_t *head, char *time)
{
	DBG_SELF("read head from flash:magik=%x,time=%ld,len=%d.", head->magik, head->time, head->len);

	if (head->magik!=EXCLOG_RECORD_MAGIK)
	{
		DEBUG_SELF("Invalid magik.");
		return -1;
	}

	time_t st, et;
	__exclog_datetime_2_time_t(&req->stime, &st);
	__exclog_datetime_2_time_t(&req->etime, &et);

	if (!(head->time>=st && head->time<=et))
	{
		DBG_SELF("time is not matched.");
		return -1;
	}

	__exclog_time_t_2_str(&(head->time), time);

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_check_message()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:	check message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,request to check.
 * @ message:IN,message to check.
 * @ time:IN,log time.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success,matched;
 * 		  -1:fail, not matched.
 ********************************************************************************************/
static int __exclog_query_check_message(char *ip, const exclog_query_req_t *req, char *message, char *time,
		exclog_query_rps_t **rps)
{
	char log_ip[32]= { '\0' };
	char log_data[EXCLOG_LOG_LEN_MAX]= { '\0' };
	char *pos1=NULL;
	char *pos2=NULL;

	/*--------------------get log owner's IP----------------------*/
	pos1=strchr(message, '[');
	if (pos1==NULL)
	{
		DEBUG_SELF("Not found '[' in packet.");
		return -1;
	}
	pos1++;

	pos2=strchr(message, ']');
	if (pos2==NULL)
	{
		DEBUG_SELF("Not found ']' in packet.");
		return -1;
	}
	strncpy(log_ip, pos1, ((pos2-pos1)>(sizeof(log_ip)-1))?(sizeof(log_ip)-1):pos2-pos1);
	log_ip[pos2-pos1]='\0';

	/*--------------------get other data except IP----------------------*/
	pos2++;
	pos1=strchr(message, '\n');
	if (pos1==NULL)
	{
		DEBUG_SELF("Not found '\n' in packet.");
		return -1;
	}
	strncpy(log_data, pos2, pos1-pos2);
	log_data[pos1-pos2]='\0';

	//transfer time to string
	char record[EXCLOG_RECORD_LEN_MAX]= { '\0' };
	snprintf(record,sizeof(record)-1, "%s;%s\t--->%s\n", time, log_data, log_ip);

	__exclog_query_check_record(ip, req, record, rps);

	return 0;
}
#endif

/********************************************************************************************
 * Function: __exclog_query_check_record()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:	judge if record is matched with request,
 * 					add to rps_list if it's matched.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @  ip: IN,IP address of query request.
 * @ req:IN,request to check.
 * @ record:IN,record to check.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success,matched;
 * 	  -1:fail, not matched.
 ********************************************************************************************/
static int __exclog_query_check_record(char *ip, const exclog_query_req_t *req, char *record, exclog_query_rps_t **rps)
{
	DBG_SELF("read record=%s", record);

	int ret=0;
	unsigned long level=0;
	unsigned long module=0;

	char time[32]= { '\0' };
	char level_str[16]= { '\0' };
	char module_str[16]= { '\0' };
	char data[EXCLOG_LOG_LEN_MAX]= { '\0' };
	char log_ip[32]= { '\0' };

	char *tmp=record;
	char *pos1=NULL;
	char *pos2=NULL;

	/*--------------------get and check log time----------------------*/
	pos1=tmp;
	pos2=strchr(tmp, ';');
	if (pos2==NULL)
	{
		DEBUG_SELF("Not found ';' in log.");
		return -1;
	}

	strncpy(time, pos1, pos2-pos1);
	time[pos2-pos1]='\0';

	ret=__exclog_query_check_time(req, time);
	if (ret!=0)
	{
		DBG_SELF("time is not matched.");
		return -1;
	}

	/*--------------------get and check log level----------------------*/
	pos1=strchr(tmp, '<');
	if (pos1==NULL)
	{
		DEBUG_SELF("Not found '<' in log.");
		return -1;
	}
	pos1++;

	pos2=strchr(tmp, '>');
	if (pos2==NULL)
	{
		DEBUG_SELF("Not found '>' in log.");
		return -1;
	}

	strncpy(level_str, pos1, pos2-pos1);
	level_str[pos2-pos1]='\0';

	level=__exclog_query_check_level(req, level_str);
	if (level==0)
	{
		DBG_SELF("level is not matched.");
		return -1;
	}

	/*--------------------get and check log module----------------------*/
	pos2++;
	pos1=strchr(tmp, '(');
	if (pos1==NULL)
	{
		DEBUG_SELF("Not found '(' in log.");
		return -1;
	}
	strncpy(module_str, pos2, pos1-pos2);
	module_str[pos1-pos2]='\0';

	module=__exclog_query_check_module(req, module_str);
	if (module==0)
	{
		DBG_SELF("module is not matched.");
		return -1;
	}

	strncpy(data, pos1,sizeof(data)-1);
	data[sizeof(data)-1]='\0';

	DBG_SELF("data=%s.", data);
	/*--------------------get and check IP address-----------------------*/
	pos1=strchr(tmp, '\t');
	if (pos1==NULL)
	{
		if (ip!=NULL)
		{
			DEBUG_SELF("Not found '\t' in log.");
			return -1;
		}
	} else
	{
		pos1+=5;
		pos2=strchr(tmp, '\n');
		if (pos2==NULL)
		{
			DEBUG_SELF("Not found '\n' in log.");
			return -1;
		}
		strncpy(log_ip, pos1, pos2-pos1);
		log_ip[pos2-pos1]='\0';

		if (ip==NULL)
		{
			char local_ip[32]= { '\0' };
			if (_exclog_public_get_ipaddr(local_ip)!=0)
			{
				DEBUG_SELF("get local ip fail.");
				return -1;
			}

			if (strcmp(log_ip, local_ip)!=0)
			{
				DBG_SELF("IP is not matched.");
				return -1;
			}

		} else if (strcmp(log_ip, ip)!=0)
		{
			DBG_SELF("IP is not matched.");
			return -1;
		}

		pos1=data;
		pos2=strchr(data, '\t');
		data[pos2-pos1]='\n';
		data[pos2-pos1+1]='\0';
	}

	/*----------------create rps and add to rps_list---------------------*/
	ret=__exclog_query_create_rps(level, module, time, data, rps);
	if (ret!=0)
	{
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_check_time()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: check if time is matched.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,request to check.
 * @ time:IN,log time.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *			0:success,matched;
 * 	     -1:fail,not matched.
 ********************************************************************************************/
static int __exclog_query_check_time(const exclog_query_req_t *req, const char *time)
{
	exclog_datetime_t datetime;
	memset(&datetime, 0, sizeof(datetime));
	__exclog_str_2_datetime(time, &datetime);

	time_t st, et, tick;
	__exclog_datetime_2_time_t(&req->stime, &st);
	__exclog_datetime_2_time_t(&req->etime, &et);
	__exclog_datetime_2_time_t(&datetime, &tick);

	if (!(tick>=st && tick<=et))
	{
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_check_level()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: check if level is matched.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,request to check.
 * @ level:IN,log level string.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *		 ret:success,matched;
 * 	      0:fail,not matched.
 ********************************************************************************************/
static unsigned long __exclog_query_check_level(const exclog_query_req_t *req, char *level)
{
	unsigned long ret=_exclog_level_str_2_hex(level);

	if (!(ret & req->level))
	{
		return 0;
	}
	return ret;
}
/********************************************************************************************
 * Function: __exclog_query_check_module()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: check if module of message is matched.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,req to check.
 * @ module:IN,module to check.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 *		 ret:success,matched;
 * 	      0:fail,not matched.
 ********************************************************************************************/
static unsigned long __exclog_query_check_module(const exclog_query_req_t *req, char *module)
{
	unsigned long ret=_exclog_module_str_2_hex(module);

	if (!(ret & req->module))
	{
		return 0;
	}

	return ret;
}
/********************************************************************************************
 * Function: __exclog_query_create_rps()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: create and set response array.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ level: IN,log level.
 * @ module:IN,log module.
 * @ tick:IN,log time.
 * @ data:IN,log data.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 *       -1:fail.
 ********************************************************************************************/
static int __exclog_query_create_rps(unsigned long level, unsigned long module, char *time, char *data,
		exclog_query_rps_t **rps)
{
	if (*rps==NULL)
	{
		*rps=(exclog_query_rps_t *)calloc(1, sizeof(exclog_query_rps_t));
		if (*rps==NULL)
		{
			DEBUG_SELF("no memory.");
			goto err;
		}
		rps_head=*rps;
		rps_tail=*rps;
	} else
	{
		rps_tail->next=(exclog_query_rps_t *)calloc(1, sizeof(exclog_query_rps_t));
		if (rps_tail->next==NULL)
		{
			DEBUG_SELF("no memory.");
			goto err;
		}
		rps_tail=rps_tail->next;
	}

	rps_tail->level=level;
	rps_tail->module=module;

	strncpy(rps_tail->data, data,sizeof(rps_tail->data)-1);
	rps_tail->data[sizeof(rps_tail->data)-1]='\0';

	__exclog_str_2_datetime(time, &rps_tail->tick);

	return 0;

err:
	_exclog_query_free(*rps);
	return -1;
}
/********************************************************************************************
 * Function: __exclog_datetime_2_time_t()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: transfer datetime to time_t.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ src:IN,datetime to transfer.
 * @ dst:OUT,result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_datetime_2_time_t(const exclog_datetime_t *src, time_t *dst)
{
	struct tm tm;
	tm.tm_year=src->year-1900;
	tm.tm_mon=src->month-1;
	tm.tm_mday=src->day;
	tm.tm_hour=src->hour;
	tm.tm_min=src->minute;
	tm.tm_sec=src->second;

	*dst=timegm(&tm);
	return;
}
/********************************************************************************************
 * Function: __exclog_char_2_datetime()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: transfer string to datetime.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ src:IN,time string to transfer.
 * @ dst:OUT,result.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_str_2_datetime(const char *src, exclog_datetime_t *dst)
{
	sscanf(src, "%04d-%02d-%02d %02d:%02d:%02d", &dst->year, &dst->month, &dst->day, &dst->hour, &dst->minute,
			&dst->second);

	return;
}

#if defined(EXCLOG_2_REMOTE)
/********************************************************************************************
 * Function: _exclog_query_from_remote()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:query log from remote.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ req: IN,query request.
 * @ rps: OUT,query result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 *    -1:fail.
 ********************************************************************************************/
int _exclog_query_from_remote(exclog_query_req_t *req, exclog_query_rps_t **rps)
{
	int ret=0;

	ret=__exclog_query_req_send(req);
	if (ret!=0)
	{
		DEBUG_SELF("__exclog_query_req_send fail.");
		return -1;
	}

	__exclog_query_rps_recv(rps);
	if (ret!=0)
	{
		DEBUG_SELF("__exclog_query_rps_recv fail.");
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_req_send()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:send log query request to remote.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ req: IN,query request.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 *    -1:fail.
 ********************************************************************************************/
static int __exclog_query_req_send(exclog_query_req_t *req)
{
	int sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if (-1==sockfd)
	{
		DEBUG_SELF("create socket fail,%s.", strerror(errno));
		return -1;
	}

	struct sockaddr_in remote;
	memset(&remote, 0, sizeof(remote));
	remote.sin_family=AF_INET;
	remote.sin_addr.s_addr=inet_addr(SERVER_IP);
	remote.sin_port=htons(EXCLOG_QUERY_REQ_PORT);

	socklen_t socklen=sizeof(struct sockaddr);

	int ret=sendto(sockfd, (char *)req, sizeof(exclog_query_req_t), 0, (struct sockaddr *)&remote, socklen);
	if (-1==ret)
	{
		DEBUG_SELF("send query request fail,%s.", strerror(errno));
		return -1;
	}

	DBG_SELF("send query request success.");

	return 0;
}
/********************************************************************************************
 * Function: __exclog_query_rps_recv()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:receive log query result from remote.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ rps: OUT,query result.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 *    -1:fail.
 ********************************************************************************************/
static int __exclog_query_rps_recv(exclog_query_rps_t **rps)
{
	int sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if (-1==sockfd)
	{
		DEBUG_SELF("create socket fail,%s.", strerror(errno));
		goto err;
	}

	struct sockaddr_in local;
	memset(&local, 0, sizeof(local));
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	local.sin_port=htons(EXCLOG_QUERY_RPS_PORT);

	socklen_t socklen=sizeof(struct sockaddr);

	if (bind(sockfd, (struct sockaddr *)&local, socklen)==-1)
	{
		DEBUG_SELF("bind fail,%s.", strerror(errno));
		goto err;
	}

	exclog_query_rps_t *tail=NULL, *tmp=NULL;
	exclog_query_remote_rps_t remote_rps;

	fd_set readfd;
	struct timeval tv= { 1, 0 };

	int ret=0;
	int total_time=0;
	while (total_time<EXCLOG_QUERY_TIME_OUT)
	{
		FD_ZERO(&readfd);
		FD_SET(sockfd, &readfd);
		tv.tv_sec=1;
		tv.tv_usec=0;

		ret=select(sockfd+1, &readfd, NULL, NULL, &tv);
		switch (ret)
		{
		case -1:
			if (errno!=EINTR)
			{
				DEBUG_SELF("select fail,%s.", strerror(errno));
				goto err;
			}
			break;
		case 0:
			DBG_SELF("select time out.");
			break;
		default:
			memset(&remote_rps, 0, sizeof(remote_rps));
			ret=recvfrom(sockfd, (char *)&remote_rps, sizeof(exclog_query_remote_rps_t), 0, NULL, &socklen);
			if (-1==ret)
			{
				DEBUG_SELF("recvfrom fail,%s.", strerror(errno));
				goto err;
			}

			if (remote_rps.tick.year==0 && remote_rps.tick.month==0 && remote_rps.tick.day==0)
			{
				if (!strcmp(remote_rps.data, "fail"))
				{
					DEBUG_SELF("query fail.");
					goto err;
				} else if (!strcmp(remote_rps.data, "finish"))
				{
					DBG_SELF("query finish.");
					total_time=EXCLOG_QUERY_TIME_OUT;
				}
			} else
			{
				if (*rps==NULL)
				{
					*rps=(exclog_query_rps_t *)calloc(1, sizeof(exclog_query_rps_t));
					if (*rps==NULL)
					{
						DEBUG_SELF("no memory.");
						goto err;
					}
					tmp=*rps;
					tail=*rps;
				} else
				{
					tail->next=(exclog_query_rps_t *)calloc(1, sizeof(exclog_query_rps_t));
					if (tail->next==NULL)
					{
						DEBUG_SELF("no memory.");
						goto err;
					}
					tmp=tail->next;
					tail=tail->next;
				}

				tmp->tick=remote_rps.tick;
				tmp->level=remote_rps.level;
				tmp->module=remote_rps.module;
				strncpy(tmp->data, remote_rps.data,sizeof(tmp->data)-1);
				tmp->data[sizeof(tmp->data)-1]='\0';
			}
			break;
		}

		total_time++;
	}

	return 0;

err:
	tmp=*rps;
	while (tmp)
	{
		*rps=(*rps)->next;
		free(tmp);
		tmp=*rps;
	}

	return -1;
}
#endif
