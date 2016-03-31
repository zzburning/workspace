/*=============================================================================
#     FileName: wlog2file.h
#         Desc: 
#       Author: zzburning
#        Email: zzburning@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-08 16:33:05
#      History:
=============================================================================*/
#ifndef __LOG2FILE_H__
#define __LOG2FILE_H__

#include <stdio.h>
#include <stdlib.h>

static FILE *fp_LOG = NULL;           \
/**
 * log_file_open always work together with log_file_close
 */
#define LOG_FILE_OPEN(lfile) \
		fp_LOG = fopen(lfile, "a+");           \
		if(fp_LOG == NULL)                      \
			printf("open log file FAIL.\n"); \
		printf("open log file SUCCESS.\n");

#define LOG_FILE_CLOSE() \
	if(fp_LOG) \
		fclose(fp_LOG);

#define LOG2FILE(format, args...) \
	do { \
		fprintf(fp_LOG, format"\n", ##args); \
		fflush(fp_LOG); \
	} while(0);

#define DBG(format, args...) \
	fprintf(stderr, "(%s.%d.DBG): "format"\n",__FILE__,__LINE__, ##args); \
	fflush(stderr); 

#endif /* __LOG_FILE_H__ */
