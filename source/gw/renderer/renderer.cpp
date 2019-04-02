﻿/////////////////////////////////////////////////////////////////////////////
//
// File: renderer.cpp
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



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
renderer::renderer()
{
	_model = CX_NULL_POINTER;
}

renderer::~renderer()
{
}

//===========================================================================
model* renderer::get_model (void)
{
	return _model;
}

void renderer::set_model (model* m)
{
	_model = m;
}

//===========================================================================
void renderer::render (graphic_t g)
{
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
