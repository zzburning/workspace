
#include <stdio.h>
#include <string.h>
// #include <s

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
		sprintf(value,"%.2f\0",*(float*)key);
		printf("key is %s float:%s\n",name,value);
	  }else{
		printf("key is %s char:%s\n",name,(char*)key);
		}
	}

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

  return 0;
}

