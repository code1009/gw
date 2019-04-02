/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
property_ghost_bar::property_ghost_bar()
{
}

property_ghost_bar::~property_ghost_bar()
{
}

//===========================================================================
std::string property_ghost_bar::get_registered_name (void)
{
	return "widget.control.property_ghost_bar";
}

std::string property_ghost_bar::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
void property_ghost_bar::draw_control (void)
{
	gw::graphic_t g;
	gw::rectangle r;


	g = get_model()->get_graphic();
	r = get_bounds();


	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_model());
	

	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = pl->get_border_width();
	border_hwidth = border_width/2.0f;


	gw::color_t bar_color;

	if (get_selected())
	{
		bar_color = gw::color_t::Black;
	}
	else
	{
		bar_color = pl->get_frame_color();
	}

	
	Pen pen(Color(bar_color.ARGB()), border_width);

	
	g->DrawLine(&pen, pl->get_ghost_bar_position(), r._p0._y, pl->get_ghost_bar_position(), r._p1._y);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void property_ghost_bar_event_handler::on_mouse_pressed (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);

	wc->set_selected(true);
}

void property_ghost_bar_event_handler::on_mouse_released (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);

	wc->set_selected(false);
}

void property_ghost_bar_event_handler::on_mouse_clicked (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);
}

void property_ghost_bar_event_handler::on_mouse_dbclicked (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);
}

void property_ghost_bar_event_handler::on_mouse_hover (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);
}

void property_ghost_bar_event_handler::on_mouse_leave (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);
}

void property_ghost_bar_event_handler::on_mouse_dragging (gw::widget_mouse_event* e)
{
	property_ghost_bar* wc = cx_gw_dynamic_cast<property_ghost_bar*>(e->_widget);


	property_list* pl = cx_gw_dynamic_cast<property_list*>(wc->get_model());


	pl->set_ghost_bar_position(e->_point._x);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
property_control::property_control()
{
	_item = CX_NULL_POINTER;
}

property_control::~property_control()
{
}

//===========================================================================
std::string property_control::get_registered_name (void)
{
	return "widget.control.property_control";
}

std::string property_control::get_class (void)
{
	return get_registered_name();
}

//===========================================================================
void property_control::draw_control (void)
{
	gw::graphic_t g;
	gw::rectangle r;


	g = get_model()->get_graphic();
	r = get_bounds();


	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_model());
	

	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = pl->get_border_width();
	border_hwidth = border_width/2.0f;


	Pen pen(Color(pl->get_frame_color().ARGB()), border_width);


	PointF p[3+7];
	cx::uint_t offset;

	gw::point_t p0;
	gw::point_t p1;

	
	offset = 0u;

#if 1
	p[offset].X = r._p0._x + border_hwidth;
	p[offset].Y = r._p1._y - border_hwidth + border_width;
	offset++;

	p[offset].X = r._p0._x + border_hwidth;
	p[offset].Y = r._p0._y + border_hwidth;
	offset++;
	
	p[offset].X = r._p0._x + border_width + f + pl->get_icon_width() + f + border_hwidth;
	p[offset].Y = r._p0._y + border_hwidth;
	offset++;
#endif

	p[offset].X = r._p0._x + border_width + f + pl->get_icon_width() + f + border_hwidth;
	p[offset].Y = r._p1._y - border_hwidth + border_width;
	offset++;

	p[offset].X = r._p0._x + border_width + f + pl->get_icon_width() + f + border_hwidth;
	p[offset].Y = r._p0._y + border_hwidth;
	offset++;
	
	p[offset].X = r._p0._x + border_width + f + pl->get_icon_width() + f + border_width + f + pl->get_name_width() + f + border_hwidth;
	p[offset].Y = r._p0._y + border_hwidth;
	offset++;

	p[offset].X = r._p0._x + border_width + f + pl->get_icon_width() + f + border_width + f + pl->get_name_width() + f + border_hwidth;
	p[offset].Y = r._p1._y - border_hwidth + border_width;
	offset++;

	p[offset].X = r._p0._x + border_width + f + pl->get_icon_width() + f + border_width + f + pl->get_name_width() + f + border_hwidth;
	p[offset].Y = r._p0._y + border_hwidth;
	offset++;
	
	p[offset].X = r._p1._x - border_hwidth - f;
	p[offset].Y = r._p0._y + border_hwidth;
	offset++;

	p[offset].X = r._p1._x - border_hwidth - f;
	p[offset].Y = r._p1._y - border_hwidth + border_width;
	offset++;

	g->DrawLines(&pen, p, offset);


	if ( get_item() )
	{
		get_item()->draw_icon (g);
		get_item()->draw_name (g);
		get_item()->draw_value(g);
	}
}

