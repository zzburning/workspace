/*        Filename: myxml.c
 **********************************************************
 * Description:
 *        this is myxml.c .
 * Version:
 *        V_0.1 2008.5.20
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.5.20 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */
#ifndef MYSRC_WITHOUT_XML
#define MYXML_NEW


#ifdef MYXML_NEW

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "myxml.h"
#include "common.h"

static void myxml_free_attribute(myxml_attribute_struct*param_attribute)
{
	if(param_attribute)
	{
		if(param_attribute->next)
		{
			myxml_free_attribute(param_attribute->next);
		}
		if(param_attribute->name)
		{
			free(param_attribute->name);
		}
		if(param_attribute->value)
		{
			free(param_attribute->value);
		}
		free(param_attribute);
	}
}
static void myxml_free_node(myxml_node_struct*param_node)
{
	if(param_node)
	{
		if(param_node->child_node)
		{
			myxml_free_node(param_node->child_node);
		}
		if(param_node->next_node)
		{
			myxml_free_node(param_node->next_node);
		}
		if(param_node->name)
		{
			free(param_node->name);
		}
		if(param_node->content)
		{
			free(param_node->content);
		}
		if(param_node->attribute)
		{
			myxml_free_attribute(param_node->attribute);
		}
		free(param_node);
	}	
}

void myxml_free(myxml_node_struct*param_node)
{
	if(param_node)
	{
		myxml_node_struct*root=param_node;
		while(root->father_node)
		{
			root=root->father_node;
		}
		while(root->pre_node)
		{
			root=root->pre_node;
		}
		myxml_free_node(root);
	}
}

typedef enum _myxml_lable_type_enum
{
	myxml_lable_type_error,
	myxml_lable_type_start,//<table>
	myxml_lable_type_end,//</table>
	myxml_lable_type_middle,//<table/>
	myxml_lable_type_head,//<?xml  ?>
	myxml_lable_type_note,//<!--  -->
	myxml_lable_type_text,//table
}myxml_lable_type_enum;

typedef enum _myxml_keyword_type_enum
{
	//<    <!--   <?xml     </     -->     ?>   >   />
	myxml_keyword_type_left_normal,//   <
	myxml_keyword_type_left_note,//     <!--
	myxml_keyword_type_left_head,//     <?xml
	myxml_keyword_type_left_end,//      </
	myxml_keyword_type_left_content,//  a~z A~Z and so on
	myxml_keyword_type_right_note,//    -->
	myxml_keyword_type_right_head,//    ?>
	myxml_keyword_type_right_normal,//  >
	myxml_keyword_type_right_middle,//  />
	myxml_keyword_type_right_content,// a~z A~Z and so on
	myxml_keyword_type_error,
}myxml_keyword_type_enum;

typedef struct _myxml_keyword_pos_struct
{
	const char *keyword_start;
	const char *keyword_end;
	myxml_keyword_type_enum keyword_type;
}myxml_keyword_pos_struct;

typedef struct _myxml_lable_pos_struct
{
	myxml_keyword_pos_struct lable_start;
	myxml_keyword_pos_struct lable_end;
	myxml_lable_type_enum lable_type;
}myxml_lable_pos_struct;

static int keyword_copy(const myxml_keyword_pos_struct*param_ori,myxml_keyword_pos_struct*param_des)
{
	int result=-1;
	if(param_ori&&param_des)
	{
		memcpy(param_des,param_ori,sizeof(myxml_keyword_pos_struct));
		result=0;
	}
	return result;
}

static myxml_lable_pos_struct keyword_to_lable(myxml_keyword_pos_struct param_start,myxml_keyword_pos_struct param_end)
{
	myxml_lable_pos_struct result={{NULL,NULL,myxml_keyword_type_error},{NULL,NULL,myxml_keyword_type_error},myxml_lable_type_error};
	/*
	 * myxml_lable_type_start,//<table>
	myxml_lable_type_end,//</table>
	myxml_lable_type_middle,//<table/>
	myxml_lable_type_head,//<?xml  ?>
	myxml_lable_type_note,//<!--  -->
	myxml_lable_type_text,//table
	 */
	if (param_start.keyword_start&&param_start.keyword_end&&param_end.keyword_start&&param_end.keyword_end&&param_start.keyword_start<=param_start.keyword_end&&param_start.keyword_end<=param_end.keyword_start&&param_end.keyword_start<=param_end.keyword_end)
	{
		if (param_start.keyword_type==myxml_keyword_type_left_normal&&param_end.keyword_type==myxml_keyword_type_right_normal)
		{
			result.lable_type=myxml_lable_type_start;
		}
		else if (param_start.keyword_type==myxml_keyword_type_left_end&&param_end.keyword_type==myxml_keyword_type_right_normal)
		{
			result.lable_type=myxml_lable_type_end;
		}
		else if (param_start.keyword_type==myxml_keyword_type_left_normal&&param_end.keyword_type==myxml_keyword_type_right_middle)
		{
			result.lable_type=myxml_lable_type_middle;
		}
		else if (param_start.keyword_type==myxml_keyword_type_left_head&&param_end.keyword_type==myxml_keyword_type_right_head)
		{
			result.lable_type=myxml_lable_type_head;
		}
		else if (param_start.keyword_type==myxml_keyword_type_left_note&&param_end.keyword_type==myxml_keyword_type_right_note)
		{
			result.lable_type=myxml_lable_type_note;
		}
		else if (param_start.keyword_type==myxml_keyword_type_left_content&&param_end.keyword_type==myxml_keyword_type_right_content)
		{
			result.lable_type=myxml_lable_type_text;
		}
		else
		{
			result.lable_type=myxml_lable_type_error;
		}
	}
	else
	{
		result.lable_type=myxml_lable_type_error;
	}
	if (result.lable_type!=myxml_lable_type_error)
	{
		keyword_copy(&param_start, &result.lable_start);
		keyword_copy(&param_end, &result.lable_end);
	}
	return result;
}

