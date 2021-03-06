//-------------------------------------------------------------------//
// This is the sizing control bar with a gripper and a caption.
// I added an optional "max" button alongside the "close" button.
//
// NOTE: Derived from code provided by Cristi Posea on 
// CodeGuru, 8/2000.
//
//	Copyright � 2001 A better Software.
//-------------------------------------------------------------------//

#if !defined(__SCBARCF_H__)
#define __SCBARCF_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// MDM	10/6/01 6:03:12 PM
// I don't want to have to include this header in the stdafx.h file!
#include "scbarg.h"								// Base class

/////////////////////////////////////////////////////////////////////////
// CSizingControlBarCF

#ifndef baseCSizingControlBarCF
#define baseCSizingControlBarCF CSizingControlBarG
#endif

class CSizingControlBarCF : public baseCSizingControlBarCF
{
    DECLARE_DYNAMIC(CSizingControlBarCF)

// Construction
public:
    CSizingControlBarCF( bool bUseMaxButton = false );

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Implementation
protected:
    // implementation helpers
    virtual void NcPaintGripper(CDC* pDC, CRect rcClient);

protected:
    BOOL    m_bActive; // a child has focus
    CString m_sFontFace;

// Generated message map functions
protected:
    //{{AFX_MSG(CSizingControlBarCF)
    //}}AFX_MSG
    afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////

#endif // !defined(__SCBARCF_H__)
