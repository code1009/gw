#ifndef INCLUDED__CX__GW__CONTROL__WH_LAYOUT__HPP
#define INCLUDED__CX__GW__CONTROL__WH_LAYOUT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: wh_v_layout.hpp
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
namespace ctrl
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: wh_layout
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class wh_layout
{
private:
	cx::bool_t    _vertical;
	rectangle_t   _bounds;
	coordinates_t _item_xsize; 
	coordinates_t _item_ysize;

	coordinates_t _padding_xsize;
	coordinates_t _padding_ysize;

	point_t _cursor;
	point_t _start;
	point_t _end;

public:
	explicit wh_layout(cx::bool_t vertical);
	virtual ~wh_layout();

public:
	rectangle get_bounds (void); // 범위영역

	coordinates_t get_item_xsize(void); 
	coordinates_t get_item_ysize(void); 

	coordinates_t get_padding_xsize(void); 
	coordinates_t get_padding_ysize(void); 

public:
	void begin            (point_t start, coordinates_t padding_xsize, coordinates_t padding_ysize);
	void set_padding_size (coordinates_t xsize, coordinates_t ysize);
	void set_item_size    (coordinates_t xsize, coordinates_t ysize);
	void add_control      (control* wc);
	void separate         (void);
	void end              (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


