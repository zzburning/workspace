/******************************************************************************
 * xeHSC.h
 *
 *  Created on: 2011-10-19
 *      Author: wuhm<wuhm@hisome.com>
 *
 * Description:
 * 	This file is Hisome C Interface
 *
 * Revision History:
 * 	V0.1 initial version code
 *****************************************************************************/

#ifndef __HISOME_XEHSC_H__
#define __HISOME_XEHSC_H__

#include "xeT.h"
#include "xeR.h"
#include "xeL.h"
#include "xeHSC_port.h"

typedef struct
{
	int log_level;
}xeHSC_init_t;

extern xeR_t xeHSC_init(xeHSC_init_t *init_p);

typedef struct
{
	int major;
	int minor;
	int revision;
	int buildID;
	char vstr[256];/*extra human readable version message*/
}xeHSC_version_t;

/******************************************************************************
 * Function: xeHSC_version()
 *-----------------------------------------------------------------------------
 * Description:
 *	Get libxeHSC's version info;
 *-----------------------------------------------------------------------------
 * Reenterable: Yes
 *-----------------------------------------------------------------------------
 * Parameters:
 *	@ver_p: memory to hold version info;
 *-----------------------------------------------------------------------------
 * Return: NONE
 *****************************************************************************/
extern void xeHSC_version(xeHSC_version_t *ver_p);

#endif /* __HISOME_XEHSC_H__ */
