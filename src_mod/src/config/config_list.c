/*****************************************************************		
 * 		Filename: config_list.c
 *****************************************************************
 * Description:
 *		define all the config option
 * Version:
 *		V_0.1	Feb-9-2009
 * Copyright:
 *		HISOME <http://www.hisome.com.>
 * Author:
 *		yangsz <yangsz@hisome.com.>
 * History:
 * 		Feb-9-2009 yangsz<yangsz@hisome.com.>
 * 			V_0.1 initial version of this file;
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_func.h"
#include "config.h"


struct conf_cmd_stru clist[] = {
	/*EQ config list */
	{HX_IOCG_EQ_HOSTNAME, "HX_IOCG_EQ_HOSTNAME", _iocg_eq_hostname},
	{HX_IOCS_EQ_HOSTNAME, "HX_IOCS_EQ_HOSTNAME", _iocs_eq_hostname},

	{HX_IOCG_EQ_BOOTPROTO, "HX_IOCG_EQ_BOOTPROTO", _iocg_eq_bootproto},
	{HX_IOCS_EQ_BOOTPROTO, "HX_IOCS_EQ_BOOTPROTO", _iocs_eq_bootproto},

	{HX_IOCG_EQ_IP, "HX_IOCG_EQ_IP", _iocg_eq_ip},
	{HX_IOCS_EQ_IP, "HX_IOCS_EQ_IP", _iocs_eq_ip},

	{HX_IOCG_EQ_DNS, "HX_IOCG_EQ_DNS", _iocg_eq_dns},
	{HX_IOCS_EQ_DNS, "HX_IOCS_EQ_DNS", _iocs_eq_dns},

	{HX_IOCG_EQ_PPPOE, "HX_IOCG_EQ_PPPOE", _iocg_eq_pppoe},
	{HX_IOCS_EQ_PPPOE, "HX_IOCS_EQ_PPPOE", _iocs_eq_pppoe},

	{HX_IOCG_EQ_DATETIME, "HX_IOCG_EQ_DATETIME", _iocg_eq_datetime},
	{HX_IOCS_EQ_DATETIME, "HX_IOCS_EQ_DATETIME", _iocs_eq_datetime},

	{HX_IOCS_EQ_DEFAULT, "HX_IOCS_EQ_DEFAULT", _iocs_eq_default},
	{HX_IOCS_EQ_REBOOT, "HX_IOCS_EQ_REBOOT", _iocs_eq_reboot},
	{HX_IOCS_EQ_HALT, "HX_IOCS_EQ_HALT", _iocs_eq_halt},

	{HX_IOCG_EQ_USER, "HX_IOCG_EQ_USER", _iocg_eq_user},
	{HX_IOCS_EQ_USER, "HX_IOCS_EQ_USER", _iocs_eq_user},

	{HX_IOCG_EQ_GROUP, "HX_IOCG_EQ_GROUP", _iocg_eq_group},
	{HX_IOCS_EQ_GROUP, "HX_IOCS_EQ_GROUP", _iocs_eq_group},

	/*get/set equipment preview windows number */
	{HX_IOCG_EQ_DISPLAY_WINDOWS, "HX_IOCG_EQ_DISPLAY_WINDOWS", _iocg_eq_display_windows},
	{HX_IOCS_EQ_DISPLAY_WINDOWS, "HX_IOCS_EQ_DISPLAY_WINDOWS", _iocs_eq_display_windows},

	/*get/set equipment preview frame position */
	{HX_IOCG_EQ_WINDOW_DISPLAY, "HX_IOCG_EQ_WINDOW_DISPLAY", _iocg_eq_window_display},
	{HX_IOCS_EQ_WINDOW_DISPLAY, "HX_IOCS_EQ_WINDOW_DISPLAY", _iocs_eq_window_display},

	{HX_IOCG_EQ_HOSTS, "HX_IOCG_EQ_HOSTS", _iocg_eq_hosts},
	{HX_IOCS_EQ_HOSTS, "HX_IOCS_EQ_HOSTS", _iocs_eq_hosts},

	{HX_IOCG_EQ_DISK, "HX_IOCG_EQ_DISK", _iocg_eq_disk},
	{HX_IOCS_EQ_DISK, "HX_IOCS_EQ_DISK", _iocs_eq_disk},
