/////////////////////////////////////////////////////////////////////////////
//
// File: drag_data.cpp
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
cx::bool_t set_drag_data (IDataObject* pDataObject, drag_data_t* pDragData, cx::uint_t cf)
{
	//-----------------------------------------------------------------------
	cx::uint_t  source_size;
	cx::byte_t* source_pointer;

	source_pointer = (cx::byte_t*)pDragData->name.c_str();
	source_size    = pDragData->name.size()+1;


	//-----------------------------------------------------------------------
	HGLOBAL hGlobal;
	

	hGlobal = create_drag_data_hglobal(source_pointer, source_size);
	if (NULL==hGlobal)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	HRESULT hr;


	FORMATETC formatetc;
	STGMEDIUM medium;


	memset(&formatetc, 0, sizeof(formatetc));
	formatetc.cfFormat = cf;
	formatetc.ptd      = NULL;
	formatetc.dwAspect = DVASPECT_CONTENT;
	formatetc.lindex   = -1;
	formatetc.tymed    = TYMED_HGLOBAL;

	memset(&medium, 0, sizeof(medium));
	medium.tymed          = TYMED_HGLOBAL;
	medium.hGlobal        = hGlobal;
	medium.pUnkForRelease = NULL;

	hr = pDataObject->SetData(&formatetc, &medium, TRUE);
	if (hr == S_OK)
	{
		return true;
	}

	GlobalFree(hGlobal); CX_DEBUG_TRACEF(TW_THISCODE, "GlobalFree()");

	return false;
}





/////////////////////////////////////////////////////////////////////////////
//
// Class: drag_data_object_clipboard_format
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
UINT drag_data_object_clipboard_format::_custom_clipboard_format = 0u;

//===========================================================================
drag_data_object_clipboard_format::drag_data_object_clipboard_format()
{
}

drag_data_object_clipboard_format::~drag_data_object_clipboard_format()
{
}

UINT drag_data_object_clipboard_format::register_clipboard_format(std::string name)
{
	_custom_clipboard_format = RegisterClipboardFormat ( name.c_str() );

	return _custom_clipboard_format;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
