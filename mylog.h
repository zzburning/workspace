/*		Filename: mylog.h
 *************************************************
 * Description:
 *		log interface.
 * Version:
 *		V_0.1	
 * Copyright:
 *		
 * Author:
 *		
 */
#ifndef mylog_H_
#define mylog_H_

#include <syslog.h>
#include <errno.h>
#include <string.h>

/*enable syslog or not*/
extern int be_syslog;
/**
 * log level,0~7,large number,large messages
 * 		0 - mylog_EMERG(fmt, args...)
 *		1 - mylog_CRIT(fmt, args...)
 *		2 - mylog_ALERT(fmt, args...)
 *		3 - mylog_ERR(fmt, args...)
 *		4 - mylog_WARNING(fmt, args...)
 *		5 - mylog_NOTICE(fmt, args...)
 *		6 - mylog_INFO(fmt, args...)
 *		7 - mylog_DEBUG(fmt, args...)
 **/
extern int log_level;
extern int mylog_exit_once_err;
/**
 * MSG_PREFIX will add to each log message head.
 * each module should have its own MSG_PREFIX
 **/ 
#define MSG_PREFIX	"mylog"

/*implement this function if any app use this file.*/
int init_mylog(void);
/* *
 * 	#include <mylog.h>
	int be_syslog=1;
	int log_level=7;
	int init_mylog(void){
		if(be_syslog){
			openlog(MSG_PREFIX,0,LOG_DAEMON);
		}	
	return 0;
	}
 * */



//================================================================
/**
 * discard any mylog_xxx() messages.
 **/ 
//#define NO_LOG	1

/**
 * discard DBG() message.
 **/
//#define NO_DEBUG	1


/**
 * call init_mylog() to init mylog_xxx();
 **/
//#define LOG_AS_SYSLOG 	1


#define LOG_AS_CONSOLE	1


/**
 * call init_mylog_network() to init mylog_xxx();
 **/
//#define LOG_AS_NETWORK	1


//================================================================
#ifdef NO_LOG
	#define mylog_EMERG(fmt, args...)
	#define mylog_CRIT(fmt, args...)
	#define mylog_ALERT(fmt, args...)
	#define mylog_ERR(fmt, args...)
	#define mylog_WARNING(fmt, args...)
	#define mylog_NOTICE(fmt, args...)
	#define mylog_INFO(fmt, args...)
	#define mylog_DEBUG(fmt, args...)
