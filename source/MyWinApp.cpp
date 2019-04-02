/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CMyWinApp::CMyWinApp()
{
}

CMyWinApp::~CMyWinApp()
{
}

//===========================================================================
BOOL CMyWinApp::InitInstance()
{
	gw::drag_data_object_clipboard_format::register_clipboard_format();

	gw::ctrl::add_default_widget_entry(&_control_widget_entry_collection);
	gw::dgrm::add_default_widget_entry(&_diagram_widget_entry_collection);

	//Create the Frame Window
	m_Mainframe.Create(); // throws a CWinException on failure    

	return TRUE;
}


