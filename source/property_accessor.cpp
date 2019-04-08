/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define MAX_FMT_SIZE 1024



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define _countofslist(x) (sizeof((x))/sizeof((x)[0]))
#define _vlist(x)        get_vlist((x),_countofslist((x)))



//===========================================================================
static std::string get_vlist(cx::char_t** slist, cx::uint_t count)
{
	std::string vlist;
	std::string value;

	cx::uint_t i;


	for (i=0u; i<count; i++)
	{
		value = slist[i];
		vlist.insert(vlist.end(), value.begin(), value.end());
		vlist.push_back(0);
	}
	vlist.push_back(0);


	return vlist;
}



#pragma region property_accessor
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
property_accessor::property_accessor(HWND hwnd)
{
	_control  = hwnd;
	_object   = CX_NULL_POINTER;
}

property_accessor::~property_accessor()
{
}

//===========================================================================
HWND property_accessor::get_control (void)
{
	return _control;
}

void property_accessor::set_object(void* o)
{
	_object = o;
}

void* property_accessor::get_object(void)
{
	return _object;
}

//===========================================================================
void property_accessor::load_property_to_control(void)
{
	CX_DEBUG_ASSERT(get_object()!=CX_NULL_POINTER);

	/*
	std::string catalog = "catalog";
	std::string name    = "name";
	std::string value;

	
	PROPGRIDITEM item;
	
	
	value = get_object()->get_name();
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);
	*/
}

void property_accessor::set_property_to_control(void)
{
	CX_DEBUG_ASSERT(get_object()!=CX_NULL_POINTER);

	/*
	std::string catalog = "catalog";
	std::string name    = "name";
	std::string value;


	PROPGRIDITEM item;
	

	value = get_object->get_name();
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), 0, &item);
	*/
}

void property_accessor::set_property_from_control(cx::int_t index, LPPROPGRIDITEM item)
{
	/*
	switch (index)
	{
	case 0:
		object->set_name( (LPTSTR)item->lpCurValue );
		break;

	default:
		break;
	}
	*/
	// PIT_EDIT, PIT_COMBO, PIT_EDITCOMBO
	// (LPTSTR)item->lpCurValue

	// PIT_STATIC
	// null

	// PIT_CHECK
	// (BOOL)item->lpCurValue
	
	// PIT_COLOR
	// (COLORREF)Item->lpCurValue

	// PIT_FONT
	// ((LPPROPGRIDFONTITEM)item->lpCurValue)->crFont
	// ((LPPROPGRIDFONTITEM)Item->lpCurValue)->logFont
	/*
	#define CopyLogFont(lfDest, lfSource) \
	lfDest.lfHeight         = lfSource.lfHeight       ; \
	lfDest.lfWidth          = lfSource.lfWidth        ; \
	lfDest.lfEscapement     = lfSource.lfEscapement   ; \
	lfDest.lfOrientation    = lfSource.lfOrientation  ; \
	lfDest.lfWeight         = lfSource.lfWeight       ; \
	lfDest.lfItalic         = lfSource.lfItalic       ; \
	lfDest.lfUnderline      = lfSource.lfUnderline    ; \
	lfDest.lfStrikeOut      = lfSource.lfStrikeOut    ; \
	lfDest.lfCharSet        = lfSource.lfCharSet      ; \
	lfDest.lfOutPrecision   = lfSource.lfOutPrecision ; \
	lfDest.lfClipPrecision  = lfSource.lfClipPrecision; \
	lfDest.lfQuality        = lfSource.lfQuality      ; \
	lfDest.lfPitchAndFamily = lfSource.lfPitchAndFamily; \
	_tmemmove(lfDest.lfFaceName,lfSource.lfFaceName,LF_FACESIZE)
	*/

	// PIT_FILE
	// ((LPPROPGRIDFDITEM)Item->lpCurValue)->lpszFilePath

	// PIT_FOLDER
	// (LPTSTR)item->lpCurValue

	// PIT_IP
	// (DWORD)Item->lpCurValue

	// PIT_DATE, PIT_TIME, PIT_DATETIME
	// (LPSYSTEMTIME)Item->lpCurValue
}
#pragma endregion property_accessor



#pragma region view_property_accessor
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static cx::char_t* _view_background_color_catalog = "바탕";
static cx::char_t* _view_background_color_name    = "배경색상";

static cx::char_t* _view_wolrd_rectangle_catalog = "바탕";
static cx::char_t* _view_wolrd_rectangle_name    = "작업영역";

static cx::char_t* _view_scale_catalog = "바탕";
static cx::char_t* _view_scale_name    = "배율";

static cx::char_t* _view_viewscale_size_catalog  = "바탕";
static cx::char_t* _view_viewscale_size_name     = "작업영역 배율크기";

static cx::char_t* _view_viewport_window_size_catalog = "표시영역";
static cx::char_t* _view_viewport_window_size_name    = "창 크기";

static cx::char_t* _view_viewport_window_offset_catalog = "표시영역";
static cx::char_t* _view_viewport_window_offset_name    = "창 작업영역 거리위치";

static cx::char_t* _view_viewport_world_rectangle_catalog = "표시영역";
static cx::char_t* _view_viewport_world_rectangle_name    = "창 작업영역 위치";

static cx::char_t* _view_grid_xsize_catalog = "격자";
static cx::char_t* _view_grid_xsize_name    = "가로 크기";

static cx::char_t* _view_grid_ysize_catalog = "격자";
static cx::char_t* _view_grid_ysize_name    = "세로 크기";

static cx::char_t* _view_grid_visible_catalog = "격자";
static cx::char_t* _view_grid_visible_name    = "보이기";
static cx::char_t* _view_grid_visible_slist[] = {"보기","숨김"};

//===========================================================================
view_property_accessor::view_property_accessor(HWND hwnd) : view_property_accessor::base_t(hwnd)
{
	_index_begin = -1;
	_index_end   = -1;
}

view_property_accessor::~view_property_accessor()
{
}

//===========================================================================
gw::view* view_property_accessor::get_view (void)
{
	return reinterpret_cast<gw::view*>( get_object() );
}