#elif defined(LOG_AS_SYSLOG)
	#define mylog_EMERG(fmt, args...) \
		if(be_syslog && log_level>=(LOG_EMERG)) { \
			syslog(LOG_CRIT, "(%s.%d.EMERG): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_CRIT(fmt, args...) \
		if(be_syslog && log_level>=(LOG_CRIT)) { \
			syslog(LOG_CRIT, "(%s.%d.CRIT): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_ALERT(fmt, args...) \
		if(be_syslog && log_level>=(LOG_ALERT)) { \
			syslog(LOG_ALERT, "(%s.%d.ALERT): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_ERR(fmt, args...) \
		if(be_syslog && log_level>=(LOG_ERR)) { \
			syslog(LOG_ERR, "(%s.%d.ERR): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_WARNING(fmt, args...) \
		if(be_syslog && log_level>=(LOG_WARNING)) { \
			syslog(LOG_WARNING, "(%s.%d.WARNING): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_NOTICE(fmt, args...) \
		if(be_syslog && log_level>=(LOG_NOTICE)) { \
			syslog(LOG_NOTICE, "(%s.%d.NOTICE): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_INFO(fmt, args...) \
		if(be_syslog && log_level>=(LOG_INFO)) { \
			syslog(LOG_INFO, "(%s.%d.INFO): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define mylog_DEBUG(fmt, args...) \
		if(be_syslog && log_level>=(LOG_DEBUG)) { \
			syslog(LOG_DEBUG, "(%s.%d.DBG): "fmt,__FILE__,__LINE__, ##args); \
		}
#elif defined(LOG_AS_CONSOLE)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
	#define mylog_EMERG(fmt, args...) \
		if(log_level>=(LOG_EMERG)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.EMERG): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}

	#define mylog_CRIT(fmt, args...) \
		if(log_level>=(LOG_CRIT)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.CRIT): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define mylog_ALERT(fmt, args...) \
		if(log_level>=(LOG_ALERT)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.ALERT): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define mylog_ERR(fmt, args...) \
		if(log_level>=(LOG_ERR)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.ERR): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
			if(mylog_exit_once_err){ \
				if(errno){ \
					fprintf(stderr, MSG_PREFIX"(%s.%d.ERR): %s\n",__FILE__,__LINE__,strerror(errno)); \
					fflush(stderr); \
				} \
				exit(-1);\
			}\
		}
	
	#define mylog_WARNING(fmt, args...) \
		if(log_level>=(LOG_WARNING)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.WARNING): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define mylog_NOTICE(fmt, args...) \
		if(log_level>=(LOG_NOTICE)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.NOTICE): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define mylog_INFO(fmt, args...) \
		if(log_level>=(LOG_INFO)) { \
			fprintf(stdout, MSG_PREFIX"(%s.%d.INFO): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stdout); \
		}
	
	#define mylog_DEBUG(fmt, args...) \
		if(log_level>=(LOG_DEBUG)) { \
			fprintf(stdout, MSG_PREFIX"(%s.%d.DBG): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stdout); \
		}

#elif defined(LOG_AS_NETWORK)
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern int mylog_sockfd;

int init_mylog_network(const char *remoteIP,int remotePort);
int dnit_mylog_network(void);
int mylog_PUSH(char *sbuf,int slen);

	#define mylog_COMMOM(lstr,fmt,args...) \
		do{	\
			char sbuf[256]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,MSG_PREFIX"(%s.%d."lstr"): "fmt"\n",__FILE__,__LINE__, ##args); \
			mylog_PUSH(sbuf,slen); \
		}while(0);

	#define mylog_EMERG(fmt, args...) \
		if(log_level>=(LOG_EMERG) ) { \
			mylog_COMMOM("EMERG",fmt, ##args); \
		}

	#define mylog_CRIT(fmt, args...) \
		if(log_level>=(LOG_CRIT) ) { \
			mylog_COMMOM("CRIT",fmt, ##args); \
		}
	
	#define mylog_ALERT(fmt, args...) \
		if(log_level>=(LOG_ALERT) ) { \
			mylog_COMMOM("ALERT",fmt, ##args); \
		}
	
	#define mylog_ERR(fmt, args...) \
		if(log_level>=(LOG_ERR) ) { \
			mylog_COMMOM("ERR",fmt, ##args); \
		}
	
	#define mylog_WARNING(fmt, args...) \
		if(log_level>=(LOG_WARNING) ) { \
			mylog_COMMOM("WARNING",fmt, ##args); \
		}
	
	#define mylog_NOTICE(fmt, args...) \
		if(log_level>=(LOG_NOTICE) ) { \
			mylog_COMMOM("NOTICE",fmt, ##args); \
		}
	
	#define mylog_INFO(fmt, args...) \
		if(log_level>=(LOG_INFO) ) { \
			mylog_COMMOM("INFO",fmt, ##args); \
		}
	
	#define mylog_DEBUG(fmt, args...) \
		if(log_level>=(LOG_DEBUG) ) { \
			mylog_COMMOM("DBG",fmt, ##args); \
		}
#endif


#ifdef NO_DEBUG
	#define DBG(fmt, args...)
#else
	#define DBG(fmt, args...) mylog_DEBUG(fmt, ##args)
#endif

#define eprintf(fmt, args...) mylog_ERR(fmt, ##args)

#define dprintf(fmt, args...) mylog_DEBUG(fmt, ##args)


#endif /*XELOG_H_*/
