
// RaspCamDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "RaspCam.h"
#include "RaspCamDlg.h"
#include "afxdialogex.h"
#include <stdio.h>  
#include <WinSock2.h>  
#include "process.h"
#include <atlimage.h>
  
#pragma comment(lib, "ws2_32.lib")  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


///////////////////////////////////////////  
#define PORT 8080
#define BUFFER_1M   1024 * 1024 
#define MSG_CLOSE 1
int g_nFrame = 0;
char framebuf[BUFFER_1M] = {'\0'};
char g_frame[BUFFER_1M] = {'\0'};
char tmp[BUFFER_1M] = {'\0'};
int nEvent[20];

DWORD WINAPI ThreadProc(LPVOID lpParam);
int soc_init(const char *strIP,char* ssochead);
SOCKET soc_connect(const char *strIP);
int soc_send(SOCKET socket, const char *pbuffer, unsigned int nlen);
int soc_recv(SOCKET sock,char* strIP);
int soc_close(SOCKET soc);
void ReplaceAllchar(char* s,char c1,char c2);
///////////////////////////////////////////


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRaspCamDlg 对话框




CRaspCamDlg::CRaspCamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRaspCamDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRaspCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_BtnAdd);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_BtnDel);
	DDX_Control(pDX, IDC_BUTTON_SHOW, m_BtnShow);
	DDX_Control(pDX, IDCANCEL, m_BtnConcel);
	DDX_Control(pDX, IDC_LIST_IP, m_ListIP);
	DDX_Control(pDX, IDC_BUTTON_CONN, m_BtnConn);
}

BEGIN_MESSAGE_MAP(CRaspCamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CRaspCamDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CONN, &CRaspCamDlg::OnBnClickedButtonConn)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_IP, &CRaspCamDlg::OnNMCustomdrawListIp)
	ON_NOTIFY(HDN_ITEMCHANGED, 0, &CRaspCamDlg::OnHdnItemchangedListIp)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CRaspCamDlg::OnBnClickedButtonShow)
END_MESSAGE_MAP()


// CRaspCamDlg 消息处理程序

