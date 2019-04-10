/////////////////////////////////////////////////////////////////////////////
//
// File: copy_diagram.cpp
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
namespace dgrm
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void copy_point_container (diagram* to, diagram* from)
{
	cx::uint_t i;
	cx::uint_t count;


	CX_DEBUG_ASSERT(to->get_class()==from->get_class());
	CX_DEBUG_ASSERT(
		to  ->get_point_container().size()
		==
		from->get_point_container().size()
		);


	count = to->get_point_container().size();

	for (i=0u; i<count; i++)
	{
		to->get_point_container()[i].set(from->get_point_container()[i]);
	}
}

void copy_anchor (diagram* to, diagram* from)
{
	design* m_to;
	design* m_from;

	widget* w_to;
	widget* w_from;

	anchor* wa_to;
	anchor* wa_from;

	cx::uint_t i;
	cx::uint_t count;


	CX_DEBUG_ASSERT(to->get_class()==from->get_class());
	CX_DEBUG_ASSERT(
		to  ->get_child()->get_container().size()
		==
		from->get_child()->get_container().size()
		);


	m_to   = to  ->get_design();
	m_from = from->get_design();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m_to  );
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=m_from);


	count = to->get_child()->get_container().size();

	for (i=0u; i<count; i++)
	{
		w_to   = to  ->get_child()->get_container()[i];
		w_from = from->get_child()->get_container()[i];
		
		wa_to   = m_to->cast_anchor(w_to  );
		wa_from = m_to->cast_anchor(w_from);


		if      ( (CX_NULL_POINTER!=wa_to) && (CX_NULL_POINTER!=wa_from) )
		{
			wa_to->set_point( wa_from->get_point() );

			wa_to->set_visible (wa_from->get_visible ());
			wa_to->set_enabled (wa_from->get_enabled ());
			wa_to->set_pressed (wa_from->get_pressed ());
			wa_to->set_selected(wa_from->get_selected());
		}
		else if ( (CX_NULL_POINTER==wa_to) && (CX_NULL_POINTER==wa_from) )
		{
		}
		else
		{
			CX_DEBUG_ASSERT(0);
		}
	}
}

void copy_widget (diagram* to, diagram* from)
{
	to->set_name (from->get_name());

	copy_point_container(to, from);

	copy_anchor         (to, from);

	to->set_parent(from->get_parent());
}

void copy_diagram (diagram* to, diagram* from)
{
	copy_widget(to, from);

	to->set_visible (from->get_visible ());
	to->set_enabled (from->get_enabled ());
	to->set_pressed (from->get_pressed ());
	to->set_selected(from->get_selected());
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
