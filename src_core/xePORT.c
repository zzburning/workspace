/*		Filename: xePORT.c
 *************************************************
 * Description:
 *		responsible of the portability of the source.
 * Version:
 * 		V_0.2	May-12-2010
 * 			1. rename to xePORT.c by wuhm<wuhm@hisome.com>
 *		V_0.1	Dec-02-2008
 * Copyright:
 *		HISOME <www.hisome.com.>
 * Author:
 *		hanln <hanln@hisome.com.>
 */

#include "xePORT.h"

#include <string.h>
#include <stdlib.h>

char * xe_strdup(const char *tmp){
	if(tmp)
#if	defined(WIN32) || defined(_WIN32_WCE)
    	return _strdup(tmp);
#else
    	return strdup(tmp);
#endif
	return NULL;
}

int xe_socket_close(xe_socket_t sockfd)
{
	if(sockfd>0)
#if	defined(WIN32) || defined(_WIN32_WCE)
		return closesocket(sockfd);
#else
		return close(sockfd);
#endif
	return -1;
}

#if	defined(WIN32) || defined(_WIN32_WCE)
int WIN_mutex_init(xe_mutex_t *mutex, void *attr)
{	
	*mutex=CreateMutex(NULL, FALSE, NULL);
	return 0;
}

int WIN_mutex_lock(xe_mutex_t * hMutex)
{
	WaitForSingleObject(*hMutex, INFINITE); /* == WAIT_TIMEOUT; */
	return 0;
}

int WIN_mutex_unlock(xe_mutex_t * hMutex)
{
	ReleaseMutex(*hMutex);
	return 0;
}

int WIN_mutex_destroy(xe_mutex_t * hMutex)
{
	CloseHandle(*hMutex);
	return 0;
}

typedef struct thread_param{
	void * (*func)(void *);
	void * arg;
}thread_param_t;

static unsigned WINAPI thread_starter(void *data){
	thread_param_t *params=(thread_param_t*)data;
	void *ret=params->func(params->arg);
	free(data);
	return (DWORD)ret;
}


int WIN_thread_create(xe_thread_t *th, void *attr, void * (*func)(void *), void *data)
{
    thread_param_t *params=malloc(sizeof(thread_param_t));
    params->func=func;
    params->arg=data;
	*th=(HANDLE)CreateThread( NULL, 0, thread_starter, params, 0, NULL);
	if(th==NULL) return -1;
	return 0;
}

int WIN_thread_join(xe_thread_t thread_h, void **unused)
{
	if (thread_h!=NULL)
	{
		WaitForSingleObject(thread_h, INFINITE);
		CloseHandle(thread_h);
	}
	return 0;
}

int WIN_cond_init(xe_cond_t *cond, void *attr)
{
	*cond=CreateEvent(NULL, FALSE, FALSE, NULL);
    return 0;
}

int WIN_cond_wait(xe_cond_t* hCond, xe_mutex_t * hMutex)
{
	//gulp: this is not very atomic ! bug here ?
	WIN_mutex_unlock(hMutex);
	WaitForSingleObject(*hCond, INFINITE);
	WIN_mutex_lock(hMutex);
    return 0;
}

//by ld
int WIN_cond_timewait(xe_cond_t* hCond, xe_mutex_t * hMutex,int tv_sec, int tv_nsec)
{
	DWORD timeout=tv_sec*1000+tv_nsec;
	DWORD ret=WaitForSingleObject(*hCond,timeout);
	if(WAIT_TIMEOUT==ret)
		return WAIT_TIMEOUT;
	else if(WAIT_OBJECT_0==ret)
		return 0;
	else
		return -1;
}
//end by ld

int WIN_cond_signal(xe_cond_t * hCond)
{
	SetEvent(*hCond);
	return 0;
}

int WIN_cond_broadcast(xe_cond_t * hCond)
{
	WIN_cond_signal(hCond);
	return 0;
}

