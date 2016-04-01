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
//extern void xeCore_version_2_var_run(char *fname_p);

#endif /* __HISOME_XEHSC_H__ */
