#include<iostream>
#include<WinSock2.h>
#include<string>
#include <WS2tcpip.h>

#pragma comment(lib,"Ws2_32.lib")

using namespace std;

int main()
{
	char IPdotdec[20];
	int port;
	scanf("%s%d", &IPdotdec, &port);

	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		cout << "WSAStartup failed" << endl;
		return -1;
	}
	SOCKET connectSocket;
	connectSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connectSocket == INVALID_SOCKET)
	{
		printf("Socket failed with error %d\n", WSAGetLastError());
		return -1;
	}

	
	struct in_addr ipaddr;
	inet_pton(AF_INET, IPdotdec, (void *)&ipaddr);

	sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = ipaddr;
	addr.sin_port = htons(port);

	connect(connectSocket, (sockaddr*)&addr, sizeof(addr));
	cout << "Connection established to remote Server at " << IPdotdec << ":" << port << endl;

	char message[256] = { 0 };
	cin.ignore();
	cin.getline(message, sizeof(message));

	int sendLength = send(connectSocket, message, strlen(message), 0);
	if (sendLength < 0)
	{
		printf("socket end error: %d\n", GetLastError());
		return -1;
	}
	cout << "  Sent " << sendLength << " bytes to the server: " << message << endl;
	char buf[256] = { 0 };
	int recvLength = recv(connectSocket, buf, sizeof(buf), 0);

	cout << "  Received " << recvLength << " bytes from the server: " << buf<< endl;

	cout << "  Shutdown the connection in 3 seconds¡­¡­" << endl;
	Sleep(3000);
	shutdown(connectSocket, SD_BOTH);
	closesocket(connectSocket);
	cout << "Connection is down." << endl;

	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("WSACleanup failed with error %d\n", WSAGetLastError());
		return -1;
	}

	return 0;


}