#ifndef  __ATS_CONFIG_H__
#define  __ATS_CONFIG_H__

#include <stdio.h>
#include "glist.h"
#include "lpconfig.h"

#define  MODNAME	"config"
/* The max para count of config command */
#define MAX_PARA_CNT    10
#define HX_G_STAT_EQ_UPTIME		5000	//get equipment boot time and now time
#define HX_G_STAT_EQ_HARDDISK	5001	//get equipment harddisk active infomations
#define HX_S_VIDEO_PREVIEW 		6000
#define MAX_CONF 20

/*for input para*/
typedef struct conf_case_stru
{
	int cmd;
	char **arg;
	int sleep;
//  int  len;
}conf_case_stru_t;

 
typedef struct conf_target_stru
{
	char *identity;
	char *username;
	char *pwd;

	int first_cha;
	int last_cha;
	int loop;
	char *sfile;				//point to the directory of log file    
	int cfile_num;
	
	//struct conf_case_stru conf_case[MAX_CONF];
}conf_target_stru_t;

 conf_target_stru_t conf_target ;

typedef struct cfname_struct
{
	/**
	 * configuration file name 
	 **/
	char cfname[32];
	
	/**
	 * flag of configuration file name is null or not 
	 **/
   int flag;						
}cfname_t;


typedef int (*conf_func_f) (hx_target_t tID, char **arg);

struct conf_cmd_stru
{
	int cl_id;
	char *cl_name;
	conf_func_f cl_func;
};

/*current config command point*/
extern struct conf_cmd_stru *cur_conf_cmd;



extern GList *conf_case_head;

int _init_para( const char *cfile);

int _free_para();

int _get_cmd_id(const char *cmdstr);

struct conf_cmd_stru *_get_cmd_stru(int cmdid);

//test if we have EQ or EN config option
int _has_eq_config();

int _has_en_config();

#if 0
const char *_get_cmd_name(int cmdid);

conf_func_f _get_cmd_func(int cmdid);
#endif

extern FILE *ats_log_f;
extern FILE *report_log_f;

#define ats_LOG(fmt, args...) { \
		fprintf(ats_log_f,fmt"\n", ##args); \
		fflush(ats_log_f); \
	}

#define report_LOG(fmt, args...) { \
		fprintf(report_log_f,fmt"\n", ##args); \
		fflush(report_log_f); \
	}

#endif	/*__ATS_CONFIG_H__*/
