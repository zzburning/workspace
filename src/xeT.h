/*
 * xeT.h
 *
 *  Created on: 2011-10-19
 *      Author: enigma
 *
 * Portable C basic data types
 */

#ifndef __HISOME_XEHSC_T_H__
#define __HISOME_XEHSC_T_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char XE_S8;
typedef signed char XE_SCHAR;

typedef unsigned char XE_U8;
typedef unsigned char XE_UCHAR;

typedef signed short XE_S16;
typedef unsigned short XE_U16;

typedef signed int XE_S32;
typedef unsigned int XE_U32;

#if defined(CONFIG_XEHSC_DEVPLAT_LINUXGCC_32)
typedef signed long long XE_S64;
typedef unsigned long long XE_U64;
#elif defined(CONFIG_XEHSC_DEVPLAT_VC6)
typedef __int64 XE_S64;
typedef unsigned __int64 XE_U64;
#else
#error "what Devplat?"
#endif

typedef void XE_VOID;

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifdef __cplusplus
};
#endif

#endif /* __HISOME_XEHSC_T_H__ */
