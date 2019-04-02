/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramPropertyDockerWnd::CGWDiagramPropertyDockerWnd()
{
	m_Model = CX_NULL_POINTER;
}

CGWDiagramPropertyDockerWnd::~CGWDiagramPropertyDockerWnd()
{
}

char _text[256] = "text";

//===========================================================================
void CGWDiagramPropertyDockerWnd::PreCreate(CREATESTRUCT& cs)
{
	CWnd::PreCreate(cs);
	
//	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
	cs.style     |= WS_CLIPCHILDREN;
	cs.dwExStyle |=  WS_EX_CLIENTEDGE;
}

HWND _PropGridCtl;

int CGWDiagramPropertyDockerWnd::OnCreate(CREATESTRUCT& cs)
{
	UNREFERENCED_PARAMETER(cs);

	m_Font.CreatePointFont(90, _T("¸¼Àº°íµñ"), CX_NULL_POINTER, FALSE, FALSE);
	SetFont(m_Font);


	//SetTimer (1, 250, NULL) ;

#if 0
	m_Model = new property_list();
	m_Model->set_window(*this);
	m_Model->create(&GetMyWinApp()._control_widget_entry_collection);


	m_ViewScrollHelper.initialize(*this, false, false);


	gw::rectangle_t r;


	r = m_Model->get_view()->get_wolrd_rectangle();

	m_ViewScrollHelper.set_contents(r.w(),r.h());
#endif

	_PropGridCtl = ::CreateWindow("PropGridCtl", "", WS_VISIBLE|WS_CHILD|WS_TABSTOP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 0,0,1,1,*this,(HMENU)1234,GetMyWinApp().GetInstanceHandle(),0);


    PROPGRIDITEM Item;
    
	
	PropGrid_ItemInit(Item);

    Item.lpszCatalog = _T("Edit, Static, and Combos");
    Item.lpszPropName = _T("Edit Field");
    Item.lpCurValue = (LPARAM)_text;
    Item.lpszPropDesc = _T("This field is editable");
    Item.iItemType = PIT_EDIT;
    PropGrid_AddItem(_PropGridCtl, &Item);


    PropGrid_ShowToolTips(_PropGridCtl,TRUE);
    PropGrid_ExpandAllCatalogs(_PropGridCtl);
	PropGrid_SetCurSel(_PropGridCtl,0);


	return 0;
}

void CGWDiagramPropertyDockerWnd::OnDestroy()
{
#if 0
	m_Model->destroy();
	delete m_Model;
	m_Model = CX_NULL_POINTER;
#endif
	PropGrid_DeleteItem(_PropGridCtl,0);
	PropGrid_ResetContent(_PropGridCtl);
	DestroyWindow(_PropGridCtl);

	m_Font.DeleteObject();
}

LRESULT CGWDiagramPropertyDockerWnd::OnNotify(WPARAM wparam, LPARAM lparam)
{
	UINT    Id    = static_cast<UINT>(wparam);
    LPNMHDR NmHdr = reinterpret_cast<LPNMHDR>(lparam);

    LPNMPROPGRID nmp = (LPNMPROPGRID)NmHdr;
	LPPROPGRIDITEM item = PropGrid_GetItemData(NmHdr->hwndFrom, nmp->iIndex);

	if ( NmHdr->code==PGN_PROPERTYCHANGE )
	{
    switch(nmp->iIndex)
    {
	case 0:
		CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", (LPTSTR)item->lpCurValue);
		break;
	}
	}

	/*
    switch (NmHdr->code)
    {

	default:
		break;
	}
	*/

	//return CWnd::OnNotifyReflect(wparam, lparam);
	return 1;
}

LRESULT CGWDiagramPropertyDockerWnd::OnNotifyReflect(WPARAM wparam, LPARAM lparam)
{
    LPNMHDR NmHdr = reinterpret_cast<LPNMHDR>(lparam);

    LPNMPROPGRID lpnmp = (LPNMPROPGRID)NmHdr;
	LPPROPGRIDITEM Item = PropGrid_GetItemData(NmHdr->hwndFrom, lpnmp->iIndex);


    switch(lpnmp->iIndex)
    {
	case 0:
		CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", (LPTSTR)Item->lpCurValue);
		break;
	}
	/*
    switch (NmHdr->code)
    {

	default:
		break;
	}
	*/

	//return CWnd::OnNotifyReflect(wparam, lparam);
	return 1;
}


LRESULT CGWDiagramPropertyDockerWnd::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "SetFocus()");

//	SetFocus();
	return FinalWindowProc(msg, wparam, lparam);
}

