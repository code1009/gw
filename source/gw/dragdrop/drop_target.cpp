/////////////////////////////////////////////////////////////////////////////
//
// File: drop_target.cpp
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
/*
http://eternalwindows.jp/ole/oledrag/oledrag01.html
http://eternalwindows.jp/ole/oledrag/oledrag02.html
http://eternalwindows.jp/ole/oledrag/oledrag03.html
*/



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: drop_target
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
drop_target::drop_target(UINT clipboard_format)
{
	_ref_count      = 1;
	_support_format = false;
	_hglobal        = NULL;
	
	_clipboard_format = clipboard_format;

	_model  = CX_NULL_POINTER;
	_window = CX_NULL_POINTER;
}

drop_target::~drop_target()
{
}

STDMETHODIMP drop_target::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;

	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDropTarget))
	{
		*ppvObject = static_cast<IDropTarget*>(this);
	}
	else
	{
		return E_NOINTERFACE;
	}

	AddRef();

	return S_OK;
}

STDMETHODIMP_(ULONG) drop_target::AddRef()
{
	return InterlockedIncrement(&_ref_count);
}

STDMETHODIMP_(ULONG) drop_target::Release()
{
	if (InterlockedDecrement(&_ref_count) == 0) 
	{
		delete this;
		return 0;
	}

	return _ref_count;
}

STDMETHODIMP drop_target::DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	//-----------------------------------------------------------------------
	HRESULT   hr;
	FORMATETC formatetc;


	*pdwEffect = DROPEFFECT_COPY;

	formatetc.cfFormat = _clipboard_format;
	formatetc.ptd      = NULL;
	formatetc.dwAspect = DVASPECT_CONTENT;
	formatetc.lindex   = -1;
	formatetc.tymed    = TYMED_HGLOBAL;

	hr = pDataObj->QueryGetData(&formatetc);
	if (hr != S_OK) 
	{
		*pdwEffect = DROPEFFECT_NONE;

		_support_format = FALSE;

		_hglobal = NULL;

		return S_OK; 
	}


	//-----------------------------------------------------------------------
	_support_format = TRUE;

	CX_DEBUG_TRACEF(TW_THISCODE, "%s:%d,%d", _support_format ? "DROPEFFECT_COPY" : "DROPEFFECT_NONE",pt.x,pt.y);

	_hglobal = get_data_object_hglobal(pDataObj, &formatetc);

	if (_hglobal == NULL)
	{
		_support_format = FALSE;

		CX_DEBUG_TRACEF(CX_TWA_WARNING, "_hglobal is null.");
		*pdwEffect = DROPEFFECT_NONE;

		_hglobal = NULL;

		return S_OK;
	}
	

	//-----------------------------------------------------------------------
	POINT client_pt;


	client_pt.x = pt.x;
	client_pt.y = pt.y;
	ScreenToClient(_window, &client_pt);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=_hglobal);


	mouse_drag_drop_event e;
	

	e._code    = EC_MOUSE_DRAG_ENTER;
	e._point   = get_model()->get_view()->viewport_window_to_world(client_pt.x, client_pt.y);
	e._hglobal = _hglobal;

	notify_drag_enter(&e);


	return S_OK; 
}

STDMETHODIMP drop_target::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	//-----------------------------------------------------------------------
	*pdwEffect = DROPEFFECT_COPY;
	
	if (!_support_format)
	{
		*pdwEffect = DROPEFFECT_NONE;

		_hglobal = NULL;

		return S_OK;
	}


	//-----------------------------------------------------------------------
//	CX_DEBUG_TRACEF(TW_THISCODE, "%s:%d,%d", _support_format ? "DROPEFFECT_COPY" : "DROPEFFECT_NONE",pt.x,pt.y);


	if (_hglobal == NULL)
	{
		CX_DEBUG_TRACEF(CX_TWA_WARNING, "_hglobal is null.");
		*pdwEffect = DROPEFFECT_NONE;

		_hglobal = NULL;

		return S_OK;
	}


	//-----------------------------------------------------------------------
	POINT client_pt;


	client_pt.x = pt.x;
	client_pt.y = pt.y;
	ScreenToClient(_window, &client_pt);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=_hglobal);


	mouse_drag_drop_event e;

	
	e._code    = EC_MOUSE_DRAG_OVER;
	e._point   = get_model()->get_view()->viewport_window_to_world(client_pt.x, client_pt.y);
	e._hglobal = _hglobal;

	notify_drag_over(&e);

	return S_OK;
}

