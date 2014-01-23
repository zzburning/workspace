/*        Filename: sip_conf.c
 **********************************************************
 * Description:
 *        this is sip_conf.c.
 * Version:
 *        V_0.1 2008.12.16
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        liuding <liuding@hisome.com.>
 * History:
 *        2008.12.16 liuding<liuding@hisome.com>
 *                V_0.1 initial version of this code.
 */

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../../include/hxSDK/hxSDK.h"
#include "./myconf/myconf.h"
#include "sip_conf.h"

static char *__get_eth_ip(const char *if_name)
{
	struct ifreq ifr;
	struct sockaddr_in *addr_in = NULL;
	int s = -1;

	s = socket(AF_INET, SOCK_DGRAM, 0);

	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", if_name);

	if (ioctl(s, SIOCGIFADDR, &ifr) == -1)
	{
		return NULL;
	}

	addr_in = (struct sockaddr_in *) &ifr.ifr_addr;
	return inet_ntoa(addr_in->sin_addr);
}

#if 0
struct hxsdk_sip_account* sip_new_from_conf(const char *param_file)
{
	struct hxsdk_sip_account* hsa;
	char conf[1024]="";

	if(NULL==param_file) return NULL;

	strcpy(conf,param_file);
	if('/'!=param_file[strlen(param_file)-1])
		strcat(conf,"/");
	strcat(conf,CONF_FILE);

	hsa=malloc(sizeof(struct hxsdk_sip_account));
	if(NULL==hsa)
		goto __sip_new_from_conf_error0;
	memset(hsa,0,sizeof(struct hxsdk_sip_account));

	myconf_info_struct* info=myconf_parser(conf,MYCONF_CASE_FIND);
	if(NULL==info)
	{
		strcpy(conf,"./"CONF_FILE);
		info=myconf_parser(conf,MYCONF_CASE_FIND);
		if(NULL==info)
		{
//			strcpy(conf,"../"CONF_FILE);
			strcpy(conf,CONF_FILE);
			info=myconf_parser(conf,MYCONF_CASE_FIND);
			if(NULL==info)
				goto __sip_new_from_conf_error1;
		}
	}

	const char* sip_temp;
	sip_temp=myconf_get_value(info,0,"sip_username");
	if(NULL!=sip_temp)
		hsa->sip_username=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_pwd");
	if(NULL!=sip_temp)
		hsa->sip_pwd=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_realm");
	if(NULL!=sip_temp)
		hsa->sip_realm=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_outbound_proxy");
	if(NULL!=sip_temp)
		hsa->sip_outbound_proxy=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_outbound_proxy_port");
	if(NULL!=sip_temp)
		hsa->sip_outbound_proxy_port=atoi(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_regsrv");
	if(NULL!=sip_temp)
		hsa->sip_regsrv=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_regsrv_port");
	if(NULL!=sip_temp)
		hsa->sip_regsrv_port=atoi(sip_temp);

	sip_temp=myconf_get_value(info,0,"local_addr");
	if(NULL!=sip_temp)
		hsa->local_addr=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"local_port");
	if(NULL!=sip_temp)
		hsa->local_port=atoi(sip_temp);

	myconf_clean(info);

	return hsa;
__sip_new_from_conf_error1:
	free(hsa);
__sip_new_from_conf_error0:
//	printf("get sip from conf[%s] FAIL.\n",conf);
	return NULL;
}
#else
struct hxsdk_sip_account* sip_new_from_conf(const char *param_file)
{
	struct hxsdk_sip_account* hsa;
	char conf[1024]="";

	if(NULL==param_file) return NULL;

	strcpy(conf,param_file);
	if('/'!=param_file[strlen(param_file)-1])
		strcat(conf,"/");
	strcat(conf,CONF_FILE);

	hsa=malloc(sizeof(struct hxsdk_sip_account));
	if(NULL==hsa)
		goto __sip_new_from_conf_error0;
	memset(hsa,0,sizeof(struct hxsdk_sip_account));

