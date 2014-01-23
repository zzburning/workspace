/*        Filename: mymem.c
 **********************************************************
 * Description:
 *        this is mymem.c .
 * Version:
 *        V_0.1 2008.5.26
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.5.26 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */
#include "mymem.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "mystring.h"
#include <time.h>

#ifdef MYMEM_MULTI_THREAD
#include <pthread.h>
#endif
#if 1
#define print_enter_fun 3
#define enter_fun(level) if(level>=print_enter_fun){printf("enter: %s %s %d\n",__FUNCTION__,__FILE__,__LINE__);}


#ifdef MYMEM_MULTI_THREAD
static pthread_mutex_t mymem_mutex=PTHREAD_MUTEX_INITIALIZER;
static int mymem_mutex_is_init=0;
#endif

static void mymem_init_mutex(void)
{
#ifdef MYMEM_MULTI_THREAD
	if(mymem_mutex_is_init==0)
	{
		pthread_mutex_init(&mymem_mutex,NULL);
		mymem_mutex_is_init=1;
	}
#endif
}

static void mymem_lock(void)
{
#ifdef MYMEM_MULTI_THREAD
	pthread_mutex_lock(&mymem_mutex);
#endif
}

static void mymem_unlock(void)
{
#ifdef MYMEM_MULTI_THREAD
	pthread_mutex_unlock(&mymem_mutex);
#endif
}

typedef struct _mymem_address_list_struct
{
	void *address;
	int count;
	char *file;
	char *fun;
	int line;
	int type;
	struct _mymem_address_list_struct *next;
	struct _mymem_address_list_struct *pre;
}mymem_address_list_struct;

static mymem_address_list_struct *mymem_address_top=NULL;
static mymem_address_list_struct *mymem_address_tail=NULL;
static int mymem_add_list(mymem_address_list_struct*address)
{
	int result=-1;
	enter_fun(2);
	mymem_lock();
	if(address)
	{
		if(mymem_address_top&&mymem_address_tail)
		{
			mymem_address_tail->next=address;
			address->pre=mymem_address_tail;
			mymem_address_tail=address;
			result=0;
		}
		else if(!mymem_address_top&&!mymem_address_tail)
		{
			mymem_address_top=address;
			mymem_address_tail=address;
			address->next=NULL;
			address->pre=NULL;
			result=0;
		}
	}
	mymem_unlock();
	return result;
}
static int mymem_del_list(mymem_address_list_struct*address)
{
	int result=-1;
	enter_fun(2);
	mymem_lock();	
	if(address)
	{
		mymem_address_list_struct*pre=address->pre;
		mymem_address_list_struct*next=address->next;
		if(pre&&next)
		{
			pre->next=next;
			next->pre=pre;
		}
		else if(pre&&!next)
		{
			mymem_address_tail=pre;
			pre->next=NULL;
		}
		else if(!pre&&next)
		{
			mymem_address_top=next;
			next->pre=NULL;
		}
		else
		{
			mymem_address_tail=NULL;
			mymem_address_top=NULL;
		}
		if(address->address)
		{
			free(address->address);
		}
		if(address->file)
		{
			free(address->file);
		}
		if(address->fun)
		{
			free(address->fun);
		}
		free(address);
	}
	mymem_unlock();
	return result;
}

void* mymem_malloc_inter(const int param_size,const int param_type,const char *pfile,const char *pfun,const int pline)
{
	void *result=NULL;
	enter_fun(2);
	mymem_init_mutex();	
	if(param_size>0)
	{
		result=(void*)malloc(param_size);
		memset(result,0,param_size);
		if(result)
		{
			int file_len=-1;
			int fun_len=-1;
			char *file=NULL;
			char *fun=NULL;
			mymem_address_list_struct*one=(mymem_address_list_struct*)malloc(sizeof(mymem_address_list_struct));
			one->address=result;
			one->count=param_size;
			file_len=strlen(pfile)+1;
			fun_len=strlen(pfun)+1;
			file=(char*)malloc(file_len);
			fun=(char*)malloc(fun_len);
			memset(file,0,file_len);
			memset(fun,0,fun_len);
			mystrncpy(file,file_len,pfile);
			mystrncpy(fun,fun_len,pfun);
			one->file=file;
			one->fun=fun;
			one->line=pline;
			one->type=param_type;
			one->next=NULL;
			one->pre=NULL;
			mymem_add_list(one);
		}
	}
	return result;
}

