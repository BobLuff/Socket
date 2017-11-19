#include<iostream>
#include<WinSock2.h>
#include<string>
#include<cstdio>

using namespace std;


#pragma comment(lib,"Ws2_32.lib")
int main()
{
	int port;
	cin >> port;
	WSADATA data;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &data);  //0,表示初始化成功
	string text = "Hello,World!";

	if (err != 0)
	{
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}

	SOCKET connectSocket, acceptSocket;
	connectSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connectSocket == INVALID_SOCKET)
	{
		printf("Socket failed with error %d\n", WSAGetLastError());
		return -1;
	}


	sockaddr_in serverAddr, clientAddr;
	int n = sizeof(clientAddr);  //获取套接字地址结构大小
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);
	bind(connectSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));  //绑定套接字
	listen(connectSocket, 10);   //最大值为128，需根据实际情况来测试可同时连接多少个客户端

	char name[256];
	gethostname(name, sizeof(name));
	hostent *serverHost = gethostbyname(name);
	in_addr addr;
	addr.S_un.S_addr = *(u_long *)serverHost->h_addr_list[0];
	cout << "EchoServer is listening on " << inet_ntoa(addr) << ":" << port << endl;

	char buf[256];
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		cout << "Waiting for a connection......." << endl;
		acceptSocket = accept(connectSocket, (sockaddr*)&clientAddr, &n);
		addr = clientAddr.sin_addr;
		cout << "Accepted connection from " << inet_ntoa(addr) << endl;
		int recvLength = recv(acceptSocket, buf, sizeof(buf), 0);
		cout << "  Received " << recvLength << " bytes from the client： " << buf << endl;
		char message[256] = { 0 };
		cin.ignore();
		cin.getline(message, sizeof(message));
		int sendLength = send(acceptSocket, message, strlen(message), 0);

		if (sendLength < 0)
		{
			printf("socket end error: %d\n", GetLastError());
			return -1;
		}
		cout << "  Sent " << sendLength << " bytes back to the client: " << message << endl;
		cout << "Connection closed by the client" << endl;
	}

	shutdown(acceptSocket, SD_BOTH);
	closesocket(acceptSocket);
	shutdown(connectSocket, SD_BOTH);
	closesocket(connectSocket);
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("WSACleanup failed with error %d\n", WSAGetLastError());
		return -1;
	}

	return 0;

}