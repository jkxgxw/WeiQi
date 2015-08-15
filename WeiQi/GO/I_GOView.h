// I_GOView.h : interface of the CI_GOView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_I_GOVIEW_H__EBF81F81_2D8E_43F9_8779_50F2E544DABE__INCLUDED_)
#define AFX_I_GOVIEW_H__EBF81F81_2D8E_43F9_8779_50F2E544DABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SetAddrDlg.h"

typedef struct 
{
	CPoint point;
	int nType;
	BOOL bCheck;
} Autom,*pAutom;


class CI_GOView : public CView
{
protected: // create from serialization only
	CI_GOView();
	DECLARE_DYNCREATE(CI_GOView)

// Attributes
public:
	CI_GODoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CI_GOView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPaint();

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CI_GOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CI_GOView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


protected:
	Autom m_BLK[19][19] ;
	Autom m_WHT[19][19] ;
	CPoint m_StartPoint;
	int m_Space;
	int m_Wideth;
	int m_Hight;

	HICON m_IcomBlk;
	HICON m_IcomWht;
	CSetAddrDlg *m_SetAddrDlg;
	CString m_strAddr;
	
public:
	BOOL m_bBLK;
	BOOL m_color;
	BOOL m_bConn;
	BOOL m_bEnable;
public:
	BOOL IsEnd();
	BOOL IsHasLife(int i,int j,BOOL isBlk);
	void InitChessFlag();
	void TiZi(int i ,int j,BOOL isBlk);
	BOOL TiZi_SubPro(int i ,int j,BOOL isBlk);
	void GamePass();
	void GameConn();
	void GameSetAddr();
	void GameExit();
	BOOL GameGetWinner();
	void OnStutusBtnUpdateStart(CCmdUI *pCmdUI);
	void OnStutusBtnUpdateStop(CCmdUI *pCmdUI);
	void LBtnDown(int x,int y);
	
};

#ifndef _DEBUG  // debug version in I_GOView.cpp
inline CI_GODoc* CI_GOView::GetDocument()
   { return (CI_GODoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_I_GOVIEW_H__EBF81F81_2D8E_43F9_8779_50F2E544DABE__INCLUDED_)
