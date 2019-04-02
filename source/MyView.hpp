#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CMyView : public CWnd
{
public:
	CMyView();
	virtual ~CMyView();

public:
	virtual std::string GetViewType (void) { return "MyView"; }
};


