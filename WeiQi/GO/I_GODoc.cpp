// I_GODoc.cpp : implementation of the CI_GODoc class
//

#include "stdafx.h"
#include "I_GO.h"

#include "I_GODoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CI_GODoc

IMPLEMENT_DYNCREATE(CI_GODoc, CDocument)

BEGIN_MESSAGE_MAP(CI_GODoc, CDocument)
	//{{AFX_MSG_MAP(CI_GODoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CI_GODoc construction/destruction

CI_GODoc::CI_GODoc()
{
	// TODO: add one-time construction code here

}

CI_GODoc::~CI_GODoc()
{
}

BOOL CI_GODoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle("Î§Æå");
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CI_GODoc serialization

void CI_GODoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CI_GODoc diagnostics

#ifdef _DEBUG
void CI_GODoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CI_GODoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CI_GODoc commands
