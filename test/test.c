
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "exclog_x.h"


typedef struct hx_ioc_i1000_general_param_class{
  float length;
  float width;
  float area_t_x0; //start_x;
  float area_t_y0;
  float area_t_x1; //end_x
  float area_t_y1;
  float area_s_x0;
  float area_s_y0;
  float area_s_x1;
  float area_s_y1;
  int model;
  char desc[16];
}class_t;

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_CHAR 2

int validate(void *key,char *name,int type){
	char value[32] = {0};
  if(!key){
		return -1;
	}else{
	  if(type == TYPE_INT){
		sprintf(value,"%d",*(int*)key);
		printf("key is %s int:%s\n",name,value);
	  }else if(type == TYPE_FLOAT){
		sprintf(value,"%.2f",*(float*)key);
		printf("key is %s float:%s\n",name,value);

		sprintf(value,"%s name",(char*)name);
		sprintf(value,"%.2f",*(float*)key);
		printf("key is %s float:%s\n",name,value);
	  }else{
		printf("key is %s char:%s\n",name,(char*)key);
		}
	}
	return 0;
}
int main(){
	class_t param, *p;
	p = &param;
	memset(p,0,sizeof(param));
	p->model = 12;
	p->length = 34.45;
	strcpy(p->desc,"test");

	validate(&p->model,"MODEL",TYPE_INT);
	validate(&p->length,"LENGTH",TYPE_FLOAT);
	validate(&p->desc,"DESC",TYPE_CHAR);

	int log_level = 7;

#if defined(EXCLOG_2_LOCAL)
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

	  sleep(3);
	}

 	deinit_exclog_local();

#endif

	excLOG_DEBUG("local excLOG_DEBUG test.");
	excLOG_INFO("local excLOG_INFO test.");
	excLOG_NOTICE("local excLOG_NOTICE test.");
	excLOG_WARNING("local excLOG_WARNING test.");
	excLOG_ERR("local excLOG_ERR test.");
	excLOG_CRIT("local excLOG_CRIT test.");
	excLOG_ALERT("local excLOG_ALERT test.");
	excLOG_EMERG("local excLOG_EMERG test.");
	sleep(3);



  return 0;
}

