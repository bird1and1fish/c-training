#include "stdio.h"
#include "windows.h"

CRITICAL_SECTION g_cs;// �ٽ����������ڼ���
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
		EnterCriticalSection(&g_cs);// �����ٽ���������������Դ
		if (tickets > 0)
			printf("Thread 1 sell tickets %d\n", tickets--);
		else
			break;
		LeaveCriticalSection(&g_cs);// �˳��ٽ������ͷ���������Դ
	}
	printf("###Thread 1 tickets sold out###\n");
	return 0;
}

DWORD WINAPI ThreadProc2(PVOID pParam)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_cs);// �����ٽ���������������Դ
		if (tickets > 0)
			printf("Thread 2 sell tickets %d\n", tickets--);
		else
			break;
		LeaveCriticalSection(&g_cs);// �˳��ٽ������ͷ���������Դ
	}
	printf("###Thread 2 tickets sold out###\n");
	return 0;
}

int main(int argc, char* argv[])
{
	/* �����̵߳�����
	// �ṹ�İ�ȫ����ָ�룬�̶߳�ջ�Ĵ�С���̺߳�������ڵ�ַ�����ݸ��̵߳Ĳ���ָ�룬�̴߳����Ŀ�����Ϣ��Ϊ0ʱ����ִ�У�
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	*/
	
	InitializeCriticalSection(&g_cs);// ��ʼ���ٽ�������
	HANDLE hHandle[2];
	hHandle[0] = CreateThread(NULL, 0, ThreadProc1, 0, 0, NULL);
	hHandle[1] = CreateThread(NULL, 0, ThreadProc2, 0, 0, NULL);
	// ��Ҫ�ȴ����̶߳����������Ҫ�ȴ����̵߳ľ������ָ�룬�ȴ����ж����ǵȴ�����һ�����󣬵ȴ�ʱ������
	WaitForMultipleObjects(2, hHandle, TRUE, INFINITE);
	DeleteCriticalSection(&g_cs);// �ͷ��ٽ�������

	return 0;
}