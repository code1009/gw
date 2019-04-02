/////////////////////////////////////////////////////////////////////////////
//
// File: document.cpp
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
std::string get_json_string (std::string v)
{
	return v;
}

std::string get_json_string_float (cx::float_t v)
{
	cx::char_t buffer[256];


	sprintf (buffer, "%f", v);


	return buffer;
}

std::string get_json_string_uint (cx::uint_t v)
{
	cx::char_t buffer[32];


	sprintf (buffer, "%d", v);


	return buffer;
}

std::string get_json_string_int (cx::int_t v)
{
	cx::char_t buffer[32];


	sprintf (buffer, "%d", v);


	return buffer;
}

std::string get_json_string_bool (cx::bool_t v)
{
	std::string json_string;


	json_string = v ? "true" : "false";


	return json_string;
}

std::string get_json_string_color (color_t v)
{
	cx::char_t buffer[32];


	sprintf (buffer, "#%08X", v.ARGB());


	return buffer;
}

//===========================================================================
std::string get_json_value_string (std::string json_string)
{
//	std::string mbcs;


//	mbcs = cx::utf8_to_mbcs(json_string);

	return json_string;
}

cx::float_t get_json_value_float (std::string json_string)
{
	cx::float_t v = 0.0f;


	v = (cx::float_t)atof (json_string.c_str());

	return v;
}

cx::uint_t get_json_value_uint (std::string json_string)
{
	cx::uint_t v = 0u;


	v = cx::parse_string_to_uint (json_string.c_str());

	return v;
}

cx::int_t get_json_value_int (std::string json_string)
{
	cx::int_t v = 0;


	v = cx::parse_string_to_int (json_string.c_str());

	return v;
}

cx::bool_t get_json_value_bool (std::string json_string)
{
	cx::bool_t v;
	

	v = cx::parse_string_to_bool(json_string.c_str());

	return v;
}

color_t get_json_value_color (std::string json_string)
{
	color_t v;

	cx::uint_t ARGB;


	ARGB = cx::parse_string_to_xuint(json_string.c_str());
	v.set_ARGB(ARGB);

	return v;
}

//===========================================================================
cx::bool_t get_json_value_string_of_json_object (cx::json_dom_node* current, std::string name, std::string& value)
{
	//-----------------------------------------------------------------------
	if (current->_type != JSON_OBJECT_BEGIN)
	{
		return false;
	}

		
	//-----------------------------------------------------------------------
	cx::json_dom_node_object* object = cx_gw_dynamic_cast<cx::json_dom_node_object*>(current);


	//-----------------------------------------------------------------------
	cx::json_dom_node* node;


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string(name));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 

		value = data->to_string();

		return true;
	}


	return false;
}	

cx::bool_t get_json_value_float_of_json_object (cx::json_dom_node* current, std::string name, cx::float_t& value)
{
	std::string json_value_string;


	if (false==get_json_value_string_of_json_object(current, name, json_value_string))
	{
		return false;
	}

	value = get_json_value_float(json_value_string);

	return true;
}

cx::bool_t get_json_value_uint_of_json_object (cx::json_dom_node* current, std::string name, cx::uint_t& value)
{
	std::string json_value_string;


	if (false==get_json_value_string_of_json_object(current, name, json_value_string))
	{
		return false;
	}

	value = get_json_value_uint(json_value_string);

	return true;
}

cx::bool_t get_json_value_int_of_json_object (cx::json_dom_node* current, std::string name, cx::int_t& value)
{
	std::string json_value_string;


	if (false==get_json_value_string_of_json_object(current, name, json_value_string))
	{
		return false;
	}

	value = get_json_value_int(json_value_string);

	return true;
}

cx::bool_t get_json_value_bool_of_json_object (cx::json_dom_node* current, std::string name, cx::bool_t& value)
{
	std::string json_value_string;


	if (false==get_json_value_string_of_json_object(current, name, json_value_string))
	{
		return false;
	}

	value = get_json_value_bool(json_value_string);

	return true;
}

cx::bool_t get_json_value_color_of_json_object (cx::json_dom_node* current, std::string name, color_t& value)
{
	std::string json_value_string;


	if (false==get_json_value_string_of_json_object(current, name, json_value_string))
	{
		return false;
	}

	value = get_json_value_color(json_value_string);

	return true;
}



