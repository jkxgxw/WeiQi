
#include "stdafx.h"

#include "rcv.h"
#include <stdio.h>  

#define PORT 8080
#define BUFFER_1M   1024 * 1024

char preceive[BUFFER_1M] = {'\0'};


int soc_init(const char *strIP,char* ssochead)
{
	WORD wVersionRequested = MAKEWORD(1, 1);  
    WSADATA wsaData;  
	
	// write HTTP head 
    // HTPP head maybe has multiline£¬every line should be end with \r\n,and the end of head must be \r\n; 
    strcat(ssochead, "GET /?action=stream HTTP/1.1\r\n");  
    strcat(ssochead, "Host: ");
	strcat(ssochead,strIP);
	strcat(ssochead,":8080\r\n");  
    strcat(ssochead, "Connection: keep-alive\r\n");  
    strcat(ssochead, "Accept: */*\r\n");  
    strcat(ssochead, "\r\n");  
  
    int err = ::WSAStartup(wVersionRequested, &wsaData);  
    if ( 0 != err )  
    {  
        printf("[connectAndSendData]: WSAStartup failed. return %d. \r\n", err);  
        return -1;  
    }  
  
    if ( wsaData.wVersion != wVersionRequested )  
    {  
        printf("[connectAndSendData]: wsaData.wVersion %d is not equal to wVersionRequested %d.\r\n", wsaData.wVersion, wVersionRequested);  
        ::WSACleanup();  
        return -2;  
    }  
	return 0;
}

///////////////////////////////////////////
SOCKET soc_connect(const char *strIP)
{
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if ( INVALID_SOCKET == sock )  
    {  
        printf("[connectAndSendData]: socket error %d. \r\n", WSAGetLastError());  
        return NULL;  
    }  
    struct hostent *p_hostent = gethostbyname(strIP);  
    if( NULL == p_hostent )  
    {  
        printf("[gethostbyname]: socket error %d. \r\n", WSAGetLastError());  
        ::closesocket(sock);  
        ::WSACleanup();  
        return NULL;  
    }  
  
    SOCKADDR_IN addr_server;  
    addr_server.sin_family  = AF_INET;  
    addr_server.sin_addr    = *((struct in_addr*)p_hostent->h_addr);  
    memset(addr_server.sin_zero, 0, 8);  
    addr_server.sin_port    = htons(PORT);  
  
    int err = ::connect(sock, (SOCKADDR*)&addr_server, sizeof(addr_server));  
    if ( SOCKET_ERROR == err )  
    {  
        printf("[connectAndSendData]: connect %s:%d error %d. \r\n", strIP, PORT, WSAGetLastError());  
        ::closesocket(sock);  
        ::WSACleanup();  
        return NULL;  
    }  
	return sock;  
}

///////////////////////////////////////////
int soc_send(SOCKET socket,const char *pbuffer, unsigned int nlen)
{ 
	int  err = ::send(socket, pbuffer, nlen, 0);  
    if ( SOCKET_ERROR == err )  
    {  
        printf("[connectAndSendData]: send error %d. \r\n", WSAGetLastError()); 
		return -1;
    }
	return 0;
}

///////////////////////////////////////////
int soc_recv(SOCKET sock)
{ 
    int n_buf_len = BUFFER_1M;  

	FILE *file = NULL;
	file = fopen("a","wb+");	
	
    while (1)  
    {  
        fd_set fds;  
        FD_ZERO(&fds);  
        FD_SET(sock, &fds);  
        struct timeval timeo;  
        timeo.tv_sec = 10;  
        timeo.tv_usec = 1000;  

        int ret = select(sock, &fds, NULL, NULL, &timeo);  
        if (ret <= 0)  
            break;  
  
        if (FD_ISSET(sock, &fds))  
        {  
			int  nLen= ::recv(sock, preceive, n_buf_len, 0);  
			
			fwrite(preceive,1,nLen,file);
        }  
    }  
	fclose(file);	
	return 0;
}  
 
///////////////////////////////////////////
int soc_close(SOCKET soc)
{
    int err = ::closesocket(soc);  
    if ( SOCKET_ERROR == err )  
    {  
        printf("[connectAndSendData]: closesocket error %d. \r\n", WSAGetLastError());  
		return -1;
    }  
    ::WSACleanup();
	return 0;
}

///////////////////////////////////////////
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	char ssochead[1024];  
    ssochead[0] = '\0';  
	char receive_buff[102400];  
    unsigned n_receive_len = 102400;  
    receive_buff[0] = '\0';
	char* strIP = (char*)lpParam;

	//init socket
	if(soc_init(strIP,ssochead) != 0)
	{
		return -1;
	}
	//connect
	SOCKET sock = soc_connect(strIP);
	if(sock == NULL)
	{
		return -1;
	}
	//send HTTP head
	int nret = soc_send(sock,ssochead,strlen(ssochead));
	if(nret < 0)
	{
		return -2;
	}
	// recv
	soc_recv(sock);
	//close
	soc_close(sock);
}

///////////////////////////////////////////
int RaspCam(char* strIP)  
{  
	//input IPaddress

	//new thread
	HANDLE pthread = CreateThread(NULL,0,ThreadProc,(void*)strIP,0,NULL);
	if(pthread == NULL)
	{
		printf("Create thread failed....");  
	}
    printf("Data collecting , press any key to exit.....");  

    getchar();  
    return 0;  
}  
 
