#ifndef INCLUDED__CX__GW__DRAGDROP__DROP_TARGET__HPP
#define INCLUDED__CX__GW__DRAGDROP__DROP_TARGET__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: drop_target.hpp
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
// Class: drop_target
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class drop_target : public IDropTarget
{
public:
	// IUnknown 가상함수
	STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
	
	// IDropTarget 가상함수
	STDMETHODIMP DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHODIMP DragLeave();
	STDMETHODIMP Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

private:
	LONG    _ref_count;
	BOOL    _support_format;
	HGLOBAL _hglobal;

private:
	UINT _clipboard_format;

private:
	model*   _model;
	window_t _window;

public:
	explicit drop_target(UINT clipboard_format);
	virtual ~drop_target();

private:
	HGLOBAL get_data_object_hglobal (IDataObject *pDataObj, FORMATETC* formatetc);

private:
	void notify_drag_enter (mouse_drag_drop_event* e);
	void notify_drag_over  (mouse_drag_drop_event* e);
	void notify_drag_leave (mouse_drag_drop_event* e);
	void notify_drop       (mouse_drag_drop_event* e);

public:
	virtual model* get_model (void);
	virtual void   set_model (model* model);

	virtual window_t get_window (void);
	virtual void     set_window (window_t window);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


