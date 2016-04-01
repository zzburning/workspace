
/* 
* File:   log.c:日志系统的实现
*/
#include "log_config.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
/*
*功能：调试输出函数
*/
void log_debug(const char *file, const int line, const char *format,...)
{
    if(!log_config->log.DebugModel) 
        return;    
    char new_format[2048];
    
    va_list va;
    va_start(va, format);
    
    snprintf(new_format, 8191 , "/n[%s] | [%s %d] %s",ServerTime(), file, line, format);

    if(vfprintf(log_config->log.debug_log, new_format, va) < 0)
        fprintf(stderr, "警告. [%s %d] %s/n", __FILE__, __LINE__, strerror(errno));

    va_end(va);
}
/*
*功能：警告或者错误输出函数
*
*/
void vlog_debug(FILE *file, const char *format,...)
{

    if(!file) 
        return;

    static char new_format[2048];
    
    va_list va;
    va_start(va, format);
    
    snprintf(new_format,8191 , "/n[%s] | %s",ServerTime(), format);

    if(vfprintf(file, new_format, va) < 0)
        fprintf(stderr, "警告 [%s %d] %s/n", __FILE__, __LINE__, strerror(errno));

    va_end(va);
}
