fdef _WIN32
#	include <Windows.h>
#else
#	include <unistd.h>
#	include <sys/times.h>
#	include <pthread.h>
#endif
#include <list>
#include <assert.h>
#include <stdio.h>
#include "Profiler.h"
#ifdef _WIN32
class Mutex
{
	CRITICAL_SECTION cs;
public:
	Mutex()
	{
		::InitializeCriticalSection(&cs);
	}
	~Mutex()
	{
		::DeleteCriticalSection(&cs);
	};
	void Lock()
	{
		::EnterCriticalSection(&cs);
	}
	void Unlock()
	{
		::LeaveCriticalSection(&cs);
	}
};
// 普通函数运行极快, 必须用高分辨率计时器. 我们用系统自带的做一个
inline static uint64 GetTicks64()
{
	uint64 ret;
	return QueryPerformanceCounter((LARGE_INTEGER*)&ret) ? ret : 0;
}
// 时钟频率, 用来换算成秒
inline static uint64 GetTicks64Frequency()
{
	uint64 ret;
	return QueryPerformanceFrequency((LARGE_INTEGER*)&ret) ? ret : 1000;
}
#else
class Mutex
{
	pthread_mutex_t mutex;
	pthread_mutexattr_t mta;
public:
	Mutex()
	{
		pthread_mutexattr_init(&mta);
		pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex, &mta);
	}
	~Mutex()
	{
		pthread_mutex_destroy(&mutex);
		pthread_mutexattr_destroy(&mta);
	};
	void Lock()
	{
		pthread_mutex_lock(&mutex);
	}
	void Unlock()
	{
		pthread_mutex_unlock(&mutex);
	}
};
inline static uint64 GetTicks64()
{
	tms tm;
	return (unsigned long long)times(&tm);
}
inline static uint64 GetTicks64Frequency()
{
	return sysconf(_SC_CLK_TCK);
}
#endif

// 多线程支持, 做成函数是为了回避全局对象初始化顺序的问题
static Mutex & g_profiler_mutex()
{
	static Mutex _profiler_mutex;
	return _profiler_mutex;
}
#ifdef _MSC_VER
#	define __thread __declspec(thread) // __thread是GCC关键字, VC的要用__declspec(thread)
#endif
// 用来记录上最后一堆栈帧的变量, 每个线程都有一个, 所以要用TLS
static __thread ProfilerStackFrame * g_last_stack_frame = 0;
static const int MAX_PROFILE_FUNC = 2000; // 不够可扩充. 
// 最好别用std::vector或std::list, 否则可能会遇到全局对象构造顺序的问题
static FunctionProfile* g_func_profile_array[MAX_PROFILE_FUNC]; 
static unsigned int g_func_profile_count = 0;
FunctionProfile::FunctionProfile(const char * _func)
	: func(_func)
{
	callCount = 0;
	timeExclusive = 0;
	//多线程时有要加锁
	g_profiler_mutex().Lock();
	assert(g_func_profile_count < MAX_PROFILE_FUNC); // 确保不数组够用
	g_func_profile_array[g_func_profile_count++] = this;
	g_profiler_mutex().Unlock();
}
void FunctionProfile::Print()
{
	// 函数名是0时就不打印(想想看有什么用)
	if(func == 0)
	{
		return;
	}
	g_profiler_mutex().Lock();
	// 转换成秒
	float te = timeExclusive / (float) GetTicks64Frequency(); 
	printf("%s(): /t%f /t%g/n", func, te, (float)callCount);
	g_profiler_mutex().Unlock();
}

ProfilerStackFrame::ProfilerStackFrame(FunctionProfile * _profile) 
{
	// 要记录两个开始时间, 已减少误差
	// 这个构造函数的call/ret和压栈出栈时间, 以及计时器本身损耗(大概)不能直接获得, 只好忽略了
	timeBegin0 = GetTicks64();   // 必须放在函数的最前面
	profile    = _profile;           // 把堆栈帧和函数对应起来
	caller     = g_last_stack_frame; // 记住调用者
	g_last_stack_frame = this;       // 最后一帧变成当前帧
	timeSub    = 0;                  
	// 构造完后, 才是这一帧的"真正"开始时间, 
	timeBegin1 = GetTicks64();  // 必须放在函数的最后
}
ProfilerStackFrame::~ProfilerStackFrame()
{
	// 计算这一帧的实际耗时(非独占), 
	uint64 t = GetTicks64() - timeBegin1; // 必须放在函数的最前面
	// 这一帧即将消失, 最后一帧将变为上一帧
	g_last_stack_frame = caller;
	
	if(profile)
	{
		// 时间累加, 多线程时必须加锁
		g_profiler_mutex().Lock();
		profile->callCount++;                  // 调用次数加1
		profile->timeExclusive+= t - timeSub;  // 时间累加, 非独占时间减去子函数的耗时就是独占
		
		g_profiler_mutex().Unlock();
	}
	if(caller)
	{
		// 要把当前帧的耗时累加到caller的子函数耗时中.
		caller->timeSub+= GetTicks64() - timeBegin0; // 必须放在函数的最后
	}
}
// 这是排序用的比较函数, 时间长的排前面
struct MoreTimeFirst
{
	bool operator()(FunctionProfile * _l, FunctionProfile * _r) const
	{
		return _l->timeExclusive > _r->timeExclusive;
	}
};
// 排序并打印结果
void PrintProfileResult()
{
	g_profiler_mutex().Lock();
	typedef std::list<FunctionProfile*> FunctionProfileList;
	FunctionProfileList func_profile_list; 
	// 把结果扔进list里
	for(unsigned int i = 0; i < g_func_profile_count; i++)
	{
		func_profile_list.push_back(g_func_profile_array[i]);
	}
	// 排序
	func_profile_list.sort(MoreTimeFirst());
	printf("profile result:/n");
	FunctionProfileList::iterator it = func_profile_list.begin();
	for(; it!= func_profile_list.end(); ++it)
	{
		FunctionProfile * o = *it;
		o->Print();
	}
	g_profiler_mutex().Unlock();
}

