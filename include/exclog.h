/******************************************************************************************************************
 * 					Filename: exclog.h
 ******************************************************************************************************************
 * Description:
 * 		 equipment log interface.
 * Version:
 *	 	 V_1.6 Jul-16-2012
 * Copyright:
 * Author: 
 *******************************************************************************************************************/
#ifndef __EXCLOG_EXTERNAL_H_
#define __EXCLOG_EXTERNAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#ifdef __cplusplus
extern "C"
{
#endif

//#define NO_LOG				1
//#define EXCLOG_2_CONSOLE		1
//#define EXCLOG_2_SYSLOG		1
//#define EXCLOG_2_REMOTE		1
//#define EXCLOG_2_LOCAL			1

#ifdef NO_LOG
#define EXCLOG_MODE_DEFINED 1
#endif

#ifdef EXCLOG_2_CONSOLE
#define EXCLOG_MODE_DEFINED 1
#endif

#ifdef EXCLOG_2_SYSLOG
#define EXCLOG_MODE_DEFINED 1
#endif

#ifdef EXCLOG_2_REMOTE
#define EXCLOG_MODE_DEFINED 1
#endif

#ifdef EXCLOG_2_LOCAL
#define EXCLOG_MODE_DEFINED 1
#endif

#ifndef EXCLOG_MODE_DEFINED
#error ("EXCLOG_2_*** undefined.")
#endif

#ifndef EXCLOG_PREFIX
#define EXCLOG_PREFIX	"N/A"
#endif

/**
 * log level,0~7,large number,large messages
 * 		0 - excLOG_EMERG(fmt, args...)
 *		1 - excLOG_CRIT(fmt, args...)
 *		2 - excLOG_ALERT(fmt, args...)
 *		3 - excLOG_ERR(fmt, args...)
 *		4 - excLOG_WARNING(fmt, args...)
 *		5 - excLOG_NOTICE(fmt, args...)
 *		6 - excLOG_INFO(fmt, args...)
 *		7 - excLOG_DEBUG(fmt, args...)
 **/

/*log level xxx */
#define EXCLOG_LEVEL_EMERG 		0x00000001UL
#define EXCLOG_LEVEL_CRIT		0x00000002UL
#define EXCLOG_LEVEL_ALERT		0x00000004UL
#define EXCLOG_LEVEL_ERR			0x00000008UL
#define EXCLOG_LEVEL_WARNING		0x00000010UL
#define EXCLOG_LEVEL_NOTICE		0x00000020UL
#define EXCLOG_LEVEL_INFO		0x00000040UL
#define EXCLOG_LEVEL_DEBUG		0x00000080UL

/*log level from 0 to N */
#define EXCLOG_LEVEL_0			EXCLOG_LEVEL_EMERG
#define EXCLOG_LEVEL_1			(EXCLOG_LEVEL_0 | EXCLOG_LEVEL_CRIT)
#define EXCLOG_LEVEL_2			(EXCLOG_LEVEL_1 | EXCLOG_LEVEL_ALERT)
#define EXCLOG_LEVEL_3			(EXCLOG_LEVEL_2 | EXCLOG_LEVEL_ERR)
#define EXCLOG_LEVEL_4			(EXCLOG_LEVEL_3 | EXCLOG_LEVEL_WARNING)
#define EXCLOG_LEVEL_5			(EXCLOG_LEVEL_4 | EXCLOG_LEVEL_NOTICE)
#define EXCLOG_LEVEL_6			(EXCLOG_LEVEL_5 | EXCLOG_LEVEL_INFO)
#define EXCLOG_LEVEL_7			(EXCLOG_LEVEL_6 | EXCLOG_LEVEL_DEBUG)

extern int log_level;
/***********************************************************************************************/
/*log module xxx */
#define EXCLOG_MODULE_NONE			0x00000000UL

#define EXCLOG_MODULE_HXSDK			0x00000001UL
#define EXCLOG_MODULE_SYSLOG		0x00000002UL
#define EXCLOG_MODULE_KERNEL 		0x00000004UL

#define EXCLOG_MODULE_APP_HXWEB		0x00000008UL
#define EXCLOG_MODULE_APP_HXFPG		0x00000010UL
#define EXCLOG_MODULE_APP_SIPUA		0x00000020UL
#define EXCLOG_MODULE_APP_SAC51		0x00000040UL
#define EXCLOG_MODULE_APP_S2506A	0x00000080UL
#define EXCLOG_MODULE_APP_HSSER		0x00000100UL
#define EXCLOG_MODULE_APP_HSVTDU	0x00000200UL
#define EXCLOG_MODULE_APP_HXGUI		0x00000400UL
#define EXCLOG_MODULE_APP_OTHER		0x00000800UL
#define EXCLOG_MODULE_APP	\
				( EXCLOG_MODULE_APP_HXWEB \
						| EXCLOG_MODULE_APP_HXFPG \
						| EXCLOG_MODULE_APP_SIPUA \
						| EXCLOG_MODULE_APP_SAC51 \
						| EXCLOG_MODULE_APP_S2506A \
						| EXCLOG_MODULE_APP_HSSER \
						| EXCLOG_MODULE_APP_HSVTDU)

/*reserved 7 defines for APP and LIB*/

#define EXCLOG_MODULE_LIB_AA		0x00020000UL
#define EXCLOG_MODULE_LIB_PM		0x00040000UL
#define EXCLOG_MODULE_LIB_CEO		0x00080000UL
#define EXCLOG_MODULE_LIB_CVA		0x00100000UL
#define EXCLOG_MODULE_LIB_DEX		0x00200000UL
#define EXCLOG_MODULE_LIB_LOG		0x00400000UL
#define EXCLOG_MODULE_LIB_PTZ		0x00800000UL
#define EXCLOG_MODULE_LIB_SOE		0x01000000UL
#define EXCLOG_MODULE_LIB_SAP		0x02000000UL
#define EXCLOG_MODULE_LIB_SIS		0x04000000UL
#define EXCLOG_MODULE_LIB_WDG		0x08000000UL
#define EXCLOG_MODULE_LIB_AC51		0x10000000UL
#define EXCLOG_MODULE_LIB_IPCAM		0x20000000UL
#define EXCLOG_MODULE_LIB_DAVINCI	0x40000000UL
#define EXCLOG_MODULE_CORE_OTHER	0x80000000UL
#define EXCLOG_MODULE_CORE \
				( EXCLOG_MODULE_LIB_AA \
						| EXCLOG_MODULE_LIB_PM \
						| EXCLOG_MODULE_LIB_CEO \
						| EXCLOG_MODULE_LIB_CVA \
						| EXCLOG_MODULE_LIB_DEX \
						| EXCLOG_MODULE_LIB_LOG \
						| EXCLOG_MODULE_LIB_PTZ \
						| EXCLOG_MODULE_LIB_SOE \
						| EXCLOG_MODULE_LIB_SAP \
						| EXCLOG_MODULE_LIB_SIS \
						| EXCLOG_MODULE_LIB_WDG \
						| EXCLOG_MODULE_LIB_AC51 \
						| EXCLOG_MODULE_LIB_IPCAM \
						| EXCLOG_MODULE_LIB_DAVINCI \
						| EXCLOG_MODULE_CORE_OTHER )

#define EXCLOG_MODULE_USER \
				( EXCLOG_MODULE_HXSDK \
						| EXCLOG_MODULE_APP \
						| EXCLOG_MODULE_CORE )

#define EXCLOG_MODULE_ALL		(EXCLOG_MODULE_USER	| EXCLOG_MODULE_KERNEL | EXCLOG_MODULE_SYSLOG)

#define EXCLOG_FILE_PATH_LEN			(128)/*max length of log file path*/

/**********************************************************************************************
 * Structure:
 * 		struct init_exclog_local;
 * Description:
 * 		use this struct to describe initialize parameters used in EXCLOG_2_LOCAL mode;
 *********************************************************************************************/
typedef struct init_exclog_local
{
	/**
	 * enable or disable receive remote log
	 * 0-disable
	 * 514-enable
	 */
	int local_port;

	/**
	 * enable or disable receive system log
	 * 0-disable
	 * 1-enable
	 */
	int be_syslog;

	/**
	 *enable or disable receive kernel log
	 * 0-disable
	 * 1-enable
	 */
	int be_klog;

	/**
	 * store log whose level is less than log_level
	 */
	int log_level;

	/**
	 * absolute path of log file
	 */
	char path[EXCLOG_FILE_PATH_LEN];

	/**
	 * max log file num [1,30]
	 */
	int num;

	/**
	 * size of each log file,unit:bytes [16KB,10MB]
	 */
	int size;

	/**
	 * Apr-26-2011 added by wuhm<wuhm@hisome.com>
	 * set one of following member to '1' enable message
	 * output to stdout or stderr for ease debug;
	 */
	int msg2stdout,msg2stderr;
} init_exclog_local_t;

int init_exclog_local(const init_exclog_local_t *ix_p);
int deinit_exclog_local(void);

/**********************************************************************************************
 * Structure:
 * 		struct init_exclog_remote;
 * Description:
 * 		use this struct to describe initialize parameters used in EXCLOG_2_REMOTE mode;
 *********************************************************************************************/
typedef struct init_exclog_remote
{
	/**
	 * store log whose level is less than log_level
	 */
	int log_level;

	/**
	 * enable or disable receive system log
	 * 0-disable
	 * 1-enable
	 */
	int be_syslog;

	/**
	 * enable or disable receive kernel log
	 * 0-disable
	 * 1-enable
	 */
	int be_klog;

	/**
	 * IP address of remote receiver
	 */
	char remoteIP[32];

	/**
	 * port of remote receiver,must be 514
	 */
	int remotePort;

	/**
	 * Jun-07-2011 added by renhw<renhw@hisome.com>
	 * set one of following member to '1' enable message
	 * output to stdout or stderr for ease debug;
	 */
	int msg2stdout,msg2stderr;
} init_exclog_remote_t;

int init_exclog_network(const init_exclog_remote_t *ix_p);
int deinit_exclog_network(void);

/**********************************************************************************************
 * Structure:
 * 		struct exclog_datetime;
 * Description:
 * 		use this struct to describe start time and end time of query request;
 *********************************************************************************************/
typedef struct exclog_datetime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} exclog_datetime_t;
/**********************************************************************************************
 * Structure:
 * 		struct exclog_query_request;
 * Description:
 * 		use this struct to describe log query request parameters;
 *********************************************************************************************/
