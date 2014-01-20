/*        Filename: mystring.c
 **********************************************************
 * Description:
 *        this is mystring.c .
 * Version:
 *        V_0.1 2008.4.11
 * Copyright:
 *        HISOME <http://www.hisome.com.>
 * Author:
 *        panhaijiang <panhj@hisome.com.>
 * History:
 *        2008.4.11 panhaijiang<panhj@hisome.com>
 *                V_0.1 initial version of this code.
 */
#ifndef MYSRC_WITHOUT_STRING
#include <string.h>
#include "mystring.h"
#include <ctype.h>
#include <stdlib.h>
#include "stdio.h"
#include "../common.h"
#include <stdarg.h>

int mystring_to_upper(const char *param_src,const int param_len,char *param_obj)
{
	int i=0;
	for(i=0;i<param_len;i++)
	{
		param_obj[i]=toupper(param_src[i]);
	}
	param_obj[i]='\0';
	return 0;
}

int mystring_to_lower(const char *param_src,const int param_len,char *param_obj)
{
	int i=0;
	for(i=0;i<param_len;i++)
	{
		param_obj[i]=tolower(param_src[i]);
	}
	param_obj[i]='\0';
	return 0;
}

unsigned long mystring_atoul(const char *param)
{
	unsigned long result=0;
	int len=0;
	int i=0;
	if(param==NULL)
	{
		return 0;
	}
	result=0;
	len=strlen(param);
	i=0;
	for(i=0;i<len;i++)
	{
		result=result*10+(param[i]-'0');
	}
	return result;
}

unsigned long mystring_atoul_16(const char *param)
{
	unsigned long result=0;
	if(param)
	{
		int len=strlen(param);
		int i=0;
		for(i=0;i<len;i++)
		{
			if(param[i]>='0'&&param[i]<='9')
			{
				result=result*16+param[i]-'0';
			}
			else if(param[i]>='a'&&param[i]<='f')
			{
				result=result*16+param[i]-'a'+10;
			}
			else if(param[i]>='A'&&param[i]<='F')
			{
				result=result*16+param[i]-'A'+10;
			}
			else
			{
				result=result*16;
			}
		}
	}
	return result;
}

int mystring_one_to_two(const unsigned char *param_input,const int param_input_len,char *param_output)
{
	if(param_input&&param_input_len>=0&&param_output)
	{
		int i=0;
		for(i=0;i<param_input_len;i++)
		{
			unsigned char high;
			unsigned char low;
			high=param_input[i]>>4;
			low=param_input[i]<<4;
			low=low>>4;
			if(high<=9)
			{
				param_output[2*i]=high+'0';
			}
			if(high>=10&&high<=15)
			{
				param_output[2*i]='A'+(high-10);
			}
			if(low<=9)
			{
				param_output[2*i+1]=low+'0';
			}
			if(low>=10&&low<=15)
			{
				param_output[2*i+1]='A'+(low-10);
			}
		}
		return 2*param_input_len;
	}
	else
	{
		return -1;
	}
}