char*mymem_strdup_inter(const char*param_string,const int param_type,const char *pfile,const char *pfun,const int pline)
{
	char *result=NULL;
	enter_fun(2);
	mymem_init_mutex();	
	if(param_string)
	{
		result=strdup(param_string);
		if(result)
		{
			int file_len=-1;
			int fun_len=-1;
			char *file=NULL;
			char *fun=NULL;
			mymem_address_list_struct*one=(mymem_address_list_struct*)malloc(sizeof(mymem_address_list_struct));
			one->address=result;
			one->count=strlen(result+1);
			file_len=strlen(pfile)+1;
			fun_len=strlen(pfun)+1;
			file=(char*)malloc(file_len);
			fun=(char*)malloc(fun_len);
			memset(file,0,file_len);
			memset(fun,0,fun_len);
			mystrncpy(file,file_len,pfile);
			mystrncpy(fun,fun_len,pfun);
			one->file=file;
			one->fun=fun;
			one->line=pline;
			one->type=param_type;
			one->next=NULL;
			one->pre=NULL;
			mymem_add_list(one);
		}
	}
	return result;
}

void mymem_free(void *param)
{
	enter_fun(2);
	mymem_init_mutex();
	if(param)
	{
		mymem_address_list_struct*del=mymem_address_top;
		int del_flag=0;
		while(del)
		{
			if(del->address==param)
			{
				mymem_del_list(del);
				del_flag=1;
				break;
			}
			del=del->next;
		}
		if(del_flag==0)
		{
			free(param);
		}
	}
}

static int mymem_get_int_len(const int param)
{
	char s[64];
	memset(s,0,sizeof(s));
	snprintf(s,sizeof(s),"%d",param);
	return strlen(s);
}