typedef struct exclog_query_request
{
	/**
	 * start time 
	 */
	exclog_datetime_t stime;

	/**
	 * end time 
	 */
	exclog_datetime_t etime;

	/**
	 * which level to query or which levels to query
	 * level: EXCLOG_LEVEL_xxx
	 * levels:EXCLOG_LEVEL_n,EXCLOG_LEVEL_xxx|EXCLOG_LEVEL_xxx
	 **/
	unsigned long level;

	/**
	 * which module to query or which modules to query
	 * module:	EXCLOG_MODULE_KERNEL,EXCLOG_MODULE_SYSLOG,
	 * 			EXCLOG_MODULE_HXSDK,	EXCLOG_MODULE_LIB_xxx,EXCLOG_MODULE_APP_xxx
	 * modules:	EXCLOG_MODULE_xxx | EXCLOG_MODULE_xxx,
	 * 			EXCLOG_MODULE_CORE,EXCLOG_MODULE_APP,EXCLOG_MODULE_USER,EXCLOG_MODULE_ALL
	 **/
	unsigned long module;
} exclog_query_req_t;

#define EXCLOG_LOG_LEN_MAX		(256)
/**********************************************************************************************
 * Structure:
 * 		struct exclog_query_response;
 * Description:
 * 		use this struct to hold log query response info for each excLOG_query();
 *********************************************************************************************/
