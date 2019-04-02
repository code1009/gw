#ifndef INCLUDED__CX__GW__RESOURCE__HPP
#define INCLUDED__CX__GW__RESOURCE__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: resource.hpp
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
// Class: resource
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class resource
{
private:
	model* _model;

private:
	named_graphic_object_container_t _graphic_object_container;

public:
	resource();
	virtual ~resource();

public:
	virtual model* get_model (void);
	virtual void   set_model (model* model);

public:
	virtual void delete_container (void);

public:
	virtual std::string make_name (const cx::char_t* format, ...);

public:
	virtual named_graphic_object_container_t& get_graphic_object_container (void);

public:
	virtual void delete_graphic_object_container (void);

public:
	virtual graphic_object_t find_graphic_object(std::string name);
	virtual cx::bool_t       add_graphic_object (std::string name, graphic_object_t p);

public:
	virtual font_t obtain_graphic_font (std::string familyname, cx::float_t size, cx::uint_t style);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


