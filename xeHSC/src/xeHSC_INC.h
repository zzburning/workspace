/******************************************************************************
 * xeHSC_INC.h
 *
 *  Created on: 2011-10-19
 *      Author: wuhm<wuhm@hisome.com>
 *
 * Description:
 * 	This file is libxeHSC internal include .H file
 *
 * Revision History:
 * 	V0.1 initial version code
 *****************************************************************************/

#ifndef __HISOME_XEHSC_INC_H__
#define __HISOME_XEHSC_INC_H__

#include <stdio.h>
#include <errno.h>

#include "xeHSC.h"

#include "xeL.h"
#include "xeR.h"
#include "xeT.h"
#include "xeHSC_port.h"
#include "xeLOG_internal.h"

#if defined(CONFIG_XEHSC_DEVPLAT_VC6)
#ifndef VERSION_MAJOR
#define VERSION_MAJOR	0
#endif

#ifndef VERSION_MINOR
#define VERSION_MINOR	1
#endif

#ifndef VERSION_REV
#define VERSION_REV	0
#endif

#ifndef VERSION_BUILD_ID
#define VERSION_BUILD_ID	0
#endif

#ifndef LIBNAME
#define LIBNAME "libxeHSC"
#endif

#ifndef BUILD_TARGET
#define BUILD_TARGET "Debug"
#endif

#ifndef CONFIG_PLATFORM
#define CONFIG_PLATFORM "WIN32"
#endif

#ifndef CONFIG_BOARD_NAME
#define CONFIG_BOARD_NAME "Unknown"
#endif

#ifndef CONFIG_PRODUCT_MODEL
#define CONFIG_PRODUCT_MODEL "Unknown"
#endif
#endif

#endif /* __HISOME_XEHSC_INC_H__ */
