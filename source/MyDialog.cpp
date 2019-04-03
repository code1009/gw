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
CMyDialog::CMyDialog(UINT resID) : CDialog(resID)
{
}

CMyDialog::CMyDialog(LPCTSTR resName) : CDialog(resName)
{
}

CMyDialog::~CMyDialog()
{
}

INT_PTR CMyDialog::DialogProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
//  switch (msg)
//  {
//      //Additional messages to be handled go here
//  }

    // Pass unhandled messages on to parent DialogProc
    return DialogProcDefault(msg, wparam, lparam); 
}

BOOL CMyDialog::OnCommand(WPARAM wparam, LPARAM lparam)
{
    UNREFERENCED_PARAMETER(lparam);

    UINT id = LOWORD(wparam);
    switch (id)
    {
	case IDOK:
		break;
    }

    return FALSE;
}

void CMyDialog::OnDestroy()
{
    CDialog::OnDestroy();
}

BOOL CMyDialog::OnInitDialog()
{
    // Set the Icon
    SetIconLarge(IDW_MAIN);
    SetIconSmall(IDW_MAIN);

    return TRUE;
}

void CMyDialog::OnOK()
{
	CString v = GetDlgItemText(IDC_EDIT1);


    m_InputValue = v.c_str();

    CDialog::OnOK();
}
