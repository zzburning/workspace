/*******************************************************************************************
 * 					Filename: exclog_local_test.c
 ********************************************************************************************
 * Description:
 * 		this is an test file for EXCLOG_2_LOCAL. 
 * Version:
 * 	    V_0.1 Aug-12-2010
 * Copyright:
 * Author: 
 * History:
 * 		 V_0.1 Initial version of this code.
 ********************************************************************************************/
#include "exclog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <ctype.h>

static int exit_ok=1;

static int __subscribe_callback(exclog_subscribe_rps_t *rps);

static void usage(const char *pname)
{
	printf("Usage:\n"
		"%s -p /mnt/log -n 3 -s 512 \n"
		"-p: log file path\n"
		"-n: log file num \n"
		"-s: log file size (KByte)[512,1024]\n", pname);
	exit(-1);
}

static void _signal_user(int signum)
{
	printf("signum=%d\n", signum);

	switch (signum)
	{
	case SIGHUP:
	case SIGINT:
		/*Ctrl^C in terminal*/
		break;
	case SIGTERM:
		/*kill by shell*/
		break;
	}

	exit_ok=0;

	return;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, _signal_user);

	char *path=NULL;
	int size=0;
	int num=0;
	int ch=0;

	while ((ch=getopt(argc, argv, "p:n:s:"))!=-1)
	{
		switch (ch)
		{
		case 'p':
			path=optarg;
			break;
		case 'n':
			num=atoi(optarg);
			break;
		case 's':
			size=atoi(optarg);
			break;
		case '?':
			if (isprint(optopt))
				fprintf(stderr, "%s: Unknown option '-%c'.\n",argv[0], optopt);
			else
				fprintf(stderr,"%s: Unknown option character '\\x%x'.\n",argv[0],optopt);
			usage(argv[0]);
		case ':':
			fprintf(stderr,"%s: Option '-%c' requires an argument.\n",argv[0],optopt);
			usage(argv[0]);
		default:
			usage(argv[0]);
		}
	}

	if (path==NULL || size==0 || num==0)
	{
		usage(argv[0]);
	}

	init_exclog_local_t init;
	memset(&init, 0, sizeof(init));
	init.local_port=514;
	init.be_syslog=0;
	init.be_klog=0;
	init.log_level=7;
	strncpy(init.path, path,sizeof(init.path)-1);
	init.num=num;
	init.size=size*1024;
	init.msg2stdout=1;

	int ret=init_exclog_local(&init);
	if (ret!=0)
	{
		printf("init_exclog fail.\n");
		return -1;
	}

	exclog_subscribe_req_t req;
	req.level=EXCLOG_LEVEL_7;
	req.module=EXCLOG_MODULE_ALL;
	req.sub_f=&__subscribe_callback;

	ret=excLOG_subscribe(&req);
	if (ret!=0)
	{
		printf("excLOG_subscribe fail.\n");
		return -1;
	}

	int total=0;
	while (exit_ok)
	{
		excLOG_DEBUG("local excLOG_DEBUG test.");
		excLOG_INFO("local excLOG_INFO test.");
		excLOG_NOTICE("local excLOG_NOTICE test.");
		excLOG_WARNING("local excLOG_WARNING test.");
		excLOG_ERR("local excLOG_ERR test.");
		excLOG_CRIT("local excLOG_CRIT test.");
		excLOG_ALERT("local excLOG_ALERT test.");
		excLOG_EMERG("local excLOG_EMERG test.");
		total+=8;
		sleep(1);
	}

	deinit_exclog_local();
	printf("local total=%d.\n",total);

	return 0;
}
static int __subscribe_callback(exclog_subscribe_rps_t *rps)
{
	//printf("subscribe callback:%s.\n", rps->message);

	return 0;
}
