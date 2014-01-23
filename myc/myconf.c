/*        Filename: myconf.c
 **********************************************************
 * Description:
 *        this is myconf.c.
 * Version:
 *        V_0.1 2008.6.6
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.6.6 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */


#include <stdio.h>
#include <string.h>
#include "myconf.h"
#include "mymem.h"
#include "mystring.h"

//#define myconf_print_loc

#ifdef myconf_print_loc
#define myconf_loc() printf("loc: %s %s %d\n",__FUNCTION__,__FILE__,__LINE__);
#else
#define myconf_loc()
#endif

static int MAX_ONE_LINE=1024;

const int MYCONF_FIND=0;
const int MYCONF_CASE_FIND=1;


static char* myconf_copy(const char*param_start,const char*param_end)
{
	myconf_loc();
	if (param_start&&param_end&&param_end>=param_start)
	{
		int len=param_end-param_start+2;
		int i=0;
		char *content=(char*)mymem_malloc(len);
		if (content)
		{
			memset(content,0,len);	
			for (i=0;i<len-1;i++)
			{
				content[i]=param_start[i];
			}
			return content;
		}		
	}
	return NULL;
}

static void myconf_clean_value_link_fun(void *param)
{
	myconf_loc();
	if(param)
	{
		mymem_free(param);
	}
}

static myconf_struct* myconf_malloc_newnode(const char *param_name,const char *param_value)
{
	myconf_loc();
	if(param_name&&param_value)
	{
		myconf_struct*node=(myconf_struct*)mymem_malloc(sizeof(myconf_struct));
		char *name=(char*)mymem_malloc(strlen(param_name)+1);
		mystrncpy(name,strlen(param_name)+1,param_name);
		node->name=name;
		mylink_info_struct*value_link=(mylink_info_struct*)mymem_malloc(sizeof(mylink_info_struct));
		char *value=(char*)mymem_malloc(strlen(param_value)+1);
		mystrncpy(value,strlen(param_value)+1,param_value);
		mylink_set_clean_fun(value_link,myconf_clean_value_link_fun);
		mylink_add(value_link,value);
		node->value=value_link;
		return node;
	}
	else
	{
		return NULL;
	}
}

static myconf_struct*myconf_find(myconf_info_struct*param_myconf_info,const char*param_name)
{
	myconf_loc();
	if(param_myconf_info&&param_myconf_info->head&&param_name)
	{
		int count=mylink_get_count(param_myconf_info->head);
		int i=0;
		myconf_struct*one;
		for(i=0;i<count;i++)
		{
			one=mylink_get_data(param_myconf_info->head,i);
			if(one)
			{
				if(param_myconf_info->find_type==MYCONF_FIND)
				{
					if(!strcmp(one->name,param_name))
					{
						return one;
					}
				}
				else
				{
					if(!strcasecmp(one->name,param_name))
					{
						return one;
					}
				}
			}
		}
	}
	return NULL;
}

static int myconf_add_node(myconf_struct*param_node,const char *param_value)
{
	myconf_loc();
	if(param_value&&param_node)
	{
		char *value=(char*)mymem_malloc(strlen(param_value)+1);
		mystrncpy(value,strlen(param_value)+1,param_value);
		mylink_add(param_node->value,value);
		return 0;
	}
	else
	{
		return -1;
	}
}

