#ifndef INCLUDED__CX__GW__DRAGDROP__DRAG_DATA_OBJECT__HPP
#define INCLUDED__CX__GW__DRAGDROP__DRAG_DATA_OBJECT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: drag_drag_data_object.hpp
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
// Class: drag_data_object
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class drag_data_object : public IDataObject, public IEnumFORMATETC
{
public:
	// IUnknown 가상함수
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	// IDataObject 가상함수
	STDMETHODIMP GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium);
	STDMETHODIMP GetDataHere(FORMATETC *pformatetc, STGMEDIUM *pmedium);
	STDMETHODIMP QueryGetData(FORMATETC *pformatetc);
	STDMETHODIMP GetCanonicalFormatEtc(FORMATETC *pformatectIn, FORMATETC *pformatetcOut);
	STDMETHODIMP SetData(FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease);
	STDMETHODIMP EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc);
	STDMETHODIMP DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection);
	STDMETHODIMP DUnadvise(DWORD dwConnection);
	STDMETHODIMP EnumDAdvise(IEnumSTATDATA **ppenumAdvise);
	
	// IEnumFORMATETC 가상함수
	STDMETHODIMP Next(ULONG celt, FORMATETC *rgelt, ULONG *pceltFetched);
	STDMETHODIMP Skip(ULONG celt);
	STDMETHODIMP Reset(VOID);
	STDMETHODIMP Clone(IEnumFORMATETC **ppenum);

private:
	LONG    _ref_count;
	ULONG   _enum_count;
	HGLOBAL _hglobal;

private:
	UINT _clipboard_format;

public:
	explicit drag_data_object(UINT clipboard_format);
	virtual ~drag_data_object();
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


