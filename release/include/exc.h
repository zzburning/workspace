/******************************************************************************
 * exc.h
 *
 *  Created on: 2011-10-19
 *      Author: 
 *
 * Description:
 * 	This file is EXC Interface
 *
 * Revision History:
 * 	V0.1 initial version code
 *****************************************************************************/

#ifndef __EXC_H__
#define __EXC_H__

#include "excT.h"
#include "excR.h"
#include "exclist.h"
#include "excport.h"
#include "excmd5.h"
// #include "exclog.h"
#include "exclog_x.h"

#include "lpconfig.h"
#include "glist.h"
#include "memwatch.h"

typedef struct
{
	int log_level;
}exc_init_t;

// extern excR_t exc_init(exc_init_t *init_p);

// typedef struct
// {
// 	int major;
// 	int minor;
// 	int revision;
// 	int buildID;
// 	char vstr[256];/*extra human readable version message*/
// }exc_version_t;
// 
/******************************************************************************
 * Function: exc_version()
 *-----------------------------------------------------------------------------
 * Description:
 *	Get libexc's version info;
 *-----------------------------------------------------------------------------
 * Reenterable: Yes
 *-----------------------------------------------------------------------------
 * Parameters:
 *	@ver_p: memory to hold version info;
 *-----------------------------------------------------------------------------
 * Return: NONE
 *****************************************************************************/
// extern void exc_version(exc_version_t *ver_p);

#endif /* __EXC_H__ */
