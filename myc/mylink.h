/*        Filename: MYLINK.h
 **********************************************************
 * Description:
 *        this is mylink.c header.
 * Version:
 *        V_0.1 2008.5.28
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.5.28 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */

#ifndef MYLINK_H_2008_5_28
#define MYLINK_H_2008_5_28


#include "mylink_struct.h"


extern mylink_info_struct*mylink_create(void);
extern int mylink_add(mylink_info_struct*param_mylink_info,void *param_data);
extern int mylink_add_index(mylink_info_struct*param_mylink_info,int param_index,void *param_data);
extern int mylink_set_add_fun(mylink_info_struct*param_mylink_info,mylink_add_callback add_fun);
extern void* mylink_del(mylink_info_struct*param_mylink_info,int param_index);
extern void* mylink_del2(mylink_info_struct*param_mylink_info,void *param_data);
extern int mylink_clean(mylink_info_struct*param_mylink_info);
extern int mylink_set_clean_fun(mylink_info_struct*param_mylink_info,mylink_clean_callback clean_fun);
//notice!!!
//mylink_get_data this function should use mylink_lock and mylink_unlock
extern void* mylink_get_data(mylink_info_struct*param_mylink_info,int param_index);
extern int mylink_get_count(mylink_info_struct*param_mylink_info);
extern int mylink_set_find_fun(mylink_info_struct*param_mylink_info,mylink_find_callback find_fun);
extern int mylink_find(mylink_info_struct*param_mylink_info,void*param_data);
extern void mylink_lock(mylink_info_struct*param_mylink_info);
extern void mylink_unlock(mylink_info_struct*param_mylink_info);



#endif /*MYLINK_H_*/
