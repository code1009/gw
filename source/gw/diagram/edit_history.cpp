/////////////////////////////////////////////////////////////////////////////
//
// File: edit_history.cpp
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
#if 1
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
// Class: edit_history
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
edit_timeline::edit_timeline()
{
}

edit_timeline::~edit_timeline()
{
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: edit_history
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
edit_history::edit_history()
{
	_edit      = CX_NULL_POINTER;
	_enabled   = true;
	_max_count = GW_DIAGRAM_EDIT_HISTORY_MAX_COUNT;
	_current   = -1;
}

edit_history::~edit_history()
{
	clear();
}

//===========================================================================
edit* edit_history::get_edit (void)
{
	return _edit;
}

edit_timeline_pointer_container_t& edit_history::get_container(void)
{
	return _container;
}

//===========================================================================
void edit_history::initialize (edit* m)
{
	_edit = m;

	clear();
	create_current_timeline();

	_current++;
}

cx::bool_t edit_history::get_enabled (void)
{
	return _enabled;
}

void edit_history::set_enabled(cx::bool_t enabled)
{
	CX_DEBUG_TRACEF(TW_THISCODE, "%s", enabled ? "TRUE" : "FALSE" );

	_enabled = enabled;
}

//===========================================================================
cx::int_t edit_history::get_current (void)
{
	return _current;
}

cx::int_t edit_history::get_count (void)
{
	return static_cast<cx::int_t>( get_container().size() );
}

//===========================================================================
void edit_history::record (void)
{
	//-----------------------------------------------------------------------
	if (false == get_enabled())
	{
		return;
	}


	//-----------------------------------------------------------------------
	set_enabled(false);


	//-----------------------------------------------------------------------
	if (false==delete_forward_timeline())
	{
		return;
	}

	if (false==create_current_timeline())
	{
		return;
	}

	_current++;


	//-----------------------------------------------------------------------
	if (get_count()==(_max_count+1))
	{
		if (delete_first_timeline())
		{
			_current--;

			CX_DEBUG_ASSERT(get_count()<=_max_count);
		}
	}


	//-----------------------------------------------------------------------
	set_enabled(true);


	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "=============================================================================");
	CX_DEBUG_TRACEF(TW_THISCODE, "%d / %d", get_current(), get_count());
	CX_DEBUG_TRACEF(TW_THISCODE, "=============================================================================");
}

//===========================================================================
cx::bool_t edit_history::forward  (void)
{
	if (0==get_count())
	{
		return false;
	}

	if ((_current+1) < get_count())
	{
		if (false==write_timeline(get_edit(), _current+1))
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	_current++;


	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%d / %d", get_current(), get_count());


	return true;
}

cx::bool_t edit_history::backward (void)
{
	if (0==get_count())
	{
		return false;
	}

	if ((_current-1) >= 0)
	{
		if (false==write_timeline(get_edit(), _current-1))
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	_current--;


	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%d / %d", get_current(), get_count());
	

	return true;
}

//===========================================================================
void edit_history::clear (void)
{
	//-----------------------------------------------------------------------
	edit_timeline_pointer_container_t::iterator i;

	edit_timeline* timeline;


	for(i=get_container().begin(); i!=get_container().end(); i++)
	{
		timeline = (*i);

		timeline->_diagram.delete_container();

		delete timeline;
	}

	get_container().clear();


	//-----------------------------------------------------------------------
	_current = -1;


	//-----------------------------------------------------------------------
	CX_DEBUG_TRACEF(TW_THISCODE, "%d / %d", get_current(), get_count());
}

//===========================================================================
cx::bool_t edit_history::delete_first_timeline (void)
{
	//-----------------------------------------------------------------------
	edit_timeline* timeline;
	

	//-----------------------------------------------------------------------
	edit_timeline_pointer_container_t::iterator f;

	edit_timeline* first_timeline = CX_NULL_POINTER;


	cx::int_t index;
	cx::int_t count;


	count = get_count();

	for (index=0; index<count; index++)
	{
		timeline = get_container()[index];

		timeline->_diagram.delete_container();

		delete timeline;


		if (CX_NULL_POINTER==first_timeline)
		{
			first_timeline = timeline;
		}

		break;
	}

	
	if (first_timeline)
	{
		f = std::find(get_container().begin(), get_container().end(), first_timeline); 
		CX_DEBUG_ASSERT (f!=get_container().end());


		if (f!=get_container().end())
		{
			get_container().erase(f);
		}
	}


	return true;
}

cx::bool_t edit_history::delete_forward_timeline (void)
{
	//-----------------------------------------------------------------------
	edit_timeline* timeline;
	

	//-----------------------------------------------------------------------
	edit_timeline_pointer_container_t::iterator f;

	edit_timeline* first_timeline = CX_NULL_POINTER;


	cx::int_t index;
	cx::int_t count;
	cx::int_t current;

	 
	current = _current;

	count = get_count();

	for(index=current+1; index<count; index++)
	{
		timeline = get_container()[index];

		timeline->_diagram.delete_container();

		delete timeline;


		if (CX_NULL_POINTER==first_timeline)
		{
			first_timeline = timeline;
		}
	}

	
	if (first_timeline)
	{
		f = std::find(get_container().begin(), get_container().end(), first_timeline); 
		CX_DEBUG_ASSERT (f!=get_container().end());


		if (f!=get_container().end())
		{
			get_container().erase(f, get_container().end());
		}
	}


	return true;
}

cx::bool_t edit_history::create_current_timeline (void)
{
	//-----------------------------------------------------------------------
	edit* e;

	
	e = get_edit();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=e);


	//-----------------------------------------------------------------------
	edit_timeline* timeline;


	timeline = new edit_timeline();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=timeline);
	if (CX_NULL_POINTER==timeline)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	diagram* wd_clone;
	

	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;


	//-----------------------------------------------------------------------
	for (i =e->get_widget()->get_container().begin();
	     i!=e->get_widget()->get_container().end();
		 i++)
	{
		w = (*i);


		wd = e->cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();

			if (wd_clone)
			{
				timeline->_diagram.get_container().push_back(wd_clone);

				if ( e->get_selected_diagram()->is_in_collection(wd) )
				{
					timeline->_selected_diagram.get_container().push_back(wd_clone);
				}
			}
		}
	}


	get_container().push_back(timeline);


	return true;
}

cx::bool_t edit_history::write_timeline (edit* e, cx::int_t index)
{
	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=e);
	CX_DEBUG_ASSERT(index<get_count());
	CX_DEBUG_ASSERT(index>=0);

	
	if (CX_NULL_POINTER==e)
	{
		return false;
	}

	if ( !((0<=index) && (index<get_count())) )
	{
		return false;
	}


	//-----------------------------------------------------------------------
	e->get_widget()->delete_container();
	e->get_selected_diagram()->get_container().clear();


	//-----------------------------------------------------------------------
	edit_timeline* timeline;


	timeline = get_container()[index];


	//-----------------------------------------------------------------------
	diagram* wd_clone;
	

	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;


	//-----------------------------------------------------------------------
	for (i =timeline->_diagram.get_container().begin();
	     i!=timeline->_diagram.get_container().end();
		 i++)
	{
		w = (*i);


		wd = e->cast_diagram(w);
		if (wd)
		{
			wd_clone = wd->clone();

			if (wd_clone)
			{
				e->get_widget()->get_container().push_back(wd_clone);

				if ( timeline->_selected_diagram.is_in_collection(wd) )
				{
					e->get_selected_diagram()->get_container().push_back(wd_clone);
				}
			}
		}
	}


	return true;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