typedef enum _myxml_split_flag_enum
{
	myxml_split_flag_true,
	myxml_split_flag_false,
}myxml_split_flag_enum;

static myxml_split_flag_enum myxml_is_split_flag(const char param_char)
{
	if(param_char==' '||param_char=='	'||param_char=='\n')
	{
		return myxml_split_flag_true;
	}
	else
	{
		return myxml_split_flag_false;
	}
}


static myxml_lable_pos_struct myxml_lable_parser(const char *param_start,const char *param_end)
{
	myxml_lable_pos_struct result={{NULL,NULL},{NULL,NULL},myxml_lable_type_error};
	if(param_start&&param_end&&param_end>=param_start)
	{
		/*myxml_lable_type_error,
			myxml_lable_type_start,//<table>
			myxml_lable_type_end,//</table>
			myxml_lable_type_middle,//<table/>
			myxml_lable_type_head,//<?xml  ?>
			myxml_lable_type_note,//<!--  -->
			myxml_lable_type_text,//table*/
		const char *i=NULL;
		myxml_keyword_pos_struct lable_start={NULL,NULL,myxml_keyword_type_error};
		myxml_keyword_pos_struct lable_end={NULL,NULL,myxml_keyword_type_error};
		for(i=param_start;i<=param_end;i++)
		{
			if(myxml_is_split_flag(*i)==myxml_split_flag_false)
			{
				if(*i=='<')
				{
					if(i+1)
					{
						if(i[1]=='/')
						{
							lable_start.keyword_end=i+1;
							lable_start.keyword_type=myxml_keyword_type_left_end;
						}
						else if(i[1]=='?')
						{
							if(i+2&&i+3&&i+4&&(i[2]=='x'||i[2]=='X')&&(i[3]=='m'||i[3]=='M')&&(i[4]=='l'||i[4]=='L'))
							{
								lable_start.keyword_end=i+4;
								lable_start.keyword_type=myxml_keyword_type_left_head;
							}
						}
						else if(i[1]=='!')
						{
							if(i+2&&i+3&&i[2]=='-'&&i[3]=='-')
							{
								lable_start.keyword_end=i+3;
								lable_start.keyword_type=myxml_keyword_type_left_note;
							}
						}
						else
						{
							lable_start.keyword_end=i;
							lable_start.keyword_type=myxml_keyword_type_left_normal;
						}
					}
					else
					{
					}
				}
				else
				{
					lable_start.keyword_end=i;
					lable_start.keyword_type=myxml_keyword_type_left_content;
				}
				lable_start.keyword_start=i;
				break;
			}
			else
			{
			}
		}
		if(i&&lable_start.keyword_type!=myxml_keyword_type_error)
		{
			for(;i<=param_end;i++)
			{
				if(lable_start.keyword_type==myxml_keyword_type_left_content)
				{
					if(*i=='<'||i==param_end)
					{
						while(i)
						{
							if(myxml_is_split_flag(*i)==myxml_split_flag_false&&*i!='<')
							{
								lable_end.keyword_start=i;
								lable_end.keyword_end=i;
								lable_end.keyword_type=myxml_keyword_type_right_content;
								break;
							}
							i--;
						}
						break;
					}
				}
				else if(lable_start.keyword_type==myxml_keyword_type_left_note)
				{
					if(*i=='-')
					{
						if(i+1&&i+2&&i[1]=='-'&&i[2]=='>')
						{
							lable_end.keyword_start=i;
							lable_end.keyword_end=i+2;
							lable_end.keyword_type=myxml_keyword_type_right_note;
							break;
						}
					}
				}
				else
				{
					if(*i=='>')
					{
						lable_end.keyword_end=i;
						if(i-1)
						{
							if(i[-1]=='/')
							{
								lable_end.keyword_start=i-1;
								lable_end.keyword_type=myxml_keyword_type_right_middle;
							}
							else if(i[-1]=='?')
							{
								lable_end.keyword_start=i-1;
								lable_end.keyword_type=myxml_keyword_type_right_head;
							}
							else
							{
								lable_end.keyword_start=i;
								lable_end.keyword_type=myxml_keyword_type_right_normal;
							}
						}
						break;
					}
				}
			}
		}
		result=keyword_to_lable(lable_start,lable_end);
	}
	return result;
}

myxml_node_struct *myxml_malloc_node(void)
{
	myxml_node_struct*result=(myxml_node_struct*)malloc(sizeof(myxml_node_struct));
	if(result)
	{
		memset(result,0,sizeof(result));
		result->type=myxml_node_error;
		result->depth=0;
		result->name=NULL;
		result->content=NULL;
		result->attribute=NULL;
		result->father_node=NULL;
		result->child_node=NULL;
		result->next_node=NULL;
		result->pre_node=NULL;
	}
	return result;
}

static int myxml_copy(const char*param_start,const char*param_end,char *param_result,const int param_result_len)
{
	int result=-1;
	if(param_start&&param_end&&param_result&&param_end>=param_start&&param_end-param_start+1<param_result_len)
	{
		const char *tmp;
		result=0;
		for(tmp=param_start;tmp<=param_end;tmp++)
		{
			param_result[result++]=*tmp;
		}
	}
	return result;
}

