#include<WinSock2.h>
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

#pragma comment(lib,"WS2_32.lib")

int main()
{
	WSADATA data;
	WORD w = MAKEWORD(2, 0);
	char sztext[] = "��ӭ��\r\n";
	
	::WSAStartup(w, &data);
	SOCKET s, s1;
	s = ::socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr, addr2;
	int n = sizeof(addr2);
	addr.sin_family = AF_INET; //ָ����ַ��ʽ

	addr.sin_port = htons(75);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(s, (sockaddr*)&addr, sizeof(addr));
	::listen(s, 5);
	printf("�������Ѿ�����\r\n");

	while (true)
	{
		s1 = ::accept(s, (sockaddr*)&addr2, &n);
		if (s1 != NULL)
		{
			printf("%s�Ѿ�������\r\n", inet_ntoa(addr2.sin_addr));  //inet_ntoa �������ֽ�˳��ת��Ϊ�ַ���IP��ַ����ӡ����
			::send(s1, sztext, sizeof(sztext), 0);
		}
		::closesocket(s);
		::closesocket(s1);
		::WSACleanup();
		if (getchar())
		{
			return 0;
		}
		else
		{
			::Sleep(100);
		}
	}

}