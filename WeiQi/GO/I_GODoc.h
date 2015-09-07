// I_GODoc.h : interface of the CI_GODoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_I_GODOC_H__AD60563E_CEC3_4A37_8DCF_DB10C55899BB__INCLUDED_)
#define AFX_I_GODOC_H__AD60563E_CEC3_4A37_8DCF_DB10C55899BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CI_GODoc : public CDocument
{
protected: // create from serialization only
	CI_GODoc();
	DECLARE_DYNCREATE(CI_GODoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CI_GODoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CI_GODoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CI_GODoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_I_GODOC_H__AD60563E_CEC3_4A37_8DCF_DB10C55899BB__INCLUDED_)
