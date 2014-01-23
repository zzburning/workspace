/*******************************************************************************************
 * 					Filename: exclog_public.h
********************************************************************************************
 * Description:
 * 		 this is a public file header for libexcLOG.
 * Version:
 * 	     V_0.5 May-24-2010
 * Copyright:
 * Author: 
 * History:
 * 		 V_0.1 Initial version of this code.
********************************************************************************************/
#ifndef __EXCLOG_PUBLIC_H_
#define __EXCLOG_PUBLIC_H_

#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/klog.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/socket.h>

#include "exclog.h"
#include "exclog_query.h"

/*store log to file or flash*/
#define EXCLOG_2_FILE	1
//#define EXCLOG_2_FLASH	1

//#define EXCLOG_QUERY_SWITCH	1	/*enable or disable receive remote query request*/
/*******************************************************************************************/
#define EXCLOG_LEVEL_DEFAULT 		(5)/*default log level*/

/**
 * log file num,[1,10]
 **/
#define EXCLOG_FILE_NUM_MIN	(1)
#define EXCLOG_FILE_NUM_MAX	(10)
#define EXCLOG_FILE_NUM_DEFAULT	(6)

/**
 * log file size,[512KB,1MB]
 **/
#define EXCLOG_FILE_SIZE_MIN	(524288)
#define EXCLOG_FILE_SIZE_MAX	(1048576)
#define EXCLOG_FILE_SIZE_DEFAULT  EXCLOG_FILE_SIZE_MAX
/**
 * max message and record length,max log file name length
 **/
#define EXCLOG_MSG_LEN_MAX 			(EXCLOG_LOG_LEN_MAX + 64)
#define EXCLOG_RECORD_LEN_MAX 		(EXCLOG_MSG_LEN_MAX + 20)
#define EXCLOG_FILE_NAME_LEN			(EXCLOG_FILE_PATH_LEN + 10)

/**
 * buffer size: sizeof(exclog_packet_t)*EXCLOG_QUEUE_SIZE
 */
#ifdef DEBUG
#define EXCLOG_QUEUE_SIZE			(1024)
#else
#define EXCLOG_QUEUE_SIZE			(128)
#endif

#define EXCLOG_POOL_SIZE				(10)
#define EXCLOG_REPEAT_NUM_MAX		(1000)
#define EXCLOG_RESPONSE_NUM_MAX		(128)
#define EXCLOG_SUBSCRIBE_NUM_MAX		(128)

#define EXCLOG_QUERY_REQ_PORT 		(6000)
#define EXCLOG_QUERY_RPS_PORT 		(6005)
#define EXCLOG_QUERY_TIME_OUT		(30)

#define EXCLOG_IPADDRESS_LEN			(32)
#define EXCLOG_RECORD_MAGIK 			(0x20100812)
#define EXCLOG_STDOUT_MAGIK_STR		"0x20100823"
#define EXCLOG_FILE_PREFIX			"message"
#define EXCLOG_ERROR_LOG				"/tmp/libexcLOG_error_log"

extern char SERVER_IP[32];
extern char EXCLOG_PATH[EXCLOG_FILE_PATH_LEN];

extern int slist_num;
extern exclog_subscribe_req_t slist[EXCLOG_SUBSCRIBE_NUM_MAX];

extern exclog_query_info_t query_info;
/*******************************************************************************************/
/*Declaration:
 * 
 * data:log content.
 * 
 * message:<level>module(fname.line):data.\t--->IP\n
 * 
 * packet:time + message length + message
 * 
 * record example:
 *
 *  EXCLOG_2_FILE: 2010-08-28 15:30:00;<6>libexcLOG(exclog_query.c.100):log data.\t--->192.168.9.161\n
 * 
 * 	EXCLOG_2_FLASH:${magik}${time stamp}${len}${message}
 */
/*******************************************************************************************/
/**
 * Define packet for transmit on net
 */
typedef struct exclog_packet
{
	/**
	 * packet status
	 * 0-not in use
	 * 1-in use
	 **/
	int status;

	/**
	 *event happen timestamp 
	 */
	struct timeval tv;
	
	/**
	 *message length 
	 */
	int len;

	/**
	 *message which has been format according to data
	 */
	char message[EXCLOG_MSG_LEN_MAX];
	
	struct exclog_packet *next;
}exclog_packet_t;

/**
 * Define record head
 */
typedef struct exclog_head
{
	int magik;

	time_t time;

	int len;
} exclog_head_t;

/**
 * Define record
 */
typedef struct exclog_record
{
	exclog_head_t head;

	char message[EXCLOG_MSG_LEN_MAX];
	
}exclog_record_t;