int mystring_two_to_one(const char *param_input,unsigned char *param_output)
{
	if(param_input&&param_output)
	{
		int len=strlen(param_input);
		if(len%2==0)
		{
			int i=0;
			for(i=0;i<len/2;i++)
			{
				char high_c=param_input[2*i];
				char low_c=param_input[2*i+1];
				unsigned char high=0;
				unsigned char low=0;
				if(high_c>='a'&&high_c<='f')
				{
					high=high_c-'a'+10;
				}
				else if(high_c>='A'&&high_c<='F')
				{
					high=high_c-'A'+10;
				}
				else if(high_c>='0'&&high_c<='9')
				{
					high=high_c-'0';
				}
				else
				{
					return -1;
				}
				if(low_c>='a'&&low_c<='f')
				{
					low=low_c-'a'+10;
				}
				else if(low_c>='A'&&low_c<='F')
				{
					low=low_c-'A'+10;
				}
				else if(low_c>='0'&&low_c<='9')
				{
					low=low_c-'0';
				}
				else
				{
					return -1;
				}
				param_output[i]=high*16+low;
			}
			return len/2;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

//0 class a; 1 class b; 2 class c; 3 class d; 4 class e; 5 other (mybe domain)
int mystring_get_ip(const char *param_ip_string,int *param_ip)
{
	int len=0;
	if(param_ip_string&&(len=strlen(param_ip_string))<=128)
	{
		int point_count=0;
		int i=0;
		int point_i=0;
		int point[16];
		char ip[16][128];
		if(strcasecmp(param_ip_string,"0")==0||strcasecmp(param_ip_string,"NULL")==0)
		{
			return -1;
		}
		memset(point,0,sizeof(point));
		memset(ip,0,sizeof(ip));
		point_i=0;
		for(i=0;i<len;i++)
		{
			if(param_ip_string[i]=='.')
			{
				point_count++;
				point[point_i++]=i;
			}
			else if(param_ip_string[i]>='0'&&param_ip_string[i]<='9')
			{
			}
			else
			{
				return 5;
			}
		}
		if(point_count==3)
		{
			int j=0;
			int k=0;
			for (j=0, k=0; j<point[0]; k++, j++)
			{
				ip[0][k]=param_ip_string[j];
			}
			for (j=point[0]+1, k=0; j<point[1]; k++, j++)
			{
				ip[1][k]=param_ip_string[j];
			}
			for (j=point[1]+1, k=0; j<point[2]; k++, j++)
			{
				ip[2][k]=param_ip_string[j];
			}
			for (j=point[2]+1, k=0; j<len; k++, j++)
			{
				ip[3][k]=param_ip_string[j];
			}
			for(j=0;j<4;j++)
			{
				if(strlen(ip[j])<=0)
				{
					return 5;
				}
				if(!(atoi(ip[j])>=0&&atoi(ip[j])<=255))
				{
					return 5;
				}
				if(param_ip)
				{
					param_ip[j]=atoi(ip[j]);
				}
			}
			//return 0;
			if(atoi(ip[0])>=0&&atoi(ip[0])<=127)
			{
				return 0;
			}
			else if(atoi(ip[0])>=128&&atoi(ip[0])<=191)
			{
				return 1;
			}
			else if(atoi(ip[0])>=192&&atoi(ip[0])<=223)
			{
				return 2;
			}
			else if(atoi(ip[0])>=224&&atoi(ip[0])<=239)
			{
				return 3;
			}
			else if(atoi(ip[0])>=240&&atoi(ip[0])<=255)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
		else
		{
			return 5;
		}
	}
	else
	{
		return -1;
	}
}

int mystring_is_port(const int param_port)
{
	if(param_port>=0&&param_port<=65535)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}



int enter_oneline(char *data)
{
	int i=0;
	while (1)
	{
		char c;
		if (i>=1022)
		{
			break;
		}		
		scanf("%c", &c);
		if (c=='\n')
		{
			break;
		}
		data[i++]=c;
	}
	return i;
}

int enter_oneline_to_int(int *data,const int min,const int max)
{
	char s[1024];
	int result=-1;
	while(1)
	{
		int len=0;
		memset(s,0,sizeof(s));
		len=enter_oneline(s);
		if(len==0)
		{
			*data=0;
			if(*data>=min&&*data<=max)
			{
				result=0;
				break;
			}
			else
			{
				printf("error,overflow,enter an interger between %d and %d again\n",min,max);
				continue;
			}
		}
		else if(len>10)
		{
			printf("error,overflow,enter an integer again\n");
			continue;
		}
		else
		{
			int i=0;
			int check=0;
			for(i=0;i<len;i++)
			{
				if(!(s[i]>='0'&&s[i]<='9'))
				{
					check=-1;
					break;
				}
			}
			if(check==-1)
			{
				printf("error,not an interger,enter an interger again\n");
				continue;
			}
			else
			{
				*data=atoi(s);
				if(*data>=min&&*data<=max)
				{
					result=0;
					break;
				}
				else
				{
					printf("error,overflow,enter an interger between %d and %d again\n",min,max);
					continue;
				}
			}
		}
	}
	return result;
}



int enter_oneline_to_ip(char *ip)
{
	char s[1024];
	while(1)
	{
		int len=0;
		memset(s,0,sizeof(s));
		len=enter_oneline(s);
		if(len<7||len>15)
		{
			printf("error,not ip format,enter ip again\n");
			continue;
		}
		else
		{
			int tmp=mystring_get_ip(s,NULL);
			if(tmp>=0)
			{
				strcpy(ip,s);
				return tmp;
			}
			else
			{
				printf("error,not ip format,enter ip again\n");
				continue;
			}
		}
	}
}



int mystrncpy(char *des,int len,const char*src)
{
	if(des&&src&&len>0)
	{
		int result=-1;
		int srclen=strlen(src);
		if(srclen<len)
		{
			strcpy(des,src);
			result=srclen;
		}
		else
		{
			strncpy(des,src,len-1);
			des[len-1]='\0';
			result=len-1;
		}
		return result;
	}
	else
	{
		return -1;
	}
}

int mystrncat(char *des,int len,const char*src)
{
	if(des&&src&&len>0)
	{
		int result=-1;
		int srclen=strlen(src);
		int deslen=strlen(des);
		if(srclen+deslen<len)
		{
			strcat(des,src);
			result=srclen;
		}
		else
		{
			strncat(des,src,len-deslen-1);
			des[len-1]='\0';
			result=len-srclen-1;
		}
		return result;
	}
	else
	{
		return -1;
	}
}

void mystring_change_runtime_to_string(const unsigned int param_time,char*param_time_string,int param_time_string_len)
{
	int day,hour,minute,second;
	day=param_time/(60*60*24);
	hour=(param_time/(60*60))%24;
	minute=(param_time/60)%60;
	second=param_time%60;
	snprintf(param_time_string,param_time_string_len,"%d-%d:%d:%d",day,hour,minute,second);
}

void mystring_get_build_date(char *param_date,int param_date_len)
{
	char data[128];
	char *pos1=NULL;
	char *pos2=NULL;
	memset(data,0,sizeof(data));
	snprintf(data,sizeof(data),__DATE__);
	pos1=NULL;
	pos2=NULL;
	pos1=strstr(data," ");
	if(pos1[1]==' ')
	{
		pos1++;
	}
	if(pos1)
	{
		pos2=strstr(pos1+1," ");
	}
	if(pos1&&pos2)
	{
		char day[128];
		int day_i=0;
		int month=0;
		memset(day,0,sizeof(day));
		mystrncpy(day,sizeof(day),pos1+1);
		day[pos2-pos1-1]='\0';
		mystrncpy(param_date,param_date_len,pos2+1);
		mystrncat(param_date,param_date_len,"-");
		/*if(strstr(data,"Jan")){mystrncat(param_date,param_date_len,"01");}
		else if(strstr(data,"Feb")){mystrncat(param_date,param_date_len,"02");}
		else if(strstr(data,"Mar")){mystrncat(param_date,param_date_len,"03");}
		else if(strstr(data,"Apr")){mystrncat(param_date,param_date_len,"04");}
		else if(strstr(data,"May")){mystrncat(param_date,param_date_len,"05");}
		else if(strstr(data,"Jun")){mystrncat(param_date,param_date_len,"06");}
		else if(strstr(data,"Jul")){mystrncat(param_date,param_date_len,"07");}
		else if(strstr(data,"Aug")){mystrncat(param_date,param_date_len,"08");}
		else if(strstr(data,"Sep")){mystrncat(param_date,param_date_len,"09");}
		else if(strstr(data,"Oct")){mystrncat(param_date,param_date_len,"10");}
		else if(strstr(data,"Nov")){mystrncat(param_date,param_date_len,"11");}
		else if(strstr(data,"Dec")){mystrncat(param_date,param_date_len,"12");}
		else{	mystrncat(param_date,param_date_len,"99");}*/
		month=mystring_month_char_to_int(data);
		if(month>=1&&month<=12)
		{
			char s[32];
			snprintf(s,sizeof(s),"%02d",month);
			mystrncat(param_date,param_date_len,s);
		}
		else
		{
			mystrncat(param_date,param_date_len,"99");
		}
		mystrncat(param_date,param_date_len,"-");
		day_i=atoi(day);
		if(day_i<10)
		{
			mystrncat(param_date,param_date_len,"0");
		}
		mystrncat(param_date,param_date_len,day);
	}
}


int mystring_add_head(char *des,const int des_len,const char*src)
{
	int result=0;
	if(des&&src)
	{
		char *tmp=strdup(des);
		mystrncpy(des,des_len,src);
		mystrncat(des,des_len,tmp);
		free(tmp);
		result=0;
	}
	else
	{
		result=-1;
	}
	return result;
}

int mystring_reverse(char *des,const char *src)
{
	int result=0;
	if(des&&src)
	{
		int len=strlen(src);
		int i=0;
		char *tmp=(char*)malloc(len+1);
		memset(tmp,0,len+1);
		for(i=0;i<len;i++)
		{
			tmp[i]=src[i];
		}
		strcpy(des,tmp);
		free(tmp);
	}
	return result;
}

static const unsigned long unix_npt_time=2208988800UL;

time_npt unix_to_npt_time(time_t param_time)
{
	return param_time+unix_npt_time;
}
time_t npt_to_unix_time(time_npt param_time)
{
	return param_time-unix_npt_time;
}
unsigned long get_ntp_unix_time(void)
{
	return unix_npt_time;
}

const unsigned int mystring_bit[32]=
{
		0x1,0x2,0x4,0x8,
		0x10,0x20,0x40,0x80,
		0x100,0x200,0x400,0x800,
		0x1000,0x2000,0x4000,0x8000,
		0x10000,0x20000,0x40000,0x80000,
		0x100000,0x200000,0x400000,0x800000,
		0x1000000,0x2000000,0x4000000,0x8000000,
		0x10000000,0x20000000,0x40000000,0x80000000,
};

int mystring_replace(char *str,const char old_char,const char new_char)
{
	int result=-1;
	if(str)
	{
		int len=strlen(str);
		int i;
		result=0;
		for(i=0;i<len;i++)
		{
			if(str[i]==old_char)
			{
				str[i]=new_char;
				result++;
			}
		}
	}
	return result;
}


int mystring_get_value(const char *str,const char *name,char *value,int value_len)
{
	int result=-1;
	if(str&&name&&value&&value_len>0)
	{
		const char *tmp=NULL;
		tmp=strstr(str,name);
		if(tmp)
		{
			const char *pos1=NULL;
			const char *pos2=NULL;
			const char *pos3=NULL;
			pos1=strstr(tmp,"=");
			pos2=strstr(tmp,"\"");
			if(pos2&&pos2+1)
			{
				pos3=strstr(pos2+1,"\"");
			}
			if(pos1&&pos2&&pos3&&pos3-pos2-1>0&&pos3-pos2-1<value_len)
			{
				int i=0;
				const char *tmp2=NULL;
				for(tmp2=pos2+1;tmp2<pos3;tmp2++)
				{
					value[i++]=tmp2[0];
				}
				result=0;
			}
		}
	}
	return result;
}

int mystring_change_time(const char *param_char,mystring_time_struct*param_result)
{
	int result=-1;
	if(param_char&&param_result)
	{
		param_result->year=-1;
		param_result->month=-1;
		param_result->day=-1;
		param_result->hour=-1;
		param_result->min=-1;
		param_result->sec=-1;
		sscanf(param_char,"%d-%d-%d %d:%d:%d",&param_result->year,&param_result->month,&param_result->day,&param_result->hour,&param_result->min,&param_result->sec);
		if(param_result->year>=1700&&param_result->year<=3000&&\
				param_result->month>=1&&param_result->month<=12&&\
				param_result->day>=1&&param_result->day<=31&&\
				param_result->min>=0&&param_result->min<=59&&\
				param_result->sec>=0&&param_result->sec<=59)
		{
			result=0;
		}
	}
	return result;
}

int mystring_unix_to_mystring_time(const time_t param_unix_time,mystring_time_struct *param_mystring_time)
{
	struct tm *b=gmtime(&param_unix_time);
	param_mystring_time->year=b->tm_year+1900;
	param_mystring_time->month=b->tm_mon+1;
	param_mystring_time->day=b->tm_mday;
	param_mystring_time->hour=b->tm_hour;
	param_mystring_time->min=b->tm_min;
	param_mystring_time->sec=b->tm_sec;
	return 0;
}
int mystring_unix_to_mystring_localtime(const time_t param_unix_time,mystring_time_struct *param_mystring_time)
{
	struct tm *b=localtime(&param_unix_time);
	param_mystring_time->year=b->tm_year+1900;
	param_mystring_time->month=b->tm_mon+1;
	param_mystring_time->day=b->tm_mday;
	param_mystring_time->hour=b->tm_hour;
	param_mystring_time->min=b->tm_min;
	param_mystring_time->sec=b->tm_sec;
	return 0;
}

int mystring_month_char_to_int(const char* param_month)
{
	int result=-1;
	if(param_month)
	{
		char *data=strdup(param_month);
		if(data)
		{
			int len=strlen(data);
			int i=0;
			for(i=0;i<len;i++)
			{
				if(data[i]>='A'&&data[i]<='Z')
				{
					data[i]=data[i]-'A'+'a';
				}
			}
			if (strstr(data, "jan"))
			{
				result=1;
			}
			else if (strstr(data, "feb"))
			{
				result=2;
			}
			else if (strstr(data, "mar"))
			{
				result=3;
			}
			else if (strstr(data, "apr"))
			{
				result=4;
			}
			else if (strstr(data, "may"))
			{
				result=5;
			}
			else if (strstr(data, "jun"))
			{
				result=6;
			}
			else if (strstr(data, "jul"))
			{
				result=7;
			}
			else if (strstr(data, "aug"))
			{
				result=8;
			}
			else if (strstr(data, "sep"))
			{
				result=9;
			}
			else if (strstr(data, "oct"))
			{
				result=10;
			}
			else if (strstr(data, "nov"))
			{
				result=11;
			}
			else if (strstr(data, "dec"))
			{
				result=12;
			}
			free(data);
		}
	}
	return result;
}
int mystring_month_int_to_char(const int month,char* param_month,const int param_month_len)
{
	int result=-1;
	if(month>=1&&month<=12&&param_month&&param_month_len>0)
	{
		result=0;
		switch(month)
		{
		case 1:
			snprintf(param_month,param_month_len,"%s","Jan");
			break;
		case 2:
			snprintf(param_month,param_month_len,"%s","Feb");
			break;
		case 3:
			snprintf(param_month,param_month_len,"%s","Mar");
			break;
		case 4:
			snprintf(param_month,param_month_len,"%s","Apr");
			break;
		case 5:
			snprintf(param_month,param_month_len,"%s","May");
			break;
		case 6:
			snprintf(param_month,param_month_len,"%s","Jun");
			break;
		case 7:
			snprintf(param_month,param_month_len,"%s","Jul");
			break;
		case 8:
			snprintf(param_month,param_month_len,"%s","Aug");
			break;
		case 9:
			snprintf(param_month,param_month_len,"%s","Sep");
			break;
		case 10:
			snprintf(param_month,param_month_len,"%s","Oct");
			break;
		case 11:
			snprintf(param_month,param_month_len,"%s","Nov");
			break;
		case 12:
			snprintf(param_month,param_month_len,"%s","Dec");
			break;
		default:
			snprintf(param_month,param_month_len,"%s","");
			result=-1;
			break;
		}
	}
	return result;
}


int mystring_week_char_to_int(const char*param_week)
{
	int result=-1;
	if(param_week)
	{
		char *s=strdup(param_week);
		if(s)
		{
			if (strstr(param_week, "mon"))
			{
				result=1;
			}
			else if (strstr(param_week, "tue"))
			{
				result=2;
			}
			else if (strstr(param_week, "wed"))
			{
				result=3;
			}
			else if (strstr(param_week, "thu"))
			{
				result=4;
			}
			else if (strstr(param_week, "fri"))
			{
				result=5;
			}
			else if (strstr(param_week, "sat"))
			{
				result=6;
			}
			else if (strstr(param_week, "sun"))
			{
				result=7;
			}
			free(s);
		}
	}
	return result;
}
int mystring_week_int_to_char(const int week,char *param_week,const int param_week_len)
{
	int result=-1;
	if(week>=1&&week<=7&&param_week&&param_week_len>0)
	{
		result=0;
		switch(week)
		{
		case 1:
			snprintf(param_week,param_week_len,"%s","Mon");
			break;
		case 2:
			snprintf(param_week,param_week_len,"%s","Tue");
			break;
		case 3:
			snprintf(param_week,param_week_len,"%s","Wed");
			break;
		case 4:
			snprintf(param_week,param_week_len,"%s","Thu");
			break;
		case 5:
			snprintf(param_week,param_week_len,"%s","Fri");
			break;
		case 6:
			snprintf(param_week,param_week_len,"%s","Sat");
			break;
		case 7:
			snprintf(param_week,param_week_len,"%s","Sun");
			break;
		default:
			snprintf(param_week,param_week_len,"%s","");
			result=-1;
			break;
		}
	}
	return result;
}


#endif//MYSRC_WITHOUT_STRING


