// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GList.h"
#include "process.h"
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define CONN 0x01
#define BTNDOWN 0x02
#define GIVEUP 0x03
#define NETCLOSE 0x04


typedef struct
{
	int nFlag;
	int i;
	int j;
}strGOSoc;


soc_node head;
SOCKET server;
SOCKET g_client[] = {0};

void ServerProc(void *param);
void ClientProc(void *Param);

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA WSAData;
	int nRet = 0;

	nRet = WSAStartup(0x101,&WSAData);
	if(nRet != 0)
	{
		return 0;
	}
	List_Init(&head);
	if(_beginthread(ServerProc,0,NULL) == -1)
	{
		printf("thread create error");
	}

	printf("Server > \r\nPress 'q' to exit:\r\n");
	while (getchar() != 'q');
	closesocket(server);
	WSACleanup();
	List_Destroy(&head);

	return 0;
}

void ServerProc(void *param)
{
	int nLen = 0;
	int iClient = 0;
	sockaddr_in addr;
	sockaddr_in addr_client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons((u_short)20248);
	addr.sin_addr.s_addr = INADDR_ANY;

	server = socket(AF_INET,SOCK_STREAM,0);
	if(bind(server,(sockaddr*)&addr,sizeof(addr)) != 0)
	{
		return ;
	}
	if(listen(server,2) != 0)
	{
		return;
	}

	nLen = sizeof(addr_client);
	while (TRUE)
	{
		//g_client will be done in queue
		*(g_client + iClient)= accept(server,(sockaddr*)&addr_client,&nLen);
		if (*(g_client + iClient) == -1 )
		{
			continue;
		}

		_beginthread(ClientProc,0,(void*)*(g_client + iClient));	
		iClient++;
	}
}

void ClientProc(void *Param)
{
	int nError = 0;
	strGOSoc strsoc;
	SOCKET soc_vs;
	SOCKET client = (SOCKET)Param;

	List_Add(&head,client);
	send(client,"Connected...",strlen("Connected..."),0);
	//nError = WSAGetLastError();

	printf("%d : connected...\n",client);

	List_GetVS(&head,client,&soc_vs);
	if(soc_vs != NULL)
	{
		strsoc.nFlag = CONN;
		send(soc_vs,(char*)&strsoc,sizeof(strsoc),0);
	}

	while(TRUE)
	{
		strGOSoc soc;
		int nRet = recv(client,(char*)&soc,sizeof(soc),0);
		//Sleep(300);

		if(nRet <= 0)
			break;

		printf("receive %d : Flag:%d  i:%d  j:%d \n ",client,soc.nFlag,soc.i,soc.j);
		List_GetVS(&head,client,&soc_vs);
		if(soc_vs)
			send(soc_vs,(char*)&soc,sizeof(soc),0);
		
		if( NETCLOSE == soc.nFlag)
		{
			List_Del(&head,client);
			List_Del(&head,soc_vs);
		}

	}
}