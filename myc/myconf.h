/*        Filename: myconf.h
 **********************************************************
 * Description:
 *        this is myconf.c header.
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

#ifndef MYCONF_H_2008_6_6
#define MYCONF_H_2008_6_6


#include "myconf_struct.h"


extern const int MYCONF_FIND;
extern const int MYCONF_CASE_FIND;

extern myconf_info_struct* myconf_parser(const char *param_file,int param_find_type);
extern int myconf_clean(myconf_info_struct*param_conf_info);
extern int myconf_get_value_count(myconf_info_struct*param_myconf_info,const char *param_name);
extern const char* myconf_get_value(myconf_info_struct*param_myconf_info,const int param_index,const char*param_name);
extern int myconf_get_name_count(myconf_info_struct*param_myconf_info);
extern const char* myconf_get_name(myconf_info_struct*param_myconf_info,const int param_index);








#endif /*MYCONF_H_*/