LRESULT CGWDiagramPropertyDockerWnd::OnSize(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);

	// If not minimized, save the window size
	if (wparam != SIZE_MINIMIZED)
	{
		m_cxClientMax = LOWORD (lparam) ;
		if (m_cxClientMax < 1)
			m_cxClientMax = 1;

		m_cyClientMax = HIWORD (lparam) ;
		if (m_cyClientMax < 1)
			m_cyClientMax = 1;

		
#if 0
		m_Model->resize_control(m_cxClientMax,m_cyClientMax);


		gw::rectangle_t r;


		r = m_Model->get_view()->get_wolrd_rectangle();

		m_ViewScrollHelper.set_contents(r.w(),r.h());


		m_Model->get_view()->set_viewport_window_size(m_cxClientMax, m_cyClientMax);

		m_ViewScrollHelper.set_window(m_cxClientMax, m_cyClientMax, true);

		m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());

		Invalidate();
#endif

		if ( ::IsWindow(_PropGridCtl) )
		{
			::MoveWindow(_PropGridCtl, 0,0,m_cxClientMax,m_cyClientMax, TRUE);
			::RedrawWindow(_PropGridCtl, NULL, NULL, RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW);


    PROPGRIDITEM Item;
    
	
	PropGrid_ItemInit(Item);

    Item.lpszCatalog = _T("Edit, Static, and Combos");
    Item.lpszPropName = _T("Edit Field");
    Item.lpCurValue = (LPARAM)"xxxxxxxxxxxxxx";
    Item.lpszPropDesc = _T("This field is editable");
    Item.iItemType = PIT_EDIT;
    PropGrid_SetItemData(_PropGridCtl, 0, &Item);

		}
	}

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnHScroll (UINT msg, WPARAM wparam, LPARAM lparam)
{
	int  code     ;
	HWND scrollbar;

	int  position ;


	code       = (int )LOWORD(wparam);
	scrollbar  = (HWND)lparam;

	if (SB_THUMBTRACK   == code || 
		SB_THUMBPOSITION== code  )
	{
		position = (SHORT)HIWORD(wparam);
	}
	else
	{
		position = GetScrollPos(SB_HORZ);
	}


#if 0
	m_ViewScrollHelper.on_xscroll(code,position);
		
	m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());
#endif

	Invalidate();

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnVScroll (UINT msg, WPARAM wparam, LPARAM lparam)
{
	int  code     ;
	HWND scrollbar;

	int  position ;


	code       = (int )LOWORD(wparam);
	scrollbar  = (HWND)lparam;

	if (SB_THUMBTRACK   == code || 
		SB_THUMBPOSITION== code  )
	{
		position = (SHORT)HIWORD(wparam);
	}
	else
	{
		position = GetScrollPos(SB_VERT);
	}


#if 0
	m_ViewScrollHelper.on_yscroll(code,position);
		
	m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());
#endif

	Invalidate();

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnMouseWheel (UINT msg, WPARAM wparam, LPARAM lparam)
{
	CPoint ptMouse((short)LOWORD(lparam), (short)HIWORD(lparam));
	UINT   uMouseFlag = wparam;

	WORD  fwKeys = LOWORD(wparam);
	SHORT zDelta = HIWORD(wparam);


	cx::bool_t scale = false;

	switch (fwKeys)
	{
	case MK_CONTROL  :
		scale = true;
		break;
	case MK_LBUTTON  :
	case MK_RBUTTON  :
		break;
	case MK_MBUTTON  :
		break;
	case MK_SHIFT    :
		break;
	case MK_XBUTTON1 :
	case MK_XBUTTON2 :
		break;
	}

#if 0

//	scale = false;
	if ( scale )
	{
		cx::float_t viewscale_delta;
		cx::float_t viewscale_max  ;
		cx::float_t viewscale_min  ;

		cx::float_t viewscale;
		cx::float_t previous_viewscale;


		viewscale       = m_Model->get_view()->get_viewscale();
		viewscale_max   =  5.0f;
		viewscale_min   =  0.1f;
		viewscale_delta =  0.1f;

		previous_viewscale = viewscale;



		if ( zDelta>0 ) 
		{
			viewscale = viewscale + viewscale_delta;
		}
		else
		{
			viewscale = viewscale - viewscale_delta;
		}

		if (viewscale>viewscale_max)
		{
			viewscale = viewscale_max;
		}
		if (viewscale<viewscale_min)
		{
			viewscale = viewscale_min;
		}

		m_Model->get_view()->set_viewscale(viewscale);


		gw::rectangle_t r;


		r = m_Model->get_view()->get_wolrd_rectangle();

		m_ViewScrollHelper.set_contents(r.w()*m_Model->get_view()->get_viewscale(), r.h()*m_Model->get_view()->get_viewscale(), true);
		
		m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


		Invalidate();
	}
	else
	{
		if ( zDelta > 0 )
		{
			OnVScroll(0,MAKEWORD(SB_LINEUP,0),0);
		}
		else
		{
			OnVScroll(0,MAKEWORD(SB_LINEDOWN,0),0);
		}
	}
#endif

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnTimer(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wparam);
	UNREFERENCED_PARAMETER(lparam);

	return 0;
}

