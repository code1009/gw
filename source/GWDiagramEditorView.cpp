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
//===========================================================================
diagram_edit::diagram_edit()
{
}

diagram_edit::~diagram_edit()
{
}

//===========================================================================
cx::bool_t diagram_edit::create (gw::widget_entry_collection* wec)
{
	cx::bool_t result;


	result = gw::dgrm::edit::create(wec);
	if (false==result)
	{
		return false;
	}


	return true;
}

void diagram_edit::destroy (void)
{
	gw::dgrm::edit::destroy();
}

void diagram_edit::update_system_clipboard (cx::bool_t save)
{
	UINT cf = gw::drag_data_object_clipboard_format::get_clipboard_format();


	if (save)
	{
		// diagram_clipboard to system_clipboard

		//-------------------------------------------------------------------
		std::string stream;


		//-------------------------------------------------------------------
		cx::bool_t result;


		gw::dgrm::json_document_writer io(1u, stream);

	
		result = io.create(&GetMyWinApp()->_diagram_widget_entry_collection);
		if (result)
		{
			result = io.write(this, get_diagram_clipboard());
		}
		io.destroy();
		

		//-------------------------------------------------------------------
		if (false==result)
		{
			return;
		}


		//-------------------------------------------------------------------
		stream = io.get_string();
		if (stream.empty())
		{
			return;
		}


		//-------------------------------------------------------------------
#if defined(CX_DEBUG)
		cx::debug::print ("TO WINDOWS CLIPBOARD\n");
//		cx::debug::print (stream.c_str()+3);
//		cx::debug::print ("\n");
		cx::debug::print (cx::utf8_to_mbcs(stream.c_str()+3).c_str());
		cx::debug::print ("\n");
#endif	

	
		//-------------------------------------------------------------------
		HGLOBAL hglobal;
			
		cx::byte_t* target_pointer;
		cx::byte_t* source_pointer;
		cx::uint_t  size;


		if (FALSE==::OpenClipboard(get_window()))
		{
			return;
		}


		::EmptyClipboard();

			
		size    = stream.size();
		hglobal = GlobalAlloc(GMEM_MOVEABLE, size);
		if (NULL==hglobal)
		{
			::CloseClipboard(); 
			return;
		}
		
		source_pointer = (cx::byte_t*)stream.c_str();
		target_pointer = (cx::byte_t*)GlobalLock(hglobal);
		memcpy(target_pointer, source_pointer,  size);
		GlobalUnlock(hglobal); 

			
		::SetClipboardData(cf, hglobal);


		::CloseClipboard(); 
	}
	else
	{
		// system_clipboard to diagram_clipboard 

		//-------------------------------------------------------------------
		std::string stream;


		//-------------------------------------------------------------------
		if (!::IsClipboardFormatAvailable(cf)) 
		{
			return;
		}


		if (FALSE==::OpenClipboard(get_window()))
		{
			return;
		}

		
		//-------------------------------------------------------------------
		HGLOBAL hglobal;

		cx::char_t* source_pointer;
		cx::uint_t  size;


		hglobal = ::GetClipboardData(cf); 
		if (NULL==hglobal)
		{ 
			::CloseClipboard();
			return;
		}


		size = GlobalSize(hglobal);
		source_pointer = (cx::char_t*) GlobalLock(hglobal);
		stream.insert(stream.begin(), source_pointer, source_pointer+size);
		GlobalUnlock(hglobal); 


		:: CloseClipboard(); 


		//-------------------------------------------------------------------
#if defined(CX_DEBUG)
		cx::debug::print ("FROM WINDOWS CLIPBOARD\n");
//		cx::debug::print (stream.c_str()+3);
//		cx::debug::print ("\n");
		cx::debug::print (cx::utf8_to_mbcs(stream.c_str()+3).c_str());
		cx::debug::print ("\n");
#endif


		//-------------------------------------------------------------------
		gw::widget_collection collection;


		//-------------------------------------------------------------------
		cx::bool_t result;


		gw::dgrm::json_document_reader io(1u, stream);

	
		result = io.create(&GetMyWinApp()->_diagram_widget_entry_collection);
		if (result)
		{
			result = io.read(this, &collection);
		}
		io.destroy();


		//-------------------------------------------------------------------
		if (false==result)
		{
			collection.delete_container();

			return;
		}

		
		//-------------------------------------------------------------------
		get_diagram_clipboard()->delete_container();


		//-------------------------------------------------------------------
		gw::dgrm::diagram* wd_clone;


		//-------------------------------------------------------------------
		gw::widget_pointer_container_t::iterator i;
		gw::widget* w;

		gw::dgrm::diagram* wd;
	

		//-------------------------------------------------------------------
		for (i =collection.get_container().begin();
			 i!=collection.get_container().end();
			 i++)
		{
			w = (*i);

			wd = cast_diagram(w);
			if (wd)
			{
				wd_clone = wd->clone();

				get_diagram_clipboard()->get_container().push_back(wd_clone);
			}
		}


		//-------------------------------------------------------------------
		collection.delete_container();
	}
}

