/**********************************************************************************
 * 					Filename: exclog.c
 ***********************************************************************************
 * Description:
 * 		 this is an implement file of equipment log interface.
 * Copyright:
 * Author: 
 ***********************************************************************************/
#include "exclog.h"
#include "exclog_public.h"
#include "exclog_local.h"
#include "exclog_remote.h"
#include "exclog_query.h"

int log_level=EXCLOG_LEVEL_DEFAULT;
char EXCLOG_PATH[EXCLOG_FILE_PATH_LEN]=EXCLOG_STDOUT_MAGIK_STR;

/*subscribe list and num*/
int slist_num=0;
exclog_subscribe_req_t slist[EXCLOG_SUBSCRIBE_NUM_MAX]= { };

exclog_query_info_t query_info;

/*indicate query is running or not,default is not.*/
static int START_QUERY=0;

#if defined(EXCLOG_2_LOCAL)
/*Apr-26-2011 added by wuhm<wuhm@hisome.com>*/
static int msg2stdout = 0,msg2stderr = 0;

/********************************************************************************************
 * Function: init_exclog_local()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:user should call this first before use excLOG_XXX when run as EXCLOG_2_LOCAL.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ ix_p:IN,initialize structure.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int init_exclog_local(const init_exclog_local_t *ix_p)
{	
	int i = 0;
	for (i = 0; i < EXCLOG_SUBSCRIBE_NUM_MAX; i++)
	{
		slist[i].module = EXCLOG_MODULE_NONE;
	}

	memset(&query_info, 0, sizeof(query_info));

	if (_exclog_local_init(ix_p) != 0)
	{
		DEBUG_SELF("_exclog_local_init fail.");
		return -1;
	}

	if (_exclog_local_startup() != 0)
	{
		DEBUG_SELF("_exclog_local_startup fail.");
		return -1;
	}

	msg2stdout = ix_p->msg2stdout;
	msg2stderr = ix_p->msg2stderr;

	DEBUG_SELF("init_exclog_local success.");
	return 0;
}
/********************************************************************************************
 * Function: deinit_exclog_local()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: close socket,free all sources.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return : 0.
 ********************************************************************************************/
int deinit_exclog_local(void)
{
	_exclog_local_deinit();
	DEBUG_SELF("deinit_exclog_local success,exit normally.");
	return 0;
}

/********************************************************************************************
 * Function: excLOG_local()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:put log to local queue.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ sbuf:IN,log content.
 * @ slen:IN,length of log.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int excLOG_local(char *sbuf, int slen)
{		
#ifdef DEBUG
	// time_t ticknow;
	// ticknow = time(NULL);
	/**
	 * Apr-26-2011 added by wuhm<wuhm@hisome.com>
	 */
	if(msg2stdout)
	{
		// fprintf(stdout,"%u->%s",(unsigned int)ticknow,sbuf);
		fprintf(stdout,"%s->%s",XELOG_GET_DATE_TIME(),sbuf);
	}

	if(!msg2stdout && msg2stderr)
	{
		// fprintf(stderr,"%u->%s",(unsigned int)ticknow,sbuf);
		fprintf(stderr,"%s->%s",XELOG_GET_DATE_TIME(),sbuf);
	}
#endif

	if (_exclog_local_put_queue(sbuf, slen)!=0)
	{
		DEBUG_SELF("excLOG_local fail.");
		return -1;
	}

	return 0;
}
#endif

#if defined(EXCLOG_2_REMOTE)
/********************************************************************************************
 * Function: init_exclog_network()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:set IP address and port of log receiver,user must call this function first
 *  				before use excLOG_XXX when run as EXCLOG_2_REMOTE.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ ix_p:IN,initialize structure.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int init_exclog_network(const init_exclog_remote_t *ix_p)
{
	if (_exclog_remote_init(ix_p)!=0)
	{
		DEBUG_SELF("init_exclog_network fail.");
		return -1;
	}

	if (_exclog_remote_startup()!=0)
	{
		DEBUG_SELF("init_exclog_network fail.");
		return -1;
	}

	DEBUG_SELF("init_exclog_network success.");
	return 0;
}
/********************************************************************************************
 * Function: deinit_exclog_network()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: close socket.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return : 0.
 ********************************************************************************************/
int deinit_exclog_network(void)
{
	_exclog_remote_deinit();
	DEBUG_SELF("deinit_exclog_network success,exit normally.");
	return 0;
}
/********************************************************************************************
 * Function: excLOG_PUSH()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: push log to remote.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ sbuf: IN, log to send.
 * @ slen: IN, length of log.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int excLOG_PUSH(char *sbuf, int slen)
{
	if (_exclog_remote_put_queue(sbuf, slen)!=0)
	{
		DEBUG_SELF("excLOG_PUSH fail.");
		return -1;
	}

	return 0;
}
#endif

/********************************************************************************************
 * Function: excLOG_query()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:query log according to start/end time,level,module.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,query request.
 * @ rps:OUT,query response.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 * 		 1:busy.
 ********************************************************************************************/
