/////////////////////////////////////////////////////////////////////////////
//
// File: drag_data_hglobal.cpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//
// Headers
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "../header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 0
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
HGLOBAL create_drag_data_hglobal (cx::pointer_t source_pointer, cx::uint_t source_size, cx::uint_t flags)
{
	// flags = GHND | GMEM_SHARE

	HGLOBAL hGlobal;
	LPVOID  pointer;
	

	hGlobal = GlobalAlloc(flags, source_size);
	CX_DEBUG_TRACEF(TW_THISCODE, "GlobalAlloc()");
	if (NULL==hGlobal)
	{
		return NULL;
	}

	pointer = GlobalLock(hGlobal);
	if ( NULL == pointer )
	{
		GlobalFree ( hGlobal ); CX_DEBUG_TRACEF(TW_THISCODE, "GlobalFree()");
		return NULL;
	}

	memcpy (pointer, source_pointer, source_size);

	GlobalUnlock(hGlobal);


	return hGlobal;
}

//===========================================================================
HGLOBAL clone_drag_data_hglobal (HGLOBAL source_hglobal, cx::uint_t flags)
{
	HGLOBAL hglobal;

	cx::uint_t    source_size;
	cx::pointer_t source_pointer;


	source_size    = GlobalSize(source_hglobal);
	source_pointer = GlobalLock(source_hglobal);
	if ( NULL == source_pointer )
	{
		return NULL;
	}

	hglobal = create_drag_data_hglobal(source_pointer, source_size, flags);

	GlobalUnlock(source_hglobal);

	return hglobal;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
