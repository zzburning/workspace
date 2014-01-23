/*        Filename: mystring.h
 **********************************************************
 * Description:
 *        this is mystring.c header.
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


#ifndef MYSTRING_H_2008_4_11
#define MYSTRING_H_2008_4_11

#ifndef MYSRC_WITHOUT_STRING

#include <time.h>


#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

extern int mystring_to_upper(const char *param_src,const int param_len,char *param_obj);
extern int mystring_to_lower(const char *param_src,const int param_len,char *param_obj);

extern unsigned long mystring_atoul(const char *param);
extern unsigned long mystring_atoul_16(const char *param);

extern int mystring_one_to_two(const unsigned char *param_input,const int param_input_len,char *param_output);
extern int mystring_two_to_one(const char *param_input,unsigned char *param_output);

extern int mystring_get_ip(const char *param_ip_string,int *param_ip);//if the string is ip format return >0,else return -1
extern int mystring_is_port(const int param_port);//if the number is port return 0,else return -1


extern int enter_oneline(char *data);
extern int enter_oneline_to_int(int *data,const int min,const int max);
extern int enter_oneline_to_ip(char *ip);

extern int mystrncpy(char *des,int len,const char*src);
extern int mystrncat(char *des,int len,const char*src);

extern void mystring_change_runtime_to_string(const unsigned int param_time,char*param_time_string,int param_time_string_len);
extern void mystring_get_build_date(char *param_date,int param_date_len);

extern int mystring_add_head(char *des,const int des_len,const char*src);

extern int mystring_reverse(char *des,const char *src);

typedef unsigned long time_npt;
extern time_npt unix_to_npt_time(time_t param_time);
extern time_t npt_to_unix_time(time_npt param_time);
extern unsigned long get_ntp_unix_time(void);

extern int mystring_replace(char *str,const char old_char,const char new_char);

extern const unsigned int mystring_bit[32];

//extern int myscanf(const char *param_format,...);


extern int mystring_get_value(const char *str,const char *name,char *value,int value_len);

typedef struct _mystring_time_struct
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}mystring_time_struct;

extern int mystring_change_time(const char *param_char,mystring_time_struct*param_result);

extern int mystring_unix_to_mystring_time(const time_t param_unix_time,mystring_time_struct *param_mystring_time);
extern int mystring_unix_to_mystring_localtime(const time_t param_unix_time,mystring_time_struct *param_mystring_time);

extern int mystring_month_char_to_int(const char* param_month);
extern int mystring_month_int_to_char(const int month,char* param_month,const int param_month_len);

extern int mystring_week_char_to_int(const char*param_week);
extern int mystring_week_int_to_char(const int week,char *param_week,const int param_week_len);

#ifdef __cplusplus
}
#endif//__cplusplus


#endif//MYSRC_WITHOUT_STRING


#endif /*MYSTRING_H_*/