/**********************************************************************************************
 * Structure:
 * 		struct exclog_query_remote_response;
 * Description:
 * 		use this struct to hold log query response info for each excLOG_query();
 *********************************************************************************************/
typedef struct exclog_query_remote_response
{
	/*indicate message level*/
	unsigned long level;

	/*indicate which module generate this message*/
	unsigned long module;

	/*human readable message of log*/
	char data[EXCLOG_LOG_LEN_MAX];

	/*indicate message timestamp*/
	exclog_datetime_t tick;
	
} exclog_query_remote_rps_t;

/*******************************************************************************************/
struct mtd_info_user {
	uint8_t type;
	uint32_t flags;
	uint32_t size;	 // Total size of the MTD
	uint32_t erasesize;
	uint32_t writesize;
	uint32_t oobsize;   // Amount of OOB data per block (e.g. 16)
	/* The below two fields are obsolete and broken, do not use them
	 * (TODO: remove at some point) */
	uint32_t ecctype;
	uint32_t eccsize;
};

struct region_info_user {
	uint32_t offset;		/* At which this region starts,
					 * from the beginning of the MTD */
	uint32_t erasesize;		/* For this region */
	uint32_t numblocks;		/* Number of blocks in this region */
	uint32_t regionindex;
};

struct erase_info_user {
	uint32_t start;
	uint32_t length;
};

#define MEMGETINFO					_IOR('M', 1, struct mtd_info_user)
#define MEMERASE					_IOW('M', 2, struct erase_info_user)
#define MEMGETREGIONCOUNT			_IOR('M', 7, int)
#define MEMGETREGIONINFO			_IOWR('M', 8, struct region_info_user)
#define MEMLOCK						_IOW('M', 5, struct erase_info_user)
#define MEMUNLOCK					_IOW('M', 6, struct erase_info_user)

/********************************************************************************************
 * Function: _exclog_public_get_ipaddr()
 *--------------------------------------------------------------------------------------------------------
 * Description:get local IP address.
 *--------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ ip :OUT,result returned by this function 
 *--------------------------------------------------------------------------------------------------------
 * Return:	
 *		 	 0: success;
 *			-1: system error.
 ********************************************************************************************/
int _exclog_public_get_ipaddr(char *ip);

/********************************************************************************************
 * Function: _exclog_add_ipaddr_2_pkt()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:add ip address to pkt->message to distinguish packet owner.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ ip:IN,ip address to add.
 *  @ pkt:add ip to whose message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
void _exclog_add_ipaddr_2_pkt(exclog_packet_t *pkt,char *ip);

/********************************************************************************************
 * Function: _exclog_check_last_message()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:check if current message to store equals to last message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ pkt:IN,check whose message.
 *  @ last_message:last message stored.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	
			0:not repeat
		  -1:repeat
 ********************************************************************************************/
int _exclog_check_last_message(exclog_packet_t *pkt,char *last_message);

/********************************************************************************************
 * Function: _exclog_get_last_level_module()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:get log level of last message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ last_message:IN,last message stored.
 *  @ last_level:OUT,level of last message.
 *  @ last_module:OUT,module of last message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	
 0:not repeat
 -1:repeat
 ********************************************************************************************/
int _exclog_get_last_level_module(char *last_message, char *level, char *module);

/********************************************************************************************
 * Function: _exclog_level_str_2_hex()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:transfer level string to hex.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ level:IN,log level string.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :log level in hex.
 ********************************************************************************************/
unsigned long _exclog_level_str_2_hex(char *level);

/********************************************************************************************
 * Function: _exclog_module_str_2_hex()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:transfer level string to hex.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ module:IN,log module string.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :log module in hex.
 ********************************************************************************************/
unsigned long _exclog_module_str_2_hex(char *module);

/********************************************************************************************
 * Function: EXCLOG_DEBUG_FUNCTION()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:debug function implement in libexcLOG.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ fmt:log format.
 *  @  ... :varying arguments.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :log module in hex.
 ********************************************************************************************/
void EXCLOG_DEBUG_FUNCTION(char *fmt,...);

char *XELOG_GET_DATE_TIME(void);


/*******************************************************************************************/
/*#define DEBUG_SELF(fmt, args...){\
			EXCLOG_DEBUG_FUNCTION("(%s.%d):"fmt"\n",__FILE__,__LINE__, ##args);\
		}*/

#define DEBUG_SELF(fmt, args...){\
			fprintf(stdout,"(%s.%d):"fmt"\n",__FILE__,__LINE__, ##args);\
		}

#ifdef CONFIG_CLOSE_DBG
	#define DBG_SELF(fmt, args...)
#else
	#define DBG_SELF(fmt, args...) DEBUG_SELF(fmt, ##args)
#endif

#endif /*__EXCLOG_PUBLIC_H_*/
