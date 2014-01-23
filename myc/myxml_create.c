/*        Filename: myxml.c
 **********************************************************
 * Description:
 *        this is myxml.c .
 * Version:
 *        V_0.1 2009.1.19
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2009.1.19 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */
#ifndef MYSRC_WITHOUT_XML

#include "myxml.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "mystring.h"


myxml_node_struct* myxml_create_node(const char*param_name,const char*param_content)
{
	myxml_node_struct*node=NULL;
	if(param_name)
	{
		node=(myxml_node_struct*)malloc(sizeof(myxml_node_struct));
		if(node)
		{
			char *name=NULL;
			memset(node,0,sizeof(myxml_node_struct));
			node->attribute=NULL;
			node->child_node=NULL;
			node->content=NULL;
			node->depth=0;
			node->father_node=NULL;
			node->name=NULL;
			node->next_node=NULL;
			node->pre_node=NULL;
			node->type=myxml_node_node;
			name=strdup(param_name);
			node->name=name;
			if(param_content)
			{
				char*content=strdup(param_content);
				node->content=content;
			}
			else
			{
				node->content=NULL;
			}
		}
	}
	return node;
}

myxml_node_struct* myxml_create_note(const char*param_note)
{
	myxml_node_struct*note=NULL;
	if(param_note)
	{
		note=(myxml_node_struct*)malloc(sizeof(myxml_node_struct));
		if(note)
		{
			memset(note,0,sizeof(myxml_node_struct));
			note->attribute=NULL;
			note->child_node=NULL;
			note->content=NULL;
			note->depth=0;
			note->father_node=NULL;
			note->name=NULL;
			note->next_node=NULL;
			note->pre_node=NULL;
			note->type=myxml_node_note;
			if(param_note&&strlen(param_note)>0)
			{
				note->content=strdup(param_note);
			}
			else
			{
				note->content=NULL;
			}
		}
	}
	return note;
}

myxml_node_struct* myxml_create_head(const char*param_version,const char*param_encoding)
{
	myxml_node_struct*head=NULL;
	head=(myxml_node_struct*)malloc(sizeof(myxml_node_struct));
	if (head)
	{
		memset(head, 0, sizeof(myxml_node_struct));
		head->attribute=NULL;
		head->child_node=NULL;
		head->content=NULL;
		head->depth=0;
		head->father_node=NULL;
		head->name=NULL;
		head->next_node=NULL;
		head->pre_node=NULL;
		head->type=myxml_node_head;
		if(param_version)
		{
			myxml_add_attribute(head,"version",param_version);
		}
		if(param_encoding)
		{
			myxml_add_attribute(head,"encoding",param_encoding);
		}
	}
	return head;
}




int myxml_set_content(myxml_node_struct*param_node,const char *param_content)
{
	int result=-1;
	if(param_node&&param_node->type==myxml_node_node)
	{
		if(param_node->content)
		{
			free(param_node->content);
			param_node->content=NULL;
		}
		if(param_content&&strlen(param_content)>0)
		{
			param_node->content=strdup(param_content);
		}
		result=0;
	}
	return result;
}

int myxml_set_note(myxml_node_struct*param_node,const char* param_note)
{
	int result=-1;
	if(param_node&&param_node->type==myxml_node_note)
	{
		if(param_node->content)
		{
			free(param_node->content);
			param_node->content=NULL;
		}
		if(param_note&&strlen(param_note)>0)
		{
			param_node->content=strdup(param_note);
		}
		result=0;
	}
	return result;
}

int myxml_add_attribute(myxml_node_struct*param_node,const char*param_name,const char*param_value)
{
	int result=0;
	if(param_node&&((param_name&&param_node->type==myxml_node_node)||param_node->type==myxml_node_head))
	{
		myxml_attribute_struct*attribute=NULL;
		char*name=NULL;
		char*value=NULL;
		name=strdup(param_name);
		if(param_value)
		{
			value=strdup(param_value);
		}
		attribute=(myxml_attribute_struct*)malloc(sizeof(myxml_attribute_struct));
		attribute->name=name;
		attribute->value=value;
		if(param_node->attribute)
		{
			myxml_attribute_struct*tmp=param_node->attribute;
			while(tmp->next)
			{
				tmp=tmp->next;
			}
			tmp->next=attribute;
			attribute->next=NULL;
			attribute->pre=tmp;
		}
		else
		{
			param_node->attribute=attribute;
			attribute->pre=NULL;
			attribute->next=NULL;
		}
	}
	else
	{
		result=-1;
	}
	return result;
}

static int myxml_set_depth_root(myxml_node_struct*param_root_node,const int param_depth)
{
	if(param_root_node)
	{
		myxml_node_struct*child=param_root_node->child_node;
		param_root_node->depth=param_depth;
		while(child)
		{
			myxml_set_depth_root(child,param_depth+1);
			child=child->next_node;
		}
	}
	return 0;
}

static int myxml_set_depth(myxml_node_struct*param_node)
{
	if(param_node)
	{
		myxml_node_struct*root_node=param_node;
		while(root_node->father_node)
		{
			root_node=root_node->father_node;
		}
		myxml_set_depth_root(root_node,0);
	}
	return 0;
}

