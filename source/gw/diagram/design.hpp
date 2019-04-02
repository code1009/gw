#ifndef INCLUDED__CX__GW__DIAGRAM__DESIGN__HPP
#define INCLUDED__CX__GW__DIAGRAM__DESIGN__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: design.hpp
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
namespace dgrm
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: design
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class design : public model
{
private:
	diagram_creator _diagram_creator;

public:
	design();
	virtual ~design();

	// model
public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual void on_event (event* e);

	virtual void on_widget_mouse_clicked   (widget_mouse_event* e);
	virtual void on_widget_mouse_dbclicked (widget_mouse_event* e);

	// design
public:
	virtual void on_diagram_property_changed (diagram_event* e);

public:
	virtual diagram_mode_t get_diagram_mode (void);

public:
	virtual diagram_creator* get_diagram_creator (void);

public:
	virtual diagram* cast_diagram (widget* w);
	virtual anchor*  cast_anchor  (widget* w);

public:
	virtual void clear (void);

public:
	virtual cx::bool_t read  (document_reader* io);
	virtual cx::bool_t write (document_writer* io);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


