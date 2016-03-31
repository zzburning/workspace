/*        Filename: mylink.c
 **********************************************************
 * Description:
 *        this is mylink.c.
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

#include "mylink.h"
#include <string.h>
#include "mymem.h"




void mylink_lock(mylink_info_struct*param_mylink_info)
{
#ifdef MYLINK_MULTI_THREAD
	pthread_mutex_lock(&(param_mylink_info->mylink_mutex));
#endif
}

void mylink_unlock(mylink_info_struct*param_mylink_info)
{
#ifdef MYLINK_MULTI_THREAD
	pthread_mutex_unlock(&(param_mylink_info->mylink_mutex));
#endif
}

static void* mylink_get_data_inter(int param_index,mylink_info_struct*param_mylink_info);
static void* mylink_del_inter(int param_index,mylink_info_struct*param_mylink_info);
static int mylink_add_index_inter(mylink_info_struct*param_mylink_info,int param_index,void *param_data);

static mylink_node_struct*mylink_malloc_node()
{
	mylink_node_struct*result=(mylink_node_struct*)mymem_malloc_mysrc(sizeof(mylink_node_struct));
	if(result)
	{
		memset(result,0,sizeof(mylink_node_struct));
		result->data=NULL;
		result->next=NULL;
		result->pre=NULL;
	}
	return result;
}

static void mylink_free_node(mylink_node_struct*param_node)
{
	if(param_node)
	{
		mymem_free(param_node);
	}
}

#ifdef MYLINK_MULTI_THREAD
extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind);
#endif

mylink_info_struct*mylink_create(void)
{
	mylink_info_struct*result=(mylink_info_struct*)mymem_malloc_mysrc(sizeof(mylink_info_struct));
	if(result)
	{
		memset(result,0,sizeof(mylink_info_struct));
		result->count=0;
		result->head=NULL;
		result->tail=NULL;
		result->cur=NULL;
		result->cur_index=-1;
		result->clean_fun=NULL;
		result->find_fun=NULL;
		result->add_fun=NULL;
#ifdef MYLINK_MULTI_THREAD
		//pthread_mutex_init(&(result->mylink_mutex),NULL);		
		pthread_mutexattr_t mutexattr;
		pthread_mutexattr_init(&mutexattr);
		pthread_mutexattr_setpshared(&mutexattr,PTHREAD_PROCESS_PRIVATE);
		pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(&(result->mylink_mutex),&mutexattr);
		pthread_mutexattr_destroy(&mutexattr);
#endif
	}
	return result;
}

/*int mylink_add(mylink_info_struct*param_mylink_info,void *param_data)
{
	mylink_lock(param_mylink_info);
	int result=0;
	if(param_data&&param_mylink_info)
	{
		mylink_node_struct*node=mylink_malloc_node();
		if(node)
		{
			node->data=param_data;
			if(param_mylink_info->count>0)
			{
				node->next=NULL;
				node->pre=param_mylink_info->tail;
				param_mylink_info->tail->next=node;
				param_mylink_info->tail=node;
				param_mylink_info->count++;
			}
			else
			{
				node->next=NULL;
				node->pre=NULL;
				param_mylink_info->head=node;
				param_mylink_info->tail=node;
				param_mylink_info->cur=node;
				param_mylink_info->cur_index=0;
				param_mylink_info->count=1;
			}
			result=0;
		}
		else
		{
			result=-1;
		}
	}
	else
	{
		result=-1;
	}
	mylink_unlock(param_mylink_info);
	return result;
}*/

int mylink_add(mylink_info_struct*param_mylink_info,void *param_data)
{
	int result=0;
	mylink_lock(param_mylink_info);	
	if(param_mylink_info->add_fun&&param_mylink_info->count>0)
	{
		int i=0;
		for(i=0;i<param_mylink_info->count+1;i++)
		{
			int pre_i;
			int next_i;
			void*pre;
			void*next;
			if(i==0)
			{
				pre_i=-1;
				pre=NULL;
				next_i=0;
				next=mylink_get_data_inter(0,param_mylink_info);
			}
			else if(i==param_mylink_info->count)
			{
				pre_i=i-1;
				pre=mylink_get_data_inter(i-1,param_mylink_info);
				next_i=i;
				next=mylink_get_data_inter(i,param_mylink_info);
			}
			else
			{
				pre_i=i-1;
				pre=mylink_get_data_inter(i-1,param_mylink_info);
				next_i=-1;
				next=NULL;
			}
			if(param_mylink_info->add_fun(pre_i,pre,next_i,next,param_data)>=0)
			{
				break;
			}
		}
		if(i>=0&&i<=param_mylink_info->count)
		{
			mylink_add_index_inter(param_mylink_info,i,param_data);
		}
		else
		{
			mylink_add_index_inter(param_mylink_info,param_mylink_info->count,param_data);
		}
	}
	else
	{
		mylink_add_index_inter(param_mylink_info,param_mylink_info->count,param_data);
	}
	mylink_unlock(param_mylink_info);
	return result;
}

