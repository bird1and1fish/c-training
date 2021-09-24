#include "stdio.h"
#include "windows.h"

CRITICAL_SECTION g_cs;// 临界区对象，用于加锁
int tickets = 1000;

DWORD WINAPI ThreadProc(PVOID pParam)
{
	printf("hello thread\n");
	return 0;
}

DWORD WINAPI ThreadProc1(PVOID pParam)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);// 进入临界区，锁定共享资源
		if (tickets > 0)
			printf("Thread 1 sell tickets %d\n", tickets--);
		else
			break;
		LeaveCriticalSection(&g_cs);// 退出临界区，释放锁定的资源
	}
	printf("###Thread 1 tickets sold out###\n");
	return 0;
}

DWORD WINAPI ThreadProc2(PVOID pParam)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);// 进入临界区，锁定共享资源
		if (tickets > 0)
			printf("Thread 2 sell tickets %d\n", tickets--);
		else
			break;
		LeaveCriticalSection(&g_cs);// 退出临界区，释放锁定的资源
	}
	printf("###Thread 2 tickets sold out###\n");
	return 0;
}

int main(int argc, char* argv[])
{
	/* 单个线程的例子
	// 结构的安全属性指针，线程堆栈的大小，线程函数的入口地址，传递给线程的参数指针，线程创建的控制信息（为0时立即执行）
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	*/
	
	InitializeCriticalSection(&g_cs);// 初始化临界区对象
	HANDLE hHandle[2];
	hHandle[0] = CreateThread(NULL, 0, ThreadProc1, 0, 0, NULL);
	hHandle[1] = CreateThread(NULL, 0, ThreadProc2, 0, 0, NULL);
	// 需要等待的线程对象个数，需要等待的线程的句柄数组指针，等待所有对象还是等待任意一个对象，等待时间上限
	WaitForMultipleObjects(2, hHandle, TRUE, INFINITE);
	DeleteCriticalSection(&g_cs);// 释放临界区对象

	return 0;
}