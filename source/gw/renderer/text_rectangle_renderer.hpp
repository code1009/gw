#ifndef INCLUDED__CX__GW__RENDERER__TEXT_RECTANGLE_RENDERER__HPP
#define INCLUDED__CX__GW__RENDERER__TEXT_RECTANGLE_RENDERER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: text_rectangle_renderer.hpp
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
// Class: text_rectangle_renderer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class text_rectangle_renderer : public renderer
{
private:
	rectangle_t  _rectangle;

	std::string  _text;
	std::wstring _textw;

	color_t      _text_color;
	
	cx::uint_t   _text_format_alignment     ;
	cx::uint_t   _text_format_line_alignment;

	std::string  _text_font_familyname ;
	cx::float_t  _text_font_size       ;
	cx::uint_t   _text_font_style      ;
	font_t       _text_font            ;

public:
	text_rectangle_renderer();
	virtual ~text_rectangle_renderer();

	// renderer 가상함수
public:
	virtual void render (graphic_t g);

public:
	void set_rectangle (rectangle_t v);

	void set_text (std::string v);

	void set_text_color (color_t v);
	     
	void set_text_format_alignment (cx::uint_t alignment=1u, cx::uint_t line_alignment=1u);

	void set_text_font (std::string familyname=GW_DEFAULT_TEXT_FONT_FAMILYNAME, cx::float_t size=GW_DEFAULT_TEXT_FONT_SIZE, cx::uint_t style=0u);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





#endif


