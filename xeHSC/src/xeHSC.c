/******************************************************************************
 * xeHSC.c
 *
 *  Created on: 2011-10-19
 *      Author: wuhm<wuhm@hisome.com>
 *
 * Description:
 * 	This file is libxeHSC main .C file
 *
 * Revision History:
 * 	V0.1 initial version code
 *****************************************************************************/

#include "xeHSC_INC.h"

#ifdef MEMWATCH
#include <memwatch.h>
#endif/*MEMWATCH*/

#ifdef CONFIG_USE_XEHSC

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_USE_EXTERNAL_XELOG
int _xeHSC_log_level = 5;
#endif/*CONFIG_USE_EXTERNAL_XELOG*/

xeR_t xeHSC_init(xeHSC_init_t *init_p)
{
#ifndef CONFIG_USE_EXTERNAL_XELOG
	_xeHSC_log_level = init_p->log_level;
#endif
	
	xeLOG_INFO("xeHSC_init success.");
	return XER_SUCCESS;
	
}

void xeHSC_version(xeHSC_version_t *xsv_p)
{
	xsv_p->major = VERSION_MAJOR;
	xsv_p->minor = VERSION_MINOR;
	xsv_p->revision = VERSION_REV;
	xsv_p->buildID = VERSION_BUILD_ID;
#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
	snprintf(xsv_p->vstr,sizeof(xsv_p->vstr),"%s(%s) Version: %d.%d.%d-%d, DATE: %s %s, GCC: %s " \
		"TARGET_PLATFORM(%s)  TARGET_BOARD_NAME(%s) TARGET_PRODUCT_MODEL(%s)", \
		LIBNAME,BUILD_TARGET,VERSION_MAJOR,VERSION_MINOR,VERSION_REV,VERSION_BUILD_ID, \
		__DATE__,__TIME__,__VERSION__, \
		CONFIG_PLATFORM,CONFIG_BOARD_NAME,CONFIG_PRODUCT_MODEL);
#elif defined(CONFIG_XEHSC_DEVPLAT_VC6)
	snprintf(xsv_p->vstr,sizeof(xsv_p->vstr),"%s(%s) Version: %d.%d.%d-%d, DATE: %s %s, " \
		"TARGET_PLATFORM(%s)  TARGET_BOARD_NAME(%s) TARGET_PRODUCT_MODEL(%s)", \
		LIBNAME,BUILD_TARGET,VERSION_MAJOR,VERSION_MINOR,VERSION_REV,VERSION_BUILD_ID, \
		__DATE__,__TIME__, \
		CONFIG_PLATFORM,CONFIG_BOARD_NAME,CONFIG_PRODUCT_MODEL);
#else
#error "what Devplat?"
#endif
	return;
}

#ifdef __cplusplus
};
#endif

#endif