BOOL CRaspCamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetClientRect(m_videoRect);
	m_videoRect.bottom -= 240;
	m_videoRect.right -= 10;

	InitList();
	// show video 
	for(int i = 0; i < 10; i++)
	{
		nEvent[i] = i + 1;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//////////////////////////////////////////////////////
void CRaspCamDlg::InitList()
{
	m_ListIP.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	LONG lStyle;
	lStyle = GetWindowLong(m_ListIP.m_hWnd,GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_ListIP.m_hWnd,GWL_STYLE ,lStyle |LVS_SHOWSELALWAYS);

	//read ini file

	m_ListIP.InsertColumn(0,L"序号",LVCFMT_CENTER,80);
	m_ListIP.InsertColumn(1,L"IP",LVCFMT_CENTER,200);
	m_ListIP.InsertColumn(2,L"状态",LVCFMT_CENTER,60);
	m_ListIP.InsertColumn(3,L"备注",LVCFMT_CENTER,200);
	// add List
	m_ListIP.InsertItem(0,L"");
	m_ListIP.SetItemText(0,0,L"1");
	m_ListIP.SetItemText(0,1,L"192.168.1.101");
	m_ListIP.SetItemText(0,2,L"未启用");
	m_ListIP.SetItemText(0,3,L"展厅1");

	m_ListIP.InsertItem(1,L"");
	m_ListIP.SetItemText(1,0,L"2");
	m_ListIP.SetItemText(1,1,L"192.168.1.102");
	m_ListIP.SetItemText(1,2,L"未启用");
	m_ListIP.SetItemText(1,3,L"展厅2");
}
//////////////////////////////////////////////////////
void CRaspCamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRaspCamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// double buffer draw background
		CPaintDC dc(this);
		CRect rc;
		CDC dcMem;
	//	GetClientRect(&rc);
		rc = m_videoRect;
		CBitmap bmp; //内存中承载临时图象的位图

		dcMem.CreateCompatibleDC(&dc); //依附窗口DC创建兼容内存DC
		//创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
		bmp.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
		CBitmap *pOldBit=dcMem.SelectObject(&bmp);
		//按原来背景填充客户区，不然会是黑色
		//dcMem.FillSolidRect(rc,dcMem.GetBkColor());
		//画图，添加你要画图的代码，不过用dcMem画，而不是pDC；
		//DrawBK(&dcMem);
		DrawImage(&dcMem);
		
		dc.BitBlt(10,10,rc.Width() - 10,rc.Height() - 10 ,&dcMem,0,0,SRCCOPY);
		//将内存DC上的图象拷贝到前台
		//绘图完成后的清理
		dcMem.DeleteDC();     //删除DC
		bmp.DeleteObject(); //删除位图

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRaspCamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRaspCamDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CRaspCamDlg::DrawImage(CDC *dcMem)
{
	if(g_nFrame > 0 && strlen(g_frame) > 0)
		{
			try
			{
				COleStreamFile osf;
				osf.CreateMemoryStream(NULL);
				osf.Write(g_frame,g_nFrame);
				osf.SeekToBegin();
				CImage img;
				img.Load(osf.GetStream());
				dcMem->SetStretchBltMode(COLORONCOLOR);// 解决图像失真问题
				if(!img.IsNull())
					img.Draw(dcMem->GetSafeHdc(),m_videoRect);
				osf.Close();
			}
			catch(...)
			{
			}

		}
	
}
	
void CRaspCamDlg::OnBnClickedButtonConn()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_ListIP.GetFirstSelectedItemPosition();
	int nIndex = m_ListIP.GetNextSelectedItem(pos);

	CString strIP = m_ListIP.GetItemText(nIndex,1);
	CString strState = m_ListIP.GetItemText(nIndex,2);
	if(strIP.IsEmpty())
	{
		return ;
	}
	if(strState.Compare(L"未启用") == 0)
	{
		USES_CONVERSION;
		static char pIP[50];
		memcpy(pIP,T2A(strIP),strlen(T2A(strIP)));
		HANDLE pthread = CreateThread(NULL,0,ThreadProc,(LPVOID)pIP,0,NULL);
		if(pthread == NULL)
		{
			printf("Create thread failed....");  
		}
		else
		{
			m_ListIP.SetItemText(nIndex,2,L"监控中...");
			m_ListIP.SetItemData(nIndex,(DWORD_PTR)pthread);
			SetTimer(nEvent[nIndex],200,NULL); // 刷的太快也会闪，系统资源占用大多导致
		}
	}
	else
	{
		//stop 
		HANDLE pthd = (HANDLE)m_ListIP.GetItemData(nIndex);
		//PostThreadMessage((DWORD)pthd,MSG_CLOSE,0,0); // sometimes this message can't succcess
		PostMessage((UINT)pthd,MSG_CLOSE,0);
		m_ListIP.SetItemText(nIndex,2,L"未启用");
		//Sleep(1000);
		KillTimer(nEvent[nIndex]);
	}
	m_ListIP.SetFocus();
}


