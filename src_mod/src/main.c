#include <string.h>
#include <pthread.h>

#include "wlog.h"
#include "lpconfig.h"
#include "core.h"
//#include "module.h"

#if 0
static void __test_module(void){
	module_t *mod_p;
	char *modname="build/modules/mod_skeleton.so";
	
	mod_p = load_module(modname);
	if(mod_p==NULL){
		xeLOG_ERR("load module %s fail.",modname);
		return;
	}else{
		xeLOG_INFO("module %s loaded.",mod_p->name);
		mod_p->init_f("tst.conf");
		mod_p->run_f();
		
		deload_module(mod_p);
	}
	
	return;
}
#endif
//void pth_fun(void);
int  exit_once_err=0;
static char *core_cfile=NULL;

static char *mode=NULL;
static int process_num=1;
static int thread_num=1;

static char *modir=NULL;
static char *confdir=NULL;

const char *get_modir(void)
{
	if( modir )
	{
		return "src";
	}
	else
	{
		return "src";
	}
}
const char *get_confdir(void)
{
	if( confdir )
	{
		return "conf";
	}
	else
	{
		return "conf";
	}
}

//load conf from cfile
//return -1 if fail, 0 if success;
static int __load_main_conf(const char *cfile)
{
	LpConfig *lpc;
	DBG("conf file is: %s",cfile);
	lpc = lp_config_new(cfile);
	if(lpc==NULL)
	{
		wLOG_ERR("open(%s) fail.",cfile);
		return -1;
	}
	
	mode = strdup(lp_config_get_string(lpc,"global","MODE","process"));
	if(mode==NULL)return -1;
	
	DBG("MODE=%s.",mode);
	
	process_num = lp_config_get_int(lpc,"global","PROCESS_NUM",1);
	thread_num = lp_config_get_int(lpc,"global","THREAD_NUM",1);

	exit_once_err = lp_config_get_int(lpc,"global","EXIT_ONCE_ERROR",0);	
	core_cfile = strdup(lp_config_get_string(lpc,"core","CORECONF","linE.conf"));
	if(core_cfile==NULL)return -1;
	
	modir = strdup(lp_config_get_string(lpc,"dir","MODIR","modules"));
	if(modir==NULL)return -1;
	
	confdir = strdup(lp_config_get_string(lpc,"dir","CONFDIR","conf"));
	if(confdir==NULL)return -1;
	
	lp_config_destroy(lpc);

	return 0;
}


int main(int argc, char *argv[])
{
	int ret;
	
	//__test_module();
// 	if(argc!=3 || strcmp(argv[1],"-f")){
// 		wLOG_ERR("usage: %s -f ${ats.conf}",argv[0]);
// 		return -1;
// 	}
	
// 	ret = __load_main_conf(argv[2]);
 	char *cfile = "/home/tao/tmp/utils/src/wmod/conf/ats.conf";
 	ret = __load_main_conf(cfile);
	if(ret==-1){
		wLOG_ERR("%s: load conf from %s fail.",argv[0],argv[2]);
		return -1;
	}
       ret = init_core(core_cfile);
       if(ret==-1){
		wLOG_ERR("%s: init ats with %s fail.",argv[0],core_cfile);
		return -1;
	}
	core_mainloop();
	deinit_core();		//free memory
	if(mode) free(mode);
	if(core_cfile) free(core_cfile);
	if(modir) free(modir);
	if(confdir) free(confdir);
	return 0;
}

#if 0
void pth_fun(void)
{
	int ret;
	ret = init_core(core_cfile);
	if(ret==-1){
		xeLOG_ERR("init ats fail.");
		return;
	}	
	core_mainloop();
	return;
}
#endif
