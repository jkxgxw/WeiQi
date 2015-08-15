
#include "stdafx.h"
#include <stdio.h>  
#include <WinSock2.h>  
#include "process.h"

#pragma once

#pragma comment(lib, "ws2_32.lib")  

///////////////////////////////////////////  

DWORD WINAPI ThreadProc(LPVOID lpParam);
int soc_init(const char *strIP,char* ssochead);
SOCKET soc_connect(const char *strIP);
int soc_send(SOCKET socket, const char *pbuffer, unsigned int nlen);
int soc_recv(SOCKET sock);
int soc_close(SOCKET soc);
int RaspCam(char* strIP) ;
///////////////////////////////////////////
