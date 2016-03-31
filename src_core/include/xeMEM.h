/*
 * xeMEM.h
 *
 *  Created on: 2010-5-12
 *      Author: enigma
 */

#ifndef __HISOME_XEMEM_H__
#define __HISOME_XEMEM_H__

#include <stdlib.h>

#if defined(CONFIG_PLATFORM_X86_SIMULATE) \
	|| defined(CONFIG_PLATFORM_K2)
#define xemem_calloc(nmemb,size)	calloc(nmemb,size)
#define xemem_malloc(size)	malloc(size)
#define xemem_free(ptr)	free(ptr)
#define xemem_realloc(ptr,size) realloc(ptr,size)
#else/*CONFIG_PLATFORM_xxx*/
extern void *xemem_calloc(size_t nmemb, size_t size);
extern void *xemem_malloc(size_t size);
extern void xemem_free(void *ptr);
extern void *xemem_realloc(void *ptr, size_t size);
#endif/*!CONFIG_PLATFORM_xxx*/

#endif /* __HISOME_XEMEM_H__ */