//===========================================================================
void set_default_json_document_view_parameter(json_document_view_parameter_t* v)
{
	v->background_color = color_t::White;
	v->wolrd_rectangle  = rectangle_t(1920, 1080);
	v->viewscale        = 1.0f;
	v->grid_xsize       = 5;
	v->grid_ysize       = 5;
	v->grid_visible     = true;
	v->snap_to_grid     = true;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: json_document_reader
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
json_document_reader::json_document_reader(std::string file_path)
{
	_json_root_pointer    = CX_NULL_POINTER;
	_json_current_pointer = CX_NULL_POINTER;


	_flag      = 0;
	_file_path = file_path;
}

json_document_reader::json_document_reader(cx::uint_t flag, std::string s)
{
	_json_root_pointer    = CX_NULL_POINTER;
	_json_current_pointer = CX_NULL_POINTER;


	_flag = flag;
	switch(_flag)
	{
	case 0u:
		_file_path = s;
		break;
	case 1u:
		_string = s;
		break;
	default:
		break;
	}
}

json_document_reader::~json_document_reader()
{
}

//===========================================================================
cx::bool_t json_document_reader::create (widget_entry_collection* wec)
{
	cx::bool_t result;


	result = document_reader::create(wec);
	
	reset_view_parameter();

	return result;
}

void json_document_reader::destroy (void)
{
	document_reader::destroy();
}

cx::bool_t json_document_reader::read (model* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	design* md;


	md = cx_gw_dynamic_cast<design*>(m);
	if (CX_NULL_POINTER == md)
	{
		return false;
	}


	switch(_flag)
	{
	case 0u:
		return read_from_file(md, collection);
		break;
	case 1u:
		return read_from_string(md, collection);
		break;
	default:
		break;
	}

	return false;
}

//===========================================================================
cx::json_dom_node* json_document_reader::get_json_root (void)
{
	return _json_root_pointer;
}

cx::json_dom_node* json_document_reader::get_json_current (void)
{
	return _json_current_pointer;
}

void json_document_reader::set_json_current (cx::json_dom_node* node)
{
	_json_current_pointer = node;
}

//===========================================================================
cx::bool_t json_document_reader::read_from_file (design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	if (_file_path.empty())
	{
		return false;
	}

	
	//-----------------------------------------------------------------------
	LPBYTE buffer_pointer = CX_NULL_POINTER;
	DWORD  buffer_size    = 0u;


	if (FALSE==cx::LoadFileToBuffer(_file_path.c_str(), buffer_pointer, buffer_size))
	{
		if (buffer_pointer)
		{
			cx::ReleaseFileBuffer(buffer_pointer);
		}

		return false;
	}


	//-----------------------------------------------------------------------
	cx::text_file_bom_t tfb;


	get_text_file_bom(buffer_pointer, buffer_size, tfb);
	if (cx::TEXT_FILE_BOM_UTF8!=tfb)
	{
		if (buffer_pointer)
		{
			cx::ReleaseFileBuffer(buffer_pointer);
		}

		return false;
	}


	//-----------------------------------------------------------------------
	cx::bool_t result;

	const cx::char_t text_file_bom_utf8 [3] = {0xEFu, 0xBBu, 0xBFu};


	result = read_from_buffer(m, collection, buffer_pointer+sizeof(text_file_bom_utf8), buffer_size-sizeof(text_file_bom_utf8));
//	result = read_from_buffer(m, collection, buffer_pointer, buffer_size);

	if (buffer_pointer)
	{
		cx::ReleaseFileBuffer(buffer_pointer);
	}


	return result;
}

cx::bool_t json_document_reader::read_from_string (design* m, widget_collection* collection)
{
	cx::byte_t* buffer_pointer;
	cx::uint_t  buffer_size;


	buffer_pointer = (cx::byte_t*)_string.c_str();
	buffer_size    = _string.size();


	cx::bool_t result;

	const cx::char_t text_file_bom_utf8 [3] = {0xEFu, 0xBBu, 0xBFu};


	result = read_from_buffer(m, collection, buffer_pointer+sizeof(text_file_bom_utf8), buffer_size-sizeof(text_file_bom_utf8));


	return result;
}

cx::bool_t json_document_reader::read_from_buffer (design* m, widget_collection* collection, cx::byte_t* buffer_pointer, cx::uint_t buffer_size)
{
	//-----------------------------------------------------------------------
	cx::json_reader reader;

	cx::json_dom_node* root_pointer = CX_NULL_POINTER;



	if (false==reader.create())
	{
		return false;
	}

	if (false==reader.read((const ::cx::char_t*)buffer_pointer, buffer_size, root_pointer ))
	{
		return false;
	}

	reader.destroy();


	//-----------------------------------------------------------------------
	cx::bool_t result;


	_json_root_pointer    = root_pointer;
	_json_current_pointer = root_pointer;

	result = read_root (m, collection);

	cx::json_reader::delete_root_pointer (root_pointer);

	_json_root_pointer    = CX_NULL_POINTER;
	_json_current_pointer = CX_NULL_POINTER;


	return result;
}

cx::bool_t json_document_reader::read_root (design* m, widget_collection* collection)
{
	cx::json_dom_node* node;
	

	node = get_json_root();
	if (JSON_OBJECT_BEGIN==node->_type)
	{
		set_json_current(node);

		return read_document (m, collection);
	}

	return false;
}

cx::bool_t json_document_reader::read_document (design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	cx::json_dom_node_object* object = cx_gw_dynamic_cast<cx::json_dom_node_object*>(get_json_current());


	CX_DEBUG_ASSERT(CX_NULL_POINTER  !=object);
	CX_DEBUG_ASSERT(JSON_OBJECT_BEGIN==object->_type);

	
	//-----------------------------------------------------------------------
	cx::json_dom_node* node;


	node = object->find (get_json_value_string("표시"));
	if (node)
	{
		if (JSON_OBJECT_BEGIN==node->_type)
		{
			set_json_current(node);

			if (false==read_view_parameter(m, collection))
			{
				return false;
			}
		}
	}


	node = object->find (get_json_value_string("도표"));
	if (node)
	{
		if (JSON_ARRAY_BEGIN==node->_type)
		{
			set_json_current(node);

			if (false==read_diagram_collection(m, collection))
			{
				return false;
			}
		}
	}


	return true;
}

cx::bool_t json_document_reader::read_view_parameter (design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	cx::json_dom_node_object* object = cx_gw_dynamic_cast<cx::json_dom_node_object*>(get_json_current());


	CX_DEBUG_ASSERT(CX_NULL_POINTER  !=object);
	CX_DEBUG_ASSERT(JSON_OBJECT_BEGIN==object->_type);


	//-----------------------------------------------------------------------
	cx::json_dom_node* node;


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("배경색상"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->background_color = get_json_value_color(data->to_string());
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("작업영역.P0.X"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->wolrd_rectangle._p0._x = get_json_value_float(data->to_string());
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("작업영역.P0.Y"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->wolrd_rectangle._p0._y = get_json_value_float(data->to_string());
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("작업영역.P1.X"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->wolrd_rectangle._p1._x = get_json_value_float(data->to_string());
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("작업영역.P1.Y"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->wolrd_rectangle._p1._y = get_json_value_float(data->to_string());
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("배율"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->viewscale = ( get_json_value_float(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("가로격자크기"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->grid_xsize = ( get_json_value_uint(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("세로격자크기"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->grid_ysize = ( get_json_value_uint(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("격자보기"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->grid_visible = ( get_json_value_bool(data->to_string()) );
	}


	//-----------------------------------------------------------------------
	node = object->find (get_json_value_string("격자고정"));
	if (node)
	{
		if (node->_type != JSON_STRING)
		{
			return false;
		}


		cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


		get_view_parameter()->snap_to_grid = ( get_json_value_bool(data->to_string()) );
	}


	return true;
}

cx::bool_t json_document_reader::read_diagram_collection (design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	cx::json_dom_node_array* array = cx_gw_dynamic_cast<cx::json_dom_node_array*>(get_json_current());


	CX_DEBUG_ASSERT(CX_NULL_POINTER !=array);
	CX_DEBUG_ASSERT(JSON_ARRAY_BEGIN==array->_type);


	//-----------------------------------------------------------------------
	cx::json_dom_node* node;


	std::vector<cx::json_dom_node*>::iterator i;


	for (i=array->_collection.begin(); i!=array->_collection.end(); i++)
	{
		node = (*i);

		if (JSON_OBJECT_BEGIN==node->_type)
		{
			set_json_current(node);
			if (false==read_diagram(m, collection))
			{
				return false;
			}
		}
	}

	return true;
}

cx::bool_t json_document_reader::read_diagram (design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	cx::json_dom_node_object* object = cx_gw_dynamic_cast<cx::json_dom_node_object*>(get_json_current());


	CX_DEBUG_ASSERT(CX_NULL_POINTER  !=object);
	CX_DEBUG_ASSERT(JSON_OBJECT_BEGIN==object->_type);


	//-----------------------------------------------------------------------
	cx::json_dom_node* node;


	node = object->find (get_json_value_string("형식"));
	if (CX_NULL_POINTER==node)
	{
		return false;
	}
	if (JSON_STRING!=node->_type)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	cx::json_dom_node_data* data = cx_gw_dynamic_cast<cx::json_dom_node_data*>(node); 


	if (CX_NULL_POINTER==data)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	std::string wc;
	
	
	wc = data->to_string();


	//-----------------------------------------------------------------------
	widget_iostream* io = CX_NULL_POINTER;


	
	io = get_widget_iostream()->find (wc);
	if (CX_NULL_POINTER==io)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	diagram* wd;
	
	
	wd = m->get_diagram_creator()->create_diagram(wc);
	if (CX_NULL_POINTER==wd)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	if (false==io->read(this, wd, m))
	{
		wd->delete_instance();

		return false;
	}


	//-----------------------------------------------------------------------
	collection->get_container().push_back( wd );


	return true;
}

//===========================================================================
json_document_view_parameter_t* json_document_reader::get_view_parameter(void)
{
	return &_view_parameter;
}

//===========================================================================
void json_document_reader::reset_view_parameter(void)
{
	set_default_json_document_view_parameter(get_view_parameter());
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: json_document_writer
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
json_document_writer::json_document_writer(std::string file_path)
{
	_file_path = file_path;
}

json_document_writer::json_document_writer(cx::uint_t flag, std::string s)
{
	_flag = flag;
	switch(_flag)
	{
	case 0u:
		_file_path = s;
		break;
	case 1u:
		_string = s;
		break;
	default:
		break;
	}
}

json_document_writer::~json_document_writer()
{
}

//===========================================================================
cx::bool_t json_document_writer::create (widget_entry_collection* wec)
{
	cx::bool_t result;


	result = document_writer::create(wec);

	reset_view_parameter();

	return result;
}

void json_document_writer::destroy (void)
{
	document_writer::destroy();
}

cx::bool_t json_document_writer::write (model* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	design* md;


	md = cx_gw_dynamic_cast<design*>(m);
	if (CX_NULL_POINTER == md)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	set_view_parameter(md);


	//-----------------------------------------------------------------------
	get_json_writer()->_output.clear();
#if 1
	get_json_writer()->_output =
		"/*      \n"
		" * json \n"
		" *      \n"
		" */     \n";
#endif


	//-----------------------------------------------------------------------
	if (false==get_json_writer()->create())
	{
		return false;
	}

	
	//-----------------------------------------------------------------------
	if (false == write_document(md, collection))
	{
		get_json_writer()->destroy();
		return false;
	}


	//-----------------------------------------------------------------------
	get_json_writer()->destroy();


	//-----------------------------------------------------------------------
#if defined(CX_DEBUG)
//	cx::debug::print (get_json_writer()->_output.c_str());
//	cx::debug::print ("\n");
//	cx::debug::print (cx::utf8_to_mbcs(get_json_writer()->_output).c_str());
//	cx::debug::print ("\n");
#endif


	switch(_flag)
	{
	case 0u:
		return write_to_file();
		break;
	case 1u:
		return write_to_string();
		break;
	default:
		break;
	}

	return false;
}

//===========================================================================
cx::json_writer* json_document_writer::get_json_writer (void)
{
	return &_json_writer;
}

//===========================================================================
cx::bool_t json_document_writer::write_document(design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
//	get_json_writer()->key("문서");
//	get_json_writer()->key("document");
	get_json_writer()->object_begin();


	//-----------------------------------------------------------------------
	if(false==write_view_parameter (m, collection))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	if(false==write_diagram_collection (m, collection))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	get_json_writer()->object_end();


	return true;
}

cx::bool_t json_document_writer::write_view_parameter(design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	get_json_writer()->key("표시");
//	get_json_writer()->key("view");
	get_json_writer()->object_begin();

			
	//-----------------------------------------------------------------------
	get_json_writer()->value( "배경색상"      , get_json_string_color ( get_view_parameter()->background_color       ) );
	get_json_writer()->value( "작업영역.P0.X" , get_json_string_float ( get_view_parameter()->wolrd_rectangle._p0._x ) );
	get_json_writer()->value( "작업영역.P0.Y" , get_json_string_float ( get_view_parameter()->wolrd_rectangle._p0._y ) );
	get_json_writer()->value( "작업영역.P1.X" , get_json_string_float ( get_view_parameter()->wolrd_rectangle._p1._x ) );
	get_json_writer()->value( "작업영역.P1.Y" , get_json_string_float ( get_view_parameter()->wolrd_rectangle._p1._y ) );
	get_json_writer()->value( "배율"          , get_json_string_float ( get_view_parameter()->viewscale              ) );
	get_json_writer()->value( "가로격자크기"  , get_json_string_uint  ( get_view_parameter()->grid_xsize             ) );
	get_json_writer()->value( "세로격자크기"  , get_json_string_uint  ( get_view_parameter()->grid_ysize             ) );
	get_json_writer()->value( "격자보기"      , get_json_string_bool  ( get_view_parameter()->grid_visible           ) );
	get_json_writer()->value( "격자고정"      , get_json_string_bool  ( get_view_parameter()->snap_to_grid           ) );


	//-----------------------------------------------------------------------
	get_json_writer()->object_end();


	return true;
}

cx::bool_t json_document_writer::write_diagram_collection(design* m, widget_collection* collection)
{
	//-----------------------------------------------------------------------
	get_json_writer()->key("도표");
//	get_json_writer()->key("diagram");
	get_json_writer()->array_begin();

			
	//-----------------------------------------------------------------------
	widget_pointer_container_t::iterator i;
	widget* w;

	diagram* wd;
	
	
	//-----------------------------------------------------------------------
	for (i =collection->get_container().begin();
	     i!=collection->get_container().end();
		 i++)
	{
		w = (*i);

		wd = m->cast_diagram(w);
		if (wd)
		{
			if (false==write_diagram(m,wd))
			{
				return false;
			}
		}
	}


	//-----------------------------------------------------------------------
	get_json_writer()->array_end();


	return true;
}

cx::bool_t json_document_writer::write_diagram (design* m, diagram* wd)
{
	//-----------------------------------------------------------------------
	widget_iostream* io = CX_NULL_POINTER;


	
	io = get_widget_iostream()->find (wd->get_class());
	if (CX_NULL_POINTER==io)
	{
		return false;
	}


	//-----------------------------------------------------------------------
//	get_json_writer()->key(wd->get_class());
	get_json_writer()->object_begin();


	//-----------------------------------------------------------------------
	if (false==io->write(this, wd, m))
	{
		return false;
	}
	

	//-----------------------------------------------------------------------
	get_json_writer()->object_end();


	return true;
}

//===========================================================================
cx::bool_t json_document_writer::write_to_file (void)
{
	//-----------------------------------------------------------------------
	if (_file_path.empty())
	{
		return false;
	}

	
	//-----------------------------------------------------------------------
	const cx::char_t text_file_bom_utf8 [3] = {0xEFu, 0xBBu, 0xBFu};
	
	std::string text;


	text.insert(text.begin(), text_file_bom_utf8, text_file_bom_utf8+sizeof(text_file_bom_utf8));
	text.append(get_json_writer()->_output);


	//-----------------------------------------------------------------------
	BOOL result;
	
	const LPBYTE buffer_pointer = (const LPBYTE) ( text.c_str() ); // reinterpret_cast<const LPBYTE>( text.c_str() );
	DWORD        buffer_size    = static_cast<DWORD>( text.size() );
	

	result = cx::SaveFileFromBuffer(_file_path.c_str(), buffer_pointer, buffer_size);
	if (FALSE==result)
	{
		return false;
	}

	return true;
}

cx::bool_t json_document_writer::write_to_string (void)
{
	//-----------------------------------------------------------------------
	_string.clear();

	
	//-----------------------------------------------------------------------
	const cx::char_t text_file_bom_utf8 [3] = {0xEFu, 0xBBu, 0xBFu};


	_string.insert(_string.begin(), text_file_bom_utf8, text_file_bom_utf8+sizeof(text_file_bom_utf8));
	_string.append(get_json_writer()->_output);


	return true;
}

std::string& json_document_writer::get_string (void)
{
	return _string;
}


//===========================================================================
json_document_view_parameter_t* json_document_writer::get_view_parameter(void)
{
	return &_view_parameter;
}

void json_document_writer::reset_view_parameter(void)
{
	set_default_json_document_view_parameter(get_view_parameter());
}

void json_document_writer::set_view_parameter(design* m)
{
	get_view_parameter()->background_color = m->get_view()->get_background_color();
	get_view_parameter()->wolrd_rectangle  = m->get_view()->get_wolrd_rectangle ();
	get_view_parameter()->viewscale        = m->get_view()->get_viewscale       ();
	get_view_parameter()->grid_xsize       = m->get_view()->get_grid_xsize      ();
	get_view_parameter()->grid_ysize       = m->get_view()->get_grid_ysize      ();
	get_view_parameter()->grid_visible     = m->get_view()->get_grid_visible    ();
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}
