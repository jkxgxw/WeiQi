// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "process.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")

SOCKET Server;

void ServerPro(void* param);

int _tmain(int argc, _TCHAR* argv[])
{
	WSAData wdata;

	if(WSAStartup(0x101,&wdata) != 0)
	{
		return 0;
	}

	_beginthread(ServerPro,0,NULL);
	printf("Client >\r\nPress 'q' exit:\n");
	while(getchar() != 'q');
	
	closesocket(Server);
	WSACleanup();
	return 0;
}

void ServerPro(void* param)
{
	char buf[512];
	int nEnd = 0;
	int iIndex = 0;
	int nBind;
	sockaddr_in addr;
	addr.sin_family = AF_INET;//TCP/IP
	addr.sin_port = htons((u_short)20248);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");


	Server = socket(AF_INET,SOCK_STREAM,0);

	if (connect(Server,(sockaddr*)&addr,sizeof(addr)) != 0)
	{
		closesocket(Server);
		return;
	}
	nEnd = recv(Server,buf,512,0);
	buf[nEnd] = 0;
	printf("recv : %s \n",buf);
	//nEnd = WSAGetLastError();
	send(Server,"hi",strlen("hi"),0);
	nEnd = recv(Server,buf,512,0);
	buf[nEnd] = 0;
	printf("recv : %s \n",buf);
	closesocket(Server);
}