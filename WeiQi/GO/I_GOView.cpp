// I_GOView.cpp : implementation of the CI_GOView class
//

#include "stdafx.h"
#include "I_GO.h"

#include "I_GODoc.h"
#include "I_GOView.h"

#include "GOAPI.h"
#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void ServerPro(void* Param);
void RecvPro(void *Param,strGOSoc* soc);
/////////////////////////////////////////////////////////////////////////////
// CI_GOView

IMPLEMENT_DYNCREATE(CI_GOView, CView)

BEGIN_MESSAGE_MAP(CI_GOView, CView)
	//{{AFX_MSG_MAP(CI_GOView)
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_BUTTON_PASS,CI_GOView::GamePass)
	ON_COMMAND(ID_BUTTON_SETADDR,CI_GOView::GameSetAddr)
	ON_COMMAND(ID_BUTTON_START,CI_GOView::GameConn)
	ON_COMMAND(ID_BUTTON_EXIT,CI_GOView::GameExit)
	ON_COMMAND(ID_GAME_DM,CI_GOView::GameGetWinner)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_START,CI_GOView::OnStutusBtnUpdateStart)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SETADDR,CI_GOView::OnStutusBtnUpdateStop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CI_GOView construction/destruction

CI_GOView::CI_GOView()
{
	// TODO: add construction code here
	m_IcomBlk = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON_BLK));
	m_IcomWht = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON_WHT));

	memset(m_BLK,0x00,sizeof(Autom));
	memset(m_WHT,0x00,sizeof(Autom));
	m_StartPoint.x = 20;
	m_StartPoint.y = 20;
	m_Space = 30;
	m_Wideth = 18 * m_Space ;
	m_Hight = 18 * m_Space ;
	m_bBLK = TRUE;
	m_color = FALSE;
	m_bConn = FALSE;
	m_bEnable = FALSE;
	NetInit();

	m_SetAddrDlg = NULL;
//	strcpy(m_strAddr.GetBuffer(0),"127.0.0.1");
	m_strAddr = "127.0.0.1";
	//init draw line
	CPoint point = m_StartPoint;
	
	for (int i = 0;i < 19;i++)
	{//row
		for (int j = 0;j < 19;j++)
		{
			m_BLK[i][j].point.x = point.x + j * m_Space;
			m_BLK[i][j].point.y = point.y + i * m_Space;
			m_WHT[i][j].point.x = point.x + j * m_Space;
			m_WHT[i][j].point.y = point.y + i * m_Space;
			
			m_BLK[i][j].nType = DY_AUTOM_NULL;
			m_WHT[i][j].nType = DY_AUTOM_NULL;
		}
	}
}

CI_GOView::~CI_GOView()
{
	strGOSoc soc;

	soc.nFlag = NETCLOSE;
	soc.i = 0;
	soc.j = 0;
	
	NetSend(soc);
	NetClose();
}

void CI_GOView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType,cx,cy);
}

void CI_GOView::OnCreate(LPCREATESTRUCT lpcs)
{
	CView::OnCreate(lpcs);
}

BOOL CI_GOView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CI_GOView drawing

void CI_GOView::OnDraw(CDC* pDC)
{
	CI_GODoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	// double cache solve flash 
	//back picture
	CDC MemDC;
	CBitmap bm;
	CRect rect ;	
	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC); 
	bm.LoadBitmap(IDB_BITMAP2);

	MemDC.SelectObject(bm);  

	CPoint point = m_StartPoint;
	//draw cheese
	for (int i = 0;i < 19;i++)
	{//row
		for (int j = 0;j < 19;j++)
		{
			//black chess
			if (m_BLK[i][j].nType == DY_AUTOM_BLK)
			{
				MemDC.DrawIcon(m_BLK[i][j].point.x - m_Space/2 ,\
 					m_BLK[i][j].point.y - m_Space/2 ,m_IcomBlk);
			}
			//white chess
			if (m_WHT[i][j].nType == DY_AUTOM_WHT)
			{	
				MemDC.DrawIcon(m_WHT[i][j].point.x - m_Space/2 ,\
 					m_WHT[i][j].point.y - m_Space/2 ,m_IcomWht);
			}
		}
	}
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.DeleteDC();
	bm.DeleteObject();

	CView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CI_GOView printing

