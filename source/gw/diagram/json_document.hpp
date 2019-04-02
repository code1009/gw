#ifndef INCLUDED__CX__GW__DIAGRAM__JSON_DOCUMENT__HPP
#define INCLUDED__CX__GW__DIAGRAM__JSON_DOCUMENT__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: json_document.hpp
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
//===========================================================================
std::string get_json_string       (std::string v);
std::string get_json_string_float (cx::float_t v);
std::string get_json_string_uint  (cx::uint_t  v);
std::string get_json_string_int   (cx::int_t   v);
std::string get_json_string_bool  (cx::bool_t  v);
std::string get_json_string_color (color_t     v);

std::string get_json_value_string(std::string json_string);
cx::float_t get_json_value_float (std::string json_string);
cx::uint_t  get_json_value_uint  (std::string json_string);
cx::int_t   get_json_value_int   (std::string json_string);
cx::bool_t  get_json_value_bool  (std::string json_string);
color_t     get_json_value_color (std::string json_string);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cx::bool_t get_json_value_string_of_json_object (cx::json_dom_node* current, std::string name, std::string& value);
cx::bool_t get_json_value_float_of_json_object  (cx::json_dom_node* current, std::string name, cx::float_t& value);
cx::bool_t get_json_value_uint_of_json_object   (cx::json_dom_node* current, std::string name, cx::uint_t& value);
cx::bool_t get_json_value_int_of_json_object    (cx::json_dom_node* current, std::string name, cx::int_t& value);
cx::bool_t get_json_value_bool_of_json_object   (cx::json_dom_node* current, std::string name, cx::bool_t& value);
cx::bool_t get_json_value_color_of_json_object  (cx::json_dom_node* current, std::string name, color_t& value);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _json_document_view_parameter_t
{
	color_t     background_color ;
	rectangle_t wolrd_rectangle  ;
	cx::float_t viewscale        ;
	cx::int_t   grid_xsize       ;
	cx::int_t   grid_ysize       ;
	cx::bool_t  grid_visible     ;
	cx::bool_t  snap_to_grid     ;
}
json_document_view_parameter_t;


	
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void set_default_json_document_view_parameter(json_document_view_parameter_t* v);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
json_document_reader(cx::uint_t flag, std::string s)
json_document_writer(cx::uint_t flag, std::string s)

# flag 설명
	0: 파일경로
	1: string으로 Copy/Paste를 위해 diagram만 읽고 쓰기
*/



/////////////////////////////////////////////////////////////////////////////
//
// Class: json_document_reader
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class json_document_reader : public document_reader
{
private:
	cx::json_dom_node* _json_root_pointer;
	cx::json_dom_node* _json_current_pointer;

private:
	json_document_view_parameter_t _view_parameter;

private:
	cx::uint_t  _flag;
	std::string _string;
	std::string _file_path;

public:
	explicit json_document_reader(std::string file_path);
	explicit json_document_reader(cx::uint_t flag, std::string s);
	virtual ~json_document_reader();
	
	// document_reader 가상함수
public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);
public:
	virtual cx::bool_t read (model* m, widget_collection* collection);

public:
	cx::json_dom_node* get_json_root    (void);
	cx::json_dom_node* get_json_current (void);
	void               set_json_current (cx::json_dom_node* node);

public:
	cx::bool_t read_from_string        (design* m, widget_collection* collection);
	cx::bool_t read_from_file          (design* m, widget_collection* collection);
	cx::bool_t read_from_buffer        (design* m, widget_collection* collection, cx::byte_t* buffer_pointer, cx::uint_t buffer_size);
	cx::bool_t read_root               (design* m, widget_collection* collection);
	cx::bool_t read_document           (design* m, widget_collection* collection);
	cx::bool_t read_view_parameter     (design* m, widget_collection* collection);
	cx::bool_t read_diagram_collection (design* m, widget_collection* collection);
	cx::bool_t read_diagram            (design* m, widget_collection* collection);

public:
	json_document_view_parameter_t* get_view_parameter(void);

public:
	void reset_view_parameter(void);
};



/////////////////////////////////////////////////////////////////////////////
//
// Class: json_document_writer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class json_document_writer : public document_writer
{
private:
	cx::json_writer _json_writer;

private:
	json_document_view_parameter_t _view_parameter;

private:
	cx::uint_t  _flag;
	std::string _string;
	std::string _file_path;

public:
	explicit json_document_writer(std::string file_path);
	explicit json_document_writer(cx::uint_t flag, std::string s);
	virtual ~json_document_writer();

	// document_writer 가상함수
public:
	virtual cx::bool_t create  (widget_entry_collection* wec);
	virtual void       destroy (void);
public:
	virtual cx::bool_t write (model* m, widget_collection* collection);

public:
	cx::json_writer* get_json_writer (void);

public:
	cx::bool_t write_document           (design* m, widget_collection* collection);
	cx::bool_t write_view_parameter     (design* m, widget_collection* collection);
	cx::bool_t write_diagram_collection (design* m, widget_collection* collection);
	cx::bool_t write_diagram            (design* m, diagram* wd);
	cx::bool_t write_to_file            (void);
	cx::bool_t write_to_string          (void);

public:
	std::string& get_string (void);

public:
	json_document_view_parameter_t* get_view_parameter(void);

public:
	void reset_view_parameter(void);
	void set_view_parameter  (design* m);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


