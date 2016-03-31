/***********************************************************************************
 * 					Filename: exclog_public.c
 ***********************************************************************************
 * Description:
 * 		public function.
 * Copyright:
 * Author: 
 ***********************************************************************************/
#include "exclog_public.h"

void EXCLOG_DEBUG_FUNCTION(char *fmt, ...)
{
	FILE *fd = NULL;
	fd = fopen(EXCLOG_ERROR_LOG, "a+");
	if (fd)
	{
		va_list args;

		va_start(args,fmt);
		vfprintf(fd, fmt, args);
		va_end(args);

		fclose(fd);
	}
	return;
}

/********************************************************************************************
 * Function: _exclog_add_ipaddr_2_pkt()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:add ip address to pkt->message to distinguish packet owner.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ pkt:IN/OUT,add ip to whose message.
 *  @ ip:IN,ip address to add.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	NULL.
 ********************************************************************************************/
void _exclog_add_ipaddr_2_pkt(exclog_packet_t *pkt, char *ip)
{
	char message[EXCLOG_MSG_LEN_MAX] = { '\0' };
	char *pos1 = NULL;
	char *pos2 = NULL;

	pos1 = pkt->message;
	pos2 = strchr(pkt->message, '\n');
	if (pos2 == NULL)
	{
		DBG_SELF("Not found '\n' in packet.");
		strncpy(message, pos1, pkt->len);
	}
	else
	{
		strncpy(message, pos1, pos2 - pos1);
		message[pos2 - pos1] = '\0';
	}

	pkt->len = snprintf(pkt->message, sizeof(pkt->message) - 1, "%s\t--->%s\n", message, ip);

	return;
}
/********************************************************************************************
 * Function: _exclog_check_last_message()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:check if current message equals to last message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ pkt:IN,check whose message.
 *  @ last_message:IN,last message stored.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	
 *		 0:not repeat
 *		-1:repeat
 ********************************************************************************************/
int _exclog_check_last_message(exclog_packet_t *pkt, char *last_message)
{
	if (!strncmp(pkt->message, last_message, EXCLOG_MSG_LEN_MAX))
	{
		return -1;
	}

	return 0;
}
/********************************************************************************************
 * Function: _exclog_get_last_level_module()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:get log level of last message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 *  @ last_message:IN,last message stored.
 *  @ last_level:OUT,level of last message.
 *  @ last_module:OUT,module of last message.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :	
 *		 0:success
 *		-1:fail
 ********************************************************************************************/
int _exclog_get_last_level_module(char *last_message, char *level, char *module)
{
	char *tmp = last_message;
	char *pos1 = NULL;
	char *pos2 = NULL;

	pos1 = strchr(tmp, '<');
	if (pos1 == NULL)
	{
		return -1;
	}
	pos1++;
	pos2 = strchr(tmp, '>');
	if (pos2 == NULL)
	{
		return -1;
	}
	strncpy(level, pos1, pos2 - pos1);
	level[pos2 - pos1] = '\0';

	pos2++;
	pos1 = strchr(tmp, '(');
	if (pos1 == NULL)
	{
		return -1;
	}
	strncpy(module, pos2, pos1 - pos2);
	module[pos1 - pos2] = '\0';

	return 0;
}

/********************************************************************************************
 * Function: _exclog_public_get_ipaddr()
 *--------------------------------------------------------------------------------------------------------
 * Description:get local IP address.
 *--------------------------------------------------------------------------------------------------------
 * Parameters:
 * @ ip :OUT,result returned by this function 
 *--------------------------------------------------------------------------------------------------------
 * Return:	
 *		0: success;
 *	   -1: system error.
 ********************************************************************************************/
