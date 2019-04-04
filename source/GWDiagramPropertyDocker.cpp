/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramPropertyDockerWnd::CGWDiagramPropertyDockerWnd()
{
	m_PropGridCtlID = 1000;
	m_hPropGridCtl  = NULL;

	m_ActivatedProperty = ACTIVATED_PROPERTY_NONE;

	m_ViewPropertyAccessor = CX_NULL_POINTER;

	m_View =  CX_NULL_POINTER;
	m_ViewPropertyChanged = false;

	m_Diagram = CX_NULL_POINTER;
	m_DiagramPropertyChanged = false;
}

CGWDiagramPropertyDockerWnd::~CGWDiagramPropertyDockerWnd()
{
}

//===========================================================================
void CGWDiagramPropertyDockerWnd::PreCreate(CREATESTRUCT& cs)
{
	CWnd::PreCreate(cs);
	
//	cs.style     |= (WS_VSCROLL | WS_HSCROLL);
	cs.style     |= WS_CLIPCHILDREN;
//	cs.dwExStyle |=  WS_EX_CLIENTEDGE;
}

int CGWDiagramPropertyDockerWnd::OnCreate(CREATESTRUCT& cs)
{
	//-----------------------------------------------------------------------
	UNREFERENCED_PARAMETER(cs);


	//-----------------------------------------------------------------------
#if 0
	m_hPropGridCtl = ::CreateWindow(
		"PropGridCtl", 
		"", 
		WS_VISIBLE|WS_CHILD|WS_TABSTOP|WS_CLIPCHILDREN, 
		0,0,1,1,
		*this,
		(HMENU)m_PropGridCtlID,
		GetMyWinApp()->GetInstanceHandle(),
		0
		);
#endif
	m_hPropGridCtl = New_PropertyGrid(*this, m_PropGridCtlID);

	
	//-----------------------------------------------------------------------
	cx::int_t pixels_per_logical_inch;
	HDC hdc;
	cx::float_t scale;
	cx::int_t   height;

	hdc = ::GetWindowDC(m_hPropGridCtl);
	pixels_per_logical_inch = GetDeviceCaps(hdc, LOGPIXELSY);
	::ReleaseDC(m_hPropGridCtl, hdc);

	scale = pixels_per_logical_inch/96.0f;

	height = PropGrid_GetItemHeight(m_hPropGridCtl);
	PropGrid_SetItemHeight(m_hPropGridCtl, static_cast<cx::int_t>(height*scale));


	//-----------------------------------------------------------------------
	PropGrid_ShowToolTips            (m_hPropGridCtl,FALSE);
	PropGrid_ShowPropertyDescriptions(m_hPropGridCtl,FALSE);

	PropGrid_SetFlatStyleChecks(m_hPropGridCtl,TRUE);
	
	PropGrid_ExpandAllCatalogs (m_hPropGridCtl);
	

	//-----------------------------------------------------------------------
	m_ViewPropertyAccessor = new view_property_accessor(m_hPropGridCtl);

	LoadEntry();


	//-----------------------------------------------------------------------
	SetTimer(1, 500, NULL);

	m_ActivatedProperty      = ACTIVATED_PROPERTY_NONE;
	m_ViewPropertyChanged    = false;
	m_DiagramPropertyChanged = false;


	//-----------------------------------------------------------------------
	m_UserCustomBrowseFlag = 0u;

	return 0;
}

void CGWDiagramPropertyDockerWnd::OnDestroy()
{
	KillTimer(1);

	
	DeleteEntryContainer();
	
	
	delete m_ViewPropertyAccessor;
	m_ViewPropertyAccessor = CX_NULL_POINTER;


	::DestroyWindow(m_hPropGridCtl);
	m_hPropGridCtl = NULL;
}

