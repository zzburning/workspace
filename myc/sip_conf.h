/*        Filename: sip_conf.h
 **********************************************************
 * Description:
 *        this is sip_conf.c header.
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

#ifndef  __sip__2008_12_16_h__
#define __sip__2008_12_16_h__

//#define CONF_PATH "../../"
//#define CONF_FILE "/home/hxWEB/sip.conf"

#ifdef STATIC_MODE
#define cgiDBG(fmt, args...) printf("%s.%d:"fmt, __FILE__, __LINE__, ##args)
#else
#define cgiDBG(fmt, args...)
#endif /* STATIC_MODE */

#define VTDU_TREE_PATH				"/home/conf/HSVTDU/VTDU_tree.ini"
#define VTDU_TREE_BACK				"/home/conf/HSVTDU/VTDU_tree.ini.bak"
#define VTDU_TREE_TEMP				"/home/buffer/VTDU_tree.tmp"
#define OSD_CONF_DOWNLOAD			"/home/buffer/SIPx000_OSD_CONF_DOWNLOAD.txt"
#define OSD_CONF_UPLOAD				"/home/buffer/SIPx000_OSD_CONF_UPLOAD.txt"
#define OSD_CONF_DOWNLOAD_NAME		"SIPx000_OSD_CONF_DOWNLOAD.txt"
#define BUFFER_SIZE					4096


extern struct hxsdk_sip_account* sip_new_from_conf(const char *param_file);

extern void sip_destroy(struct hxsdk_sip_account* hsa);

extern char *sip_get_param(const char *param_file,const char *param_name);

#endif
