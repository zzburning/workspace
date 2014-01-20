/******************************************************************************
 * xeHSC_port.c
 *
 *  Created on: 2013-06-05
 *      Author: hanln<hanln@hisome.com>
 *
 * Description:
 * 	This file is libxeHSC port .C file
 *
 * Revision History:
 * 	V0.1 initial version code
 *****************************************************************************/

#include "xeHSC_INC.h"
#include "xeHSC_port.h"

#ifdef MEMWATCH
#include <memwatch.h>
#endif/*MEMWATCH*/

#ifdef CONFIG_USE_XEHSC

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_XEHSC_DEVPLAT_VC6)

int WIN_pthread_mutex_init(xe_pthread_mutex_t *mutex, void *attr)
{
	*mutex=CreateMutex(NULL, FALSE, NULL);
	return 0;
}

int WIN_pthread_mutex_lock(xe_pthread_mutex_t * hMutex)
{
	WaitForSingleObject(*hMutex, INFINITE);
	return 0;
}

int WIN_pthread_mutex_unlock(xe_pthread_mutex_t * hMutex)
{
	ReleaseMutex(*hMutex);
	return 0;
}

int WIN_pthread_mutex_destroy(xe_pthread_mutex_t * hMutex)
{
	CloseHandle(*hMutex);
	return 0;
}

typedef struct thread_param
{
	void * (*func)(void *);
	void * arg;
}thread_param_t;

static unsigned WINAPI thread_starter(void *data)
{
	thread_param_t *params=(thread_param_t*)data;
	void *ret=params->func(params->arg);
	free(data);
	return (DWORD)ret;
}

int WIN_pthread_create(xe_pthread_t *th, void *attr, void * (*func)(void *), void *data)
{
    thread_param_t *params=malloc(sizeof(thread_param_t));
    params->func=func;
    params->arg=data;
    *th=(HANDLE)CreateThread(NULL, 0, thread_starter, params, 0, NULL);
    if(th==NULL)
		return -1;
    else
		return 0;
}

int WIN_pthread_join(xe_pthread_t thread_h, void **unused)
{
	if (thread_h!=NULL)
	{
		WaitForSingleObject(thread_h, INFINITE);
		CloseHandle(thread_h);
	}
	return 0;
}

int WIN_pthread_cond_init(xe_pthread_cond_t *cond, void *attr)
{
	*cond=CreateEvent(NULL, FALSE, FALSE, NULL);
	return 0;
}

int WIN_pthread_cond_wait(xe_pthread_cond_t* hCond, xe_pthread_mutex_t * hMutex)
{
	WIN_pthread_mutex_unlock(hMutex);
	WaitForSingleObject(*hCond, INFINITE);
	WIN_pthread_mutex_lock(hMutex);
	return 0;
}

int WIN_pthread_cond_signal(xe_pthread_cond_t * hCond)
{
	SetEvent(*hCond);
	return 0;
}

int WIN_pthread_cond_broadcast(xe_pthread_cond_t * hCond)
{
	WIN_pthread_cond_signal(hCond);
	return 0;
}

int WIN_pthread_cond_destroy(xe_pthread_cond_t * hCond)
{
	CloseHandle(*hCond);
	return 0;
}

int WIN_pthread_cond_timedwait(xe_pthread_cond_t *hCond, xe_pthread_mutex_t *hMutex, DWORD dwMilliseconds)
{
	DWORD ret=WaitForSingleObject(*hCond,dwMilliseconds);
	if(WAIT_TIMEOUT==ret)
		return WAIT_TIMEOUT;
	else if(WAIT_FAILED==ret)
		return WAIT_FAILED;
	else if(WAIT_OBJECT_0==ret)
		return 0;
	else
		return -1;
}

