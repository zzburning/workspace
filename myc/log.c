
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

/* 
* File:   log_config.c:整个程序文件的配置文件实现
*/
#include "log_config.h"
//#include "log.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>


struct timeval current_time;
struct config_t conf, *log_config;

/*
*函数功能：将当前时间压入时间容器，以求达到定时获取时间而不影响性能的目的
*/
void CurrentTimeGet(void) {
     gettimeofday(&current_time, NULL);
}
/*
*函数功能：获取服务器端时间
*返回的值为时间的格式化后的字符串
*/
char *ServerTime(void) {
    CurrentTimeGet();
    static char timestr[128];
    struct tm *tm = gmtime(&(current_time.tv_sec));
    if (tm == NULL)
        return NULL;

    strftime(timestr, 127, "%Y/%m/%d %H:%M:%S", tm);
    return timestr;
}
/*
*函数功能：从给定的文件中获取指定项的配置值
*返回的值为堆内存，需要显示释放
*/
char *ReadConfigfile(char *fileName, char *item) {
    FILE *fp;
    char *locate = NULL;
    char *pmove = NULL;
    char confLine[CONLINELENGTH] = {};
    char context[CONLINELENGTH] = {};
    int result = 1;
    char *pline;
    int itl;


    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("打开文件 : %s 失败!!/n", fileName);
        return NULL;
    }

    while (fgets(confLine, CONLINELENGTH, fp) != NULL) {
        pline = confLine;
        if (*pline == '#'||*pline == '/'||*pline == '*') {
            memset(confLine, '0', CONLINELENGTH);
            continue;
        }
        while (isspace(*pline) != 0)pline++;
        locate = strchr(pline, '=');
        if (locate == NULL) {
            memset(confLine, '0', CONLINELENGTH);
            continue;
        }
        pmove = locate;
        pmove--;
        while (isspace(*pmove) != 0)pmove--;
        itl = pmove - pline + 1;
        if (itl == strlen(item)) {
            result = strncasecmp(pline, item, itl);
            if (result == 0) {
                locate++;
                while (isspace(*locate) != 0)locate++;
                pmove = locate;
                while (isspace(*pmove) == 0)pmove++;
                if (pmove - locate + 1 < 0) {
                    strncpy(context, locate, pmove - locate + 1);
                    break;
                } else {
                    fclose(fp);
                    return NULL;
                }
            } else {
                memset(confLine, '0', CONLINELENGTH);
                continue;
            }
        } else {
            memset(confLine, '0', CONLINELENGTH);
            continue;
        }
    }
    fclose(fp);
    char * rtn=(char *)malloc(strlen(context)+1);
    strcpy(rtn,context);

    char *tmp=rtn;
    while(*tmp   !=   '/n')           //去掉字符串结束符'/0'前的'/n'    
	tmp++; 
    *tmp   =   '/0';

    return rtn;
}
/*
*获得配置文件的Int值
*/
int GetConfInt(char * confPath,char *name)
{
    int rtn=0;
    char *readname=ReadConfigfile(confPath,name);
    if(readname!=NULL)
    {
        rtn=atol(readname);
        int len=strlen(readname);
        char * ls=readname;
        ls+=len-1;
        *ls=tolower(*ls);
        //内存单位换算，结果为byte
        if(*ls=='m')//M
            rtn=rtn*1024*1024;
        if(*ls=='k')//K
            rtn=rtn*1024;
        if(*ls=='g')//G
            rtn=rtn*1024*1024*1024;
        //时间单位换算，结果为秒
        if(*ls=='s')//分
            rtn=rtn*60;
        if(*ls=='h')//小时
            rtn=rtn*60*60;
        if(*ls=='d')//天
            rtn=rtn*60*60*24;
    }
    else
    {
        printf("配置文件中找不到叫:%s的项!",name);
    }
    free(readname);
    return rtn;
}
/*
*内部函数：初始化Log
*/
void InitLog(char * confPath)
{
     //设置logPath,如果成功就打开log文件
    char *logpath=ReadConfigfile(confPath,"LogPath");
    if(logpath!=NULL)
    {
        strcpy(log_config->log.LogPath,logpath);
        log_config->log.log_log = fopen(logpath, "a");
        setvbuf(log_config->log.log_log, NULL, _IONBF, 0);
    }
    else
    {
        printf("logPath路径不正确！/n");
    }
    free(logpath);
     //设置debugPath,如果成功就打开log文件
    char *debugpath=ReadConfigfile(confPath,"DebugPath");
    if(debugpath!=NULL)
    {
        strcpy(log_config->log.DebugPath,debugpath);
        log_config->log.debug_log = fopen(debugpath, "a");
        setvbuf(log_config->log.debug_log, NULL, _IONBF, 0);
    }
      else
    {
        printf("debugPath路径不正确！/n");
    }
    free(debugpath);
     //设置accessLogPath,如果成功就打开log文件
    char *accesspath=ReadConfigfile(confPath,"AccessPath");
    if(accesspath!=NULL)
    {
        strcpy(log_config->log.AccessPath,accesspath);
        log_config->log.access_log = fopen(accesspath, "a");
        setvbuf(log_config->log.access_log, NULL, _IONBF, 0);
    }
    else
    {
        printf("accessPath路径不正确！/n");
    }
    free(accesspath);
   // log_debug(__FILE__, __LINE__, "完成了系统日志的初始化!/n");
   printf("/n日志系统初始化完毕，路径如下：/n   L___%s/n   L___%s/n  L___%s/n",log_config->log.LogPath,log_config->log.AccessPath,log_config->log.DebugPath);

    char *debugmodel=ReadConfigfile(confPath,"DebugModel");
    if(debugmodel!=NULL)
    {
        int debugm=atoi(debugmodel);
        log_config->log.DebugModel=debugm;
        if(debugm)
            printf("   L___调试状态开启/n");
    }
    free(debugmodel);
}
/*
*功能：初始化内存池相关，内部函数
*返回：空
*/
void InitMem(char *confPath)
{
      //设置MaxIndex
    log_config->memory.MinIndex=GetConfInt(confPath,"MinIndex");
    log_config->memory.Align=GetConfInt(confPath,"Align"); 
    log_config->memory.ExpendMemItem=GetConfInt(confPath,"ExpendMemItem");
    log_config->memory.InitMemItem=GetConfInt(confPath,"InitMemItem");
    log_config->memory.MaxMemory=GetConfInt(confPath,"MaxMemory");
    printf("内存池配置：MinIndex =%d,Align =%d/n           InitMemItem=%d,ExpendMemItem =%d,MaxMemory=%d/n",log_config->memory.MinIndex,log_config->memory.Align,log_config->memory.InitMemItem,log_config->memory.ExpendMemItem,log_config->memory.MaxMemory);

}
/*
     *函数功能：初始化服务器配置文件
     *返回值：void
     */
void InitConf()
{
    log_config=(struct log_config_t*)malloc(sizeof(struct config_t));
    //此处的配置字符串以后要改成读取应用程序根目录下面的文件，从而达到直接读取配置文件的目的
    char *confPath="net.conf.default";
    InitLog(confPath);
    InitMem(confPath);
     //初始化内存池
    //InitPool();
}
/*
*销毁系统，为重新加载作准备
*/
void DestroySystem()
{
    //销毁Mempool
    //FreePool();
    free(log_config);
}
/*
     *函数功能：测试log_config各函数的功能
     *返回值：void
     */
void TestConf()
{
    printf("当前正在测试log_config文件的ReadConfigfile函数功能\n");
    char * port=NULL;
    port = strdup(ReadConfigfile("test.conf","port"));
    if(port!=NULL)
        printf("参数port的值为%s\n",port);
    else
        printf("参数port的值不存在\n");
    printf("当前正在测试服务器端时间函数:\n");
    printf("当前时间：%s\n",ServerTime());
}

