
#ifndef __MD5_H__
#define __MD5_H__

#include "md5_uglib.h"

typedef char gint8;
typedef long glong;

#define MD5_DATASIZE    64
#define MD5_DIGEST_LEN  16

typedef struct
{
    guint32 buf[4];
    guint32 bits[2];
    guchar data[MD5_DATASIZE];
    guchar digest[MD5_DIGEST_LEN];
} Md5sum;

void md5_sum_init (Md5sum *md5);
void md5_sum_update (Md5sum *md5,const guchar *data,gsize length);
void md5_sum_close (Md5sum *md5);
gchar * md5_sum_to_string (Md5sum *md5);

#endif

