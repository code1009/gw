#ifndef INCLUDED__CX__GW__STDAFX__H
#define INCLUDED__CX__GW__STDAFX__H
#if 0

/////////////////////////////////////////////////////////////////////////////
//
// File: stdafx.h
//
// Created by code1009.
// Created on Dec-17th, 2014.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//#include "../stdafx.h"
// Predefinitions for windows.h go here
//#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers
#define WINVER          0x0501
#define _WIN32_WINNT    0x0501
#define _WIN32_IE       0x0601
#define _RICHEDIT_VER   0x0300

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// stops windows.h including winsock.h
#define _WINSOCKAPI_



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//
//#include <stdio.h>
//
#pragma comment(lib, "Ws2_32.lib")

#include <SDKDDKVer.h>

#include <vector>               // Add support for std::vector
#include <map>                  // Add support for std::map
#include <string>               // Add support for std::string
#include <sstream>              // Add support for stringstream
#include <cassert>              // Add support for the assert macro
#include <stdio.h>              // Add support for C style printf, sprintf, etc.
#include <stdlib.h>             // Add support for C style character conversions atoi etc. 
#include <tchar.h>              // Add support for C style TCHARs.


#endif
#endif


