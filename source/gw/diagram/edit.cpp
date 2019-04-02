/////////////////////////////////////////////////////////////////////////////
//
// File: edit.cpp
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
#if 0
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{
namespace dgrm
{


/////////////////////////////////////////////////////////////////////////////
//
// Class: edit
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
edit::edit()
{
	_edit_action = CX_NULL_POINTER;
	_modified = false;
	_snap_to_grid = false;
	_paste_action_count = 0u;
}

edit::~edit()
{
	destroy();
}

//===========================================================================
cx::bool_t edit::create (widget_entry_collection* wec)
{
	//-----------------------------------------------------------------------
	get_resource()->set_model(this);


	//-----------------------------------------------------------------------
	get_view()->set_model(this);
	get_view()->set_background_color(color_t::White);
	get_view()->set_wolrd_rectangle(rectangle_t(1920, 1080));
	get_view()->set_grid_size(5, 5);
	get_view()->set_grid_visible(true);


	//-----------------------------------------------------------------------
	get_window_event_handler()->set_model(this);


	//-----------------------------------------------------------------------
	widget_entry_pointer_container_t::iterator i;

	widget_entry*         we;
	std::string           wc;
	widget_event_handler* weh;

	widget*  w;
	diagram* wd;


	for (i = wec->get_container().begin(); i != wec->get_container().end(); i++)
	{
		we = (*i);


		w = we->get_widget_factory()->create_instance();

		wd = cast_diagram(w);
		if (wd)
		{
			wd->set_model(this);
			wd->initialize();

			if (false == get_diagram_creator()->register_entry(wd))
			{
				delete wd;

				return false;
			}


			wc  = we->get_widget_class();
			weh = CX_NULL_POINTER;

			if (false == get_widget_event_handler()->add(wc, weh))
			{
				return false;
			}
		}
		else
		{
			delete w;


			wc  = we->get_widget_class();
			weh = we->get_widget_event_handler_factory()->create_instance();

			if (false == get_widget_event_handler()->add(wc, weh))
			{
				return false;
			}
		}
	}	


	//-----------------------------------------------------------------------
	set_snap_to_grid(true);


	//-----------------------------------------------------------------------
	get_diagram_select_edit_action       ()->initialize(this);
	get_diagram_single_select_edit_action()->initialize(this);
	get_diagram_move_edit_action         ()->initialize(this);
	get_diagram_add_edit_action          ()->initialize(this);
	get_anchor_move_edit_action          ()->initialize(this);

	set_edit_action(CX_NULL_POINTER);


	//-----------------------------------------------------------------------
	set_modified (true);


	//-----------------------------------------------------------------------
	get_edit_history()->initialize(this);


	return true;
}

void edit::destroy (void)
{
	//-----------------------------------------------------------------------
	get_edit_history()->clear();


	//-----------------------------------------------------------------------
	get_diagram_clipboard()->delete_container();


	//-----------------------------------------------------------------------
	get_widget()->delete_container();


	//-----------------------------------------------------------------------
	get_diagram_creator()->delete_container ();


	//-----------------------------------------------------------------------
	get_widget_event_handler()->delete_container();

	get_resource()->delete_container();
}

void edit::draw (void)
{
	graphic_t g;

	g = get_graphic();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=g);


	model::draw();

	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->draw(g);
	}
}

//===========================================================================
void edit::on_mouse_move (mouse_event* e)
{
	//--------------------------------------------------------------------------
//	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);


	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_move(e);
	}
}

void edit::on_mouse_lbutton_down (mouse_event* e)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);


	//--------------------------------------------------------------------------
	widget*  w;
	anchor*  wa;
	diagram* wd;


	w = get_widget()->find(e->_point);
	if (CX_NULL_POINTER==w)
	{
		set_edit_action(get_diagram_select_edit_action());
	}
	else
	{
		wa = cast_anchor (w);
		wd = cast_diagram(w);
		if (wd)
		{
			if (false==e->_shift_key_pressed && false==e->_ctrl_key_pressed)
			{
				set_edit_action(get_diagram_move_edit_action());
			}
			else
			{
				set_edit_action(get_diagram_single_select_edit_action());
			}
		}
		else if (wa)
		{
			wd = wa->get_diagram();

			if ( wd->get_selected() )
			{
				set_edit_action(get_anchor_move_edit_action());
			}
			else
			{
				if (false==e->_shift_key_pressed && false==e->_ctrl_key_pressed)
				{
					set_edit_action(get_diagram_move_edit_action());
				}
				else
				{
					set_edit_action(get_diagram_single_select_edit_action());
				}
			}
		}
	}


	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_lbutton_down(e);
	}
}