static int myxml_parser_lable_name(myxml_node_struct*param_node,const char *param_start,const char *param_end,const char **param_result_start,const char **param_result_end)
{
	int result=-1;
	if(param_result_start)
	{
		*param_result_start=NULL;
	}
	if(param_result_end)
	{
		*param_result_end=NULL;
	}
	if(param_node&&param_start&&param_end)
	{
		const char *i;
		const char *name_start=NULL;
		const char *name_end=NULL;
		for(i=param_start;i<=param_end;i++)
		{
			if(myxml_is_split_flag(*i)==myxml_split_flag_false)
			{
				name_start=i;
				break;
			}
		}
		if(name_start)
		{
			name_end=param_end;
			for(i=name_start;i<=param_end;i++)
			{
				if(myxml_is_split_flag(*i)==myxml_split_flag_true)
				{
					name_end=i-1;
					break;
				}
			}
		}
		if(name_start&&name_end&&name_end>=name_start)
		{
			int name_len=name_end-name_start+1;
			char *name=(char*)malloc(name_len+1);
			if(name)
			{
				memset(name,0,name_len+1);
				myxml_copy(name_start,name_end,name,name_len+1);
				param_node->name=name;
				if(param_result_start)
				{
					*param_result_start=name_start;
				}
				if(param_result_end)
				{
					*param_result_end=name_end;
				}
				result=0;
			}
		}
	}
	return result;
}

static int myxml_parser_attribute(myxml_node_struct*param_node,const char*param_start,const char*param_end)
{
	int result=0;
	if(param_start<=param_end)
	{
		int flag=0;
		//0[1name]2=3["4value"]0
		const char *attribute_name_start=NULL;
		const char *attribute_name_end=NULL;
		const char *attribute_value_start=NULL;
		const char *attribute_value_end=NULL;
		const char *i=NULL;
		for(i=param_start;i<=param_end;i++)
		{
			switch(flag)
			{
			case 0:
				if(myxml_is_split_flag(*i)==myxml_split_flag_false)
				{
					attribute_name_start=i;
					flag=1;
				}
				break;
			case 1:
				if(myxml_is_split_flag(*i)==myxml_split_flag_true)
				{
					attribute_name_end=i-1;
					flag=2;
				}
				else if(*i=='=')
				{
					attribute_name_end=i-1;
					flag=3;
				}
				break;
			case 2:
				if(*i=='=')
				{
					flag=3;
				}
				break;
			case 3:
				if(*i=='\''||*i=='"')
				{
					attribute_value_start=i;
					flag=4;
				}
				break;
			case 4:
				if(*i=='\''||*i=='"')
				{
					attribute_value_end=i;
					flag=0;
					if(attribute_name_start&&attribute_name_end&&attribute_value_start&&attribute_value_end)
					{
						if(attribute_name_end>=attribute_name_start&&attribute_value_end>attribute_value_start&&attribute_value_start>attribute_name_end)
						{
							int name_len=attribute_name_end-attribute_name_start+1;
							int value_len=attribute_value_end-attribute_value_start-1;
							char *name=NULL;
							char *value=NULL;
							if(name_len>0)
							{
								name=(char*)malloc(name_len+1);
								memset(name,0,name_len+1);
								myxml_copy(attribute_name_start,attribute_name_end,name,name_len+1);
							}
							if(value_len>0)
							{
								value=(char*)malloc(value_len+1);
								memset(value,0,value_len+1);
								myxml_copy(attribute_value_start+1,attribute_value_end-1,value,value_len+1);
							}
							if (name)
							{
								myxml_attribute_struct*attribute=(myxml_attribute_struct*)malloc(sizeof(myxml_attribute_struct));
								if(attribute)
								{
									memset(attribute,0,sizeof(myxml_attribute_struct));
									attribute->name=name;
									attribute->value=value;
									attribute->next=NULL;
									attribute->pre=NULL;
									if(param_node->attribute)
									{
										myxml_attribute_struct*last=param_node->attribute;
										while(last->next)
										{
											last=last->next;
										}
										last->next=attribute;
										attribute->pre=last;
									}
									else
									{
										param_node->attribute=attribute;
									}
								}
							}
						}
					}
					attribute_name_start=NULL;
					attribute_name_end=NULL;
					attribute_value_start=NULL;
					attribute_value_end=NULL;
				}
				break;
			default:
				break;
			}
		}
	}
	return result;
}

static int myxml_parser_lable_name_attribute(myxml_node_struct*param_node,myxml_lable_pos_struct*param_lable_pos)
{
	int result=-1;
	const char *start=param_lable_pos->lable_start.keyword_end+1;
	const char *end=param_lable_pos->lable_end.keyword_start-1;
	const char *name_start=NULL;
	const char *name_end=NULL;
	result=myxml_parser_lable_name(param_node,start,end,&name_start,&name_end);
	if(result==0)
	{
		result=myxml_parser_attribute(param_node,name_end+1,end);
	}
	return result;
}

static int myxml_parser_lable_head(myxml_node_struct*param_node,myxml_lable_pos_struct*param_lable_pos)
{
	int result=-1;
	const char *start=param_lable_pos->lable_start.keyword_end+1;
	const char *end=param_lable_pos->lable_end.keyword_start-1;
	result=myxml_parser_attribute(param_node,start,end);
	return result;
}

