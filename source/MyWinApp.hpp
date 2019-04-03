#pragma once

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "Mainframe.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CMyWinApp : public CWinApp
{
public:
	gw::widget_entry_collection _control_widget_entry_collection;
	gw::widget_entry_collection _diagram_widget_entry_collection;

public:
	CMyWinApp();
	virtual ~CMyWinApp();
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	CMainFrame* GetMainFrame() { return &m_Mainframe; }

private:
	CMainFrame m_Mainframe;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// returns a reference to the CMyWinApp object
inline CMyWinApp* GetMyWinApp() 
{
	return static_cast<CMyWinApp*>(&GetApp()); 
}
