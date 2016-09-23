#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "module.h"
#include "wlog.h"
#include "config.h"

#define  CONFIG_TYPE_EQ		1
#define  CONFIG_TYPE_EN		2


static int __config_test_main();

FILE *ats_log_f = NULL;
FILE *report_log_f = NULL;

hx_target_t cur_tID = 0;

static int __config_init(const char *cfile)
{
	DBG(MODNAME ": init with cfile=%s.", cfile);
	int ret = -1;
	ret =  _init_para(cfile);
	if(ret < 0)
		return -1;
	ats_log_f = fopen(conf_target.sfile, "a+");	//all run message save in it;
	if(NULL == ats_log_f)
	{
		xeLOG_ERR("open log file FAIL!!!");
		return -1;
	}	

	static char *report_log_file = "report_log_file.txt";
	report_log_f = fopen(report_log_file, "a+");	//all run message save in it;
	if(NULL == report_log_f)
	{
		xeLOG_ERR("open report log file FAIL!!!");
		return -1;
	}
	return 0;
}

/***************************************************
 * This is main function to run
 ***************************************************/
static int __config_run(void)
{
	DBG(MODNAME ": start running......");

	int ret = -1;

	ret = __config_test_main();

	DBG(MODNAME ": stop running......");
	if(ret < 0)
		return -1;
	return 0;
}

static void __config_deinit(void)
{
	DBG(MODNAME ": de-init called.");

	int ret = -1;

	ret = _free_para();
	if(ret < 0)
	{
		xeLOG_ERR("free para FAIL!!!");
	}
	else
	{
		DBG("free para OK!");
	}

	if(ats_log_f)
		fclose(ats_log_f);
	if(report_log_f)
		fclose(report_log_f);
}

/*************************************************************************
 * ats-core will load mod_export symble, so we must declare it as this.
 ************************************************************************/
ats_module_t mod_export = {
	.name = MODNAME,
	.init_f = __config_init,
	.run_f = __config_run,
	.deinit_f = __config_deinit,
};

/**********************************************************************
 * Func:
 * 		__config_test_sub
 * Desc:
 * 		config test sub function,invocated by __config_test_main function
 *----------------------------------------------------------------------
 * Arg:
 * 		tID: config target
 * 		type: config type,CONFIG_EQ or CONFIG_EN
 *----------------------------------------------------------------------
 * Return:
 * 		0: success
 * 		else: fail number
 **********************************************************************/
static int total_cnt = 0;

static int eq_conf_cnt = 0, en_conf_cnt = 0, stat_conf_cnt = 0;

static int __config_test_sub(hx_target_t tID, int type)
{
	int fail_cnt = 0, ret = -1;

	GList *lst_head = conf_case_head;

	while(lst_head)
	{
		cur_tID = tID;			//record current target ID
		struct conf_case_stru *cdata = lst_head->data;

		int cid = cdata->cmd;

		if(CONFIG_TYPE_EQ == type)	//jump the option do not face the command
		{
			if(cid < HX_IOC_EQ_MIN
			   || (cid > HX_IOC_EQ_MAX && cid != HX_G_STAT_EQ_UPTIME && cid != HX_G_STAT_EQ_HARDDISK 
			   		&& cid != HX_S_VIDEO_PREVIEW))
			{
				lst_head = lst_head->next;
				continue;
			}
		}
		else if(CONFIG_TYPE_EN == type)
		{
			if(cid < HX_IOC_EN_MIN || cid > HX_IOC_EN_MAX)
			{
				lst_head = lst_head->next;
				continue;
			}
		}
		else
		{
			xeLOG_ERR("It's a bug!!!");
			continue;
		}

		cur_conf_cmd = _get_cmd_stru(cid);

		if(cur_conf_cmd)
		{
			conf_func_f cfunc = cur_conf_cmd->cl_func;

			ret = cfunc(tID, cdata->arg);
			if(cid >= HX_IOC_EQ_MIN && cid <= HX_IOC_EQ_MAX)
				eq_conf_cnt++;
			if(cid >= HX_IOC_EN_MIN && cid <= HX_IOC_EN_MAX)
				en_conf_cnt++;
			if(cid == HX_G_STAT_EQ_UPTIME || cid == HX_G_STAT_EQ_HARDDISK)
				stat_conf_cnt++;
			// if(cid == HX_S_VIDEO_PREVIEW)
				// s_conf_cnt++;
			total_cnt++;
			if(ret < 0)
			{
				xeLOG_ERR("Config command(%s) FAIL!!!", cur_conf_cmd->cl_name);
				fail_cnt++;
			}
			else
			{
				DBG("Config command(%s) PASS!!!", cur_conf_cmd->cl_name);
			}
		}
		sleep(cdata->sleep);
		lst_head = lst_head->next;
	}
	return fail_cnt;
}

/*************************************************************************
 * this is the main function,to run config test,
 * for all the case read from config file(config.conf)
 *************************************************************************/
static int __config_test_main()
{
	int i, j,ret;

	int fail_cnt = 0;//,test_no=0;

	char target[32];

	hx_target_t tID = -1;
	for (j=1; j<=conf_target.loop; j++) {
		ats_LOG("###################################################");
		ats_LOG("Equipment config loop %d start....",j);
		if (!_has_eq_config()) {
			ats_LOG("\tNo EQ config option.");
			goto lp1;
		}
		sprintf(target, "%s", conf_target.identity);
		tID = hx_open(target, conf_target.username, conf_target.pwd, 0);
		if (tID < 0) {
			xeLOG_ERR("open target(%s) FAIL!!!", target);
			goto lp1;
		}
		DBG("open target(%s) OK!", target);
		ret = __config_test_sub(tID, CONFIG_TYPE_EQ);
		fail_cnt += ret;
		hx_close(tID);
		lp1: ats_LOG("Equipment config end.\n");

		ats_LOG("Channel config start.....");
		if (!_has_en_config()) {
			ats_LOG("\tNo EN config option.");
			goto lp2;
		}
		int fcha = conf_target.first_cha; //first channel and last channel

		int lcha = conf_target.last_cha;

		for (i = fcha; i <= lcha; i++) {
			// ats_LOG("channel %d:", i);
			sprintf(target, "%s:%d", conf_target.identity, i);
			tID = hx_open(target, conf_target.username, conf_target.pwd, 0);
			if (tID < 0) {
				xeLOG_ERR("open target(%s) FAIL!!!", target);
				continue;
			}
			DBG("open target(%s) OK!", target);

			ret = __config_test_sub(tID, CONFIG_TYPE_EN);

			// if(ret)
			// {
			// 	ats_LOG("Channel %d:TEST is PASS\n",i);
			// }else{
			// 	ats_LOG("Channel %d:TEST_is FAIL\n",i);
			// }
			fail_cnt += ret;
			hx_close(tID);
		}
		lp2: ats_LOG("Channel config end.\n");
		ats_LOG("loop %d result:Config Fail Count: %d   Total Count: %d(EQ:%d EN:%d STAT:%d)\n\n",
				conf_target.loop,fail_cnt, total_cnt, eq_conf_cnt, en_conf_cnt, stat_conf_cnt);
	}
	return ((fail_cnt) ? -1 : 0);
}