//===========================================================================
void view_property_accessor::load_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::load_property_to_control();


	//-----------------------------------------------------------------------
	_index_begin = PropGrid_GetCount(get_control());


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_view()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;

	
	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];


	//-----------------------------------------------------------------------
	gw::color_t     background_color        ;
	gw::rectangle_t wolrd_rectangle         ;
	cx::float_t     viewscale               ;
	cx::int_t       viewscale_xsize         ;
	cx::int_t       viewscale_ysize         ;
	cx::int_t       viewport_window_xsize   ;
	cx::int_t       viewport_window_ysize   ;
	cx::int_t       viewport_window_xoffset ;
	cx::int_t       viewport_window_yoffset ;
	gw::rectangle_t viewport_world_rectangle;
	cx::int_t       grid_xsize              ;
	cx::int_t       grid_ysize              ;
	cx::bool_t      grid_visible            ;


	background_color         = get_view()->get_background_color        ();
	wolrd_rectangle          = get_view()->get_wolrd_rectangle         ();
	viewscale                = get_view()->get_viewscale               ();
	viewscale_xsize          = get_view()->get_viewscale_xsize         ();
	viewscale_ysize          = get_view()->get_viewscale_ysize         ();
	viewport_window_xsize    = get_view()->get_viewport_window_xsize   ();
	viewport_window_ysize    = get_view()->get_viewport_window_ysize   ();
	viewport_window_xoffset  = get_view()->get_viewport_window_xoffset ();
	viewport_window_yoffset  = get_view()->get_viewport_window_yoffset ();
	viewport_world_rectangle = get_view()->get_viewport_world_rectangle();
	grid_xsize               = get_view()->get_grid_xsize              ();
	grid_ysize               = get_view()->get_grid_ysize              ();
	grid_visible             = get_view()->get_grid_visible            ();


	//-----------------------------------------------------------------------
	catalog = _view_background_color_catalog;
	name    = _view_background_color_name;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)background_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f, %.2f", wolrd_rectangle.w(), wolrd_rectangle.h());


	catalog = _view_wolrd_rectangle_catalog;
	name    = _view_wolrd_rectangle_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f", viewscale);


	catalog = _view_scale_catalog;
	name    = _view_scale_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d, %d", viewscale_xsize, viewscale_ysize);


	catalog = _view_viewscale_size_catalog;
	name    = _view_viewscale_size_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d, %d", viewport_window_xsize, viewport_window_ysize);


	catalog = _view_viewport_window_size_catalog;
	name    = _view_viewport_window_size_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d, %d", viewport_window_xoffset, viewport_window_yoffset);


	catalog = _view_viewport_window_offset_catalog;
	name    = _view_viewport_window_offset_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "(%.2f, %.2f)-(%.2f, %.2f)", 
		viewport_world_rectangle._p0._x,
		viewport_world_rectangle._p0._y,
		viewport_world_rectangle._p1._x,
		viewport_world_rectangle._p1._y);


	catalog = _view_viewport_world_rectangle_catalog;
	name    = _view_viewport_world_rectangle_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", grid_xsize);


	catalog = _view_grid_xsize_catalog;
	name    = _view_grid_xsize_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", grid_ysize);


	catalog = _view_grid_ysize_catalog;
	name    = _view_grid_ysize_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _view_grid_visible_catalog;
	name    = _view_grid_visible_name;   
	vlist   = _vlist(_view_grid_visible_slist);
	value   = grid_visible ? _view_grid_visible_slist[0] : _view_grid_visible_slist[1];

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);

#if 1
	//-----------------------------------------------------------------------
	catalog = "test";
	name    = "test1";   
	value   = "value";

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_USERCUSTOM;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = "test";
	name    = "test2";   
	value   = "value";

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_USERCUSTOM;
	PropGrid_AddItem (get_control(), &item);
#endif

	//-----------------------------------------------------------------------
	_index_end = PropGrid_GetCount(get_control());
}

void view_property_accessor::set_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::set_property_to_control();


	//-----------------------------------------------------------------------
	cx::uint_t index;


	index = _index_begin;

	
	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_view()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;
	

	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];
	

	//-----------------------------------------------------------------------
	gw::color_t     background_color        ;
	gw::rectangle_t wolrd_rectangle         ;
	cx::float_t     viewscale               ;
	cx::int_t       viewscale_xsize         ;
	cx::int_t       viewscale_ysize         ;
	cx::int_t       viewport_window_xsize   ;
	cx::int_t       viewport_window_ysize   ;
	cx::int_t       viewport_window_xoffset ;
	cx::int_t       viewport_window_yoffset ;
	gw::rectangle_t viewport_world_rectangle;
	cx::int_t       grid_xsize              ;
	cx::int_t       grid_ysize              ;
	cx::bool_t      grid_visible            ;


	background_color         = get_view()->get_background_color        ();
	wolrd_rectangle          = get_view()->get_wolrd_rectangle         ();
	viewscale                = get_view()->get_viewscale               ();
	viewscale_xsize          = get_view()->get_viewscale_xsize         ();
	viewscale_ysize          = get_view()->get_viewscale_ysize         ();
	viewport_window_xsize    = get_view()->get_viewport_window_xsize   ();
	viewport_window_ysize    = get_view()->get_viewport_window_ysize   ();
	viewport_window_xoffset  = get_view()->get_viewport_window_xoffset ();
	viewport_window_yoffset  = get_view()->get_viewport_window_yoffset ();
	viewport_world_rectangle = get_view()->get_viewport_world_rectangle();
	grid_xsize               = get_view()->get_grid_xsize              ();
	grid_ysize               = get_view()->get_grid_ysize              ();
	grid_visible             = get_view()->get_grid_visible            ();


	//-----------------------------------------------------------------------
	catalog = _view_background_color_catalog;
	name    = _view_background_color_name;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)background_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f, %.2f", wolrd_rectangle.w(), wolrd_rectangle.h());


	catalog = _view_wolrd_rectangle_catalog;
	name    = _view_wolrd_rectangle_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f", viewscale);


	catalog = _view_scale_catalog;
	name    = _view_scale_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d, %d", viewscale_xsize, viewscale_ysize);


	catalog = _view_viewscale_size_catalog;
	name    = _view_viewscale_size_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d, %d", viewport_window_xsize, viewport_window_ysize);


	catalog = _view_viewport_window_size_catalog;
	name    = _view_viewport_window_size_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d, %d", viewport_window_xoffset, viewport_window_yoffset);


	catalog = _view_viewport_window_offset_catalog;
	name    = _view_viewport_window_offset_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "(%.2f, %.2f)-(%.2f, %.2f)", 
		viewport_world_rectangle._p0._x,
		viewport_world_rectangle._p0._y,
		viewport_world_rectangle._p1._x,
		viewport_world_rectangle._p1._y);


	catalog = _view_viewport_world_rectangle_catalog;
	name    = _view_viewport_world_rectangle_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", grid_xsize);


	catalog = _view_grid_xsize_catalog;
	name    = _view_grid_xsize_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", grid_ysize);


	catalog = _view_grid_ysize_catalog;
	name    = _view_grid_ysize_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _view_grid_visible_catalog;
	name    = _view_grid_visible_name;   
	vlist   = _vlist(_view_grid_visible_slist);
	value   = grid_visible ? _view_grid_visible_slist[0] : _view_grid_visible_slist[1];

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


#if 1
	//-----------------------------------------------------------------------
	/*
	catalog = "test";
	name    = "test1";   
	value   = "value";

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_USERCUSTOM;
	PropGrid_SetItemData (get_control(), index++, &item);
	*/

	//-----------------------------------------------------------------------
	/*
	catalog = "test";
	name    = "test1";   
	value   = "value";

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_USERCUSTOM;
	PropGrid_SetItemData (get_control(), index++, &item);
	*/

	//-----------------------------------------------------------------------
	index+=2;
#endif

	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(index==_index_end);
}

