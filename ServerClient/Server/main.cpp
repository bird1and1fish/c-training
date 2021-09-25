#include <iostream>
#include <stdlib.h>
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")// 链接库文件

using namespace std;

DWORD WINAPI threadpro(LPVOID pParam)
{
	SOCKET hsock = (SOCKET)pParam;
	char buffer[1024];
	char sendBuffer[1024];

	if (hsock != INVALID_SOCKET)
		cout << "Start receive" << endl;

	while (1)
	{
		int num = recv(hsock, buffer, 1024, 0);// 阻塞函数，等待接收内容
		if (num >= 0)
			cout << "Receive from clinet" << buffer << endl;
		if (!strcmp(buffer, "A"))
		{
			memset(sendBuffer, 0, 1024);
			strcpy(sendBuffer, "B");
			int ires = send(hsock, sendBuffer, sizeof(sendBuffer), 0);// 回送信息
			cout << "Send to client" << sendBuffer << endl;
		}

		else if (!strcmp(buffer, "C"))
		{
			memset(sendBuffer, 0, 1024);
			strcpy(sendBuffer, "D");
			int ires = send(hsock, sendBuffer, sizeof(sendBuffer), 0);// 回送信息
			cout << "Send to client" << sendBuffer << endl;
		}

		else if (!strcmp(buffer, "exit"))
		{
			cout << "Client close" << endl;
			cout << "Server process close" << endl;
			return 0;
		}

		else
		{
			memset(sendBuffer, 0, 1024);
			strcpy(sendBuffer, "ERR");
			int ires = send(hsock, sendBuffer, sizeof(sendBuffer), 0);// 回送信息
			cout << "Send to client" << sendBuffer << endl;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	WSADATA wsd;// 该结构记录了套接字信息
	WSAStartup(MAKEWORD(2, 2), &wsd);// 初始化Winsock
	SOCKET m_SockServer;
	sockaddr_in serveraddr;
	sockaddr_in serveraddrfrom;
	SOCKET m_Server[20];

	serveraddr.sin_family = AF_INET;// 设置服务器地址家族
	serveraddr.sin_port = htons(4600);// 设置服务器端口号
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	m_SockServer = socket(AF_INET, SOCK_STREAM, 0);

	int i = bind(m_SockServer, (sockaddr*)&serveraddr, sizeof(serveraddr));// 将套接字绑定到指定的端口和地址上
	cout << "bind:" << i << endl;

	int iMaxConnect = 20;// 最大连接数
	int iConnect = 0;
	int iLisRet;
	char buf[] = "THIS IS SERVER\0";// 向客户端发送的内容
	char WarnBuf[] = "It is voer Max connect\0";
	int len = sizeof(sockaddr);

	while (1)
	{
		iLisRet = listen(m_SockServer, 0);// 进行监听
		m_Server[iConnect] = accept(m_SockServer, (sockaddr*)&serveraddrfrom, &len);// 同意建立连接
		if (m_Server[iConnect] != INVALID_SOCKET)
		{
			int ires = send(m_Server[iConnect], buf, sizeof(buf), 0);
			cout << " accept" << ires << endl;// 显示已经建立连接次数
			++iConnect;
			if (iConnect > iMaxConnect)
			{
				int ires = send(m_Server[iConnect], WarnBuf, sizeof(WarnBuf), 0);
			}
			else
			{
				HANDLE m_Handle;// 线程句柄
				DWORD nThreadId = 0;// 线程ID
				m_Handle = (HANDLE)::CreateThread(NULL, 0, threadpro, (LPVOID)m_Server[--iConnect], 0, &nThreadId);// 启动线程
			}
		}
		WSACleanup;
	}

	return 0;
}