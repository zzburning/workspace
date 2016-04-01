#ifndef wLOG_H_
#define wLOG_H_

#include <syslog.h>
#include <errno.h>
#include <string.h>

/*enable syslog or not*/
extern int be_syslog;
/**
 * log level,0~7,large number,large messages
 * 		0 - wLOG_EMERG(fmt, args...)
 *		1 - wLOG_CRIT(fmt, args...)
 *		2 - wLOG_ALERT(fmt, args...)
 *		3 - wLOG_ERR(fmt, args...)
 *		4 - wLOG_WARNING(fmt, args...)
 *		5 - wLOG_NOTICE(fmt, args...)
 *		6 - wLOG_INFO(fmt, args...)
 *		7 - wLOG_DEBUG(fmt, args...)
 **/
extern int log_level;
extern int exit_once_err;
/**
 * MSG_PREFIX will add to each log message head.
 * each module should have its own MSG_PREFIX
 **/ 
#define MSG_PREFIX	"wlog"

/*implement this function if any app use this file.*/
int init_wlog(void);
/* *
 * 	#include <wlog.h>
	int be_syslog=1;
	int log_level=7;
	int init_wlog(void){
		if(be_syslog){
			openlog(MSG_PREFIX,0,LOG_DAEMON);
		}	
	return 0;
	}
 * */



//================================================================
/**
 * discard any wLOG_xxx() messages.
 **/ 
//#define NO_LOG	1

/**
 * discard DBG() message.
 **/
//#define NO_DEBUG	1


/**
 * call init_wlog() to init wLOG_xxx();
 **/
//#define LOG_AS_SYSLOG 	1


#define LOG_AS_CONSOLE	1


/**
 * call init_wlog_network() to init wLOG_xxx();
 **/
//#define LOG_AS_NETWORK	1


//================================================================
#ifdef NO_LOG
	#define wLOG_EMERG(fmt, args...)
	#define wLOG_CRIT(fmt, args...)
	#define wLOG_ALERT(fmt, args...)
	#define wLOG_ERR(fmt, args...)
	#define wLOG_WARNING(fmt, args...)
	#define wLOG_NOTICE(fmt, args...)
	#define wLOG_INFO(fmt, args...)
	#define wLOG_DEBUG(fmt, args...)