STDMETHODIMP drop_target::DragLeave()
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%s", _support_format ? "DROPEFFECT_COPY" : "DROPEFFECT_NONE");


	_hglobal = NULL;


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());
	CX_DEBUG_ASSERT(CX_NULL_POINTER==_hglobal);


	mouse_drag_drop_event e;
	

	e._code     = EC_MOUSE_DRAG_LEAVE;
	e._point._x = static_cast<coordinates_t>(0);
	e._point._y = static_cast<coordinates_t>(0);
	e._hglobal  = _hglobal;

	notify_drag_leave(&e);

	return S_OK;
}

STDMETHODIMP drop_target::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	//-----------------------------------------------------------------------
	HRESULT   hr;
	FORMATETC formatetc;
	

	*pdwEffect = DROPEFFECT_COPY;

	formatetc.cfFormat = _clipboard_format;
	formatetc.ptd      = NULL;
	formatetc.dwAspect = DVASPECT_CONTENT;
	formatetc.lindex   = -1;
	formatetc.tymed    = TYMED_HGLOBAL;
	
	hr = pDataObj->QueryGetData(&formatetc);
	if (hr != S_OK) 
	{
		*pdwEffect = DROPEFFECT_NONE;

		_hglobal = NULL;

		return E_FAIL;
	}


	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%s:%d,%d", _support_format ? "DROPEFFECT_COPY" : "DROPEFFECT_NONE", pt.x, pt.y);


//	_hglobal = get_data_object_hglobal(pDataObj, &formatetc);
	if (_hglobal == NULL)
	{
		CX_DEBUG_TRACEF(CX_TWA_WARNING, "_hglobal is null.");

		*pdwEffect = DROPEFFECT_NONE;

		_hglobal = NULL;

		return E_FAIL;
	}


	//-----------------------------------------------------------------------
	POINT client_pt;


	client_pt.x = pt.x;
	client_pt.y = pt.y;
	ScreenToClient(_window, &client_pt);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=_hglobal);


	mouse_drag_drop_event e;
	

	e._code    = EC_MOUSE_DROP;
	e._point   = get_model()->get_view()->viewport_window_to_world(client_pt.x, client_pt.y);
	e._hglobal = _hglobal;

	notify_drop(&e);


	SendMessage(_window, WM_MOUSEACTIVATE, 0, 0);

	return S_OK;
}

//===========================================================================
HGLOBAL drop_target::get_data_object_hglobal (IDataObject *pDataObj, FORMATETC* formatetc)
{
	//-----------------------------------------------------------------------
	HRESULT   hr;
	STGMEDIUM medium;


	hr = pDataObj->GetData(formatetc, &medium);
	if (FAILED(hr)) 
	{
		return NULL;
	}


	//-----------------------------------------------------------------------
	HGLOBAL hGlobal;


	hGlobal = medium.hGlobal;


	//-----------------------------------------------------------------------
	/*
	cx::byte_t* source_pointer;
	cx::uint_t  source_size;
	
	
	source_pointer = (cx::byte_t*)GlobalLock(hGlobal);
	source_size    = GlobalSize(hGlobal);
	
	GlobalUnlock(medium.hGlobal);
	*/

	return hGlobal;
}

//===========================================================================
model* drop_target::get_model (void)
{
	return _model;
}

void drop_target::set_model (model* m)
{
	_model = m;
}

window_t drop_target::get_window (void)
{
	return _window;
}

void drop_target::set_window (window_t window)
{
	_window = window;
}

void drop_target::notify_drag_enter (mouse_drag_drop_event* e)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());

	get_model()->on_event(e);
}

void drop_target::notify_drag_over (mouse_drag_drop_event* e)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());

	get_model()->on_event(e);
}

void drop_target::notify_drag_leave (mouse_drag_drop_event* e)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());

	get_model()->on_event(e);
}

void drop_target::notify_drop (mouse_drag_drop_event* e)
{
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=get_model());

	get_model()->on_event(e);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