BOOL CI_GOView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CI_GOView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CI_GOView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CI_GOView diagnostics

#ifdef _DEBUG
void CI_GOView::AssertValid() const
{
	CView::AssertValid();
}

void CI_GOView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CI_GODoc* CI_GOView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CI_GODoc)));
	return (CI_GODoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CI_GOView message handlers
void CI_GOView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

void CI_GOView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bEnable && PtInRect(CRect(m_StartPoint.x - m_Space/3,m_StartPoint.y - m_Space/3,\
		m_StartPoint.x + m_Wideth +m_Space/3,m_StartPoint.y + m_Hight + m_Space/3),point))
	{
		for (int i = 0; i < 19 ; i++)
		{
			for(int j = 0 ;j < 19 ;j++)
			{
				if (PtInRect(CRect(m_BLK[i][j].point.x - m_Space/3,\
					m_BLK[i][j].point.y - m_Space/3,\
					m_BLK[i][j].point.x + m_Space/3,\
					m_BLK[i][j].point.y + m_Space/3),point))
				{// point is valid
					strGOSoc soc;
					
					soc.nFlag = BTNDOWN;
					soc.i = i;
					soc.j = j;

					LBtnDown(i,j);
					m_bEnable = FALSE;
					NetSend(soc);
					break;
				}
			}
		}
	}
	CView::OnLButtonDown(nFlags,point);
}

void CI_GOView::LBtnDown(int x,int y)
{
	int i = x;
	int j = y;
	
	InitChessFlag();
	if (m_BLK[i][j].nType == DY_AUTOM_NULL && \
		m_WHT[i][j].nType == DY_AUTOM_NULL)
	{// this area is empty,
		if (m_bBLK)
		{// black 
			m_BLK[i][j].nType = DY_AUTOM_BLK;
		}
		else
		{//white
			m_WHT[i][j].nType = DY_AUTOM_WHT;
		}
		// ti zi
		TiZi(i,j,!m_bBLK);

		if(IsHasLife(i,j,m_bBLK))
		{//so this step is valid

			if (m_bBLK)
			{// black 
			//	m_bBLK = FALSE;
				m_BLK[i][j].nType = DY_AUTOM_BLK;
			}
			else
			{//white
			//	m_bBLK = TRUE;
				m_WHT[i][j].nType = DY_AUTOM_WHT;
			}
			
			if(IsEnd())
			{
				AfxMessageBox("The End...");
			}
			InvalidateRect(CRect(m_BLK[i][j].point.x - m_Space,\
				m_BLK[i][j].point.y - m_Space,\
				m_BLK[i][j].point.x + m_Space,\
				m_BLK[i][j].point.y + m_Space),FALSE);
		}
		else
		{
			m_BLK[i][j].nType = DY_AUTOM_NULL;
			m_WHT[i][j].nType = DY_AUTOM_NULL;	
		}
	}
	

}

void CI_GOView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
}

