/*        Filename: common.h
 **********************************************************
 * Description:
 *        this is mysrc's common header.
 * Version:
 *        V_0.1 2008.5.29
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.5.29 panhaijiang<panhaijiang@hisome.com>
 *                V_0.1 initial version of this code.
 */

#ifndef COMMON_H_2008_5_29
#define COMMON_H_2008_5_29
#ifdef BUILD_TARGET_HXSDK_POLICE
/*
//multity thread
#define MYLINK_MULTI_THREAD
#define MYMEM_MULTI_THREAD
#define MYUDP_MULTI_THREAD
#define MYTCP_SERVER_MULTI_THREAD
#define MYTCP_CLIENT_MULTI_THREAD
#define MYLOG_MULTI_THREAD
#define MYTHREADPOOL_MULTI_THREAD

//print more debug info
//#define MYLOG_TRACE_INFO

//net log
#define MYLOG_SEND_BY_UDP
*/

#ifdef WIN32
#define __FUNCTION__ "__FUNCTION__"
#endif
#ifdef WIN32
#define snprintf _snprintf
#endif
#endif// BUILD_TARGET_HXSDK_POLICE

#endif /*COMMON_H_*/
