
// RaspCamDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CRaspCamDlg �Ի���
class CRaspCamDlg : public CDialogEx
{
// ����
public:
	CRaspCamDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RASPCAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
