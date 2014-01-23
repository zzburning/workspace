/*******************************************************************************************
 * 					Filename: exclog_store.c
 ********************************************************************************************
 * Description:
 * 		format and store log. 
 * Copyright:
 * Author: 
 ********************************************************************************************/
#include "exclog_public.h"
#include "exclog_store.h"

exclog_flash_info_t region_list[EXCLOG_FILE_NUM_MAX] = { };/*memory region info array*/
int region_num = 0;/*current total region num*/
int region_cur = 0;/*current working region*/

#ifdef EXCLOG_2_FILE
static int __exclog_store_2_file(const exclog_packet_t *pkt);
static int __exclog_store_file_get(int len);
static int __exclog_store_file_erase(int index);
static int __exclog_store_file_write(const char *record, int record_len);
static void __exclog_store_message_2_string(const exclog_packet_t *pkt, char *record, int max_len, int *len);
#endif

#ifdef EXCLOG_2_FLASH
static int __exclog_store_2_flash(const exclog_packet_t *pkt);
static int __exclog_store_flash_get(int len);
static int __exclog_store_flash_erase(int index);
static int __exclog_store_flash_write(const exclog_record_t *record, int record_len);
static void __exclog_store_message_2_struct(const exclog_packet_t *pkt, exclog_record_t *record, int *len);
#endif

static void __exclog_subscribe_process(const char *record);

