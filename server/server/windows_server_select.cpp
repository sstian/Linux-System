/*
	2019.06.30
	Socket通讯：Windows + Linux，
	select多路IO复用模型,存在一只不停地接收问题？
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100
const char* ADDRESS = "127.0.0.1";	// 192.168.119.1
const int PORT = 10086;

using namespace std;

fd_set g_fd = { 0 };	// 总集
void Close(SOCKET& sock)
{
	for (int i = 0; i < (int)g_fd.fd_count; i++)
	{
		if (g_fd.fd_array[i] == sock)
		{
			if (g_fd.fd_count != i + 1)
				memcpy(g_fd.fd_array + i, g_fd.fd_array + i + 1, sizeof(SOCKET)*g_fd.fd_count - i - 1);
			g_fd.fd_count--;
			break;
		}
	}
	closesocket(sock);
}

void Accept(SOCKET& sock)
{
	sockaddr_in sockaddrConn;
	int size = sizeof(sockaddr_in);
	SOCKET socketConnect = accept(g_fd.fd_array[0], (SOCKADDR*)&sockaddrConn, &size);
	g_fd.fd_array[g_fd.fd_count++] = socketConnect;

	char* addrConn = inet_ntoa(sockaddrConn.sin_addr);
	int portConn = ntohs(sockaddrConn.sin_port);
	cout << addrConn << ":" << portConn << "登录：" << endl;
}

void Receive(SOCKET& sock)
{
	char buffer[BUF_SIZE];								//缓冲区
	int strLen = recv(sock, buffer, BUF_SIZE, 0);		//接收客户端发来的数据
	buffer[strLen] = '\0';
	//if (strLen < 0)
	//	Close(sock);

	sockaddr_in sockaddrConn;
	int size = sizeof(sockaddr_in);
	getpeername(sock, (SOCKADDR*)& sockaddrConn, &size);
	char* addrConn = inet_ntoa(sockaddrConn.sin_addr);
	int portConn = ntohs(sockaddrConn.sin_port);
	cout << "Message from client [" << addrConn << ":" << portConn << "]:\n" << buffer << endl;

	send(sock, buffer, strLen, 0);					//将数据原样返回

}


void TheProc(fd_set& fdset)
{
	// 轮询
	for (int index = 0; index < (int)fdset.fd_count; index++)
	{
		SOCKET& sock = fdset.fd_array[index];
		if (sock == g_fd.fd_array[0])
			Accept(sock);		// 监听SOCKET
		else
			Receive(sock);		// 接收消息
	}
}
int main() 
{
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);

	//绑定套接字
	sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));			//每个字节都用0填充
	sockaddr.sin_family = AF_INET;					//使用IPv4地址
	sockaddr.sin_addr.s_addr = inet_addr(ADDRESS);  //具体的IP地址
	sockaddr.sin_port = htons(PORT);				//端口
	bind(socketServer, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));

	//进入监听状态
	listen(socketServer, SOMAXCONN);

	//接收客户端请求
	g_fd.fd_array[g_fd.fd_count++] = socketServer;
	while (true)
	{
		fd_set fdset = g_fd;
		timeval tv = { 0, 256 };
		int n = 0;
		n = select(0, &fdset, NULL, NULL, &tv);
		if (!n)
			continue;
		if(fdset.fd_count > 0)
			TheProc(fdset);

	}


	//关闭套接字
	closesocket(socketServer);

	//终止 DLL 的使用
	WSACleanup();
	
	system("pause");
	return 0;
}

/**
#define FD_SETSIZE      64
typedef struct fd_set {
	u_int fd_count;					// how many are SET?
	SOCKET  fd_array[FD_SETSIZE];   // an array of SOCKETs
} fd_set;
struct timeval {
		long    tv_sec;			// seconds
		long    tv_usec;				// and microseconds
};

int WSAAPI select(
	_In_ int nfds,
	_Inout_opt_ fd_set FAR * readfds,
	_Inout_opt_ fd_set FAR * writefds,
	_Inout_opt_ fd_set FAR * exceptfds,
	_In_opt_ const struct timeval FAR * timeout
	);

**/