int excLOG_query(const exclog_query_req_t *req)
{
	int ret=0;
	
	ret=_exclog_query_check_req(req);
	switch (ret)
	{
	case 0:
		DBG_SELF("Check req success.");
		break;
	case 1:
		DEBUG_SELF("Invalid start time.");
		return -1;
	case 2:
		DEBUG_SELF("Invalid end time.");
		return -1;
	case 3:
		DEBUG_SELF("start time > end time.");
		return -1;
	case 4:
		DEBUG_SELF("Invalid log level,must be 0~7.");
		return -1;
	case 5:
		DEBUG_SELF("Invalid module.");
		return -1;
	case 6:
		DEBUG_SELF("Empty request.");
		return -1;
	default:
		break;
	}
	
	if (1==START_QUERY)
	{
		DEBUG_SELF("busy,there is query task running.");
		return 1;
	}
	
	memset(&query_info,0,sizeof(query_info));
	query_info.req.stime=req->stime;
	query_info.req.etime=req->etime;
	query_info.req.level=req->level;
	query_info.req.module=req->module;
	
	START_QUERY=1;
	
	return 0;
}
/********************************************************************************************
 * Function: excLOG_read()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:start query and return to user.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ rps:OUT,query response.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int excLOG_read(exclog_query_rps_t **rps)
{
	if (0 == START_QUERY)
	{
		DEBUG_SELF("user should call excLOG_query() before excLOG_read().");
		return -1;
	}

	int ret=0;
	
#ifdef EXCLOG_2_LOCAL
	ret=_exclog_query_startup(NULL, rps);
#endif

#ifdef EXCLOG_2_REMOTE
	//ret=_exclog_query_from_remote(req, rps);
#endif
	
	return ret;
}
/********************************************************************************************
 * Function: excLOG_close()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:close query task..
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return : NULL.
 ********************************************************************************************/
void excLOG_close()
{
	_exclog_query_stop();
	memset(&query_info,0,sizeof(query_info));
	START_QUERY=0;
	return;
}
/********************************************************************************************
 * Function: excLOG_subscribe()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:subscribe log,run callback when request fired .
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ req:IN,subscribe request.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int excLOG_subscribe(exclog_subscribe_req_t *ereq)
{
	if (!((ereq->level & EXCLOG_LEVEL_EMERG)\
			|| (ereq->level & EXCLOG_LEVEL_CRIT) \
			|| (ereq->level	& EXCLOG_LEVEL_ALERT) \
			|| (ereq->level & EXCLOG_LEVEL_ERR) \
			|| (ereq->level	& EXCLOG_LEVEL_WARNING) \
			|| (ereq->level & EXCLOG_LEVEL_NOTICE)\
			|| (ereq->level	& EXCLOG_LEVEL_INFO) \
			|| (ereq->level & EXCLOG_LEVEL_DEBUG)))
	{
		DEBUG_SELF("subscribe fail,invalid level.");
		return -1;
	}

	/*------------check module------------------*/
	if (!((ereq->module & EXCLOG_MODULE_KERNEL) \
			|| (ereq->module & EXCLOG_MODULE_SYSLOG)\
			|| (ereq->module & EXCLOG_MODULE_HXSDK)\
			|| (ereq->module & EXCLOG_MODULE_LIB_CEO)\
			|| (ereq->module & EXCLOG_MODULE_LIB_AA)\
			|| (ereq->module & EXCLOG_MODULE_LIB_SOE)\
			|| (ereq->module & EXCLOG_MODULE_LIB_SAP)\
			|| (ereq->module & EXCLOG_MODULE_LIB_PTZ)\
			|| (ereq->module & EXCLOG_MODULE_LIB_LOG) \
			|| (ereq->module & EXCLOG_MODULE_LIB_PM)\
			|| (ereq->module & EXCLOG_MODULE_LIB_SIS)\
			|| (ereq->module & EXCLOG_MODULE_LIB_DAVINCI)\
			|| (ereq->module & EXCLOG_MODULE_CORE_OTHER)
			|| (ereq->module & EXCLOG_MODULE_APP_S2506A) \
			|| (ereq->module & EXCLOG_MODULE_APP_SIPUA)\
			|| (ereq->module & EXCLOG_MODULE_APP_HXWEB) \
			|| (ereq->module & EXCLOG_MODULE_APP_HXGUI)
			|| (ereq->module & EXCLOG_MODULE_APP_OTHER)))
	{
		DEBUG_SELF("subscribe fail,invalid module.");
		return -1;
	}

	if(ereq->sub_f==NULL)
	{
		DEBUG_SELF("subscribe fail,invalid callback function.");
		return -1;
	}

	int i;
	for (i=0; i<EXCLOG_SUBSCRIBE_NUM_MAX; i++)
	{
		if (slist[i].module==EXCLOG_MODULE_NONE)
		{
			slist[i].module=ereq->module;
			slist[i].level=ereq->level;
			slist[i].sub_f=ereq->sub_f;
			slist_num++;
		} else if (i==EXCLOG_SUBSCRIBE_NUM_MAX-1)
		{
			DEBUG_SELF("subscribe fail,max num=%d.", EXCLOG_SUBSCRIBE_NUM_MAX);
			return -1;
		}
	}

	DBG_SELF("excLOG_subscribe success.");
	return 0;
}
/********************************************************************************************
 * Function: excLOG_level_set()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:set log_level.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ new_level:IN,new log level to set.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int excLOG_level_set(int new_level)
{
	log_level=new_level;
	DBG_SELF("set log_level to %d.",new_level);
	return 0;
}
/********************************************************************************************
 * Function: excLOG_level_get()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:get current log level.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Parameters:NULL.
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Return :
 * 		0~7:current log level.
 ********************************************************************************************/
int  excLOG_level_get(void)
{
	return log_level;
}