int WIN_cond_destroy(xe_cond_t * hCond)
{
	CloseHandle(*hCond);
	return 0;
}
#endif

/**
 * Apr-11-2011 comment out by wuhm<wuhm@hisome.com>
 */
#if 0
#if !defined(WIN32) && !defined(_WIN32_WCE)
#include <sys/time.h>
#include <errno.h>
int LIN_cond_timewait(xe_cond_t* hCond, xe_mutex_t * hMutex,int tv_sec, int tv_nsec)
{
	int ret=-1;
	struct timespec timeout;
	struct timeval now;
	gettimeofday(&now,NULL);
	
	long s=now.tv_sec+tv_sec+tv_nsec/1000;
	long ms=now.tv_usec/1000+tv_nsec%1000;
	if(ms>999)
	{
		ms-=1000;
		s+=1;
	}
	timeout.tv_sec=s;
	timeout.tv_nsec=ms;
	
	pthread_mutex_lock(hMutex);
	while(1)
	{
		ret=pthread_cond_timedwait(hCond,hMutex,&timeout);
		if(ETIMEDOUT==ret || 0==ret)
			break;
	}
	pthread_mutex_unlock(hMutex);
	
	return ret;
}
#endif
#endif

#if	!defined(_WIN32) && !defined(_WIN32_WCE)
/* Use UNIX inet_aton method */
#else
int gettimeofday(struct timeval *tv, void *tz)
{
	DWORD timemillis = GetTickCount();
	tv->tv_sec  = timemillis/1000;
	tv->tv_usec = (timemillis - (tv->tv_sec*1000)) * 1000;
	return 0;
}

int inet_aton(const char * cp, struct in_addr * addr)
{
	unsigned long retval;
	
	retval = inet_addr (cp);
	
	if (retval == INADDR_NONE) 
	{
		return -1;
	}
	else
	{
		addr->S_un.S_addr = retval;
		return 1;
	}
}

pipe_t * lpipe (){
	int s = 0;
	int timeout = 0;
	static int aport = 10500;
	struct sockaddr_in raddr;
	int j;

	pipe_t *my_pipe = (pipe_t *)malloc (sizeof(pipe_t));

	if (my_pipe == NULL)
		return NULL;

	s = (int) socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (0 > s){
		free (my_pipe);
		return NULL;
    }
	my_pipe->pipes[1] = (int) socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (0 > my_pipe->pipes[1])
    {
		closesocket (s);
		free (my_pipe);
		return NULL;
    }

	raddr.sin_addr.s_addr = inet_addr ("127.0.0.1");
	raddr.sin_family = AF_INET;

	j = 50;
	while (aport++ && j-- > 0){
		raddr.sin_port = htons ((short) aport);
		if (bind (s, (struct sockaddr *) &raddr, sizeof (raddr)) < 0){
			xeLOG_ERR("Bind a local socket ERROR!");
		}else
			break;
    }

	if (j == 0){
		xeLOG_ERR("Failed to bind a local socket, aborting!");
		closesocket (s);
		closesocket (my_pipe->pipes[1]);
		free (my_pipe);
    }

	j = listen (s, 1);
	if (j != 0){
		xeLOG_ERR("Failed to listen on a local socket, aborting!");
		closesocket (s);
		closesocket (my_pipe->pipes[1]);
		free (my_pipe);
    }

	j = setsockopt (my_pipe->pipes[1],
                  SOL_SOCKET,
                  SO_RCVTIMEO, (const char *) &timeout, sizeof (timeout));
	if (j != NO_ERROR){
		/* failed for some reason... */
		xeLOG_ERR("udp plugin; cannot set O_NONBLOCK to the file desciptor!");
		closesocket (s);
		closesocket (my_pipe->pipes[1]);
		free (my_pipe);
    }

	connect (my_pipe->pipes[1], (struct sockaddr *) &raddr, sizeof (raddr));

	my_pipe->pipes[0] = accept (s, NULL, NULL);

	if (my_pipe->pipes[0] <= 0){
		closesocket (s);
		closesocket (my_pipe->pipes[1]);
		free (my_pipe);
	}

	return my_pipe;
}

