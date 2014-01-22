/*
 * excT.h
 *
 *  Created on: 2011-10-19
 *      Author: 
 *
 * Portable C basic data types
 */

#ifndef __EXC_T_H__
#define __EXC_T_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char EXC_S8;
typedef signed char EXC_SCHAR;

typedef unsigned char EXC_U8;
typedef unsigned char EXC_UCHAR;

typedef signed short EXC_S16;
typedef unsigned short EXC_U16;

typedef signed int EXC_S32;
typedef unsigned int EXC_U32;

#if defined(CONFIG_EXC_DEVPLAT_LINUXGCC_32)
typedef signed long long EXC_S64;
typedef unsigned long long EXC_U64;
#elif defined(CONFIG_EXC_DEVPLAT_VC6)
typedef __int64 EXC_S64;
typedef unsigned __int64 EXC_U64;
#else
#error "what Devplat?"
#endif

typedef void EXC_VOID;

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

#endif /* __EXC_T_H__ */
