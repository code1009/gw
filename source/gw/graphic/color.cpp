/////////////////////////////////////////////////////////////////////////////
//
// File: color.cpp
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
#include "../header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cx::byte_t color_level(cx::byte_t v, cx::float_t f)
{
	cx::byte_t  level;
	cx::float_t value;


	value = v * f;

	if ( (v<=64) && (f>=1.0f) )
	{
		value = 64.0f * f;
	}

	if      (value > 255.0f) { value = 255.0f; }
	else if (value <   0.0f) { value =   0.0f; }

	level = static_cast<cx::byte_t>(value);

	return level;
}
	
	
color color_level(color v, cx::float_t f)
{
	color level;


	level.set
	(
		color_level ( v.R(), f ),
		color_level ( v.G(), f ),
		color_level ( v.B(), f ),
		v.A()
	);

	return level;
}
	

	
/////////////////////////////////////////////////////////////////////////////
//
// Class: color
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
color::color()
{
	set(0u, 0u, 0u);
}

color::color(cx::byte_t r, cx::byte_t g, cx::byte_t b, cx::byte_t a)
{
	set(r, g, b, a);
}

color::color(const color& o)
{
	set(o._R, o._G, o._B, o._A);
}

/*
color::~color()
{
}
*/

//===========================================================================
color& color::operator= (const color& rhs)
{
	set(rhs._R, rhs._G, rhs._B, rhs._A);

	return *this;
}

//===========================================================================
cx::bool_t color::operator==(const color& rhs)
{
	if (_R != rhs._R){ return false; }
	if (_G != rhs._G){ return false; }
	if (_B != rhs._B){ return false; }
	if (_A != rhs._A){ return false; }

	return true;
}

cx::bool_t color::operator!=(const color& rhs)
{
	return !operator==(rhs);
}

//===========================================================================
void color::set (cx::byte_t r, cx::byte_t g, cx::byte_t b, cx::byte_t a)
{
	//-----------------------------------------------------------------------
	_R = r;
	_G = g;
	_B = b;
	_A = a;
}

void color::set_ARGB (cx::uint_t ARGB_value)
{
	cx::byte_t A;
	cx::byte_t R;
	cx::byte_t G;
	cx::byte_t B;


	A = static_cast<cx::byte_t>( (ARGB_value & 0xFF000000) >> 24 );
	R = static_cast<cx::byte_t>( (ARGB_value & 0x00FF0000) >> 16 );
	G = static_cast<cx::byte_t>( (ARGB_value & 0x0000FF00) >>  8 );
	B = static_cast<cx::byte_t>( (ARGB_value & 0x000000FF) >>  0 );


	set(R,G,B,A);
}

void color::set_ABGR (cx::uint_t ABGR_value)
{
	cx::byte_t A;
	cx::byte_t B;
	cx::byte_t G;
	cx::byte_t R;


	A = static_cast<cx::byte_t>( (ABGR_value & 0xFF000000) >> 24 );
	B = static_cast<cx::byte_t>( (ABGR_value & 0x00FF0000) >> 16 );
	G = static_cast<cx::byte_t>( (ABGR_value & 0x0000FF00) >>  8 );
	R = static_cast<cx::byte_t>( (ABGR_value & 0x000000FF) >>  0 );

	set(R,G,B,A);
}

//===========================================================================
cx::byte_t color::R (void)
{
	return _R;
}

cx::byte_t color::G (void)
{
	return _G;
}

cx::byte_t color::B (void)
{
	return _B;
}

cx::byte_t color::A (void)
{
	return _A;
}

void color::R (cx::byte_t r)
{
	_R = r;
}

void color::G (cx::byte_t g)
{
	_G = g;
}

void color::B (cx::byte_t b)
{
	_B = b;
}

void color::A (cx::byte_t a)
{
	_A = a;
}

//===========================================================================
cx::uint_t color::ABGR(void)
{
	cx::uint_t v;

	v =
		(_R       ) |
		(_G <<  8u) |
		(_B << 16u) |
		(_A << 24u);

	return v;
}

cx::uint_t color::ARGB (void)
{
	cx::uint_t v;

	v =
		(_B       ) |
		(_G <<  8u) |
		(_R << 16u) |
		(_A << 24u);

	return v;
}

//===========================================================================
cx::bool_t color::get_alpha_zero (void)
{
	return (_A == 0x00u);
}

void color::set_alpha_zero (void)
{
	_A = 0x00u;
}

void color::set_alpha (cx::float_t f)
{
	cx::float_t value;


	value = f * 0xFFu;
	if      (value > 255.0f) { value = 255.0f; }
	else if (value <   0.0f) { value =   0.0f; }


	_A = static_cast<cx::byte_t>(value);
}

//===========================================================================
void color::set_red (cx::float_t f) 
{
	cx::float_t value;


	value = f * 0xFFu;
	if      (value > 255.0f) { value = 255.0f; }
	else if (value <   0.0f) { value =   0.0f; }


	_R = static_cast<cx::byte_t>(value);
}

void color::set_green (cx::float_t f)
{
	cx::float_t value;


	value = f * 0xFFu;
	if      (value > 255.0f) { value = 255.0f; }
	else if (value <   0.0f) { value =   0.0f; }


	_G = static_cast<cx::byte_t>(value);
}

void color::set_blue (cx::float_t f)
{
	cx::float_t value;


	value = f * 0xFFu;
	if      (value > 255.0f) { value = 255.0f; }
	else if (value <   0.0f) { value =   0.0f; }


	_B = static_cast<cx::byte_t>(value);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