void diagram_edit::on_edit_action_diagram_modified (void)
{
	gw::dgrm::edit::on_edit_action_diagram_modified();
}

void diagram_edit::on_diagram_property_changed (gw::dgrm::diagram_event* e)
{
	gw::dgrm::edit::on_diagram_property_changed(e);


	gw::dgrm::diagram* diagram_pointer;


	diagram_pointer = e->_diagram;

	if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
	{
		GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnDiagramPropertyChanged(diagram_pointer);
	}
}

void diagram_edit::on_modified (cx::bool_t modified)
{
	//gw::dgrm::edit::on_modified(modified);
}

void diagram_edit::on_select_changed (gw::dgrm::edit::select_changed_action_t action)
{
	gw::dgrm::edit::on_select_changed(action);


	gw::widget_collection* selected_diagram = get_selected_diagram();
	gw::dgrm::diagram* diagram_pointer;

	
	if (selected_diagram->get_container().empty())
	{
		if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
		{
			GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnSelectChanged(CX_NULL_POINTER);
		}
	}
	else
	{
		if (selected_diagram->get_container().size()!=1)
		{
			if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
			{
				GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnSelectChanged(CX_NULL_POINTER);
			}
		}
		else
		{
			diagram_pointer = (gw::dgrm::diagram*)selected_diagram->get_container()[0];

			if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
			{
				GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnSelectChanged(diagram_pointer);
			}
		}
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramEditorView::CGWDiagramEditorView()
{
	m_Model = CX_NULL_POINTER;

	m_pDropTarget = NULL;
}

CGWDiagramEditorView::~CGWDiagramEditorView()
{
}

//===========================================================================
void CGWDiagramEditorView::PreCreate(CREATESTRUCT& cs)
{
    CWnd::PreCreate(cs);
	
	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
	cs.dwExStyle |=  WS_EX_CLIENTEDGE;
}

int CGWDiagramEditorView::OnCreate(CREATESTRUCT& cs)
{
    UNREFERENCED_PARAMETER(cs);

    SetTimer (1, 250, NULL) ;

	m_Model = new diagram_edit();
	m_Model->set_window(*this);
	m_Model->create(&GetMyWinApp()->_diagram_widget_entry_collection);


	gw::rectangle_t r;
	
	
	r = m_Model->get_view()->get_wolrd_rectangle();
	m_ViewScrollHelper.initialize(*this);
	m_ViewScrollHelper.set_contents(r.w(),r.h());


//	OleInitialize(NULL);


	gw::drop_target* drop_target_pointer;


	drop_target_pointer = new gw::drop_target( gw::drag_data_object_clipboard_format::get_clipboard_format() );
	drop_target_pointer->set_model(m_Model);
	drop_target_pointer->set_window(*this);
	m_pDropTarget = drop_target_pointer;
	
	
	HRESULT hr;
	

	hr = RegisterDragDrop(*this, m_pDropTarget);
	if ( FAILED(hr) )
	{
		CX_DEBUG_TRACEF(CX_TWA_CRITICAL, "RegisterDragDrop() failed = %08x", hr);
	}

    return 0;
}

void CGWDiagramEditorView::OnDestroy()
{
	if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
	{
		GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnCloseView(m_Model->get_view());
	}


	HRESULT hr;
	

	hr = RevokeDragDrop(*this);
	if ( FAILED(hr) )
	{
		CX_DEBUG_TRACEF(CX_TWA_CRITICAL, "RevokeDragDrop() failed = %08x", hr);
	}

	if (m_pDropTarget != NULL)
	{
		m_pDropTarget->Release();
	}


//	OleUninitialize();


	m_Model->destroy();
	delete m_Model;
	m_Model = CX_NULL_POINTER;

    KillTimer(1);
}

LRESULT CGWDiagramEditorView::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "SetFocus()");

    SetFocus();

	if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
	{
		GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnActivatedView(m_Model->get_view());
	}

    return FinalWindowProc(msg, wparam, lparam);
}

