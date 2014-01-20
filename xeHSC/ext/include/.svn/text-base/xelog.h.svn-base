/******************************************************************************************************************
 * 					Filename: xelog.h
 ******************************************************************************************************************
 * Description:
 * 		 equipment log interface.
 * Version:
 *	 	 V_1.0 Jul-12-2011
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
//#define XELOG_2_CONSOLE	1
//#define XELOG_2_SYSLOG		1
//#define XELOG_2_REMOTE		1
//#define XELOG_2_LOCAL		1

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

#define XELOG_MODULE_KERNEL_DM642	0x00000001UL
#define XELOG_MODULE_KERNEL_OS		0x00000002UL	//equals to HX_LOG_MODULE_KERNEL_OTHER
#define XELOG_MODULE_KERNEL 		(XELOG_MODULE_KERNEL_DM642|XELOG_MODULE_KERNEL_OS)

#define XELOG_MODULE_LIB_CEO		0x00000010UL
#define XELOG_MODULE_LIB_AA			0x00000020UL
#define XELOG_MODULE_LIB_SOE		0x00000040UL
#define XELOG_MODULE_LIB_SAP		0x00000080UL
#define XELOG_MODULE_LIB_SUCK		0x00000100UL
#define XELOG_MODULE_LIB_PTZ		0x00000200UL
#define XELOG_MODULE_LIB_LOG		0x00000400UL
#define XELOG_MODULE_LIB_PM			0x00000800UL
#define XELOG_MODULE_LIB_SIS		0x00001000UL
#define XELOG_MODULE_LIB_DAVINCI	0x00002000UL
#define XELOG_MODULE_LIB_CONF		0x00004000UL
#define XELOG_MODULE_LIB_IPCAM		0x00008000UL
#define XELOG_MODULE_CORE_OTHER		0x00010000UL
#define XELOG_MODULE_CORE \
				( XELOG_MODULE_LIB_CEO \
						| XELOG_MODULE_LIB_AA \
						| XELOG_MODULE_LIB_SOE \
						| XELOG_MODULE_LIB_SAP \
						| XELOG_MODULE_LIB_SUCK \
						| XELOG_MODULE_LIB_PTZ \
						| XELOG_MODULE_LIB_LOG \
						| XELOG_MODULE_LIB_PM \
						| XELOG_MODULE_LIB_SIS \
						| XELOG_MODULE_LIB_DAVINCI \
						| XELOG_MODULE_LIB_CONF\
						| XELOG_MODULE_LIB_IPCAM \
						| XELOG_MODULE_CORE_OTHER )

#define XELOG_MODULE_APP_S2506A		0x00020000UL
#define XELOG_MODULE_APP_SIPUA		0x00040000UL
#define XELOG_MODULE_APP_HXGUI		0x00080000UL
#define XELOG_MODULE_APP_HXWEB		0x00100000UL
#define XELOG_MODULE_APP_OTHER		0x00200000UL
#define XELOG_MODULE_APP	\
			(XELOG_MODULE_APP_S2506A \
						| XELOG_MODULE_APP_SIPUA \
						| XELOG_MODULE_APP_HXGUI \
						| XELOG_MODULE_APP_HXWEB \
						| XELOG_MODULE_APP_OTHER )

#define XELOG_MODULE_RAMDISK		0x00400000UL
#define XELOG_MODULE_SYSLOG			0x00800000UL
#define XELOG_MODULE_HXSDK			0x01000000UL

#define XELOG_MODULE_USER \
				( XELOG_MODULE_RAMDISK \
						| XELOG_MODULE_SYSLOG \
						| XELOG_MODULE_HXSDK \
						| XELOG_MODULE_CORE \
						| XELOG_MODULE_APP)

#define XELOG_MODULE_ALL		(XELOG_MODULE_USER	| XELOG_MODULE_KERNEL)

#define XELOG_FILE_PATH_LEN			(128)/*max length of log file path*/
/**********************************************************************************************
 * Structure:
 * 		struct init_xelog_local;
 * Description:
 * 		use this struct to describe initialize parameters used in local mode;
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
	 * size of each log file,unit:bytes [512KB,4MB]
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
 * 		use this struct to describe initialize parameters used in remote mode;
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
	 * 				XELOG_MODULE_RAMDISK,XELOG_MODULE_HXSDK,
	 * 				XELOG_MODULE_LIB_xxx,XELOG_MODULE_APP_xxx
	 * modules:	XELOG_MODULE_xxx | XELOG_MODULE_xxx,
	 * 			    XELOG_MODULE_CORE,XELOG_MODULE_APP,XELOG_MODULE_USER,XELOG_MODULE_ALL
	 * 			  	
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
	 * 				XELOG_MODULE_RAMDISK,XELOG_MODULE_HXSDK,
	 * 				XELOG_MODULE_LIB_xxx,XELOG_MODULE_APP_xxx
	 * modules:	XELOG_MODULE_xxx | XELOG_MODULE_xxx,
	 * 			   XELOG_MODULE_CORE,XELOG_MODULE_APP,XELOG_MODULE_USER,XELOG_MODULE_ALL
	 * 			  	
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

#define xeLOG_EMERG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_EMERG)) { \
				fprintf(stderr, XELOG_PREFIX"(%s.%d.EMERG):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_CRIT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_CRIT)) { \
				fprintf(stderr, XELOG_PREFIX"(%s.%d.CRIT):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_ALERT(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ALERT)) { \
				fprintf(stderr, XELOG_PREFIX"(%s.%d.ALERT):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_ERR(fmt, args...) \
		do{	\
			if(log_level>=(LOG_ERR)) { \
				fprintf(stderr, XELOG_PREFIX"(%s.%d.ERR):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_WARNING(fmt, args...) \
		do{	\
			if(log_level>=(LOG_WARNING)) { \
				fprintf(stderr, XELOG_PREFIX"(%s.%d.WARNING):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_NOTICE(fmt, args...) \
		do{	\
			if(log_level>=(LOG_NOTICE)) { \
				fprintf(stderr, XELOG_PREFIX"(%s.%d.NOTICE):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_INFO(fmt, args...) \
		do{	\
			if(log_level>=(LOG_INFO)) { \
				fprintf(stdout, XELOG_PREFIX"(%s.%d.INFO):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

#define xeLOG_DEBUG(fmt, args...) \
		do{	\
			if(log_level>=(LOG_DEBUG)) { \
				fprintf(stdout, XELOG_PREFIX"(%s.%d.DBG):"fmt"\n",__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);
#endif/*XELOG_2_CONSOLE*/

#if defined(XELOG_2_REMOTE)

int xeLOG_PUSH(char *sbuf, int slen);

#define xeLOG_COMMOM(lvl,fmt,args...) \
		do{	\
			char sbuf[XELOG_LOG_LEN_MAX]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,"<%d>"XELOG_PREFIX"(%s.%d):"fmt"\n", \
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
		}while(0);
#endif/*BUG*/

#ifndef BUGMSG
#define BUGMSG(fmt,args...) \
		do{	\
			xeLOG_ALERT("BUG: "fmt,##args);\
		}while(0);
#endif/*BUGMSG*/
/***********************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /*XELOG_H_*/