int soc_init(const char *strIP,char* ssochead)
{
	WORD wVersionRequested = MAKEWORD(1, 1);  
    WSADATA wsaData;  
	
	// write HTTP head 
    // HTPP head maybe has multiline，every line should be end with \r\n,and the end of head must be \r\n; 
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
int soc_recv(SOCKET sock,char* strIP)
{ 
    int n_buf_len = BUFFER_1M;  

	FILE *file = NULL;
	char fname[20];

	strcpy(fname,strIP);
	ReplaceAllchar(fname,'.','-');
	strcat(fname,".mjpg");
	file = fopen(fname,"wb+");	
	int nframelen = 0;	
	bool bhead = false;
	bool bend = false;
	char* bFFD8 = NULL;
	char* bFFD9 = NULL;

	int begin = 0;
	int end = 0;

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
			int nLen = 0;
			nLen= ::recv(sock, framebuf, n_buf_len, 0);  
				
			if(nLen > 0)
			{
				//save frame
				fwrite(framebuf,1,nLen,file);
				// get jpg frame
				if((nframelen + nLen ) >= BUFFER_1M)
				{
					if(bhead)
					{
						bhead = false;
						bend = false;
						//g_nFrame = nframelen;
						//memset(g_frame,0x0,BUFFER_1M);
						//memcpy(g_frame,tmp + begin,g_nFrame + 1);
					//	memset(tmp,0x0,BUFFER_1M);
						//tmp[1] = '\0';
						end = begin = 0;
						nframelen = 0;
					}
					else
					{
						nframelen = 0;
						end = begin = 0;
					}
				}
				else
				{
					memcpy(tmp + nframelen,framebuf,nLen);// overflow
					nframelen += nLen;
				}
				// is a jpg frame ?
	
			
				if(!bhead && strlen(tmp) > 1)
				{
					char* eFFD8 = tmp + 1;
					do
					{
						//memchr() 在内存中查找指定字节
						eFFD8 = (char *) memchr(eFFD8 + 1,0xd8,nframelen - (eFFD8 - tmp + 1));
						if(eFFD8 != NULL)
						{
							char* bFFD8 = (char *) memchr(eFFD8 - 1,0xff,1);
							if(bFFD8 != NULL)
							{
								bhead = true;
								begin = bFFD8 - tmp;
								break;
							}
						}
					}while(eFFD8 != NULL);
				}
				if(!bend && strlen(tmp) > 1)
				{
					char* eFFD9 = tmp + 1;
					do
					{
						eFFD9 = (char *) memchr(eFFD9 + 1,0xd9,nframelen - (eFFD9 - tmp + 1));
						if(eFFD9 != NULL)
						{
							char* bFFD9 = (char *) memchr(eFFD9 - 1,0xff,1);
							if(bFFD9 != NULL)
							{
								bend = true;
								end = bFFD9 - tmp;
								break;
							}
						}
					}while(eFFD9 != NULL);
				}
				if(bhead && bend )
				{
					if( end > begin)
					{
						bhead = false;
						bend = false;
						g_nFrame = end - begin;
						memset(g_frame,0x0,BUFFER_1M);
						memcpy(g_frame,tmp + begin,g_nFrame + 1);
						memset(tmp,0x0,BUFFER_1M);
						//tmp[1] = '\0';
						end = begin = 0;
						nframelen = 0;
					}
					else if(end <= begin)
					{
					//	end = begin = 0;
						
						g_nFrame = 0;
						memcpy(tmp,tmp + begin,begin);
						memset(g_frame,0x0,BUFFER_1M);
						end = begin + 1;
						nframelen = 0;
					//	bhead = false;
						bend = false;
					}
				}

			}
        }  
		MSG msg;
		
		if(PeekMessage(&msg,0,0,0,0))
			break;
	  
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
	soc_recv(sock,strIP);
	//close
	soc_close(sock);
}

///////////////////////////////////////////

void CRaspCamDlg::OnNMCustomdrawListIp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(pNMHDR->idFrom == IDC_LIST_IP)
	{
		NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
		if( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;
		}
		else if(CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
		{
			int nItem = pLVCD->nmcd.dwItemSpec;
	
			CString str = m_ListIP.GetItemText(nItem,2);
			if(str == L"未启用")
			{
				pLVCD->clrTextBk = RGB(255,0,0);
			}
			else
			{
				pLVCD->clrTextBk = RGB(0,100,0);
			}
			pResult = CDRF_DODEFAULT;
			return ;
		}
	}
	*pResult = 0;
}


void CRaspCamDlg::OnHdnItemchangedListIp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	*pResult = 0;
}


void CRaspCamDlg::OnBnClickedButtonShow()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_ListIP.GetFirstSelectedItemPosition();
	int nIndex = m_ListIP.GetNextSelectedItem(pos);

	CString strIP = m_ListIP.GetItemText(nIndex,1);
	CString strState = m_ListIP.GetItemText(nIndex,2);
	if(strIP.IsEmpty())
	{
		return ;
	}
}

////////////////////////////////////////
void CRaspCamDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	InvalidateRect(m_videoRect,false);
}

///////////////////////////////////////
BOOL CRaspCamDlg::OnEraseBkgnd(CDC* pDC)
{
	//return CDialog::OnEraseBkgnd(pDC);
	return false;
}

void ReplaceAllchar(char* s,char c1,char c2)
{
	char* ps = s;
	if(ps == NULL)
	{
		return ;
	}
	while(*ps != '\0')
	{
		if(*ps == '.')
			*ps = '-';
		ps++;
	}
}