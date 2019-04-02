/////////////////////////////////////////////////////////////////////////////
//
// File: resource.cpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//
// Headers
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
resource::resource()
{
	_model = CX_NULL_POINTER;
}

resource::~resource()
{
}

//===========================================================================
model* resource::get_model (void)
{
	return _model;
}

void resource::set_model (model* m)
{
	_model = m;
}

//===========================================================================
void resource::delete_container (void)
{
	delete_graphic_object_container();
}

std::string resource::make_name (const cx::char_t* format, ...)
{
	std::string s;


	if (CX_NULL_POINTER==format)
	{
		return s;
	}


	cx::char_t buffer[CX_GW_RESOURCE_MAX_NAME] = { 0 };
	cx::int_t  max_count;
	cx::int_t  length;
	va_list    args;


	max_count = sizeof(buffer)-1;

	va_start (args, format);
	length = vsnprintf (buffer, max_count, format, args);
	va_end (args);
	
	if (length>0)
	{
		buffer[length] = '\0';

		s = buffer;
	}


	return s;
}

//===========================================================================
named_graphic_object_container_t& resource::get_graphic_object_container (void)
{
	return _graphic_object_container;
}

void resource::delete_graphic_object_container (void)
{
	named_graphic_object_container_t::iterator i;
	graphic_object_t p;
	

	for (i=get_graphic_object_container().begin(); i!=get_graphic_object_container().end(); i++)
	{
		p = (*i).second;

		if (p)
		{
			delete p;
		}
	}

	get_graphic_object_container().clear();
}

//===========================================================================
graphic_object_t resource::find_graphic_object (std::string name)
{
	named_graphic_object_container_t::iterator i;
	graphic_object_t p;

	
	p = CX_NULL_POINTER;

	i = get_graphic_object_container().find(name);
	if (i==get_graphic_object_container().end())
	{
		return p;
	}

	p = (*i).second;

	return p;
}

cx::bool_t resource::add_graphic_object(std::string name, graphic_object_t p)
{
	graphic_object_t o;


	o = find_graphic_object (name);
	if (o!=CX_NULL_POINTER)
	{
		return false;
	}


	get_graphic_object_container()[name] = p;

	return true;
}

font_t resource::obtain_graphic_font (std::string familyname, cx::float_t size, cx::uint_t style)
{
	std::string      key;
	graphic_object_t p;
	font_t           o;


	key = make_name("Font:%s;%.2f;0x%08x", familyname.c_str(), size, style);

	o = CX_NULL_POINTER;
	p = find_graphic_object(key);
	if (CX_NULL_POINTER!=p)
	{
		//o = cx_gw_dynamic_cast<font_t>( p ); // error?
		o = static_cast<font_t>( p );

		return o;
	}


	std::wstring font_familynamew;


	if (familyname.empty())
	{
		font_familynamew.clear();
	}
	else
	{
		font_familynamew = cx::mbcs_to_wcs(familyname);
	}


	CX_DEBUG_ASSERT(!font_familynamew.empty());


	o = new Font (font_familynamew.c_str(), size, style);

	if (false == add_graphic_object(key, o))
	{
		delete o;

		return CX_NULL_POINTER;
	}


	return o;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