typedef struct exclog_query_response
{
	/*indicate message level*/
	unsigned long level;

	/*indicate which module generate this message*/
	unsigned long module;

	/*human readable message of log*/
	char data[EXCLOG_LOG_LEN_MAX];

	/*indicate message timestamp*/
	exclog_datetime_t tick;

	/*next log message, NULL if last one*/
	struct exclog_query_response *next;
} exclog_query_rps_t;

/********************************************************************************************
 * Function: excLOG_query()
 *------------------------------------------------------------------------------------------
 * Description:start query.
 *------------------------------------------------------------------------------------------
 * Basic Work flow:
 * 			 excLOG_query()--->excLOG_read()----> read any more?----->excLOG_close()
 * 			   					^			  		|yes		no
 * 			   					|___________________|
 *
 *(1)log query must start with excLOG_query(),or else excLOG_read() will fail;
 *(2)log query must stop  with excLOG_close(),or else new excLOG_query() will return 'busy'
 *	 because only one query task can be run simultaneously;
 *(3)every excLOG_read() return 128 query results at most,user can use this API in while.
 *------------------------------------------------------------------------------------------
 * Parameters:
 * @ req:IN,query request.
 *------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 * 		 1:busy.
 ********************************************************************************************/
int excLOG_query(const exclog_query_req_t *req);

