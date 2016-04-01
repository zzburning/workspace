/*****************************************************************
 * 		Filename: get_para.c
 *****************************************************************
 * Description:
 *		get config para from config file
 * Version:
 *		Sep-7-2010
 * Copyright:
 *		HISOME <http://www.hisome.com.>
 * Author:
 *		renyi<renyi@hisome.com>
 * History:
 * 		Sep-7-2010 renyi<renyi@hisome.com>
 * 			V_0.1 init conf file
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "glist.h"
#include "lpconfig.h"
#include "wlog.h"
#include "config.h"

static int __build_arg_list(char **argv, char *argstr);
static cfname_t conf_name[MAX_CONF];

GList *conf_case_head = NULL;

static int __read_target_para( const char *cfile,conf_target_stru_t *tgt_info)
{
	LpConfig *lpc;

	lpc = lp_config_new(cfile);
	if (NULL == lpc)
		return -1;

	if(lpc == NULL || !lp_config_has_section(lpc, "TARGET"))
		return -1;

	char *s = NULL;

	s = lp_config_get_string(lpc, "TARGET", "IDENTITY", NULL);
	if(s)
	{
		tgt_info->identity = strdup(s);
		if(NULL == tgt_info->identity)
			goto dup_err_out;
	}
	else
	{
		xeLOG_ERR("identity cannot be NULL!!!");
		goto err_out;
	}

	s = lp_config_get_string(lpc, "TARGET", "USERNAME", NULL);
	if(s)
	{
		tgt_info->username = strdup(s);
		if(NULL == tgt_info->username)
			goto dup_err_out;
	}
	s = lp_config_get_string(lpc, "TARGET", "PWD", NULL);
	if(s)
	{
		tgt_info->pwd = strdup(s);
		if(NULL == tgt_info->pwd)
			goto dup_err_out;
	}
	tgt_info->first_cha = lp_config_get_int(lpc, "TARGET", "FIRST_CHA", 0);
	tgt_info->last_cha = lp_config_get_int(lpc, "TARGET", "LAST_CHA", 15);
	int fc = tgt_info->first_cha;

	int lc = tgt_info->last_cha;

	if(fc >= 0 && fc <= 23 && lc >= 0 && lc <= 23 && fc <= lc)
	{
		DBG("read target info OK!");
	}
	else
	{
		xeLOG_ERR("channel input FAIL!!!");
	}

	tgt_info->loop= lp_config_get_int(lpc, "TARGET", "LOOP", 1);

	s = lp_config_get_string(lpc, "TARGET", "RES_FILE", "conf_res");
	if (s) {
		tgt_info->sfile = strdup(s);
		if (NULL == tgt_info->sfile)
			goto dup_err_out;
	}

	tgt_info->cfile_num = lp_config_get_int(lpc, "TARGET", "CFILE_NUM", 0);

	if (lpc == NULL || !lp_config_has_section(lpc, "CFILE"))
	{
		xeLOG_ERR("lp_config_has setction config CFILE fail!");
		return -1;
	}
	int i;
	char sname[32]="";
	for (i = 0; i < tgt_info->cfile_num; i++) {
		snprintf(sname,sizeof(sname)-1,"CFILE_%d",i);
		s = lp_config_get_string(lpc, "CFILE", sname, NULL);
		if (s != NULL) {
			strncpy(conf_name[i].cfname, s, sizeof(conf_name[i].cfname) - 1);
			conf_name[i].flag = 1;
		} else {
			conf_name[i].flag = 0;
		}
	}
	if(lpc != NULL)
		lp_config_destroy(lpc);
	return 0;

  dup_err_out:
	xeLOG_ERR("strdup FAIL!!!");

  err_out:
  if(lpc != NULL)
  	lp_config_destroy(lpc);
	return -1;
}

static char *conf_modir=NULL;

const char *conf_get_modir(void)
{
	if(conf_modir)
	{
		return conf_modir;
	}
	else
	{
		return "wdir/modules/config_case_conf";
	}
}
static int __read_conf_para(const char *cfile,conf_case_stru_t *cc_p)
{
	LpConfig *lpc=NULL;
	char filename[128];
	memset(filename, 0 ,sizeof(filename));
	snprintf(filename,sizeof(filename)-1,"%s/%s",conf_get_modir(),cfile);

	lpc = lp_config_new(filename);
	if (NULL == lpc)
		return -1;
	int i = 0, ret;

	char sname[32];

	bzero(sname, sizeof(sname));
	while(1)
	{
		char *s = NULL;

		snprintf(sname, sizeof(sname) - 1, "TEST_%d", i);

		if(!lp_config_has_section(lpc, sname))
			break;
		i++;
		int cmdid;

		cc_p = calloc(1, sizeof(struct conf_case_stru));
		if(NULL == cc_p)
		{
			xeLOG_ERR("section %s: conf_case calloc FAIL!!!", sname);
			continue;
		}
		s = lp_config_get_string(lpc, sname, "CMD", NULL);
		if(NULL == s)
		{
			xeLOG_WARNING("section %s: cmd is NULL!!!", sname);
			free(cc_p);
			continue;
		}

		// printf("section %s: cmd is:%s\n",sname,s );
		cmdid = _get_cmd_id(s);	//get the command ID by the name
		if(cmdid < 0)
		{
			xeLOG_ERR("section %s: cmd(%s) Not Found!!!", sname, s);
			free(cc_p);
			continue;
		}
		cc_p->cmd = cmdid;
		cc_p->arg = (char **)calloc(MAX_PARA_CNT + 1, sizeof(char *));	//calloc point array to save config paras
		if(NULL == cc_p->arg)
		{
			xeLOG_ERR("section %s: para point array calloc FAIL!!!", sname);
			free(cc_p);
			continue;
		}

		s = lp_config_get_string(lpc, sname, "ARG", NULL);
		if(s)					//have argument,then let the para point to point to the para
		{
			char *tmp;

			tmp = strdup(s);
			if(NULL == tmp)
			{
				free(cc_p);
				free(cc_p->arg);
				continue;
			}
			ret = __build_arg_list(cc_p->arg, tmp);
			if(ret < 0)
			{
				xeLOG_ERR("build_arg_list(%s) FAIL!!!", s);
				free(tmp);
				free(cc_p->arg);
				free(cc_p);
				continue;
			}
		}
		cc_p->sleep = lp_config_get_int(lpc, sname, "SLEEP", 0);
		conf_case_head = g_list_append(conf_case_head, cc_p);
	}
	if(NULL == conf_case_head)
	{
		xeLOG_ERR("Not have a valid test case!!!");
		return -1;
	}
	if(lpc != NULL)
		lp_config_destroy(lpc);
	return 0;
}

/******************************************************
 * This is for build argument vector list
 ******************************************************/
