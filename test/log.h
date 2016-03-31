/* 
* File:   log.h:日志系统的头文件
*/

#include "log_config.h"


#ifndef _LOG_H
#define _LOG_H

//#ifdef    __cplusplus
//extern "C" {
//#endif

    
#define Error(fmt, ...) /
             vlog_debug(log_config->log.log_log, "[%s %d] 错误： "fmt, __FILE__, __LINE__, __VA_ARGS__)

#define Warning(fmt, ...) /
             vlog_debug(log_config->log.log_log, "[%s %d] 警告： "fmt, __FILE__, __LINE__, __VA_ARGS__)
#define Record(fmt, ...) /
             vlog_debug(log_config->log.access_log, "[%s %d] 记录： "fmt, __FILE__, __LINE__, __VA_ARGS__)

#define Debug(fmt, ...) /
             log_debug(__FILE__, __LINE__, fmt, __VA_ARGS__)
    

extern void log_debug(const char *file, const int line, const char *format,...);
extern void vlog_debug(FILE *file, const char *format,...);

/*#ifdef    __cplusplus*/
//}
//#endif

#endif    /* _LOG_H */
