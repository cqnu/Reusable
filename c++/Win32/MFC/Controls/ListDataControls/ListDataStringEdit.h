//-------------------------------------------------------------------//
// ListDataStringEdit
//
//	Copyright � 2001 A better Software.
//-------------------------------------------------------------------//

#if !defined(LIST_DATA_STRING_EDIT_H)
#define LIST_DATA_STRING_EDIT_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListDataStringEdit.h : header file
//

#include <Controls\EditTrans.h>														// For transparent background edit controls.

#include "ListDataControlData.h"


/////////////////////////////////////////////////////////////////////////////
// ListDataStringEdit window

class ListDataStringEdit : public CEditTrans, public ListDataControlData< CString >
{
	typedef CEditTrans inherited;

// Construction
public:
	ListDataStringEdit();

	void Initialize(
		CString*					pNewDBVar,
		CString*					pNewAltDBVar,
		int						nNewListColumn
	);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListDataStringEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ListDataStringEdit();

	void ExtractControlValue();

	CString GetValueAsString();
	CString GetAltVarAsString();

protected:

	// This indicates when the text has been changed and we are ready
	// for an update.  Note that database data is never changed unless
	// a change has been made within the edit text.
	bool m_bUpdated;

	bool m_bMultiPrompt;

	void DisplayControlValue();

	// Generated message map functions
	//{{AFX_MSG(ListDataStringEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(LIST_DATA_STRING_EDIT_H)
