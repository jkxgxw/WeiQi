
#include "StdAfx.h"
#include "GOAPI.h"

SOCKET g_server;

bool NetInit()
{	
	WSAData wdata;

	if(WSAStartup(0x101,&wdata) != 0)
	{
		return 0;
	}
	return 1;
}

void NetClose()
{
	if(g_server != NULL)
		closesocket(g_server);
	WSACleanup();
}
bool NetConn(char* strAddr)
{
	char buf[512];
	int nEnd = 0;
	int iIndex = 0;
	sockaddr_in addr;
	addr.sin_family = AF_INET;//TCP/IP
	addr.sin_port = htons((u_short)20248);
	addr.sin_addr.s_addr = inet_addr(strAddr);//gxw 


	g_server = socket(AF_INET,SOCK_STREAM,0);

	if (connect(g_server,(sockaddr*)&addr,sizeof(addr)) != 0)
	{
		closesocket(g_server);
		return false;
	}
	nEnd = recv(g_server,buf,512,0);
	buf[nEnd] = 0;
	printf("recv : %s \n",buf);

	return true;
}


void NetSend(strGOSoc soc)
{
	send(g_server,(char*)&soc,sizeof(strGOSoc),0);
}


int NetRecv(strGOSoc *soc)
{
	int nRet = recv(g_server,(char*)soc,sizeof(strGOSoc),0);
	return nRet;
}