static int myconf_add_value(myconf_info_struct*param_myconf_info,const char *param_name,const char *param_value)
{
	myconf_loc();
	if(param_name&&param_myconf_info)
	{
		if(param_myconf_info->head)
		{
			myconf_struct*node=myconf_find(param_myconf_info,param_name);
			if(node)
			{
				myconf_add_node(node,param_value);
			}
			else
			{
				myconf_struct*one=myconf_malloc_newnode(param_name,param_value);
				mylink_add(param_myconf_info->head,one);
			}
		}
		else
		{
			myconf_struct*one=myconf_malloc_newnode(param_name,param_value);
			mylink_add(param_myconf_info->head,one);
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

static int check_oneline(const char*param_oneline)
{
	int result=0;
	if(param_oneline)
	{
		int count=strlen(param_oneline);
		if(count>0)
		{
			if(strstr(param_oneline,"="))
			{
				const char *pos=param_oneline;
				while(pos!='\0')
				{
					if(*pos==' '||*pos=='	')
					{
						pos++;
					}
					else
					{
						break;
					}
				}
				if(*pos=='\0'||*pos=='#')
				{
					result=-4;
				}
				else
				{
					result=0;
				}
			}
			else
			{
				result=-3;
			}
		}
		else
		{
			result=-2;
		}
	}
	else
	{
		result=-1;
	}
	return result;
}

static int myconf_do_oneline(myconf_info_struct*param_head,const char *param_oneline)
{
	myconf_loc();
	if(param_oneline&&param_head&&check_oneline(param_oneline)>=0)
	{
		const char *name_start=param_oneline;
		const char *value_end=param_oneline+strlen(param_oneline)-1;
		const char *name_end=NULL;
		const char *value_start=NULL;
		while(1)
		{
			if(name_start>=value_end)
			{
				return -1;
			}
			int flag=0;
			if(*name_start==' '||*name_start=='	'||*name_start=='\n'||*name_start=='\r')
			{
				name_start++;
				flag=1;
			}
			if(*value_end==' '||*value_end=='	'||*value_end=='\n'||*value_end=='\r')
			{
				value_end--;
				flag=1;
			}
			if(flag==0)
			{
				break;
			}
		}
		const char *equal=strstr(param_oneline,"=");
		if(equal&&equal>name_start&&equal<value_end)
		{
			name_end=equal-1;
			value_start=equal+1;
			while(1)
			{
				if(name_start>name_end)
				{
					return -1;
				}
				if(*name_end==' '||*name_end=='	'||*name_end=='\n'||*name_end=='\r')
				{
					name_end--;
				}
				else
				{
					break;
				}
			}
			while(1)
			{
				if(value_start>value_end)
				{
					return -1;
				}
				if(*value_start==' '||*value_start=='	'||*value_start=='\n'||*value_start=='\r')
				{
					value_start++;
				}
				else
				{
					break;
				}
			}
		}
		char *name=myconf_copy(name_start,name_end);
		char *value=myconf_copy(value_start,value_end);
		if(name[0]!='#')
		{
			myconf_add_value(param_head,name,value);
		}
		mymem_free(name);
		mymem_free(value);
	}
	return 0;
}

myconf_info_struct* myconf_parser(const char *param_file,int param_find_type)
{
	myconf_loc();
	if(param_file)
	{
		FILE *p=fopen(param_file,"r");
		if(p)
		{
			myconf_info_struct* info=(myconf_info_struct*)mymem_malloc(sizeof(myconf_info_struct));
			mylink_info_struct* head=mylink_create();
			info->find_type=param_find_type;
			info->head=head;
			char oneline[MAX_ONE_LINE];
			memset(oneline,0,sizeof(oneline));
			int i=0;
			while(1)
			{
				signed char c;
				c=fgetc(p);
				if(c==EOF)
				{
					myconf_do_oneline(info,oneline);
					memset(oneline,0,sizeof(oneline));
					i=0;
					break;
				}
				else if(c=='\r'||c=='\n')
				{
					myconf_do_oneline(info,oneline);
					memset(oneline,0,sizeof(oneline));
					i=0;
				}
				else
				{
					oneline[i]=c;
					i++;
				}
			}
			fclose(p);
			return info;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

static void myconf_clean_node_link(void *param)
{
	myconf_loc();
	if(param)
	{
		myconf_struct*one=(myconf_struct*)param;
		mymem_free(one->name);
		mylink_clean(one->value);
		mymem_free(one);
	}
}

int myconf_clean(myconf_info_struct*param_conf_info)
{
	myconf_loc();
	if(param_conf_info)
	{
		if(param_conf_info->head)
		{
			mylink_set_clean_fun(param_conf_info->head,myconf_clean_node_link);
			mylink_clean(param_conf_info->head);
		}
		mymem_free(param_conf_info);
		return 0;
	}
	else
	{
		return -1;
	}
}

int myconf_get_value_count(myconf_info_struct*param_myconf_info,const char *param_name)
{
	myconf_loc();
	if(param_name&&param_myconf_info)
	{
		myconf_struct*node=myconf_find(param_myconf_info,param_name);
		if(node)
		{
			return mylink_get_count(node->value);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return -1;
	}
}

const char* myconf_get_value(myconf_info_struct*param_myconf_info,const int param_index,const char*param_name)
{
	myconf_loc();
	if(param_name&&param_myconf_info&&param_index>=0)
	{
		myconf_struct*node=myconf_find(param_myconf_info,param_name);
		if(node)
		{
			return mylink_get_data(node->value,param_index);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

int myconf_get_name_count(myconf_info_struct*param_myconf_info)
{
	myconf_loc();
	if(param_myconf_info&&param_myconf_info->head)
	{
		return mylink_get_count(param_myconf_info->head);
	}
	else
	{
		return -1;
	}
}
const char* myconf_get_name(myconf_info_struct*param_myconf_info,const int param_index)
{
	myconf_loc();
	if(param_index>=0&&param_myconf_info&&param_myconf_info->head)
	{
		myconf_struct*node=mylink_get_data(param_myconf_info->head,param_index);
		if(node)
		{
			return node->name;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}