void edit::on_mouse_lbutton_up (mouse_event* e)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);


	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_lbutton_up(e);
	}


	//--------------------------------------------------------------------------
	set_edit_action(CX_NULL_POINTER);
}

//===========================================================================
void edit::on_mouse_drag_enter (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);

	//--------------------------------------------------------------------------
	set_edit_action(get_diagram_add_edit_action());


	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_drag_enter(e);
	}
}

void edit::on_mouse_drag_over (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
//	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);

	
	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_drag_over(e);
	}
}

void edit::on_mouse_drag_leave (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);
	

	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_drag_leave(e);
	}


	//--------------------------------------------------------------------------
	set_edit_action(CX_NULL_POINTER);
}

void edit::on_mouse_drop (mouse_drag_drop_event* e)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%f,%f", e->_point._x, e->_point._y);


	//--------------------------------------------------------------------------
	if (CX_NULL_POINTER!=get_edit_action())
	{
		get_edit_action()->on_mouse_drop(e);
	}


	//--------------------------------------------------------------------------
	set_edit_action(CX_NULL_POINTER);
}

//===========================================================================
void edit::on_diagram_property_changed (diagram_event* e)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=e->_diagram);


	//--------------------------------------------------------------------------
//	CX_DEBUG_TRACEF(TW_THISCODE, "%s", e->_diagram->get_class().c_str());


	//--------------------------------------------------------------------------
	set_modified(true);
	get_edit_history()->record ();
}

diagram_mode_t edit::get_diagram_mode(void)
{
	return DIAGRAM_MODE_EDIT;
}

void edit::clear (void)
{
	//-----------------------------------------------------------------------
	select_all();
	remove();


	//-----------------------------------------------------------------------
	get_edit_history()->clear();


	//-----------------------------------------------------------------------
	set_modified(true);
	get_edit_history()->record ();


	//-----------------------------------------------------------------------
	set_redraw();
}

//===========================================================================
cx::bool_t edit::read (document_reader* io)
{
	cx::bool_t result;


	get_edit_history()->set_enabled(false);

	result = design::read(io);

	get_edit_history()->set_enabled(true);


	if (result)
	{
		get_edit_history()->clear();

		get_edit_history()->record ();

		set_modified(false);
	}


	return result;
}

cx::bool_t edit::write (document_writer* io)
{
	cx::bool_t result;


	get_edit_history()->set_enabled(false);

	result = design::write(io);

	get_edit_history()->set_enabled(true);


	if (result)
	{
		set_modified(false);
	}


	return result;
}

//===========================================================================
edit_action* edit::get_edit_action(void)
{
	return _edit_action;
}

void edit::set_edit_action (edit_action* ea)
{
	_edit_action = ea;
}

diagram_select_edit_action* edit::get_diagram_select_edit_action (void)
{
	return &_diagram_select_edit_action;
}

diagram_single_select_edit_action* edit::get_diagram_single_select_edit_action (void)
{
	return &_diagram_single_select_edit_action;
}

diagram_move_edit_action* edit::get_diagram_move_edit_action (void)
{
	return &_diagram_move_edit_action;
}

diagram_add_edit_action* edit::get_diagram_add_edit_action (void)
{
	return &_diagram_add_edit_action;
}

anchor_move_edit_action* edit::get_anchor_move_edit_action (void)
{
	return &_anchor_move_edit_action;
}

//===========================================================================
void edit::on_edit_action_diagram_modified (void)
{
	set_modified(true);

	get_edit_history()->record();
}

//===========================================================================
cx::bool_t edit::get_modified (void)
{
	return _modified;
}

void edit::set_modified (cx::bool_t modified)
{
	if (_modified != modified)
	{
		_modified = modified;

		on_modified(_modified);
	}
}

void edit::on_modified (cx::bool_t modified)
{
	//--------------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%s", modified ? "true" : "false" );
}

//===========================================================================
point_t edit::to_snapped_point (point_t world)
{
	if (get_snap_to_grid())
	{
		return get_view()->to_grid_point (world);
	}

	return world;
}

cx::bool_t edit::get_snap_to_grid (void)
{
	return _snap_to_grid;
}

void edit::set_snap_to_grid (cx::bool_t snap_to_grid)
{
	_snap_to_grid = snap_to_grid;
}

