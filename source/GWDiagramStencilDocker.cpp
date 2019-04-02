/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_stencil
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_stencil::diagram_stencil()
{
	_drag_data_pointer = CX_NULL_POINTER;

	_pDropSource = CX_NULL_POINTER;
	_pDataObject = CX_NULL_POINTER;
}

diagram_stencil::~diagram_stencil()
{
}

//===========================================================================
cx::bool_t diagram_stencil::create(gw::widget_entry_collection* wec)
{
	if (false == gw::ctrl::form::create(wec))
	{
		return false;
	}


	return true;
}

void diagram_stencil::destroy (void)
{
	gw::ctrl::form::destroy();
}

//===========================================================================
void diagram_stencil::on_widget_mouse_clicked (gw::widget_mouse_event* e)
{
	gw::ctrl::blue_highlight* wc = static_cast<gw::ctrl::blue_highlight*>(e->_widget);

	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", wc->get_text().c_str());
}

void diagram_stencil::on_widget_mouse_dbclicked (gw::widget_mouse_event* e)
{
	gw::ctrl::blue_highlight* wc = static_cast<gw::ctrl::blue_highlight*>(e->_widget);

	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", wc->get_text().c_str());
}

void diagram_stencil::on_widget_mouse_pressed  (gw::widget_mouse_event* e)
{
	gw::ctrl::blue_highlight* wc = static_cast<gw::ctrl::blue_highlight*>(e->_widget);
	

	std::string name;

	cx::uint_t i;
	cx::uint_t count;


	count = _control_container.size();
	for (i=0u; i<count; i++)
	{
		if (wc == _control_container[i] )
		{
			name = _control_param_container[i];
			break;
		}
	}


	if (!name.empty())
	{
		drag_drop(e, name);
	}
}

void diagram_stencil::drag_drop(gw::widget_mouse_event* e, std::string name)
{
	//-----------------------------------------------------------------------
	_drag_data_pointer->name  = name;

	if (false==gw::set_drag_data (_pDataObject, _drag_data_pointer, gw::drag_data_object_clipboard_format::get_clipboard_format()))
	{
		return;
	}


	//-----------------------------------------------------------------------
	HRESULT hr;
	DWORD   dwEffect;


	get_window_event_handler()->set_window_mouse_capture_enabled(false);

	hr = DoDragDrop (_pDataObject, _pDropSource, DROPEFFECT_COPY, &dwEffect);
	if ( FAILED(hr) )
	{
		CX_DEBUG_TRACEF(CX_TWA_CRITICAL, "DoDragDrop() failed = %08x", hr);
	}

	get_window_event_handler()->set_window_mouse_capture_enabled(true);


	//-----------------------------------------------------------------------
	/*
	DRAGDROP_S_DROP
	DRAGDROP_S_CANCEL
	E_UNSPEC
	*/
	if (DRAGDROP_S_DROP==hr || DRAGDROP_S_CANCEL==hr)
	{
		switch ( dwEffect )
		{
		case DROPEFFECT_COPY:
			CX_DEBUG_TRACEF(TW_THISCODE, "DROPEFFECT_COPY(0x%08x)", dwEffect);
			break;

		case DROPEFFECT_MOVE:
			CX_DEBUG_TRACEF(TW_THISCODE, "DROPEFFECT_MOVE(0x%08x)", dwEffect);
			break;

		case DROPEFFECT_NONE:
			CX_DEBUG_TRACEF(TW_THISCODE, "DROPEFFECT_NONE(0x%08x)", dwEffect);
			break;

		default:
			CX_DEBUG_TRACEF(TW_THISCODE, "?(0x%08x)", dwEffect);
			break;
		}
	}
	else
	{
		CX_DEBUG_TRACEF(TW_THISCODE, "DoDragDrop() failed (hr=0x%08x)", dwEffect);
	}


	//-----------------------------------------------------------------------
	gw::widget_mouse_event wme;


	wme = *e;
	wme._code = gw::EC_MOUSE_LBUTTON_UP;

	get_window_event_handler()->on_mouse_lbutton_up(&wme);
}

