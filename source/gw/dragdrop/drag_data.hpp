#ifndef INCLUDED__CX__GW__DRAGDROP__DRAG_DATA__HPP
#define INCLUDED__CX__GW__DRAGDROP__DRAG_DATA__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: drag_data.hpp
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
//===========================================================================
typedef struct _drag_data_t 
{ 
	std::string name;
}
drag_data_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cx::bool_t set_drag_data (IDataObject* pDataObject, drag_data_t* pDragData, cx::uint_t cf);



/////////////////////////////////////////////////////////////////////////////
//
// Class: drag_data_object_clipboard_format
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class drag_data_object_clipboard_format
{
private:
	static UINT _custom_clipboard_format;

public:
	drag_data_object_clipboard_format();
	virtual ~drag_data_object_clipboard_format();

public:
	static UINT register_clipboard_format (std::string name="gw.widget={4EF1BA30-54D7-4F6F-A169-0B10005E9F08}");
	static UINT get_clipboard_format (void)    { return _custom_clipboard_format; }
	static void set_clipboard_format (UINT cf) { _custom_clipboard_format = cf;   }
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


