/*        Filename: mylink_struct.h
 **********************************************************
 * Description:
 *        this is mylink.h header.
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

#ifndef MYLINK_STRUCT_H_2008_5_28
#define MYLINK_STRUCT_H_2008_5_28


#include "common.h"

#ifdef MYLINK_MULTI_THREAD
#include <pthread.h>
#endif

typedef struct _mylink_node_struct
{
	void * data;
	struct _mylink_node_struct*pre;
	struct _mylink_node_struct*next;
}mylink_node_struct;

typedef void(*mylink_clean_callback)(void*param_data);
typedef int(*mylink_find_callback)(void*param_data1,void*param_data2);
typedef int(*mylink_add_callback)(int param_pre_index,void*param_pre_data,int param_next_index,void*param_next_data,void*param_insert_data);

typedef struct _mylink_info_struct
{
	mylink_node_struct*head;
	mylink_node_struct*tail;
	mylink_node_struct*cur;
	int cur_index;
	int count;
	mylink_clean_callback clean_fun;
	mylink_find_callback find_fun;
	mylink_add_callback add_fun;
#ifdef MYLINK_MULTI_THREAD
	pthread_mutex_t mylink_mutex;
#endif
}mylink_info_struct;






#endif /*MYLINK_STRUCT_H_*/
