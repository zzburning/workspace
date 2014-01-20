/******************************************************************************************************************
 * 					Filename: xelog.h
 ******************************************************************************************************************
 * Description:
 * 		 equipment log interface.
 * Version:
 *	 	 V_1.6 Jul-16-2012
 * Copyright:
 * 		 HISOME <http://www.hisome.com>
 * Author: 
 * 		 renhw <renhw@hisome.com.>
 *******************************************************************************************************************/
#ifndef __XELOG_EXTERNAL_H_
#define __XELOG_EXTERNAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#ifdef __cplusplus
extern "C"
{
#endif

//#define NO_LOG				1
//#define XELOG_2_CONSOLE		1
//#define XELOG_2_SYSLOG		1
//#define XELOG_2_REMOTE		1
//#define XELOG_2_LOCAL			1

#ifdef NO_LOG
#define XELOG_MODE_DEFINED 1
#endif

#ifdef XELOG_2_CONSOLE
#define XELOG_MODE_DEFINED 1
#endif

#ifdef XELOG_2_SYSLOG
#define XELOG_MODE_DEFINED 1
#endif

#ifdef XELOG_2_REMOTE
#define XELOG_MODE_DEFINED 1
#endif

#ifdef XELOG_2_LOCAL
#define XELOG_MODE_DEFINED 1
#endif

#ifndef XELOG_MODE_DEFINED
#error ("XELOG_2_*** undefined.")
#endif

#ifndef XELOG_PREFIX
#define XELOG_PREFIX	"N/A"
#endif

/**
 * log level,0~7,large number,large messages
 * 		0 - xeLOG_EMERG(fmt, args...)
 *		1 - xeLOG_CRIT(fmt, args...)
 *		2 - xeLOG_ALERT(fmt, args...)
 *		3 - xeLOG_ERR(fmt, args...)
 *		4 - xeLOG_WARNING(fmt, args...)
 *		5 - xeLOG_NOTICE(fmt, args...)
 *		6 - xeLOG_INFO(fmt, args...)
 *		7 - xeLOG_DEBUG(fmt, args...)
 **/

/*log level xxx */
#define XELOG_LEVEL_EMERG 		0x00000001UL
#define XELOG_LEVEL_CRIT		0x00000002UL
#define XELOG_LEVEL_ALERT		0x00000004UL
#define XELOG_LEVEL_ERR			0x00000008UL
#define XELOG_LEVEL_WARNING		0x00000010UL
#define XELOG_LEVEL_NOTICE		0x00000020UL
#define XELOG_LEVEL_INFO		0x00000040UL
#define XELOG_LEVEL_DEBUG		0x00000080UL

/*log level from 0 to N */
#define XELOG_LEVEL_0			XELOG_LEVEL_EMERG
#define XELOG_LEVEL_1			(XELOG_LEVEL_0 | XELOG_LEVEL_CRIT)
#define XELOG_LEVEL_2			(XELOG_LEVEL_1 | XELOG_LEVEL_ALERT)
#define XELOG_LEVEL_3			(XELOG_LEVEL_2 | XELOG_LEVEL_ERR)
#define XELOG_LEVEL_4			(XELOG_LEVEL_3 | XELOG_LEVEL_WARNING)
#define XELOG_LEVEL_5			(XELOG_LEVEL_4 | XELOG_LEVEL_NOTICE)
#define XELOG_LEVEL_6			(XELOG_LEVEL_5 | XELOG_LEVEL_INFO)
#define XELOG_LEVEL_7			(XELOG_LEVEL_6 | XELOG_LEVEL_DEBUG)

extern int log_level;
/***********************************************************************************************/
/*log module xxx */
#define XELOG_MODULE_NONE			0x00000000UL

#define XELOG_MODULE_HXSDK			0x00000001UL
#define XELOG_MODULE_SYSLOG			0x00000002UL
#define XELOG_MODULE_KERNEL 		0x00000004UL

#define XELOG_MODULE_APP_HXWEB		0x00000008UL
#define XELOG_MODULE_APP_HXFPG		0x00000010UL
#define XELOG_MODULE_APP_SIPUA		0x00000020UL
#define XELOG_MODULE_APP_SAC51		0x00000040UL
#define XELOG_MODULE_APP_S2506A		0x00000080UL
#define XELOG_MODULE_APP_HSSER		0x00000100UL
#define XELOG_MODULE_APP_HSVTDU		0x00000200UL
#define XELOG_MODULE_APP	\
				( XELOG_MODULE_APP_HXWEB \
						| XELOG_MODULE_APP_HXFPG \
						| XELOG_MODULE_APP_SIPUA \
						| XELOG_MODULE_APP_SAC51 \
						| XELOG_MODULE_APP_S2506A \
						| XELOG_MODULE_APP_HSSER \
						| XELOG_MODULE_APP_HSVTDU)

/*reserved 7 defines for APP and LIB*/

#define XELOG_MODULE_LIB_AA			0x00020000UL
#define XELOG_MODULE_LIB_PM			0x00040000UL
#define XELOG_MODULE_LIB_CEO		0x00080000UL
#define XELOG_MODULE_LIB_CVA		0x00100000UL
#define XELOG_MODULE_LIB_DEX		0x00200000UL
#define XELOG_MODULE_LIB_LOG		0x00400000UL
#define XELOG_MODULE_LIB_PTZ		0x00800000UL
#define XELOG_MODULE_LIB_SOE		0x01000000UL
#define XELOG_MODULE_LIB_SAP		0x02000000UL
#define XELOG_MODULE_LIB_SIS		0x04000000UL
#define XELOG_MODULE_LIB_WDG		0x08000000UL
#define XELOG_MODULE_LIB_AC51		0x10000000UL
#define XELOG_MODULE_LIB_IPCAM		0x20000000UL
#define XELOG_MODULE_LIB_DAVINCI	0x40000000UL
#define XELOG_MODULE_CORE_OTHER		0x80000000UL
#define XELOG_MODULE_CORE \
				( XELOG_MODULE_LIB_AA \
						| XELOG_MODULE_LIB_PM \
						| XELOG_MODULE_LIB_CEO \
						| XELOG_MODULE_LIB_CVA \
						| XELOG_MODULE_LIB_DEX \
						| XELOG_MODULE_LIB_LOG \
						| XELOG_MODULE_LIB_PTZ \
						| XELOG_MODULE_LIB_SOE \
						| XELOG_MODULE_LIB_SAP \
						| XELOG_MODULE_LIB_SIS \
						| XELOG_MODULE_LIB_WDG \
						| XELOG_MODULE_LIB_AC51 \
						| XELOG_MODULE_LIB_IPCAM \
						| XELOG_MODULE_LIB_DAVINCI \
						| XELOG_MODULE_CORE_OTHER )

#define XELOG_MODULE_USER \
				( XELOG_MODULE_HXSDK \
						| XELOG_MODULE_APP \
						| XELOG_MODULE_CORE )

#define XELOG_MODULE_ALL		(XELOG_MODULE_USER	| XELOG_MODULE_KERNEL | XELOG_MODULE_SYSLOG)

#define XELOG_FILE_PATH_LEN			(128)/*max length of log file path*/

/**********************************************************************************************
 * Structure:
 * 		struct init_xelog_local;
 * Description:
 * 		use this struct to describe initialize parameters used in XELOG_2_LOCAL mode;
 *********************************************************************************************/
typedef struct init_xelog_local
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
	char path[XELOG_FILE_PATH_LEN];

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
} init_xelog_local_t;