void diagram_stencil::load_diagram(gw::widget_entry_collection* wec)
{
	//-----------------------------------------------------------------------
	gw::ctrl::blue_highlight* wc;
//	gw::ctrl::button* wc;


	//-----------------------------------------------------------------------
	gw::widget_entry_pointer_container_t::iterator i;
	gw::widget_entry* we;


	for (i = wec->get_container().begin(); i != wec->get_container().end(); i++)
	{
		we = (*i);


		wc = new gw::ctrl::blue_highlight();
//		wc = new gw::ctrl::button();

		wc->set_text( we->get_name() );

		get_widget()->get_container().push_back(wc);

		_control_container      .push_back( wc );
		_control_param_container.push_back( we->get_widget_class() );
	}


	//-----------------------------------------------------------------------
	get_widget()->set_model(this);
	get_widget()->initialize();


	//-----------------------------------------------------------------------
	resize_control(100, 100);
}

void diagram_stencil::resize_control (cx::int_t window_cx, cx::int_t window_cy)
{
	gw::ctrl::wh_layout l(true);

	gw::coordinates_t item_xsize;
	gw::coordinates_t item_ysize;


	item_ysize = 24;
	if (window_cx < 100)
	{
		item_xsize = 100;
	}
	else
	{
		item_xsize = window_cx-10.0f;
	}


	cx::uint_t i;
	cx::uint_t count;


	l.begin(gw::point_t(0,5), 5,0);

	l.set_item_size(item_xsize,item_ysize);


	count = _control_container.size();
	for (i=0u; i<count; i++)
	{
		l.add_control(_control_container[i]);

		if ( (i!=0u) && (0u==((i+1)%32)) )
		{
			l.separate();
		}
	}

	l.end();


	gw::rectangle_t r;


	r = l.get_bounds();
	get_view()->set_wolrd_rectangle(gw::rectangle_t(r._p1._x,r._p1._y+10));
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramStencilWnd::CGWDiagramStencilWnd()
{
	m_pDropSource = NULL;
	m_pDataObject = NULL; 

	m_Model = CX_NULL_POINTER;
}

CGWDiagramStencilWnd::~CGWDiagramStencilWnd()
{
}

//===========================================================================
void CGWDiagramStencilWnd::PreCreate(CREATESTRUCT& cs)
{
    CWnd::PreCreate(cs);
	
	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
//	cs.dwExStyle |=  WS_EX_CLIENTEDGE;
}

int CGWDiagramStencilWnd::OnCreate(CREATESTRUCT& cs)
{
	//-----------------------------------------------------------------------
    UNREFERENCED_PARAMETER(cs);

    //SetTimer (1, 250, NULL) ;

	m_Model = new diagram_stencil();
	m_Model->set_window(*this);
	m_Model->create(&GetMyWinApp()->_control_widget_entry_collection);
	m_Model->load_diagram(&GetMyWinApp()->_diagram_widget_entry_collection);


	m_ViewScrollHelper.initialize(*this, false, false);


	gw::rectangle_t r;


	r = m_Model->get_view()->get_wolrd_rectangle();

	m_ViewScrollHelper.set_contents(r.w(),r.h());


//	OleInitialize(NULL);


	m_pDropSource = new gw::drop_source();
	m_pDataObject = new gw::drag_data_object( gw::drag_data_object_clipboard_format::get_clipboard_format() );


	m_Model->_drag_data_pointer = &m_DragData;

	m_Model->_pDropSource = m_pDropSource;
	m_Model->_pDataObject = m_pDataObject;

    return 0;
}

void CGWDiagramStencilWnd::OnDestroy()
{
	m_Model->destroy();
	delete m_Model;
	m_Model = CX_NULL_POINTER;


	if (m_pDataObject != NULL)
	{
		m_pDataObject->Release();
	}

	if (m_pDropSource != NULL)
	{
		m_pDropSource->Release();
	}


//	OleUninitialize();


    //KillTimer(1);
}

LRESULT CGWDiagramStencilWnd::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "SetFocus()");

    SetFocus();
    return FinalWindowProc(msg, wparam, lparam);
}