//===========================================================================
gw::rectangle_t property_control::get_icon_rectangle (void)
{
	gw::rectangle_t r;


	r = get_bounds();


	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_model());
	

	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = pl->get_border_width();
	border_hwidth = border_width/2.0f;


	f = 0.0f;
	border_width  = pl->get_border_width();
	border_hwidth = border_width/2.0f;


	gw::rectangle r_icon ;


	r_icon ._p0._x = r._p0._x + border_width + f;
	r_icon ._p0._y = r._p0._y + border_width + f;
	r_icon ._p1._x = r._p0._x + border_width + pl->get_icon_width() - 1.0f;
	r_icon ._p1._y = r._p1._y;


	return r_icon;
}

gw::rectangle_t property_control::get_name_rectangle (void)
{
	gw::rectangle_t r;


	r = get_bounds();


	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_model());
	

	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = pl->get_border_width();
	border_hwidth = border_width/2.0f;


	gw::rectangle r_name ;


	r_name ._p0._x = r._p0._x + border_width + f + pl->get_icon_width() + f + border_width;
	r_name ._p0._y = r._p0._y + border_width + f;
	r_name ._p1._x = r._p0._x + border_width + f + pl->get_icon_width() + f + border_width + f + pl->get_name_width() - 1.0f;
	r_name ._p1._y = r._p1._y;


	return r_name;
}

gw::rectangle property_control::get_value_rectangle (void)
{
	gw::rectangle r;


	r = get_bounds();


	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_model());
	

	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = pl->get_border_width();
	border_hwidth = border_width/2.0f;


	gw::rectangle r_value;


	r_value._p0._x = r._p0._x + border_width + f + pl->get_icon_width() + f + border_width + f + pl->get_name_width() + f + border_width;
	r_value._p0._y = r._p0._y + border_width + f;
	r_value._p1._x = r._p1._x - border_width - f - 1.0f;
	r_value._p1._y = r._p1._y;


	return r_value;
}

property_item* property_control::get_item(void)
{
	return _item;
}

void property_control::set_item(property_item* v)
{
	if (_item != v)
	{
		_item = v;
		set_redraw();
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void property_control_event_handler::on_mouse_pressed (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);


//	wc->set_selected(true);
}

void property_control_event_handler::on_mouse_released (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);

//	wc->set_selected(false);
}

void property_control_event_handler::on_mouse_clicked (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);

/*
	if (wc->get_selected())
	{
		wc->set_selected(false);
	}
	else
	{
		wc->set_selected(true);
	}
*/
	
/*	
	CX_DEBUG_ASSERT (CX_NULL_POINTER!=wc->get_item());

	if ( PROPERTY_ITEM_TYPE_CATEGORY == wc->get_item()->get_type() )
	{
		if ( wc->get_icon_rectangle().is_point_in( e->_point ) )
		{
			category_property_item* wc_category = cx_gw_dynamic_cast<category_property_item*>( wc->get_item() );
	

			if (wc_category->is_expanded())
			{
				wc_category->collapse();
			}
			else
			{
				wc_category->expand();
			}
		}
	}
*/
}

void property_control_event_handler::on_mouse_dbclicked (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);
}

void property_control_event_handler::on_mouse_hover (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);
}

void property_control_event_handler::on_mouse_leave (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);
}

