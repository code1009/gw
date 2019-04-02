#ifndef INCLUDED__CX__GW__DIAGRAM__DIAGRAM_CREATOR__HPP
#define INCLUDED__CX__GW__DIAGRAM__DIAGRAM_CREATOR__HPP

/////////////////////////////////////////////////////////////////////////////
//
// File: diagram_creator.hpp
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
//
// Class: diagram_creator
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_creator
{
private:
	named_diagram_pointer_container_t _container;
	
public:
	diagram_creator();
	virtual ~diagram_creator();

public:
	named_diagram_pointer_container_t& get_container (void);

public:
	virtual void delete_container (void);

public:
	virtual diagram*   find (std::string name);
	virtual cx::bool_t register_entry (diagram* wd);

public:
	virtual diagram* create_diagram (std::string name);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}
}





#endif