static int mylink_add_index_inter(mylink_info_struct*param_mylink_info,int param_index,void *param_data)
{
	int result=0;
	if(param_data&&param_mylink_info&&param_index>=0&&param_index<=param_mylink_info->count)
	{
		mylink_node_struct*node=mylink_malloc_node();
		if(node)
		{
			node->data=param_data;
			if(param_mylink_info->count>0)
			{
				if(param_index==param_mylink_info->count)
				{
					node->next=NULL;
					node->pre=param_mylink_info->tail;
					param_mylink_info->tail->next=node;
					param_mylink_info->tail=node;
				}
				else if(param_index==0)
				{
					node->next=param_mylink_info->head;
					node->pre=NULL;
					param_mylink_info->head->pre=node;
					param_mylink_info->head=node;
				}
				else
				{
					int i=0;
					mylink_node_struct*next=param_mylink_info->head;
					for(i=0;i<param_index;i++)
					{
						next=next->next;
					}
					node->next=next;
					node->pre=next->pre;
					next->pre->next=node;
					next->pre=node;
				}
				param_mylink_info->count++;
				if(param_index<=param_mylink_info->cur_index)
				{
					param_mylink_info->cur_index++;
				}
			}
			else
			{
				node->next=NULL;
				node->pre=NULL;
				param_mylink_info->head=node;
				param_mylink_info->tail=node;
				param_mylink_info->cur=node;
				param_mylink_info->cur_index=0;
				param_mylink_info->count=1;
			}
			result=0;
		}
		else
		{
			result=-1;
		}
	}
	else
	{
		result=-1;
	}
	return result;
}


int mylink_add_index(mylink_info_struct*param_mylink_info,int param_index,void *param_data)
{
	int result=0;
	mylink_lock(param_mylink_info);
	result=mylink_add_index_inter(param_mylink_info,param_index,param_data);
	mylink_unlock(param_mylink_info);
	return result;
}

void* mylink_del2(mylink_info_struct*param_mylink_info,void* param_data)
{
	void*result=NULL;
	int count=0;
	int i=0;
	mylink_lock(param_mylink_info);
	count=param_mylink_info->count;
	i=0;
	for(i=0;i<count;i++)
	{
		if(mylink_get_data_inter(i,param_mylink_info)==param_data)
		{
			break;
		}
	}
	if(i>=0&&i<count)
	{
		result=mylink_del_inter(i,param_mylink_info);
	}
	mylink_unlock(param_mylink_info);
	return result;
}

static void* mylink_del_inter(int param_index,mylink_info_struct*param_mylink_info)
{
	void *result=NULL;
	if(param_mylink_info&&param_index>=0&&param_index<param_mylink_info->count)
	{
		int len=param_index-param_mylink_info->cur_index;
		mylink_node_struct*pre;
		mylink_node_struct*next;
		mylink_node_struct*cur=param_mylink_info->cur;
		if(len>0)
		{
			int i=0;
			for(i=0;i<len;i++)
			{
				cur=cur->next;
				param_mylink_info->cur_index++;
			}
		}
		else if(len<0)
		{
			int i=0;
			for(i=0;i<-len;i++)
			{
				cur=cur->pre;
				param_mylink_info->cur_index--;
			}
		}
		pre=cur->pre;
		next=cur->next;
		result=cur->data;
		if(pre&&next)
		{
			pre->next=next;
			next->pre=pre;
			param_mylink_info->cur=next;
		}
		else if(!pre&&next)
		{
			param_mylink_info->head=next;
			next->pre=NULL;
			param_mylink_info->cur=next;
		}
		else if(pre&&!next)
		{
			param_mylink_info->tail=pre;
			pre->next=NULL;
			param_mylink_info->cur=pre;
			param_mylink_info->cur_index--;
		}
		else if(!pre&&!next)
		{
			param_mylink_info->head=NULL;
			param_mylink_info->tail=NULL;
			param_mylink_info->cur=NULL;
			param_mylink_info->cur_index=-1;
		}
		param_mylink_info->count--;
		mylink_free_node(cur);
	}
	if(param_mylink_info->clean_fun&&result)
	{
		param_mylink_info->clean_fun(result);
		result=NULL;
	}
	return result;
}

