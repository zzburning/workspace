/* - data hashing functions
 *
 * Copyright (C) 2007  Emmanuele Bassi  <ebassi@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "md5.h"

static const gchar hex_digits[] = "0123456789abcdef";

//#define G_LITTLE_ENDIAN 1

#ifdef G_LITTLE_ENDIAN
#define md5_byte_reverse(buffer,length) 
#else
/* assume that the passed buffer is integer aligned */
static inline void
md5_byte_reverse (guchar *buffer,
                  gulong  length)
{
  guint32 bit;

  do
    {
      bit = (guint32) ((unsigned) buffer[3] << 8 | buffer[2]) << 16 |
                      ((unsigned) buffer[1] << 8 | buffer[0]);
      * (guint32 *) buffer = bit;
      buffer += 4;
    }
  while (--length);
}
#endif /* G_LITTLE_ENDIAN */

static gchar *
digest_to_string (guint8 *digest,
                  gsize   digest_len)
{
    gint len = digest_len * 2;
    gint i;
    gchar *retval;

    retval = (gchar *)calloc (sizeof(gchar), len + 1);

    if (retval)
    {
        for (i = 0; i < digest_len; i++)
        {
            guint8 byte = digest[i];

            retval[2 * i] = hex_digits[byte >> 4];
            retval[2 * i + 1] = hex_digits[byte & 0xf];
        }

        retval[len] = 0;
    }

    return retval;
}

/*
 * MD5 Checksum
 */

/* This MD5 digest computation is based on the equivalent code
 * written by Colin Plumb. It came with this notice:
 *
 * This code implements the MD5 message-digest algorithm.
 * The algorithm is due to Ron Rivest.  This code was
 * written by Colin Plumb in 1993, no copyright is claimed.
 * This code is in the public domain; do with it what you wish.
 *
 * Equivalent code is available from RSA Data Security, Inc.
 * This code has been tested against that, and is equivalent,
 * except that you don't need to include two pages of legalese
 * with every copy.
 */

void md5_sum_init (Md5sum *md5)
{
    /* arbitrary constants */
    md5->buf[0] = 0x67452301;
    md5->buf[1] = 0xefcdab89;
    md5->buf[2] = 0x98badcfe;
    md5->buf[3] = 0x10325476;

    md5->bits[0] = md5->bits[1] = 0;
}

/*
 * The core of the MD5 algorithm, this alters an existing MD5 hash to
 * reflect the addition of 16 longwords of new data.  md5_sum_update()
 * blocks the data and converts bytes into longwords for this routine.
 */
