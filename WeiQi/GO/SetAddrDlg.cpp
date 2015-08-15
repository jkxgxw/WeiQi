// SetAddrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "i_go.h"
#include "SetAddrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetAddrDlg dialog


CSetAddrDlg::CSetAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetAddrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetAddrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetAddrDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetAddrDlg, CDialog)
	//{{AFX_MSG_MAP(CSetAddrDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetAddrDlg message handlers
BOOL CSetAddrDlg::OnInitDialog()
{
	m_pipaddr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1);    
	m_pipaddr->SetAddress(BYTE(127),BYTE(0),BYTE(0),BYTE(1));
	m_pipaddr->SetFocus();
	return true;
}

void CSetAddrDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText(IDC_IPADDRESS1,m_strAddr);
	CDialog::OnOK();
}

void CSetAddrDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
