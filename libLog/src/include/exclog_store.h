/*******************************************************************************************
 * 					Filename: exclog_store.h
********************************************************************************************
 * Description:
 * 		this is a file header of exclog_store.c for libexcLOG. 
 * Version:
 * 	    V_0.1 Aug-11-2010
 * Copyright:
 * Author: 
 * History:
 * 		 V_0.1 Initial version of this code.
********************************************************************************************/
#ifndef __EXCLOG_STORE_H_
#define __EXCLOG_STORE_H_

#include "exclog_public.h"

/**
 * Define flash information
 */
typedef struct exclog_flash_info
{
	/**
	 * flash region start position from the begining of MTD
	 */
	int offset;
	
	/**
	 * total size
	 */
	int size;
	
	/**
	 * flash region status
	 * 0-not full
	 * 1-full
	 */
	int status ;

	/**
	 * current write position from the beginning of this region
	 */
	int pos;
	
	/**
	 * left space of this region
	 */
	int left;
}exclog_flash_info_t;

extern exclog_flash_info_t region_list[EXCLOG_FILE_NUM_MAX];/*memory region info array*/
extern int region_num;/*total region num*/
extern int region_cur;/*current working region*/
/********************************************************************************************
 * Function: _exclog_store()
 *----------------------------------------------------------------------------------------------------------------------------------------
 * Description: format log and store it.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Parameters:
 * @ pkt:IN,log to store.
 *---------------------------------------------------------------------------------------------------------------------------------------- 
 * Return :
 * 		 0:success.
 * 		-1:fail.
 ********************************************************************************************/
int _exclog_store(const exclog_packet_t *pkt);

#endif/*__EXCLOG_STORE_H_*/
