#ifndef INCLUDED__CX__GW__DIAGRAM__DECLARATION__HPP
#define INCLUDED__CX__GW__DIAGRAM__DECLARATION__HPP

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
namespace dgrm
{



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class document;
class json_document_reader;
class json_document_writer;

class anchor;
class diagram; // dtor(): 소유하고 있는 instance delete 호출

class diagram_creator; // dtor(): 소유하고 있는 instance delete 호출

class design;

class edit;
class edit_action;
	class diagram_select_edit_action       ;
	class diagram_single_select_edit_action;
	class diagram_move_edit_action         ;
	class diagram_add_edit_action          ;
	class anchor_move_edit_action          ;
class edit_timeline;
class edit_history ; // dtor(): 소유하고 있는 instance delete 호출


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef std::map<std::string, diagram*> named_diagram_pointer_container_t;
typedef std::vector<edit_timeline*>     edit_timeline_pointer_container_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef enum _diagram_mode_t
{
	DIAGRAM_MODE_NONE   = 0,
	DIAGRAM_MODE_DESIGN = 1,
	DIAGRAM_MODE_EDIT   = 2,
} diagram_mode_t;
	
//===========================================================================
typedef enum _anchor_id_t
{
	ANCHOR_ID_NONE   =  0,
	ANCHOR_ID_LT     =  1,
	ANCHOR_ID_RT     =  2,
	ANCHOR_ID_RB     =  3,
	ANCHOR_ID_LB     =  4,
	ANCHOR_ID_CENTER =  5,
	ANCHOR_ID_VC_L   =  6,
	ANCHOR_ID_VC_R   =  7,
	ANCHOR_ID_HC_T   =  8,
	ANCHOR_ID_HC_B   =  9,
} anchor_id_t;
	


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#define GW_DIAGRAM_EDIT_HISTORY_MAX_COUNT 100





#endif


