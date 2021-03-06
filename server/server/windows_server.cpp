/*
	2019.06.30
	Socket通讯：Windows + Linux
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100
const char* ADDRESS = "192.168.119.1";	// 127.0.0.1
const int PORT = 10086;

using namespace std;

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
	sockaddr_in sockaddrConn;
	int size = sizeof(sockaddr_in);
	SOCKET socketConnect = accept(socketServer, (SOCKADDR*)&sockaddrConn, &size);
	char buffer[BUF_SIZE];									//缓冲区
	int strLen = recv(socketConnect, buffer, BUF_SIZE, 0);		//接收客户端发来的数据
	//buffer[strLen] = '\0';
	char* addrConn = inet_ntoa(sockaddrConn.sin_addr);
	int portConn = ntohs(sockaddrConn.sin_port);
	cout << "Message from client [" << addrConn << ":" << portConn << "]:\n" << buffer << endl;

	send(socketConnect, buffer, strLen, 0);					//将数据原样返回

	//关闭套接字
	closesocket(socketConnect);
	closesocket(socketServer);

	//终止 DLL 的使用
	WSACleanup();
	
	system("pause");
	return 0;
}