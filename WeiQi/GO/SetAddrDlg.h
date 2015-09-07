#if !defined(AFX_SETADDRDLG_H__83606ECE_A316_4163_8F52_0642820F77E7__INCLUDED_)
#define AFX_SETADDRDLG_H__83606ECE_A316_4163_8F52_0642820F77E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetAddrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetAddrDlg dialog

class CSetAddrDlg : public CDialog
{
// Construction
public:
	CSetAddrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetAddrDlg)
	enum { IDD = IDD_DIALOG_ADDR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	CIPAddressCtrl *m_pipaddr;
	CString m_strAddr;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetAddrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetAddrDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETADDRDLG_H__83606ECE_A316_4163_8F52_0642820F77E7__INCLUDED_)