int init_xelog_local(const init_xelog_local_t *ix_p);
int deinit_xelog_local(void);

/**********************************************************************************************
 * Structure:
 * 		struct init_xelog_remote;
 * Description:
 * 		use this struct to describe initialize parameters used in XELOG_2_REMOTE mode;
 *********************************************************************************************/
typedef struct init_xelog_remote
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
} init_xelog_remote_t;

int init_xelog_network(const init_xelog_remote_t *ix_p);
int deinit_xelog_network(void);

/**********************************************************************************************
 * Structure:
 * 		struct xelog_datetime;
 * Description:
 * 		use this struct to describe start time and end time of query request;
 *********************************************************************************************/
typedef struct xelog_datetime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} xelog_datetime_t;
/**********************************************************************************************
 * Structure:
 * 		struct xelog_query_request;
 * Description:
 * 		use this struct to describe log query request parameters;
 *********************************************************************************************/
typedef struct xelog_query_request
{
	/**
	 * start time 
	 */
	xelog_datetime_t stime;

	/**
	 * end time 
	 */
	xelog_datetime_t etime;

	/**
	 * which level to query or which levels to query
	 * level: XELOG_LEVEL_xxx
	 * levels:XELOG_LEVEL_n,XELOG_LEVEL_xxx|XELOG_LEVEL_xxx
	 **/
	unsigned long level;

	/**
	 * which module to query or which modules to query
	 * module:	XELOG_MODULE_KERNEL,XELOG_MODULE_SYSLOG,
	 * 			XELOG_MODULE_HXSDK,	XELOG_MODULE_LIB_xxx,XELOG_MODULE_APP_xxx
	 * modules:	XELOG_MODULE_xxx | XELOG_MODULE_xxx,
	 * 			XELOG_MODULE_CORE,XELOG_MODULE_APP,XELOG_MODULE_USER,XELOG_MODULE_ALL
	 **/
	unsigned long module;
} xelog_query_req_t;

