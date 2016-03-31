/*        Filename: MYMEM.h
 **********************************************************
 * Description:
 *        this is mymem.c header.
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


#ifndef MYMEM_H_2008_5_26
#define MYMEM_H_2008_5_26

#include "common.h"

//this function only called by mymem_malloc function,other function do not called
extern void* mymem_malloc_inter(const int param_size,const int param_type,const char *pfile,const char *pfun,const int pline);
extern char*mymem_strdup_inter(const char*param_string,const int param_type,const char *pfile,const char *pfun,const int pline);
#define mymem_value_type_golbal 1
#define mymem_value_type_local 2
#define mymem_value_type_mysrc 3


//free memory
extern void mymem_free(void *param);
//malloc memory
#define mymem_malloc(param_size) \
	mymem_malloc_inter(param_size,mymem_value_type_local,__FILE__,__FUNCTION__,__LINE__);
#define mymem_malloc_golbal(param_size) \
	mymem_malloc_inter(param_size,mymem_value_type_golbal,__FILE__,__FUNCTION__,__LINE__);
#define mymem_malloc_mysrc(param_size) \
	mymem_malloc_inter(param_size,mymem_value_type_mysrc,__FILE__,__FUNCTION__,__LINE__);

#define mymem_strdup(param_string) \
	mymem_strdup_inter(param_string,mymem_value_type_local,__FILE__,__FUNCTION__,__LINE__);
#define mymem_strdup_golbal(param_string) \
	mymem_strdup_inter(param_string,mymem_value_type_golbal,__FILE__,__FUNCTION__,__LINE__);
#define mymem_strdup_mysrc(param_string) \
	mymem_strdup_inter(param_string,mymem_value_type_mysrc,__FILE__,__FUNCTION__,__LINE__);



//print the memory,that do not free
extern int mymem_print(const char*file);

#endif /*MYMEM_H_*/