int mymem_print(const char *file)
{
	
	int global_count=0;
	int local_count=0;
	int mysrc_count=0;
	mymem_address_list_struct*one=mymem_address_top;
	int global_i=0;
	int local_i=0;
	int mysrc_i;
	int num_i=0;
	unsigned int num_len=0;
	unsigned int file_len=0;
	unsigned int fun_len=0;
	unsigned int line_len=0;
	unsigned int mem_len=0;
	int max_line=0;
	int max_mem=0;
	FILE *p_file=NULL;

	char s1[1024]="";
	char s2[1024]="";
	char *t1="num";
	char *t2="file";
	char *t3="fun";
	char *t4="line";
	char *t5="mem";
	
	enter_fun(2);
	mymem_init_mutex();
	mymem_lock();

	if(file)
	{
		p_file=fopen(file,"a+");
		if(p_file)
		{
			time_t t=time(NULL);
			struct tm *r;
			r=localtime(&t);
			fprintf(p_file,"----------------------------\n");
			fprintf(p_file,"%04d-%02d-%02d %02d:%02d:%02d",r->tm_year+1900, r->tm_mon+1, r->tm_mday,r->tm_hour, r->tm_min, r->tm_sec);
		}
	}
	num_i=0;
	while(one)
	{
		if(strlen(one->file)>file_len)
		{
			file_len=strlen(one->file);
		}
		if(strlen(one->fun)>fun_len)
		{
			fun_len=strlen(one->fun);
		}
		if(one->line>max_line)
		{
			max_line=one->line;
		}
		if(one->count>max_mem)
		{
			max_mem=one->count;
		}
		num_i++;
		one=one->next;
	}
	num_len=mymem_get_int_len(num_i);
	line_len=mymem_get_int_len(max_line);
	mem_len=mymem_get_int_len(max_mem);
	//char s1[1024];
	//char s2[1024];
	memset(s1,0,sizeof(s1));
	memset(s2,0,sizeof(s2));
	//char *t1="num";
	//char *t2="file";
	//char *t3="fun";
	//char *t4="line";
	//char *t5="mem";
	if(strlen(t1)>num_len)
	{
		num_len=strlen(t1);
	}
	if(strlen(t2)>file_len)
	{
		file_len=strlen(t2);
	}
	if(strlen(t3)>fun_len)
	{
		fun_len=strlen(t3);
	}
	if(strlen(t4)>line_len)
	{
		line_len=strlen(t4);
	}
	if(strlen(t5)>mem_len)
	{
		mem_len=strlen(t5);
	}
	snprintf(s1,sizeof(s1),"%%-%ds %%-%ds %%-%ds %%-%ds %%-%ds\n",num_len,file_len,fun_len,line_len,mem_len);
	snprintf(s2,sizeof(s2),"%%-%dd %%-%ds %%-%ds %%-%dd %%-%dd\n",num_len,file_len,fun_len,line_len,mem_len);
	one=mymem_address_top;
	local_i=0;
	while(one)
	{
		if(one->type==mymem_value_type_local)
		{
			local_count+=one->count;
			if(local_i==0)
			{
				printf("\nlocal\n");				
				printf(s1,t1,t2,t3,t4,t5);
				if(p_file)
				{
					fprintf(p_file,"\nlocal\n");
					fprintf(p_file,s1,t1,t2,t3,t4,t5);
				}
			}
			printf(s2,local_i+1,one->file,one->fun,one->line,one->count);
			if(p_file)
			{
				fprintf(p_file,s2,local_i+1,one->file,one->fun,one->line,one->count);
			}
			local_i++;
		}
		one=one->next;
	}
	one=mymem_address_top;
	mysrc_i=0;
	while(one)
	{
		if(one->type==mymem_value_type_mysrc)
		{
			mysrc_count+=one->count;
			if(mysrc_i==0)
			{
				printf("\nmysrc\n");
				printf(s1,t1,t2,t3,t4,t5);
				if(p_file)
				{
					fprintf(p_file,"\nmysrc\n");
					fprintf(p_file,s1,t1,t2,t3,t4,t5);
				}
			}
			printf(s2,mysrc_i+1,one->file,one->fun,one->line,one->count);
			if(p_file)
			{
				fprintf(p_file,s2,mysrc_i+1,one->file,one->fun,one->line,one->count);
			}
			mysrc_i++;
		}
		one=one->next;
	}
	one=mymem_address_top;
	global_i=0;
	while(one)
	{
		if(one->type==mymem_value_type_golbal)
		{
			global_count+=one->count;
			if(global_i==0)
			{
				printf("\nglobal\n");
				printf(s1,t1,t2,t3,t4,t5);
				if(p_file)
				{
					fprintf(p_file,"\nglobal\n");
					fprintf(p_file,s1,t1,t2,t3,t4,t5);
				}
			}
			printf(s2,global_i+1,one->file,one->fun,one->line,one->count);
			if(p_file)
			{
				fprintf(p_file,s2,global_i+1,one->file,one->fun,one->line,one->count);
			}
			global_i++;
		}
		one=one->next;
	}
	if(global_count+local_count+mysrc_count>0)
	{
		printf("local_block:%d\nlocal_memory:%d\n", local_i, local_count);
		if (p_file)
		{
			fprintf(p_file, "local_block:%d\nlocal_memory:%d\n", local_i,local_count);
		}
		printf("mysrc_block:%d\nmysrc_memory:%d\n", mysrc_i, mysrc_count);
		if (p_file)
		{
			fprintf(p_file, "mysrc_block:%d\nmysrc_memory:%d\n", mysrc_i,	mysrc_count);
		}
		printf("glocal_block:%d\nglocal_memory:%d\n\n", global_i,global_count);
		if (p_file)
		{
			fprintf(p_file, "glocal_block:%d\nglocal_memory:%d\n\n", global_i,global_count);
		}
	}
	else
	{
		printf("\nmemory status is ok, tested by mymem!\n\n");
		if(p_file)
		{
			fprintf(p_file,"\nmemory status is ok, tested by mymem!\n\n");
		}
	}
	if(p_file)
	{
		fclose(p_file);
	}
	mymem_unlock();
	return global_count+local_count+mysrc_count;
}

#endif







