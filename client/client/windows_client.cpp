#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100
const char* ADDRESS = "192.168.119.131";	// 127.0.0.1
const int PORT = 10086;

using namespace std;

int main() 
{
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//向服务器发起请求
	sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));			//每个字节都用0填充
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(ADDRESS);	
	sockaddr.sin_port = htons(PORT);
	connect(sock, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));

	//获取用户输入的字符串并发送给服务器
	char bufSend[BUF_SIZE] = { 0 };
	cout << "Input a string: \n";
	cin >> bufSend;
	send(sock, bufSend, (int)strlen(bufSend), 0);

	//接收服务器传回的数据
	char bufRecv[BUF_SIZE] = { 0 };
	recv(sock, bufRecv, BUF_SIZE, 0);

	//输出接收到的数据
	cout << "Message from server [" << ADDRESS << ":" << PORT << "]:\n" << bufRecv << endl;

	//关闭套接字
	closesocket(sock);

	//终止使用 DLL
	WSACleanup();

	system("pause");
	return 0;
}