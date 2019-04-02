#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWControlFormView : public CMyView
{
public:
	CGWControlFormView();
	virtual ~CGWControlFormView();

public:
	virtual void PreCreate(CREATESTRUCT& cs);

public:
	virtual int OnCreate(CREATESTRUCT& cs);
	virtual void OnDestroy();

public:
	virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

public:
//    virtual LRESULT OnPaint(UINT msg, WPARAM wparam, LPARAM lparam);
	virtual void OnDraw (CDC& dc);
	virtual BOOL OnEraseBkgnd(CDC& dc);

private:
	LRESULT OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnTimer(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnSize(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnHScroll(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnVScroll(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnMouseWheel(UINT msg, WPARAM wparam, LPARAM lparam);

private:
	void Draw (CDC& dc);

private:
	int m_cxClientMax;
	int m_cyClientMax;

private:
	gw::ctrl::form* m_Model;
};