void view_property_accessor::set_property_from_control(cx::int_t index, LPPROPGRIDITEM item)
{
	//-----------------------------------------------------------------------
	base_t::set_property_from_control(index, item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_view()!=CX_NULL_POINTER);


	//-----------------------------------------------------------------------
	if (index<_index_begin)
	{
		return;
	}
	if (index>=_index_end)
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::uint_t item_index;


	item_index = index - _index_begin;


	//-----------------------------------------------------------------------
	gw::color_t     background_color        ;
	gw::rectangle_t wolrd_rectangle         ;
	cx::float_t     viewscale               ;
	cx::int_t       viewscale_xsize         ;
	cx::int_t       viewscale_ysize         ;
	cx::int_t       viewport_window_xsize   ;
	cx::int_t       viewport_window_ysize   ;
	cx::int_t       viewport_window_xoffset ;
	cx::int_t       viewport_window_yoffset ;
	gw::rectangle_t viewport_world_rectangle;
	cx::int_t       grid_xsize              ;
	cx::int_t       grid_ysize              ;
	cx::bool_t      grid_visible            ;


	background_color         = get_view()->get_background_color        ();
	wolrd_rectangle          = get_view()->get_wolrd_rectangle         ();
	viewscale                = get_view()->get_viewscale               ();
	viewscale_xsize          = get_view()->get_viewscale_xsize         ();
	viewscale_ysize          = get_view()->get_viewscale_ysize         ();
	viewport_window_xsize    = get_view()->get_viewport_window_xsize   ();
	viewport_window_ysize    = get_view()->get_viewport_window_ysize   ();
	viewport_window_xoffset  = get_view()->get_viewport_window_xoffset ();
	viewport_window_yoffset  = get_view()->get_viewport_window_yoffset ();
	viewport_world_rectangle = get_view()->get_viewport_world_rectangle();
	grid_xsize               = get_view()->get_grid_xsize              ();
	grid_ysize               = get_view()->get_grid_ysize              ();
	grid_visible             = get_view()->get_grid_visible            ();


	//-----------------------------------------------------------------------
	std::string value;
	COLORREF    value_cr;


	//-----------------------------------------------------------------------
	switch (item_index)
	{
	case 0:
		value_cr = (COLORREF)item->lpCurValue;
		background_color.R(GetRValue(value_cr));
		background_color.G(GetGValue(value_cr));
		background_color.B(GetBValue(value_cr));
		get_view()->set_background_color(background_color);
		break;

	case 1: // wolrd_rectangle
		break;

	case 2: // viewscale
		// 스크롤처리 문제
		/*
		value = (LPTSTR)item->lpCurValue;
		if (!value.empty())
		{
			sscanf(value.c_str(), "%f", &viewscale);
			if (0.1f<=viewscale && viewscale<=5.0f)
			{
				get_view()->set_viewscale(viewscale);
				get_view()->get_model()->set_redraw();
			}
		}
		*/
		break;

	case 3: // viewscale_size
		break;

	case 4: // viewport_window_size
		break;

	case 5: // viewport_window_offset
		break;

	case 6: // viewport_world_rectangle
		break;

	case 7:
		value = (LPTSTR)item->lpCurValue;
		grid_xsize = cx::parse_string_to_uint(value.c_str(), 5);
		get_view()->set_grid_size(grid_xsize, grid_ysize);
		set_property_to_control();
		break;

	case 8:
		value = (LPTSTR)item->lpCurValue;
		grid_ysize = cx::parse_string_to_uint(value.c_str(), 5);
		get_view()->set_grid_size(grid_xsize, grid_ysize);
		set_property_to_control();
		break;

	case 9:
		value = (LPTSTR)item->lpCurValue;
		get_view()->set_grid_visible( (value==_view_grid_visible_slist[0]) ? true : false );
		break;

#if 0
	case 10:
	case 11:
		value = (LPTSTR)item->lpCurValue;
		CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%s", value.c_str());
		break;
#endif

	default:
		break;
	}
}
#pragma endregion view_property_accessor



#pragma region widget_property_accessor
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static cx::char_t* _widget_zorder_catalog  = "객체";
static cx::char_t* _widget_zorder_name     = "순서";

static cx::char_t* _widget_class_catalog   = "객체";
static cx::char_t* _widget_class_name      = "형식";

static cx::char_t* _widget_name_catalog    = "객체";
static cx::char_t* _widget_name_name       = "이름";

static cx::char_t* _widget_point_catalog   = "좌표";
static cx::char_t* _widget_point_name      = "좌표";
static cx::char_t* _widget_point_value_fmt = "%.2f, %.2f";

//===========================================================================
widget_property_accessor::widget_property_accessor(HWND hwnd) : widget_property_accessor::base_t(hwnd)
{
	_index_begin = -1;
	_index_end   = -1;
}

widget_property_accessor::~widget_property_accessor()
{
}

//===========================================================================
gw::widget* widget_property_accessor::get_widget (void)
{
	return reinterpret_cast<gw::widget*>( get_object() );
}

//===========================================================================
void widget_property_accessor::load_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::load_property_to_control();


	//-----------------------------------------------------------------------
	_index_begin = PropGrid_GetCount(get_control());


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_widget()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;

	
	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];
	cx::uint_t count;
	cx::uint_t i;


	
	//-----------------------------------------------------------------------
	gw::widget_pointer_container_t::iterator f;
	cx::int_t zorder;

	
	f = std::find(
		get_widget()->get_model()->get_widget()->get_container().begin(),
		get_widget()->get_model()->get_widget()->get_container().end(),
		get_widget());
	if (f==get_widget()->get_model()->get_widget()->get_container().end())
	{
		zorder = -1;
	}
	else
	{
		zorder = f - get_widget()->get_model()->get_widget()->get_container().begin();
	}
	sprintf(fmt, "%d", zorder);


	catalog = _widget_zorder_catalog;
	name    = _widget_zorder_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _widget_name_catalog;
	name    = _widget_name_name;
	value   = get_widget()->get_name();

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _widget_class_catalog;
	name    = _widget_class_name;
	value   = get_widget()->get_class();

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	count = get_widget()->get_point_container().size();
	for (i=0u; i<count; i++)
	{
		catalog = _widget_point_catalog;

		sprintf(fmt,"[%d]", i);
		name = fmt;

		sprintf(fmt, _widget_point_value_fmt, get_widget()->get_point_container()[i]._x,  get_widget()->get_point_container()[i]._y);
		value = fmt;

		item.lpszCatalog   = (LPTSTR)catalog.c_str();
		item.lpszPropName  = (LPTSTR)name.c_str();
		item.lpszzCmbItems = NULL;
		item.lpszPropDesc  = NULL;
		item.lpCurValue    = (LPARAM)value.c_str();
		item.lpUserData    = NULL;
		item.iItemType     = PIT_STATIC;
		PropGrid_AddItem (get_control(), &item);
	}


	//-----------------------------------------------------------------------
	_index_end = PropGrid_GetCount(get_control());
}

void widget_property_accessor::set_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::set_property_to_control();


	//-----------------------------------------------------------------------
	cx::uint_t index;


	index = _index_begin;

	
	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_widget()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;

	
	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];
	cx::uint_t count;
	cx::uint_t i;


	//-----------------------------------------------------------------------
	gw::widget_pointer_container_t::iterator f;
	cx::int_t zorder;

	
	f = std::find(
		get_widget()->get_model()->get_widget()->get_container().begin(),
		get_widget()->get_model()->get_widget()->get_container().end(),
		get_widget());
	if (f==get_widget()->get_model()->get_widget()->get_container().end())
	{
		zorder = -1;
	}
	else
	{
		zorder = f - get_widget()->get_model()->get_widget()->get_container().begin();
	}
	sprintf(fmt, "%d", zorder);


	catalog = _widget_zorder_catalog;
	name    = _widget_zorder_name;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _widget_name_catalog;
	name    = _widget_name_name;
	value   = get_widget()->get_name();

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _widget_class_catalog;
	name    = _widget_class_name;
	value   = get_widget()->get_class();

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_STATIC;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	count = get_widget()->get_point_container().size();
	for (i=0u; i<count; i++)
	{
		catalog = _widget_point_catalog;

		sprintf(fmt,"[%d]", i);
		name = fmt;

		sprintf(fmt, _widget_point_value_fmt, get_widget()->get_point_container()[i]._x,  get_widget()->get_point_container()[i]._y);
		value = fmt;

		item.lpszCatalog   = (LPTSTR)catalog.c_str();
		item.lpszPropName  = (LPTSTR)name.c_str();
		item.lpszzCmbItems = NULL;
		item.lpszPropDesc  = NULL;
		item.lpCurValue    = (LPARAM)value.c_str();
		item.lpUserData    = NULL;
		item.iItemType     = PIT_STATIC;
		PropGrid_SetItemData (get_control(), index++, &item);
	}


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(index==_index_end);
}

