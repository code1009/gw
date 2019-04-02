#ifndef INCLUDED__CX__GW__DIAGRAM__DIAGRAM_BUFFER__HPP
#define INCLUDED__CX__GW__DIAGRAM__DIAGRAM_BUFFER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: diagram_buffer.hpp
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
// Class: diagram_buffer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_buffer
{
private:
	widget_collection _widget;

public:
	diagram_buffer();
	virtual ~diagram_buffer();

public:
	virtual widget_collection* get_widget (void);

public:
	virtual void clear (void);

public:
	virtual cx::bool_t load (design* m);
	virtual cx::bool_t save (design* m);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


