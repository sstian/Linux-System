#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
const char* ADDRESS = "192.168.119.1";	// 127.0.0.1
const int PORT = 10086;

int main()
{
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  		//每个字节都用0填充
    serv_addr.sin_family = AF_INET;  					//使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(ADDRESS);  	//具体的IP地址
    serv_addr.sin_port = htons(PORT);  					//端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    // 向服务端发送数据
	char buffer[BUF_SIZE];
	printf("Input a string: \n");
	scanf("%s", buffer);
    write(sock, buffer, sizeof(buffer)); 
    
    //读取服务器传回的数据
    read(sock, buffer, sizeof(buffer)-1);
    printf("Message from server [%s:%d]:\n%s\n", ADDRESS, PORT, buffer);
   
    //关闭套接字
    close(sock);

    return 0;
}