	myconf_info_struct* info=myconf_parser(conf,MYCONF_CASE_FIND);
	if(NULL==info)
	{
		strcpy(conf,"./"CONF_FILE);
		info=myconf_parser(conf,MYCONF_CASE_FIND);
		if(NULL==info)
		{
//			strcpy(conf,"../"CONF_FILE);
			strcpy(conf,CONF_FILE);
			info=myconf_parser(conf,MYCONF_CASE_FIND);
			if(NULL==info)
				goto __sip_new_from_conf_error1;
		}
	}

	const char* sip_temp;
	sip_temp=myconf_get_value(info,0,"sip_username");
	if(NULL!=sip_temp)
		hsa->sip_username=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_pwd");
	if(NULL!=sip_temp)
		hsa->sip_pwd=strdup(sip_temp);

	sip_temp=__get_eth_ip("eth0");
	if(NULL!=sip_temp)
	{
		hsa->sip_realm=strdup(sip_temp);
		hsa->sip_outbound_proxy=strdup(sip_temp);
		hsa->sip_regsrv=strdup(sip_temp);
	}

	sip_temp=myconf_get_value(info,0,"sip_outbound_proxy_port");
	if(NULL!=sip_temp)
		hsa->sip_outbound_proxy_port=atoi(sip_temp);

	sip_temp=myconf_get_value(info,0,"sip_regsrv_port");
	if(NULL!=sip_temp)
		hsa->sip_regsrv_port=atoi(sip_temp);

	sip_temp=myconf_get_value(info,0,"local_addr");
	if(NULL!=sip_temp)
		hsa->local_addr=strdup(sip_temp);

	sip_temp=myconf_get_value(info,0,"local_port");
	if(NULL!=sip_temp)
		hsa->local_port=atoi(sip_temp);

	myconf_clean(info);

	return hsa;
__sip_new_from_conf_error1:
	free(hsa);
__sip_new_from_conf_error0:
//	printf("get sip from conf[%s] FAIL.\n",conf);
	return NULL;
}
#endif

char *sip_get_param(const char *param_file,const char *param_name)
{
	char* param_value=NULL;
	char conf[1024]="";

	if(NULL==param_file) return NULL;

	strcpy(conf,param_file);
	if('/'!=param_file[strlen(param_file)-1])
		strcat(conf,"/");
	strcat(conf,CONF_FILE);

	myconf_info_struct* info=myconf_parser(conf,MYCONF_CASE_FIND);
	if(NULL==info)
	{
		strcpy(conf,"./"CONF_FILE);
		info=myconf_parser(conf,MYCONF_CASE_FIND);
		if(NULL==info)
		{
			strcpy(conf,"../"CONF_FILE);
			info=myconf_parser(conf,MYCONF_CASE_FIND);
			if(NULL==info)
				goto __sip_get_param_value_error0;
		}
	}

	char *sip_temp;
	sip_temp=(char *)myconf_get_value(info,0,param_name);
	if(NULL!=sip_temp)
	{
		param_value=strdup(sip_temp);
	}

	myconf_clean(info);

	return param_value;
__sip_get_param_value_error0:
	printf("get sip from conf[%s] FAIL.\n",conf);
	return NULL;
}

void sip_destroy(struct hxsdk_sip_account* hsa)
{
	if(NULL==hsa) return;

	if(NULL!=hsa->sip_username)
		free(hsa->sip_username);
	if(NULL!=hsa->sip_pwd)
		free(hsa->sip_pwd);
	if(NULL!=hsa->sip_realm)
		free(hsa->sip_realm);
	if(NULL!=hsa->sip_outbound_proxy)
		free(hsa->sip_outbound_proxy);
	if(NULL!=hsa->sip_regsrv)
		free(hsa->sip_regsrv);
	if(NULL!=hsa->local_addr)
		free(hsa->local_addr);
	free(hsa);
	hsa=NULL;
}