static int myxml_parser_lable_note(myxml_node_struct*param_node,myxml_lable_pos_struct*param_lable_pos)
{
	int result=-1;
	if (param_node&&param_lable_pos)
	{
		const char *start=NULL;
		const char *end=NULL;
		for(start=param_lable_pos->lable_start.keyword_end+1;start<=param_lable_pos->lable_end.keyword_start-1;start++)
		{
			if(myxml_is_split_flag(*start)==myxml_split_flag_false)
			{
				break;
			}
		}
		for(end=param_lable_pos->lable_end.keyword_start-1;end>=param_lable_pos->lable_start.keyword_end+1;end--)
		{
			if(myxml_is_split_flag(*end)==myxml_split_flag_false)
			{
				break;
			}
		}
		if (start&&end&&end>=start)
		{
			int len=end-start+1;
			char *note=(char*)malloc(len+1);
			if (note)
			{
				memset(note, 0, len+1);
				myxml_copy(start, end, note, len+1);
				if (param_node->content)
				{
					free(param_node->content);
					param_node->content=NULL;
				}
				param_node->content=note;
			}
		}
	}
	return result;
}

static int myxml_add_node(myxml_node_struct*param_father,myxml_node_struct*param_child)
{
	int result=-1;
	if(param_father&&param_child)
	{
		myxml_node_struct*child_node=param_father->child_node;
		result=0;
		if(child_node)
		{
			while(child_node->next_node)
			{
				child_node=child_node->next_node;
			}
			child_node->next_node=param_child;
			param_child->pre_node=child_node;
			param_child->father_node=param_father;
		}
		else
		{
			param_father->child_node=param_child;
			param_child->father_node=param_father;
		}
	}
	return result;
}

typedef enum _myxml_parser_type
{
	myxml_parser_all,
	myxml_parser_only_node,
}myxml_parser_type;

static myxml_node_struct* myxml_parser_lable(myxml_node_struct *param_father,const char *param_start,const char*param_end,myxml_parser_type param_parser_type)
{
	myxml_node_struct*result=NULL;
	if(param_start&&param_end&&param_end>=param_start)
	{
		myxml_node_struct*current_node=NULL;
		myxml_node_struct*new_node=NULL;
		const char *tmp_start=param_start;
		while(1)
		{
			myxml_lable_pos_struct lable_pos=myxml_lable_parser(tmp_start,param_end);
			/*mmyxml_lable_type_error,
	myxml_lable_type_start,//<table>
	myxml_lable_type_end,//</table>
	myxml_lable_type_middle,//<table/>
	myxml_lable_type_head,//<?xml  ?>
	myxml_lable_type_note,//<!--  -->
	myxml_lable_type_text,//table*/
			if (lable_pos.lable_type==myxml_lable_type_start)
			{
				new_node=myxml_malloc_node();
				new_node->type=myxml_node_node;
				myxml_parser_lable_name_attribute(new_node,&lable_pos);
				if(!current_node)
				{
					current_node=new_node;
				}
				else
				{
					myxml_add_node(current_node,new_node);
					current_node=new_node;
				}
			}
			else if (lable_pos.lable_type==myxml_lable_type_end)
			{
				if (current_node&&current_node->father_node)
				{
					current_node=current_node->father_node;
					if (!current_node)
					{
						break;
					}
				}
				else
				{
					break;//error
				}
			}
			else if (lable_pos.lable_type==myxml_lable_type_middle)
			{
				new_node=myxml_malloc_node();
				new_node->type=myxml_node_node;
				myxml_parser_lable_name_attribute(new_node,&lable_pos);
				if(!current_node)
				{
					current_node=new_node;
				}
				else
				{
					myxml_add_node(current_node,new_node);
				}
			}
			else if (lable_pos.lable_type==myxml_lable_type_head)
			{
				if(param_parser_type==myxml_parser_all&&!current_node)
				{
					new_node=myxml_malloc_node();
					new_node->type=myxml_node_null;
					current_node=new_node;
					new_node=myxml_malloc_node();
					new_node->type=myxml_node_head;
					myxml_parser_lable_head(new_node,&lable_pos);
					myxml_add_node(current_node,new_node);
				}
			}
			else if (lable_pos.lable_type==myxml_lable_type_note)
			{
				if(param_parser_type==myxml_parser_all&&current_node)
				{
					new_node=myxml_malloc_node();
					new_node->type=myxml_node_note;
					myxml_parser_lable_note(new_node,&lable_pos);
					myxml_add_node(current_node,new_node);
				}
			}
			else if (lable_pos.lable_type==myxml_lable_type_text)
			{
				if (current_node)
				{
					int content_len=lable_pos.lable_end.keyword_end-lable_pos.lable_start.keyword_start+1;
					char *content=(char*)malloc(content_len+1);
					memset(content, 0, content_len+1);
					myxml_copy(lable_pos.lable_start.keyword_start, lable_pos.lable_end.keyword_end, content, content_len+1);
					if (current_node->content)
					{
						free(current_node->content);
					}
					current_node->content=content;
				}
				else
				{
					break;//error
				}
			}
			else
			{
				break;
			}
			if(!result)
			{
				result=current_node;
			}
			tmp_start=lable_pos.lable_end.keyword_end+1;
		}
	}
	return result;
}

static int myxml_set_depth2(myxml_node_struct*param_node,int depth)
{
	int result=0;
	if (param_node)
	{
		param_node->depth=depth;
		if(param_node->next_node)
		{
			myxml_set_depth2(param_node->next_node, depth);
		}
		if (param_node->child_node)
		{
			myxml_set_depth2(param_node->child_node, depth+1);
		}
	}
	return result;
}
static int myxml_set_depth(myxml_node_struct*param_node)
{
	int result=0;
	if(param_node)
	{
		myxml_node_struct*root=param_node;
		while(root->father_node)
		{
			root=root->father_node;
		}
		myxml_set_depth2(root,0);
	}
	return result;
}
myxml_node_struct* myxml_parser_char(const char *param_char)
{
	myxml_node_struct*result=NULL;
	result=myxml_parser_lable(NULL,param_char,param_char+strlen(param_char)-1,myxml_parser_only_node);
	if(result)
	{
		myxml_set_depth(result);
	}
	return result;
}
myxml_node_struct* myxml_parser_char2(const char *param_char)
{
	myxml_node_struct*result=NULL;
	result=myxml_parser_lable(NULL,param_char,param_char+strlen(param_char)-1,myxml_parser_all);
	if(result)
	{
		if(result->type==myxml_node_null)
		{
			myxml_node_struct*tmp=result;
			result=result->child_node;
			free(tmp);
			tmp=result;
			while(tmp)
			{
				tmp->father_node=NULL;
				tmp=tmp->next_node;
			}
		}
		myxml_set_depth(result);
	}
	return result;
}