void widget_property_accessor::set_property_from_control(cx::int_t index, LPPROPGRIDITEM item)
{
	//-----------------------------------------------------------------------
	base_t::set_property_from_control(index, item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_widget()!=CX_NULL_POINTER);


	//-----------------------------------------------------------------------
	if (index<_index_begin)
	{
		return;
	}
	if (index>=_index_end)
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::uint_t item_index;


	item_index = index - _index_begin;


	//-----------------------------------------------------------------------
	std::string value;


	//-----------------------------------------------------------------------
	switch (item_index)
	{
	case 0: // zorder
		break;

	case 1:
		value = (LPTSTR)item->lpCurValue;
		get_widget()->set_name( value );
		break;

	case 2: // class
		break;

	case 3: // point
		break;

	default:
		break;
	}
}
#pragma endregion widget_property_accessor



#pragma region diagram_property_accessor
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static cx::char_t* _diagram_anchor_catalog   = "기준점";
static cx::char_t* _diagram_anchor_name      = "기준점";
static cx::char_t* _diagram_anchor_value_fmt = "%.2f, %.2f";

static cx::char_t* _diagram_visible_catalog="동작";
static cx::char_t* _diagram_visible_name   ="보이기";
static cx::char_t* _diagram_visible_slist[]={"보이기", "감추기"};

static cx::char_t* _diagram_enabled_catalog="동작";
static cx::char_t* _diagram_enabled_name   ="동작가능";
static cx::char_t* _diagram_enabled_slist[]={"활성화", "비활성화"};

//===========================================================================
diagram_property_accessor::diagram_property_accessor(HWND hwnd) : diagram_property_accessor::base_t(hwnd)
{
	_index_begin = -1;
	_index_end   = -1;
}

diagram_property_accessor::~diagram_property_accessor()
{
}

//===========================================================================
gw::dgrm::diagram* diagram_property_accessor::get_diagram (void)
{
	return cx_gw_dynamic_cast<gw::dgrm::diagram*>( get_widget() );
}

//===========================================================================
void diagram_property_accessor::load_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::load_property_to_control();


	//-----------------------------------------------------------------------
	_index_begin = PropGrid_GetCount(get_control());


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_diagram()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;


	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];
	cx::uint_t count;
	cx::uint_t i;

	gw::widget*       w;
	gw::dgrm::anchor* wa;
	gw::point_t       p;


	//-----------------------------------------------------------------------
	catalog = _diagram_visible_catalog;
	name    = _diagram_visible_name;	
	vlist   = _vlist(_diagram_visible_slist);
	value   = get_diagram()->get_visible() ? _diagram_visible_slist[0] : _diagram_visible_slist[1];

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_enabled_catalog;
	name    = _diagram_enabled_name;   
	vlist   = _vlist(_diagram_enabled_slist);
	value   = get_diagram()->get_enabled() ? _diagram_enabled_slist[0] : _diagram_enabled_slist[1];

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	count = get_diagram()->get_child()->get_container().size();
	for (i=0u; i<count; i++)
	{
		w = get_diagram()->get_child()->get_container()[i];
		
		wa = get_diagram()->get_design()->cast_anchor(w);

		if (wa)
		{
			p = wa->get_point();


			catalog = _diagram_anchor_catalog;

			sprintf(fmt,"[%d]", i);
			name = fmt;

			sprintf(fmt, _diagram_anchor_value_fmt, p._x, p._y);
			value = fmt;

			item.lpszCatalog   = (LPTSTR)catalog.c_str();
			item.lpszPropName  = (LPTSTR)name.c_str();
			item.lpszzCmbItems = NULL;
			item.lpszPropDesc  = NULL;
			item.lpCurValue    = (LPARAM)value.c_str();
			item.lpUserData    = NULL;
			item.iItemType     = PIT_STATIC;
			PropGrid_AddItem (get_control(), &item);
		}
	}


	//-----------------------------------------------------------------------
	_index_end = PropGrid_GetCount(get_control());
}

void diagram_property_accessor::set_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::set_property_to_control();


	//-----------------------------------------------------------------------
	cx::uint_t index;


	index = _index_begin;

	
	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_diagram()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;

	
	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];
	cx::uint_t count;
	cx::uint_t i;

	gw::widget*       w;
	gw::dgrm::anchor* wa;
	gw::point_t       p;


	//-----------------------------------------------------------------------
	catalog = _diagram_visible_catalog;
	name    = _diagram_visible_name;	
	vlist   = _vlist(_diagram_visible_slist);
	value   = get_diagram()->get_visible() ? _diagram_visible_slist[0] : _diagram_visible_slist[1];

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_enabled_catalog;
	name    = _diagram_enabled_name;   
	vlist   = _vlist(_diagram_enabled_slist);
	value   = get_diagram()->get_enabled() ? _diagram_enabled_slist[0] : _diagram_enabled_slist[1];

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	count = get_diagram()->get_child()->get_container().size();
	for (i=0u; i<count; i++)
	{
		w = get_diagram()->get_child()->get_container()[i];
		
		wa = get_diagram()->get_design()->cast_anchor(w);

		if (wa)
		{
			p = wa->get_point();


			catalog = _diagram_anchor_catalog;

			sprintf(fmt,"[%d]", i);
			name = fmt;

			sprintf(fmt, _diagram_anchor_value_fmt, p._x, p._y);
			value = fmt;

			item.lpszCatalog   = (LPTSTR)catalog.c_str();
			item.lpszPropName  = (LPTSTR)name.c_str();
			item.lpszzCmbItems = NULL;
			item.lpszPropDesc  = NULL;
			item.lpCurValue    = (LPARAM)value.c_str();
			item.lpUserData    = NULL;
			item.iItemType     = PIT_STATIC;
			PropGrid_SetItemData (get_control(), index++, &item);
		}
	}


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(index==_index_end);
}

void diagram_property_accessor::set_property_from_control(cx::int_t index, LPPROPGRIDITEM item)
{
	//-----------------------------------------------------------------------
	base_t::set_property_from_control(index, item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_diagram()!=CX_NULL_POINTER);


	//-----------------------------------------------------------------------
	if (index<_index_begin)
	{
		return;
	}
	if (index>=_index_end)
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::uint_t item_index;


	item_index = index - _index_begin;


	//-----------------------------------------------------------------------
	std::string value;


	//-----------------------------------------------------------------------
	switch (item_index)
	{
	case 0:
		value = (LPTSTR)item->lpCurValue;
		get_diagram()->set_visible( (value==_diagram_visible_slist[0]) ? true : false );
		break;

	case 1:
		value = (LPTSTR)item->lpCurValue;
		get_diagram()->set_enabled( (value==_diagram_enabled_slist[0]) ? true : false );
		break;

	default:
		break;
	}
}
#pragma endregion diagram_property_accessor



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static cx::char_t* _diagram_text_catalog = "글쓰기";
static cx::char_t* _diagram_text_name    = "글";