LRESULT CGWDiagramEditorView::OnSize(UINT msg, WPARAM wparam, LPARAM lparam)
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


		m_Model->get_view()->set_viewport_window_size(m_cxClientMax, m_cyClientMax);

		m_ViewScrollHelper.set_window(m_cxClientMax, m_cyClientMax, true);

		m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


		Invalidate();
	}

	
	SetViewPropertyChanged();


	return 0;
}

LRESULT CGWDiagramEditorView::OnHScroll (UINT msg, WPARAM wparam, LPARAM lparam)
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

	
	SetViewPropertyChanged();


    return 0;
}

LRESULT CGWDiagramEditorView::OnVScroll (UINT msg, WPARAM wparam, LPARAM lparam)
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

	
	SetViewPropertyChanged();


    return 0;
}

LRESULT CGWDiagramEditorView::OnMouseWheel (UINT msg, WPARAM wparam, LPARAM lparam)
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


	SetViewPropertyChanged();


    return 0;
}

LRESULT CGWDiagramEditorView::OnTimer(UINT msg, WPARAM wparam, LPARAM lparam)
{
    UNREFERENCED_PARAMETER(msg);
    UNREFERENCED_PARAMETER(wparam);
    UNREFERENCED_PARAMETER(lparam);

    return 0;
}

/*
LRESULT CGWDiagramEditorView::OnPaint(UINT msg, WPARAM wparam, LPARAM lparam)
{
    UNREFERENCED_PARAMETER(msg);
    UNREFERENCED_PARAMETER(wparam);
    UNREFERENCED_PARAMETER(lparam);

	CPaintDC dc(GetHwnd());


	Draw(dc);


    return 0;
}
*/

void CGWDiagramEditorView::OnDraw(CDC& dc)
{
	// OnDraw is called automatically whenever a part of the window needs to be redrawn.
	Draw(dc);
}

void CGWDiagramEditorView::Draw (CDC& dc)
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
}

BOOL CGWDiagramEditorView::OnEraseBkgnd(CDC& dc)
{
	UNREFERENCED_PARAMETER(dc);

	return TRUE;
}

LRESULT CGWDiagramEditorView::OnClose(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return 1;
}

LRESULT CGWDiagramEditorView::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


    switch (msg)
    {
    case WM_MOUSEACTIVATE:  lResult = OnMouseActivate (msg, wparam, lparam); break;
    case WM_SIZE:           lResult = OnSize          (msg, wparam, lparam); break;
    case WM_HSCROLL:        lResult = OnHScroll       (msg, wparam, lparam); break;
    case WM_VSCROLL:        lResult = OnVScroll       (msg, wparam, lparam); break;
	case WM_MOUSEWHEEL:     lResult = OnMouseWheel    (msg, wparam, lparam); break;
    case WM_TIMER:          lResult = OnTimer         (msg, wparam, lparam); break;
//	case WM_PAINT:          lResult = OnPaint         (msg, wparam, lparam); break;
	case WM_CLOSE:          lResult = OnClose         (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
    }

	if (m_Model)
	{
		m_Model->get_window_event_handler()->on_windows_message(*this, msg, wparam, lparam);
	}

    return lResult;
}

BOOL CGWDiagramEditorView::OnFileOpen()
{
#if 0
	//-----------------------------------------------------------------------
	static cx::char_t filter[] = _T("json File(*.json)|*.json|All Files(*.*)|*.*||");

	CFileDialog fd(TRUE, _T(".json"), NULL, OFN_HIDEREADONLY, filter);


	if (IDOK!=fd.DoModal(*this))
	{
		return true;
	}
#endif

	
	//-----------------------------------------------------------------------
	std::string file_path;


#if defined (DEBUG) || (_DEBUG) 
	file_path = "d:\\a.json";
#else
//	file_path = fd.GetPathName();
	file_path = get_open_file_path(*this);
#endif

	
	if (file_path.empty())
	{
		return TRUE;
	}


	//-----------------------------------------------------------------------
	cx::bool_t  result;


	gw::dgrm::json_document_reader io(file_path);

	
	result = io.create(&GetMyWinApp()->_diagram_widget_entry_collection);
	if (result)
	{
		result = m_Model->read(&io);
		if (result)
		{
			m_Model->get_view()->set_background_color(io.get_view_parameter()->background_color);
			m_Model->get_view()->set_wolrd_rectangle (io.get_view_parameter()->wolrd_rectangle );
			m_Model->get_view()->set_viewscale       (io.get_view_parameter()->viewscale       );
			m_Model->get_view()->set_grid_size       (io.get_view_parameter()->grid_xsize, io.get_view_parameter()->grid_ysize);
			m_Model->get_view()->set_grid_visible    (io.get_view_parameter()->grid_visible    );
			
			m_Model->set_snap_to_grid( io.get_view_parameter()->snap_to_grid );
	

//			m_Model->get_view()->set_viewport_window_offset (0, 0);


			m_ViewScrollHelper.initialize(*this);

			m_ViewScrollHelper.set_window(m_cxClientMax, m_cyClientMax, true);


//			m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


			gw::rectangle_t r;


			r = m_Model->get_view()->get_wolrd_rectangle();

			m_ViewScrollHelper.set_contents(r.w()*m_Model->get_view()->get_viewscale(), r.h()*m_Model->get_view()->get_viewscale(), true);
		
			m_Model->get_view()->set_viewport_window_offset(m_ViewScrollHelper.get_view_xoffset(),m_ViewScrollHelper.get_view_yoffset());


			Invalidate();
	

			SetViewPropertyChanged();
		}
	}
	io.destroy();


	//-----------------------------------------------------------------------
	if (false==result)
	{
	}


	return TRUE;
}