#define XELOG_LOG_LEN_MAX		(256)
/**********************************************************************************************
 * Structure:
 * 		struct xelog_query_response;
 * Description:
 * 		use this struct to hold log query response info for each xeLOG_query();
 *********************************************************************************************/
typedef struct xelog_query_response
{
	/*indicate message level*/
	unsigned long level;

	/*indicate which module generate this message*/
	unsigned long module;

	/*human readable message of log*/
	char data[XELOG_LOG_LEN_MAX];

	/*indicate message timestamp*/
	xelog_datetime_t tick;

	/*next log message, NULL if last one*/
	struct xelog_query_response *next;
} xelog_query_rps_t;

/********************************************************************************************
 * Function: xeLOG_query()
 *------------------------------------------------------------------------------------------
 * Description:start query.
 *------------------------------------------------------------------------------------------
 * Basic Work flow:
 * 			 xeLOG_query()--->xeLOG_read()----> read any more?----->xeLOG_close()
 * 			   					^			  		|yes		no
 * 			   					|___________________|
 *
 *(1)log query must start with xeLOG_query(),or else xeLOG_read() will fail;
 *(2)log query must stop  with xeLOG_close(),or else new xeLOG_query() will return 'busy'
 *	 because only one query task can be run simultaneously;
 *(3)every xeLOG_read() return 128 query results at most,user can use this API in while.
 *------------------------------------------------------------------------------------------
 * Parameters:
 * @ req:IN,query request.
 *------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 * 		 1:busy.
 ********************************************************************************************/
int xeLOG_query(const xelog_query_req_t *req);

/********************************************************************************************
 * Function: xeLOG_read()
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
int xeLOG_read(xelog_query_rps_t **rps);

/********************************************************************************************
 * Function: xeLOG_close()
  *------------------------------------------------------------------------------------------
 * Description:stop query task,free memory calloced for query results;
 *			   user must call this API when no more query results needed.
 *------------------------------------------------------------------------------------------
 * Parameters:NULL;
 *------------------------------------------------------------------------------------------
 * Return :NULL.
 ********************************************************************************************/
void xeLOG_close();