static cx::char_t* _diagram_text_color_catalog = "글쓰기";
static cx::char_t* _diagram_text_color_name    = "글색상";

static cx::char_t* _diagram_text_colorA_catalog = "글쓰기";
static cx::char_t* _diagram_text_colorA_name    = "글색상투명도";

static cx::char_t* _diagram_text_format_alignment_catalog = "글쓰기";
static cx::char_t* _diagram_text_format_alignment_name    = "글정렬";
static cx::char_t* _diagram_text_format_alignment_slist[] = {"왼쪽","가운데","오른쪽"};

static cx::char_t* _diagram_text_format_line_alignment_catalog = "글쓰기";
static cx::char_t* _diagram_text_format_line_alignment_name    = "글세로정렬";
static cx::char_t* _diagram_text_format_line_alignment_slist[] = {"위","가운데","아래"};

static cx::char_t* _diagram_text_font_familyname_catalog = "글쓰기";
static cx::char_t* _diagram_text_font_familyname_name    = "글꼴";

static cx::char_t* _diagram_text_font_size_catalog = "글쓰기";
static cx::char_t* _diagram_text_font_size_name    = "글꼴크기";

static cx::char_t* _diagram_text_font_style_catalog = "글쓰기";
static cx::char_t* _diagram_text_font_style_name    = "글꼴모양";

static cx::char_t* _diagram_text_font_catalog = "글쓰기";
static cx::char_t* _diagram_text_font_name    = "글꼴";


static cx::char_t* _diagram_fill_color_catalog = "채우기";
static cx::char_t* _diagram_fill_color_name    = "채움색상";

static cx::char_t* _diagram_fill_colorA_catalog = "채우기";
static cx::char_t* _diagram_fill_colorA_name    = "채움색상투명도";

static cx::char_t* _diagram_fill_style_catalog = "채우기";
static cx::char_t* _diagram_fill_style_name    = "채움모양";


static cx::char_t* _diagram_line_width_catalog = "선그리기";
static cx::char_t* _diagram_line_width_name    = "선크기";

static cx::char_t* _diagram_line_color_catalog = "선그리기";
static cx::char_t* _diagram_line_color_name    = "선색상";

static cx::char_t* _diagram_line_colorA_catalog = "선그리기";
static cx::char_t* _diagram_line_colorA_name    = "선색상투명도";

static cx::char_t* _diagram_line_dash_style_catalog = "선그리기";
static cx::char_t* _diagram_line_dash_style_name    = "선모양";
static cx::char_t* _diagram_line_dash_style_slist[] ={"실선", "점선"};



#pragma region rectangle_shape_property_accessor
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
rectangle_shape_property_accessor::rectangle_shape_property_accessor(HWND hwnd) : rectangle_shape_property_accessor::base_t(hwnd)
{
	_index_begin = -1;
	_index_end   = -1;
}

rectangle_shape_property_accessor::~rectangle_shape_property_accessor()
{
}

//===========================================================================
gw::dgrm::rectangle_shape* rectangle_shape_property_accessor::get_rectangle_shape (void)
{
	return cx_gw_dynamic_cast<gw::dgrm::rectangle_shape*>( get_diagram() );
}

//===========================================================================
void rectangle_shape_property_accessor::load_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::load_property_to_control();


	//-----------------------------------------------------------------------
	_index_begin = PropGrid_GetCount(get_control());


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_rectangle_shape()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;


	PROPGRIDITEM item;
	PROPGRIDFONTITEM itemFont;

	cx::char_t fmt[MAX_FMT_SIZE];


	//-----------------------------------------------------------------------
	std::string text                      ;
	gw::color_t text_color                ;
	cx::uint_t  text_format_alignment     ;
	cx::uint_t  text_format_line_alignment;
	std::string text_font_familyname      ;
	cx::float_t text_font_size            ;
	cx::uint_t  text_font_style           ;

	gw::color_t fill_color;
	cx::uint_t  fill_style;

	cx::float_t line_width     ;
	gw::color_t line_color     ;
	cx::uint_t  line_dash_style;


	text                       = get_rectangle_shape()->get_text                      ();
	text_color                 = get_rectangle_shape()->get_text_color                ();
	text_format_alignment      = get_rectangle_shape()->get_text_format_alignment     ();
	text_format_line_alignment = get_rectangle_shape()->get_text_format_line_alignment();
	text_font_familyname       = get_rectangle_shape()->get_text_font_familyname      ();
	text_font_size             = get_rectangle_shape()->get_text_font_size            ();
	text_font_style            = get_rectangle_shape()->get_text_font_style           ();


	fill_color = get_rectangle_shape()->get_fill_color();
	fill_style = get_rectangle_shape()->get_fill_style();


	line_width     =get_rectangle_shape()->get_line_width     ();
	line_color     =get_rectangle_shape()->get_line_color     ();
	line_dash_style=get_rectangle_shape()->get_line_dash_style();


	//-----------------------------------------------------------------------
	LOGFONT lf;

	cx::int_t pixels_per_logical_inch;
	HDC hdc;


	hdc = GetWindowDC(get_control());
	pixels_per_logical_inch = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(get_control(), hdc);


	memset (&lf, 0, sizeof(LOGFONT));
	lf.lfHeight    = -MulDiv(static_cast<cx::int_t>(text_font_size), pixels_per_logical_inch, 72);
	lf.lfWidth     = 0;
	lf.lfItalic    = text_font_style & FontStyleItalic    ? TRUE : FALSE;
	lf.lfWeight    = text_font_style & FontStyleBold      ? FW_BOLD : FW_NORMAL;
	lf.lfUnderline = text_font_style & FontStyleUnderline ? TRUE : FALSE;
	lf.lfStrikeOut = text_font_style & FontStyleStrikeout ? TRUE : FALSE;
	lstrcpy (lf.lfFaceName, text_font_familyname.c_str()); 


	//-----------------------------------------------------------------------
	catalog = _diagram_text_catalog;
	name    = _diagram_text_name;	
	value   = text;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_text_color_catalog;
	name    = _diagram_text_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)text_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( text_color.A()) );

	catalog = _diagram_text_colorA_catalog;
	name    = _diagram_text_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	switch(text_format_alignment)
	{
	case 0: value = _diagram_text_format_alignment_slist[0]; break;
	case 1: value = _diagram_text_format_alignment_slist[1]; break;
	case 2: value = _diagram_text_format_alignment_slist[2]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_text_format_alignment_catalog;
	name    = _diagram_text_format_alignment_name;
	vlist   = _vlist( _diagram_text_format_alignment_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	switch(text_format_line_alignment)
	{
	case 0: value = _diagram_text_format_line_alignment_slist[0]; break;
	case 1: value = _diagram_text_format_line_alignment_slist[1]; break;
	case 2: value = _diagram_text_format_line_alignment_slist[2]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_text_format_line_alignment_catalog;
	name    = _diagram_text_format_line_alignment_name;
	vlist   = _vlist( _diagram_text_format_line_alignment_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	memcpy(&itemFont.logFont, &lf, sizeof(lf));
	itemFont.crFont = text_color.ABGR();

	catalog = _diagram_text_font_catalog;
	name    = _diagram_text_font_name;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)&itemFont;
	item.lpUserData    = NULL;
	item.iItemType     = PIT_FONT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_fill_color_catalog;
	name    = _diagram_fill_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)fill_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( fill_color.A()) );

	catalog = _diagram_fill_colorA_catalog;
	name    = _diagram_fill_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
#if 0
	sprintf(fmt, "%d", static_cast<cx::uint_t>( fill_style) );

	catalog = _diagram_fill_style_catalog;
	name    = _diagram_fill_style_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);
