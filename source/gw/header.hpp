#ifndef INCLUDED__CX__GW__HEADER__HPP
#define INCLUDED__CX__GW__HEADER__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: heaer.hpp
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"

#include <objidl.h>

//===========================================================================
#ifdef _MSC_VER
#pragma warning (disable : 4458) // disable warning: declaration hides class member
#endif
#include <gdiplus.h>
#ifdef _MSC_VER
#pragma warning (default : 4458) // return warning to default
#endif

//===========================================================================
using namespace Gdiplus;

//===========================================================================
#include <string>
#include <map>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

//===========================================================================
#include <cx3/library/header.hpp>
#include <cx3/library/system/header.hpp>
#include <cx3/library/string/header.hpp>
#include <cx3/library/filesystem/header.hpp>
#include <cx3/library/string/windows_charset_converter.hpp>
#include <cx3/library/string/parse_value_string.hpp>
#include <cx3/library/json_libjson/header.hpp>
//#include <../libjson/1.00/json.h>
//#include "D:\\Development\\Project\\2018.12.19\\FG\\sdk\\libjson\\1.00\\json.h"
//#include "D:\\Development\\Project\\2018.12.19\\FG\\sdk\\libjson\\1.00\\json.h"
//#include <cx3/library/json_libjson/json_helper.hpp>
//#include <cx3/library/json_libjson/json_writer.hpp>
//#include <cx3/library/json_libjson/json_reader.hpp>

#include <cx3/library/file/text_file_bom.hpp>
#include <cx3/library/windows/SimpleFile.hpp>

//===========================================================================
#include "declaration.hpp"

//===========================================================================
#include "window/declaration.hpp"

//===========================================================================
#include "coordinates/declaration.hpp"
#include "coordinates/typedef.hpp"

#include "coordinates/point.hpp"
#include "coordinates/rectangle.hpp"
#include "coordinates/utility.hpp"

//===========================================================================
#include "graphic/declaration.hpp"
#include "graphic/typedef.hpp"

#include "graphic/color.hpp"

//===========================================================================
#include "renderer/declaration.hpp"

#include "renderer/renderer.hpp"
#include "renderer/rectangle_renderer.hpp"
#include "renderer/round_rectangle_renderer.hpp"
#include "renderer/rectangle_3d_renderer.hpp"
#include "renderer/ellipse_renderer.hpp"
#include "renderer/text_rectangle_renderer.hpp"
#include "renderer/line_renderer.hpp"

//===========================================================================
#include "resource.hpp"
#include "view.hpp"
#include "event.hpp"
#include "window_event_handler.hpp"

#include "widget.hpp"
#include "widget_event.hpp"
#include "widget_event_handler.hpp"
#include "widget_factory.hpp"
#include "widget_iostream.hpp"
#include "widget_entry.hpp"

#include "document.hpp"

#include "model.hpp"

//===========================================================================
#include "control/declaration.hpp"

#include "control/control.hpp"
#include "control/form.hpp"
#include "control/wh_layout.hpp"

#include "control/control_default_widget_entry.hpp"
#include "control/item/led_button.hpp"
#include "control/item/button.hpp"
#include "control/item/blue_highlight.hpp"

//===========================================================================
#include "diagram/declaration.hpp"

#include "diagram/diagram_buffer.hpp"
#include "diagram/json_document.hpp"

#include "diagram/anchor.hpp"
#include "diagram/diagram.hpp"
#include "diagram/diagram_event.hpp"
#include "diagram/diagram_creator.hpp"

#include "diagram/design.hpp"

#include "diagram/edit_action.hpp"
#include "diagram/edit_history.hpp"
#include "diagram/edit.hpp"

#include "diagram/copy_diagram.hpp"

#include "diagram/diagram_default_widget_entry.hpp"
#include "diagram/item/rectangle_shape.hpp"
#include "diagram/item/straight_line.hpp"

//===========================================================================
#include "dragdrop/declaration.hpp"

#include "dragdrop/drop_target.hpp"

#include "dragdrop/drop_source.hpp"
#include "dragdrop/drag_data_object.hpp"

#include "dragdrop/drag_data.hpp"
#include "dragdrop/drag_data_hglobal.hpp"


#endif


