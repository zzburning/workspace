nclude <math.h>
#include <stdio.h>
#ifdef _WIN32
#	include <Windows.h>
#else
#	include <pthread.h>
#endif
#define ENABLE_PROFILE // 性能分析开关
#include "Profiler.h"
float dummySum = 0;
void func_b(int n);
void func_a(int n)
{
	FUNCTION_PROFILE;
	if(n)
	{
		func_b(n-1);
		for(int i=0; i<1000000; i++)
		{
			dummySum+= sin((float)i);
		}
	}
}
void func_b(int n)
{
	FUNCTION_PROFILE;
	if(n)
	{
		func_a(n-1);
		for(int i=0; i<1000000; i++)
		{
			dummySum+= cos((float)i);
		}
	}
}
#ifdef _WIN32
DWORD WINAPI ThreadFunc(LPVOID)
{
	FUNCTION_PROFILE;
	func_a(10);
	return 0;
}
void test()
{
	FUNCTION_PROFILE;
	DWORD tid;
	HANDLE hThread = CreateThread(0, 0, &ThreadFunc, 0, 0, &tid);
	func_a(10);
	// 等另一个线程结束
	::WaitForSingleObject(hThread, INFINITE);
}
#else
void * ThreadFunc(void *)
{
	FUNCTION_PROFILE;
	func_a(10);
	return 0;
}
void test()
{
	FUNCTION_PROFILE;
	
	pthread_t id;
	pthread_create(&id, 0, &ThreadFunc, 0);
	func_a(10);
	// 等另一个线程结束
	void * status;
	pthread_join(id, &status);
}
#endif

int main(int argc, char ** argv)
{
	test();
	PrintProfileResult();
	getchar();
	return 0;
}

