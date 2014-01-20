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
