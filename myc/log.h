/* 
* File:   log.h:日志系统的头文件
*/

#include "log_config.h"


#ifndef _LOG_H
#define _LOG_H


    
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


#endif    /* _LOG_H */
/* 
* File:   log_config.h:整个程序的配置文件头文件
*/
#ifndef _LOG_CONFIG_H
#define _LOG_CONFIG_H


#define CONLINELENGTH 1024
#include <stdio.h>
#include <arpa/inet.h>

extern struct config_t *log_config;
extern struct timeval current_time;

/*
 *结构体功能：定义基本的系统配置信息
 *由config Init函数初始化
 */
struct config_t {

    struct {
        int DebugModel;
        char DebugPath[400];
        FILE *debug_log;
        char LogPath[400];
        FILE *log_log;
        char AccessPath[400];
        FILE *access_log;
    } log;

    struct {
        int port;
        struct in_addr localIP;
        int debug_mode;
        long long MaxMem;
    } server;

    struct {
        time_t client_life;
        time_t server_life;
        time_t request;
        time_t reply;
        time_t connect;
    } timeout;

    struct {
        int MinIndex; //pool 
        int Align;//对齐步进单位，4，8，16等等，每项所能容纳的最大内存为Align*index，index为shortint，所以单项最大容量为Align*255*255字节，4字节对齐最大为260K，8字节对齐为512K
        int InitMemItem; //初始化池所能拥有的数量不能超过255*255
        int ExpendMemItem; //每次扩展池多少项。不能超过255*255
        long MaxMemory; //内存池最大容量 300M
    } memory;
};
/*
 *函数功能：将当前时间压入时间容器，以求达到定时获取时间而不影响性能的目的
 */
extern void CurrentTimeGet(void);
/*
 *函数功能：获取服务器端时间
 *返回的值为时间的格式化后的字符串
 */
extern char *ServerTime(void) ;
/*
 *函数功能：从给定的文件中获取指定项的配置值
 *返回的值为堆内存，需要显示释放
 */
extern char *ReadConfigfile(char *fileName, char *item);
  /*
  *函数功能：初始化服务器配置文件
  *返回值：void
  */
extern void InitConf();
 /*
  *函数功能：测试config各函数的功能
  *返回值：void
  */
extern void TestConf();
/*
 *销毁系统，为重新加载作准备
 */
extern void DestroySystem();



#endif    /* _CONFIG_H */