BOOL CGWDiagramEditorView::OnFileSave()
{
	//-----------------------------------------------------------------------
/*
	static cx::char_t filter[] = _T("json File(*.json)|*.json|All Files(*.*)|*.*||");

	CFileDialog fd(FALSE, _T(".json"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);


	if (IDOK!=fd.DoModal(*this))
	{
		return TRUE;
	}
*/


	//-----------------------------------------------------------------------
	std::string file_path;


//#if 0
#if defined (DEBUG) || (_DEBUG) 
	file_path = "d:\\a.json";
#else
//	file_path = fd.GetPathName();
	file_path = get_save_file_path(*this);
#endif


	if (file_path.empty())
	{
		return TRUE;
	}


	//-----------------------------------------------------------------------
	cx::bool_t result;


	gw::dgrm::json_document_writer io(file_path);

	
	result = io.create(&GetMyWinApp()->_diagram_widget_entry_collection);
	if (result)
	{
		result = m_Model->write(&io);
	}
	io.destroy();


	//-----------------------------------------------------------------------
	if (false==result)
	{
	}

	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditSelectAll()
{
	m_Model->select_all();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditBringToTop()
{
	m_Model->bring_to_top();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditSendToBottom()
{
	m_Model->send_to_bottom();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditUndo()
{
	m_Model->undo();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditRedo()
{
	m_Model->redo();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditCut()
{
	m_Model->cut();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditCopy()
{
	m_Model->copy();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditPaste()
{
	m_Model->paste();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnDiagramEditDelete()
{
	m_Model->remove();
	return TRUE;
}

BOOL CGWDiagramEditorView::OnCommand(WPARAM wparam, LPARAM lparam)
{
    UINT id = LOWORD(wparam);
    switch (id)
    {
	case IDM_FILE_OPEN:	  return OnFileOpen();
	case IDM_FILE_SAVE:	  return OnFileSave();

	case IDM_DIAGRAM_EDIT_BRING_TO_TOP   : return OnDiagramEditBringToTop   ();
	case IDM_DIAGRAM_EDIT_SEND_TO_BOTTOM : return OnDiagramEditSendToBottom ();
	case IDM_DIAGRAM_EDIT_SELECT_ALL     : return OnDiagramEditSelectAll    ();
	case IDM_DIAGRAM_EDIT_UNDO           : return OnDiagramEditUndo         ();
	case IDM_DIAGRAM_EDIT_REDO           : return OnDiagramEditRedo         ();
	case IDM_DIAGRAM_EDIT_CUT            : return OnDiagramEditCut          ();
	case IDM_DIAGRAM_EDIT_COPY           : return OnDiagramEditCopy         ();
	case IDM_DIAGRAM_EDIT_PASTE          : return OnDiagramEditPaste        ();
	case IDM_DIAGRAM_EDIT_DELETE         : return OnDiagramEditDelete       ();

    default:
		break;
    }

    return FALSE;
}

void CGWDiagramEditorView::SetViewPropertyChanged(void)
{
	if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker)
	{
		GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker->m_DockContainer.m_Wnd.OnViewPropertyChanged(m_Model->get_view());
	}
}

diagram_edit* CGWDiagramEditorView::GetModel (void)
{
	return m_Model;
}
