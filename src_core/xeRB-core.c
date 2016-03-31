/*		Filename: xeRB-core.c
*************************************************
* Description:
*		xeRB  core main source file.
* Version:
*		V_0.1	Mar-27-2016
* Copyright:
*		xxx <www.xxx.com.>
* Author:
*		xxx <xxx@xxx.com.>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <linux/watchdog.h> 

#include <xeSOE.h>
#include <xeSAP.h>
#include <xeCEO.h>
#include <xeAA.h>
#include <hx_package.h>
#include <xelog.h>
#include <CORE.h>
#include <xeWDG.h>

#ifdef MEMWATCH
#include <memwatch.h>
#endif

int be_syslog;
#define XECORE_SIGNAL_HALT	    (501)

static xeWDG_ID_t wdgID = -1;

char gDir_etc[64];
char gDir_home[64];

static int __sig_handle_calling=0;

static int _log2stderr = 0;
static int _be_daemon = 0;

char core_bin_name[64]="";

struct my_app_struct{
	char *appname;
	pid_t appid;
	char *argv[12];
}__myapp[]=
{
#if 0
	/* ./xeRB.bin -d DEV://ttyS1 -b 115200 -a 127.0.0.1 -i 7 -l 6 */
	{
		.appname="/home/bin/xeRB.bin",
		.appid=0,
		.argv[0]="xeRB.bin",
		.argv[1]="-d",
		.argv[2]="DEV://ttyS1",
		.argv[3]="-b",
		.argv[4]="115200",
		.argv[5]="-a",
		.argv[6]="127.0.0.1",
		.argv[7]="-i",
		.argv[8]="7",
		.argv[9]="-l",
		.argv[10]="6",
		.argv[11]=NULL,
	},
	/* web server */
	{
		.appname="/home/bin/boa.bin",
		.appid=1,
		.argv[0]="boa.bin",
		.argv[1]="-d",
		.argv[2]=NULL,
	},
#endif	
};

static int __spawn_my_app(void)
{
	pid_t appid;
	int status,ret,p;
	int i=0;
	while(0x20080427)
	{
		for(p=0;p<sizeof(__myapp)/sizeof(__myapp[0]);p++)
		{
			if(!__sig_handle_calling && __myapp[p].appid==0)
			{
				appid = vfork();
				if(appid==-1)
				{
					xeLOG_ERR("vfork fail, %s",strerror(errno));
				}else if(appid==0)
				{
					for(i=3; i<256; i++)
					{
						close(i);
					}
					//in child
					ret = execv(__myapp[p].appname,__myapp[p].argv);
					if(ret==-1){
						xeLOG_ERR("execl(%s) fail, %s",__myapp[p].appname,strerror(errno));
						exit(-1);
					}
				}else{
					//in parent
					__myapp[p].appid = appid;
				}
			}
		}
		
#if 0
		if(wdgID!=-1)
			xeWDG_app_close(wdgID);
		wdgID = -1;
		
		ret = __call_buzzer();
		if(ret == -1)
		{
			xeLOG_ERR("fpga_buzzer startup fail.");
			exit(-1);
		}
#endif
		appid = wait(&status);

		for(p=0;p<sizeof(__myapp)/sizeof(__myapp[0]);p++){		
			if(appid==__myapp[p].appid){
				if(WIFEXITED(status)){
					xeLOG_ERR("%s exit normally, %d, respawn it.",__myapp[p].appname,WEXITSTATUS(status));
				}else{
					xeLOG_ERR("%s exit abnormally, signal %d, respawn it.",__myapp[p].appname,WTERMSIG(status));
				}

				__myapp[p].appid = 0;
				sleep(1);
				continue;
			}
		}
	}

	return 0;
}

int __kill_my_app(void)
{
	printf("\nQuit from %s ... ...\n","core");
	xeWDG_app_t wdgkillApp = {.name="CoreKill",.interval=60};
#ifndef NFS_DEBUG_MODE
	xeWDG_app_open(&wdgkillApp,&wdgID);
#endif
	/*fpga_led_set(FPGA_LED_POWER,FPGA_LED_RED);*/
	//_deinit_base_lib_xeAC51();

	printf("%s\t...","RB"); 
	rectask_produce_stop();
	__deinit_recording();
	printf("Stopped.\n");

	printf("%s\t...","soe"); 
	xesoe_deinit();
	printf("Stopped.\n");

	//printf("%s\t...\t","sap"); 
	//xesap_deinit();
	//printf("Stopped.\n");

	//printf("%s\t...","aa"); 
	//xeaa_deinit();
	//xeaa_halt();
	//printf("Stopped.\n");

	//printf("%s\t...","ceo"); 
	//xeceo_deinit();
	//printf("Stopped.\n");

	int p;
	for(p=0;p<sizeof(__myapp)/sizeof(__myapp[0]);p++)
	{
		if(__myapp[p].appid!=0)
		{
			DBG("kill %s.",__myapp[p].appname);
			kill(__myapp[p].appid, SIGTERM);
		}
	}
	if(wdgID!=-1)
		xeWDG_app_close(wdgID);	
	return 0;
}

