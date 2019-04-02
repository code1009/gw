/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CMyTabbedMDI::CMyTabbedMDI()
{
}

//===========================================================================
CWnd* CMyTabbedMDI::NewMDIChildFromID(int mdiChild)
{
    CWnd* pView = NULL;

	
	switch(mdiChild)
    {
	case ID_MDI_VIEW_FORM:
		pView = new CGWControlFormView();
		break;

    default:
        TRACE("Unknown TabbedMDI id\n");
        break;
    }

    return pView;
}

CWnd* CMyTabbedMDI::AddMDIChild(CWnd* pView, LPCTSTR pTabText, int mdiChildID /*= 0*/)
{
    assert(pView); // Cannot add Null CWnd*
    assert(lstrlen(pTabText) < MAX_MENU_STRING);

    GetTab().AddTabPage(pView, pTabText, IDI_VIEW, mdiChildID);

    // Fake a WM_MOUSEACTIVATE to propagate focus change to dockers
    if (IsWindow())
        GetParent().SendMessage(WM_MOUSEACTIVATE, (WPARAM)(GetAncestor().GetHwnd()),
                                    MAKELPARAM(HTCLIENT,WM_LBUTTONDOWN));

    return pView;
}

BOOL CMyTabbedMDI::OnTabClose(int page)
{
	//--------------------------------------------------------------------------
	TabPageInfo tpi;
	
	
	tpi = GetTab().GetTabPageInfo(page);
	
	
	//--------------------------------------------------------------------------
	CMyView* pMyView;
	CGWDiagramEditorView* pGWDiagramEditorView;

	
	pMyView = (CMyView*)tpi.pView;
	
	if (pMyView->GetViewType()=="GWDiagramEditorView")
	{
		pGWDiagramEditorView = (CGWDiagramEditorView*)pMyView;

		pGWDiagramEditorView->GetModel();


		if (IDYES!=MessageBox("´Ý¾î?", "È®ÀÎ", MB_YESNO))
		{
			return FALSE;
		}
	}


#if 0
	//--------------------------------------------------------------------------
	LONG window_id;
	
	
	window_id = tpi.pView->GetWindowLong(GWLP_ID);
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "id = %d", window_id);

	if (IDYES!=MessageBox("´Ý¾î?", "È®ÀÎ", MB_YESNO))
	{
		return FALSE;
	}
#endif

	return TRUE;
}
