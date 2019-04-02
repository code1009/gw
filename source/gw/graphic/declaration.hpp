#ifndef INCLUDED__CX__GW__GRAPHIC__DECLARATION__HPP
#define INCLUDED__CX__GW__GRAPHIC__DECLARATION__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: declaration.hpp
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



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef Graphics*    graphic_t;
typedef GdiplusBase* graphic_object_t;
typedef Font*        font_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class color;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//#define GW_DEFAULT_TEXT_FONT_FAMILYNAME "굴림체"
//#define GW_DEFAULT_TEXT_FONT_SIZE       10.0f
#define GW_DEFAULT_TEXT_FONT_FAMILYNAME "맑은 고딕"
#define GW_DEFAULT_TEXT_FONT_SIZE       10.0f
#define GW_DEFAULT_TEXT_FONT_STYLE      Gdiplus::FontStyleRegular

#define GW_DEFAULT_TEXT_FORMAT_ALIGNMENT      Gdiplus::StringAlignmentCenter;
#define GW_DEFAULT_TEXT_FORMAT_LINE_ALIGNMENT Gdiplus::StringAlignmentCenter;




#endif