/********************************************************************************************
 * Function: _exclog_store()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: store log to file or flash.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt:IN,log to store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_store(const exclog_packet_t *pkt)
{
#ifdef EXCLOG_2_FILE	
	__exclog_store_2_file(pkt);
#endif

#ifdef EXCLOG_2_FLASH	
	__exclog_store_2_flash(pkt);
#endif

	return 0;
}
#ifdef EXCLOG_2_FILE
/********************************************************************************************
 * Function: __exclog_store_2_file()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: store log to file.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt:IN,log to store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_2_file(const exclog_packet_t *pkt)
{
	int ret = 0;
	int record_len = 0;
	char record[EXCLOG_RECORD_LEN_MAX] = { '\0' };
	__exclog_store_message_2_string(pkt, record, EXCLOG_RECORD_LEN_MAX, &record_len);

	if (!strcmp(EXCLOG_PATH, EXCLOG_STDOUT_MAGIK_STR))
	{
		fprintf(stdout, "%s", record);
	}
	else
	{
		ret = __exclog_store_file_get(record_len);
		if (ret < 0)
		{
			DBG_SELF("no ready log file.");
			return -1;
		}

		ret = __exclog_store_file_write(record, record_len);
		if (ret != 0)
		{
			DBG_SELF("store fail.");
			return -1;
		}
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_store_file_get()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: get file to write.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ len: IN,length needed to write record.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_file_get(int len)
{
	if (region_list[region_cur].left >= len)
	{
		return region_cur;
	}

	region_list[region_cur].status = 1;
	region_cur = ((region_cur + 1) >= region_num ? 0 : region_cur + 1);

	DBG_SELF("switch to %s/%s%d.",EXCLOG_PATH,EXCLOG_FILE_PREFIX,region_cur);

	if (0 == region_list[region_cur].status)
	{
		return region_cur;
	}
	else
	{
		int ret = __exclog_store_file_erase(region_cur);
		if (0 == ret)
		{
			return region_cur;
		}
		else
		{
			return -1;
		}
	}
}
/********************************************************************************************
 * Function: __exclog_store_file_erase()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: clear file.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ index:IN, clear which file.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_file_erase(const int index)
{
	region_list[index].status = 0;
	region_list[index].left = region_list[index].size;

	char devname[EXCLOG_FILE_NAME_LEN] = { '\0' };
	snprintf(devname, sizeof(devname) - 1, "%s/%s%d", EXCLOG_PATH, EXCLOG_FILE_PREFIX, index);

	//unlink(devname);

	FILE *fd = fopen(devname, "w");
	if (fd == NULL)
	{
		DEBUG_SELF("fopen %s fail,%s.",devname,strerror(errno));
		return -1;
	}
	fclose(fd);

	return 0;
}
/********************************************************************************************
 * Function: __exclog_store_file_write()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: write record to file.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ record:IN,record to store to file.
 * @ record_len:IN,length of record.
 * @ index:IN, write to which region.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_file_write(const char *record, int record_len)
{
	char devname[EXCLOG_FILE_NAME_LEN] = { '\0' };
	snprintf(devname, sizeof(devname) - 1, "%s/%s%d", EXCLOG_PATH, EXCLOG_FILE_PREFIX, region_cur);

	FILE *fd = fopen(devname, "a");
	if (fd == NULL)
	{
		DEBUG_SELF("fopen %s fail,%s.", devname, strerror(errno));
		return -1;
	}

	int wlen = 0;
	wlen = fwrite(record, record_len, 1, fd);
	if (wlen < 0)
	{
		DEBUG_SELF("write log to file fail.");
		fclose(fd);
		return -1;
	}
	fclose(fd);

	region_list[region_cur].left -= record_len;
	if (0 == region_list[region_cur].left)
	{
		region_list[region_cur].status = 1;
		region_cur = ((region_cur + 1) >= region_num ? 0 : region_cur + 1);
	}
	return 0;
}
/********************************************************************************************
 * Function: __exclog_store_message_2_string()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: format message to record string.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ pkt:IN,message to format.
 * @ record:OUT,result.
 * @ len:OUT,length of record.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_store_message_2_string(const exclog_packet_t *pkt, char *record, int max_len,
		int *len)
{
	struct tm tm;
	localtime_r(&(pkt->tv.tv_sec), &tm);

	*len = snprintf(record, max_len - 1, "%04d-%02d-%02d %02d:%02d:%02d;%s", (1900 + tm.tm_year),
			(1 + tm.tm_mon), tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, pkt->message);

	DBG_SELF("To store:len=%d,record=%s",*len,record);

	__exclog_subscribe_process(record);

	return;
}
#endif

#ifdef EXCLOG_2_FLASH
/********************************************************************************************
 * Function: __exclog_store_2_flash()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: store log to flash.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ pkt:IN,log to store.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_2_flash(const exclog_packet_t *pkt)
{
	int ret=0;
	int record_len=0;
	exclog_record_t record;
	memset(&record, 0, sizeof(record));
	__exclog_store_message_2_struct(pkt, &record, &record_len);

	ret=__exclog_store_flash_get(record_len);
	if (ret<0)
	{
		DEBUG_SELF("no ready log file.");
		return -1;
	}

	ret=__exclog_store_flash_write(&record, record_len);
	if (ret!=0)
	{
		DEBUG_SELF("store fail.");
		return -1;
	}DBG_SELF("store success.");

	return 0;
}
/********************************************************************************************
 * Function: __exclog_store_flash_get()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: get flash region to write.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ len: IN,length needed to write record.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_flash_get(int len)
{
	if (region_list[region_cur].left>=len)
	{
		return region_cur;
	}

	region_list[region_cur].status=1;
	region_cur=((region_cur+1)>=region_num ? 0 : region_cur+1);

	DBG_SELF("switch to message[%d].",region_cur);
	if (0==region_list[region_cur].status)
	{
		return region_cur;
	}
	else
	{
		int ret=__exclog_store_flash_erase(region_cur);
		if (0==ret)
		{
			return region_cur;
		}
	}

	return -1;
}
/********************************************************************************************
 * Function: __exclog_store_flash_erase()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: erase flash region.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ index:IN, erase which region.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_flash_erase(const int index)
{
	struct erase_info_user erase;
	memset(&erase, 0, sizeof(erase));
	erase.start=region_list[index].offset;
	erase.length=region_list[index].size;

	char devname[EXCLOG_FILE_NAME_LEN]=
	{	'\0'};
	snprintf(devname,sizeof(devname)-1, "%s", EXCLOG_PATH);

	int fd=open(devname, O_RDWR);
	if (-1==fd)
	{
		DEBUG_SELF("open %s fail,%s.", devname, strerror(errno));
		return -1;
	}

	int success=1;
	if (0==ioctl(fd, MEMERASE, &erase))
	{
		DBG_SELF("erase region[%d] success.",index);
	}
	else
	{
		DBG_SELF("erase region[%d] fail.",index);
		success=0;
	}
	close(fd);

	if (1==success)
	{
		region_list[index].pos=0;
		region_list[index].status=0;
		region_list[index].left=region_list[index].size;
	}
	else
	{
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: __exclog_store_flash_write()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: write record to flash.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ record:IN,record to store to flash.
 * @ record_len:IN,length of record.
 * @ index:IN, write to which region.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
static int __exclog_store_flash_write(const exclog_record_t *record, int record_len)
{
	FILE *fd=fopen(EXCLOG_PATH, "ab");
	if (fd==NULL)
	{
		DEBUG_SELF("open %s fail,%s.", EXCLOG_PATH, strerror(errno));
		return -1;
	}

	int start=region_list[region_cur].offset+region_list[region_cur].pos;
	if (fseek(fd, start, SEEK_SET)!=0)
	{
		fclose(fd);
		DEBUG_SELF("fseek to 0x%x fail,%s.",start,strerror(errno));
		return -1;
	}

	int wlen=0;
	wlen=fwrite((const void*)record, record_len, 1, fd);
	if (wlen<0)
	{
		DEBUG_SELF("write log to flash fail.");
		fclose(fd);
		return -1;
	}DBG_SELF("write log to flash success.");

	region_list[region_cur].pos+=record_len;
	region_list[region_cur].left-=record_len;
	if (0==region_list[region_cur].left)
	{
		region_list[region_cur].status=1;
		region_cur=((region_cur+1)>=region_num ? 0 : region_cur+1);
	}

	fclose(fd);

	return 0;
}
/********************************************************************************************
 * Function: __exclog_store_message_2_struct()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: format message to record struct for EXCLOG_2_FLASH.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt:IN,message to format.
 * @ record:OUT,result.
 * @ len:OUT,length of record.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_store_message_2_struct(const exclog_packet_t *pkt, exclog_record_t *record, int *len)
{
	exclog_head_t head;
	memset(&head, 0, sizeof(head));
	head.magik=EXCLOG_RECORD_MAGIK;
	head.time=pkt->tv.tv_sec;
	head.len=pkt->len;

	record->head=head;
	strncpy(record->message, pkt->message,sizeof(record->message)-1);
	record->message[sizeof(record->message)-1]='\0';

	*len=sizeof(head)+pkt->len;

	return;
}
#endif

/********************************************************************************************
 * Function: __exclog_subscribe_process()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:start subscribe callback function according to event.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ record:IN,log message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :NULL.
 ********************************************************************************************/