#if 0
	{HX_IOCG_EQ_DISK_EXT, "HX_IOCG_EQ_DISK_EXT", _iocg_eq_disk_ext},
#endif

	{HX_IOCG_EQ_SIP, "HX_IOCG_EQ_SIP", _iocg_eq_sip},
	{HX_IOCS_EQ_SIP, "HX_IOCS_EQ_SIP", _iocs_eq_sip},

	{HX_IOCG_EQ_UDP_PKTSIZE, "HX_IOCG_EQ_UDP_PKTSIZE", _iocg_eq_udp_pktsize},
	{HX_IOCS_EQ_UDP_PKTSIZE, "HX_IOCS_EQ_UDP_PKTSIZE", _iocs_eq_udp_pktsize},

	{HX_IOCG_EQ_IP_ACL, "HX_IOCG_EQ_IP_ACL", _iocg_eq_ip_acl},
	{HX_IOCS_EQ_IP_ACL, "HX_IOCS_EQ_IP_ACL", _iocs_eq_ip_acl},

	{HX_IOCG_EQ_SIPURI_ACL, "HX_IOCG_EQ_SIPURI_ACL", _iocg_eq_sipuri_acl},
	{HX_IOCS_EQ_SIPURI_ACL, "HX_IOCS_EQ_SIPURI_ACL", _iocs_eq_sipuri_acl},

	{HX_IOCG_EQ_EQUIPMENT_ID, "HX_IOCG_EQ_EQUIPMENT_ID", _iocg_eq_equipment_id},
	{HX_IOCS_EQ_EQUIPMENT_ID, "HX_IOCS_EQ_EQUIPMENT_ID", _iocs_eq_equipment_id},

	{HX_IOCS_EQ_COMMIT, "HX_IOCS_EQ_COMMIT", _iocs_eq_commit},

	{HX_IOCG_EQ_KTASK, "HX_IOCG_EQ_KTASK", _iocg_eq_ktask},
	{HX_IOCS_EQ_KTASK, "HX_IOCS_EQ_KTASK", _iocs_eq_ktask},

	{HX_IOCG_EQ_STASK, "HX_IOCG_EQ_STASK", _iocg_eq_stask},
	{HX_IOCS_EQ_STASK, "HX_IOCS_EQ_STASK", _iocs_eq_stask},

	{HX_IOCG_EQ_LOGSERVER, "HX_IOCG_EQ_LOGSERVER", _iocg_eq_logserver},
	{HX_IOCS_EQ_LOGSERVER, "HX_IOCS_EQ_LOGSERVER", _iocs_eq_logserver},

	{HX_IOCG_EQ_SW_VERSION, "HX_IOCG_EQ_SW_VERSION", _iocg_eq_sw_version},

	{HX_IOCS_EQ_UPDATE, "HX_IOCS_EQ_UPDATE", _iocs_eq_update},

	{HX_IOCG_EQ_GAUUID, "HX_IOCG_EQ_GAUUID", _iocg_eq_gauuid},
	{HX_IOCS_EQ_GAUUID, "HX_IOCS_EQ_GAUUID", _iocs_eq_gauuid},
	
	{ HX_IOCG_EQ_CAN_INDEX," HX_IOCG_EQ_CAN_INDEX",_iocg_eq_can_index},
	{ HX_IOCS_EQ_CAN_INDEX," HX_IOCS_EQ_CAN_INDEX",_iocs_eq_can_index},
	
	{HX_IOCG_EQ_RW_NUM,"HX_IOCG_EQ_RW_NUM", _iocg_eq_rw_num},
	{HX_IOCS_EQ_RW_NUM,"HX_IOCS_EQ_RW_NUM", _iocs_eq_rw_num},
	
	//add by wangtao
	{HX_IOCG_EQ_VIDEO_WINNUM,"HX_IOCG_EQ_VIDEO_WINNUM", _iocg_eq_video_winnum},
	{HX_IOCS_EQ_VIDEO_WINNUM,"HX_IOCS_EQ_VIDEO_WINNUM", _iocs_eq_video_winnum},

	{HX_IOCG_EQ_VIDEO_RESOLUTION,"HX_IOCG_EQ_VIDEO_RESOLUTION", _iocg_eq_video_resolution},
	{HX_IOCS_EQ_VIDEO_RESOLUTION,"HX_IOCS_EQ_VIDEO_RESOLUTION", _iocs_eq_video_resolution},

	{HX_IOCG_EQ_VIDEO_STATUS,"HX_IOCG_EQ_VIDEO_STATUS", _iocg_eq_video_status},
	{HX_IOCS_EQ_VIDEO_STATUS,"HX_IOCS_EQ_VIDEO_STATUS", _iocs_eq_video_status},

	{HX_IOCG_EQ_NTP,"HX_IOCG_EQ_NTP", _iocg_eq_ntp},
	{HX_IOCS_EQ_NTP,"HX_IOCS_EQ_NTP", _iocs_eq_ntp},


	{HX_IOCG_EQ_VIDEO_WINDOWS_4_DE,"HX_IOCG_EQ_VIDEO_WINDOWS_4_DE", _iocg_eq_video_windows_4_de},

	/*EN config list */
	{HX_IOCG_EN_NAME, "HX_IOCG_EN_NAME", _iocg_en_name},
	{HX_IOCS_EN_NAME, "HX_IOCS_EN_NAME", _iocs_en_name},

	{HX_IOCS_EN_DEFAULT, "HX_IOCS_EN_DEFAULT", _iocs_en_default},

	{HX_IOCG_EN_VIDEO_ENCODER, "HX_IOCG_EN_VIDEO_ENCODER", _iocg_en_video_encoder},
	{HX_IOCG_EN_VIDEO_SIZE, "HX_IOCG_EN_VIDEO_SIZE", _iocg_en_video_size},

	{HX_IOCG_EN_VIDEO_BITRATE, "HX_IOCG_EN_VIDEO_BITRATE", _iocg_en_video_bitrate},
	{HX_IOCS_EN_VIDEO_BITRATE, "HX_IOCS_EN_VIDEO_BITRATE", _iocs_en_video_bitrate},

	{HX_IOCG_EN_VIDEO_RATIO, "HX_IOCG_EN_VIDEO_RATIO", _iocg_en_video_ratio},
	{HX_IOCS_EN_VIDEO_RATIO, "HX_IOCS_EN_VIDEO_RATIO", _iocs_en_video_ratio},

	{HX_IOCG_EN_VIDEO_BTYPE, "HX_IOCG_EN_VIDEO_BTYPE", _iocg_en_video_btype},
	{HX_IOCS_EN_VIDEO_BTYPE, "HX_IOCS_EN_VIDEO_BTYPE", _iocs_en_video_btype},

	{HX_IOCG_EN_VIDEO_FRAMERATE, "HX_IOCG_EN_VIDEO_FRAMERATE", _iocg_en_video_framerate},

	{HX_IOCG_EN_VIDEO_IFRAMEINTERVAL, "HX_IOCG_EN_VIDEO_IFRAMEINTERVAL", _iocg_en_video_iframeinterval},
	{HX_IOCS_EN_VIDEO_IFRAMEINTERVAL, "HX_IOCS_EN_VIDEO_IFRAMEINTERVAL", _iocs_en_video_iframeinterval},

	{HX_IOCG_EN_VIDEO_COLOR, "HX_IOCG_EN_VIDEO_COLOR", _iocg_en_video_color},
	{HX_IOCS_EN_VIDEO_COLOR, "HX_IOCS_EN_VIDEO_COLOR", _iocs_en_video_color},

	{HX_IOCG_EN_VIDEO_OSD, "HX_IOCG_EN_VIDEO_OSD", _iocg_en_video_osd},
	{HX_IOCS_EN_VIDEO_OSD, "HX_IOCS_EN_VIDEO_OSD", _iocs_en_video_osd},

	{HX_IOCG_EN_AUDIO_ENCODER, "HX_IOCG_EN_AUDIO_ENCODER", _iocg_en_audio_encoder},

	{HX_IOCG_EN_MUX, "HX_IOCG_EN_MUX", _iocg_en_mux},

	{HX_IOCG_EN_MULTICAST, "HX_IOCG_EN_MULTICAST", _iocg_en_multicast},
	{HX_IOCS_EN_MULTICAST, "HX_IOCS_EN_MULTICAST", _iocs_en_multicast},

	{HX_IOCG_EN_PTZ, "HX_IOCG_EN_PTZ", _iocg_en_ptz},
	{HX_IOCS_EN_PTZ, "HX_IOCS_EN_PTZ", _iocs_en_ptz},

	{HX_IOCG_EN_RECWD, "HX_IOCG_EN_RECWD", _iocg_en_recwd},
	{HX_IOCS_EN_RECWD, "HX_IOCS_EN_RECWD", _iocs_en_recwd},

	{HX_IOCS_EN_RECWD_DUP_2_CHANNELS,"HX_IOCS_EN_RECWD_DUP_2_CHANNELS",_iocs_en_recwd_dup_2_channels},
	{HX_IOCS_EN_RECWD_DUP_2_WDAYS,"HX_IOCS_EN_RECWD_DUP_2_WDAYS",_iocs_en_rewd_dup_2_weekdays},

	{HX_IOCG_EN_SUB_RECWD, "HX_IOCG_EN_SUB_RECWD", _iocg_en_sub_recwd},
	{HX_IOCS_EN_SUB_RECWD, "HX_IOCS_EN_SUB_RECWD", _iocs_en_sub_recwd},

	{HX_IOCG_EN_MDET, "HX_IOCG_EN_MDET", _iocg_en_mdet},
	{HX_IOCS_EN_MDET, "HX_IOCS_EN_MDET", _iocs_en_mdet},

	{HX_IOCG_EN_PTZ_PROTOCOLS, "HX_IOCG_EN_PTZ_PROTOCOLS", _iocg_en_ptz_protocols},

	{HX_IOCG_EN_SIP, "HX_IOCG_EN_SIP", _iocg_en_sip},
	{HX_IOCS_EN_SIP, "HX_IOCS_EN_SIP", _iocs_en_sip},

	{HX_IOCG_EN_VIDEO_BITRATE_RAW, "HX_IOCG_EN_VIDEO_BITRATE_RAW", _iocg_en_video_bitrate_raw},
	{HX_IOCS_EN_VIDEO_BITRATE_RAW, "HX_IOCS_EN_VIDEO_BITRATE_RAW", _iocs_en_video_bitrate_raw},

	{HX_IOCG_EN_KTASK, "HX_IOCG_EN_KTASK", _iocg_en_ktask},
	{HX_IOCS_EN_KTASK, "HX_IOCS_EN_KTASK", _iocs_en_ktask},

	{HX_IOCG_EN_STASK, "HX_IOCG_EN_STASK", _iocg_en_stask},
	{HX_IOCS_EN_STASK, "HX_IOCS_EN_STASK", _iocs_en_stask},

