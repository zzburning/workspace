/*****************************************************************		
 * 		Filename: history_stream.c
 *****************************************************************
 * Description:
 *		at_suite module history_stream file,this is main file 
 * Version:
 *		V_0.1	Nov-12-2008
 * Copyright:
 *		HISOME <http://www.hisome.com.>
 * Author:
 *		yangsz <yangsz@hisome.com.>
 * History:
 * 		Sep-17-2010 renyi<renyi@hisome.com>
 * 			V_0.2 add threads queryfile ,loops queryfile and playback file
 * 		Nov-12-2008 yangsz<yangsz@hisome.com.>
 * 			V_0.1 initial version of this file;
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ats_hty_stream.h"

static pthread_mutex_t ls_mutex = PTHREAD_MUTEX_INITIALIZER;
FILE *fp_report_log = NULL;


static int __history_stream_init(const char *cfile)
{
	DBG(MODNAME ": init with cfile=%s.", cfile);
	int ret;
	ret= read_conf_para(cfile);
	if(ret<0)
	{
		printf("init history stream fail\n");
	}

	static char *report_log_file = "report_log_file.txt";
	fp_report_log = fopen(report_log_file, "a+");	//all run message save in it;
	if(NULL == fp_report_log)
	{
		xeLOG_ERR("open report log file FAIL!!!");
		return -1;
	}
	return 0;
}


static int ___run_queryfile(hty_thread_t *arg)
{
	int chaID, ret, fail_reason,loop;
	for (loop=0; loop<query_arg.loop; loop++) {
		for (chaID = target_arg.first_cha; chaID <= target_arg.last_cha; chaID++) {
			// chaID = 0;
			hx_target_t tID;
			char target[64];

			snprintf(target, sizeof(target)-1, "%s:%d", target_arg.identity,chaID);
			tID = hx_open(target, target_arg.username, target_arg.pwd, 0);
			if (tID < 0) {
				//TODO:
				continue;
			}
			fprintf(arg->fp,"query channel %2d from %04d-%02d-%02d %02d:%02d:%02d to %04d-%02d-%02d %02d:%02d:%02d\n", chaID,
					query_arg.start.year, query_arg.start.mon, query_arg.start.day,
					query_arg.start.hour, query_arg.start.min, query_arg.start.sec,
					query_arg.end.year, query_arg.end.mon, query_arg.end.day,
					query_arg.end.hour, query_arg.end.min, query_arg.end.sec);
			usleep(100);
			ret = hty_queryfile(tID, &query_arg, &fail_reason,arg);

			if (ret < 0) {
				printf("query fail. fail_reason:%s\n", hx_get_strerror(fail_reason));
			} else {
				printf("query file success.\n");
			}
			hx_close(tID);
		}
	}
	return 0;
}

static int ___run_download(hty_thread_t *arg)
{
	int chaID, ret, fail_reason,loop;
	
	for (loop=0; loop<download_arg.loop; loop++) {
		for (chaID = target_arg.first_cha; chaID <= target_arg.last_cha; chaID++) {
			// chaID = 0;
			hx_target_t tID;
			char target[64];

			snprintf(target, sizeof(target), "%s:%d", target_arg.identity,
					chaID);
			tID = hx_open(target, target_arg.username, target_arg.pwd, 0);
			if (tID < 0) {
				//TODO:
				continue;
			}

			download_arg.chaID = chaID;
			fprintf(arg->fp,"download channel %2d from %04d-%02d-%02d %02d:%02d:%02d to %04d-%02d-%02d %02d:%02d:%02d \n", chaID,
					download_arg.start.year, download_arg.start.mon, download_arg.start.day,
					download_arg.start.hour, download_arg.start.min, download_arg.start.sec,
					download_arg.end.year, download_arg.end.mon, download_arg.end.day,
					download_arg.end.hour, download_arg.end.min, download_arg.end.sec);
			
			ret = hty_download(tID, &download_arg, &fail_reason,arg);
			if (ret < 0) {
				printf("download fail. fail_reason:%s\n", hx_get_strerror(fail_reason));
			} else {
				printf("download file success.\n");
			}
			hx_close(tID);
		}
	}
	return 0;
}

int __queryfile()
{
	int chaID = 0;
	int ret;
	
	hx_target_t tID;
	char target[64];

	snprintf(target, sizeof(target)-1, "%s:%d", target_arg.identity,chaID);
	tID = hx_open(target, target_arg.username, target_arg.pwd, 0);
	if (tID < 0) {
		//TODO:
	}
	fprintf(arg->fp,"query channel %2d from %04d-%02d-%02d %02d:%02d:%02d to %04d-%02d-%02d %02d:%02d:%02d\n", chaID,
			query_arg.start.year, query_arg.start.mon, query_arg.start.day,
			query_arg.start.hour, query_arg.start.min, query_arg.start.sec,
			query_arg.end.year, query_arg.end.mon, query_arg.end.day,
			query_arg.end.hour, query_arg.end.min, query_arg.end.sec);
	usleep(100);

	ret = hty_queryfile(tID, &query_arg, &fail_reason,arg);

	if (ret < 0) {
		printf("query fail. fail_reason:%s\n", hx_get_strerror(fail_reason));
	} else {
		printf("query file success.\n");
	}
}

struct __playback_file_struct
{
	char identity[32];
} __playback_file_user[2]={};

static int __playback_file_cb(int eID,void *user,void *ep)
{
	struct __playback_file_struct * __pf_p=user;
	printf("%s: get eID=%s(%d)\n", __pf_p->identity, hx_streID(eID, NULL, 0), eID);
	return 0;
}

static int __run_playback_file()
{
	int chaID;
	char target[64];
	hx_target_t ftID, ptID;
	int type;
	int ret_s;
	// int loop;


	// for (loop=0; loop<playback_arg.loop; loop++) {
		// for (chaID=target_arg.first_cha; chaID<=target_arg.last_cha; chaID++) {
			chaID = 0;
			sprintf(target, "%s:%d", target_arg.identity, chaID);
			strcpy(__playback_file_user[0].identity, target);

			ftID=hx_open(target, NULL, NULL, HX_TARGET_TYPE_CHA_ENC);
			if (ftID==-1) {
				printf("hx_open  %s HX_TARGET_TYPE_CHA_ENC fail!\n", target);
				goto ERR;
			}

			sprintf(target, "%s:%d", playback_arg.mipaddr,playback_arg.mchaid);
			strcpy(__playback_file_user[1].identity, target);

			ptID=hx_open(target, NULL, NULL, HX_TARGET_TYPE_CHA_DEC);
			if (ptID==-1) {
				printf("hx_open %s HX_TARGET_TYPE_CHA_DEC fail!\n", target);
				goto ERR;
			}


			char fname[64];
			sprintf(fname, "DUR:%d-%d-%d_%d:%d:%d_2_%d-%d-%d_%d:%d:%d",
				playback_arg.start.year, playback_arg.start.mon, playback_arg.start.day, 
				playback_arg.start.hour, playback_arg.start.min, playback_arg.start.sec, 
				playback_arg.end.year, playback_arg.end.mon, playback_arg.end.day, 
				playback_arg.end.hour, playback_arg.end.min, playback_arg.end.sec);

			if (!strcmp(playback_arg.type, "alarm")) {
				type=HX_FILE_TYPE_ALARM;
			} else if (!strcmp(playback_arg.type, "time")) {
				type=HX_FILE_TYPE_TIME;
			} else if (!strcmp(playback_arg.type, "manual")) {
				type=HX_FILE_TYPE_MANUAL;
			}


			hx_stream_desc_t fsd, psd;

			memset(&fsd, 0, sizeof(fsd));
 			fsd.mode = HX_SDESC_MODE_PORT;
			fsd.proto = HX_SDESC_PROTO_DEC;
			// fsd.proto = HX_SDESC_PROTO_TCP;
			fsd.async_event_f = __playback_file_cb;
			fsd.async_event_user = &__playback_file_user[0];
			fsd.hx_file_type=type;
			fsd.stype=playback_arg.stype;
			// fsd.smux=HX_STREAM_MUX_HTTP;

			memset(&psd, 0, sizeof(psd));
 			psd.mode = HX_SDESC_MODE_PORT;
			psd.proto = HX_SDESC_PROTO_DEC;			
			// fsd.proto = HX_SDESC_PROTO_TCP;
			psd.async_event_f = __playback_file_cb;
			psd.async_event_user = &__playback_file_user[1];
			psd.hx_file_type=type;

			ret_s=hx_file_setopt(ftID, HX_FILE_OPT_START, NULL);
			if(ret_s==-1){
				printf("HX_FILE_OPT_START fail.\n");
				goto ERR;
			}

			hx_file_t fID=-1;
			hx_stream_t sID=-1;


			hx_file_playback(ftID, fname, &fsd, ptID, &psd, &fID, &sID);
			if (fID==-1) {
				printf("open file %s fail!\n", fname);
				goto ERR;
			// } else if (sID==-1) {
			// 	printf("open stream for %s file fail!\n", fname);
			// 	goto ERR;
			} else {
				printf("FILE:\t\t%s:%d  --->  %s:%d\n", fsd.addr_local,
						fsd.port_local, fsd.addr_remote, fsd.port_remote);
				if (fsd.addr_local)
					free(fsd.addr_local);
				if (fsd.addr_remote)
					free(fsd.addr_remote);
				printf("PLAYBACK:\t%s:%d  <---  %s:%d\n", psd.addr_local,
						psd.port_local, psd.addr_remote, psd.port_remote);
				if (psd.addr_remote)
					free(psd.addr_remote);
				if (psd.addr_local)
					free(psd.addr_local);
			}
			// wait x second
			sleep(10);
			ret_s = hx_file_setopt(ftID, HX_FILE_OPT_STOP, NULL);
			// if(ret_s==-1){
			// 	printf("HX_FILE_OPT_STOP fail.\n");
			// 	goto ERR;
			// }	
			// // ret=playback_file_opt(&playback_arg);
			// if (ret==-1) {
			// 	printf("playback file opt fail!\n");
			// 	return -1;
			// }

			
			if (fID!=-1) {
				printf("hx_file_close-->%d", fID);
				hx_file_close(fID);
			}
			if (sID!=-1) {
				printf("hx_stream_close-->%d,sID", sID);
				hx_stream_close(sID);
			}
			hx_close(ftID);
			hx_close(ptID);
		// }//end of channels
	// }//end of loops
			sleep(20);
			report_LOG("================================================");
			report_LOG("\tplay back file over");
		
			return 0;

	ERR:
		if (fID!=-1) {
			printf("hx_file_close-->%d", fID);
			hx_file_close(fID);
		}
		if (sID!=-1) {
			printf("hx_stream_close-->%d,sID", sID);
			hx_stream_close(sID);
		}
		if (ftID != -1)
			hx_close(ftID);
		if (ptID != -1)
			hx_close(ptID);

		report_LOG("================================================");
		report_LOG("\tplay back file fail");
		return -1;
}

static void * thread_run_test(target_arg_t *arg)
{
	DBG(MODNAME ": start running......");

	if (!ats_qry_enable && !ats_dl_enable && !ats_pb_enable) {
		xeLOG_INFO(MODNAME ": nothing to do.");
		return 0;
	}
	static int thread_no=0;
	int ret;
	hty_thread_t my_thread;
	memset(&my_thread, 0, sizeof(my_thread));
	pthread_mutex_lock(&ls_mutex);
	thread_no++;
	my_thread.thread_no=thread_no;
	pthread_mutex_unlock(&ls_mutex);

	char filename[64];
	snprintf(filename, sizeof(filename)-1, "%s/thread_%d.txt", arg->sdp,my_thread.thread_no);
	
	my_thread.fp=fopen(filename, "a+");
	if (my_thread.fp == NULL) {
		my_thread.my_errno = errno;
		xeLOG_ERR("error happen when open file,errno=%d,strerror=%s",my_thread.my_errno, strerror(my_thread.my_errno));
		return NULL;
	}
	int loop;
	for(loop=1;loop<=arg->loop;loop++)
	{

		if(ats_qry_enable) //query option is active
		{
			ret=___run_queryfile(&my_thread);
			if(ret<0)
			{
				fprintf(my_thread.fp,"loop_%d:error happen,errno=%d,strerror=%s\n",arg->loop,my_thread.my_errno, strerror(my_thread.my_errno));
			} else {
				fprintf(my_thread.fp,"loop_%d: thread_%d is run success\n",loop,my_thread.thread_no);
			}
		}

		if(ats_dl_enable)
		{
			ret=___run_download(&my_thread);
			if(ret<0)
			{
				fprintf(my_thread.fp,"loop_%d:error happen,errno=%d,strerror=%s\n",arg->loop,my_thread.my_errno, strerror(my_thread.my_errno));
			} else {
				fprintf(my_thread.fp,"loop_%d:thread_%d  is run success\n",loop,thread_no);
			}
		}
		if(ats_pb_enable)
		{
			ret=__run_playback_file();
			if(ret==0)
			{
				printf("play back file success\n");
			}else{
				printf("play back file fail\n");
			}
		}
	}
		fprintf(my_thread.fp,MODNAME ": it's over\n");
		fclose(my_thread.fp);
		return NULL;
}

static int __history_stream_run(void)
{
	//create test result dir 
	char crd[128];
	snprintf(crd,sizeof(crd)-1,"rm -rf %s;mkdir -p %s",target_arg.sdp,target_arg.sdp);
	system(crd);
	int thread_cnt=target_arg.thread;
	int i,ret;
	pthread_t *pID=calloc(thread_cnt,sizeof(pthread_t));
	
	for(i=0;i<thread_cnt;i++)
	{
		ret=pthread_create(&pID[i],NULL,(void *)thread_run_test,&target_arg);
		if(ret<0)
		{
			printf("create thread fail\n" );
			return -1;
		}
	}
	for(i=0;i<thread_cnt;i++)
	{
		pthread_join(pID[i],NULL);
	}
	free(pID);
	return 0;
}

static void __history_stream_deinit(void)
{
	DBG(MODNAME ": de-init called.");
	free_conf_para();
	if(fp_report_log)
		fclose(fp_report_log);
}


/*************************************************************************
 * ats-core will load mod_export symble, so we must declare it as this.
 ************************************************************************/
ats_module_t mod_export = {
	.name = MODNAME,
	.init_f = __history_stream_init,
	.run_f = __history_stream_run,
	.deinit_f = __history_stream_deinit,
};