LRESULT CGWDiagramPropertyDockerWnd::OnNotify(WPARAM wparam, LPARAM lparam)
{
	UINT    id    = static_cast<UINT>(wparam);
	LPNMHDR NmHdr = reinterpret_cast<LPNMHDR>(lparam);


	if (m_PropGridCtlID == id )
	{
		if ( NmHdr->code==PGN_PROPERTYCHANGE )
		{
			LPNMPROPGRID   nmp  = (LPNMPROPGRID)NmHdr;
			LPPROPGRIDITEM item = PropGrid_GetItemData(NmHdr->hwndFrom, nmp->iIndex);


			switch (m_ActivatedProperty)
			{
			case ACTIVATED_PROPERTY_VIEW:    SetViewPropertyFromControl   (nmp->iIndex, item); break;
			case ACTIVATED_PROPERTY_DIAGRAM: SetDiagramPropertyFromControl(nmp->iIndex, item); break;
			default:
				break;
			}

			return 1;
		}
		if ( NmHdr->code==PGN_USERCUSTOMBROWSE )
		{
			LPNMPROPGRIDUSERCUSTOM nmp  = (LPNMPROPGRIDUSERCUSTOM)NmHdr;
			LPPROPGRIDITEM         item = PropGrid_GetItemData(NmHdr->hwndFrom, nmp->iIndex);


			CMyDialog dlg(IDW_INPUT);

			
			m_UserCustomBrowseFlag = 1u;

			if (IDOK==dlg.DoModal(m_hPropGridCtl))
			{
				// Dialog 가 떠있는 상황에서 문서 ViewWindow를 닫거나 
				// 다른 문서 ViewWindow를 선택할경우 
				// 유효하지 않은 item과 object가 될수 있음
				if (nmp->iIndex!=PropGrid_GetCurSel(m_hPropGridCtl))
				{
					MessageBeep(MB_ICONSTOP);
					//MessageBox("취소되었습니다!", "확인", MB_OK);
					return 0;
				}
				if (m_UserCustomBrowseFlag != 1u)
				{
					MessageBeep(MB_ICONSTOP);
					//MessageBox("취소되었습니다.", "확인", MB_OK);
					return 0;
				}

				std::string catalog = "test";
				std::string name    = "test1";   
				std::string value   = "1234567";


				if (nmp->iIndex==11)
				{
					name = "test2";   
				}


				value = (LPTSTR)item->lpCurValue;
				value = dlg.m_InputValue;


//				item->lpszCatalog   = (LPTSTR)catalog.c_str();
//				item->lpszPropName  = (LPTSTR)name.c_str();
//				item->lpszzCmbItems = NULL;
//				item->lpszPropDesc  = NULL;
				item->lpCurValue    = (LPARAM)value.c_str();
//				item->lpUserData    = NULL;
//				item->iItemType     = PIT_USERCUSTOM;
				PropGrid_SetItemData (m_hPropGridCtl, nmp->iIndex, item);

				// TODO: 객체 값 변경
				// object->set_name_value(value);
			}
		}
	}

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam)
// Respond to a mouse click on the window
{
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "SetFocus()");

	SetFocus();
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

		
		if ( ::IsWindow(m_hPropGridCtl) )
		{
			::MoveWindow  (m_hPropGridCtl, 0,0,m_cxClientMax, m_cyClientMax, TRUE);
			::RedrawWindow(m_hPropGridCtl, NULL, NULL, RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW);
		}
	}

	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::OnTimer(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (m_ActivatedProperty)
	{
	case ACTIVATED_PROPERTY_VIEW:
		{
			if (m_ViewPropertyChanged)
			{
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "ACTIVATED_PROPERTY_VIEW");

				m_ViewPropertyChanged = false;

				SetViewPropertyToControl();
			}
		}
		break;

	case ACTIVATED_PROPERTY_DIAGRAM:
		{
			if (m_DiagramPropertyChanged)
			{
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "ACTIVATED_PROPERTY_DIAGRAM");

				m_DiagramPropertyChanged = false;

				SetDiagramPropertyToControl();
			}
		}
		break;

	default:
		CX_DEBUG_TRACEF(CX_TWA_NORMAL, "ACTIVATED_PROPERTY_NONE");
		break;
	}


	return 0;
}

LRESULT CGWDiagramPropertyDockerWnd::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT lResult;


	switch (msg)
	{
	case WM_MOUSEACTIVATE:  lResult = OnMouseActivate (msg, wparam, lparam); break;
	case WM_SIZE:           lResult = OnSize          (msg, wparam, lparam); break;
	case WM_TIMER:          lResult = OnTimer         (msg, wparam, lparam); break;

	default:
		lResult = WndProcDefault(msg, wparam, lparam);
		break;
	}


	return lResult;
}

