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
#include <stdlib.h>

#define MACRO "xx"

#if 0
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

/**
 * @file pipe.c
 * @synopsis  pipe
 * @author wangtao <wangtao@hisome.com>
 * @version 0.1
 * @date 2014-01-08
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LINE 80 
#define PIPE_STDIN 0 
#define PIPE_STDOUT 1 

#define DEMO_SIMPLE 0
#define DEMO_FORK 0
#define DEMO_LS_PIPE_WC 0
#define DEMO_FIFO 1

/* --------------------------------------------------------------------------*/
/**
 * @synopsis  create a new pipe 创建新的匿名管道,用于父子进程间通信
 *
 * @param fds[2] dir:OUT fds[0]-for read fds[1]-for write
 *
 * @returns   0-success; -1-fail
 */
/* ----------------------------------------------------------------------------*/
// int pipe(int fds[2]);

/* --------------------------------------------------------------------------*/
/**
 * @synopsis dup,dup2 拷贝文件描述符 
 *
 * @param oldfb
 * @param targetfb
 *
 * @returns   
 */
/* ----------------------------------------------------------------------------*/
// int dup(int oldfb); 
// int dup(int oldfb, int targetfb);

/* --------------------------------------------------------------------------*/
/**
 * @synopsis  mkfifo  创建命名管道,用于任意两进程间通信
 *
 * @param pathname 文件系统中创建的专用文件
 * @param mode FIFO的读写权限
 *
 * @returns 0-success; -1-fail 
 */
/* ----------------------------------------------------------------------------*/
// int mkfifo(const char *pathname, mode_t mode);

int main()
{
  const char *string={"A sample message."};
  int ret, myPipe[2];
  FILE *pfb, *pfb2;
  char buffer[MAX_LINE+1];

  /**//* 建立管道 */
  ret = pipe( myPipe );

  if (ret == 0) {

#if DEMO_SIMPLE
	//---simple write & read
	/**//* 将消息写入管道 */
	write( myPipe[PIPE_STDOUT], string, strlen(string) );

	/**//* 从管道读取消息 */
	ret = read( myPipe[PIPE_STDIN], buffer, MAX_LINE );

	/**//* 利用Null结束字符串 */
	buffer[ ret ] = 0;

	printf("%s\n", buffer);
#endif

#if DEMO_FORK
	// --use fork 共同祖先的进程间通信
	if (fork() == 0) {
	  ret = read( myPipe[0], buffer, MAX_LINE );
	  buffer[ret] = 0;
	  printf( "Child read %s\n", buffer);//note-add \n after buffer
	} else {
	  ret = write(myPipe[1], string, strlen(string) );
	  ret = wait( NULL );
	}

#endif

#if DEMO_LS_PIPE_WC
	if ( fork() == 0 ) {
	  close(1);
	  dup2(myPipe[1], 1 );
	  close(myPipe[0] );
	  execlp( "ls", "ls", "-1", NULL );
	} else {
	  close(0);
	  dup2(myPipe[0], 0 );
	  close(myPipe[1] );
	  execlp( "wc", "wc", "-l", NULL );
	}
#endif

	// 	close(myPipe[0]);
	// 	close(myPipe[1]);
  }

#if DEMO_FIFO
  ret = mkfifo("/tmp/fifo_first", S_IFIFO | 0666);
  if(ret == 0){
	printf("create fifo success.\n");
	// 	if(fork() == 0) {
	pfb2 = fopen("/tmp/fifo_first", "rw+");
	fprintf(pfb2,"Here is a test String\n");
	fclose(pfb2);
	// 	}else{
	pfb = fopen("/tmp/fifo_first", "r");
	fscanf(pfb,"%s",buffer);
	buffer[ret] = '\0';
	printf("%s\n",buffer);
	fclose(pfb);
	// 	}
  }else{
	printf("create fifo failed.\n");
  }
#endif

  return 0;
}
main(_){_^448&&main(-~_);putchar(--_%64?32|-~7[__TIME__-_/8%8][">'txiZ^(~z?"-48]>>";;;====~$::199"[_*2&8|_/64]/(_&2?1:8)%8&1:10);}
#endif

/* getopt.c */
#include <unistd.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
  int aflag=0, bflag=0, cflag=0;
  int ch;
  while ((ch = getopt(argc, argv, "ab:c")) != -1)
  {
	printf("optind: %d\n", optind);
	switch (ch) {
	  case 'a':
		printf("HAVE option: -a\n");
		aflag = 1;
		break;
	  case 'b':
		printf("HAVE option: -b\n");
		bflag = 1;
		printf("The argument of -b is %s\n", optarg);
		break;
	  case 'c':
		printf("HAVE option: -c\n");
		cflag = 1;
		break;
	  case '?':
		printf("Unknown option: %c\n",(char)optopt);
		break;
		// 			default:
	}
  }
}

typedef struct
{
  char name[21];
  char city[21];
  char phone[21];
  char *comment;
} Addr;
// 如果没有评论记录，评论框里只包含一个指针（4个字节）。包含评论的记录会分配恰到好处的空间，保存评论的的字符串，这取决于用户输入的字符串的长度。
void get_info()
{
//   char cmms[20] = "hello world!";
//   gets(cmms);
//   printf("sizeof array char[20]:%d, strlen:%d\n", sizeof(cmms), strlen(cmms));
  Addr s;
  char comm[100];
  char *p;

  gets(s.name);
  gets(s.city);
  gets(s.phone);
  gets(comm);
  s.comment = (char *) malloc(strlen(comm)+1);
  strcpy(s.comment, comm);
  //do something using struct s
}
