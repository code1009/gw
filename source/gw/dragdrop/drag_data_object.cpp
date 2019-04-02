/////////////////////////////////////////////////////////////////////////////
//
// File: drag_data_object.cpp
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
//
// Class: drag_data_object
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
drag_data_object::drag_data_object(UINT clipboard_format)
{
	_ref_count  = 1;
	_enum_count = 0;
	_hglobal    = NULL;

	_clipboard_format = clipboard_format;
}

drag_data_object::~drag_data_object()
{
	if (_hglobal != NULL)
	{
		GlobalFree(_hglobal); CX_DEBUG_TRACEF(TW_THISCODE, "GlobalFree()");
		_hglobal = NULL;
	}
}

STDMETHODIMP drag_data_object::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;

	if      (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDataObject))
	{
		*ppvObject = static_cast<IDataObject*>(this);
	}
	else if (IsEqualIID(riid, IID_IEnumFORMATETC))
	{
		*ppvObject = static_cast<IEnumFORMATETC*>(this);
	}
	else
	{
		return E_NOINTERFACE;
	}

	AddRef();
	
	return S_OK;
}

STDMETHODIMP_(ULONG) drag_data_object::AddRef()
{
	return InterlockedIncrement(&_ref_count);
}

STDMETHODIMP_(ULONG) drag_data_object::Release()
{
	if (InterlockedDecrement(&_ref_count) == 0) 
	{
		delete this;
		return 0;
	}

	return _ref_count;
}

STDMETHODIMP drag_data_object::GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium)
{
	if (pformatetcIn->cfFormat == _clipboard_format) 
	{
		pmedium->tymed          = TYMED_HGLOBAL;
		pmedium->hGlobal        = _hglobal;
		pmedium->pUnkForRelease = NULL;

		return S_OK;
	}

	return E_FAIL;
}

STDMETHODIMP drag_data_object::GetDataHere(FORMATETC *pformatetc, STGMEDIUM *pmedium)
{
	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::QueryGetData(FORMATETC *pformatetc)
{
	if (pformatetc->cfFormat == _clipboard_format)
	{
		return S_OK;
	}

	return S_FALSE;
}

STDMETHODIMP drag_data_object::GetCanonicalFormatEtc(FORMATETC *pformatectIn, FORMATETC *pformatetcOut)
{
	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::SetData(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease)
{
	if (pformatetc->cfFormat == _clipboard_format) 
	{
		if (_hglobal != NULL) 
		{
			GlobalFree(_hglobal); CX_DEBUG_TRACEF(TW_THISCODE, "GlobalFree()");
			_hglobal = NULL;
		}
		

		HGLOBAL hGlobal;
		
		
		hGlobal = clone_drag_data_hglobal(pmedium->hGlobal);
		
		_hglobal = hGlobal;


		if (fRelease)
		{
			GlobalFree(pmedium->hGlobal); CX_DEBUG_TRACEF(TW_THISCODE, "GlobalFree()");
		}


		return S_OK;
	}

	return E_FAIL;
}

STDMETHODIMP drag_data_object::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc)
{
	if (dwDirection == DATADIR_GET)
	{
		return QueryInterface(IID_PPV_ARGS(ppenumFormatEtc));
	}

	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::DUnadvise(DWORD dwConnection)
{
	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::EnumDAdvise(IEnumSTATDATA **ppenumAdvise)
{
	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::Next(ULONG celt, FORMATETC *rgelt, ULONG *pceltFetched)
{
	FORMATETC formatetc[] = 
	{
		{_clipboard_format, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL}
	};


	if (_enum_count >= 1)
	{
		return S_FALSE;
	}

	*rgelt = formatetc[_enum_count];

	if (pceltFetched != NULL)
	{
		*pceltFetched = 1;
	}

	_enum_count++;

	return S_OK;
}

STDMETHODIMP drag_data_object::Skip(ULONG celt)
{
	return E_NOTIMPL;
}

STDMETHODIMP drag_data_object::Reset(VOID)
{
	_enum_count = 0;

	return S_OK;
}

STDMETHODIMP drag_data_object::Clone(IEnumFORMATETC **ppenum)
{
	return E_NOTIMPL;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