int myxml_add_child_node(myxml_node_struct*param_father_node,myxml_node_struct*param_child_node)
{
	int result=0;
	if(param_father_node&&param_child_node&&param_father_node->type==myxml_node_node)
	{
		myxml_node_struct*child=param_father_node->child_node;
		myxml_node_struct*tmp=NULL;
		if(child)
		{
			while(child->next_node)
			{
				child=child->next_node;
			}
			child->next_node=param_child_node;
			param_child_node->pre_node=child;
		}
		else
		{
			param_father_node->child_node=param_child_node;
			param_child_node->pre_node=NULL;			
		}		
		//param_child_node->child_node=NULL;
		param_child_node->father_node=param_father_node;
		tmp=param_child_node->next_node;
		if (tmp)
		{
			while (tmp)
			{
				tmp->father_node=param_father_node;
				tmp=tmp->next_node;
			}
			myxml_set_depth(tmp);
		}
		//param_child_node->next_node=NULL;
		param_child_node->depth=param_father_node->depth+1;
		result=0;
	}
	else
	{
		result=-1;
	}
	return result;
}
int myxml_add_pre_node(myxml_node_struct*param_node,myxml_node_struct*param_new_node)
{
	int result=0;
	if(param_node&&param_node->father_node&&param_new_node)
	{
		if(param_node->father_node->child_node==param_node)
		{
			param_node->father_node->child_node=param_new_node;
			param_new_node->pre_node=NULL;
		}
		else
		{
			param_new_node->pre_node=param_node->pre_node;
			param_node->pre_node->next_node=param_new_node;
		}
		param_node->pre_node=param_new_node;
		//param_new_node->child_node=NULL;
		param_new_node->father_node=param_node->father_node;
		param_new_node->depth=param_node->depth;
		param_new_node->next_node=param_node;
		result=0;
	}
	else
	{
		result=-1;
	}
	return result;
}

int myxml_add_next_node(myxml_node_struct*param_node,myxml_node_struct*param_new_node)
{
	int result=0;
	if(param_node&&param_node&&param_new_node)
	{
		if(param_node->father_node)
		{
			param_new_node->father_node=param_node->father_node;
		}
		else
		{
			param_new_node->father_node=NULL;
		}
		param_new_node->pre_node=param_node;
		param_new_node->next_node=param_node->next_node;
		param_node->next_node=param_new_node;
		param_new_node->depth=param_node->depth;
		result=0;
	}
	else
	{
		result=-1;
	}
	return result;
}

static int myxml_lable_start_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=-1;
	if(param_node&&param_node->name)
	{
		myxml_attribute_struct*attribute=NULL;
		mystrncat(param_string,param_string_len,"<");
		mystrncat(param_string,param_string_len,param_node->name);
		attribute=param_node->attribute;
		while (attribute)
		{
			if (attribute->name)
			{
				mystrncat(param_string, param_string_len, " ");
				mystrncat(param_string, param_string_len, attribute->name);
				mystrncat(param_string, param_string_len, "=\"");
				if (attribute->value)
				{
					mystrncat(param_string, param_string_len, attribute->value);
				}
				mystrncat(param_string, param_string_len, "\"");
				attribute=attribute->next;
			}
		}
		mystrncat(param_string,param_string_len,">");
		result=0;
	}
	return result;
}

static int myxml_head_to_char2(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=-1;
	if(param_node)
	{
		myxml_attribute_struct*attribute=NULL;
		mystrncat(param_string,param_string_len,"<?xml");
		attribute=param_node->attribute;
		while (attribute)
		{
			if (attribute->name)
			{
				mystrncat(param_string, param_string_len, " ");
				mystrncat(param_string, param_string_len, attribute->name);
				mystrncat(param_string, param_string_len, "=\"");
				if (attribute->value)
				{
					mystrncat(param_string, param_string_len, attribute->value);
				}
				mystrncat(param_string, param_string_len, "\"");
				attribute=attribute->next;
			}
		}
		mystrncat(param_string,param_string_len," ?>");
		result=0;
	}
	return result;
}
static int myxml_lable_end_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=-1;
	if(param_node&&param_node->name)
	{
		mystrncat(param_string,param_string_len,"</");
		mystrncat(param_string,param_string_len,param_node->name);
		mystrncat(param_string,param_string_len,">");
		result=0;
	}
	return result;
}
static int myxml_content_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=-1;
	if(param_node&&param_node->content)
	{
		mystrncat(param_string,param_string_len,param_node->content);
		result=0;
	}
	return result;
}