//===========================================================================
widget_collection* edit::get_selected_diagram (void)
{
	return &_selected_diagram;
}

void edit::select_in_bounds (rectangle_t bounds)
{
	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	
	//-----------------------------------------------------------------------
	for (i =get_widget()->get_container().begin();
	     i!=get_widget()->get_container().end();
		 i++)
	{
		w = (*i);

		if ( is_point_container_in_rectangle(w->get_point_container(), bounds) )
		{
			wd = cast_diagram(w);
			if (wd)
			{
				//select(wd);
				{
					if (false==get_selected_diagram()->is_in_collection(wd))
					{
						wd->set_selected(true);

						get_selected_diagram()->get_container().push_back(wd);

						//---------------------------------------------------
						action = true;
					}
				}
			}
		}
	}


	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();

		on_select_changed(SELECT_CHANGED_ACTION_SELECT);
	}
}

void edit::select_all (void)
{
	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	unselect_all();
	/*
	{
		get_selected_diagram()->get_container().clear();
	}
	*/


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	
	//-----------------------------------------------------------------------
	for (i =get_widget()->get_container().begin();
	     i!=get_widget()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			//select(wd);
			{
				wd->set_selected(true);

				get_selected_diagram()->get_container().push_back(wd);
			}


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();

		on_select_changed(SELECT_CHANGED_ACTION_SELECT_ALL);
	}
}

void edit::select (diagram* wd_item)
{
	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	if (false==get_selected_diagram()->is_in_collection(wd_item))
	{
		wd_item->set_selected(true);

		get_selected_diagram()->get_container().push_back(wd_item);


		//-------------------------------------------------------------------
		action = true;
	}


	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();

		on_select_changed(SELECT_CHANGED_ACTION_SELECT);
	}
}

void edit::unselect (diagram* wd_item)
{
	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator f;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	
	//-----------------------------------------------------------------------
	f = get_selected_diagram()->get_container().end();
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd==wd_item)
		{
			wd->set_selected(false);
			f = i;

			break;
		}		
	}


	//-----------------------------------------------------------------------
	if (f!=get_selected_diagram()->get_container().end())
	{
		get_selected_diagram()->get_container().erase(f);


		//-------------------------------------------------------------------
		action = true;
	}


	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();

		on_select_changed(SELECT_CHANGED_ACTION_UNSELECT);
	}
}

void edit::unselect_all (void)
{
	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	
	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			// unselect(wd);
			{
				wd->set_selected(false);
			}


			//---------------------------------------------------------------
			action = true;
		}
	}


	get_selected_diagram()->get_container().clear();



	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();

		on_select_changed(SELECT_CHANGED_ACTION_UNSELECT_ALL);
	}
}

void edit::on_select_changed (select_changed_action_t action)
{
	switch (action)
	{
	case SELECT_CHANGED_ACTION_SELECT      :
		CX_DEBUG_TRACEF(TW_THISCODE, "SELECT_CHANGED_ACTION_SELECT");
		break;

	case SELECT_CHANGED_ACTION_SELECT_ALL  :
		CX_DEBUG_TRACEF(TW_THISCODE, "SELECT_CHANGED_ACTION_SELECT_ALL");
		break;

	case SELECT_CHANGED_ACTION_UNSELECT    :
		CX_DEBUG_TRACEF(TW_THISCODE, "SELECT_CHANGED_ACTION_UNSELECT");
		break;

	case SELECT_CHANGED_ACTION_UNSELECT_ALL:
		CX_DEBUG_TRACEF(TW_THISCODE, "SELECT_CHANGED_ACTION_UNSELECT_ALL");
		break;

	case SELECT_CHANGED_ACTION_UNDO:
		CX_DEBUG_TRACEF(TW_THISCODE, "SELECT_CHANGED_ACTION_UNDO");
		break;

	case SELECT_CHANGED_ACTION_REDO:
		CX_DEBUG_TRACEF(TW_THISCODE, "SELECT_CHANGED_ACTION_REDO");
		break;

	default:
		break;
	}
}

//===========================================================================
void edit::bring_to_top (void)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "selected diagram = %d", get_selected_diagram()->get_container().size());


	//-----------------------------------------------------------------------
	if (false==can_bring_to_top())
	{
		return;
	}


	//-----------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator f;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget*  w;

	diagram* wd;
	
	
	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			f = std::find(get_widget()->get_container().begin(), get_widget()->get_container().end(), wd);
			CX_DEBUG_ASSERT(f!=get_widget()->get_container().end());

			get_widget()->get_container().erase(f);


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			get_widget()->get_container().push_back(w);


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();
	}
}

