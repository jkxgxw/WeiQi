
// RaspCam.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRaspCamApp:
// �йش����ʵ�֣������ RaspCam.cpp
//

class CRaspCamApp : public CWinApp
{
public:
	CRaspCamApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRaspCamApp theApp;