/********************************************************************************************
 * Function: excLOG_read()
  *------------------------------------------------------------------------------------------
 * Description:read query results.
 *------------------------------------------------------------------------------------------
 * Parameters:
 * @ rps:OUT,query results.
 *------------------------------------------------------------------------------------------
 * Return :
 * 	   >=0:total number of results read this time(<=128);
 * 		-1:fail.
 ********************************************************************************************/
int excLOG_read(exclog_query_rps_t **rps);

/********************************************************************************************
 * Function: excLOG_close()
  *------------------------------------------------------------------------------------------
 * Description:stop query task,free memory calloced for query results;
 *			   user must call this API when no more query results needed.
 *------------------------------------------------------------------------------------------
 * Parameters:NULL;
 *------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
void excLOG_close();

/**********************************************************************************************
 * Structure:
 * 		struct exclog_subscribe_response;
 * Description:
 * 		use this struct to hold log subscribe response info for exclog_event_subscribe();
 *********************************************************************************************/
typedef struct exclog_subscribe_response
{
	/*indicate message level*/
	int level;

	/*indicate which module generate this message*/
	char module[16];

	/*human readable message of log*/
	char message[EXCLOG_LOG_LEN_MAX];
} exclog_subscribe_rps_t;

/*********************************************************************************************
 * log subscribe callback
 *-------------------------------------------------------------------------------------
 * @erps: which subscribe fired.
 * 		->module: which module generate message;
 * 		->level:  which level fired;
 * 		->message:human readable message;
 *-------------------------------------------------------------------------------------
 *********************************************************************************************/
typedef int (*exclog_subscribe_f)(exclog_subscribe_rps_t *erps);

/**********************************************************************************************
 * Structure:
 * 		struct exclog_subscribe_request;
 * Description:
 * 		use this struct to descrive log subscribe request parameters;
 *********************************************************************************************/
typedef struct exclog_subscribe_request
{
	/**
	 * which module to subscribe or which modules to subscribe
	 * module:	EXCLOG_MODULE_KERNEL,EXCLOG_MODULE_SYSLOG,
	 * 			EXCLOG_MODULE_HXSDK,	EXCLOG_MODULE_LIB_xxx,EXCLOG_MODULE_APP_xxx
	 * modules:	EXCLOG_MODULE_xxx | EXCLOG_MODULE_xxx,
	 * 			EXCLOG_MODULE_CORE,EXCLOG_MODULE_APP,EXCLOG_MODULE_USER,EXCLOG_MODULE_ALL
	 **/
	unsigned long module;

	/**
	 * which level to subscribe or which levels to subscribe
	 *	level: EXCLOG_LEVEL_xxx
	 * 	levels:EXCLOG_LEVEL_n,EXCLOG_LEVEL_xxx|EXCLOG_LEVEL_xxx
	 **/
	unsigned long level;
	
	/**
	 * subscribe callback function 
	 */
	exclog_subscribe_f sub_f;
} exclog_subscribe_req_t;