void edit::send_to_bottom (void)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "selected diagram = %d", get_selected_diagram()->get_container().size());


	//-----------------------------------------------------------------------
	if (false==can_send_to_bottom())
	{
		return;
	}


	//-----------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator f;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::reverse_iterator ri;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;
	
	diagram* wd;


	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			f = std::find(get_widget()->get_container().begin(), get_widget()->get_container().end(), wd);
			CX_DEBUG_ASSERT(f!=get_widget()->get_container().end());

			get_widget()->get_container().erase(f);


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	for (ri =get_selected_diagram()->get_container().rbegin();
	     ri!=get_selected_diagram()->get_container().rend();
		 ri++)
	{
		w = (*ri);


		wd = cast_diagram(w);
		if (wd)
		{
			get_widget()->get_container().insert(get_widget()->get_container().begin(), wd);


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	if (action)
	{
		get_edit_history()->record ();
	}
}

cx::bool_t edit::can_bring_to_top (void)
{
	if (get_selected_diagram()->get_container().empty())
	{
		return false;
	}

	return true;
}

cx::bool_t edit::can_send_to_bottom (void)
{
	if (get_selected_diagram()->get_container().empty())
	{
		return false;
	}

	return true;
}

//===========================================================================
void edit::update_system_clipboard (cx::bool_t save)
{
	if (save)
	{
		// diagram_clipboard to system_clipboard
	}
	else
	{
		// system_clipboard to diagram_clipboard 
	}
}

widget_collection* edit::get_diagram_clipboard (void)
{
	return &_diagram_clipboard;
}

void edit::copy (void)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "selected diagram = %d", get_selected_diagram()->get_container().size());


	//-----------------------------------------------------------------------
	if (false==can_copy())
	{
		return;
	}


	//-----------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return;
	}


	//-----------------------------------------------------------------------
	get_diagram_clipboard()->delete_container();
	_paste_action_count = 1u;


	//-----------------------------------------------------------------------
	diagram* wd_clone;


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	

	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();
			CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd_clone);


			if (CX_NULL_POINTER!=wd_clone)
			{
				get_diagram_clipboard()->get_container().push_back(wd_clone);


				//-----------------------------------------------------------
				action = true;
			}
		}
	}


	//-----------------------------------------------------------------------
//	set_redraw();


	//-----------------------------------------------------------------------
	if (action)
	{
		//-------------------------------------------------------------------
//		get_edit_history()->record ();


		//-------------------------------------------------------------------
		update_system_clipboard(true);
	}
}

void edit::cut (void)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "selected diagram = %d", get_selected_diagram()->get_container().size());


	//-----------------------------------------------------------------------
	if (false==can_cut())
	{
		return;
	}


	//-----------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return;
	}


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(false);


	//-----------------------------------------------------------------------
	get_diagram_clipboard()->delete_container();
	_paste_action_count = 0u;


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator f;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	

	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			wd->set_selected (false);

			get_diagram_clipboard()->get_container().push_back(wd);


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			f = std::find(get_widget()->get_container().begin(), get_widget()->get_container().end(), wd);
			CX_DEBUG_ASSERT(f!=get_widget()->get_container().end());

			get_widget()->get_container().erase(f);


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	get_selected_diagram()->get_container().clear();


	//-----------------------------------------------------------------------
	get_window_event_handler()->on_update_widget();


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(true);


	//-----------------------------------------------------------------------
	if (action)
	{
		//-------------------------------------------------------------------
		set_modified(true);
		get_edit_history()->record ();

		// unselect all
		on_select_changed(SELECT_CHANGED_ACTION_UNSELECT_ALL);


		//-------------------------------------------------------------------
		update_system_clipboard(true);
	}
}

