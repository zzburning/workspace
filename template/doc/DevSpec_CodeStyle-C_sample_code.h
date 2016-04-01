/******************************************************************************	
 * Filename: DevSpec_CodeStyle-C_sample_code.h
 ******************************************************************************
 * Description:
 *		this is a sample .h file header.
 * Version:
 *		V_0.2	Jan-4-2007
 * Copyright:
 *		HISOME <www.hisome.com.>
 * Author:
 *		developer <developer@hisome.com.>
 * History:
 *	Aug-8-2007  developer1<developer1@hisome.com>
 *		V_0.2 add a new API hx_new_func().
 * 	Jan-4-2007  developer<developer@hisome.com>
 *		V_0.1 initial version of this code.
 *****************************************************************************/

#ifndef __HISOME_SAMPLE_CODE_H__
#define __HISOME_SAMPLE_CODE_H__

/******************************************************************************
 * Function: hx_sample_func();
 *-----------------------------------------------------------------------------
 * Description:
 *  	this is a sample func declare.
 *-----------------------------------------------------------------------------
 * @arg1: IN arguments 1, Must supply;
 * @arg2: IN arguments 2, May NULL;
 * @arg3: IN/OUT, hold return values;
 * @flags: IN other flags;
 *-----------------------------------------------------------------------------
 * Returns:
 *  XER_ERROR: FAIL;
 *  XER_SUCCESS: SUCCESS;
 *-----------------------------------------------------------------------------
 * possible errors:
 * 		ERRNO1: invalid arguments;
 * 		ERRNO2: out of memory;
 *-----------------------------------------------------------------------------
 * History: 
 * 	Add Modification history here if it has
 *****************************************************************************/
extern xeR_t hx_sample_func(IN const char *arg1,IN const char *arg2,
		    					INOUT char *arg3, IN unsigned long  flags);

/******************************************************************************
 * Structure:
 *	hx_sample_struct;
 * Description:
 *	this is a sample struct.
 *  	It is used to ......
 *****************************************************************************/
typedef struct hx_sample_struct
{
	int member1;/*this member used to ...*/
	char *name;/*name of ..., should free() it after use.*/
}hx_sample_t;


#endif /*__HISOME_SAMPLE_CODE_H__*/
