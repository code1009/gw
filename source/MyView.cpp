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
CMyView::CMyView()
{
}

CMyView::~CMyView()
{
}

//===========================================================================