#endif


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f", line_width );

	catalog = _diagram_line_width_catalog;
	name    = _diagram_line_width_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_line_color_catalog;
	name    = _diagram_line_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)line_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( line_color.A()) );

	catalog = _diagram_line_colorA_catalog;
	name    = _diagram_line_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	switch(line_dash_style)
	{
	case DashStyleSolid: value = _diagram_line_dash_style_slist[0]; break;
	case DashStyleDot  : value = _diagram_line_dash_style_slist[1]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_line_dash_style_catalog;
	name    = _diagram_line_dash_style_name;
	vlist   = _vlist( _diagram_line_dash_style_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	_index_end = PropGrid_GetCount(get_control());
}

void rectangle_shape_property_accessor::set_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::set_property_to_control();


	//-----------------------------------------------------------------------
	cx::uint_t index;


	index = _index_begin;

	
	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_rectangle_shape()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;

	
	PROPGRIDITEM item;
	PROPGRIDFONTITEM itemFont;

	cx::char_t fmt[MAX_FMT_SIZE];


	//-----------------------------------------------------------------------
	std::string text                      ;
	gw::color_t text_color                ;
	cx::uint_t  text_format_alignment     ;
	cx::uint_t  text_format_line_alignment;
	std::string text_font_familyname      ;
	cx::float_t text_font_size            ;
	cx::uint_t  text_font_style           ;

	gw::color_t fill_color;
	cx::uint_t  fill_style;

	cx::float_t line_width     ;
	gw::color_t line_color     ;
	cx::uint_t  line_dash_style;


	text                       = get_rectangle_shape()->get_text                      ();
	text_color                 = get_rectangle_shape()->get_text_color                ();
	text_format_alignment      = get_rectangle_shape()->get_text_format_alignment     ();
	text_format_line_alignment = get_rectangle_shape()->get_text_format_line_alignment();
	text_font_familyname       = get_rectangle_shape()->get_text_font_familyname      ();
	text_font_size             = get_rectangle_shape()->get_text_font_size            ();
	text_font_style            = get_rectangle_shape()->get_text_font_style           ();


	fill_color = get_rectangle_shape()->get_fill_color();
	fill_style = get_rectangle_shape()->get_fill_style();


	line_width     =get_rectangle_shape()->get_line_width     ();
	line_color     =get_rectangle_shape()->get_line_color     ();
	line_dash_style=get_rectangle_shape()->get_line_dash_style();


	//-----------------------------------------------------------------------
	LOGFONT lf;

	cx::int_t pixels_per_logical_inch;
	HDC hdc;


	hdc = GetWindowDC(get_control());
	pixels_per_logical_inch = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(get_control(), hdc);


	memset (&lf, 0, sizeof(LOGFONT));
	lf.lfHeight    = -MulDiv(static_cast<cx::int_t>(text_font_size), pixels_per_logical_inch, 72);
	lf.lfWidth     = 0;
	lf.lfItalic    = text_font_style & FontStyleItalic    ? TRUE : FALSE;
	lf.lfWeight    = text_font_style & FontStyleBold      ? FW_BOLD : FW_NORMAL;
	lf.lfUnderline = text_font_style & FontStyleUnderline ? TRUE : FALSE;
	lf.lfStrikeOut = text_font_style & FontStyleStrikeout ? TRUE : FALSE;
	lstrcpy (lf.lfFaceName, text_font_familyname.c_str()); 


	//-----------------------------------------------------------------------
	catalog = _diagram_text_catalog;
	name    = _diagram_text_name;	
	value   = text;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_text_color_catalog;
	name    = _diagram_text_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)text_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( text_color.A()) );

	catalog = _diagram_text_colorA_catalog;
	name    = _diagram_text_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	switch(text_format_alignment)
	{
	case 0: value = _diagram_text_format_alignment_slist[0]; break;
	case 1: value = _diagram_text_format_alignment_slist[1]; break;
	case 2: value = _diagram_text_format_alignment_slist[2]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_text_format_alignment_catalog;
	name    = _diagram_text_format_alignment_name;
	vlist   = _vlist( _diagram_text_format_alignment_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	switch(text_format_line_alignment)
	{
	case 0: value = _diagram_text_format_line_alignment_slist[0]; break;
	case 1: value = _diagram_text_format_line_alignment_slist[1]; break;
	case 2: value = _diagram_text_format_line_alignment_slist[2]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_text_format_line_alignment_catalog;
	name    = _diagram_text_format_line_alignment_name;
	vlist   = _vlist( _diagram_text_format_line_alignment_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	memcpy(&itemFont.logFont, &lf, sizeof(lf));
	itemFont.crFont = text_color.ABGR();

	catalog = _diagram_text_font_catalog;
	name    = _diagram_text_font_name;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)&itemFont;
	item.lpUserData    = NULL;
	item.iItemType     = PIT_FONT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_fill_color_catalog;
	name    = _diagram_fill_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)fill_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( fill_color.A()) );

	catalog = _diagram_fill_colorA_catalog;
	name    = _diagram_fill_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
#if 0
	sprintf(fmt, "%d", static_cast<cx::uint_t>( fill_style) );

	catalog = _diagram_fill_style_catalog;
	name    = _diagram_fill_style_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);
