
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "exclog_x.h"
#include "memwatch.h"

int test_exclog();
int test_memwatch();
extern int test_memwatch_sample();
extern int test_cjson();

int main(){

  test_exclog();
  test_memwatch();
  test_memwatch_sample();
  test_cjson();
  return 0;
}

int test_exclog(){
#if defined(EXCLOG_2_LOCAL)
	int log_level = 7;

	init_exclog_local_t init;	 
	memset(&init,0,sizeof(init));

	init.local_port=514;
	init.be_syslog=0;
	init.be_klog=0;
	init.log_level=7;
	strncpy(init.path, "./",sizeof(init.path)-1);
	init.num=1;
	init.size=1024*1024;//byte
	init.msg2stdout=1;

	int ret=init_exclog_local(&init);
	if (ret!=0) {
	  printf("init_exclog fail.\n");
	  return -1;
	} else {
	  printf("init_exclog success.\n");
	}
	
	while (0)
	{
	  excLOG_DEBUG("debug message");
	  excLOG_INFO("info msg");
	  excLOG_NOTICE("notice msg");
	  excLOG_WARNING("warning msg");
	  excLOG_ERR("error msg");
	  excLOG_ALERT("alert msg");
	  excLOG_CRIT("crit msg");
	  excLOG_EMERG("emerg msg");

	  sleep(3);//time for flush_2_file
	}

 	deinit_exclog_local();

#endif
	return 0;
}


int test_memwatch(){
  char *a = NULL;
  if ((a = (char *) malloc(sizeof(char))) == NULL)
  {
	printf("malloc fail,%s.\n", strerror(errno));
	return -1;
  }
  return 0;
}

