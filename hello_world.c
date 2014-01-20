/*=============================================================================
#     FileName: hello_world.c
#         Desc: 
#       Author: zzburning
#        Email: zzburning@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-08 13:57:21
#      History:
=============================================================================*/
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MACRO "xx"
int main(void)
{
	char path[64] = "", buf[256] = "";

// 	snprintf(path,sizeof(path),"/sys/block/%s","sdd");
	snprintf(path,sizeof(path),"/sys/block/%s","sdb");

	if((-1)==readlink(path,buf,sizeof(buf)-1))
		printf("readlink(%s) fail\n",path);

	printf("disk:%s link:%s\n",path,buf);
	return 0;


	//===
	int start = time((time_t *)NULL);

	printf("hello world!");
	char *str = MACRO;
	if(1==1){
		printf("The sun rise from the east");
	}
	char *str1 = "hell";
	char *str2 = "hell";
	int ret = strcmp(str2,str1);
	printf("ret is %d\n",ret);

	sleep(3);
	int end = time((time_t *)NULL);
	printf("use time %d\n",(end - start));

	int i;
	for(i=0; i<2; i++)
	{
		fork();
//		printf("-");
		printf("%d",i);
	}

	return 0;
}