#endif


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f", line_width );

	catalog = _diagram_line_width_catalog;
	name    = _diagram_line_width_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_line_color_catalog;
	name    = _diagram_line_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)line_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( line_color.A()) );

	catalog = _diagram_line_colorA_catalog;
	name    = _diagram_line_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	switch(line_dash_style)
	{
	case DashStyleSolid: value = _diagram_line_dash_style_slist[0]; break;
	case DashStyleDot  : value = _diagram_line_dash_style_slist[1]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_line_dash_style_catalog;
	name    = _diagram_line_dash_style_name;
	vlist   = _vlist( _diagram_line_dash_style_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(index==_index_end);
}

void rectangle_shape_property_accessor::set_property_from_control(cx::int_t index, LPPROPGRIDITEM item)
{
	//-----------------------------------------------------------------------
	base_t::set_property_from_control(index, item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_rectangle_shape()!=CX_NULL_POINTER);


	//-----------------------------------------------------------------------
	if (index<_index_begin)
	{
		return;
	}
	if (index>=_index_end)
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::uint_t item_index;


	item_index = index - _index_begin;


	//-----------------------------------------------------------------------
	std::string       value;
	COLORREF          value_cr;
	PROPGRIDFONTITEM* value_font;
	

	//-----------------------------------------------------------------------
	std::string text                      ;
	gw::color_t text_color                ;
	cx::uint_t  text_format_alignment     ;
	cx::uint_t  text_format_line_alignment;
	std::string text_font_familyname      ;
	cx::float_t text_font_size            ;
	cx::uint_t  text_font_style           ;
	
	gw::color_t fill_color;
	cx::uint_t  fill_style;

	cx::float_t line_width     ;
	gw::color_t line_color     ;
	cx::uint_t  line_dash_style;


	text                       = get_rectangle_shape()->get_text                      ();
	text_color                 = get_rectangle_shape()->get_text_color                ();
	text_format_alignment      = get_rectangle_shape()->get_text_format_alignment     ();
	text_format_line_alignment = get_rectangle_shape()->get_text_format_line_alignment();
	text_font_familyname       = get_rectangle_shape()->get_text_font_familyname      ();
	text_font_size             = get_rectangle_shape()->get_text_font_size            ();
	text_font_style            = get_rectangle_shape()->get_text_font_style           ();

	fill_color = get_rectangle_shape()->get_fill_color();
	fill_style = get_rectangle_shape()->get_fill_style();


	line_width     =get_rectangle_shape()->get_line_width     ();
	line_color     =get_rectangle_shape()->get_line_color     ();
	line_dash_style=get_rectangle_shape()->get_line_dash_style();


	//-----------------------------------------------------------------------
	LOGFONT lf;

	cx::int_t pixels_per_logical_inch;
	HDC hdc;


	hdc = GetWindowDC(get_control());
	pixels_per_logical_inch = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(get_control(), hdc);


	memset (&lf, 0, sizeof(LOGFONT));
	lf.lfHeight    = -MulDiv(static_cast<cx::int_t>(text_font_size), pixels_per_logical_inch, 72);
	lf.lfWidth     = 0;
	lf.lfItalic    = text_font_style & FontStyleItalic    ? TRUE : FALSE;
	lf.lfWeight    = text_font_style & FontStyleBold      ? FW_BOLD : FW_NORMAL;
	lf.lfUnderline = text_font_style & FontStyleUnderline ? TRUE : FALSE;
	lf.lfStrikeOut = text_font_style & FontStyleStrikeout ? TRUE : FALSE;
	lstrcpy (lf.lfFaceName, text_font_familyname.c_str()); 


	//-----------------------------------------------------------------------
	switch (item_index)
	{
	case 0:
		value = (LPTSTR)item->lpCurValue;
		get_rectangle_shape()->set_text( value );
		break;

	case 1:
		value_cr = (COLORREF)item->lpCurValue;
		text_color.R(GetRValue(value_cr));
		text_color.G(GetGValue(value_cr));
		text_color.B(GetBValue(value_cr));
		get_rectangle_shape()->set_text_color(text_color);
		break;

	case 2:
		value = (LPTSTR)item->lpCurValue;
		text_color.A( cx::parse_string_to_uint(value.c_str(), 255) );
		get_rectangle_shape()->set_text_color(text_color);
		break;

	case 3:
		value = (LPTSTR)item->lpCurValue;
		if      (value==_diagram_text_format_alignment_slist[0]) { get_rectangle_shape()->set_text_format_alignment(0u); }
		else if (value==_diagram_text_format_alignment_slist[1]) { get_rectangle_shape()->set_text_format_alignment(1u); }
		else if (value==_diagram_text_format_alignment_slist[2]) { get_rectangle_shape()->set_text_format_alignment(2u); }
		else                                                     { get_rectangle_shape()->set_text_format_alignment(1u); }
		break;

	case 4:
		value = (LPTSTR)item->lpCurValue;
		if      (value==_diagram_text_format_line_alignment_slist[0]) { get_rectangle_shape()->set_text_format_line_alignment(0u); }
		else if (value==_diagram_text_format_line_alignment_slist[1]) { get_rectangle_shape()->set_text_format_line_alignment(1u); }
		else if (value==_diagram_text_format_line_alignment_slist[2]) { get_rectangle_shape()->set_text_format_line_alignment(2u); }
		else                                                          { get_rectangle_shape()->set_text_format_line_alignment(1u); }
		break;

	case 5:
		value_font = (PROPGRIDFONTITEM*)item->lpCurValue;
		text_color.R(GetRValue(value_font->crFont));
		text_color.G(GetGValue(value_font->crFont));
		text_color.B(GetBValue(value_font->crFont));
		get_rectangle_shape()->set_text_color(text_color);
		{
			PROPGRIDITEM itemOther;
			std::string catalog;
			std::string name;

			catalog = _diagram_text_color_catalog;
			name    = _diagram_text_color_name;

			itemOther.lpszCatalog   = (LPTSTR)catalog.c_str();
			itemOther.lpszPropName  = (LPTSTR)name.c_str();
			itemOther.lpszzCmbItems = NULL;
			itemOther.lpszPropDesc  = NULL;
			itemOther.lpCurValue    = (LPARAM)text_color.ABGR();
			itemOther.lpUserData    = NULL;
			itemOther.iItemType     = PIT_COLOR;
			PropGrid_SetItemData (get_control(), _index_begin+1, &itemOther);
		}

		memcpy(&lf, &value_font->logFont, sizeof(lf));

		text_font_familyname = lf.lfFaceName;
		if (!text_font_familyname.empty())
		{
			get_rectangle_shape()->set_text_font_familyname(text_font_familyname);
		}

		text_font_size = static_cast<cx::float_t>( -MulDiv(lf.lfHeight, 72, pixels_per_logical_inch) );
		if (text_font_size>0.0f && text_font_size<255.0f)
		{
			get_rectangle_shape()->set_text_font_size(text_font_size);
		}

		text_font_style = 0u;
		if (lf.lfWeight != FW_NORMAL) { text_font_style |= FontStyleBold;      }
		if (lf.lfItalic             ) { text_font_style |= FontStyleItalic;    }
		if (lf.lfUnderline          ) { text_font_style |= FontStyleUnderline; }
		if (lf.lfStrikeOut          ) { text_font_style |= FontStyleStrikeout; }
		get_rectangle_shape()->set_text_font_style(text_font_style);
		break;

	case 6:
		value_cr = (COLORREF)item->lpCurValue;
		fill_color.R(GetRValue(value_cr));
		fill_color.G(GetGValue(value_cr));
		fill_color.B(GetBValue(value_cr));
		get_rectangle_shape()->set_fill_color(fill_color);
		break;

	case 7:
		value = (LPTSTR)item->lpCurValue;
		fill_color.A( cx::parse_string_to_uint(value.c_str(), 255) );
		get_rectangle_shape()->set_fill_color(fill_color);
		break;

#if 0
	case 8:
		value = (LPTSTR)item->lpCurValue;
		fill_style = cx::parse_string_to_uint(value.c_str(), 0);
		get_rectangle_shape()->set_fill_style(fill_style);
		break;
#endif

	case 8:
		value = (LPTSTR)item->lpCurValue;
		if (!value.empty())
		{
			sscanf(value.c_str(), "%f", &line_width);
			get_rectangle_shape()->set_line_width(line_width);
		}
		else
		{
			set_property_to_control();
		}
		break;

	case 9:
		value_cr = (COLORREF)item->lpCurValue;
		line_color.R(GetRValue(value_cr));
		line_color.G(GetGValue(value_cr));
		line_color.B(GetBValue(value_cr));
		get_rectangle_shape()->set_line_color(line_color);
		break;

	case 10:
		value = (LPTSTR)item->lpCurValue;
		line_color.A( cx::parse_string_to_uint(value.c_str(), 255) );
		get_rectangle_shape()->set_line_color(line_color);
		break;

	case 11:
		value = (LPTSTR)item->lpCurValue;
		if      (value==_diagram_line_dash_style_slist[0]) { get_rectangle_shape()->set_line_dash_style(DashStyleSolid); }
		else if (value==_diagram_line_dash_style_slist[1]) { get_rectangle_shape()->set_line_dash_style(DashStyleDot  ); }
		else                                               { get_rectangle_shape()->set_line_dash_style(DashStyleSolid); }
		break;

	default:
		break;
	}
}
#pragma endregion rectangle_shape_property_accessor



#pragma region straight_line_property_accessor
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
straight_line_property_accessor::straight_line_property_accessor(HWND hwnd) : straight_line_property_accessor::base_t(hwnd)
{
	_index_begin = -1;
	_index_end   = -1;
}

straight_line_property_accessor::~straight_line_property_accessor()
{
}

//===========================================================================
gw::dgrm::straight_line* straight_line_property_accessor::get_straight_line (void)
{
	return cx_gw_dynamic_cast<gw::dgrm::straight_line*>( get_diagram() );
}

//===========================================================================
void straight_line_property_accessor::load_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::load_property_to_control();


	//-----------------------------------------------------------------------
	_index_begin = PropGrid_GetCount(get_control());


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_straight_line()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;


	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];


	//-----------------------------------------------------------------------
	cx::float_t line_width     ;
	gw::color_t line_color     ;
	cx::uint_t  line_dash_style;


	line_width     =get_straight_line()->get_line_width     ();
	line_color     =get_straight_line()->get_line_color     ();
	line_dash_style=get_straight_line()->get_line_dash_style();


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f", line_width );

	catalog = _diagram_line_width_catalog;
	name    = _diagram_line_width_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_line_color_catalog;
	name    = _diagram_line_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)line_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( line_color.A()) );

	catalog = _diagram_line_colorA_catalog;
	name    = _diagram_line_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	switch(line_dash_style)
	{
	case DashStyleSolid: value = _diagram_line_dash_style_slist[0]; break;
	case DashStyleDot  : value = _diagram_line_dash_style_slist[1]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_line_dash_style_catalog;
	name    = _diagram_line_dash_style_name;
	vlist   = _vlist( _diagram_line_dash_style_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_AddItem (get_control(), &item);


	//-----------------------------------------------------------------------
	_index_end = PropGrid_GetCount(get_control());
}

void straight_line_property_accessor::set_property_to_control(void)
{
	//-----------------------------------------------------------------------
	base_t::set_property_to_control();


	//-----------------------------------------------------------------------
	cx::uint_t index;


	index = _index_begin;

	
	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_straight_line()!=CX_NULL_POINTER);

	std::string catalog;
	std::string name;
	std::string value;
	std::string vlist;

	
	PROPGRIDITEM item;

	cx::char_t fmt[MAX_FMT_SIZE];


	//-----------------------------------------------------------------------
	cx::float_t line_width     ;
	gw::color_t line_color     ;
	cx::uint_t  line_dash_style;


	line_width     =get_straight_line()->get_line_width     ();
	line_color     =get_straight_line()->get_line_color     ();
	line_dash_style=get_straight_line()->get_line_dash_style();


	//-----------------------------------------------------------------------
	sprintf(fmt, "%.2f", line_width );

	catalog = _diagram_line_width_catalog;
	name    = _diagram_line_width_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	catalog = _diagram_line_color_catalog;
	name    = _diagram_line_color_name;
	
	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)line_color.ABGR();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COLOR;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	sprintf(fmt, "%d", static_cast<cx::uint_t>( line_color.A()) );

	catalog = _diagram_line_colorA_catalog;
	name    = _diagram_line_colorA_name;;
	value   = fmt;

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = NULL;
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_EDIT;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	switch(line_dash_style)
	{
	case DashStyleSolid: value = _diagram_line_dash_style_slist[0]; break;
	case DashStyleDot  : value = _diagram_line_dash_style_slist[1]; break;
	default:
		value = "?";
		break;
	}

	catalog = _diagram_line_dash_style_catalog;
	name    = _diagram_line_dash_style_name;
	vlist   = _vlist( _diagram_line_dash_style_slist );

	item.lpszCatalog   = (LPTSTR)catalog.c_str();
	item.lpszPropName  = (LPTSTR)name.c_str();
	item.lpszzCmbItems = (LPTSTR)vlist.c_str();
	item.lpszPropDesc  = NULL;
	item.lpCurValue    = (LPARAM)value.c_str();
	item.lpUserData    = NULL;
	item.iItemType     = PIT_COMBO;
	PropGrid_SetItemData (get_control(), index++, &item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(index==_index_end);
}

