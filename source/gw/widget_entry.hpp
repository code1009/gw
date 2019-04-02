#ifndef INCLUDED__CX__GW__WIDGET_ENTRY__HPP
#define INCLUDED__CX__GW__WIDGET_ENTRY__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: widget_entry.hpp
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
// Class: widget_entry
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_entry
{
private:
	std::string                   _name;
	std::string                   _description;
	std::string                   _widget_class;
	widget_factory*               _widget_factory;
	widget_event_handler_factory* _widget_event_handler_factory;
	widget_iostream_factory*      _widget_iostream_factory;

public:
	widget_entry(
		std::string                   name                                 , 
		std::string                   description                          , 
		std::string                   widget_class                         , 
		widget_factory*               widget_factory_pointer               , 
		widget_event_handler_factory* widget_event_handler_factory_pointer ,
	    widget_iostream_factory*      widget_iostream_factory_pointer      );
	virtual ~widget_entry();

public:
	std::string                   get_name                         (void);
	std::string                   get_description                  (void);
	std::string                   get_widget_class                 (void);
	widget_factory*               get_widget_factory               (void);
	widget_event_handler_factory* get_widget_event_handler_factory (void);
	widget_iostream_factory*      get_widget_iostream_factory      (void);

private:
	void set(
		std::string                   name                                 , 
		std::string                   description                          , 
		std::string                   widget_class                         , 
		widget_factory*               widget_factory_pointer               , 
		widget_event_handler_factory* widget_event_handler_factory_pointer ,
	    widget_iostream_factory*      widget_iostream_factory_pointer      );

public:
	virtual void delete_instance (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template<typename Twidget, typename Twidget_event_handler, typename Twidget_iostream>
widget_entry* create_widget_entry (std::string name, std::string description = std::string())
{
	widget_entry* we;
	
	
	we = new widget_entry(
		name,
		description,
		Twidget::get_registered_name(),
		new widget_class_factory<typename Twidget>(),
		new widget_event_handler_class_factory<typename Twidget_event_handler>(),
		new widget_iostream_class_factory<typename Twidget_iostream>()
		);


	return we;
}

template<typename Twidget, typename Twidget_event_handler>
widget_entry* create_widget_entry(std::string name, std::string description = std::string())
{
	widget_entry* we;


	we = new widget_entry(
		name,
		description,
		Twidget::get_registered_name(),
		new widget_class_factory<typename Twidget>(),
		new widget_event_handler_class_factory<typename Twidget_event_handler>(),
		new widget_iostream_factory()
		);


	return we;
}

template<typename Twidget>
widget_entry* create_widget_entry(std::string name, std::string description = std::string())
{
	widget_entry* we;


	we = new widget_entry(
		name,
		description,
		Twidget::get_registered_name(),
		new widget_class_factory<typename Twidget>(),
		new widget_event_handler_factory(),
		new widget_iostream_factory()
		);


	return we;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_entry_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_entry_collection
{
private:
	widget_entry_pointer_container_t _container;

public:
	widget_entry_collection();
	virtual ~widget_entry_collection();

public:
	widget_entry_pointer_container_t& get_container(void);

public:
	void delete_container(void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


