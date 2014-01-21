/******************************************************************************
 * EXC_port.h
 *
 *  Created on: 2013-06-05
 *      Author: 
 *
 * Description:
 * 	This file is EXC Interface
 *
 * Revision History:
 * 	V0.1 initial version code
 *****************************************************************************/

#ifndef __EXC_PORT_H__
#define __EXC_PORT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_EXC_DEVPLAT_LINUXGCC_32)

#include <pthread.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

typedef int 		exc_socket_t;
typedef socklen_t 	exc_socklen_t;
#define exc_socket_close	close

typedef pthread_t exc_pthread_t;
typedef pthread_mutex_t exc_pthread_mutex_t;
typedef pthread_cond_t exc_pthread_cond_t;
#define exc_pthread_create			pthread_create
#define exc_pthread_join 			pthread_join
#define exc_pthread_exit 			pthread_exit
#define exc_pthread_mutex_init		pthread_mutex_init
#define exc_pthread_mutex_lock		pthread_mutex_lock
#define exc_pthread_mutex_unlock 	pthread_mutex_unlock
#define exc_pthread_mutex_destroy	pthread_mutex_destroy
#define exc_pthread_cond_init		pthread_cond_init
#define exc_pthread_cond_signal	 	pthread_cond_signal
#define exc_pthread_cond_broadcast	pthread_cond_broadcast
#define exc_pthread_cond_wait		pthread_cond_wait
#define exc_pthread_cond_destroy		pthread_cond_destroy
#define exc_pthread_cond_timewait	pthread_cond_timewait
#define HXETIMEDOUT	ETIMEDOUT

#elif defined(CONFIG_EXC_DEVPLAT_VC6)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <Winsock2.h>
#include <process.h>
#include <ws2tcpip.h>
#include <errno.h>
#include <time.h>

typedef unsigned int in_addr_t;
typedef SOCKET	exc_socket_t;
typedef int 	exc_socklen_t;
#define exc_socket_close		closesocket

typedef HANDLE exc_pthread_t;
typedef HANDLE exc_pthread_mutex_t;
typedef HANDLE exc_pthread_cond_t;
#define exc_pthread_create			WIN_pthread_create
#define exc_pthread_join				WIN_pthread_join
#define exc_pthread_mutex_init		WIN_pthread_mutex_init
#define exc_pthread_mutex_lock		WIN_pthread_mutex_lock
#define exc_pthread_mutex_unlock		WIN_pthread_mutex_unlock
#define exc_pthread_mutex_destroy	WIN_pthread_mutex_destroy
#define exc_pthread_cond_init		WIN_pthread_cond_init
#define exc_pthread_cond_signal		WIN_pthread_cond_signal
#define exc_pthread_cond_broadcast	WIN_pthread_cond_broadcast
#define exc_pthread_cond_wait		WIN_pthread_cond_wait
#define exc_pthread_cond_destroy		WIN_pthread_cond_destroy
#define exc_pthread_cond_timedwait	WIN_pthread_cond_timedwait
#define HXETIMEDOUT	WAIT_TIMEOUT

int WIN_pthread_create(exc_pthread_t *t, void *attr_unused, void *(*func)(void*), void *arg);
int WIN_pthread_join(exc_pthread_t thread, void **unused);
int WIN_pthread_mutex_init(exc_pthread_mutex_t *m, void *attr_unused);
int WIN_pthread_mutex_lock(exc_pthread_mutex_t *mutex);
int WIN_pthread_mutex_unlock(exc_pthread_mutex_t *mutex);
int WIN_pthread_mutex_destroy(exc_pthread_mutex_t *mutex);
int WIN_pthread_cond_init(exc_pthread_cond_t *cond, void *attr_unused);
int WIN_pthread_cond_wait(exc_pthread_cond_t * cond, exc_pthread_mutex_t * mutex);
int WIN_pthread_cond_signal(exc_pthread_cond_t * cond);
int WIN_pthread_cond_broadcast(exc_pthread_cond_t * cond);
int WIN_pthread_cond_destroy(exc_pthread_cond_t * cond);
int WIN_pthread_cond_timedwait(exc_pthread_cond_t *hCond, exc_pthread_mutex_t *hMutex, DWORD dwMilliseconds);

void excLOG_EMERG_fprintf(char *fmt,...);
void excLOG_CRIT_fprintf(char *fmt,...);
void excLOG_ALERT_fprintf(char *fmt,...);
void excLOG_ERR_fprintf(char *fmt,...);
void excLOG_WARNING_fprintf(char *fmt,...);
void excLOG_NOTICE_fprintf(char *fmt,...);
void excLOG_INFO_fprintf(char *fmt,...);
void excLOG_DEBUG_fprintf(char *fmt,...);

#ifndef vsnprintf
#define vsnprintf	_vsnprintf
#endif

#ifndef snprintf
#define snprintf	_snprintf
#endif

#ifndef strdup
#define _strdup strdup
#endif

#ifndef strncasecmp
#define strncasecmp strnicmp
#endif

#ifndef strcasecmp
#define strcasecmp stricmp
#endif

#ifndef random
#define random rand
#endif

#ifndef srandom
#define srandom srand
#endif

int gettimeofday(struct timeval *tv, void* tz);
int inet_aton(const char *cp, struct in_addr *addr);
void usleep(int usec);
void localtime_r(time_t *tick_now, struct tm *tm);

#else
#error "what Devplat?"
#endif

#ifdef __cplusplus
}
#endif

#endif /* __EXC_PORT_H__ */