static void __exclog_subscribe_process(const char *record)
{
	if (0 == slist_num)
	{
		DBG_SELF("there is no subscriber.");
		return;
	}

	unsigned long level;
	unsigned long module;

	char level_str[16] = { '\0' };
	char module_str[16] = { '\0' };

	const char *tmp = record;
	char *pos1 = NULL;
	char *pos2 = NULL;

	//get level
	pos1 = strchr(tmp, '<');
	pos2 = strchr(tmp, '>');

	if (pos1 == NULL || pos2 == NULL)
	{
		return;
	}

	pos1++;

	strncpy(level_str, pos1,
			((pos2 - pos1) <= (sizeof(level_str) - 1))\
			? (pos2 - pos1) : (sizeof(level_str) - 1));

	level_str[pos2 - pos1] = '\0';
	level = _exclog_level_str_2_hex(level_str);

	//get module
	pos1 = strchr(tmp, '(');
	pos2++;

	if (pos1 == NULL || pos2 == NULL)
		return;

	strncpy(module_str, pos2,
			((pos1 - pos2) <= (sizeof(module_str) - 1))\
			? (pos1 - pos2) : (sizeof(module_str) - 1));

	module_str[pos1 - pos2] = '\0';
	module = _exclog_module_str_2_hex(module_str);

	//check subscribe list
	int i;
	for (i = 0; i < EXCLOG_SUBSCRIBE_NUM_MAX; i++)
	{
		if ((module & slist[i].module) && (level & slist[i].level))
		{
			exclog_subscribe_rps_t rps;
			memset(&rps, 0, sizeof(rps));

			rps.level = atoi(level_str);
			strncpy(rps.module, module_str, sizeof(rps.module) - 1);
			strncpy(rps.message, record, sizeof(rps.message) - 1);

			slist[i].sub_f(&rps);
		}
		else if (slist[i].module == EXCLOG_MODULE_NONE)
		{
			break;
		}
	}

	return;
}