//===========================================================================
void CGWDiagramPropertyDockerWnd::OnCloseView (gw::view* view_pointer)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "view_pointer=%p", view_pointer);


	//-----------------------------------------------------------------------
	cx::uint_t reset_view    = false;
	cx::uint_t reset_diagram = false;


	if (m_View == view_pointer)
	{
		m_View=CX_NULL_POINTER;
		m_ViewPropertyChanged = false;

		reset_view = true;
	}


	if (m_Diagram)
	{
		if (m_Diagram->get_model()->get_view()==view_pointer)
		{
			m_Diagram = CX_NULL_POINTER;
			m_DiagramPropertyChanged = false;

			reset_diagram = true;
		}
	}



	cx::bool_t reset = false;


	if (ACTIVATED_PROPERTY_VIEW==m_ActivatedProperty)
	{
		if (reset_view)
		{
			if (::IsWindow(m_hPropGridCtl))
			{
				PropGrid_ResetContent(m_hPropGridCtl);
			}
			reset = true;
		}
	}

	if (ACTIVATED_PROPERTY_DIAGRAM==m_ActivatedProperty)
	{
		if (reset_diagram)
		{
			if (::IsWindow(m_hPropGridCtl))
			{
				PropGrid_ResetContent(m_hPropGridCtl);
			}
			reset = true;
		}
	}


	if (reset)
	{
		m_ActivatedProperty = ACTIVATED_PROPERTY_NONE;

		m_UserCustomBrowseFlag = 0u;
	}
}

void CGWDiagramPropertyDockerWnd::OnActivatedView(gw::view* view_pointer)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "view_pointer=%p", view_pointer);


	//-----------------------------------------------------------------------
	if (m_View == view_pointer)
	{
		return;
	}

	
	m_View = view_pointer;

	
	if (ACTIVATED_PROPERTY_DIAGRAM==m_ActivatedProperty)
	{
		if (m_Diagram)
		{
			if (m_Diagram->get_model()->get_view()==m_View)
			{
				return;
			}
		}
	}


	LoadViewPropertyToControl();
}

void CGWDiagramPropertyDockerWnd::OnViewPropertyChanged(gw::view* view_pointer)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "view_pointer=%p", view_pointer);


	//-----------------------------------------------------------------------
	if (view_pointer!=m_View)
	{
		return;
	}


	if (CX_NULL_POINTER==m_View)
	{
		return;
	}


	m_ViewPropertyChanged = true;
}

//===========================================================================
void CGWDiagramPropertyDockerWnd::LoadViewPropertyToControl (void)
{
	m_UserCustomBrowseFlag = 0u;

	PropGrid_ResetContent(m_hPropGridCtl);
	m_ActivatedProperty = ACTIVATED_PROPERTY_NONE;


	m_ViewPropertyAccessor->set_object(m_View);
	if (CX_NULL_POINTER==m_View)
	{
		return;
	}


	m_ViewPropertyAccessor->load_property_to_control();


	PropGrid_ExpandAllCatalogs (m_hPropGridCtl);
	//PropGrid_SetCurSel(m_hPropGridCtl,0);


	m_ActivatedProperty = ACTIVATED_PROPERTY_VIEW;
}

void CGWDiagramPropertyDockerWnd::SetViewPropertyToControl (void)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m_View);
	if (CX_NULL_POINTER==m_View)
	{
		return;
	}


	m_ViewPropertyAccessor->set_object(m_View);
	m_ViewPropertyAccessor->set_property_to_control();
}

void CGWDiagramPropertyDockerWnd::SetViewPropertyFromControl(cx::int_t index, LPPROPGRIDITEM item)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m_View);
	if (CX_NULL_POINTER==m_View)
	{
		return;
	}


	m_ViewPropertyAccessor->set_object(m_View);
	m_ViewPropertyAccessor->set_property_from_control(index, item);
}

//===========================================================================
void CGWDiagramPropertyDockerWnd::OnSelectChanged(gw::dgrm::diagram* diagram_pointer)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "diagram_pointer=%p", diagram_pointer);


	//-----------------------------------------------------------------------
	m_Diagram = diagram_pointer;


	if (CX_NULL_POINTER==m_Diagram)
	{
		LoadViewPropertyToControl();
		return;
	}

	LoadDiagramPropertyToControl();
}

void CGWDiagramPropertyDockerWnd::OnDiagramPropertyChanged(gw::dgrm::diagram* diagram_pointer)
{
	//-----------------------------------------------------------------------
//	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "diagram_pointer=%p", diagram_pointer);


	//-----------------------------------------------------------------------
	if (diagram_pointer!=m_Diagram)
	{
		return;
	}


	if (CX_NULL_POINTER==m_Diagram)
	{
		return;
	}


	m_DiagramPropertyChanged = true;
}

