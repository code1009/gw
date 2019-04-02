#ifndef INCLUDED__CX__GW__DIAGRAM__EDIT_HISTORY__HPP
#define INCLUDED__CX__GW__DIAGRAM__EDIT_HISTORY__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: edit_history.hpp
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
// Class: edit_timeline
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class edit_timeline
{
public:
	widget_collection _selected_diagram;
	widget_collection _diagram;

public:
	edit_timeline();
	virtual ~edit_timeline();
};


	
/////////////////////////////////////////////////////////////////////////////
//
// Class: edit_history
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class edit_history
{
private:
	edit*      _edit     ;
	cx::bool_t _enabled  ;
	cx::int_t  _max_count;
	cx::int_t  _current  ;

private:
	edit_timeline_pointer_container_t _container;

public:
	edit_history();
	virtual ~edit_history();

public:
	virtual edit* get_edit (void);

public:
	virtual edit_timeline_pointer_container_t& get_container(void);

public:
	virtual void initialize (edit* m);

public:
	virtual cx::bool_t get_enabled(void);
	virtual void       set_enabled(cx::bool_t enabled);

public:
	virtual cx::int_t get_current (void);
	virtual cx::int_t get_count   (void);

public:
	virtual void record (void);

public:
	virtual cx::bool_t forward  (void);
	virtual cx::bool_t backward (void);

public:
	virtual void clear (void);

private:
	cx::bool_t delete_first_timeline   (void);
	cx::bool_t delete_forward_timeline (void);
	cx::bool_t create_current_timeline (void);

	cx::bool_t write_timeline (edit* e, cx::int_t index);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


