
#include "winsock2.h"
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

/***********************************/
//void NetSetAddr(sockaddr *addr);
bool NetInit();
bool NetConn(char* strAddr);//sockaddr *addr = NULL);
void NetSend(strGOSoc soc);
int NetRecv(strGOSoc *soc);
void NetClose();