#else

#include "myxml.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "../common.h"

#define print_enter_fun 5
#define enter_fun(level) if(level>=print_enter_fun){printf("enter: %s %s %d\n",__FUNCTION__,__FILE__,__LINE__);}
#define exit_fun(level) if(level>=print_enter_fun){printf("exit: %s %s %d\n",__FUNCTION__,__FILE__,__LINE__);}










////////////////////////define inter funxtions   start///////////////////////////////////////
static myxml_node_struct* myxml_parser_node(myxml_node_struct*param_father_node,myxml_node_struct*param_pre_node,const char *param_start,const char *param_end);
static int myxml_count_child_node(const char *param_start,const char *param_end);
static int myxml_split_child(const char *param_start,const char *param_end,int **param_start_result,int **param_end_result);
static int myxml_add_node(myxml_node_struct* param_new_node,myxml_node_struct*param_father_node,myxml_node_struct*param_pre_node);

static int myxml_child_node_pos(const char *param_start,const char *param_end,const char** param_child_start,const char** param_child_end);
static int myxml_next_node_pos(const char *param_start,const char *param_end,const char** param_next_start,const char** param_next_end);

static int myxml_split_attribute(const char *param_start,const char *param_end,int **param_start_result,int **param_end_result);
static int myxml_parser_name_attribute(myxml_node_struct*param_node,const char *param_start,const char *param_end);
static int myxml_parser_content(myxml_node_struct* param_node,const char*param_start,const char *param_end);
static myxml_attribute_struct* myxml_parser_attribute(const char *param_start,const char *param_end);

//match string,return the position
static const char* myxml_get_xml_start(const char *param_char);
static const char* myxml_get_xml_end(const char *param_char);
static const char* myxml_keyword_pos(const char *param_start,const char* param_end,int * param_result_type);
static const char* myxml_keyword_pos_cmp(const char *param_pos,const char *param_posn);
static const char* myxml_lable_type(const char *param_start,const char *param_end,int *param_result_type);

//malloc free copy memory
static char* myxml_copy(const char*param_start,const char*param_end);
static char* myxml_copy_visible(const char*param_start,const char*param_end);
static myxml_attribute_struct* myxml_malloc_attribute(void);
static void myxml_free_attribute(myxml_attribute_struct*param_attribute);
static myxml_node_struct *myxml_malloc_node(void);
static void myxml_free_node(myxml_node_struct*param_node);
static void myxml_free_int(int *param);
static void myxml_free_char(char *param_char);
////////////////////////define inter funxtions   end///////////////////////////////////////










myxml_node_struct* myxml_parser_char(const char *param_char)
{
	myxml_node_struct*result=NULL;
	enter_fun(3);
	if(param_char)
	{
		const char *start=myxml_get_xml_start(param_char);
		const char *end=myxml_get_xml_end(param_char);
		result=myxml_parser_node(NULL,NULL,start,end);
	}
	else
	{
		result=NULL;
	}
	exit_fun(3);
	return result;
}