void property_control_event_handler::on_mouse_dragging (gw::widget_mouse_event* e)
{
	property_control* wc = cx_gw_dynamic_cast<property_control*>(e->_widget);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::string convert_value_to_string (std::string v)
{
	return v;
}


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
property_value::property_value()
{
}

property_value::~property_value()
{
}

//===========================================================================
property_item* property_value::get_item(void)
{
	return _item;
}

void property_value::set_item(property_item* v)
{
	_item = v;
}

//===========================================================================
std::string property_value::to_string (void)
{
	return "Value";
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
property_item::property_item()
{
	_name  = "noname";

	_control = CX_NULL_POINTER;
}

property_item::~property_item()
{
}

//===========================================================================
cx::uint_t property_item::get_type (void)
{
	return PROPERTY_ITEM_TYPE_NONE;
}

//===========================================================================
property_control* property_item::get_control(void)
{
	return _control;
}

void property_item::set_control(property_control* value)
{
	_control = value;
}

//===========================================================================
std::string property_item::get_name (void)
{
	return _name;
}

property_value* property_item::get_value(void)
{
	return CX_NULL_POINTER;
}

void property_item::set_name (std::string name)
{
	_name = name;
}

void property_item::set_value(property_value* value)
{
}

//===========================================================================
void property_item::draw_icon (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_icon_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (pl->get_frame_color());
	_renderer1.set_line_color (pl->get_frame_color());

	_renderer1.set_line_width (1.0f);

	_renderer1.render(g);
}

void property_item::draw_name (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_name_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (gw::color_t::White);
	_renderer1.set_line_color (gw::color_t::White);
	_renderer1.set_line_width (1.0f);

	
	_renderer2.set_model     (pl);
	_renderer2.set_rectangle (r);

	_renderer2.set_text      ( get_name() );
	_renderer2.set_text_font ();
	_renderer2.set_text_format_alignment (StringAlignmentNear, StringAlignmentCenter);
	_renderer2.set_text_color(gw::color_t::Black);
	

	if ( get_control()->get_selected() )
	{
		_renderer1.set_fill_color(gw::color_t::Blue);
		_renderer1.set_line_color(gw::color_t::Blue);

		_renderer2.set_text_color(gw::color_t::White);
	}


	_renderer1.render(g);
	_renderer2.render(g);
}

void property_item::draw_value (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_value_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (gw::color_t::White);
	_renderer1.set_line_color (gw::color_t::White);

	_renderer1.set_line_width (1.0f);

	
	_renderer3.set_model     (pl);
	_renderer3.set_rectangle (r);

	_renderer3.set_text      ( "Value" );
	_renderer3.set_text_font ();
	_renderer3.set_text_format_alignment (StringAlignmentNear, StringAlignmentCenter);
	_renderer3.set_text_color(gw::color_t::DarkGray);


	_renderer1.render(g);
	_renderer3.render(g);
}

CWnd* property_item::create_inplace_window(HWND hWnd)
{
	return CX_NULL_POINTER;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
category_property_item::category_property_item()
{
}

category_property_item::~category_property_item()
{
}

//===========================================================================
cx::uint_t category_property_item::get_type (void)
{
	return PROPERTY_ITEM_TYPE_CATEGORY;
}

//===========================================================================
void category_property_item::draw_icon (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_icon_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (pl->get_frame_color());
	_renderer1.set_line_color (pl->get_frame_color());

	_renderer1.set_line_width (1.0f);

	_renderer1.render(g);


	_renderer2.set_model     (pl);
	_renderer2.set_rectangle (r);

	if (is_expanded())
	{
		_renderer2.set_text ( "¡å" );
	}
	else
	{
		_renderer2.set_text ( "¢º" );
	}

	_renderer2.set_text_font (GW_DEFAULT_TEXT_FONT_FAMILYNAME, GW_DEFAULT_TEXT_FONT_SIZE, FontStyleBold);
	_renderer2.set_text_format_alignment (StringAlignmentNear, StringAlignmentCenter);
	_renderer2.set_text_color(gw::color_t::Black);
	

	_renderer2.render(g);
}

void category_property_item::draw_name (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_name_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (pl->get_frame_color());
	_renderer1.set_line_color (pl->get_frame_color());
	_renderer1.set_line_width (1.0f);

	
	_renderer2.set_model     (pl);
	_renderer2.set_rectangle (r);

	_renderer2.set_text      ( get_name() );
	_renderer2.set_text_font (GW_DEFAULT_TEXT_FONT_FAMILYNAME, GW_DEFAULT_TEXT_FONT_SIZE, FontStyleBold);
	_renderer2.set_text_format_alignment (StringAlignmentNear, StringAlignmentCenter);
	_renderer2.set_text_color(gw::color_t::Black);
	

	_renderer1.render(g);
	_renderer2.render(g);
}

void category_property_item::draw_value (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_value_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (pl->get_frame_color());
	_renderer1.set_line_color (pl->get_frame_color());

	_renderer1.set_line_width (1.0f);

	
	_renderer1.render(g);
}

//===========================================================================
property_control_pointer_container_t& category_property_item::get_control_container(void)
{
	return _control_container;
}

cx::bool_t category_property_item::is_expanded (void)
{
	return _expanded;
}

void category_property_item::expand (void)
{
	//-----------------------------------------------------------------------
	property_list* pl;
	property_control* pc;


	pc = get_control();
	pl = cx_gw_dynamic_cast<property_list*>(pc->get_model());


	//-----------------------------------------------------------------------
	property_control_pointer_container_t::iterator f;

	gw::widget_pointer_container_t::iterator j;

	property_control_pointer_container_t::iterator i;

	property_control* pc_last;


	pc_last = pc;

	for (i=get_control_container().begin(); i!= get_control_container().end(); i++)
	{
		pc = (*i);

		CX_DEBUG_ASSERT (pc->get_item()->get_type() != PROPERTY_ITEM_TYPE_CATEGORY);


		f = std::find(pl->get_control_container().begin(), pl->get_control_container().end(), pc_last);
		CX_DEBUG_ASSERT(f!=pl->get_control_container().end());

		pl->get_control_container().insert(++f, pc);


		j = std::find(pl->get_widget()->get_container().begin(), pl->get_widget()->get_container().end(), pc_last);
		CX_DEBUG_ASSERT(j!=pl->get_widget()->get_container().end());

		pl->get_widget()->get_container().insert(++j, pc);


		pc_last = pc;
	}

	
	//-----------------------------------------------------------------------
	get_control_container().clear();


	//-----------------------------------------------------------------------
	_expanded = true;


	//-----------------------------------------------------------------------
	pl->set_redraw();
}

void category_property_item::collapse (void)
{
	//-----------------------------------------------------------------------
	property_list* pl;
	property_control* pc;


	pc = get_control();
	pl = cx_gw_dynamic_cast<property_list*>(pc->get_model());


	//-----------------------------------------------------------------------
	//CX_DEBUG_ASSERT(get_control_container().empty()==true);


	//-----------------------------------------------------------------------
	property_control_pointer_container_t::iterator f;


	f = std::find(pl->get_control_container().begin(), pl->get_control_container().end(), pc);
	CX_DEBUG_ASSERT(f!=pl->get_control_container().end());


	//-----------------------------------------------------------------------
	property_control_pointer_container_t::iterator i;


	for (i=(++f); i!=pl->get_control_container().end(); i++)
	{
		pc = (*i);

		if (pc->get_item()->get_type() == PROPERTY_ITEM_TYPE_CATEGORY)
		{
			break;
		}
		else
		{
			get_control_container().push_back(pc);
		}
	}


	//-----------------------------------------------------------------------
	gw::widget_pointer_container_t::iterator j;


	for (i=get_control_container().begin(); i!= get_control_container().end(); i++)
	{
		pc = (*i);

		f = std::find(pl->get_control_container().begin(), pl->get_control_container().end(), pc);
		CX_DEBUG_ASSERT(f!=pl->get_control_container().end());
		pl->get_control_container().erase(f);
		
		
		j = std::find(pl->get_widget()->get_container().begin(), pl->get_widget()->get_container().end(), pc);
		CX_DEBUG_ASSERT(j!=pl->get_widget()->get_container().end());
		pl->get_widget()->get_container().erase(j);
	}


	//-----------------------------------------------------------------------
	_expanded = false;


	//-----------------------------------------------------------------------
	pl->set_redraw();
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
read_only_string_property_item::read_only_string_property_item()
{
	_value.set_item(this);
}

read_only_string_property_item::~read_only_string_property_item()
{
}

//===========================================================================
cx::uint_t read_only_string_property_item::get_type (void)
{
	return PROPERTY_ITEM_TYPE_VALUE;
}

//===========================================================================
property_value* read_only_string_property_item::get_value(void)
{
	return &_value;
}

void read_only_string_property_item::set_value(property_value* value)
{
	property_string_value_t* v1;
	property_string_value_t* v2;


	v1 = cx_gw_dynamic_cast< property_string_value_t* >( value       );
	v2 = cx_gw_dynamic_cast< property_string_value_t* >( get_value() );
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=v1);
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=v2);

	v2->set(v1->get());
}

//===========================================================================
void read_only_string_property_item::draw_icon (gw::graphic_t g)
{
	property_item::draw_icon(g);
}

void read_only_string_property_item::draw_name (gw::graphic_t g)
{
	property_item::draw_name(g);
}

void read_only_string_property_item::draw_value (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_value_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (gw::color_t::White);
	_renderer1.set_line_color (gw::color_t::White);

	_renderer1.set_line_width (1.0f);

	
	_renderer3.set_model     (pl);
	_renderer3.set_rectangle (r);

	_renderer3.set_text      ( get_value()->to_string() );
	_renderer3.set_text_font ();
	_renderer3.set_text_format_alignment (StringAlignmentNear, StringAlignmentCenter);
	_renderer3.set_text_color(gw::color_t::DarkGray);


	_renderer1.render(g);
	_renderer3.render(g);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
string_property_item::string_property_item()
{
	_value.set_item(this);
}

string_property_item::~string_property_item()
{
}

//===========================================================================
cx::uint_t string_property_item::get_type (void)
{
	return PROPERTY_ITEM_TYPE_VALUE;
}

//===========================================================================
property_value* string_property_item::get_value(void)
{
	return &_value;
}

void string_property_item::set_value(property_value* value)
{
	property_string_value_t* v1;
	property_string_value_t* v2;


	v1 = cx_gw_dynamic_cast< property_string_value_t* >( value       );
	v2 = cx_gw_dynamic_cast< property_string_value_t* >( get_value() );
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=v1);
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=v2);

	v2->set(v1->get());
}

//===========================================================================
void string_property_item::draw_icon (gw::graphic_t g)
{
	property_item::draw_icon(g);
}

void string_property_item::draw_name (gw::graphic_t g)
{
	property_item::draw_name(g);
}

void string_property_item::draw_value (gw::graphic_t g)
{
	property_list* pl = cx_gw_dynamic_cast<property_list*>(get_control()->get_model());
	gw::rectangle  r  = get_control()->get_value_rectangle();


	_renderer1.set_model     (pl);
	_renderer1.set_rectangle (r);

	_renderer1.set_fill_color (gw::color_t::White);
	_renderer1.set_line_color (gw::color_t::White);

	_renderer1.set_line_width (1.0f);

	
	_renderer3.set_model     (pl);
	_renderer3.set_rectangle (r);

	_renderer3.set_text      ( get_value()->to_string() );
	_renderer3.set_text_font ();
	_renderer3.set_text_format_alignment (StringAlignmentNear, StringAlignmentCenter);
	_renderer3.set_text_color(gw::color_t::Black);


	_renderer1.render(g);
	_renderer3.render(g);
}

CWnd* string_property_item::create_inplace_window(HWND hWnd)
{
	property_string_value_t* v;


	v = cx_gw_dynamic_cast< property_string_value_t* >( get_value() );


	gw::rectangle r;
	cx::int_t x;
	cx::int_t y;

    RECT rc;


	r = get_control()->get_value_rectangle();
	get_control()->get_model()->get_view()->world_to_viewport_window(r._p0, x, y);
	rc.left = x;
	rc.top  = y+3;
	get_control()->get_model()->get_view()->world_to_viewport_window(r._p1, x, y);
	rc.right  = x;
	rc.bottom = y;

    
	CInplaceEditWindow* w = new CInplaceEditWindow();
    
    	
//	w->Create(hWnd, rc, v->get().c_str(), WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOHSCROLL);
	w->Create(hWnd);
	w->MoveWindow(rc);
	w->SetWindowText(v->get().c_str());

	HFONT hFont = (HFONT)::SendMessage(hWnd, WM_GETFONT, 0, 0);
	w->SetFont( hFont  );
//	w->SetMargins(2+8, 8);
	w->SetMargins(4, 0);

	CX_DEBUG_ASSERT(::IsWindow(*w)==TRUE);


    return w;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: property_list
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
property_list::property_list()
{
	_border_width = 1.0f;

	_control_height = 24.0f;

	_icon_width =  16.0f;
	_name_width = PROPERTY_LIST_NAME_WIDTH_DEFAULT;

	_ghost_bar = CX_NULL_POINTER;

	_selected_item = CX_NULL_POINTER;

	_inplace_window = CX_NULL_POINTER;
}

property_list::~property_list()
{
}

//===========================================================================
cx::bool_t property_list::create(gw::widget_entry_collection* wec)
{
	if (false == gw::ctrl::form::create(wec))
	{
		return false;
	}


	std::string               wc;
	gw::widget_event_handler* weh;


	wc  = property_control::get_registered_name();
	weh = new property_control_event_handler();

	if (false == get_widget_event_handler()->add(wc, weh))
	{
		delete weh;

		return false;
	}


	wc  = property_ghost_bar::get_registered_name();
	weh = new property_ghost_bar_event_handler();

	if (false == get_widget_event_handler()->add(wc, weh))
	{
		delete weh;

		return false;
	}

	
	get_view()->set_background_color(gw::color_t::White);


	_ghost_bar = new property_ghost_bar();
	_ghost_bar->set_model(this);
	_ghost_bar->initialize();
	get_widget()->get_container().push_back( _ghost_bar );


//	property_item* p;
	category_property_item* category;	
	read_only_string_property_item* read_only_string;
	property_string_value_t  string_value;
	string_property_item* text;

	category = new category_property_item();
	add_item(category);
	category->set_name("category1");

	read_only_string = new read_only_string_property_item();
	add_item(read_only_string);
	read_only_string->set_name("name1");
	string_value.set("text1");
	read_only_string->set_value(&string_value);

	text = new string_property_item();
	add_item(text);
	text->set_name("name3");
	string_value.set("text3");
	text->set_value(&string_value);


	read_only_string = new read_only_string_property_item();
	add_item(read_only_string);
	read_only_string->set_name("name2");
	string_value.set("text2");
	read_only_string->set_value(&string_value);

	category = new category_property_item();
	category->set_name("category2");
	add_item(category);

	add_item(new property_item());
	add_item(new property_item());

	return true;
}

void property_list::destroy (void)
{
	destroy_inplace_window();


	gw::ctrl::form::destroy();


	property_item_pointer_container_t::iterator i;
	property_control_pointer_container_t::iterator j;

	property_item* pi;
	category_property_item* pi_category;
	property_control* pc;


	for (i = get_item_container().begin(); i != get_item_container().end(); i++)
	{
		pi = (*i);

		if (pi->get_type() == PROPERTY_ITEM_TYPE_CATEGORY)
		{
			pi_category = cx_gw_dynamic_cast<category_property_item*>(pi);
			CX_DEBUG_ASSERT(CX_NULL_POINTER!=pi_category);

			for (j = pi_category->get_control_container().begin(); j != pi_category->get_control_container().end(); j++)
			{
				pc = (*j);

				pc->delete_instance();
			}
		}

		delete pi;
	}

	get_item_container().clear();
	get_control_container().clear();
}

void property_list::draw (void)
{
	gw::graphic_t g;

	g = get_graphic();
	CX_DEBUG_ASSERT(CX_NULL_POINTER!=g);

	draw_background(g);

	gw::model::draw();
}

//===========================================================================
void property_list::on_widget_mouse_clicked (gw::widget_mouse_event* e)
{
	gw::ctrl::control* wc = cx_gw_dynamic_cast<gw::ctrl::control*>(e->_widget);

	
	CX_DEBUG_ASSERT (CX_NULL_POINTER!=wc);


	if ( wc->get_class()==property_control::get_registered_name() )
	{
		property_control* wc_property_control = cx_gw_dynamic_cast<property_control*>(e->_widget);

	
		CX_DEBUG_ASSERT (CX_NULL_POINTER!=wc_property_control->get_item());

	
		if ( PROPERTY_ITEM_TYPE_CATEGORY == wc_property_control->get_item()->get_type() )
		{
			if ( wc_property_control->get_icon_rectangle().is_point_in( e->_point ) )
			{
				category_property_item* category = cx_gw_dynamic_cast<category_property_item*>( wc_property_control->get_item() );
	

				if (category->is_expanded())
				{
					category->collapse();
				}
				else
				{
					category->expand();
				}
			
				resize_control(get_view()->get_viewport_window_xsize(), get_view()->get_viewport_window_ysize());
			}
		}
		else
		{
			select_item(wc_property_control->get_item());
		}
	}
}

void property_list::on_widget_mouse_dbclicked (gw::widget_mouse_event* e)
{
	gw::ctrl::control* wc = cx_gw_dynamic_cast<gw::ctrl::control*>(e->_widget);

	
	CX_DEBUG_ASSERT (CX_NULL_POINTER!=wc);


	if ( wc->get_class()==property_control::get_registered_name() )
	{
		property_control* wc_property_control = cx_gw_dynamic_cast<property_control*>(e->_widget);

	
		CX_DEBUG_ASSERT (CX_NULL_POINTER!=wc_property_control->get_item());

	
		if ( PROPERTY_ITEM_TYPE_CATEGORY == wc_property_control->get_item()->get_type() )
		{
			category_property_item* category = cx_gw_dynamic_cast<category_property_item*>( wc_property_control->get_item() );
	

			if (category->is_expanded())
			{
				category->collapse();
			}
			else
			{
				category->expand();
			}
			
			resize_control(get_view()->get_viewport_window_xsize(), get_view()->get_viewport_window_ysize());
		}
	}
}

void property_list::on_widget_mouse_pressed (gw::widget_mouse_event* e)
{
}

void property_list::on_widget_mouse_released (gw::widget_mouse_event* e)
{
}

//===========================================================================
void property_list::resize_control (cx::int_t window_cx, cx::int_t window_cy)
{
	//-----------------------------------------------------------------------
	gw::ctrl::wh_layout l(true);

	gw::coordinates_t item_xsize;
	gw::coordinates_t item_ysize;


	item_ysize = get_border_width() + get_control_height();
	if (window_cx < static_cast<gw::coordinates_t>(100.0f))
	{
		item_xsize = static_cast<gw::coordinates_t>(100.0f);
	}
	else
	{
		item_xsize = static_cast<gw::coordinates_t>(window_cx);
	}


	//-----------------------------------------------------------------------
	cx::uint_t i;
	cx::uint_t count;


	l.begin(gw::point_t(0,0), 0,0);

	l.set_item_size(item_xsize,item_ysize);


	count = _control_container.size();
	for (i=0u; i<count; i++)
	{
		l.add_control(_control_container[i]);

		//if ( (i!=0u) && (0u==((i+1)%32)) )
		//{
		//	l.separate();
		//}
	}

	l.end();


	//-----------------------------------------------------------------------
	gw::rectangle_t r;


	r = l.get_bounds();
	get_view()->set_wolrd_rectangle(gw::rectangle_t(r._p1._x,r._p1._y));



	//-----------------------------------------------------------------------
	gw::rectangle_t r_ghost_bar;


	r_ghost_bar = r;

	r_ghost_bar._p0._x = get_ghost_bar_position() - 2.0f;
	r_ghost_bar._p1._x = get_ghost_bar_position() + 2.0f; 

	_ghost_bar->set_bounds(r_ghost_bar);
}

//===========================================================================
property_item_pointer_container_t& property_list::get_item_container (void)
{
	return _item_container;
}

property_control_pointer_container_t& property_list::get_control_container(void)
{
	return _control_container;
}

//===========================================================================
gw::coordinates_t property_list::get_ghost_bar_position(void)
{
	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = get_border_width();
	border_hwidth = border_width/2.0f;


	gw::rectangle_t r;


	r = get_view()->get_wolrd_rectangle();

	
	return r._p0._x + border_width + f +get_icon_width() + f + border_width + f + get_name_width() + f + border_hwidth;
}

void property_list::set_ghost_bar_position(gw::coordinates_t v)
{
	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;


	f = 0.0f;
	border_width  = get_border_width();
	border_hwidth = border_width/2.0f;


	gw::rectangle_t r;
	gw::coordinates_t fixed;
	gw::coordinates_t d;


	r = get_view()->get_wolrd_rectangle();
	fixed = r._p0._x + border_width + f +get_icon_width() + f + border_width + f + f + border_hwidth;
	d = v - fixed;
	if (d<PROPERTY_LIST_NAME_WIDTH_MIN)
	{
		return;
	}
	if (d>PROPERTY_LIST_NAME_WIDTH_MAX)
	{
		return;
	}
	
	_name_width = d;

	
	resize_control(get_view()->get_viewport_window_xsize(), get_view()->get_viewport_window_ysize());
}

//===========================================================================
/*
 icon_width                 ghost_bar       
   |                            |
   +                            +
+-----+-------------------------+--------------------------------------------------+
|  +  | name_width              | value_width                                      | control_height
+-----+-------------------------+--------------------------------------------------+
*/
cx::float_t property_list::get_border_width (void)
{
	return _border_width;
}

gw::coordinates_t property_list::get_control_height(void)
{
	return _control_height;
}

gw::coordinates_t property_list::get_icon_width (void)
{
	return _icon_width;
}

gw::coordinates_t property_list::get_name_width (void)
{
	return _name_width;
}

gw::color_t property_list::get_frame_color(void)
{
	gw::color_t c(0xECu,0xECu,0xECu);

	return c;
}

//===========================================================================
property_item* property_list::add_item (property_item* item)
{
	//-----------------------------------------------------------------------
	gw::widget_pointer_container_t::iterator f;


	f = std::find(get_widget()->get_container().begin(), get_widget()->get_container().end(), _ghost_bar);
	CX_DEBUG_ASSERT(f!=get_widget()->get_container().end());
	get_widget()->get_container().erase(f);


	//-----------------------------------------------------------------------
	property_control* pc;


	pc = new property_control();
	pc->set_model(this);
	pc->initialize();
	get_widget()->get_container().push_back(pc);


	//-----------------------------------------------------------------------
	pc->set_item(item);
	_control_container.push_back(pc);

	item->set_control(pc);
	_item_container.push_back(item);	


	//-----------------------------------------------------------------------
	resize_control(get_view()->get_viewport_window_xsize(), get_view()->get_viewport_window_ysize());


	//-----------------------------------------------------------------------
	get_widget()->get_container().push_back(_ghost_bar);


	return item;
}

void property_list::select_item (property_item* item)
{
	property_item_pointer_container_t::iterator i;

	property_item* pi;
	property_control* pc;

	category_property_item* pi_category;


	for (i = get_item_container().begin(); i != get_item_container().end(); i++)
	{
		pi = (*i);
		pc = pi->get_control();


		if (pi->get_type() == PROPERTY_ITEM_TYPE_CATEGORY)
		{
			pi_category = cx_gw_dynamic_cast<category_property_item*>(pi);

			pc->set_selected(false);
		}
		else
		{
			if (pi == item)
			{
				pc->set_selected(true);
			}
			else
			{
				pc->set_selected(false);
			}
		}
	}

	if (_selected_item!=item)
	{
		_selected_item=item;

		on_item_select_changed();
	}
}

property_item* property_list::get_selected_item (void)
{
	return _selected_item;
}

void property_list::draw_background (gw::graphic_t g)
{
	gw::rectangle r = get_view()->get_wolrd_rectangle();


	cx::float_t border_width ;
	cx::float_t border_hwidth;
	cx::float_t f;

	f = 1.0f;
	border_width  = get_border_width();
	border_hwidth = border_width/2.0f;


	Pen pen(Color(get_frame_color().ARGB()), border_width);


	gw::point_t p0;
	gw::point_t p1;

	p0._x = r._p0._x;	
	p0._y = r._p1._y + border_width - border_hwidth + f;
	p1._x = r._p1._x;
	p1._y = r._p1._y + border_width - border_hwidth + f;
	g->DrawLine(&pen, p0._x, p0._y, p1._x, p1._y);
}


void property_list::on_item_select_changed(void)
{
	destroy_inplace_window();


	property_item* selected_item = get_selected_item();


	if (CX_NULL_POINTER!=selected_item)
	{
		create_inplace_window(selected_item);
	}
}

CWnd* property_list::get_inplace_window (void)
{
	return _inplace_window;
}

void property_list::create_inplace_window(property_item* item)
{
	destroy_inplace_window();

	
	HWND hwnd = get_window();


	_inplace_window = item->create_inplace_window(hwnd);
	if (_inplace_window)
	{
		::SetWindowPos(*_inplace_window, HWND_TOP, 0,0,0,0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	set_redraw();
}

void property_list::destroy_inplace_window()
{
	HWND hwnd_owner = get_window();
	HWND hwnd_focus = ::GetFocus();


	if (_inplace_window)
	{
		if ( _inplace_window->IsWindow() )
		{
			if( hwnd_focus != hwnd_owner && ::IsChild(hwnd_owner, hwnd_focus) )
			{
				::SetFocus (hwnd_owner);
			}

			_inplace_window->Destroy();
		}

		delete _inplace_window;
	}

	_inplace_window = CX_NULL_POINTER;

	set_redraw();
}

