#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_value;
class property_item;
class	category_property_item;

class property_control;
class property_list;



//===========================================================================
typedef std::vector<property_item*> property_item_pointer_container_t;
typedef std::vector<property_control*> property_control_pointer_container_t;

//===========================================================================
#define PROPERTY_LIST_NAME_WIDTH_DEFAULT 100.0f
#define PROPERTY_LIST_NAME_WIDTH_MIN      50.0f
#define PROPERTY_LIST_NAME_WIDTH_MAX     200.0f



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef enum _property_item_type_t
{
	PROPERTY_ITEM_TYPE_NONE     = 0,
	PROPERTY_ITEM_TYPE_CATEGORY = 1,
	PROPERTY_ITEM_TYPE_VALUE    = 2
} property_item_type_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_ghost_bar : public gw::ctrl::control
{
public:
	gw::rectangle_renderer _renderer1;

public:
	property_ghost_bar();
	virtual ~property_ghost_bar();

	// gw::widget
public:
	static std::string  get_registered_name (void);
	virtual std::string get_class (void);

	// gw::ctrl::control
	virtual void draw_control (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_ghost_bar_event_handler : public gw::ctrl::control_event_handler
{
public:
	virtual void on_mouse_pressed  (gw::widget_mouse_event* e);
	virtual void on_mouse_released (gw::widget_mouse_event* e);
	virtual void on_mouse_clicked  (gw::widget_mouse_event* e);
	virtual void on_mouse_dbclicked(gw::widget_mouse_event* e);
	virtual void on_mouse_hover    (gw::widget_mouse_event* e);
	virtual void on_mouse_leave    (gw::widget_mouse_event* e);
	virtual void on_mouse_dragging (gw::widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_control : public gw::ctrl::control
{
private:
	property_item* _item;

public:
	property_control();
	virtual ~property_control();

	// gw::widget
public:
	static std::string  get_registered_name (void);
	virtual std::string get_class (void);

	// gw::ctrl::control
	virtual void draw_control (void);

	// property_control
public:
	virtual gw::rectangle get_icon_rectangle  (void);
	virtual gw::rectangle get_name_rectangle  (void);
	virtual gw::rectangle get_value_rectangle (void);

public:
	virtual property_item* get_item(void);
	virtual void           set_item(property_item* v);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_control_event_handler : public gw::ctrl::control_event_handler
{
public:
	virtual void on_mouse_pressed  (gw::widget_mouse_event* e);
	virtual void on_mouse_released (gw::widget_mouse_event* e);
	virtual void on_mouse_clicked  (gw::widget_mouse_event* e);
	virtual void on_mouse_dbclicked(gw::widget_mouse_event* e);
	virtual void on_mouse_hover    (gw::widget_mouse_event* e);
	virtual void on_mouse_leave    (gw::widget_mouse_event* e);
	virtual void on_mouse_dragging (gw::widget_mouse_event* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::string convert_value_to_string (std::string v);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_value
{
public:
	property_item* _item;

public:
	property_value();
	virtual ~property_value();

public:
	virtual property_item* get_item(void);
	virtual void           set_item(property_item* v);

public:
	virtual std::string to_string (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
template<typename T>
class property_type_value : public property_value
{
private:
	typename T _value;

public:
	property_type_value()
	{
	}

	virtual ~property_type_value()
	{
	}

public:
	virtual std::string to_string (void)
	{
		std::string s;

		s = convert_value_to_string(get());

		return s;
	}

public:
	typename T get (void)
	{
		return _value;
	}

	void set (typename T v)
	{
		if ( _value != v )
		{
			_value = v;

			if ( get_item() )
			{
				if ( get_item()->get_control() )
				{
					get_item()->get_control()->set_redraw();
				}
			}
		}
	}
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef property_type_value<std::string> property_string_value_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_item
{
private:
	std::string _name;

private:
	property_control* _control;

protected:
	gw::rectangle_renderer      _renderer1;
	gw::text_rectangle_renderer _renderer2;
	gw::text_rectangle_renderer _renderer3;

public:
	property_item();
	virtual ~property_item();

public:
	virtual cx::uint_t get_type (void);

public:
	virtual property_control* get_control(void);
	virtual void              set_control(property_control* value);

public:
	virtual std::string     get_name (void);
	virtual property_value* get_value(void);

	virtual void set_name (std::string     name);
	virtual void set_value(property_value* value);

public:
	virtual void draw_icon  (gw::graphic_t g);
	virtual void draw_name  (gw::graphic_t g);
	virtual void draw_value (gw::graphic_t g);

public:
	virtual CWnd* create_inplace_window(HWND hWnd);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class category_property_item : public property_item
{
private:
	property_control_pointer_container_t _control_container;
	cx::bool_t _expanded;

public:
	category_property_item();
	virtual ~category_property_item();

public:
	virtual cx::uint_t get_type (void);

public:
	virtual void draw_icon  (gw::graphic_t g);
	virtual void draw_name  (gw::graphic_t g);
	virtual void draw_value (gw::graphic_t g);

public:
	property_control_pointer_container_t& get_control_container(void);

public:
	cx::bool_t is_expanded (void);
	void       expand      (void);
	void       collapse    (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class read_only_string_property_item : public property_item
{
private:
	property_string_value_t _value;

public:
	read_only_string_property_item();
	virtual ~read_only_string_property_item();

public:
	virtual cx::uint_t get_type (void);

public:
	virtual property_value* get_value(void);
	virtual void            set_value(property_value* value);

public:
	virtual void draw_icon  (gw::graphic_t g);
	virtual void draw_name  (gw::graphic_t g);
	virtual void draw_value (gw::graphic_t g);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class string_property_item : public property_item
{
private:
	property_string_value_t _value;

public:
	string_property_item();
	virtual ~string_property_item();

public:
	virtual cx::uint_t get_type (void);

public:
	virtual property_value* get_value(void);
	virtual void            set_value(property_value* value);

public:
	virtual void draw_icon  (gw::graphic_t g);
	virtual void draw_name  (gw::graphic_t g);
	virtual void draw_value (gw::graphic_t g);

public:
	virtual CWnd* create_inplace_window(HWND hWnd);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_list : public gw::ctrl::form
{
private:
	property_item_pointer_container_t    _item_container;
	property_control_pointer_container_t _control_container;

	property_ghost_bar* _ghost_bar;

	property_item* _selected_item;

	CWnd* _inplace_window;

private:
	cx::float_t       _border_width;
	gw::coordinates_t _control_height;
	gw::coordinates_t _icon_width;
	gw::coordinates_t _name_width;

public:
	property_list();
	virtual ~property_list();

public:
	virtual cx::bool_t create  (gw::widget_entry_collection* wec);
	virtual void       destroy (void);
	virtual void       draw    (void);

public:
	virtual void on_widget_mouse_clicked   (gw::widget_mouse_event* e);
	virtual void on_widget_mouse_dbclicked (gw::widget_mouse_event* e);
	virtual void on_widget_mouse_pressed   (gw::widget_mouse_event* e);
	virtual void on_widget_mouse_released  (gw::widget_mouse_event* e);

public:
	void resize_control (cx::int_t window_cx, cx::int_t window_cy);

public:
	property_item_pointer_container_t&    get_item_container   (void);
	property_control_pointer_container_t& get_control_container(void);

public:
	gw::coordinates_t get_ghost_bar_position(void);
	void              set_ghost_bar_position(gw::coordinates_t v);

public:
	cx::float_t       get_border_width  (void);
	gw::coordinates_t get_control_height(void);
	gw::coordinates_t get_icon_width (void);
	gw::coordinates_t get_name_width (void);
	gw::color_t       get_frame_color(void);

public:
	property_item* add_item (property_item* item);
	void select_item (property_item* item);

	property_item* get_selected_item (void);

public:
	void draw_background (gw::graphic_t g);

public:
	virtual void on_item_select_changed(void);

public:
	CWnd* get_inplace_window (void);
	void create_inplace_window(property_item* item);
	void destroy_inplace_window();
};
	

