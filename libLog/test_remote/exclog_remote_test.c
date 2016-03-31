/*******************************************************************************************
 * 					Filename: exclog_remote_test.c
********************************************************************************************
 * Description:
 * 		this is an test file for EXCLOG_2_REMOTE. 
 * Version:
 * 	    V_0.1 Aug-12-2010
 * Copyright:
 * 		 HISOME <http://www.hisome.com>
 * Author: 
 * 		 renhw <renhw@hisome.com>
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
static void usage(const char *pname)
{
	printf("Usage:\n"
			"%s -i 192.168.9.161 -n 2\n"		
			"-i: remote IP address\n"
			"-n: send num(must >0) \n",pname);	
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
int main(int argc,char *argv[])
{		
	signal(SIGINT,_signal_user);

	int num=0;
	int ch;
	char *ip=NULL;
	
	while ((ch=getopt(argc, argv, "i:n:"))!=-1)
	{
		switch (ch)
		{
		case 'n':
			num=atoi(optarg);
			break;
		case 'i':
			ip=optarg;
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
	
	if(num==0 || ip==NULL)
	{
		usage(argv[0]);
	}
		
	init_exclog_remote_t init;
	memset(&init,0,sizeof(init));
	init.log_level=7;
	init.remotePort=514;
	init.be_syslog=0;
	init.be_klog=0;
	strncpy(init.remoteIP,ip,sizeof(init.remoteIP)-1);
	
	int ret=init_exclog_network(&init);
	if(ret!=0)
	{
		printf("init_exclog_network fail.\n");
		return -1;
	}
	
	int i=0;
	int total=0;
	while (exit_ok)
	{
		for (i=0; i<10; i++)
		{
			excLOG_DEBUG("remote excLOG_DEBUG test.");
			excLOG_INFO("remote excLOG_INFO test");
			excLOG_NOTICE("remote excLOG_NOTICE test.");
			excLOG_WARNING("remote excLOG_WARNING test.");
			excLOG_ERR("remote excLOG_ERR test.");
			excLOG_CRIT("remote excLOG_CRIT test.");
			excLOG_ALERT("remote excLOG_ALERT test.");
			excLOG_EMERG("remote excLOG_EMERG test.");
			total+=8;
		}
		sleep(1);		
	}
	printf("finish.\n");
	
	printf("waiting...\n");
	while (exit_ok)
	{
		sleep(1);
	}
	
	deinit_exclog_network();
	printf("remote_total=%d.\n",total);

	return 0;
}
