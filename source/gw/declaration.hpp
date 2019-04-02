#ifndef INCLUDED__CX__GW__DECLARATION__HPP
#define INCLUDED__CX__GW__DECLARATION__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: declaration.hpp
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
class model;

class resource;
class view;
class window_event_handler;

class event;
	class mouse_event;
	class mouse_drag_drop_event;
	class widget_mouse_event;

class widget;
class widget_collection;
class widget_event_handler;
class named_widget_event_handler_collection;

class widget_iostream;
class named_widget_iostream_collection;

class document_reader;
class document_writer;

class widget_factory;
class widget_event_handler_factory;
class widget_iostream_factory;

class widget_entry;
class widget_entry_collection; // dtor(): 소유하고 있는 instance 호출



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef std::vector<widget*>                         widget_pointer_container_t;
typedef std::map<std::string, widget_event_handler*> named_widget_event_handler_pointer_container_t;
typedef std::vector<widget_entry*>                   widget_entry_pointer_container_t;

typedef std::map<std::string, widget_iostream*>      named_widget_iostream_pointer_container_t;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define CX_GW_NO_RTTI_SUPPORT

//===========================================================================
#if defined (CX_GW_NO_RTTI_SUPPORT)

template<typename T1, typename T2>
typename T1 cx_gw_dynamic_cast(typename T2 p)
{
	return static_cast<typename T1>(p);
}

#else

#define cx_cx_gw_dynamic_cast dynamic_cast

#endif



//===========================================================================
#define CX_GW_RESOURCE_MAX_NAME 1024





#endif