#if 0
	{HX_IOCG_EN_OVERLAP_STATUS, "HX_IOCG_EN_OVERLAP_STATUS", _iocg_en_overlap_status},
	{HX_IOCS_EN_OVERLAP_STATUS, "HX_IOCS_EN_OVERLAP_STATUS", _iocs_en_overlap_status},

	{HX_IOCG_EN_OVERLAP_AREA, "HX_IOCG_EN_OVERLAP_AREA", _iocg_en_overlap_area},
	{HX_IOCS_EN_OVERLAP_AREA, "HX_IOCS_EN_OVERLAP_AREA", _iocs_en_overlap_area},

	{HX_IOCG_EN_OSG_STATUS, "HX_IOCG_EN_OSG_STATUS", _iocg_en_osg_status},
	{HX_IOCS_EN_OSG_STATUS, "HX_IOCS_EN_OSG_STATUS", _iocs_en_osg_status},

	{HX_IOCG_EN_OSG_FOCUS, "HX_IOCG_EN_OSG_FOCUS", _iocg_en_osg_focus},
	{HX_IOCS_EN_OSG_FOCUS, "HX_IOCS_EN_OSG_FOCUS", _iocs_en_osg_focus},

	{HX_IOCG_EN_OSG_COLOR, "HX_IOCG_EN_OSG_COLOR", _iocg_en_osg_color},
	{HX_IOCS_EN_OSG_COLOR, "HX_IOCS_EN_OSG_COLOR", _iocs_en_osg_color},

	{HX_IOCG_EN_MDET_AN_AREA, "HX_IOCG_EN_MDET_AN_AREA", _iocg_en_mdet_an_area},
	{HX_IOCS_EN_MDET_AN_AREA, "HX_IOCS_EN_MDET_AN_AREA", _iocs_en_mdet_an_area},

	{HX_IOCG_EN_OVERLAP_AN_AREA, "HX_IOCG_EN_OVERLAP_AN_AREA", _iocg_en_overlap_an_area},
	{HX_IOCS_EN_OVERLAP_AN_AREA, "HX_IOCS_EN_OVERLAP_AN_AREA", _iocs_en_overlap_an_area},
