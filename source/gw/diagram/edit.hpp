#ifndef INCLUDED__CX__GW__DIAGRAM__EDIT__HPP
#define INCLUDED__CX__GW__DIAGRAM__EDIT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: edit.hpp
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
// Class: edit
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class edit : public design
{
private:
	edit_action* _edit_action;

	diagram_select_edit_action        _diagram_select_edit_action       ;
	diagram_single_select_edit_action _diagram_single_select_edit_action;
	diagram_move_edit_action          _diagram_move_edit_action         ;
	diagram_add_edit_action           _diagram_add_edit_action          ;
	anchor_move_edit_action           _anchor_move_edit_action          ;

private:
	cx::bool_t _modified;

private:
	cx::bool_t _snap_to_grid;

public:
	typedef enum _select_changed_action_t
	{
		SELECT_CHANGED_ACTION_NONE        ,
		SELECT_CHANGED_ACTION_SELECT      ,
		SELECT_CHANGED_ACTION_SELECT_ALL  ,
		SELECT_CHANGED_ACTION_UNSELECT    ,
		SELECT_CHANGED_ACTION_UNSELECT_ALL,
		SELECT_CHANGED_ACTION_UNDO        ,
		SELECT_CHANGED_ACTION_REDO        
	} select_changed_action_t;

private:
	widget_collection _selected_diagram;

private:
	widget_collection _diagram_clipboard;
	cx::uint_t        _paste_action_count;

private:
	edit_history _edit_history;

public:
	edit();
	virtual ~edit();

	// model 가상함수
public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);
	virtual void       draw    (void);

public:
	virtual void on_mouse_move         (mouse_event* e);
	virtual void on_mouse_lbutton_down (mouse_event* e);
	virtual void on_mouse_lbutton_up   (mouse_event* e);

	virtual void on_mouse_drag_enter (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_over  (mouse_drag_drop_event* e);
	virtual void on_mouse_drag_leave (mouse_drag_drop_event* e);
	virtual void on_mouse_drop       (mouse_drag_drop_event* e);

	// design 가상함수
public:
	virtual void on_diagram_property_changed (diagram_event* e); // from diagram class

public:
	virtual diagram_mode_t get_diagram_mode(void);

public:
	virtual void clear (void);

public:
	virtual cx::bool_t read  (document_reader* io);
	virtual cx::bool_t write (document_writer* io);

	// edit 가상함수
public:
	virtual edit_action* get_edit_action(void);
	virtual void         set_edit_action(edit_action* ea);

	virtual diagram_select_edit_action*        get_diagram_select_edit_action       (void);
	virtual diagram_single_select_edit_action* get_diagram_single_select_edit_action(void);
	virtual diagram_move_edit_action*          get_diagram_move_edit_action         (void);
	virtual diagram_add_edit_action*           get_diagram_add_edit_action          (void);
	virtual anchor_move_edit_action*           get_anchor_move_edit_action          (void);

public:
	virtual void on_edit_action_diagram_modified (void); // from edit_action class

public:
	virtual cx::bool_t get_modified (void);
	virtual void       set_modified (cx::bool_t modified);

	virtual void on_modified (cx::bool_t modified); // from this(edit) class

public:
	virtual point_t to_snapped_point (point_t world);

	virtual cx::bool_t get_snap_to_grid (void);
	virtual void       set_snap_to_grid (cx::bool_t snap_to_grid);

public:
	virtual widget_collection* get_selected_diagram(void);

	virtual void select_in_bounds (rectangle_t bounds);
	virtual void select_all       (void);
	virtual void select           (diagram* wd_item);
	virtual void unselect         (diagram* wd_item);
	virtual void unselect_all     (void);

	virtual void on_select_changed (select_changed_action_t action); // from this(edit) class

public:
	virtual void move(cx::uint_t direction);

public:
	virtual void bring_to_top    (void);
	virtual void send_to_bottom (void);

	virtual cx::bool_t can_bring_to_top    (void);
	virtual cx::bool_t can_send_to_bottom (void);

public:
	virtual void update_system_clipboard (cx::bool_t save);

public:
	virtual widget_collection* get_diagram_clipboard(void);

	virtual void copy   (void);
	virtual void cut    (void);
	virtual void paste  (void);
	virtual void remove (void);

	virtual cx::bool_t can_copy   (void);
	virtual cx::bool_t can_cut    (void);
	virtual cx::bool_t can_paste  (void);
	virtual cx::bool_t can_remove (void);

public:
	virtual edit_history* get_edit_history (void);
	
	virtual void undo (void);
	virtual void redo (void);

	virtual cx::bool_t can_undo (void);
	virtual cx::bool_t can_redo (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


