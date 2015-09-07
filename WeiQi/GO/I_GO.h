// I_GO.h : main header file for the I_GO application
//

#if !defined(AFX_I_GO_H__DCD72B51_0F2A_4C1D_8AB3_1187EE2D7F35__INCLUDED_)
#define AFX_I_GO_H__DCD72B51_0F2A_4C1D_8AB3_1187EE2D7F35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CI_GOApp:
// See I_GO.cpp for the implementation of this class
//

class CI_GOApp : public CWinApp
{
public:
	CI_GOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CI_GOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CI_GOApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_I_GO_H__DCD72B51_0F2A_4C1D_8AB3_1187EE2D7F35__INCLUDED_)