static void *__update_kill_all_thread(void *arg)
{
	int ret=0;
	pthread_detach(pthread_self());

	while(wdgID != -1)
	{
		usleep(500000);
	}
//	soe_CVA_setreset();
	_xeWDG_drv_stop();
	exit(-1);
	//pthread_exit(NULL);
}

void __my_sig_handle(int signum)
{
	int ret;
	pthread_t pid;
	if(__sig_handle_calling)
		return;

	__sig_handle_calling = 1;
	xeLOG_ERR("get signal %d.\n",signum);
	if (signum==11)
	{
		int i =0;
		printf("RB-S2012 crashed\n");
		for (i=0; i<10;i++)
			printf("*\n");
		__set_buzzer(1);
		sleep(1);
		__set_buzzer(0);
		//set OSD system crash.
	}

	if(signum == 10)//SIGUSR1
	{
		if((ret=pthread_create(&pid, NULL,__update_kill_all_thread,NULL)) != 0)
		{
			xeLOG_ERR("pthread_create() fail, %s",strerror(ret));
			exit(-1);
		}
		return;
	}

	__kill_my_app();

	if(signum==XECORE_SIGNAL_HALT)
	{
		sync();
		xeLOG_INFO("start halt device...");
		usleep(200000);
	}
	if(signum!=499)
		sync();
	sleep(2);
	xeWDG_drv_reboot(); 
	exit(-1);
}

static int init_core_log(const char *cfile_log)/*xeceo.host.conf*/
{
	int ret = 0;

	LpConfig *lcp=NULL;

#ifdef CONFIG_USE_EXTERNAL_XELOG

	init_xelog_local_t init;
	int level, filesize, filenum, port;
	char status[16], log_path[64], log_server[32];

	lcp=lp_config_new(cfile_log);/**parse the file cfile_log,and save value to lcp<huwb@xxx.com>*/
	if(lcp==NULL){
		xeLOG_ERR("open(%s) FAIL.", cfile_log);
		return -1;
	}

	strncpy(status, lp_config_get_string(lcp, "logserver", "STATUS", "disable"), sizeof(status)-1);
	level = lp_config_get_int(lcp, "logserver", "LEVEL", 5);
	filenum = lp_config_get_int(lcp, "logserver", "LOG_FILENUM", 1);
	filesize = lp_config_get_int(lcp, "logserver", "LOG_FILESIZE", 512);//(MB)

	strncpy(log_path, lp_config_get_string(lcp, "logserver", "PATH", "/home/log"), sizeof(log_path)-1);

	strncpy(log_server, lp_config_get_string(lcp, "logserver", "REMOTEIP", "127.0.0.1"), sizeof(log_server)-1);

	port = lp_config_get_int(lcp, "logserver", "REMOTEPORT", 514);


	memset(&init, 0, sizeof(init));

	init.local_port=port;
	init.be_syslog=1;
	init.be_klog=1;    
	if(strcmp(status,"disable"))
	{
		init.log_level=level;
	}
	else
	{
		init.log_level = 0;
	}
	strcpy(init.path, log_path);

	init.num=filenum;
	init.size=filesize*1024*1024;
	init.msg2stdout  = 0;
	if(_log2stderr)
		init.msg2stderr = 1;

#ifdef XELOG_2_LOCAL 

	ret=init_xelog_local(&init);
	if(ret != 0)
	{
		xeLOG_ERR("init_xelog local fail.\n");
		goto log_out;
	}

	dprintf("init_xelog local success.\n");
#endif

#ifdef XELOG_2_REMOTE
	ret = init_xelog_network(&init);
	if(ret != 0)
	{
		xeLOG_ERR("init_xelog network fail.\n");	//pthread_t wd_pid;
		//pthread_create(&wd_pid,NULL,__h3616_watchdog_thread,NULL);
		goto log_out;
	}
	dprintf("init_xelog local success.\n");
#endif


#endif

log_out:
	if(lcp)
		lp_config_destroy(lcp);

	return ret;
}


void exitCall ()
{
	return;
}

extern void xeCore_version_2_var_run(char *fname_p);

