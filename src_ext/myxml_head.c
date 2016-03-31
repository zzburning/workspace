#ifndef MYSRC_WITHOUT_XML
#include "myxml.h"
#include <malloc.h>
#include <string.h>
#include "mystring.h"
#include <stdio.h>

myxml_head_struct* myxml_parser_head_char(const char *param_char)
{
	myxml_head_struct*result=NULL;
	if(param_char)
	{
		char *start_pos=NULL;
		char *end_pos=NULL;
		start_pos=strstr(param_char,"<?");
		if(start_pos&&start_pos+1)
		{
			end_pos=strstr(start_pos+1,"?>");
		}
		if(start_pos&&end_pos&&end_pos>start_pos+2)
		{
			char *s=(char*)malloc(end_pos-start_pos+1);
			char *tmp;
			int i=0;
			char version[32];
			char encoding[32];
			memset(s,0,end_pos-start_pos+1);
			result=(myxml_head_struct*)malloc(sizeof(myxml_head_struct));
			memset(result,0,sizeof(myxml_head_struct));
			result->encoding=myxml_encode_unknow;
			memset(version,0,sizeof(version));
			memset(encoding,0,sizeof(encoding));
			memset(s,0,end_pos-start_pos+1);
			for(tmp=start_pos+2;tmp<end_pos;tmp++)
			{
				s[i++]=tmp[0];
			}
			mystring_to_lower(s,strlen(s),s);
			
			if(mystring_get_value(s,"version",version,sizeof(version))==0)
			{
				result->version=strdup(version);
			}
			if(mystring_get_value(s,"encoding",encoding,sizeof(encoding))==0)
			{
				mystring_to_lower(encoding,strlen(encoding),encoding);
				if(strcmp(encoding,"utf-8")==0)
				{
					result->encoding=myxml_encode_utf8;
				}
				else if(strcmp(encoding,"gb2312")==0)
				{
					result->encoding=myxml_encode_gb2312;
				}
				else
				{
					result->encoding=myxml_encode_unknow;
				}
			}
			free(s);
		}
	}
	return result;
}
void myxml_head_free(myxml_head_struct*param)
{
	if(param)
	{
		if(param->version)
		{
			free(param->version);
		}
		free(param);
	}
}



myxml_head_struct* myxml_head_create(const char *param_version,const myxml_encoding_enum param_encoding)
{
	myxml_head_struct*result=(myxml_head_struct*)malloc(sizeof(myxml_head_struct));
	if(result)
	{
		memset(result,0,sizeof(myxml_head_struct));
		if(param_version)
		{
			result->version=strdup(param_version);
		}
		result->encoding=param_encoding;
	}
	return result;
}
int myxml_head_set_version(myxml_head_struct*param_head,const char*param_version)
{
	if(param_head)
	{
		if(param_head->version)
		{
			free(param_head->version);
			param_head->version=NULL;
		}
		if(param_version)
		{
			param_head->version=strdup(param_version);
		}
	}
	return 0;
}
int myxml_head_set_encoding(myxml_head_struct*param_head,const myxml_encoding_enum param_encoding)
{
	if(param_head)
	{
		param_head->encoding=param_encoding;
	}
	return 0;
}

int myxml_head_to_char(myxml_head_struct*param_head,char *param_string,const int param_string_len)
{
	int result=0;
	if(param_head)
	{
		char version[128];
		char encoding[128];
		memset(version,0,sizeof(version));
		memset(encoding,0,sizeof(encoding));
		if(param_head->version)
		{
#ifdef WIN32
			_snprintf(version,sizeof(version),"version=\"%s\"",param_head->version);
#else//WIN32
			snprintf(version,sizeof(version),"version=\"%s\"",param_head->version);
#endif//WIN32
		}
		switch(param_head->encoding)
		{
		case myxml_encode_gb2312:
#ifdef WIN32
			_snprintf(encoding,sizeof(encoding),"encoding=\"%s\"","GB2312");
#else//WIN32
			snprintf(encoding,sizeof(encoding),"encoding=\"%s\"","GB2312");
#endif//WIN32
			break;
		case myxml_encode_utf8:
#ifdef WIN32
			_snprintf(encoding,sizeof(encoding),"encoding=\"%s\"","UTF-8");
#else//WIN32
			snprintf(encoding,sizeof(encoding),"encoding=\"%s\"","UTF-8");
#endif//WIN32
			break;
		default:
			break;
		}
#ifdef WIN32
		_snprintf(param_string,param_string_len,"<?xml %s %s ?>",version,encoding);
#else//WIN32
		snprintf(param_string,param_string_len,"<?xml %s %s ?>",version,encoding);
#endif//WIN32
		result=strlen(param_string);
	}
	return result;
}


int myxml_all_to_char(myxml_head_struct*param_head,myxml_node_struct *param_node,char *param_string,const int param_string_len)
{
	int result=0;
	int len=0;
	if(param_head)
	{
		len=myxml_head_to_char(param_head,param_string,param_string_len);
	}
	if(len>0&&param_node)
	{
		strcat(param_string,"\n");
	}
	if(param_node)
	{
		if(len<0)
		{
			len=0;
		}
		myxml_to_char(param_node,param_string+strlen(param_string),param_string_len-strlen(param_string));
	}
	result=strlen(param_string);
	return result;
}

#endif//MYSRC_WITHOUT_XML