LRESULT CGWDiagramStencilWnd::OnSize(UINT msg, WPARAM wparam, LPARAM lparam)
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

		
		m_Model->resize_control(m_cxClientMax,m_cyClientMax);


		gw::rectangle_t r;


		r = m_Model->get_view()->get_wolrd_rectangle();

		m_ViewScrollHelper.set_contents(r.w(),r.h());


		m_Model->get_view()->set_viewport_window_size(m_cxClientMax, m_cyClientMax);

		m_ViewScrollHelper.set_window(m_cxClientMax, m_cyClientMax, true);

		m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


		Invalidate();
	}

	return 0;
}

LRESULT CGWDiagramStencilWnd::OnHScroll (UINT msg, WPARAM wparam, LPARAM lparam)
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


	m_ViewScrollHelper.on_xscroll(code,position);
		
	m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


	Invalidate();

    return 0;
}

LRESULT CGWDiagramStencilWnd::OnVScroll (UINT msg, WPARAM wparam, LPARAM lparam)
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


	m_ViewScrollHelper.on_yscroll(code,position);
		
	m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


	Invalidate();

    return 0;
}

LRESULT CGWDiagramStencilWnd::OnMouseWheel (UINT msg, WPARAM wparam, LPARAM lparam)
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

	scale = false;
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

    return 0;
}

LRESULT CGWDiagramStencilWnd::OnTimer(UINT msg, WPARAM wparam, LPARAM lparam)
{
    UNREFERENCED_PARAMETER(msg);
    UNREFERENCED_PARAMETER(wparam);
    UNREFERENCED_PARAMETER(lparam);

    return 0;
}

/*
LRESULT CGWDiagramStencilWnd::OnPaint(UINT msg, WPARAM wparam, LPARAM lparam)
{
    UNREFERENCED_PARAMETER(msg);
    UNREFERENCED_PARAMETER(wparam);
    UNREFERENCED_PARAMETER(lparam);

	CPaintDC dc(GetHwnd());


	Draw(dc);


    return 0;
}
*/

void CGWDiagramStencilWnd::OnDraw(CDC& dc)
{
	// OnDraw is called automatically whenever a part of the window needs to be redrawn.
	Draw(dc);
}

void CGWDiagramStencilWnd::Draw (CDC& dc)
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

	if (m_Model)
	{
		m_Model->get_view()->draw(memoryDC);
	}


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

BOOL CGWDiagramStencilWnd::OnEraseBkgnd(CDC& dc)
{
	UNREFERENCED_PARAMETER(dc);

	return TRUE;
}

LRESULT CGWDiagramStencilWnd::OnLButtonUp(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_LBUTTONUP");
	return 0;
}

