/*******************************************************************************************
 * 					Filename: exclog_query_test.c
 ********************************************************************************************
 * Description:
 * 		this is an test file for query log. 
 * Version:
 * 	    V_0.1 Aug-16-2010
 * Copyright:
 * 		 HISOME <http://www.hisome.com>
 * Author: 
 * History:
 ********************************************************************************************/
#include "exclog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <signal.h>
#include <ctype.h>

static int exit_ok=1;

static unsigned long _exclog_get_level(char *level);
static unsigned long _exclog_get_module(char *module);

static void usage(const char *pname)
{
	printf("Usage:\n"
		"%s  -p /mnt/exclog -l 7 -m all -s 2010-08-16_12:00:00 -e 2010-08-16_14:00:00\n"
		"-p: log file path for init_exclog_local() \n"
		"-l: log level [0,7] \n"
		"-m: log module[all,app,core,kernel,syslog]\n"
		"-s: start time\n"
		"-e: end time \n", pname);
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
	char *stime=NULL;
	char *etime=NULL;
	char *level=NULL;
	char *module=NULL;

	exclog_query_req_t req;
	memset(&req, 0, sizeof(req));

	int ch;
	while ((ch=getopt(argc, argv, "p:l:m:s:e:"))!=-1)
	{
		switch (ch)
		{
		case 'p':
			path=optarg;
			break;
		case 'l':
			level=optarg;
			break;
		case 'm':
			module=optarg;
			break;
		case 's':
			stime=optarg;
			break;
		case 'e':
			etime=optarg;
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

	if (stime==NULL || etime==NULL || module==NULL || level==NULL || path==NULL)
	{
		usage(argv[0]);
	}

	exclog_datetime_t st, et;
	sscanf(stime, "%04d-%02d-%02d_%02d:%02d:%02d", &st.year, &st.month, &st.day, &st.hour, &st.minute, &st.second);
	sscanf(etime, "%04d-%02d-%02d_%02d:%02d:%02d", &et.year, &et.month, &et.day, &et.hour, &et.minute, &et.second);
	req.stime=st;
	req.etime=et;

	req.level=_exclog_get_level(level);
	req.module=_exclog_get_module(module);

	int ret=0;

	init_exclog_local_t init;
	memset(&init, 0, sizeof(init));
	strncpy(init.path, path,sizeof(init.path)-1);
	init.num=6;
	init.size=1048576;
	ret=init_exclog_local(&init);
	if (ret!=0)
	{
		printf("init_exclog fail.\n");
		return -1;
	}

	ret=excLOG_query(&req);
	if (1==ret)
	{
		printf("device busy,please query again later.");
		return 0;
	}

	exclog_query_rps_t *rps=NULL, *tmp=NULL;

	unsigned long int i=0;
	unsigned long int j=0;

	printf("Query result:\n");
	while (exit_ok)
	{
		printf("Read time=%lu.\n", ++j);
		rps=NULL;
		ret=excLOG_read(&rps);
		if (-1==ret)
		{
			printf("Query failed.\n");
			break;
		} else if (0==ret)
		{
			printf("Query finished.\n");
			break;
		} else
		{
			tmp=rps;
			char time_str[32]= { '\0' };
			while (tmp)
			{
				snprintf(time_str,sizeof(time_str)-1, "%04d-%02d-%02d %02d:%02d:%02d", tmp->tick.year, tmp->tick.month, tmp->tick.day,
						tmp->tick.hour, tmp->tick.minute, tmp->tick.second);
				printf("%lu.%s <%lu>%lu--->%s", ++i, time_str, tmp->level, tmp->module, tmp->data);

				rps=rps->next;
				tmp=rps;
			}
		}
	}
	excLOG_close();

	while(exit_ok)
	{
		sleep(1);
	}
	return 0;
}
/********************************************************************************************
 * Function: _exclog_level_str_2_hex()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:transfer level string to hex.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ level:IN,log level string.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :log level in hex.
 ********************************************************************************************/
static unsigned long _exclog_get_level(char *level)
{
	if (!strcmp(level, "0"))
	{
		return EXCLOG_LEVEL_0;
	} else if (!strcmp(level, "1"))
	{
		return EXCLOG_LEVEL_1;
	} else if (!strcmp(level, "2"))
	{
		return EXCLOG_LEVEL_2;
	} else if (!strcmp(level, "3"))
	{
		return EXCLOG_LEVEL_3;
	} else if (!strcmp(level, "4"))
	{
		return EXCLOG_LEVEL_4;
	} else if (!strcmp(level, "5"))
	{
		return EXCLOG_LEVEL_5;
	} else if (!strcmp(level, "6"))
	{
		return EXCLOG_LEVEL_6;
	} else if (!strcmp(level, "7"))
	{
		return EXCLOG_LEVEL_7;
	} else
	{
		return -1;
	}
}
static unsigned long _exclog_get_module(char *module)
{
	if (!strcmp(module, "kernel"))
	{
		return EXCLOG_MODULE_KERNEL;
	} 
	// else if (!strcmp(module, "ramdisk"))
	// {
	// 	return EXCLOG_MODULE_RAMDISK;
	// } 
	else if (!strcmp(module, "syslog"))
	{
		return EXCLOG_MODULE_SYSLOG;
	} else if (!strcmp(module, "libhxSDK"))
	{
		return EXCLOG_MODULE_HXSDK;
	} else if (!strcmp(module, "libxeCEO"))
	{
		return EXCLOG_MODULE_LIB_CEO;
	} else if (!strcmp(module, "libxeAA"))
	{
		return EXCLOG_MODULE_LIB_AA;
	} else if (!strcmp(module, "libxeSOE"))
	{
		return EXCLOG_MODULE_LIB_SOE;
	} else if (!strcmp(module, "libxeSAP"))
	{
		return EXCLOG_MODULE_LIB_SAP;
	} 
	// else if (!strcmp(module, "libxeSUCK"))
	// {
	// 	return EXCLOG_MODULE_LIB_SUCK;
	// }
	else if (!strcmp(module, "libxePTZ"))
	{
		return EXCLOG_MODULE_LIB_PTZ;
	} else if (!strcmp(module, "libexcLOG"))
	{
		return EXCLOG_MODULE_LIB_LOG;
	} else if (!strcmp(module, "libxePM"))
	{
		return EXCLOG_MODULE_LIB_PM;
	} else if (!strcmp(module, "libxeSIS"))
	{
		return EXCLOG_MODULE_LIB_SIS;
	} else if (!strcmp(module, "libxeDavinci"))
	{
		return EXCLOG_MODULE_LIB_DAVINCI;
	} 
	// else if (!strcmp(module, "libxeCONF"))
	// {
	// 	return EXCLOG_MODULE_LIB_CONF;
	// } 
	else if (!strcmp(module, "app_S2506A"))
	{
		return EXCLOG_MODULE_APP_S2506A;
	} else if (!strcmp(module, "app_SIPUA"))
	{
		return EXCLOG_MODULE_APP_SIPUA;
	} else if (!strcmp(module, "app_hxGUI"))
	{
		return EXCLOG_MODULE_APP_HXGUI;
	} else if (!strcmp(module, "app_hxWEB"))
	{
		return EXCLOG_MODULE_APP_HXWEB;
	} else if (!strcmp(module, "app_other"))
	{
		return EXCLOG_MODULE_APP_OTHER;
	} else if (!strcmp(module, "app"))
	{
		return EXCLOG_MODULE_APP;
	} else if (!strcmp(module, "all"))
	{
		return EXCLOG_MODULE_ALL;
	} else
	{
		return -1;
	}
}