/**********************************************************************************************
 * Structure:
 * 		struct xelog_subscribe_response;
 * Description:
 * 		use this struct to hold log subscribe response info for xelog_event_subscribe();
 *********************************************************************************************/
typedef struct xelog_subscribe_response
{
	/*indicate message level*/
	int level;

	/*indicate which module generate this message*/
	char module[16];

	/*human readable message of log*/
	char message[XELOG_LOG_LEN_MAX];
} xelog_subscribe_rps_t;

/*********************************************************************************************
 * log subscribe callback
 *-------------------------------------------------------------------------------------
 * @erps: which subscribe fired.
 * 		->module: which module generate message;
 * 		->level:  which level fired;
 * 		->message:human readable message;
 *-------------------------------------------------------------------------------------
 *********************************************************************************************/
typedef int (*xelog_subscribe_f)(xelog_subscribe_rps_t *erps);

/**********************************************************************************************
 * Structure:
 * 		struct xelog_subscribe_request;
 * Description:
 * 		use this struct to descrive log subscribe request parameters;
 *********************************************************************************************/
typedef struct xelog_subscribe_request
{
	/**
	 * which module to subscribe or which modules to subscribe
	 * module:	XELOG_MODULE_KERNEL,XELOG_MODULE_SYSLOG,
	 * 			XELOG_MODULE_HXSDK,	XELOG_MODULE_LIB_xxx,XELOG_MODULE_APP_xxx
	 * modules:	XELOG_MODULE_xxx | XELOG_MODULE_xxx,
	 * 			XELOG_MODULE_CORE,XELOG_MODULE_APP,XELOG_MODULE_USER,XELOG_MODULE_ALL
	 **/
	unsigned long module;

	/**
	 * which level to subscribe or which levels to subscribe
	 *	level: XELOG_LEVEL_xxx
	 * 	levels:XELOG_LEVEL_n,XELOG_LEVEL_xxx|XELOG_LEVEL_xxx
	 **/
	unsigned long level;
	
	/**
	 * subscribe callback function 
	 */
	xelog_subscribe_f sub_f;
} xelog_subscribe_req_t;

int xeLOG_subscribe(xelog_subscribe_req_t *ereq);

/***********************************************************************************************/
/**
 * API for get and set log_level
 **/
int xeLOG_level_get(void);
int xeLOG_level_set(int new_level);

/**
 * API for dynamic set msg2stdout
 * print message to stdout or not,1-yes,0-not
 */
int xeLOG_msg2stdout_set(int new_value);

/********************************************************************************************
 * Function: xeLOG_dump_backstrace()
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
void xeLOG_dump_backstrace(int max_num) __attribute__((noinline));

/***********************************************************************************************/
#ifdef NO_LOG
#define xeLOG_EMERG(fmt, args...)
#define xeLOG_CRIT(fmt, args...)
#define xeLOG_ALERT(fmt, args...)
#define xeLOG_ERR(fmt, args...)
#define xeLOG_WARNING(fmt, args...)
#define xeLOG_NOTICE(fmt, args...)
#define xeLOG_INFO(fmt, args...)
#define xeLOG_DEBUG(fmt, args...)
#endif/*NO_LOG*/

#if defined(XELOG_2_SYSLOG)

