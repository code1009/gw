/////////////////////////////////////////////////////////////////////////////
//
// File: text_rectangle_renderer.cpp
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
text_rectangle_renderer::text_rectangle_renderer()
{
	_text_color = color_t::Black;

	_text_format_alignment      = GW_DEFAULT_TEXT_FORMAT_ALIGNMENT      ;
	_text_format_line_alignment = GW_DEFAULT_TEXT_FORMAT_LINE_ALIGNMENT ;

	_text_font_familyname = GW_DEFAULT_TEXT_FONT_FAMILYNAME;
	_text_font_size       = GW_DEFAULT_TEXT_FONT_SIZE;
	_text_font_style      = GW_DEFAULT_TEXT_FONT_STYLE;
	_text_font            = CX_NULL_POINTER;
}

text_rectangle_renderer::~text_rectangle_renderer()
{
}

//===========================================================================
void text_rectangle_renderer::render (graphic_t g)
{
	RectF r;


	r = rectangle_to_RectF(_rectangle);

	
	if (!_textw.empty())
	{
		if (!_text_color.get_alpha_zero())
		{
			SolidBrush fill(Color(_text_color.ARGB()));


			cx::int_t    sf_flags = 0;
			StringFormat sf(sf_flags);


			sf.SetAlignment    ( static_cast<StringAlignment>(_text_format_alignment     ) );
			sf.SetLineAlignment( static_cast<StringAlignment>(_text_format_line_alignment) );

	
			CX_DEBUG_ASSERT (CX_NULL_POINTER!=_text_font);


			g->DrawString(
				_textw.c_str(),
				_textw.size(),
				_text_font,
				r,
				&sf,
				&fill
				);
		}
	}
}

//===========================================================================
void text_rectangle_renderer::set_rectangle (rectangle_t v)
{
	_rectangle = v;
}

void text_rectangle_renderer::set_text (std::string v)
{
	if (_text == v)
	{
		return;
	}

	_text = v;
	
	if (_text.empty())
	{
		_textw.clear();
	}
	else
	{
		_textw = cx::mbcs_to_wcs(_text);
	}
}

void text_rectangle_renderer::set_text_color (color_t v)
{
	_text_color = v;
}

void text_rectangle_renderer::set_text_format_alignment (cx::uint_t alignment, cx::uint_t line_alignment)
{
	_text_format_alignment      = alignment;
	_text_format_line_alignment = line_alignment;
}

void text_rectangle_renderer::set_text_font (std::string familyname, cx::float_t size, cx::uint_t style)
{
	if ( (_text_font_familyname == familyname) &&
	     (_text_font_size       == size      ) &&
	     (_text_font_style      == style     ) )
	{
		if (CX_NULL_POINTER!=_text_font)
		{
			return;
		}
	}


	_text_font_familyname = familyname;
	_text_font_size       = size;
	_text_font_style      = style;

	CX_DEBUG_ASSERT( CX_NULL_POINTER!=get_model() );
	
	_text_font = get_model()->get_resource()->obtain_graphic_font(familyname.c_str(), size, style);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
