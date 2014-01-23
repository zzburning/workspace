/*        Filename: myconf_struct.h
 **********************************************************
 * Description:
 *        this is myconf.h header.
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

#ifndef MYCONF_STRUCT_H_2008_6_6
#define MYCONF_STRUCT_H_2008_6_6


#include "mylink.h"

typedef struct _myconf_struct
{
	char*name;//variable name
	mylink_info_struct* value;//variable vale link
}myconf_struct;



typedef struct _myconf_info_struct
{
	mylink_info_struct*head;
	int find_type;
}myconf_info_struct;




#endif /*MYCONF_STRUCT_H_*/
