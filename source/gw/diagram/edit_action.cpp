/////////////////////////////////////////////////////////////////////////////
//
// File: edit_action.cpp
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
//
// Class: edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
edit_action::edit_action()
{
	_edit = CX_NULL_POINTER;
}

edit_action::~edit_action()
{
}

//===========================================================================
void edit_action::initialize (edit* m)
{
	_edit = m;
}

edit* edit_action::get_edit (void)
{
	return _edit;
}

void edit_action::draw (graphic_t g)
{
}

void edit_action::on_mouse_move         (mouse_event* e){}
void edit_action::on_mouse_lbutton_down (mouse_event* e){}
void edit_action::on_mouse_lbutton_up   (mouse_event* e){}

void edit_action::on_mouse_drag_enter (mouse_drag_drop_event* e){}
void edit_action::on_mouse_drag_over  (mouse_drag_drop_event* e){}
void edit_action::on_mouse_drag_leave (mouse_drag_drop_event* e){}
void edit_action::on_mouse_drop       (mouse_drag_drop_event* e){}



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_select_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_select_edit_action::diagram_select_edit_action()
{
}

diagram_select_edit_action::~diagram_select_edit_action()
{
}

//===========================================================================
void diagram_select_edit_action::initialize (edit* m)
{
	edit_action::initialize(m);

	set_bounds_tracking_enabled(false);
}

void diagram_select_edit_action::draw (graphic_t g)
{
	if (get_bounds_tracking_enabled())
	{
		rectangle_renderer r;

		r.set_model(get_edit());
		r.set_rectangle(_bounds);
		r.set_fill_color(color_t(0x80,0x80,0xff,0x40));
		r.set_line_color(color_t(0x00,0x00,0xff,0x80));
		r.set_line_width(1.0f);
		r.render(g);
	}
}

void diagram_select_edit_action::on_mouse_move (mouse_event* e)
{
	//--------------------------------------------------------------------------
	cx::bool_t forced_redraw;


	forced_redraw = get_bounds_tracking_enabled();


	//--------------------------------------------------------------------------
	set_last_point(e->_point);

	
	//--------------------------------------------------------------------------
	if (forced_redraw)
	{
		get_edit()->set_redraw();
	}
}

void diagram_select_edit_action::on_mouse_lbutton_down (mouse_event* e)
{
	if (false==e->_shift_key_pressed && false==e->_ctrl_key_pressed)
	{
		get_edit()->unselect_all ();
	}


	//--------------------------------------------------------------------------
	set_first_point(e->_point);
	set_last_point (e->_point);


	//--------------------------------------------------------------------------
	set_bounds_tracking_enabled(true);
}

void diagram_select_edit_action::on_mouse_lbutton_up (mouse_event* e)
{
	//--------------------------------------------------------------------------
	set_last_point(e->_point);


	//--------------------------------------------------------------------------
	if ( get_bounds_tracking_enabled() )
	{	
		select_in_bounds ();
	}


	//--------------------------------------------------------------------------
	set_bounds_tracking_enabled(false);
}

//===========================================================================
void diagram_select_edit_action::set_first_point(point_t& p)
{
	_bounds._p0 = p;
}

void diagram_select_edit_action::set_last_point(point_t& p)
{
	_bounds._p1 = p;
}

void diagram_select_edit_action::set_bounds_tracking_enabled(cx::bool_t enabled)
{
	if (_bounds_tracking_enabled != enabled)
	{
		_bounds_tracking_enabled = enabled;
		get_edit()->set_redraw();
	}
}

cx::bool_t diagram_select_edit_action::get_bounds_tracking_enabled (void)
{
	return _bounds_tracking_enabled;
}

rectangle_t diagram_select_edit_action::get_bounds (void)
{
	return _bounds;
}

void diagram_select_edit_action::select_in_bounds (void)
{
	get_edit()->select_in_bounds(get_bounds());
}




/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_single_select_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_single_select_edit_action::diagram_single_select_edit_action()
{
}

diagram_single_select_edit_action::~diagram_single_select_edit_action()
{
}

//===========================================================================
void diagram_single_select_edit_action::initialize (edit* m)
{
	edit_action::initialize(m);

	_mode = MODE_NONE;
}

void diagram_single_select_edit_action::draw (graphic_t g)
{
}

void diagram_single_select_edit_action::on_mouse_move (mouse_event* e)
{
}

void diagram_single_select_edit_action::on_mouse_lbutton_down (mouse_event* e)
{
	//--------------------------------------------------------------------------
	if      (e->_shift_key_pressed)
	{
		_mode = MODE_ADD;
	}
	else if (e->_ctrl_key_pressed)
	{
		_mode = MODE_TOGGLE;
	}


	//--------------------------------------------------------------------------
	widget* w;


	w = get_edit()->get_widget()->find(e->_point);
	CX_DEBUG_ASSERT(CX_NULL_POINTER != w);


	//--------------------------------------------------------------------------
	anchor*  wa;
	diagram* wd;


	wa = get_edit()->cast_anchor (w);
	wd = get_edit()->cast_diagram(w);

	if (wa)
	{
		wd = wa->get_diagram();
	}
	CX_DEBUG_ASSERT(CX_NULL_POINTER != wd);


	//--------------------------------------------------------------------------
	if (_mode == MODE_ADD)
	{
		get_edit()->select(wd);
		get_edit()->set_redraw();
	}


	if (_mode == MODE_TOGGLE)
	{
		if (!get_edit()->get_selected_diagram()->is_in_collection(wd))
		{
			get_edit()->select(wd);
		}
		else
		{
			get_edit()->unselect(wd);
		}
		get_edit()->set_redraw();
	}
}