int _exclog_public_get_ipaddr(char *ip)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		DEBUG_SELF("create socket fail,%s.", strerror(errno));
		return -1;
	}

	struct ifreq ifr;
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ - 1] = 0;

	if (ioctl(sockfd, SIOCGIFADDR, &ifr) < 0)
	{
		DEBUG_SELF("ioctl(SIOCGIFADDR) %s.", strerror(errno));
		return -1;
	}

	struct sockaddr_in sin;
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));

	sprintf(ip, "%s", inet_ntoa(sin.sin_addr));

	close(sockfd);
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
unsigned long _exclog_level_str_2_hex(char *level)
{
	if (!strcmp(level, "0"))
	{
		return EXCLOG_LEVEL_EMERG;
	}
	else if (!strcmp(level, "1"))
	{
		return EXCLOG_LEVEL_CRIT;
	}
	else if (!strcmp(level, "2"))
	{
		return EXCLOG_LEVEL_ALERT;
	}
	else if (!strcmp(level, "3"))
	{
		return EXCLOG_LEVEL_ERR;
	}
	else if (!strcmp(level, "4"))
	{
		return EXCLOG_LEVEL_WARNING;
	}
	else if (!strcmp(level, "5"))
	{
		return EXCLOG_LEVEL_NOTICE;
	}
	else if (!strcmp(level, "6"))
	{
		return EXCLOG_LEVEL_INFO;
	}
	else if (!strcmp(level, "7"))
	{
		return EXCLOG_LEVEL_DEBUG;
	}
	else
	{
		return -1;
	}
}
/********************************************************************************************
 * Function: _exclog_module_str_2_hex()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description:transfer level string to hex.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ module:IN,log module string.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :log module in hex.
 ********************************************************************************************/
unsigned long _exclog_module_str_2_hex(char *module)
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
	}
	else if (!strcmp(module, "libhxSDK"))
	{
		return EXCLOG_MODULE_HXSDK;
	}
	else if (!strcmp(module, "libxeCEO"))
	{
		return EXCLOG_MODULE_LIB_CEO;
	}
	else if (!strcmp(module, "libxeAA"))
	{
		return EXCLOG_MODULE_LIB_AA;
	}
	else if (!strcmp(module, "libxeSOE"))
	{
		return EXCLOG_MODULE_LIB_SOE;
	}
	else if (!strcmp(module, "libxeSAP"))
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
	}
	else if (!strcmp(module, "libexcLOG"))
	{
		return EXCLOG_MODULE_LIB_LOG;
	}
	else if (!strcmp(module, "libxePM"))
	{
		return EXCLOG_MODULE_LIB_PM;
	}
	else if (!strcmp(module, "libxeSIS"))
	{
		return EXCLOG_MODULE_LIB_SIS;
	}
	else if (!strcmp(module, "libxeDavinci"))
	{
		return EXCLOG_MODULE_LIB_DAVINCI;
	}
	// else if (!strcmp(module, "libxeCONF"))
	// {
	// 	return EXCLOG_MODULE_LIB_CONF;
	// }
	else if (!strcmp(module, "core_other"))
	{
		return EXCLOG_MODULE_CORE_OTHER;
	}
	else if (!strcmp(module, "app_S2506A"))
	{
		return EXCLOG_MODULE_APP_S2506A;
	}
	else if (!strcmp(module, "app_SIPUA"))
	{
		return EXCLOG_MODULE_APP_SIPUA;
	}
	else if (!strcmp(module, "app_hxGUI"))
	{
		return EXCLOG_MODULE_APP_HXGUI;
	}
	else if (!strcmp(module, "app_hxWEB"))
	{
		return EXCLOG_MODULE_APP_HXWEB;
	}
	else if (!strcmp(module, "app_other"))
	{
		return EXCLOG_MODULE_APP_OTHER;
	}
	else
	{
		return -1;
	}
}

char *XELOG_GET_DATE_TIME(void)
{
	static char time_string[128];

	struct timeval tv;
	gettimeofday(&tv, NULL);

	struct tm tm;
	localtime_r(&(tv.tv_sec), &tm);

	snprintf(time_string, 128 - 1, "%04d-%02d-%02d %02d:%02d:%02d", (1900 + tm.tm_year), (1 + tm.tm_mon),
			tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	return time_string;
}