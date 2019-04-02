/////////////////////////////////////////////////////////////////////////////
//
// File: drop_source.cpp
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
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: drop_source
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
drop_source::drop_source()
{
	_ref_count = 1;
}

drop_source::~drop_source()
{
}

STDMETHODIMP drop_source::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;

	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDropSource))
	{
		*ppvObject = static_cast<IDropSource*>(this);
	}
	else
	{
		return E_NOINTERFACE;
	}

	AddRef();

	return S_OK;
}

STDMETHODIMP_(ULONG) drop_source::AddRef()
{
	return InterlockedIncrement(&_ref_count);
}

STDMETHODIMP_(ULONG) drop_source::Release()
{
	if (InterlockedDecrement(&_ref_count) == 0) 
	{
		delete this;
		return 0;
	}

	return _ref_count;
}

STDMETHODIMP drop_source::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
{
	if (fEscapePressed)
	{
		return DRAGDROP_S_CANCEL;
	}

	if ((grfKeyState & MK_LBUTTON) == 0)
	{
		return DRAGDROP_S_DROP;
	}

	return S_OK;
}

STDMETHODIMP drop_source::GiveFeedback(DWORD dwEffect)
{
	return DRAGDROP_S_USEDEFAULTCURSORS;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
