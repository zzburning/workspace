#include "exclog.h"
#include "lpconfig.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
//#define CONFIG_USE_EXTERNAL_EXCLOG 1
//#define  EXCLOG_2_LOCAL 1  //#ifdef
//#define CONFIG_USE_EXTERNAL_EXCLOG 1



int main(void)
{

//#ifdef CONFIG_USE_EXTERNAL_EXCLOG

	init_exclog_local_t init;
	int level, filesize, filenum, port;
	char status[16], log_path[64], log_server[32];
	
	int ret = 0;
	char *cfg_file = "logconfig.ini";
	LpConfig *lcp = lp_config_new(cfg_file);

	//lcp=lp_config_new(cfile_log);
	if(lcp==NULL){
		printf("open(%s) FAIL.", cfg_file);///excLOG_ERR
		return -1;
	}

	strncpy(status, lp_config_get_string(lcp, "logserver", "STATUS", "disable"), sizeof(status)-1);
	level = lp_config_get_int(lcp, "logserver", "LEVEL", 7);
	filenum = lp_config_get_int(lcp, "logserver", "LOG_FILENUM", 1);
	filesize = lp_config_get_int(lcp, "logserver", "LOG_FILESIZE", 8*1024);//(MB)

	strncpy(log_path, lp_config_get_string(lcp, "logserver", "PATH", "log"), sizeof(log_path)-1);

	strncpy(log_server, lp_config_get_string(lcp, "logserver", "REMOTEIP", "127.0.0.1"), sizeof(log_server)-1);

	port = lp_config_get_int(lcp, "logserver", "REMOTEPORT", 514);


	memset(&init, 0, sizeof(init));

	init.local_port=port;
	init.be_syslog=0;//1
	init.be_klog=0;  //1
	if(!strcmp(status, "enable"))
	{
		init.log_level=level;
	}
	else
	{
		init.log_level = 0;
	}
	strcpy(init.path, log_path);

	init.num=filenum;
	init.size=filesize*1024;
	init.msg2stdout = 1;//0
	init.msg2stderr = 1;

#ifdef EXCLOG_2_LOCAL 
	ret=init_exclog_local(&init);
	if(ret != 0)
	{
		printf("ret =%d init_exclog local fail.\n", ret);
                perror("init_exclog local\n");
		goto log_out;
	}

	dprintf("init_exclog local success.\n");
#endif

     do {
         sleep(100);
     } while(1);

log_out:
     return 0;
}

