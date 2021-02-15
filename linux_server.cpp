#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 100
const char* ADDRESS = "192.168.119.131";	//127.0.0.1
const int PORT = 10086;

int main()
{
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  			//每个字节都用0填充
    serv_addr.sin_family = AF_INET;  						//使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(ADDRESS);  	//具体的IP地址
    serv_addr.sin_port = htons(PORT);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in conn_addr;
    socklen_t conn_addr_size = sizeof(conn_addr);
    int conn_sock = accept(serv_sock, (struct sockaddr*)&conn_addr, &conn_addr_size);

	//接收客户端的数据
	char str[BUF_SIZE] = { 0 };	
	char* addr = inet_ntoa(conn_addr.sin_addr);
	int port = htons(conn_addr.sin_port);
	read(conn_sock, str, sizeof(str)-1);
    printf("Message from client [%s:%d]:\n%s\n", addr, port, str);
	
	// 回传客户端原样数据
	write(conn_sock, str, sizeof(str));
   
    //关闭套接字
    close(conn_sock);
    close(serv_sock);

    return 0;
}