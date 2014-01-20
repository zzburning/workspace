/******************************************************************************************************************
 * 					Filename: xeLOG_internal.h
 ******************************************************************************************************************
 * Description:
 * 		 equipment log interface.
 * Version:
 *	 	 V_0.6 Jun-07-2011
 * Copyright:
 * 		 HISOME <http://www.hisome.com>
 * Author:
 * 		 renhw <renhw@hisome.com.>
******************************************************************************************************************/
#ifndef __XELOG_INTERNAL_H_
#define __XELOG_INTERNAL_H_

#ifdef CONFIG_USE_EXTERNAL_XELOG
#include <xelog.h>
#else/*!CONFIG_USE_EXTERNAL_XELOG*/

#include <stdio.h>
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
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
 * 		0 - xeLOG_EMERG(fmt, args...)
 *		1 - xeLOG_CRIT(fmt, args...)
 *		2 - xeLOG_ALERT(fmt, args...)
 *		3 - xeLOG_ERR(fmt, args...)
 *		4 - xeLOG_WARNING(fmt, args...)
 *		5 - xeLOG_NOTICE(fmt, args...)
 *		6 - xeLOG_INFO(fmt, args...)
 *		7 - xeLOG_DEBUG(fmt, args...)
 **/
extern int xeDEX_log_level;

#define LOG_PREFIX "libxeDEX2"

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

#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
#define xeLOG_EMERG(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_EMERG)) { \
				fprintf(stderr, COLOR_EMERG LOG_PREFIX"(%s.%d.EMERG): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_CRIT(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_CRIT)) { \
				fprintf(stderr, COLOR_CRIT LOG_PREFIX"(%s.%d.CRIT): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_ALERT(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_ALERT)) { \
				fprintf(stderr, COLOR_ALERT LOG_PREFIX"(%s.%d.ALERT): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_ERR(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_ERR)) { \
				fprintf(stderr, COLOR_ERR LOG_PREFIX"(%s.%d.ERR): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_WARNING(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_WARNING)) { \
				fprintf(stderr, COLOR_WARNING LOG_PREFIX"(%s.%d.WARNING): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_NOTICE(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_NOTICE)) { \
				fprintf(stderr, COLOR_NOTICE LOG_PREFIX"(%s.%d.NOTICE): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stderr); \
			} \
		}while(0);

#define xeLOG_INFO(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_INFO)) { \
				fprintf(stdout, COLOR_INFO LOG_PREFIX"(%s.%d.INFO): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

#define xeLOG_DEBUG(fmt, args...) \
		do{ \
			if(xeDEX_log_level>=(LOG_DEBUG)) { \
				fprintf(stdout, COLOR_DEBUG LOG_PREFIX"(%s.%d.DBG): "fmt"\n"COLOR_END,__FILE__,__LINE__, ##args); \
				fflush(stdout); \
			} \
		}while(0);

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

#ifndef BUGMSG
#define BUGMSG(fmt,args...) \
	do{	\
	xeLOG_ALERT("BUG: "fmt,##args);\
	}while(0);
#endif/*BUGMSG*/
#elif defined(CONFIG_XEHSC_DEVPLAT_VC6)
#define xeLOG_EMERG \
	if(xeDEX_log_level>=(0))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.EMERG):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(0))\
	xeLOG_EMERG_fprintf

#define xeLOG_CRIT \
	if(xeDEX_log_level>=(1))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.CRIT):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(1))\
	xeLOG_CRIT_fprintf

#define xeLOG_ALERT \
	if(xeDEX_log_level>=(2))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.ALERT):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(2))\
	xeLOG_ALERT_fprintf

#define xeLOG_ERR \
	if(xeDEX_log_level>=(3))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.ERR):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(3))\
	xeLOG_ERR_fprintf

#define xeLOG_WARNING \
	if(xeDEX_log_level>=(4))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.WARNING):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(4))\
	xeLOG_WARNING_fprintf

#define xeLOG_NOTICE \
	if(xeDEX_log_level>=(5))\
	fprintf(stderr,LOG_PREFIX"(%s.%d.NOTICE):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(5))\
	xeLOG_NOTICE_fprintf

#define xeLOG_INFO \
	if(xeDEX_log_level>=(6))\
	fprintf(stdout,LOG_PREFIX"(%s.%d.INFO):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(6))\
	xeLOG_INFO_fprintf

#define xeLOG_DEBUG \
	if(xeDEX_log_level>=(7))\
	fprintf(stdout,LOG_PREFIX"(%s.%d.DEBUG):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(7))\
	xeLOG_DEBUG_fprintf

#ifndef eprintf
#define eprintf xeLOG_ERR
#endif

#ifndef dprintf
#define dprintf xeLOG_DEBUG
#endif

#ifdef NDEBUG
#define DBG
#else
#define DBG xeLOG_DEBUG
#endif

#ifndef BUGMSG
#define BUGMSG \
	if(xeDEX_log_level>=(2))\
	fprintf(stderr,LOG_PREFIX"(BUG: %s.%d.ALERT):",__FILE__,__LINE__);\
	if(xeDEX_log_level>=(2))\
	xeLOG_ALERT_fprintf
#endif/*BUGMSG*/
#else
#error "what Devplat?"
#endif
#endif/*!CONFIG_USE_EXTERNAL_XELOG*/

#ifndef BUG
#define BUG() \
		do{	\
			xeLOG_ALERT("BUG: PC@here");\
		}while(0);
#endif/*BUG*/

#ifdef __cplusplus
}
#endif

#endif /* __XELOG_INTERNAL_H_ */
