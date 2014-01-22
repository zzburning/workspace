/******************************************************************************************************************
 * 					Filename: excLOG_internal.h
 ******************************************************************************************************************
 * Description:
 * 		 equipment log interface.
 * Version:
 *	 	 V_0.6 Jun-07-2011
 * Copyright:
 * Author:
******************************************************************************************************************/
#ifndef __EXCLOG_INTERNAL_H_
#define __EXCLOG_INTERNAL_H_

#ifdef CONFIG_USE_EXTERNAL_EXCLOG
#include <exclog.h>
#else/*!CONFIG_USE_EXTERNAL_EXCLOG*/

#include <stdio.h>
#if defined(CONFIG_EXC_DEVPLAT_LINUXGCC_32)
#include <syslog.h>
#endif
#include <errno.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
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
extern int log_level;

#define LOG_PREFIX "libexcLOG"

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

#if defined(CONFIG_EXC_DEVPLAT_LINUXGCC_32)
#define excLOG_EMERG(fmt, args...) \
		do{ \
			if(log_level>=(LOG_EMERG)) { \
				fprintf(stderr, COLOR_EMERG LOG_PREFIX"(%s.%d.EMERG): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_CRIT(fmt, args...) \
		do{ \
			if(log_level>=(LOG_CRIT)) { \
				fprintf(stderr, COLOR_CRIT LOG_PREFIX"(%s.%d.CRIT): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_ALERT(fmt, args...) \
		do{ \
			if(log_level>=(LOG_ALERT)) { \
				fprintf(stderr, COLOR_ALERT LOG_PREFIX"(%s.%d.ALERT): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_ERR(fmt, args...) \
		do{ \
			if(log_level>=(LOG_ERR)) { \
				fprintf(stderr, COLOR_ERR LOG_PREFIX"(%s.%d.ERR): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_WARNING(fmt, args...) \
		do{ \
			if(log_level>=(LOG_WARNING)) { \
				fprintf(stderr, COLOR_WARNING LOG_PREFIX"(%s.%d.WARNING): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_NOTICE(fmt, args...) \
		do{ \
			if(log_level>=(LOG_NOTICE)) { \
				fprintf(stderr, COLOR_NOTICE LOG_PREFIX"(%s.%d.NOTICE): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define excLOG_INFO(fmt, args...) \
		do{ \
			if(log_level>=(LOG_INFO)) { \
				fprintf(stdout, COLOR_INFO LOG_PREFIX"(%s.%d.INFO): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

#define excLOG_DEBUG(fmt, args...) \
		do{ \
			if(log_level>=(LOG_DEBUG)) { \
				fprintf(stdout, COLOR_DEBUG LOG_PREFIX"(%s.%d.DBG): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

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

#ifndef BUGMSG
#define BUGMSG(fmt,args...) \
	do{	\
	excLOG_ALERT("BUG: "fmt,##args);\
	}while(0);
#endif/*BUGMSG*/
#elif defined(CONFIG_EXC_DEVPLAT_VC6)
#define excLOG_EMERG \
	if(log_level>=(0))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.EMERG):",__FILE__,__LINE__);\
	if(log_level>=(0))\
	excLOG_EMERG_fprintf

#define excLOG_CRIT \
	if(log_level>=(1))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.CRIT):",__FILE__,__LINE__);\
	if(log_level>=(1))\
	excLOG_CRIT_fprintf

#define excLOG_ALERT \
	if(log_level>=(2))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.ALERT):",__FILE__,__LINE__);\
	if(log_level>=(2))\
	excLOG_ALERT_fprintf

#define excLOG_ERR \
	if(log_level>=(3))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.ERR):",__FILE__,__LINE__);\
	if(log_level>=(3))\
	excLOG_ERR_fprintf

#define excLOG_WARNING \
	if(log_level>=(4))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.WARNING):",__FILE__,__LINE__);\
	if(log_level>=(4))\
	excLOG_WARNING_fprintf

#define excLOG_NOTICE \
	if(log_level>=(5))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.NOTICE):",__FILE__,__LINE__);\
	if(log_level>=(5))\
	excLOG_NOTICE_fprintf

#define excLOG_INFO \
	if(log_level>=(6))\
	fprintf(stdout,LOG_PREFIX"(%s.%d.INFO):",__FILE__,__LINE__);\
	if(log_level>=(6))\
	excLOG_INFO_fprintf

#define excLOG_DEBUG \
	if(log_level>=(7))\
	fprintf(stdout,LOG_PREFIX"(%s.%d.DEBUG):",__FILE__,__LINE__);\
	if(log_level>=(7))\
	excLOG_DEBUG_fprintf

#ifndef eprintf
#define eprintf excLOG_ERR
#endif

#ifndef dprintf
#define dprintf excLOG_DEBUG
#endif

#ifdef NDEBUG
#define DBG
#else
#define DBG excLOG_DEBUG
#endif

#ifndef BUGMSG
#define BUGMSG \
	if(log_level>=(2))\
	fprintf(stderr,LOG_PREFIX"(BUG: %s.%d.ALERT):",__FILE__,__LINE__);\
	if(log_level>=(2))\
	excLOG_ALERT_fprintf
#endif/*BUGMSG*/
#else
#error "what Devplat?"
#endif
#endif/*!CONFIG_USE_EXTERNAL_EXCLOG*/

#ifndef BUG
#define BUG() \
		do{	\
			excLOG_ALERT("BUG: PC@here");\
		}while(0);
#endif/*BUG*/

#ifdef __cplusplus
}
#endif

#endif /* __excLOG_INTERNAL_H_ */