void* mylink_del(mylink_info_struct*param_mylink_info,int param_index)
{
	void*result=NULL;
	mylink_lock(param_mylink_info);
	result=mylink_del_inter(param_index,param_mylink_info);
	mylink_unlock(param_mylink_info);
	return result;
}

int mylink_clean(mylink_info_struct*param_mylink_info)
{
	int result=0;
	mylink_lock(param_mylink_info);
	//int result=0;
	if(param_mylink_info&&param_mylink_info->count==0)
	{
		//mymem_free(param_mylink_info);
		result=0;
	}
	else
	{
		if(param_mylink_info->clean_fun)
		{
			while(param_mylink_info->count>0)
			{
				mylink_del_inter(0,param_mylink_info);
			}
			//mymem_free(param_mylink_info);
			result=0;
		}
		else
		{
			result=-1;
		}		
	}
	mylink_unlock(param_mylink_info);
	if(result==0)
	{
#ifdef MYLINK_MULTI_THREAD
		pthread_mutex_destroy(&(param_mylink_info->mylink_mutex));
#endif
		mymem_free(param_mylink_info);
	}	
	return result;
}

static void* mylink_get_data_inter(int param_index,mylink_info_struct*param_mylink_info)
{
	void *result=NULL;
	if(param_mylink_info&&param_index>=0&&param_index<param_mylink_info->count)
	{
		int len=param_index-param_mylink_info->cur_index;
		mylink_node_struct*cur=param_mylink_info->cur;
		if(len>0)
		{
			int i=0;
			for(i=0;i<len;i++)
			{
				cur=cur->next;
				param_mylink_info->cur_index++;
			}
		}
		else if(len<0)
		{
			int i=0;
			for(i=0;i<-len;i++)
			{
				cur=cur->pre;
				param_mylink_info->cur_index--;
			}
		}
		param_mylink_info->cur=cur;
		result=cur->data;
	}
	return result;
}

void* mylink_get_data(mylink_info_struct*param_mylink_info,int param_index)
{
	void*result=NULL;
	mylink_lock(param_mylink_info);
	result=mylink_get_data_inter(param_index,param_mylink_info);
	mylink_unlock(param_mylink_info);
	return result;
}

int mylink_get_count(mylink_info_struct*param_mylink_info)
{
	int result=0;
	mylink_lock(param_mylink_info);
	if(param_mylink_info)
	{
		result=param_mylink_info->count;
	}
	mylink_unlock(param_mylink_info);
	return result;
}

int mylink_set_clean_fun(mylink_info_struct*param_mylink_info,mylink_clean_callback clean_fun)
{
	int result;
	mylink_lock(param_mylink_info);
	if(param_mylink_info)
	{
		param_mylink_info->clean_fun=clean_fun;
		result=0;
	}
	else
	{
		result=-1;
	}
	mylink_unlock(param_mylink_info);
	return result;
}

int mylink_set_add_fun(mylink_info_struct*param_mylink_info,mylink_add_callback add_fun)
{
	int result=0;
	mylink_lock(param_mylink_info);
	if(param_mylink_info)
	{
		param_mylink_info->add_fun=add_fun;
		result=0;
	}
	else
	{
		result=-1;
	}
	mylink_unlock(param_mylink_info);
	return result;
}

int mylink_set_find_fun(mylink_info_struct*param_mylink_info,mylink_find_callback find_fun)
{
	int result=0;
	mylink_lock(param_mylink_info);
	if(param_mylink_info)
	{
		param_mylink_info->find_fun=find_fun;
		result=0;
	}
	else
	{
		result=-1;
	}
	mylink_unlock(param_mylink_info);
	return result;
}
int mylink_find(mylink_info_struct*param_mylink_info,void*param_data)
{
	int result;
	mylink_lock(param_mylink_info);
	if(param_mylink_info&&param_mylink_info->find_fun)
	{
		int count=param_mylink_info->count;
		int i=0;
		for(i=0;i<count;i++)
		{
			int tmp=param_mylink_info->find_fun(param_data,mylink_get_data(param_mylink_info,i));
			if(tmp>=0)
			{
				result=0;
			}
		}
		result=-1;
	}
	else
	{
		result=-1;
	}
	mylink_unlock(param_mylink_info);
	return result;
}