int excLOG_subscribe(exclog_subscribe_req_t *ereq);

/***********************************************************************************************/
/**
 * API for get and set log_level
 **/
int excLOG_level_get(void);
int excLOG_level_set(int new_level);

/**
 * API for dynamic set msg2stdout
 * print message to stdout or not,1-yes,0-not
 */
int excLOG_msg2stdout_set(int new_value);

/********************************************************************************************
 * Function: excLOG_dump_backstrace()
  *------------------------------------------------------------------------------------------
 * Description:dump function stack information of current thread to standard error output,
 * 			   usually used in signal process function.
 *------------------------------------------------------------------------------------------
 * MUST use "LDFLAGS += -rdynamic" in your Makefile when compile,
 * so,use this function in DEBUG mode is recommended.
 *------------------------------------------------------------------------------------------
 * Parameters:
 * @ max_num:maximal num of stack information to be dumped,
 * 			 valid range is 1~512,default is 10.
 *------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
void excLOG_dump_backstrace(int max_num) __attribute__((noinline));

/***********************************************************************************************/
#ifdef NO_LOG
#define excLOG_EMERG(fmt, args...)
#define excLOG_CRIT(fmt, args...)
#define excLOG_ALERT(fmt, args...)
#define excLOG_ERR(fmt, args...)
#define excLOG_WARNING(fmt, args...)
#define excLOG_NOTICE(fmt, args...)
#define excLOG_INFO(fmt, args...)
#define excLOG_DEBUG(fmt, args...)
#endif/*NO_LOG*/

#if defined(EXCLOG_2_SYSLOG)