int lpipe_close (pipe_t * apipe)
{
	if (apipe == NULL)
		return -1;
	closesocket (apipe->pipes[0]);
	closesocket (apipe->pipes[1]);
	free(apipe);
	return 0;
}

int lpipe_write (pipe_t * apipe, const void *buf, int count)
{
	if (apipe == NULL)
		return -1;
	return send (apipe->pipes[1], buf, count, 0);
}

int lpipe_read (pipe_t * apipe, void *buf, int count)
{
	if (apipe == NULL)
		return -1;
	return recv (apipe->pipes[0], buf, count, 0);
}
#endif

#if	!defined(_WIN32) && !defined(_WIN32_WCE)
/* Use UNIX strerror(errno) method */
#else
 /* Usual winsock error string definitions*/
static const char *winsock_error_10022="Invalid socket";
static const char *winsock_error_10024="Too many socket opened";
static const char *winsock_error_10035="Resourse is not usable";
static const char *winsock_error_10036="Doing operator about winsock";
static const char *winsock_error_10042="Error proto option";
static const char *winsock_error_10048="Adress is already used";
static const char *winsock_error_10050="Network is down";
static const char *winsock_error_10051="Network is unreached";
static const char *winsock_error_10052="Network is reset";
static const char *winsock_error_10053="Connect is stopped ususally";
static const char *winsock_error_10054="Connect is reset";
static const char *winsock_error_10055="No buffer to use";
static const char *winsock_error_10057="Socket is not connected";
static const char *winsock_error_10060="Connect time out";
static const char *winsock_error_10061="Connect is refused";
static const char *winsock_error_10065="No rout to host";
static const char *winsock_error_10091="Winsock dll is not ready";
static const char *winsock_error_10092="Winsock version is not supported";
static const char *winsock_error_10110="No usalbe data";
static const char *winsock_error_11001="Host not found";
static const char *winsock_error_11002="Host not found";
static const char *winsock_error_11004="Name invalid";

/*
 * Helper Function: winsock_error_str
 *******************************************************
 * Call this function to get string of winsock error.
 */
const char* winsock_error_str(int winsock_error)
{
	switch (winsock_error)
	{
	case WSAEINVAL:
		return winsock_error_10022;
	case WSAEMFILE:
		return winsock_error_10024;
	case WSAEWOULDBLOCK:
		return winsock_error_10035;
	case WSAEINPROGRESS:
		return winsock_error_10036;
	case WSAENOPROTOOPT:
		return winsock_error_10042;
	case WSAEADDRINUSE:
		return winsock_error_10048;
	case WSAENETDOWN:
		return winsock_error_10050;
	case WSAENETUNREACH:
		return winsock_error_10051;
	case WSAENETRESET:
		return winsock_error_10052;
	case WSAECONNABORTED:
		return winsock_error_10053;
	case WSAECONNRESET:
		return winsock_error_10054;
	case WSAENOBUFS:
		return winsock_error_10055;
	case WSAENOTCONN:
		return winsock_error_10057;
	case WSAETIMEDOUT:
		return winsock_error_10060;
	case WSAECONNREFUSED:
		return winsock_error_10061;
	case WSAEHOSTUNREACH:
		return winsock_error_10065;
	case WSASYSNOTREADY:
		return winsock_error_10091;
	case WSAVERNOTSUPPORTED:
		return winsock_error_10092;
	case WSA_E_NO_MORE:
		return winsock_error_10110;
	case WSAHOST_NOT_FOUND:
		return winsock_error_11001;
	case WSATRY_AGAIN:
		return winsock_error_11002;
	case WSANO_DATA:
		return winsock_error_11004;
	default:
		return "Undefined string to winsock error";
	}
}
#endif

