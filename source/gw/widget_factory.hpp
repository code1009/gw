#ifndef INCLUDED__CX__GW__WIDGET_FACTORY__HPP
#define INCLUDED__CX__GW__WIDGET_FACTORY__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: widget_factory.hpp
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
// Class: widget_factory
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_factory
{
public:
	widget_factory();
	virtual ~widget_factory();

public:
	virtual widget* create_instance(void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_class_factory<T>
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template<class T>
class widget_class_factory : public widget_factory
{
public:
	virtual widget* create_instance(void)
	{
		typename T* instance;

		instance = new T();

		return instance;
	}
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_event_handler_factory
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_event_handler_factory
{
public:
	widget_event_handler_factory();
	virtual ~widget_event_handler_factory();

public:
	virtual widget_event_handler* create_instance(void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_event_handler_class_factory<T>
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template<class T>
class widget_event_handler_class_factory : public widget_event_handler_factory
{
public:
	virtual widget_event_handler* create_instance(void)
	{
		typename T* instance;

		instance = new T();

		return instance;
	}
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_iostream_factory
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_iostream_factory
{
public:
	widget_iostream_factory();
	virtual ~widget_iostream_factory();

public:
	virtual widget_iostream* create_instance(void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_event_handler_class_factory<T>
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template<class T>
class widget_iostream_class_factory : public widget_iostream_factory
{
public:
	virtual widget_iostream* create_instance(void)
	{
		typename T* instance;

		instance = new T();

		return instance;
	}
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


