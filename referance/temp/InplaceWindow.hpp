#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CInplaceWindow : public CWnd
{
public:
	CInplaceWindow();
	virtual ~CInplaceWindow();

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
	LRESULT OnLButtonDown(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnLButtonUp(UINT msg, WPARAM wparam, LPARAM lparam);

private:
	void Draw (CDC& dc);

private:
    int m_cxClientMax;
    int m_cyClientMax;
};


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CInplaceEditWindow : public CEdit
{
public:
	cx::bool_t m_Cancel;

public:
	CInplaceEditWindow();
	virtual ~CInplaceEditWindow();

public:
    virtual void PreCreate(CREATESTRUCT& cs);

public:
    virtual int OnCreate(CREATESTRUCT& cs);
    virtual void OnDestroy();

public:
    virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

    LRESULT OnKeyDown(UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT OnChar(UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT OnSetFocus(UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT OnKillFocus(UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT OnGetDlgCode(UINT msg, WPARAM wparam, LPARAM lparam);
};