//===========================================================================
void CGWDiagramPropertyDockerWnd::LoadDiagramPropertyToControl(void)
{
	m_UserCustomBrowseFlag = 0u;

	PropGrid_ResetContent(m_hPropGridCtl);
	m_ActivatedProperty = ACTIVATED_PROPERTY_NONE;


	if (CX_NULL_POINTER==m_Diagram)
	{
		return;
	}


	property_accessor* pa = FindEntry(m_Diagram->get_class());


	if (pa)
	{
		pa->set_object(m_Diagram);
		pa->load_property_to_control();


		PropGrid_ExpandAllCatalogs (m_hPropGridCtl);
		//PropGrid_SetCurSel(m_hPropGridCtl,0);


		m_ActivatedProperty = ACTIVATED_PROPERTY_DIAGRAM;
	}
}

void CGWDiagramPropertyDockerWnd::SetDiagramPropertyToControl(void)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m_Diagram);
	if (CX_NULL_POINTER==m_Diagram)
	{
		return;
	}

	
	property_accessor* pa = FindEntry(m_Diagram->get_class());


	if (pa)
	{
		pa->set_object(m_Diagram);
		pa->set_property_to_control();
	}
}

void CGWDiagramPropertyDockerWnd::SetDiagramPropertyFromControl(cx::int_t index, LPPROPGRIDITEM item)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m_Diagram);
	if (CX_NULL_POINTER==m_Diagram)
	{
		return;
	}

	
	property_accessor* pa = FindEntry(m_Diagram->get_class());


	if (pa)
	{
		pa->set_object(m_Diagram);
		pa->set_property_from_control(index, item);
	}
}

//===========================================================================
named_property_accessor_pointer_container_t& CGWDiagramPropertyDockerWnd::GetEntryContainer(void)
{
	return m_EntryContainer;
}

void CGWDiagramPropertyDockerWnd::DeleteEntryContainer (void)
{
	named_property_accessor_pointer_container_t::iterator i;
	property_accessor* e;
	

	for (i =GetEntryContainer().begin(); 
		 i!=GetEntryContainer().end(); 
		 i++)
	{
		e = (*i).second;

		delete e;
	}

	GetEntryContainer().clear();
}

//===========================================================================
property_accessor* CGWDiagramPropertyDockerWnd::FindEntry (std::string name)
{
	named_property_accessor_pointer_container_t::iterator i;
	property_accessor* e;


	e = CX_NULL_POINTER;


	i = GetEntryContainer().find(name);
	if (i!=GetEntryContainer().end())
	{
		e = (*i).second;
	}

	return e;
}

cx::bool_t CGWDiagramPropertyDockerWnd::AddEntry (std::string name, property_accessor* e)
{
	named_property_accessor_pointer_container_t::iterator i;


	i = GetEntryContainer().find(name);
	if (i != GetEntryContainer().end())
	{
		return false;
	}


	GetEntryContainer()[name] = e;

	return true;
}


//===========================================================================
void CGWDiagramPropertyDockerWnd::LoadEntry (void)
{
	AddEntry(gw::dgrm::rectangle_shape::get_registered_name(), new rectangle_shape_property_accessor(m_hPropGridCtl));
	AddEntry(gw::dgrm::straight_line  ::get_registered_name(), new straight_line_property_accessor  (m_hPropGridCtl));	
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramPropertyDockContainer::CGWDiagramPropertyDockContainer()
{
	SetView        (m_Wnd); 
	SetDockCaption (_T("속성"));
	SetTabText     (_T("속성"));
	SetTabIcon     (IDI_DOCKER);
} 

CGWDiagramPropertyDockContainer::~CGWDiagramPropertyDockContainer()
{
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CGWDiagramPropertyDocker::CGWDiagramPropertyDocker()
{
	//-----------------------------------------------------------------------
	GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker = this;


	//-----------------------------------------------------------------------
	SetView     (m_DockContainer);
//	SetBarWidth (4);
}

CGWDiagramPropertyDocker::~CGWDiagramPropertyDocker()
{
	//-----------------------------------------------------------------------
	if (GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker == this)
	{
		GetMyWinApp()->GetMainFrame()->m_DiagramPropertyDocker = CX_NULL_POINTER;
	}
}