#define xeLOG_EMERG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_EMERG)) { \
				syslog(LOG_EMERG, "(%s.%d.EMERG):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_CRIT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_CRIT)) { \
				syslog(LOG_CRIT, "(%s.%d.CRIT):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_ALERT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ALERT)) { \
				syslog(LOG_ALERT, "(%s.%d.ALERT):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_ERR(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ERR)) { \
				syslog(LOG_ERR, "(%s.%d.ERR):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_WARNING(fmt, args...) \
		do{	\
			if(log_level>=(LOG_WARNING)) { \
				syslog(LOG_WARNING, "(%s.%d.WARNING):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_NOTICE(fmt, args...) \
		do{	\
			if(log_level>=(LOG_NOTICE)) { \
				syslog(LOG_NOTICE, "(%s.%d.NOTICE):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_INFO(fmt, args...) \
		do{	\
			if(log_level>=(LOG_INFO)) { \
				syslog(LOG_INFO, "(%s.%d.INFO):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);

#define xeLOG_DEBUG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_DEBUG)) { \
				syslog(LOG_DEBUG, "(%s.%d.DBG):"fmt,__FILE__,__LINE__, ##args); \
			} \
		}while(0);
#endif/*XELOG_2_SYSLOG*/

#if defined(XELOG_2_CONSOLE)

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

char *XELOG_GET_DATE_TIME(void);

#define xeLOG_EMERG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_EMERG)) { \
				fprintf(stderr, COLOR_EMERG"[%s]"XELOG_PREFIX"(%s.%d.EMERG):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_CRIT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_CRIT)) { \
				fprintf(stderr, COLOR_CRIT"[%s]"XELOG_PREFIX"(%s.%d.CRIT):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_ALERT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ALERT)) { \
				fprintf(stderr, COLOR_ALERT"[%s]"XELOG_PREFIX"(%s.%d.ALERT):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_ERR(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ERR)) { \
				fprintf(stderr, COLOR_ERR"[%s]"XELOG_PREFIX"(%s.%d.ERR):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_WARNING(fmt, args...) \
		do{	\
			if(log_level>=(LOG_WARNING)) { \
				fprintf(stderr, COLOR_WARNING"[%s]"XELOG_PREFIX"(%s.%d.WARNING):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_NOTICE(fmt, args...) \
		do{	\
			if(log_level>=(LOG_NOTICE)) { \
				fprintf(stderr, COLOR_NOTICE"[%s]"XELOG_PREFIX"(%s.%d.NOTICE):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_INFO(fmt, args...) \
		do{	\
			if(log_level>=(LOG_INFO)) { \
				fprintf(stdout, COLOR_INFO"[%s]"XELOG_PREFIX"(%s.%d.INFO):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

#define xeLOG_DEBUG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_DEBUG)) { \
				fprintf(stdout, COLOR_DEBUG"[%s]"XELOG_PREFIX"(%s.%d.DBG):"fmt"\n"COLOR_END,XELOG_GET_DATE_TIME(),__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);
#endif/*XELOG_2_CONSOLE*/

#if defined(XELOG_2_REMOTE)

int xeLOG_PUSH(char *sbuf, int slen);

#define xeLOG_COMMOM(lvl,fmt,args...) \
		do{	\
			char sbuf[XELOG_LOG_LEN_MAX]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,"<%d>"XELOG_PREFIX"(%s.%d):"fmt"\n",\
					lvl, __FILE__,__LINE__, ##args); \
			if(slen>=XELOG_LOG_LEN_MAX-1){\
				sbuf[XELOG_LOG_LEN_MAX-3]='\n';sbuf[XELOG_LOG_LEN_MAX-2]='\0';slen=XELOG_LOG_LEN_MAX-1;}\
			xeLOG_PUSH(sbuf,slen); \
		}while(0);

#define xeLOG_EMERG(fmt, args...) \
		do{ \
			if(log_level>=(LOG_EMERG) ) { \
				xeLOG_COMMOM(LOG_EMERG,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_CRIT(fmt, args...) \
		do{ \
			if(log_level>=(LOG_CRIT) ) { \
				xeLOG_COMMOM(LOG_CRIT,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_ALERT(fmt, args...) \
		do{ \
			if(log_level>=(LOG_ALERT) ) { \
				xeLOG_COMMOM(LOG_ALERT,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_ERR(fmt, args...) \
		do{ \
			if(log_level>=(LOG_ERR) ) { \
				xeLOG_COMMOM(LOG_ERR,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_WARNING(fmt, args...) \
		do{ \
			if(log_level>=(LOG_WARNING) ) { \
				xeLOG_COMMOM(LOG_WARNING,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_NOTICE(fmt, args...) \
		do{ \
			if(log_level>=(LOG_NOTICE) ) { \
				xeLOG_COMMOM(LOG_NOTICE,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_INFO(fmt, args...) \
		do{ \
			if(log_level>=(LOG_INFO) ) { \
				xeLOG_COMMOM(LOG_INFO,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_DEBUG(fmt, args...) \
		do{ \
			if(log_level>=(LOG_DEBUG) ) { \
				xeLOG_COMMOM(LOG_DEBUG,fmt, ##args); \
			} \
		}while(0);
#endif/*XELOG_2_REMOTE*/

#if defined(XELOG_2_LOCAL)

int xeLOG_local(char *sbuf, int slen);

#define xeLOG_COMMOM(lvl,fmt,args...) \
		do{	\
			char sbuf[XELOG_LOG_LEN_MAX]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,"<%d>"XELOG_PREFIX"(%s.%d):"fmt"\n", \
					lvl,__FILE__,__LINE__, ##args); \
			if(slen>=XELOG_LOG_LEN_MAX-1){\
				sbuf[XELOG_LOG_LEN_MAX-3]='\n';sbuf[XELOG_LOG_LEN_MAX-2]='\0';slen=XELOG_LOG_LEN_MAX-1;}\
			xeLOG_local(sbuf,slen); \
		}while(0);

#define xeLOG_EMERG(fmt, args...) \
		do { \
			if(log_level>=(LOG_EMERG) ) { \
				xeLOG_COMMOM(LOG_EMERG,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_CRIT(fmt, args...) \
		do { \
			if(log_level>=(LOG_CRIT) ) { \
				xeLOG_COMMOM(LOG_CRIT,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_ALERT(fmt, args...) \
		do { \
			if(log_level>=(LOG_ALERT) ) { \
				xeLOG_COMMOM(LOG_ALERT,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_ERR(fmt, args...) \
		do { \
			if(log_level>=(LOG_ERR) ) { \
				xeLOG_COMMOM(LOG_ERR,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_WARNING(fmt, args...) \
		do { \
			if(log_level>=(LOG_WARNING) ) { \
				xeLOG_COMMOM(LOG_WARNING,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_NOTICE(fmt, args...) \
		do { \
			if(log_level>=(LOG_NOTICE) ) { \
				xeLOG_COMMOM(LOG_NOTICE,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_INFO(fmt, args...) \
		do { \
			if(log_level>=(LOG_INFO) ) { \
				xeLOG_COMMOM(LOG_INFO,fmt, ##args); \
			} \
		}while(0);

#define xeLOG_DEBUG(fmt, args...) \
		do { \
			if(log_level>=(LOG_DEBUG) ) { \
				xeLOG_COMMOM(LOG_DEBUG,fmt, ##args); \
			} \
		}while(0);
#endif/*XELOG_2_LOCAL*/

#define eprintf(fmt, args...) \
		do{ \
			xeLOG_ERR(fmt, ##args);\
		}while(0);

#define dprintf(fmt, args...) \
		do{ \
			xeLOG_DEBUG(fmt, ##args);\
		}while(0);

#ifdef NDEBUG
#define DBG(fmt, args...)
#else
#define DBG(fmt, args...)\
		do{	\
			xeLOG_DEBUG(fmt, ##args);\
		}while(0);
#endif

#ifndef BUG
#define BUG() \
		do{	\
			xeLOG_ALERT("BUG: PC@here");\
			xeLOG_dump_backstrace(10);\
		}while(0);
#endif/*BUG*/

#ifndef BUGMSG
#define BUGMSG(fmt,args...) \
		do{	\
			xeLOG_ALERT("BUG: "fmt,##args);\
			xeLOG_dump_backstrace(10);\
		}while(0);
#endif/*BUGMSG*/

/***********************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /*XELOG_H_*/