void CI_GOView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
BOOL CI_GOView::IsEnd()
{
	int Sum = 0;

	for (int i = 0;i < 19;i++)
	{
		for (int j = 0;j < 19;j++)
		{
			if(m_BLK[i][j].nType == DY_AUTOM_BLK ||\
				m_WHT[i][j].nType == DY_AUTOM_WHT)
			{
				Sum ++;
				if(19 * 19 == Sum )
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

/* i and j is point.x,point.y;isBlk is the type will set on this point*/
BOOL CI_GOView::IsHasLife(int i,int j,BOOL isBlk)
{
	if (isBlk)
	{
		if (i < 0 || i > 18 || j < 0 || j > 18 )
		{
			return FALSE;
		} 
		else if (m_BLK[i][j].bCheck)
		{
			return FALSE;
		}
		else
		{
			m_BLK[i][j].bCheck = TRUE;
			if (m_BLK[i][j].nType == DY_AUTOM_BLK )
			{//black point
				if(IsHasLife( i, j - 1, isBlk)) return TRUE;
				if(IsHasLife( i, j + 1, isBlk)) return TRUE;
				if(IsHasLife( i - 1, j , isBlk)) return TRUE;
				if(IsHasLife( i + 1, j , isBlk)) return TRUE;
				return FALSE;
			}
			else if (m_WHT[i][j].nType == DY_AUTOM_WHT)
			{//white point
				return FALSE;
			}
			else 
			{
				return TRUE;
			}
		}
	}
	else
	{
		if (i < 0 || i > 18 || j < 0 || j > 18)
		{
			return FALSE;
		} 
		else if (m_WHT[i][j].bCheck)
		{
			return FALSE;
		}
		else
		{
			m_WHT[i][j].bCheck = TRUE;
			if (m_WHT[i][j].nType == DY_AUTOM_WHT && m_WHT[i][j].bCheck)
			{//white point
				if(IsHasLife( i, j - 1, isBlk)) return TRUE;
				if(IsHasLife( i, j + 1, isBlk)) return TRUE;
				if(IsHasLife( i - 1, j , isBlk)) return TRUE;
				if(IsHasLife( i + 1, j , isBlk)) return TRUE;
				return FALSE;
			}
			else if (m_BLK[i][j].nType == DY_AUTOM_BLK)
			{//black point
				return FALSE;
			}
			else 
			{
				return TRUE;
			}
		}
	}
}

void CI_GOView::InitChessFlag()
{
	for (int i = 0;i < 19;i++)
	{
		for (int j = 0;j < 19;j++)
		{
			m_BLK[i][j].bCheck = FALSE;
			m_WHT[i][j].bCheck = FALSE;
		}
	}
}

 /*i and j is point.x,point.y;isBlk is the type will be take off*/
void CI_GOView::TiZi(int i ,int j,BOOL isBlk)
{
	BOOL bUpdate = FALSE;

	if (i >= 0 && j >= 0 && i < 19 && j < 19)
	{//this point is TRUE
		if(i - 1 >= 0)
		{
			if(TiZi_SubPro(i - 1,j,isBlk))
			{
				bUpdate = TRUE;
			}
		}
		if (i + 1 < 19)
		{
			if(TiZi_SubPro(i + 1,j,isBlk))
			{
				bUpdate = TRUE;
			}
		}
		if (j - 1 >= 0)
		{
			if(TiZi_SubPro(i,j - 1,isBlk))
			{
				bUpdate = TRUE;
			}
		}
		if (j + 1 < 19)
		{
			if(TiZi_SubPro(i,j + 1,isBlk))
			{
				bUpdate = TRUE;
			}
		}
	}
	if (bUpdate)
	{
		Invalidate(FALSE);
	}
}

BOOL CI_GOView::TiZi_SubPro(int i ,int j,BOOL isBlk)
{
	if (i >= 0 && j >= 0 && i < 19 && j < 19)
	{
		InitChessFlag();
		if(!IsHasLife(i,j,isBlk))
		{// judge opponent whether has life or not
			//there is NO life
			//ti zi
			for (int i = 0;i < 19;i++)
			{
				for (int j = 0;j < 19;j++)
				{
					if (isBlk && m_BLK[i][j].bCheck)
					{
						m_BLK[i][j].nType = DY_AUTOM_NULL;
					}
					else if (!isBlk &&m_WHT[i][j].bCheck)
					{
						m_WHT[i][j].nType = DY_AUTOM_NULL;
					}
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

void CI_GOView::OnPaint()
{
	CView::OnPaint();
}

void CI_GOView::GamePass()
{
	if(m_bConn && m_bEnable)
	{
		strGOSoc soc;
		
		soc.nFlag = GIVEUP;
		soc.i = 0;
		soc.j = 0;

		m_bEnable = FALSE;
		NetSend(soc);
	}
}

void CI_GOView::GameConn()
{
	if(m_SetAddrDlg != NULL) 
	{
	//	AfxMessageBox("init setaddressdlg error\n");
	//	return;
		if(m_SetAddrDlg->m_strAddr.IsEmpty())
		{
			AfxMessageBox("Empty addr.\n");
			return;
		}
		else
		{
			strcpy(m_strAddr.GetBuffer(0),m_SetAddrDlg->m_strAddr);
		}
	}


	//init 
	for(int i = 0;i < 19;i++)
	{
		for(int j = 0; j < 19;j++)
		{
			m_BLK[i][j].nType = DY_AUTOM_NULL;
			m_WHT[i][j].nType = DY_AUTOM_NULL;
		}
	}

	Invalidate(TRUE);	
	if(NetConn(m_strAddr.GetBuffer(0)))
	{
		_beginthread(ServerPro,0,this);
		m_bConn = TRUE;
	}
	else
	{
		CString str;
		
		str.Format("connect error,maybe the addr is error");
		AfxMessageBox(str);
	}

}

void CI_GOView::GameSetAddr()
{
	
	if(m_SetAddrDlg == NULL)
	{
		m_SetAddrDlg = new CSetAddrDlg();
		m_SetAddrDlg->Create(IDD_DIALOG_ADDR);
		m_SetAddrDlg->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		m_SetAddrDlg->ShowWindow(SW_SHOWNORMAL);
	}

/*	int nRet = m_SetAddrDlg.DoModal();

	if(nRet == TRUE)
	{
		strcpy(m_strAddr.GetBuffer(0),m_SetAddrDlg.m_strAddr);
	}
*/
//	strcpy(m_strAddr.GetBuffer(0),m_SetAddrDlg->m_strAddr);
}

void CI_GOView::GameExit()
{
	GetParent()->PostMessage(WM_CLOSE);
}

void CI_GOView::OnStutusBtnUpdateStop(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(m_bStop);
}

void CI_GOView::OnStutusBtnUpdateStart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bConn);
}

BOOL CI_GOView::GameGetWinner()
{
	int nBLK = 0,nWHT = 0;
	
	for (int i = 0;i < 19;i++)
	{
		for (int j = 0;j < 19;j++)
		{
			if(m_BLK[i][j].nType == DY_AUTOM_BLK) nBLK++;
			else if (m_WHT[i][j].nType == DY_AUTOM_WHT)
			{
				nWHT++;
			}
		}
	}
	
	CString str;
	str.Format("Black : %d\nWhite : %d  ",nBLK,nWHT);
	AfxMessageBox(str);
	return TRUE;
}

void ServerPro(void * Param)
{
	while(1)
	{
		strGOSoc soc;
		int nRet = NetRecv(&soc);
		if(nRet <= 0)
		{
			continue;
		}
		RecvPro(Param,&soc);
	}
}

void RecvPro(void * Param,strGOSoc * soc)
{
	CI_GOView *myview = (CI_GOView*)Param;

	switch(soc->nFlag)
	{
	case CONN:
		{
			myview->m_bConn = TRUE;
			myview->m_bEnable = TRUE;
			myview->m_color = TRUE;
			myview->m_bBLK = TRUE;
			break;
		}

	case BTNDOWN:
		{
			myview->m_bConn = TRUE;
			myview->m_bEnable = TRUE;
		
			myview->m_bBLK = !myview->m_color;
			myview->LBtnDown(soc->i,soc->j);
			myview->m_bBLK = myview->m_color;
		}
		break;

	case GIVEUP:
		{
			myview->m_bEnable = TRUE;
			myview->m_bBLK = myview->m_color;
			break;
		}

	case NETCLOSE:
		//net break
		{
			CString str;

			str.Format("unconnected...\n");
			AfxMessageBox(str);	

			myview->m_bEnable = FALSE;
			myview->m_bConn = FALSE;
			myview->m_bBLK = FALSE;
			break;
		}

	default:
		break;
	}
}
