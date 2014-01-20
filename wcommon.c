/*=============================================================================
#     FileName: wcommon.c
#         Desc: 
#       Author: zzburning
#        Email: zzburning@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-22 16:57:04
#      History:
=============================================================================*/
#include "wcommon.h"

static void __report(int res, char* action)
{
	int errno;
	char *errstr;

	if(res >= 0)
	{
		LOG2FILE("\tDo Action(%s) PASS!", action); //cur_cmd->ac_name);
	}
	else if(res <= -1)
	{
		errno = res; //report errno message
		errstr = "ERROR"; //get_errstr(action, errno);
		LOG2FILE("\tDo Action(%s) FAIL! errno=%d errstr=%s", action, errno, errstr);
	}
	else if(res == -11)
	{
		LOG2FILE("\tDo Action(%s) FAIL! ARG ERROR!!!", action);
	}
	else
	{
		DBG("It's a bug!!!");
	}
}

#include "log_config.h"
#include "wcommon.h"

int main()
{
	//int ret;
	int a = 10;
	TestConf();
	LOG_FILE_OPEN("log.txt")
	LOG2FILE("THIS IS LOG %d",a)
	LOG_FILE_CLOSE()
	return 0;
}