void diagram_single_select_edit_action::on_mouse_lbutton_up (mouse_event* e)
{
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_move_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_move_edit_action::diagram_move_edit_action()
{
}

diagram_move_edit_action::~diagram_move_edit_action()
{
}

//===========================================================================
void diagram_move_edit_action::initialize (edit* m)
{
	edit_action::initialize(m);
}

void diagram_move_edit_action::draw (graphic_t g)
{
}

void diagram_move_edit_action::on_mouse_move (mouse_event* e)
{
	//--------------------------------------------------------------------------
	set_last_point(e->_point);
}

void diagram_move_edit_action::on_mouse_lbutton_down (mouse_event* e)
{
	//--------------------------------------------------------------------------
	widget* w;


	w = get_edit()->get_widget()->find(e->_point);
	CX_DEBUG_ASSERT(CX_NULL_POINTER != w);


	//--------------------------------------------------------------------------
	anchor*  wa;
	diagram* wd;


	wa = get_edit()->cast_anchor (w);
	wd = get_edit()->cast_diagram(w);

	if (wa)
	{
		wd = wa->get_diagram();
	}
	CX_DEBUG_ASSERT(CX_NULL_POINTER != wd);


	//--------------------------------------------------------------------------
	if (!get_edit()->get_selected_diagram()->is_in_collection(wd))
	{
		get_edit()->unselect_all();
		get_edit()->select(wd);
	}
	

	//--------------------------------------------------------------------------
	set_first_point (e->_point);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(false);
}

void diagram_move_edit_action::on_mouse_lbutton_up (mouse_event* e)
{
	//--------------------------------------------------------------------------
	set_last_point(e->_point);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(true);


	//--------------------------------------------------------------------------
	if (_first_point!=_last_point)
	{
		get_edit()->on_edit_action_diagram_modified();
	}
}

//===========================================================================
void diagram_move_edit_action::set_first_point(point_t& p)
{
	//--------------------------------------------------------------------------
	_first_point = get_edit()->to_snapped_point (p);


	//--------------------------------------------------------------------------
	_current_point = _first_point;
}

void diagram_move_edit_action::set_last_point(point_t& p)
{
	//--------------------------------------------------------------------------
	_last_point = get_edit()->to_snapped_point (p);


	//--------------------------------------------------------------------------
	point_t offset;


	offset = _last_point - _current_point;
	
	get_edit()->get_selected_diagram()->move(offset);

	_current_point = _last_point;
}

	
	
/////////////////////////////////////////////////////////////////////////////
//
// Class: anchor_move_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
anchor_move_edit_action::anchor_move_edit_action()
{
}

anchor_move_edit_action::~anchor_move_edit_action()
{
}

//===========================================================================
void anchor_move_edit_action::initialize (edit* m)
{
	edit_action::initialize(m);

	set_anchor(CX_NULL_POINTER);
}

void anchor_move_edit_action::draw (graphic_t g)
{
}

void anchor_move_edit_action::on_mouse_move (mouse_event* e)
{
	//--------------------------------------------------------------------------
	set_last_point(e->_point);
}

void anchor_move_edit_action::on_mouse_lbutton_down (mouse_event* e)
{
	//--------------------------------------------------------------------------
	widget* w;


	w = get_edit()->get_widget()->find(e->_point);
	CX_DEBUG_ASSERT(CX_NULL_POINTER != w);

	
	//--------------------------------------------------------------------------
	anchor* wa;


	wa = get_edit()->cast_anchor(w);
	CX_DEBUG_ASSERT(CX_NULL_POINTER != wa);


	//--------------------------------------------------------------------------
	set_anchor(wa);
	

	//--------------------------------------------------------------------------
	set_first_point (e->_point);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(false);
}

void anchor_move_edit_action::on_mouse_lbutton_up (mouse_event* e)
{
	//--------------------------------------------------------------------------
	set_last_point(e->_point);


	//--------------------------------------------------------------------------
	set_anchor(CX_NULL_POINTER);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(true);


	//--------------------------------------------------------------------------
	if (_first_point!=_last_point)
	{
		get_edit()->on_edit_action_diagram_modified();
	}
}

//===========================================================================
void anchor_move_edit_action::set_first_point(point_t& p)
{
	//--------------------------------------------------------------------------
	_first_point = get_edit()->to_snapped_point (p);


	//--------------------------------------------------------------------------
	_current_point = _first_point;
}

void anchor_move_edit_action::set_last_point(point_t& p)
{
	//--------------------------------------------------------------------------
	_last_point = get_edit()->to_snapped_point (p);


	//--------------------------------------------------------------------------
	point_t offset;


	offset = _last_point - _current_point;
	
	get_anchor()->on_set_point(_last_point);

	_current_point = _last_point;
}

//===========================================================================
anchor* anchor_move_edit_action::get_anchor(void)
{
	return _anchor;
}

void anchor_move_edit_action::set_anchor(anchor* wa)
{
	_anchor = wa;
}

	
	
/////////////////////////////////////////////////////////////////////////////
//
// Class: diagram_add_edit_action
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
diagram_add_edit_action::diagram_add_edit_action()
{
}

diagram_add_edit_action::~diagram_add_edit_action()
{
	get_new_diagram()->delete_container();
}


//===========================================================================
void diagram_add_edit_action::initialize (edit* m)
{
	edit_action::initialize(m);
}

void diagram_add_edit_action::draw (graphic_t g)
{
	get_new_diagram()->draw();
}

void diagram_add_edit_action::on_mouse_drag_enter (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	cx::bool_t forced_redraw;


	
	//--------------------------------------------------------------------------
	if (!get_edit()->get_selected_diagram()->get_container().empty())
	{
		get_edit()->unselect_all();
		forced_redraw = true;
	}


	//--------------------------------------------------------------------------
	get_new_diagram()->delete_container();


	//--------------------------------------------------------------------------
	diagram* wd;


	wd = CX_NULL_POINTER;


	//--------------------------------------------------------------------------
	std::string name;


	//--------------------------------------------------------------------------
	HGLOBAL hglobal;

	cx::uint_t    source_size;
	cx::pointer_t source_pointer;


	hglobal = e->_hglobal;

	source_size    = GlobalSize(hglobal);
	source_pointer = GlobalLock(hglobal);
	if ( NULL != source_pointer )
	{
		if (source_size>0u)
		{
			name = reinterpret_cast<const char*>( source_pointer );
		}

		GlobalUnlock(hglobal);
	}


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(false);


	//--------------------------------------------------------------------------
	wd = get_edit()->get_diagram_creator()->create_diagram(name);


	if (CX_NULL_POINTER!=wd)
	{
		get_new_diagram()->get_container().push_back (wd);
	}


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(true);


	//--------------------------------------------------------------------------
	set_first_point(e->_point);


	//--------------------------------------------------------------------------
	forced_redraw = true;
	if (forced_redraw)
	{
		get_edit()->set_redraw();
	}
}

void diagram_add_edit_action::on_mouse_drag_over (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	cx::bool_t forced_redraw;


	forced_redraw = !get_new_diagram()->get_container().empty();


	//--------------------------------------------------------------------------
	set_last_point(e->_point);


	//--------------------------------------------------------------------------
	if (forced_redraw)
	{
		get_edit()->set_redraw();
	}
}

void diagram_add_edit_action::on_mouse_drag_leave (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	cx::bool_t forced_redraw;


	forced_redraw = !get_new_diagram()->get_container().empty();


	//--------------------------------------------------------------------------
	get_new_diagram()->delete_container();	


	//--------------------------------------------------------------------------
	if (forced_redraw)
	{
		get_edit()->set_redraw();
	}
}

void diagram_add_edit_action::on_mouse_drop (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	cx::bool_t forced_redraw;


	forced_redraw = !get_new_diagram()->get_container().empty();


	//--------------------------------------------------------------------------
	set_last_point(e->_point);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(false);


	//--------------------------------------------------------------------------
	widget*  w;
	diagram* wd;
	
	widget_pointer_container_t::iterator i;


	for (i =get_new_diagram()->get_container().begin();
	     i!=get_new_diagram()->get_container().end();
	     i++)
	{
		w = (*i);

		get_edit()->get_widget()->get_container().push_back(w);

		
		wd = reinterpret_cast<diagram*>(w);

		get_edit()->select(wd);
	}
	get_new_diagram()->get_container().clear();


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(true);


	//--------------------------------------------------------------------------
	get_edit()->on_edit_action_diagram_modified();


	//--------------------------------------------------------------------------
	if (forced_redraw)
	{
		get_edit()->set_redraw();
	}
}

//===========================================================================
void diagram_add_edit_action::set_first_point(point_t& p)
{
	//--------------------------------------------------------------------------
	_current_point = get_edit()->to_snapped_point (p);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(false);


	//--------------------------------------------------------------------------
	get_new_diagram()->move(_current_point);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(true);
}

void diagram_add_edit_action::set_last_point(point_t& p)
{
	//--------------------------------------------------------------------------
	point_t last_point;


	last_point = get_edit()->to_snapped_point (p);


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(false);


	//--------------------------------------------------------------------------
	point_t offset;


	offset = last_point - _current_point;
	
	get_new_diagram()->move(offset);

	_current_point = last_point;


	//--------------------------------------------------------------------------
	get_edit()->get_edit_history()->set_enabled(true);
}

widget_collection* diagram_add_edit_action::get_new_diagram(void)
{
	return &_new_diagram;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