int main(int argc, char *argv[]){
	int ret;
#if 0
	xeWDG_drv_t drv_dog = { .interval = 0 };
	xeWDG_app_t wdgApp = {.name="CoreMain",.interval=100};
	//signal(11, signal_handler);
	//-------------------------------------------->
	int tuy;
	/***from 1 to 64 is signal*****/
	for( tuy = 1; tuy <=64; tuy++)
	{		
		if(tuy != 17)// && tuy != 11)
			signal(tuy, __my_sig_handle);
		/*if(tuy == 11)
		{
		signal(tuy, signal_handler);
		}*/
	}	
	//--------------------------------------------< 
#endif
	
	if(argc==2 && !strcasecmp(argv[1],"-v"))
	{
		printf("%s: %s(%s) V%d.%d.%d-%d %s TARGET_PLATFORM(%s) "
			"TARGET_BOARD_NAME(%s,%s) DATE: %s %s, GCC: %s\n", \
			argv[0],
			CONFIG_PRODUCT_MODEL,BUILD_TARGET, \
			VERSION_MAJOR,VERSION_MINOR,VERSION_REV,VERSION_BUILD_ID, \
			VERSION_EXTSTR, \
			CONFIG_PLATFORM,CONFIG_BOARD_NAME,CONFIG_BOARD_VERSION, \
			__DATE__,__TIME__,__VERSION__);
		exit(0);
	}
	if(argc==2 && !strcasecmp(argv[1],"-D"))
	{
		printf("start with debug mode.");
	}
	strncpy(core_bin_name,argv[0],sizeof(core_bin_name));
#if 0
	xeWDG_drv_startup(&drv_dog);
	/**
	* Jul-9-2011 added by wuhm<wuhm@xxx.com>
	* open logic watchdog here, just for core startup success;
	**/
	xeWDG_app_open(&wdgApp,&wdgID);

	snprintf(gDir_etc, sizeof(gDir_etc) - 1, "/xxx/etc");
	snprintf(gDir_home, sizeof(gDir_home) - 1, "/home");
	chdir(gDir_home);

	/* the start config files */
	char cmd[128];
	//snprintf(cmd, sizeof(cmd) - 1, "cp -f %s/*.conf %s/*.cfg %s/*.PRO %s/*.xml %s/", gDir_etc, gDir_etc, gDir_etc, gDir_etc, gDir_home);
	snprintf(cmd, sizeof(cmd) - 1, "cp -f %s/*.conf %s/*.cfg %s/*.PRO %s/", gDir_etc, gDir_etc, gDir_etc, gDir_home);
	system(cmd); 

	ret = hx_files_unpack_and_restore(EEPROM_DEV_NAME, gDir_home);	//read config file and ....current donn't know
	/* the end config files */

	if(!_log2stderr && _be_daemon)
	{
		daemon(1/*keep current wdir*/,0);
	}
#endif
	ret = init_core_log("xeceo.host.conf");
	if(ret < 0)
	{
		xeLOG_ERR("_core_log_config_load fail");
		return -1;
	}
	//xeLOG_NOTICE("\n\n\n");
	xeLOG_NOTICE("CORE startup, compiled on %s %s with GCC %s", \
		__DATE__, __TIME__, __VERSION__);

	xeCore_version_2_var_run("core");

#if 0
#ifndef NDEBUG
	hecp_debug(1);
#else 
	hecp_debug(0);
#endif

	if(__init_soe_CVA_get_enc_num() <= 0)
	{
		xeLOG_ERR("init_soe_CVA_get_enc_num fail ret=0.");
		return -1;
	}

	/*
	wdgApp.interval = 2000;
	xeWDG_app_upinterval(wdgID, &wdgApp);

	ret=xesap_main("xesap.DM_16CHD1.conf");
	if(ret==-1){
		xeLOG_ERR("xesap startup fail.");
		goto exit_err;
	}
	wdgApp.interval = 200;
	xeWDG_app_upinterval(wdgID, &wdgApp);

	usleep(1000);
	*/

	ret=xesoe_main(0, NULL);
	if(ret==-1){
		xeLOG_ERR("xesoe startup fail.");
		goto exit_err;
	}
	xesoe_go();
	usleep(1000);
	//-------------------------------------------->
	for( tuy = 1; tuy <=64; tuy++)
	{
		if(tuy != 17)// && tuy != 11)
			signal(tuy, __my_sig_handle);
		/*if(tuy == 11)
		{
		signal(tuy, signal_handler);
		}*/
	}
	//--------------------------------------------<	

	//wangrj 20130415, xeaa not used
	ret=xeaa_main("xeaa.DM_16CHD1.conf");
	if(ret==-1){
		xeLOG_ERR("xeaa startup fail.");
		goto exit_err;
	}

	usleep(1000);

	ret = xeptz_main();
	if(ret==-1){
		xeLOG_ERR("xeptz startup fail.");
		goto exit_err;
	}

	usleep(1000);

	ret=xesoe_main_hecp();
	if(ret==-1){
		xeLOG_ERR("xeceo startup fail.");
		goto exit_err;
	}

	usleep(1000);

	ret=xeceo_main("xeceo.DM_16CHD1.conf");
	if(ret==-1){
		xeLOG_ERR("xeceo startup fail.");
		goto exit_err;
	}

	xeaa_go();

	usleep(1000);
	wdgApp.interval = 2000;
	xeWDG_app_upinterval(wdgID, &wdgApp);

	ret = __init_recording();
	if(ret==-1){
		xeLOG_ERR("init recording fail.");
		goto exit_err;
	}

	wdgApp.interval = 100;
	xeWDG_app_upinterval(wdgID, &wdgApp);
	usleep(1000);

	ret = xerecording_main_hecp();
	if(ret==-1){
		xeLOG_ERR("xerecording main hecp startup fail.");
		goto exit_err;
	}

#endif

	xeLOG_NOTICE("CORE startup done , success");
	__spawn_my_app();
	while(1){
		pause();
	}


exit_err:
	__set_buzzer(1);
	sleep(1);
	__set_buzzer(0);

	xeLOG_ERR("CORE starup fail");
	__kill_my_app();
	exit(-1);
	return 0;
}

