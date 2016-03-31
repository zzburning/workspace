
/*
 * 线程同步：条件变量
典型用法
volatile int val = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
......
THREAD_A:
pthread_mutex_lock(&mutex);
while(!val)
	 pthread_cond_wait(&cond, &mutex); 
 pthread_mutex_unlock(&mutex);
 ......
 THREAD_B:
 pthread_mutex_lock(&mutex);
 val = 1;
 pthread_mutex_unlock(&mutex);
 pthread_cond_signal(&cond)
注意：
在进入pthread_cond_wait之前需要先进行条件(val)判断，否则有可能会丢失cond唤醒;
条件val需要用volatile修饰，否则编译器优化时可能会在while(!val)处进入死循环
*/
// 条件丢失的典型例子如下O
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
volatile int val = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *test_thread(void*data)
{
	pthread_mutex_lock(&mutex);
	val = 1;
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&cond);
	return NULL;
}
int main()
{
	int ret=0;
	pthread_t pt;
	struct timespec timeout;
	printf("Create thread\n");
	pthread_create(&pt, NULL, test_thread, NULL);
	pthread_detach(pt);
	printf("sleep 1\n");
	sleep(1);
	printf("cond wait, timeout time:2\n");
	pthread_mutex_lock(&mutex);
	clock_gettime(CLOCK_REALTIME, &timeout);
	timeout.tv_sec += 2;
// 	while(!val)
	{
		ret = pthread_cond_timedwait(&cond, &mutex, &timeout);
	}
	pthread_mutex_unlock(&mutex);
	printf("ret:%d\n", ret);
	if (ret != 0){
		printf("time out\n");
		printf("error: %s\n", strerror(ret));
	}
	return 0;
}

// 上例子线程在主线程进入pthread_cond_timedwait之前唤醒条件变量，所以实际上主线程并不会检测到这次唤醒，直到2秒超时才会继续往下运行。0
