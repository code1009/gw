#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class property_accessor
{
private:
	HWND  _control;
	void* _object;

public:
	explicit property_accessor(HWND hwnd);
	virtual ~property_accessor();

public:
	virtual HWND  get_control (void);
	virtual void* get_object  (void);
	virtual void  set_object  (void* o);

public:
	virtual void load_property_to_control (void);
	virtual void set_property_to_control  (void);
	virtual void set_property_from_control(cx::int_t index, LPPROPGRIDITEM item);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class view_property_accessor : public property_accessor
{
private:
	typedef property_accessor base_t;

private:
	cx::int_t _index_begin;
	cx::int_t _index_end  ;

public:
	explicit view_property_accessor(HWND hwnd);
	virtual ~view_property_accessor();

public:
	virtual gw::view* get_view (void);

public:
	virtual void load_property_to_control (void);
	virtual void set_property_to_control  (void);
	virtual void set_property_from_control(cx::int_t index, LPPROPGRIDITEM item);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class widget_property_accessor : public property_accessor
{
private:
	typedef property_accessor base_t;

private:
	cx::int_t _index_begin;
	cx::int_t _index_end  ;

public:
	explicit widget_property_accessor(HWND hwnd);
	virtual ~widget_property_accessor();

public:
	virtual gw::widget* get_widget (void);

public:
	virtual void load_property_to_control (void);
	virtual void set_property_to_control  (void);
	virtual void set_property_from_control(cx::int_t index, LPPROPGRIDITEM item);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_property_accessor : public widget_property_accessor
{
private:
	typedef widget_property_accessor base_t;

private:
	cx::int_t _index_begin;
	cx::int_t _index_end  ;

public:
	explicit diagram_property_accessor(HWND hwnd);
	virtual ~diagram_property_accessor();

public:
	virtual gw::dgrm::diagram* get_diagram (void);

public:
	virtual void load_property_to_control (void);
	virtual void set_property_to_control  (void);
	virtual void set_property_from_control(cx::int_t index, LPPROPGRIDITEM item);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class rectangle_shape_property_accessor : public diagram_property_accessor
{
private:
	typedef diagram_property_accessor base_t;

private:
	cx::int_t _index_begin;
	cx::int_t _index_end  ;

public:
	explicit rectangle_shape_property_accessor(HWND hwnd);
	virtual ~rectangle_shape_property_accessor();

public:
	virtual gw::dgrm::rectangle_shape* get_rectangle_shape (void);

public:
	virtual void load_property_to_control (void);
	virtual void set_property_to_control  (void);
	virtual void set_property_from_control(cx::int_t index, LPPROPGRIDITEM item);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class straight_line_property_accessor : public diagram_property_accessor
{
private:
	typedef diagram_property_accessor base_t;

private:
	cx::int_t _index_begin;
	cx::int_t _index_end  ;

public:
	explicit straight_line_property_accessor(HWND hwnd);
	virtual ~straight_line_property_accessor();

public:
	virtual gw::dgrm::straight_line* get_straight_line (void);

public:
	virtual void load_property_to_control (void);
	virtual void set_property_to_control  (void);
	virtual void set_property_from_control(cx::int_t index, LPPROPGRIDITEM item);
};


