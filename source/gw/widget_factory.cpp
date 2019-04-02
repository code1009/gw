﻿/////////////////////////////////////////////////////////////////////////////
//
// File: widget_factory.cpp
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
#include "header.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace gw
{



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_factory
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_factory::widget_factory()
{
}

widget_factory::~widget_factory()
{
}

//===========================================================================
widget* widget_factory::create_instance(void)
{
	return CX_NULL_POINTER;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_event_handler_factory
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_event_handler_factory::widget_event_handler_factory()
{
}

widget_event_handler_factory::~widget_event_handler_factory()
{
}

//===========================================================================
widget_event_handler* widget_event_handler_factory::create_instance(void)
{
	return CX_NULL_POINTER;
}



/////////////////////////////////////////////////////////////////////////////
//
// Class: widget_iostream_factory
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
widget_iostream_factory::widget_iostream_factory()
{
}

widget_iostream_factory::~widget_iostream_factory()
{
}

//===========================================================================
widget_iostream* widget_iostream_factory::create_instance(void)
{
	return CX_NULL_POINTER;
}



////////////////////////////////////////////////////////////////////////////
//===========================================================================
}