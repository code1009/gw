#ifndef INCLUDED__CX__GW__WIDGET__HPP
#define INCLUDED__CX__GW__WIDGET__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: widget.hpp
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
// Class: widget_collection
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_collection
{
private:
	widget_pointer_container_t _container;

public:
	widget_collection();
	virtual ~widget_collection();

public:
	virtual widget_pointer_container_t& get_container (void);

public:
	virtual void delete_container (void);

public:
	virtual void set_model  (model* model);
	virtual void set_parent (widget* parent);
	virtual void initialize (void);
	virtual void move       (point_t offset);	
	virtual void draw       (void);

public:
	virtual cx::bool_t is_in_collection (widget* w);

public:
	virtual widget* find (widget* x, point_t p);
	virtual widget* find (point_t p);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget
{
private:
	model* _model;

private:
	std::string        _name;
	point_container_t  _point_container;
	widget_collection  _child;
	widget*            _parent;

public:
	widget();
	virtual ~widget();

	//--------------------------------------------------------------------------
public:
	static std::string get_registered_name (void);

	//--------------------------------------------------------------------------
public:
	virtual model* get_model (void);
	virtual void   set_model (model* model);

public:
	virtual std::string get_class (void);

public:
	virtual std::string get_name  (void);
	virtual void        set_name  (std::string name);

public:
	virtual widget_collection* get_child (void);

public:
	virtual widget* get_parent (void);
	virtual void    set_parent (widget* parent);

public:
	virtual void delete_instance (void);

	//--------------------------------------------------------------------------
public:
	virtual void initialize (void);

public:
	virtual point_container_t& get_point_container (void);
/*
	virtual point_t get_point (cx::uint_t i);
	virtual void    set_point (cx::uint_t i, point_t p);
*/
public:
	virtual cx::bool_t is_point_in (point_t p);

public:
	virtual void move (point_t offset);	

public:
	virtual rectangle_t get_bounds (void);
	virtual void        set_bounds (rectangle_t bounds);

public:
	virtual void set_redraw (void);
	virtual void draw (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