static void
md5_transform (guint32  buf[4],
               guint32 const in[16])
{
    register guint32 a, b, c, d;

    /* The four core functions - F1 is optimized somewhat */
#define F1(x, y, z)     (z ^ (x & (y ^ z)))
#define F2(x, y, z)     F1 (z, x, y)
#define F3(x, y, z)     (x ^ y ^ z)
#define F4(x, y, z)     (y ^ (x | ~z))

    /* This is the central step in the MD5 algorithm. */
#define md5_step(f, w, x, y, z, data, s) \
	( w += f (x, y, z) + data,  w = w << s | w >> (32 - s),  w += x )

    a = buf[0];
    b = buf[1];
    c = buf[2];
    d = buf[3];

    md5_step (F1, a, b, c, d, in[0]  + 0xd76aa478,  7);
    md5_step (F1, d, a, b, c, in[1]  + 0xe8c7b756, 12);
    md5_step (F1, c, d, a, b, in[2]  + 0x242070db, 17);
    md5_step (F1, b, c, d, a, in[3]  + 0xc1bdceee, 22);
    md5_step (F1, a, b, c, d, in[4]  + 0xf57c0faf,  7);
    md5_step (F1, d, a, b, c, in[5]  + 0x4787c62a, 12);
    md5_step (F1, c, d, a, b, in[6]  + 0xa8304613, 17);
    md5_step (F1, b, c, d, a, in[7]  + 0xfd469501, 22);
    md5_step (F1, a, b, c, d, in[8]  + 0x698098d8,  7);
    md5_step (F1, d, a, b, c, in[9]  + 0x8b44f7af, 12);
    md5_step (F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
    md5_step (F1, b, c, d, a, in[11] + 0x895cd7be, 22);
    md5_step (F1, a, b, c, d, in[12] + 0x6b901122,  7);
    md5_step (F1, d, a, b, c, in[13] + 0xfd987193, 12);
    md5_step (F1, c, d, a, b, in[14] + 0xa679438e, 17);
    md5_step (F1, b, c, d, a, in[15] + 0x49b40821, 22);

    md5_step (F2, a, b, c, d, in[1]  + 0xf61e2562,  5);
    md5_step (F2, d, a, b, c, in[6]  + 0xc040b340,  9);
    md5_step (F2, c, d, a, b, in[11] + 0x265e5a51, 14);
    md5_step (F2, b, c, d, a, in[0]  + 0xe9b6c7aa, 20);
    md5_step (F2, a, b, c, d, in[5]  + 0xd62f105d,  5);
    md5_step (F2, d, a, b, c, in[10] + 0x02441453,  9);
    md5_step (F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
    md5_step (F2, b, c, d, a, in[4]  + 0xe7d3fbc8, 20);
    md5_step (F2, a, b, c, d, in[9]  + 0x21e1cde6,  5);
    md5_step (F2, d, a, b, c, in[14] + 0xc33707d6,  9);
    md5_step (F2, c, d, a, b, in[3]  + 0xf4d50d87, 14);
    md5_step (F2, b, c, d, a, in[8]  + 0x455a14ed, 20);
    md5_step (F2, a, b, c, d, in[13] + 0xa9e3e905,  5);
    md5_step (F2, d, a, b, c, in[2]  + 0xfcefa3f8,  9);
    md5_step (F2, c, d, a, b, in[7]  + 0x676f02d9, 14);
    md5_step (F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

    md5_step (F3, a, b, c, d, in[5]  + 0xfffa3942,  4);
    md5_step (F3, d, a, b, c, in[8]  + 0x8771f681, 11);
    md5_step (F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
    md5_step (F3, b, c, d, a, in[14] + 0xfde5380c, 23);
    md5_step (F3, a, b, c, d, in[1]  + 0xa4beea44,  4);
    md5_step (F3, d, a, b, c, in[4]  + 0x4bdecfa9, 11);
    md5_step (F3, c, d, a, b, in[7]  + 0xf6bb4b60, 16);
    md5_step (F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
    md5_step (F3, a, b, c, d, in[13] + 0x289b7ec6,  4);
    md5_step (F3, d, a, b, c, in[0]  + 0xeaa127fa, 11);
    md5_step (F3, c, d, a, b, in[3]  + 0xd4ef3085, 16);
    md5_step (F3, b, c, d, a, in[6]  + 0x04881d05, 23);
    md5_step (F3, a, b, c, d, in[9]  + 0xd9d4d039,  4);
    md5_step (F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
    md5_step (F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
    md5_step (F3, b, c, d, a, in[2]  + 0xc4ac5665, 23);

    md5_step (F4, a, b, c, d, in[0]  + 0xf4292244,  6);
    md5_step (F4, d, a, b, c, in[7]  + 0x432aff97, 10);
    md5_step (F4, c, d, a, b, in[14] + 0xab9423a7, 15);
    md5_step (F4, b, c, d, a, in[5]  + 0xfc93a039, 21);
    md5_step (F4, a, b, c, d, in[12] + 0x655b59c3,  6);
    md5_step (F4, d, a, b, c, in[3]  + 0x8f0ccc92, 10);
    md5_step (F4, c, d, a, b, in[10] + 0xffeff47d, 15);
    md5_step (F4, b, c, d, a, in[1]  + 0x85845dd1, 21);
    md5_step (F4, a, b, c, d, in[8]  + 0x6fa87e4f,  6);
    md5_step (F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
    md5_step (F4, c, d, a, b, in[6]  + 0xa3014314, 15);
    md5_step (F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
    md5_step (F4, a, b, c, d, in[4]  + 0xf7537e82,  6);
    md5_step (F4, d, a, b, c, in[11] + 0xbd3af235, 10);
    md5_step (F4, c, d, a, b, in[2]  + 0x2ad7d2bb, 15);
    md5_step (F4, b, c, d, a, in[9]  + 0xeb86d391, 21);

    buf[0] += a;
    buf[1] += b;
    buf[2] += c;
    buf[3] += d;

#undef F1
#undef F2
#undef F3
#undef F4
#undef md5_step
}

void
md5_sum_update (Md5sum       *md5,
                const guchar *data,
                gsize         length)
{
    guint32 bit;

    bit = md5->bits[0];
    md5->bits[0] = bit + ((guint32) length << 3);

    /* carry from low to high */
    if (md5->bits[0] < bit)
        md5->bits[1] += 1;

    md5->bits[1] += length >> 29;

    /* bytes already in Md5sum->data */
    bit = (bit >> 3) & 0x3f;

    /* handle any leading odd-sized chunks */
    if (bit)
    {
        guchar *p = (guchar *) md5->data + bit;

        bit = MD5_DATASIZE - bit;
        if (length < bit)
        {
            memcpy (p, data, length);
            return;
        }

        memcpy (p, data, bit);

        md5_byte_reverse (md5->data, 16);
        md5_transform (md5->buf, (guint32 *) md5->data);

        data += bit;
        length -= bit;
    }

    /* process data in 64-byte chunks */
    while (length >= MD5_DATASIZE)
    {
        memcpy (md5->data, data, MD5_DATASIZE);

        md5_byte_reverse (md5->data, 16);
        md5_transform (md5->buf, (guint32 *) md5->data);

        data += MD5_DATASIZE;
        length -= MD5_DATASIZE;
    }

    /* handle any remaining bytes of data */
    memcpy (md5->data, data, length);
}

/* closes a checksum */
void
md5_sum_close (Md5sum *md5)
{
    guint count;
    guchar *p;

    /* Compute number of bytes mod 64 */
    count = (md5->bits[0] >> 3) & 0x3F;

    /* Set the first char of padding to 0x80.
     * This is safe since there is always at least one byte free
     */
    p = md5->data + count;
    *p++ = 0x80;

    /* Bytes of padding needed to make 64 bytes */
    count = MD5_DATASIZE - 1 - count;

    /* Pad out to 56 mod 64 */
    if (count < 8)
    {
        /* Two lots of padding:  Pad the first block to 64 bytes */
        memset (p, 0, count);

        md5_byte_reverse (md5->data, 16);
        md5_transform (md5->buf, (guint32 *) md5->data);

        /* Now fill the next block with 56 bytes */
        memset (md5->data, 0, MD5_DATASIZE - 8);
    }
    else
    {
        /* Pad block to 56 bytes */
        memset (p, 0, count - 8);
    }

    md5_byte_reverse (md5->data, 14);

    /* Append length in bits and transform */
    ((guint32 *) md5->data)[14] = md5->bits[0];
    ((guint32 *) md5->data)[15] = md5->bits[1];

    md5_transform (md5->buf, (guint32 *) md5->data);
    md5_byte_reverse ((guchar *) md5->buf, 4);

    memcpy (md5->digest, md5->buf, 16);

    /* Reset buffers in case they contain sensitive data */
    memset (md5->buf, 0, sizeof (md5->buf));
    memset (md5->data, 0, sizeof (md5->data));
}

gchar * md5_sum_to_string (Md5sum *md5)
{
    return digest_to_string (md5->digest, MD5_DIGEST_LEN);
}

gchar *
md5_checksum_data (const guchar *data, gsize length)
{
    gchar *retval = NULL;
    Md5sum md5;

    if (data)
    {
        md5_sum_init (&md5);
        md5_sum_update (&md5, data, length);
        md5_sum_close(&md5);
        retval = md5_sum_to_string (&md5);

    }

    return retval;
}