static int __build_arg_list(char **argv, char *argstr)
{
	if(argv == NULL || argstr == NULL)
		return -1;
	argv[0] = argstr;
//  char *str=argstr;
	char *sh;

	char *tmp = argstr;

	while(1)					//replace ' ' with '\t'
	{
		sh = strchr(tmp, '\t');
		if(NULL == sh)
			break;
		*sh++ = ' ';
		if('\0' == *sh)
			break;
	}

	tmp = argstr;
	int arg_cnt = 1;

	while(1)
	{
		sh = strchr(tmp, ' ');
		if(NULL == sh)
			break;
		*sh++ = '\0';
		while(isspace(*sh))		//point to the first char which is not space
			sh++;
		if(*sh == '\0')
			break;
		if(++arg_cnt > MAX_PARA_CNT)
		{
			xeLOG_ERR("too much para!!!");
			return -1;
		}
		argv++;
		*argv = sh;
		tmp = sh;
	}
	return 0;
}

int _init_para( const char *cfile)
{
	memset(&conf_target,0,sizeof(conf_target_stru_t));
	int ret,i;
	ret = __read_target_para(cfile,&conf_target);
	if(ret < 0)
		goto err_out;

	conf_case_stru_t data;
	memset(&data,0,sizeof(conf_case_stru_t));

	for(i=0;i<conf_target.cfile_num;i++)
	{
		if (conf_name[i].flag==1) {
			ret=__read_conf_para(conf_name[i].cfname, &data);
			if(ret<0)
			{
				goto err_out;
			}else{
				printf("read confs para is success!\n");
			}
		}
	}
	DBG("read config para OK!!!");
	return 0;

  err_out:
	xeLOG_ERR("read config para FAIL!!!");
	return -1;
}

int _free_para()
{
	if(conf_case_head)
	{
		GList *list = conf_case_head;

		while(list)
		{
			if(list->data)
			{
				struct conf_case_stru *cc_p = (struct conf_case_stru *)list->data;

				char **arg = cc_p->arg;

				if(arg)
				{
					if(arg[0])	//free para
					{
						free(arg[0]);
					}
					free(arg);	//free point array
				}

				free(list->data);
			}
			list = list->next;
		}
		g_list_free(conf_case_head);
		conf_case_head = NULL;
	}

	return 0;
}