/*
LRESULT CGWDiagramPropertyDockerWnd::OnPaint(UINT msg, WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wparam);
	UNREFERENCED_PARAMETER(lparam);

	CPaintDC dc(GetHwnd());


	Draw(dc);


	return 0;
}
*/

void CGWDiagramPropertyDockerWnd::OnDraw(CDC& dc)
{
	// OnDraw is called automatically whenever a part of the window needs to be redrawn.
	Draw(dc);
}

void CGWDiagramPropertyDockerWnd::Draw (CDC& dc)
{
	CRect rect;
	
	
	rect = GetClientRect();


#if 1
	CDC     memoryDC;
	CBitmap bitmap;
	HBITMAP hOldBitmap;

	memoryDC.CreateCompatibleDC    (dc);
	bitmap  .CreateCompatibleBitmap(dc, rect.right, rect.bottom);

	hOldBitmap = memoryDC.SelectObject(bitmap);

	memoryDC.SolidFill(RGB(0xFFu, 0xFFu, 0xFFu), rect);

#if 0
	if (m_Model)
	{
		m_Model->get_view()->draw(memoryDC);
	}
#endif

	dc.BitBlt(0, 0, rect.right, rect.bottom, memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(hOldBitmap);
	memoryDC.Destroy();

	bitmap.DeleteObject();
#else
	dc.SolidFill(RGB(0xFFu, 0xFFu, 0xFFu), rect);

	m_Model->get_view()->draw(dc);
#endif

	return;


	CRect rc = GetClientRect();


	TCHAR text[256];
	
	
	sprintf_s(text, "%d %d - %d %d %d %d ",
		m_cxClientMax, m_cyClientMax,
		rc.left,
		rc.right,
		rc.top,
		rc.bottom
		);

	dc.DrawText(text, -1, rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

BOOL CGWDiagramPropertyDockerWnd::OnEraseBkgnd(CDC& dc)
{
	UNREFERENCED_PARAMETER(dc);

	return FALSE;
}

LRESULT CGWDiagramPropertyDockerWnd::OnLButtonUp(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_LBUTTONUP");
	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnLButtonDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_LBUTTONDOWN");

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnGetFont(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return (LRESULT)((HFONT)m_Font);
}

LRESULT CGWDiagramPropertyDockerWnd::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


	switch (msg)
	{
	case WM_MOUSEACTIVATE:  lResult = OnMouseActivate (msg, wparam, lparam); break;
	case WM_SIZE:           lResult = OnSize          (msg, wparam, lparam); break;
	case WM_HSCROLL:        lResult = OnHScroll       (msg, wparam, lparam); break;
	case WM_VSCROLL:        lResult = OnVScroll       (msg, wparam, lparam); break;
	case WM_MOUSEWHEEL:     lResult = OnMouseWheel    (msg, wparam, lparam); break;
	case WM_GETFONT:        lResult = OnGetFont       (msg, wparam, lparam); break;
//	case WM_TIMER:          lResult = OnTimer         (msg, wparam, lparam); break;
//	case WM_PAINT:          lResult = OnPaint         (msg, wparam, lparam); break;
//	case WM_LBUTTONDOWN:    lResult = OnLButtonDown   (msg, wparam, lparam); break;
//	case WM_LBUTTONUP:      lResult = OnLButtonUp     (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
	}


#if 0
	if (m_Model)
	{
		m_Model->get_window_event_handler()->on_windows_message(*this, msg, wparam, lparam);
	}
#endif

	return lResult;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramPropertyDockContainer::CGWDiagramPropertyDockContainer()
{
	SetView        (m_Wnd); 
	SetDockCaption (_T("DiagramProperty - Docking container"));
	SetTabText     (_T("DiagramProperty"));
	SetTabIcon     (IDI_DOCKER);
} 



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramPropertyDocker::CGWDiagramPropertyDocker()
{
	SetView     (m_DockContainer);
//	SetBarWidth (4);
}