void edit::paste (void)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "diagram clipboard = %d", get_diagram_clipboard()->get_container().size());


	//-----------------------------------------------------------------------
	if (false==can_paste())
	{
		return;
	}


	//-----------------------------------------------------------------------
	if (get_diagram_clipboard()->get_container().empty())
	{
		return;
	}


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(false);


	//-----------------------------------------------------------------------
	unselect_all();


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	point_t offset;


	offset.set(
		_paste_action_count*get_view()->get_grid_xsize()*2.0f,
		_paste_action_count*get_view()->get_grid_ysize()*2.0f
		);


	//-----------------------------------------------------------------------
	diagram* wd_clone;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	

	//-----------------------------------------------------------------------
	for (i =get_diagram_clipboard()->get_container().begin();
	     i!=get_diagram_clipboard()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();
			CX_DEBUG_ASSERT(CX_NULL_POINTER!=wd_clone);

			if (CX_NULL_POINTER!=wd_clone)
			{
				wd_clone->move(offset);

				get_widget()->get_container().push_back(wd_clone);
			

				//select(wd_clone);
				{
					wd_clone->set_selected(true);

					get_selected_diagram()->get_container().push_back(wd_clone);
				}


				//-----------------------------------------------------------
				action = true;
			}
		}
	}


	//-----------------------------------------------------------------------
	_paste_action_count++;


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(true);


	//-----------------------------------------------------------------------
	if (action)
	{
		set_modified(true);
		get_edit_history()->record ();

		// select
		on_select_changed(SELECT_CHANGED_ACTION_SELECT);
	}
}

void edit::remove (void)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(CX_TWA_NORMAL, "selected diagram = %d", get_selected_diagram()->get_container().size());


	//-----------------------------------------------------------------------
	if (false==can_remove())
	{
		return;
	}


	//-----------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return;
	}


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(false);


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator f;


	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	

	//-----------------------------------------------------------------------
	for (i =get_selected_diagram()->get_container().begin();
	     i!=get_selected_diagram()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = cast_diagram(w);
		if (wd)
		{
			f = std::find(get_widget()->get_container().begin(), get_widget()->get_container().end(), wd);
			CX_DEBUG_ASSERT(f!=get_widget()->get_container().end());

			get_widget()->get_container().erase(f);

			wd->delete_instance();


			//---------------------------------------------------------------
			action = true;
		}
	}


	//-----------------------------------------------------------------------
	get_selected_diagram()->get_container().clear();


	//-----------------------------------------------------------------------
	get_window_event_handler()->on_update_widget();


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(true);


	//-----------------------------------------------------------------------
	if (action)
	{
		set_modified(true);
		get_edit_history()->record ();

		// unselect all
		on_select_changed(SELECT_CHANGED_ACTION_UNSELECT_ALL);
	}
}

cx::bool_t edit::can_copy (void)
{
	if (get_selected_diagram()->get_container().empty())
	{
		return false;
	}

	return true;
}

cx::bool_t edit::can_cut (void)
{
	//-------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return false;
	}

	return true;
}

cx::bool_t edit::can_paste (void)
{
	//-------------------------------------------------------------------
	update_system_clipboard(false);


	//-------------------------------------------------------------------
	if (get_diagram_clipboard()->get_container().empty())
	{
		return false;
	}

	return true;
}

cx::bool_t edit::can_remove (void)
{
	//-----------------------------------------------------------------------
	if (get_selected_diagram()->get_container().empty())
	{
		return false;
	}

	return true;
}

//===========================================================================
edit_history* edit::get_edit_history (void)
{
	return &_edit_history;
}

void edit::undo (void)
{
	//-----------------------------------------------------------------------
	if (false==can_undo())
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(false);


	//-----------------------------------------------------------------------
	if (true==get_edit_history()->backward())
	{
		action = true;
	}


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(true);


	//-----------------------------------------------------------------------
	get_window_event_handler()->on_update_widget();


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	if (action)
	{
		on_select_changed(SELECT_CHANGED_ACTION_UNDO);
		set_modified(true);
	}
}

void edit::redo (void)
{
	//-----------------------------------------------------------------------
	if (false==can_redo())
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::bool_t action = false;


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(false);


	//-----------------------------------------------------------------------
	if (get_edit_history()->forward())
	{
		action = true;
	}


	//-----------------------------------------------------------------------
	get_edit_history()->set_enabled(true);


	//-----------------------------------------------------------------------
	get_window_event_handler()->on_update_widget();


	//-----------------------------------------------------------------------
	set_redraw();


	//-----------------------------------------------------------------------
	if (action)
	{
		on_select_changed(SELECT_CHANGED_ACTION_REDO);
		set_modified(true);
	}
}

cx::bool_t edit::can_undo (void)
{
	if (0==get_edit_history()->get_count())
	{
		return false;
	}

	if (0==get_edit_history()->get_current())
	{
		return false;
	}

	return true;
}

cx::bool_t edit::can_redo (void)
{
	if (0==get_edit_history()->get_count())
	{
		return false;
	}

	if ((get_edit_history()->get_current()+1)<get_edit_history()->get_count())
	{
		return true;
	}

	return false;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
