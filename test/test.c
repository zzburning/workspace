
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
// #include "exclog_x.h"
// #include "memwatch.h"
// #include "cJSON.h"
#include "exc.h"

extern int test_memwatch_sample();
extern int test_cjson_sample();

int test_exclog();
int test_memwatch();
int test_cjson();

int main(){
//   test_memwatch_sample();
//   test_cjson_sample();
//
//   test_exclog();
//   test_memwatch();
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

int test_cjson(){
// 	char *filename="./jsontext/test1";
// 	FILE *f=fopen(filename,"rb");fseek(f,0,SEEK_END);long len=ftell(f);fseek(f,0,SEEK_SET);
// 	char *text0=(char*)malloc(len+1);fread(text0,1,len,f);fclose(f);

// 	char text1[]="[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
// 	char text2[]="[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
// 	char text3[]="{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";	
	char text4[]="{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";
// 	char text5[]="[\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";

	char *out;cJSON *json;
	
// 	json=cJSON_Parse(text0);
// 	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
// 	else
// 	{
// 		out=cJSON_Print(json);
// 		cJSON_Delete(json);
// 		printf("text string from file:=======\n%s\n",out);
// 		free(out);
// 	}
// 	free(text0);

// 	json=cJSON_Parse(text1);
	json=cJSON_Parse(text4);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("text string:=======\n%s\n",out);
		free(out);
	}
	
	return 0;
}