#elif defined(LOG_AS_SYSLOG)
	#define wLOG_EMERG(fmt, args...) \
		if(be_syslog && log_level>=(LOG_EMERG)) { \
			syslog(LOG_CRIT, "(%s.%d.EMERG): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_CRIT(fmt, args...) \
		if(be_syslog && log_level>=(LOG_CRIT)) { \
			syslog(LOG_CRIT, "(%s.%d.CRIT): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_ALERT(fmt, args...) \
		if(be_syslog && log_level>=(LOG_ALERT)) { \
			syslog(LOG_ALERT, "(%s.%d.ALERT): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_ERR(fmt, args...) \
		if(be_syslog && log_level>=(LOG_ERR)) { \
			syslog(LOG_ERR, "(%s.%d.ERR): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_WARNING(fmt, args...) \
		if(be_syslog && log_level>=(LOG_WARNING)) { \
			syslog(LOG_WARNING, "(%s.%d.WARNING): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_NOTICE(fmt, args...) \
		if(be_syslog && log_level>=(LOG_NOTICE)) { \
			syslog(LOG_NOTICE, "(%s.%d.NOTICE): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_INFO(fmt, args...) \
		if(be_syslog && log_level>=(LOG_INFO)) { \
			syslog(LOG_INFO, "(%s.%d.INFO): "fmt,__FILE__,__LINE__, ##args); \
		}

	#define wLOG_DEBUG(fmt, args...) \
		if(be_syslog && log_level>=(LOG_DEBUG)) { \
			syslog(LOG_DEBUG, "(%s.%d.DBG): "fmt,__FILE__,__LINE__, ##args); \
		}
#elif defined(LOG_AS_CONSOLE)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
	#define wLOG_EMERG(fmt, args...) \
		if(log_level>=(LOG_EMERG)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.EMERG): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}

	#define wLOG_CRIT(fmt, args...) \
		if(log_level>=(LOG_CRIT)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.CRIT): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define wLOG_ALERT(fmt, args...) \
		if(log_level>=(LOG_ALERT)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.ALERT): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define wLOG_ERR(fmt, args...) \
		if(log_level>=(LOG_ERR)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.ERR): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
			if(exit_once_err){ \
				if(errno){ \
					fprintf(stderr, MSG_PREFIX"(%s.%d.ERR): %s\n",__FILE__,__LINE__,strerror(errno)); \
					fflush(stderr); \
				} \
				exit(-1);\
			}\
		}
	
	#define wLOG_WARNING(fmt, args...) \
		if(log_level>=(LOG_WARNING)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.WARNING): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define wLOG_NOTICE(fmt, args...) \
		if(log_level>=(LOG_NOTICE)) { \
			fprintf(stderr, MSG_PREFIX"(%s.%d.NOTICE): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stderr); \
		}
	
	#define wLOG_INFO(fmt, args...) \
		if(log_level>=(LOG_INFO)) { \
			fprintf(stdout, MSG_PREFIX"(%s.%d.INFO): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stdout); \
		}
	
	#define wLOG_DEBUG(fmt, args...) \
		if(log_level>=(LOG_DEBUG)) { \
			fprintf(stdout, MSG_PREFIX"(%s.%d.DBG): "fmt"\n",__FILE__,__LINE__, ##args); \
			fflush(stdout); \
		}

#elif defined(LOG_AS_NETWORK)
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern int wlog_sockfd;

int init_wlog_network(const char *remoteIP,int remotePort);
int dnit_wlog_network(void);
int wLOG_PUSH(char *sbuf,int slen);

	#define wLOG_COMMOM(lstr,fmt,args...) \
		do{	\
			char sbuf[256]=""; int slen;\
			slen=snprintf(sbuf,sizeof(sbuf)-1,MSG_PREFIX"(%s.%d."lstr"): "fmt"\n",__FILE__,__LINE__, ##args); \
			wLOG_PUSH(sbuf,slen); \
		}while(0);

	#define wLOG_EMERG(fmt, args...) \
		if(log_level>=(LOG_EMERG) ) { \
			wLOG_COMMOM("EMERG",fmt, ##args); \
		}

	#define wLOG_CRIT(fmt, args...) \
		if(log_level>=(LOG_CRIT) ) { \
			wLOG_COMMOM("CRIT",fmt, ##args); \
		}
	
	#define wLOG_ALERT(fmt, args...) \
		if(log_level>=(LOG_ALERT) ) { \
			wLOG_COMMOM("ALERT",fmt, ##args); \
		}
	
	#define wLOG_ERR(fmt, args...) \
		if(log_level>=(LOG_ERR) ) { \
			wLOG_COMMOM("ERR",fmt, ##args); \
		}
	
	#define wLOG_WARNING(fmt, args...) \
		if(log_level>=(LOG_WARNING) ) { \
			wLOG_COMMOM("WARNING",fmt, ##args); \
		}
	
	#define wLOG_NOTICE(fmt, args...) \
		if(log_level>=(LOG_NOTICE) ) { \
			wLOG_COMMOM("NOTICE",fmt, ##args); \
		}
	
	#define wLOG_INFO(fmt, args...) \
		if(log_level>=(LOG_INFO) ) { \
			wLOG_COMMOM("INFO",fmt, ##args); \
		}
	
	#define wLOG_DEBUG(fmt, args...) \
		if(log_level>=(LOG_DEBUG) ) { \
			wLOG_COMMOM("DBG",fmt, ##args); \
		}
#endif


#ifdef NO_DEBUG
	#define DBG(fmt, args...)
#else
	#define DBG(fmt, args...) wLOG_DEBUG(fmt, ##args)
#endif

#define eprintf(fmt, args...) wLOG_ERR(fmt, ##args)

#define dprintf(fmt, args...) wLOG_DEBUG(fmt, ##args)


#endif /*XELOG_H_*/
