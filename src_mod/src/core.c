#include "wlog.h"
#include "lpconfig.h"
#include "glist.h"
#include "module.h"
#include "core.h"

const char *get_modir(void);
const char *get_confdir(void);

struct case_info{
	char *name;
	char *cfile;
};

static GList *case_head = NULL;
static int loop;

int init_core(const char *cfile)
{
	LpConfig *lpc;
	char cfpath[128]="";
	int i;
	GList *lst_head;
	
	snprintf(cfpath,sizeof(cfpath)-1,"%s/%s",get_confdir(),cfile);
	printf("confdir=%s\n",get_confdir());
	printf("cfpath=%s\n",cfpath);
	lpc = lp_config_new(cfpath);
	if(lpc==NULL){
		wLOG_ERR("open(%s) fail.",cfpath);
		return -1;
	}

	char *baselib;
	baselib = lp_config_get_string(lpc,"hxSDK","BASELIB",NULL);
	if(baselib==NULL)
	{
		wLOG_ERR("empty BASELIB, should be hxSDK-linE/lin/S250x.");
		goto err_baselib;
	}
	else if(!strcmp(baselib,"hxSDK-linE"))
	{
		DBG("assume ats link with hxSDK-linE.");
		char *tm;
		tm = lp_config_get_string(lpc,"hxSDK","TM",NULL);
		if(tm==NULL)
		{
			wLOG_ERR("empty TM, should be H3616|T1501e-H|S2504-H|K2_C6B020_C|K3_S2500_16SD");
			goto err_tm;
		}
		else if(!strcmp(tm,"H3616"))
		{
			DBG("target model: %s",tm);
		}
		else if(!strcmp(tm,"T1501e-H"))
		{
			DBG("target model: %s",tm);
		}
		else if(!strcmp(tm,"S2505-H"))
		{
			DBG("target model: %s",tm);
		}
		else if(!strcmp(tm,"H3616_EP"))
		{
			DBG("target model: %s",tm);
		}
		else if(!strcmp(tm,"K2_C6B020_C"))
		{
			DBG("target model: %s",tm);
		}else if(!strcmp(tm,"HX_TM_AGENT"))
		{
			DBG("target model: %s",tm);
		}else if(!strcmp(tm,"K3_S2500_16SD"))
		{
			DBG("target model:%s",tm);
			//harg.tm = HX_TM_K3_S2500_16SD;
		}
		else
		{
			wLOG_ERR("unknown TM(%s), should be H3616|T1501e-H|S2504-H|H3616_EP|K2_C6B020_C|K3_S2500_16SD|HX_TM_AGENT.",tm);
			goto err_tm;
		}
	}
	else
	{
		wLOG_ERR("unknown BASELIB:%s, should be hxSDK-linE/lin/S250x.",baselib);
		goto err_baselib;
	}
	

	loop=lp_config_get_int(lpc,"hxSDK","LOOP",1);
	i=0;
	do
	{
		char sname[32]="";
		snprintf(sname,sizeof(sname)-1,"CASE_%d",i);
		
		i++;//update section index
		
		if(!lp_config_has_section(lpc,sname))break;
		
		struct case_info *ci_p;
		ci_p = calloc(1,sizeof(*ci_p));
		if(ci_p==NULL)
		{
			wLOG_ERR("calloc fail, %s.",strerror(errno));
			goto err_calloc;
		}
		
		ci_p->name = strdup(lp_config_get_string(lpc,sname,"NAME",NULL));
		ci_p->cfile = strdup(lp_config_get_string(lpc,sname,"CFILE",NULL));
		if(ci_p->name == NULL || ci_p->cfile==NULL)
		{
			if(ci_p->name)free(ci_p->name);
			if(ci_p->cfile)free(ci_p->cfile);
			free(ci_p);
			goto err_calloc;
		}
		
		case_head = g_list_append(case_head,ci_p);
		
	}while(0x20081106);
	
	lp_config_destroy(lpc);
	return 0;
	
err_calloc:	
	lst_head = case_head;
	while(lst_head)
	{
		struct case_info *ci_p;
		
		ci_p = lst_head->data;
		free(ci_p->name);
		free(ci_p->cfile);
		free(ci_p);
		 
		lst_head = lst_head->next;
	};
	g_list_free(case_head);

	
err_tm:
err_baselib:
	lp_config_destroy(lpc);
	return -1;
}

int core_mainloop(void)
{
	GList *lst_head;
	int ret,i,count=1;
	struct case_info *ci_p;
	module_t *mod_p;

	for(i=0;i<loop;i++)
	{
		lst_head = case_head;
		while(lst_head)
		{
			ci_p = lst_head->data;

			char modname[256]="";
			snprintf(modname,sizeof(modname)-1,"%s/%s",get_modir(),ci_p->name);

			mod_p = load_module(modname);
			if(mod_p==NULL)
			{
				wLOG_ERR("load module(%s) fail.",modname);
				goto err_out;
			}

			char modcfile[256]="";
			snprintf(modcfile,sizeof(modcfile)-1,"%s/%s",get_modir(),ci_p->cfile);

			ret = mod_p->init_f(modcfile);
			if(ret==-1)
			{
				wLOG_ERR("module %s init fail.",mod_p->name);
				deload_module(mod_p);
				goto err_out;
			}
			ret = mod_p->run_f();
			if(ret==-1)
			{
				wLOG_ERR("module %s run fail.loop is %d",mod_p->name,count);
				deload_module(mod_p);
				goto err_out;
			}

			wLOG_INFO("module %s run success loop is %d:-).",mod_p->name,count);
			if(mod_p)
			deload_module(mod_p);
			lst_head = lst_head->next;
		}
		count++;
	}
	
	return 0;
	
err_out:
	return -1;
}
 
int deinit_core()
{
	if(case_head)
	{
		GList *list=case_head;
		while(list)
		{
			if(list->data)
			{	
				struct case_info *ci_p=list->data;
				if(ci_p->name)	free(ci_p->name);
				if(ci_p->cfile)	free(ci_p->cfile);
				free(list->data);
			}
			list=list->next;
		}

		g_list_free(case_head);		
	}
	return 0;
}