#endif
	/*EQ stat */
	{HX_G_STAT_EQ_UPTIME, "HX_STAT_EQ_UPTIME", _stat_eq_uptime},
	{HX_G_STAT_EQ_HARDDISK, "HX_STAT_EQ_HARDDISK", _stat_eq_harddisk},

	//add by wangtao
	{HX_S_VIDEO_PREVIEW,"HX_S_VIDEO_PREVIEW",_s_video_preview},
};

static int cmd_cnt = sizeof(clist) / sizeof(struct conf_cmd_stru);

struct conf_cmd_stru *cur_conf_cmd = NULL;

/*******************************************
 *get config command ID by command name as HX_IOCS_EQ_HOSTNAME
 *******************************************/
int _get_cmd_id(const char *cmdstr)
{
	if(NULL == cmdstr)
		return -1;

	int i = 0;

	char *cp;

	for(; i < cmd_cnt; i++)
	{
		cp = clist[i].cl_name;
		if(NULL == cp)
			continue;
		if(!strcmp(cmdstr, cp))
			return clist[i].cl_id;
	}
	return -1;
}

/*************************************************************
 * get config command struct point by command ID
 *************************************************************/
struct conf_cmd_stru *_get_cmd_stru(int cmdid)
{
	if(cmdid < 1)
		return NULL;
	int i = 0;