static int myxml_note_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=-1;
	if(param_node&&param_node->content)
	{
		mystrncat(param_string,param_string_len,"<!-- ");
		mystrncat(param_string,param_string_len,param_node->content);
		mystrncat(param_string,param_string_len," -->");
		result=0;
	}
	return result;
}
static int myxml_root_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	if (param_node&&param_string&&param_string_len>0)
	{
		if (param_node->type==myxml_node_node)
		{
			int flag=0;
			myxml_node_struct*child=param_node->child_node;
			int enter_flag=0;
			if (child)
			{
				enter_flag=1;
			}
			myxml_lable_start_to_char(param_node, param_string, param_string_len);
			if (enter_flag==1)
			{
				mystrncat(param_string, param_string_len, "\n");
			}
			flag=myxml_content_to_char(param_node, param_string, param_string_len);
			while (child)
			{
				if (flag==0||child!=param_node->child_node)
				{
					mystrncat(param_string, param_string_len, "\n");
				}
				myxml_root_to_char(child, param_string, param_string_len);
				child=child->next_node;
			}
			if (enter_flag==1)
			{
				mystrncat(param_string, param_string_len, "\n");
			}
			myxml_lable_end_to_char(param_node, param_string, param_string_len);
		}
		else if (param_node->type==myxml_node_head)
		{
			myxml_head_to_char2(param_node, param_string, param_string_len);
		}
		else if (param_node->type==myxml_node_note)
		{
			myxml_note_to_char(param_node, param_string, param_string_len);
		}
		else
		{
		}
	}
	return 0;
}
int myxml_to_char(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=0;
	if(param_node&&param_string&&param_string_len>0)
	{
		myxml_node_struct*root=NULL;
		memset(param_string,0,param_string_len);
		root=param_node;
		while(root->father_node)
		{
			root=root->father_node;
		}
		while(root->pre_node)
		{
			root=root->pre_node;
		}
		while(root)
		{
			result=myxml_root_to_char(root,param_string,param_string_len);
			root=root->next_node;
			if(root)
			{
				mystrncat(param_string,param_string_len,"\n");
			}
		}		
		if(result==0)
		{
			result=strlen(param_string);
		}
	}
	else
	{
		result=-1;
	}	
	return result;
}

static int myxml_root_to_char2(myxml_node_struct *param_node, char *param_string, const int param_string_len)
{
	if (param_node&&param_string&&param_string_len>0)
	{
		int i=0;
		for (i=0; i<param_node->depth; i++)
		{
			mystrncat(param_string, param_string_len, "	");
		}
		if (param_node->type==myxml_node_node)
		{
			int flag=0;
			myxml_node_struct*child=param_node->child_node;
			int enter_flag=0;
			if (child)
			{
				enter_flag=1;
			}
			myxml_lable_start_to_char(param_node, param_string, param_string_len);
			if (enter_flag==1)
			{
				mystrncat(param_string, param_string_len, "\n");
			}
			flag=myxml_content_to_char(param_node, param_string, param_string_len);
			while (child)
			{
				if (flag==0||child!=param_node->child_node)
				{
					mystrncat(param_string, param_string_len, "\n");
				}
				myxml_root_to_char2(child, param_string, param_string_len);
				child=child->next_node;
			}
			if (enter_flag==1)
			{
				mystrncat(param_string, param_string_len, "\n");
				for (i=0; i<param_node->depth; i++)
				{
					mystrncat(param_string, param_string_len, "	");
				}
			}
			myxml_lable_end_to_char(param_node, param_string, param_string_len);
		}
		else if (param_node->type==myxml_node_head)
		{
			myxml_head_to_char2(param_node, param_string, param_string_len);
		}
		else if (param_node->type==myxml_node_note)
		{
			myxml_note_to_char(param_node, param_string, param_string_len);
		}
		else
		{
		}
	}
	return 0;
}
int myxml_to_char2(myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=0;
	if(param_node&&param_string&&param_string_len>0)
	{
		myxml_node_struct*root=NULL;
		memset(param_string,0,param_string_len);
		root=param_node;
		while(root->father_node)
		{
			root=root->father_node;
		}
		while(root->pre_node)
		{
			root=root->pre_node;
		}
		while(root)
		{
			result=myxml_root_to_char2(root,param_string,param_string_len);
			root=root->next_node;
			if(root)
			{
				mystrncat(param_string,param_string_len,"\n");
			}
		}		
		if(result==0)
		{
			result=strlen(param_string);
		}
	}
	else
	{
		result=-1;
	}	
	return result;
}

myxml_node_struct *myxml_unlink_node(myxml_node_struct*param_unlink_node)
{
	myxml_node_struct*root_node=param_unlink_node;
	if(param_unlink_node)
	{
		while(root_node->father_node)
		{
			root_node=root_node->father_node;
		}
		if(root_node==param_unlink_node)
		{
			root_node=NULL;
		}
		else
		{
			myxml_node_struct*father_node=param_unlink_node->father_node;
			myxml_node_struct*pre_node=param_unlink_node->pre_node;
			myxml_node_struct*next_node=param_unlink_node->next_node;
			if(father_node->child_node==param_unlink_node)
			{
				father_node->child_node=next_node;
			}
			if(pre_node)
			{
				pre_node->next_node=next_node;
			}
			if(next_node)
			{
				next_node->pre_node=pre_node;
			}
			param_unlink_node->father_node=NULL;
			myxml_set_depth(param_unlink_node);
		}
	}
	return root_node;
}

#endif//MYSRC_WITHOUT_XML
