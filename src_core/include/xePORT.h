/*		Filename: xePORT.h
 *************************************************
 * Description:
 *		responsible of the portability of our source.
 * Version:
 *		V_0.1	May-12-2010
 * Copyright:
 *		HISOME <www.hisome.com.>
 * Author:
 *		hanln <hanln@hisome.com.>
*/
#ifndef __HISOME_XEPORT_H__
#define __HISOME_XEPORT_H__

//#define WIN32

#if !defined(WIN32) && !defined(_WIN32_WCE)


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#else

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <Winsock2.h>
#include <process.h>

/*this file will include WSPiApi.h,
 a error will happen when link, 
must define marco _WSPIAPI_COUNTOF on the top of WSPiApi.h file.
ld*/
#include <ws2tcpip.h> 

#include <errno.h>
#include <time.h>

#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(WIN32) && !defined(_WIN32_WCE)
/********************************/
/* definitions for LINUX flavour */
/********************************/

typedef int xe_socket_t;
typedef pthread_t xe_thread_t;
typedef pthread_mutex_t xe_mutex_t;
typedef pthread_cond_t xe_cond_t;

int xe_socket_close(int sockfd);
#define xe_socklen_t			socklen_t

#if 0
static const int xe_invalid_socket = -1; 
static const int xe_socket_error = -1;
#else
#define xe_invalid_socket	(-1)
#define xe_socket_error		(-1)
#endif


#define xe_thread_create		pthread_create
#define xe_thread_join			pthread_join
#define xe_thread_exit			pthread_exit
#define xe_mutex_init			pthread_mutex_init
#define xe_mutex_lock			pthread_mutex_lock
#define xe_mutex_unlock			pthread_mutex_unlock
#define xe_mutex_destroy		pthread_mutex_destroy
#define xe_cond_init			pthread_cond_init
#define xe_cond_signal			pthread_cond_signal
#define xe_cond_broadcast		pthread_cond_broadcast
#define xe_cond_wait			pthread_cond_wait
#define xe_cond_destroy			pthread_cond_destroy


#define xe_cond_timewait		LIN_cond_timewait
int LIN_cond_timewait(xe_cond_t* hCond, xe_mutex_t * hMutex,int tv_sec, int tv_nsec);

#else
/*********************************/
/* definitions for WIN32 flavour */
/*********************************/


typedef unsigned int in_addr_t;

#define vsnprintf	_vsnprintf
#define snprintf	_snprintf

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

#ifndef __FUNC__
#define __FUNC__ "function"
#endif

#ifndef __VERSION__
#define __VERSION__ "VC6.0"
#endif

typedef SOCKET xe_socket_t;
typedef HANDLE xe_thread_t;
typedef HANDLE xe_mutex_t;
typedef HANDLE xe_cond_t;

int xe_socket_close(SOCKET sockfd);
#define xe_socklen_t			int
#define xe_invalid_socket	INVALID_SOCKET
#define xe_socket_error		SOCKET_ERROR

#define xe_thread_create		WIN_thread_create
#define xe_thread_join		WIN_thread_join
#define xe_mutex_init		WIN_mutex_init
#define xe_mutex_lock		WIN_mutex_lock
#define xe_mutex_unlock		WIN_mutex_unlock
#define xe_mutex_destroy		WIN_mutex_destroy
#define xe_cond_init			WIN_cond_init
#define xe_cond_signal		WIN_cond_signal
#define xe_cond_broadcast	WIN_cond_broadcast
#define xe_cond_wait			WIN_cond_wait
#define xe_cond_destroy		WIN_cond_destroy

#define xe_cond_timewait		WIN_cond_timewait

int WIN_thread_create(xe_thread_t *t, void *attr_unused, void *(*func)(void*), void *arg);
int WIN_thread_join(xe_thread_t thread, void **unused);
int WIN_mutex_init(xe_mutex_t *m, void *attr_unused);
int WIN_mutex_lock(xe_mutex_t *mutex);
int WIN_mutex_unlock(xe_mutex_t *mutex);
int WIN_mutex_destroy(xe_mutex_t *mutex);
int WIN_cond_init(xe_cond_t *cond, void *attr_unused);
int WIN_cond_wait(xe_cond_t * cond, xe_mutex_t * mutex);
int WIN_cond_signal(xe_cond_t * cond);
int WIN_cond_broadcast(xe_cond_t * cond);
int WIN_cond_destroy(xe_cond_t * cond);


int WIN_cond_timewait(xe_cond_t* hCond, xe_mutex_t * hMutex,int tv_sec, int tv_nsec);

int gettimeofday(struct timeval *tv, void* tz);
int inet_aton (const char * cp, struct in_addr * addr);

/**
* Structure for storing a pipe descriptor
*/
typedef struct pipe_t_struct{
    int pipes[2];
}pipe_t;
/**
* Get New pipe pair.
*/
pipe_t *lpipe (void);
/**
* Close pipe
*/
int lpipe_close (pipe_t * apipe);
/**
* Write in a pipe.
*/
int lpipe_write (pipe_t * pipe, const void *buf, int count);
/**
* Read in a pipe.
*/
int lpipe_read (pipe_t * pipe, void *buf, int count);

const char* winsock_error_str(int winsock_error);

#endif//!defined(WIN32) && !defined(_WIN32_WCE)


char* xe_strdup(const char *tmp);

#ifdef __cplusplus
}
#endif

#endif/*__HISOME_XEPORT_H__*/