LRESULT CGWDiagramStencilWnd::OnLButtonDown(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_LBUTTONDOWN");


	//-----------------------------------------------------------------------
	/*
	SetCapture()호출하고, DoDragDrop()호출하면 이상해짐 WM_LBUTTON_UP도 안날라옴
	*/


	//-----------------------------------------------------------------------
	CPoint ptMouse((short)LOWORD(lparam), (short)HIWORD(lparam));
	UINT   uMouseFlag = wparam;
	WORD   fwKeys     = LOWORD(wparam);
	SHORT  zDelta     = HIWORD(wparam);


	//-----------------------------------------------------------------------
	Invalidate(FALSE);


	//-----------------------------------------------------------------------
	m_DragData.name = "widget.diagram";

	if (false==gw::set_drag_data (m_pDataObject, &m_DragData, gw::drag_data_object_clipboard_format::get_clipboard_format()))
	{
		return 0;
	}

			
	//-----------------------------------------------------------------------
	m_Model->get_window_event_handler()->set_window_mouse_capture_enabled(false);
	

	//-----------------------------------------------------------------------
	HRESULT hr;
	DWORD dwEffect;


	hr = DoDragDrop (m_pDataObject, m_pDropSource, DROPEFFECT_COPY, &dwEffect);
	if ( FAILED(hr) )
	{
		CX_DEBUG_TRACEF(CX_TWA_CRITICAL, "DoDragDrop() failed = %08x", hr);
	}	

	//-----------------------------------------------------------------------
	m_Model->get_window_event_handler()->set_window_mouse_capture_enabled(true);
	

	//-----------------------------------------------------------------------
	m_Model->get_window_event_handler()->on_windows_message(*this,WM_LBUTTONUP,wparam,lparam);


	//-----------------------------------------------------------------------
	/*
	DRAGDROP_S_DROP
	DRAGDROP_S_CANCEL
	E_UNSPEC
	*/
	if (DRAGDROP_S_DROP==hr || DRAGDROP_S_CANCEL==hr)
	{
		switch ( dwEffect )
		{
		case DROPEFFECT_COPY:
			CX_DEBUG_TRACEF(TW_THISCODE, "DROPEFFECT_COPY(0x%08x)", dwEffect);
			break;

		case DROPEFFECT_MOVE:
			CX_DEBUG_TRACEF(TW_THISCODE, "DROPEFFECT_MOVE(0x%08x)", dwEffect);
			break;

		case DROPEFFECT_NONE:
			CX_DEBUG_TRACEF(TW_THISCODE, "DROPEFFECT_NONE(0x%08x)", dwEffect);
			break;

		default:
			CX_DEBUG_TRACEF(TW_THISCODE, "?(0x%08x)", dwEffect);
			break;
		}
	}
	else
	{
		CX_DEBUG_TRACEF(TW_THISCODE, "DoDragDrop() failed (hr=0x%08x)", dwEffect);
	}


	return 0;
}

LRESULT CGWDiagramStencilWnd::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


#if 0
	// WM_LBUTTONDOW에서 DoDragDrop() 호출시
	if (m_Model)
	{
		m_Model->get_window_event_handler()->on_windows_message(*this, msg, wparam, lparam);
	}
#endif


	switch (msg)
    {
    case WM_MOUSEACTIVATE:  lResult = OnMouseActivate (msg, wparam, lparam); break;
    case WM_SIZE:           lResult = OnSize          (msg, wparam, lparam); break;
    case WM_HSCROLL:        lResult = OnHScroll       (msg, wparam, lparam); break;
    case WM_VSCROLL:        lResult = OnVScroll       (msg, wparam, lparam); break;
	case WM_MOUSEWHEEL:     lResult = OnMouseWheel    (msg, wparam, lparam); break;
//	case WM_TIMER:          lResult = OnTimer         (msg, wparam, lparam); break;
//	case WM_PAINT:          lResult = OnPaint         (msg, wparam, lparam); break;
//	case WM_LBUTTONDOWN:    lResult = OnLButtonDown   (msg, wparam, lparam); break;
//	case WM_LBUTTONUP:      lResult = OnLButtonUp     (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
    }


#if 1
	if (m_Model)
	{
		m_Model->get_window_event_handler()->on_windows_message(*this, msg, wparam, lparam);
	}
#endif


    return lResult;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramStencilContainer::CGWDiagramStencilContainer()
{
    SetView        (m_Wnd); 
    SetDockCaption (_T("도표"));
    SetTabText     (_T("도표"));
    SetTabIcon     (IDI_DOCKER);
} 

CGWDiagramStencilContainer::~CGWDiagramStencilContainer()
{
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramStencilDocker::CGWDiagramStencilDocker()
{
	//-----------------------------------------------------------------------
	GetMyWinApp()->GetMainFrame()->m_DiagramStencilDocker = this;


	//-----------------------------------------------------------------------
    SetView     (m_DockContainer);
//	SetBarWidth (4);
}

CGWDiagramStencilDocker::~CGWDiagramStencilDocker()
{
	//-----------------------------------------------------------------------
	if (GetMyWinApp()->GetMainFrame()->m_DiagramStencilDocker == this)
	{
		GetMyWinApp()->GetMainFrame()->m_DiagramStencilDocker = CX_NULL_POINTER;
	}
}
