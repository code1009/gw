#ifndef INCLUDED__CX__GW__DRAGDROP__DROP_SOURCE__HPP
#define INCLUDED__CX__GW__DRAGDROP__DROP_SOURCE__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: drop_source.hpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





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
class drop_source : public IDropSource
{
public:
	// IUnknown 가상함수
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	// IDropSource 가상함수
	STDMETHODIMP QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);
	STDMETHODIMP GiveFeedback(DWORD dwEffect);

private:
	LONG _ref_count;

public:
	drop_source();
	virtual ~drop_source();
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