//Debug message functions
static void xeLOG_fprintf_stderr(char *fmt,va_list args)
{
	char temp[255];
	char Format[255];
	char *p;
	int i=0;
	int iParam;
	double fParam;
	int nChar;

	strcpy(temp, fmt); //Copy the Format string
	p = strchr(temp,'%');

	while(p != NULL)
	{
		while((*p<'a' || *p>'z') && (*p!=0) ) p++;
		if(*p == 0)break;
		p++;

		//format string
		nChar = p - temp;
		strncpy(Format,temp, nChar);
		Format[nChar] = 0;

		//Parameters
		if(Format[nChar-1] != 'f')
		{
			iParam = va_arg( args, int);
			fprintf(stderr,Format, iParam);
		}
		else
		{
			fParam = va_arg( args, double);
			fprintf(stderr,Format, fParam);
		}

		i++;
		if(*p == 0) break;
		strcpy(temp, p);
		p = strchr(temp,'%');
	}

	if(p==NULL&&temp!=NULL){
		fprintf(stderr,temp);
	}

	return;
}

static void xeLOG_fprintf_stdout(char *fmt,va_list args)
{
	char temp[255];
	char Format[255];
	char *p;
	int i=0;
	int iParam;
	double fParam;
	int nChar;

	strcpy(temp, fmt); //Copy the Format string
	p = strchr(temp,'%');

	while(p != NULL)
	{
		while((*p<'a' || *p>'z') && (*p!=0) ) p++;
		if(*p == 0)break;
		p++;

		//format string
		nChar = p - temp;
		strncpy(Format,temp, nChar);
		Format[nChar] = 0;

		//Parameters
		if(Format[nChar-1] != 'f')
		{
			iParam = va_arg( args, int);
			fprintf(stdout,Format, iParam);
		}
		else
		{
			fParam = va_arg( args, double);
			fprintf(stdout,Format, fParam);
		}

		i++;
		if(*p == 0) break;
		strcpy(temp, p);
		p = strchr(temp,'%');
	}

	if(p==NULL&&temp!=NULL){
		fprintf(stdout,temp);
	}

	return;
}

void xeLOG_EMERG_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(0))
	{
		xeLOG_fprintf_stderr(fmt,args);
		fprintf(stderr,"\r\n");
		fflush(stderr);
	}
	va_end (args);
}

void xeLOG_CRIT_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(1))
	{
		xeLOG_fprintf_stderr(fmt,args);
		fprintf(stderr,"\r\n");
		fflush(stderr);
	}
	va_end (args);
}

void xeLOG_ALERT_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(2))
	{
		xeLOG_fprintf_stderr(fmt,args);
		fprintf(stderr,"\r\n");
		fflush(stderr);
	}
	va_end (args);
}

void xeLOG_ERR_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(3))
	{
		xeLOG_fprintf_stderr(fmt,args);
		fprintf(stderr,"\r\n");
		fflush(stderr);
	}
	va_end (args);
}

void xeLOG_WARNING_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(4))
	{
		xeLOG_fprintf_stderr(fmt,args);
		fprintf(stderr,"\r\n");
		fflush(stderr);
	}
	va_end (args);
}

void xeLOG_NOTICE_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(5))
	{
		xeLOG_fprintf_stderr(fmt,args);
		fprintf(stderr,"\r\n");
		fflush(stderr);
	}
	va_end (args);
}

void xeLOG_INFO_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(6))
	{
		xeLOG_fprintf_stdout(fmt,args);
		fprintf(stdout,"\r\n");
		fflush(stdout);
	}
	va_end (args);
}

void xeLOG_DEBUG_fprintf(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
	//if(_xeHSC_log_level>=(7))
	{
		xeLOG_fprintf_stdout(fmt,args);
		fprintf(stdout,"\r\n");
		fflush(stdout);
	}
	va_end (args);
}
//End Debug message functions

int gettimeofday(struct timeval *tv, void *tz)
{
	DWORD timemillis = GetTickCount();
	tv->tv_sec  = timemillis/1000;
	tv->tv_usec = (timemillis - (tv->tv_sec*1000)) * 1000;
	return 0;
}

int inet_aton(const char *cp, struct in_addr *addr)
{
	unsigned long retval;
	retval = inet_addr(cp);
	if(retval == INADDR_NONE)
	{
		return -1;
	}
	else
	{
		addr->S_un.S_addr = retval;
		return 1;
	}
}

void usleep(int usec)
{
	Sleep(usec/1000);
}

void localtime_r(time_t *tick, struct tm *tm)
{
	tm = localtime(tick);
}
#endif

#ifdef __cplusplus
};
#endif

#endif