	for(; i < cmd_cnt; i++)
	{
		if(cmdid == clist[i].cl_id)
			return &clist[i];
	}
	return NULL;
}

/****************************************************
 * test if has equipment config option,from conf_case_head
 * return 1 if has,0 if havn't
 ****************************************************/
int _has_eq_config()
{
	GList *head = conf_case_head;

	struct conf_case_stru *cc_p = NULL;

	int cid;

	while(head)
	{
		cc_p = head->data;
		cid = cc_p->cmd;
		if((cid >= HX_IOC_EQ_MIN && cid <= HX_IOC_EQ_MAX) || cid == HX_G_STAT_EQ_UPTIME || cid == HX_G_STAT_EQ_HARDDISK
			|| cid == HX_S_VIDEO_PREVIEW)
			return 1;
		head = head->next;
	}
	return 0;
}

int _has_en_config()
{
	GList *head = conf_case_head;

	struct conf_case_stru *cc_p = NULL;

	int cid;

	while(head)
	{
		cc_p = head->data;
		cid = cc_p->cmd;
		if(cid >= HX_IOC_EN_MIN && cid <= HX_IOC_EN_MAX)
			return 1;
		head = head->next;
	}
	return 0;
}

#if 0
/***********************************************************
 * get command string name by command ID
 ***********************************************************/
const char *_get_cmd_name(int cmdid)
{
	if(cmdid < 1)
		return NULL;
	int i = 0;

	for(; i < cmd_cnt; i++)
	{
		if(cmdid == clist[i].cl_id)
			return clist[i].cl_name;
	}
	return NULL;
}

/**********************************************************
 * get the function point of config command by command ID
 **********************************************************/
conf_func_f _get_cmd_func(int cmdid)
{
	if(cmdid < 1)
		return NULL;
	int i = 0;

	for(; i < cmd_cnt; i++)
	{
		if(cmdid == clist[i].cl_id)
			return clist[i].cl_func;
	}
	return NULL;
}
#endif