#define excLOG_EMERG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_EMERG)) { \
				syslog(LOG_EMERG, "(%s.%d.EMERG):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_CRIT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_CRIT)) { \
				syslog(LOG_CRIT, "(%s.%d.CRIT):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_ALERT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ALERT)) { \
				syslog(LOG_ALERT, "(%s.%d.ALERT):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_ERR(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ERR)) { \
				syslog(LOG_ERR, "(%s.%d.ERR):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_WARNING(fmt, args...) \
		do{	\
			if(log_level>=(LOG_WARNING)) { \
				syslog(LOG_WARNING, "(%s.%d.WARNING):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_NOTICE(fmt, args...) \
		do{	\
			if(log_level>=(LOG_NOTICE)) { \
				syslog(LOG_NOTICE, "(%s.%d.NOTICE):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_INFO(fmt, args...) \
		do{	\
			if(log_level>=(LOG_INFO)) { \
				syslog(LOG_INFO, "(%s.%d.INFO):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define excLOG_DEBUG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_DEBUG)) { \
				syslog(LOG_DEBUG, "(%s.%d.DBG):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);
#endif/*EXCLOG_2_SYSLOG*/

#if defined(EXCLOG_2_CONSOLE)

#define BLACK     "\033[0;30m"
#define RED       "\033[0;31m"
#define LIGNT_RED "\033[1;31m"
#define GREEN     "\033[0;32m"
#define YELLOW    "\033[0;33m"
#define BLUE 	  "\033[0;34m"
#define MAGENTA   "\033[0;35m"
#define CYAN   	  "\033[0;36m"
#define WHITE 	  "\033[0;38m"
#define END		  "\033[0m"

#define COLOR_DEBUG		WHITE
#define COLOR_INFO		CYAN
#define COLOR_NOTICE	BLUE
#define COLOR_WARNING	GREEN
#define COLOR_ERR		RED
#define COLOR_ALERT		YELLOW
#define COLOR_CRIT		MAGENTA
#define COLOR_EMERG		LIGNT_RED
#define COLOR_END		END

char *EXCLOG_GET_DATE_TIME(void);

#define excLOG_EMERG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_EMERG)) { \
				fprintf(stderr, COLOR_EMERG"[%s]"EXCLOG_PREFIX"(%s.%d.EMERG):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_CRIT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_CRIT)) { \
				fprintf(stderr, COLOR_CRIT"[%s]"EXCLOG_PREFIX"(%s.%d.CRIT):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_ALERT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ALERT)) { \
				fprintf(stderr, COLOR_ALERT"[%s]"EXCLOG_PREFIX"(%s.%d.ALERT):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_ERR(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ERR)) { \
				fprintf(stderr, COLOR_ERR"[%s]"EXCLOG_PREFIX"(%s.%d.ERR):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_WARNING(fmt, args...) \
		do{	\
			if(log_level>=(LOG_WARNING)) { \
				fprintf(stderr, COLOR_WARNING"[%s]"EXCLOG_PREFIX"(%s.%d.WARNING):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_NOTICE(fmt, args...) \
		do{	\
			if(log_level>=(LOG_NOTICE)) { \
				fprintf(stderr, COLOR_NOTICE"[%s]"EXCLOG_PREFIX"(%s.%d.NOTICE):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_INFO(fmt, args...) \
		do{	\
			if(log_level>=(LOG_INFO)) { \
				fprintf(stdout, COLOR_INFO"[%s]"EXCLOG_PREFIX"(%s.%d.INFO):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

#define excLOG_DEBUG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_DEBUG)) { \
				fprintf(stdout, COLOR_DEBUG"[%s]"EXCLOG_PREFIX"(%s.%d.DBG):"fmt"\n"COLOR_END,EXCLOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);
#endif/*EXCLOG_2_CONSOLE*/

#if defined(EXCLOG_2_REMOTE)

int excLOG_PUSH(char *sbuf, int slen);

#define excLOG_COMMOM(lvl,fmt,args...) \
		do{	\
			char sbuf[EXCLOG_LOG_LEN_MAX]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,"<%d>"EXCLOG_PREFIX"(%s.%d):"fmt"\n",\
					lvl, __FILE__,__LINE__, ##args); \
			if(slen>=EXCLOG_LOG_LEN_MAX-1){\
				sbuf[EXCLOG_LOG_LEN_MAX-3]='\n';sbuf[EXCLOG_LOG_LEN_MAX-2]='\0';slen=EXCLOG_LOG_LEN_MAX-1;}\
			excLOG_PUSH(sbuf,slen); \
		}while(0);

#define excLOG_EMERG(fmt, args...) \
		do{ \
			if(log_level>=(LOG_EMERG) ) { \
				excLOG_COMMOM(LOG_EMERG,fmt, ##args); \
			} \
		}while(0);

#define excLOG_CRIT(fmt, args...) \
		do{ \
			if(log_level>=(LOG_CRIT) ) { \
				excLOG_COMMOM(LOG_CRIT,fmt, ##args); \
			} \
		}while(0);

#define excLOG_ALERT(fmt, args...) \
		do{ \
			if(log_level>=(LOG_ALERT) ) { \
				excLOG_COMMOM(LOG_ALERT,fmt, ##args); \
			} \
		}while(0);

#define excLOG_ERR(fmt, args...) \
		do{ \
			if(log_level>=(LOG_ERR) ) { \
				excLOG_COMMOM(LOG_ERR,fmt, ##args); \
			} \
		}while(0);

#define excLOG_WARNING(fmt, args...) \
		do{ \
			if(log_level>=(LOG_WARNING) ) { \
				excLOG_COMMOM(LOG_WARNING,fmt, ##args); \
			} \
		}while(0);

#define excLOG_NOTICE(fmt, args...) \
		do{ \
			if(log_level>=(LOG_NOTICE) ) { \
				excLOG_COMMOM(LOG_NOTICE,fmt, ##args); \
			} \
		}while(0);

#define excLOG_INFO(fmt, args...) \
		do{ \
			if(log_level>=(LOG_INFO) ) { \
				excLOG_COMMOM(LOG_INFO,fmt, ##args); \
			} \
		}while(0);

#define excLOG_DEBUG(fmt, args...) \
		do{ \
			if(log_level>=(LOG_DEBUG) ) { \
				excLOG_COMMOM(LOG_DEBUG,fmt, ##args); \
			} \
		}while(0);
#endif/*EXCLOG_2_REMOTE*/

#if defined(EXCLOG_2_LOCAL)

int excLOG_local(char *sbuf, int slen);

#define excLOG_COMMOM(lvl,fmt,args...) \
		do{	\
			char sbuf[EXCLOG_LOG_LEN_MAX]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,"<%d>"EXCLOG_PREFIX"(%s.%d):"fmt"\n", \
					lvl,__FILE__,__LINE__, ##args); \
			if(slen>=EXCLOG_LOG_LEN_MAX-1){\
				sbuf[EXCLOG_LOG_LEN_MAX-3]='\n';sbuf[EXCLOG_LOG_LEN_MAX-2]='\0';slen=EXCLOG_LOG_LEN_MAX-1;}\
			excLOG_local(sbuf,slen); \
		}while(0);

#define excLOG_EMERG(fmt, args...) \
		do { \
			if(log_level>=(LOG_EMERG) ) { \
				excLOG_COMMOM(LOG_EMERG,fmt, ##args); \
			} \
		}while(0);

#define excLOG_CRIT(fmt, args...) \
		do { \
			if(log_level>=(LOG_CRIT) ) { \
				excLOG_COMMOM(LOG_CRIT,fmt, ##args); \
			} \
		}while(0);

#define excLOG_ALERT(fmt, args...) \
		do { \
			if(log_level>=(LOG_ALERT) ) { \
				excLOG_COMMOM(LOG_ALERT,fmt, ##args); \
			} \
		}while(0);

#define excLOG_ERR(fmt, args...) \
		do { \
			if(log_level>=(LOG_ERR) ) { \
				excLOG_COMMOM(LOG_ERR,fmt, ##args); \
			} \
		}while(0);

#define excLOG_WARNING(fmt, args...) \
		do { \
			if(log_level>=(LOG_WARNING) ) { \
				excLOG_COMMOM(LOG_WARNING,fmt, ##args); \
			} \
		}while(0);

#define excLOG_NOTICE(fmt, args...) \
		do { \
			if(log_level>=(LOG_NOTICE) ) { \
				excLOG_COMMOM(LOG_NOTICE,fmt, ##args); \
			} \
		}while(0);

#define excLOG_INFO(fmt, args...) \
		do { \
			if(log_level>=(LOG_INFO) ) { \
				excLOG_COMMOM(LOG_INFO,fmt, ##args); \
			} \
		}while(0);

#define excLOG_DEBUG(fmt, args...) \
		do { \
			if(log_level>=(LOG_DEBUG) ) { \
				excLOG_COMMOM(LOG_DEBUG,fmt, ##args); \
			} \
		}while(0);
#endif/*EXCLOG_2_LOCAL*/

#define eprintf(fmt, args...) \
		do{ \
			excLOG_ERR(fmt, ##args);\
		}while(0);

#define dprintf(fmt, args...) \
		do{ \
			excLOG_DEBUG(fmt, ##args);\
		}while(0);

#ifdef NDEBUG
#define DBG(fmt, args...)
#else
#define DBG(fmt, args...)\
		do{	\
			excLOG_DEBUG(fmt, ##args);\
		}while(0);
#endif

#ifndef BUG
#define BUG() \
		do{	\
			excLOG_ALERT("BUG: PC@here");\
			excLOG_dump_backstrace(10);\
		}while(0);
#endif/*BUG*/

#ifndef BUGMSG
#define BUGMSG(fmt,args...) \
		do{	\
			excLOG_ALERT("BUG: "fmt,##args);\
			excLOG_dump_backstrace(10);\
		}while(0);
#endif/*BUGMSG*/

/***********************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /*EXCLOG_H_*/