static myxml_node_struct* myxml_parser_node(myxml_node_struct*param_father_node,myxml_node_struct*param_pre_node,const char *param_start,const char *param_end)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start)
	{
		int type=-1;
		param_start=myxml_keyword_pos(param_start,param_end,&type);
		if(param_start&&type==4)
		{
			myxml_node_struct*node=myxml_malloc_node();
			if (node)
			{
				int *divide_start=NULL;
				int *divide_end=NULL;
				int count=0;
				myxml_add_node(node,param_father_node,param_pre_node);
				myxml_parser_name_attribute(node,param_start,param_end);
				
				count=myxml_split_child(param_start,param_end,&divide_start,&divide_end);
				if (count>0)//have child node
				{
					int i=0;
					myxml_node_struct*child_node=NULL;
					for (i=0;i<count;i++)
					{
						child_node=myxml_parser_node(node,child_node,param_start+divide_start[i],param_start+divide_end[i]);
					}
				}
				else if(count==0)//have not child node
				{
					myxml_parser_content(node,param_start,param_end);
				}
				else//错误
				{			
				}
				myxml_free_int(divide_start);
				myxml_free_int(divide_end);
			}	
			return node;
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


static int myxml_split_child(const char *param_start,const char *param_end,int **param_start_result,int **param_end_result)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start&&param_start_result&&param_end_result)
	{
		const char *pos=NULL;
		int type;
		pos=myxml_keyword_pos(param_start+1,param_end,&type);
		if (type<0||type==1)
		{
			return 0;
		}
		else
		{
			int count_child_node=myxml_count_child_node(param_start,param_end);
			if (count_child_node>0)
			{
				int i=0;
				int *start=NULL;
				int *end=NULL;
				const char *start_char=NULL;
				const char *end_char=NULL;
				
				start=(int*)malloc(sizeof(int)*count_child_node);
				end=(int*)malloc(sizeof(int)*count_child_node);

				memset(start,0,sizeof(int)*count_child_node);
				memset(end,0,sizeof(int)*count_child_node);
				*param_start_result=start;
				*param_end_result=end;

				myxml_child_node_pos(param_start,param_end,&start_char,&end_char);
				start[0]=start_char-param_start;
				end[0]=end_char-param_start;
				for (i=1;i<count_child_node;i++)
				{
					const char *temp_start=NULL;
					const char *temp_end=NULL;
					myxml_next_node_pos(end_char+1,param_end,&temp_start,&temp_end);
					start_char=temp_start;
					end_char=temp_end;
					start[i]=start_char-param_start;
					end[i]=end_char-param_start;
				}
				return count_child_node;
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

static int myxml_parser_name_attribute(myxml_node_struct*param_node,const char *param_start,const char *param_end)
{
	int result=0;
	enter_fun(2);	
	if(param_node&&param_start&&param_end)
	{
		const char *name_start=NULL;
		const char *name_end=NULL;
		const char *attribute_start=NULL;
		const char *attribute_end=NULL;
		int *one_attribute_start=NULL;
		int *one_attribute_end=NULL;
		int attribute_count=0;
		int i=0;
		myxml_attribute_struct* first_attribute=NULL;
		myxml_attribute_struct* last_attribute=NULL;
		name_start=param_start+1;
		while(1)
		{
			if(*name_start!=' '&&*name_start!='	'&&*name_start!='\n')
			{
				break;
			}
			name_start++;
		}
		name_end=name_start;
		while(name_end)
		{
			if(*name_end==' '||*name_end=='	'||*name_end=='\n'||*name_end=='/'||*name_end=='>')
			{
				break;
			}
			name_end++;
		}
		if(name_end&&name_end>name_start)
		{
			name_end--;
			if (name_end&&name_end>=param_start)
			{
				param_node->name=myxml_copy_visible(name_start,name_end);
				attribute_start=name_end+1;
				while (*attribute_start==' '||*attribute_start=='	'||*attribute_start=='\n')
				{
					attribute_start++;
				}
				attribute_end=strstr(attribute_start,">");
				if(attribute_end&&attribute_end>attribute_start)
				{
					attribute_end--;
					if (*attribute_end=='/')
					{
						attribute_end--;
					}
					attribute_count=myxml_split_attribute(attribute_start,attribute_end,&one_attribute_start,&one_attribute_end);
					for (i=0;i<attribute_count;i++)
					{
						myxml_attribute_struct* attribute=myxml_parser_attribute(attribute_start+one_attribute_start[i],attribute_start+one_attribute_end[i]);
						if(attribute)
						{
							if(first_attribute==NULL)
							{
								first_attribute=attribute;
								last_attribute=attribute;
							}
							else
							{
								last_attribute->next=attribute;
								attribute->pre=last_attribute;
								last_attribute=attribute;
							}
						}
						
					}
					param_node->attribute=first_attribute;
					myxml_free_int(one_attribute_start);
					myxml_free_int(one_attribute_end);
					result=0;
				}
				else
				{
					result=-1;
				}
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
	return result;
}

static int myxml_parser_content(myxml_node_struct* param_node,const char*param_start,const char *param_end)
{
	enter_fun(2);
	if(param_node&&param_start&&param_end)
	{
		char *node=myxml_copy_visible(param_start,param_end);
		char *content_end=NULL;
		char *content_start=NULL;
		content_start=strstr(param_start,">");
		if (content_start)
		{
			content_end=strstr(param_start,"</");
			if (content_end)
			{
				if (content_end-content_start>=2)
				{
					content_start++;
					content_end--;
					param_node->content=myxml_copy_visible(content_start,content_end);
				}
			}
		}
		myxml_free_char(node);
		return 0;
	}
	else
	{
		return -1;
	}
}

static char* myxml_copy(const char*param_start,const char*param_end)
{
	enter_fun(2);
	if (param_start&&param_end&&param_end>=param_start)
	{
		int len=param_end-param_start+2;
		int i=0;
		char *content=(char*)malloc(len);
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


static void myxml_free_char(char *param_char)
{
	enter_fun(2);
	if (param_char)
	{
		free(param_char);
	}
}

static myxml_node_struct *myxml_malloc_node(void)
{
	myxml_node_struct *node=NULL;
	enter_fun(2);
	node=(myxml_node_struct *)malloc(sizeof(myxml_node_struct));
	if (node)
	{
		memset(node,0,sizeof(myxml_node_struct));
	}
	return node;
}

static void myxml_free_node(myxml_node_struct*param_node)
{
	enter_fun(2);
	if(param_node)
	{
		if(param_node->child_node)
		{
			myxml_free_node(param_node->child_node);
		}
		if(param_node->next_node)
		{
			myxml_free_node(param_node->next_node);
		}
		if(param_node->name)
		{
			free(param_node->name);
		}
		if(param_node->content)
		{
			free(param_node->content);
		}
		if(param_node->attribute)
		{
			myxml_free_attribute(param_node->attribute);
		}
		free(param_node);
	}	
}


static int myxml_add_node(myxml_node_struct* param_new_node,myxml_node_struct*param_father_node,myxml_node_struct*param_pre_node)
{
	enter_fun(2);
	if(param_new_node)
	{
		if (param_father_node)
		{
			param_new_node->child_node=NULL;
			param_new_node->father_node=param_father_node;
			if (!param_father_node->child_node)
			{
				param_father_node->child_node=param_new_node;
			}
			param_new_node->depth=param_father_node->depth+1;
		}
		else
		{
			param_new_node->father_node=NULL;
			param_new_node->child_node=NULL;
			param_new_node->depth=0;
		}
		if (param_pre_node)
		{
			param_pre_node->next_node=param_new_node;
			param_new_node->pre_node=param_pre_node;
			param_new_node->next_node=NULL;
		}
		else
		{
			param_new_node->pre_node=NULL;
			param_new_node->next_node=NULL;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

static myxml_attribute_struct* myxml_parser_attribute(const char *param_start,const char *param_end)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start)
	{
		const char *name_start=NULL;
		const char *name_end=NULL;
		const char *value_start=NULL;
		const char *value_end=NULL;
		char *name=NULL;
		char *value=NULL;
		myxml_attribute_struct*attribute=NULL;
		name_start=param_start;
		name_end=strstr(name_start,"=");
		if (name_end)
		{	
			name_end--;
			value_start=name_end+3;
			value_end=strstr(value_start,"\"");
			value_end--;
		}
		name=myxml_copy_visible(name_start,name_end);
		value=myxml_copy_visible(value_start,value_end);
		if(name)
		{
			attribute=myxml_malloc_attribute();
			attribute->name=name;
			attribute->value=value;
		}
		return attribute;
	}
	else
	{
		return NULL;
	}
}

static int myxml_split_attribute(const char *param_start,const char *param_end,int **param_start_result,int **param_end_result)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start&&param_start_result&&param_end_result)
	{
		int result=0;
		if (param_start&&param_end&&param_end>param_start)
		{
			int black_count=1;
			const char *pos=NULL;
			char *attribute=myxml_copy_visible(param_start,param_end);
			int *start=NULL;
			int *end=NULL;
			int start_flag=1;
			int i=0;
			for (pos=param_start;pos<param_end;pos++)
			{
				if (*pos==' '||*pos=='	'||*pos=='\n')
				{
					black_count++;
				}
			}
			start=(int*)malloc(sizeof(int)*black_count);
			end=(int*)malloc(sizeof(int)*black_count);
			memset(start,0,sizeof(int)*black_count);
			memset(end,0,sizeof(int)*black_count);
			start_flag=1;
			pos=attribute;
			while (pos<attribute+strlen(attribute))
			{
				if (start_flag==1)
				{
					if (*pos!=' '&&*pos!='	'&&*pos!='\n')
					{
						start[i]=pos-attribute;
						start_flag=0;
					}
				}
				else
				{
					if (*pos==' '||*pos=='	'||*pos=='\n')
					{
						end[i++]=pos-attribute-1;
						start_flag=1;
						result++;
					}
				}
				pos++;
			}
			if (start_flag!=1)
			{
				end[i]=pos-attribute-1;
				result++;
			}
			*param_start_result=start;
			*param_end_result=end;
			myxml_free_char(attribute);
		}
		return result;
	}
	else
	{
		return -1;
	}
}

static void myxml_free_int(int *param)
{
	enter_fun(2);
	if (param)
	{
		free(param);
	}
}

static myxml_attribute_struct* myxml_malloc_attribute(void)
{
	myxml_attribute_struct*attribute=NULL;
	enter_fun(2);
	attribute=(myxml_attribute_struct*)malloc(sizeof(myxml_attribute_struct));
	if (attribute)
	{
		memset(attribute,0,sizeof(myxml_attribute_struct));
		return attribute;
	}
	return NULL;
}

static const char* myxml_keyword_pos(const char *param_start,const char* param_end,int * param_result_type)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start&&param_result_type)
	{
		if (param_start&&param_end&&param_result_type)
		{
			const char *pos1=NULL;// />
			const char *pos2=NULL;// </
			const char *pos3=NULL;// >
			const char *pos4=NULL;// <	
			const char *pos5=NULL;// <!
			const char *pos=NULL;
			pos1=strstr(param_start,"/>");
			pos2=strstr(param_start,"</");
			pos3=strstr(param_start,">");
			pos4=strstr(param_start,"<");
			pos5=strstr(param_start,"<!");
			
			if (pos1&&(pos1>param_end||pos1<param_start))
			{
				pos1=NULL;
			}
			if (pos2&&(pos2>param_end||pos2<param_start))
			{
				pos2=NULL;
			}
			if (pos3&&(pos3>param_end||pos3<param_start))
			{
				pos3=NULL;
			}
			if (pos4&&(pos4>param_end||pos4<param_start))
			{
				pos4=NULL;
			}
			if (pos5&&(pos5>param_end||pos5<param_start))
			{
				pos5=NULL;
			}
			pos=myxml_keyword_pos_cmp(pos,pos1);
			pos=myxml_keyword_pos_cmp(pos,pos2);
			pos=myxml_keyword_pos_cmp(pos,pos3);
			pos=myxml_keyword_pos_cmp(pos,pos4);
			pos=myxml_keyword_pos_cmp(pos,pos5);
			if (pos==NULL)
			{
				*param_result_type=-1;
			}
			else if (pos==pos1)
			{
				*param_result_type=1;
			}
			else if (pos==pos2)
			{
				*param_result_type=2;
			}
			else if (pos==pos5)
			{
				*param_result_type=5;
			}
			else if (pos==pos3)
			{
				*param_result_type=3;
			}
			else if (pos==pos4)
			{
				*param_result_type=4;
			}
			else
			{
				*param_result_type=-1;
			}
			return pos;
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

static const char* myxml_keyword_pos_cmp(const char *param_pos,const char *param_posn)
{
	enter_fun(2);
	if(param_pos&&param_posn)
	{
		if(param_pos<param_posn)
		{
			return param_pos;
		}
		else
		{
			return param_posn;
		}
	}
	else if(!param_pos&&param_posn)
	{
		return param_posn;
	}
	else if(param_pos&&!param_posn)
	{
		return param_pos;
	}
	else
	{
		return NULL;
	}
}

static int myxml_child_node_pos(const char *param_start,const char *param_end,const char** param_child_start,const char** param_child_end)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start&&param_child_start&&param_child_end)
	{
		while (1)
		{
			if(*param_start=='>')
			{
				break;
			}
			param_start++;
		}
		return myxml_next_node_pos(param_start+1,param_end,param_child_start,param_child_end);
	}
	else
	{
		return -1;
	}
}

static int myxml_next_node_pos(const char *param_start,const char *param_end,const char** param_next_start,const char** param_next_end)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start&&param_next_start&&param_next_end)
	{
		int depth=0;
		int type;	
		const char *pos=myxml_keyword_pos(param_start,param_end,&type);
		*param_next_start=pos;
		while (1)
		{
			pos=myxml_lable_type(pos,param_end,&type);
			switch(type)
			{
			case 1://</ >
				depth--;
				break;
			case 2://< >
				depth++;
				break;
			case 3://< />
				break;
			case 4://<! >
				break;
			default:
				return -2;
			}
			if (depth==0)
			{
				break;
			}
			if (depth<0)
			{
				return -1;
			}
			pos++;
			//if (*pos=='>')
			//{
			//	pos++;
			//}
		}
		if (*pos=='/')
		{
			pos++;
		}
		*param_next_end=pos;
		return 0;
	}
	else
	{
		return -1;
	}
}

static int myxml_count_child_node(const char *param_start,const char *param_end)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start)
	{
		int depth=0;
		int type;
		int count=0;
		const char *pos=myxml_keyword_pos(param_start,param_end,&type);
		if(pos)
		{
			pos=myxml_keyword_pos(pos+1,param_end,&type);
		}
		if(pos)
		{
			pos=myxml_keyword_pos(pos+1,param_end,&type);
		}
		if (pos==NULL)
		{
			return 0;
		}
		while (pos)
		{
			pos=myxml_lable_type(pos,param_end,&type);
			switch(type)
			{
			case 1://</ >
				depth--;
				break;
			case 2://< >
				depth++;
				break;
			case 3://< />
				break;
			case 4://<!   >
				break;
			default:
				break;
			}
			if (depth==0)
			{
				count++;
			}
			if (depth<0)
			{
				return count;
			}
			if(pos==NULL)
			{
				break;
			}
			pos++;
			//if (*pos=='>')
			//{
			//	pos++;
			//}
		}
		return 1;
	}
	else
	{
		return -1;
	}
}

static const char *myxml_lable_type(const char *param_start,const char *param_end,int *param_result_type)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start&&param_result_type)
	{
		int start_type=-1;
		int end_type=-1;
		const char *start_pos=myxml_keyword_pos(param_start,param_end,&start_type);
		const char *end_pos=myxml_keyword_pos(start_pos+1,param_end,&end_type);
		if (start_type==2&&end_type==3)//</ >
		{
			*param_result_type=1;
		}
		else if (start_type==4&&end_type==3)//< >
		{
			*param_result_type=2;
		}
		else if (start_type==4&&end_type==1)//< />
		{
			*param_result_type=3;
			end_pos++;
		}
		else if(start_type==5&&end_type==3)//<!  >
		{
			*param_result_type=4;
		}
		else
		{
			*param_result_type=-1;
		}
		return end_pos;
	}
	else
	{
		return NULL;
	}
}

void myxml_free(myxml_node_struct*param_node)
{
	//enter_fun(3);
	if(param_node)
	{
		myxml_node_struct*root=param_node;
		while(root->father_node)
		{
			root=root->father_node;
		}
		myxml_free_node(root);
	}
	//exit_fun(3);
}

static void myxml_free_attribute(myxml_attribute_struct*param_attribute)
{
	enter_fun(2);
	if(param_attribute)
	{
		if(param_attribute->next)
		{
			myxml_free_attribute(param_attribute->next);
		}
		if(param_attribute->name)
		{
			free(param_attribute->name);
		}
		if(param_attribute->value)
		{
			free(param_attribute->value);
		}
		free(param_attribute);
	}
}

static const char* myxml_get_xml_start(const char *param_char)
{
	if(param_char)
	{
		const char *pos=param_char;
		const char *start=param_char;
		while(pos)
		{
			pos=strstr(pos,"?>");
			if(pos)
			{
				start=pos;
				pos++;
			}
			else
			{
				break;
			}
		}
		pos=start;
		while(pos)
		{
			if(*pos=='\0')
			{
				return NULL;
			}
			else if(*pos=='<')
			{
				return pos;
			}
			pos++;
		}
	}
	return NULL;
}

static const char* myxml_get_xml_end(const char *param_char)
{
	if(param_char)
	{
		const char *end=param_char+strlen(param_char)-1;
		while(end&&end>=param_char)
		{
			if(*end=='>')
			{
				return end;
			}
			end--;
		}
	}
	return NULL;
}

static char* myxml_copy_visible(const char*param_start,const char*param_end)
{
	enter_fun(2);
	if(param_start&&param_end&&param_end>=param_start)
	{
		while(param_start&&param_end&&param_end>=param_start)
		{
			if(*param_start==' '||*param_start=='	'||*param_start=='\n'||*param_start=='\r')
			{
				param_start++;
			}
			else
			{
				break;
			}
		}
		while(param_start&&param_end&&param_end>=param_start)
		{
			if(*param_end==' '||*param_end=='	'||*param_end=='\n'||*param_end=='\r')
			{
				param_end--;
			}
			else
			{
				break;
			}
		}
		if(param_start&&param_end&&param_end>=param_start)
		{
			return myxml_copy(param_start,param_end);
		}
	}
	return NULL;
}
#endif

#endif//MYSRC_WITHOUT_XML

