
// RaspCamDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CRaspCamDlg 对话框
class CRaspCamDlg : public CDialogEx
{
// 构造
public:
	CRaspCamDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RASPCAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_BtnAdd;
	CButton m_BtnDel;
	CButton m_BtnShow;
	CButton m_BtnConcel;
	afx_msg void OnBnClickedButtonAdd();
	CListCtrl m_ListIP;
	CRect m_videoRect;

	void DrawImage(CDC *dcMem);
	void InitList();

	CButton m_BtnConn;
	afx_msg void OnBnClickedButtonConn();

	afx_msg void OnNMCustomdrawListIp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemchangedListIp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonShow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void OnTimer(UINT_PTR nIDEvent);
};