void straight_line_property_accessor::set_property_from_control(cx::int_t index, LPPROPGRIDITEM item)
{
	//-----------------------------------------------------------------------
	base_t::set_property_from_control(index, item);


	//-----------------------------------------------------------------------
	CX_DEBUG_ASSERT(get_straight_line()!=CX_NULL_POINTER);


	//-----------------------------------------------------------------------
	if (index<_index_begin)
	{
		return;
	}
	if (index>=_index_end)
	{
		return;
	}


	//-----------------------------------------------------------------------
	cx::uint_t item_index;


	item_index = index - _index_begin;


	//-----------------------------------------------------------------------
	std::string       value;
	COLORREF          value_cr;
	

	//-----------------------------------------------------------------------
	cx::float_t line_width     ;
	gw::color_t line_color     ;
	cx::uint_t  line_dash_style;


	line_width     =get_straight_line()->get_line_width     ();
	line_color     =get_straight_line()->get_line_color     ();
	line_dash_style=get_straight_line()->get_line_dash_style();


	//-----------------------------------------------------------------------
	switch (item_index)
	{
	case 0:
		value = (LPTSTR)item->lpCurValue;
		if (!value.empty())
		{
			sscanf(value.c_str(), "%f", &line_width);
			get_straight_line()->set_line_width(line_width);
		}
		else
		{
			set_property_to_control();
		}
		break;

	case 1:
		value_cr = (COLORREF)item->lpCurValue;
		line_color.R(GetRValue(value_cr));
		line_color.G(GetGValue(value_cr));
		line_color.B(GetBValue(value_cr));
		get_straight_line()->set_line_color(line_color);
		break;

	case 2:
		value = (LPTSTR)item->lpCurValue;
		line_color.A( cx::parse_string_to_uint(value.c_str(), 255) );
		get_straight_line()->set_line_color(line_color);
		break;

	case 3:
		value = (LPTSTR)item->lpCurValue;
		if      (value==_diagram_line_dash_style_slist[0]) { get_straight_line()->set_line_dash_style(DashStyleSolid); }
		else if (value==_diagram_line_dash_style_slist[1]) { get_straight_line()->set_line_dash_style(DashStyleDot  ); }
		else                                               { get_straight_line()->set_line_dash_style(DashStyleSolid); }
		break;

	default:
		break;
	}
}
#pragma endregion straight_line_property_accessor
