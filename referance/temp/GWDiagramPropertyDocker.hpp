#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramPropertyDockerWnd : public CWnd
{
public:
	CFont m_Font;

public:
	CGWDiagramPropertyDockerWnd();
	virtual ~CGWDiagramPropertyDockerWnd();

public:
    virtual void PreCreate(CREATESTRUCT& cs);

public:
    virtual int OnCreate(CREATESTRUCT& cs);
    virtual void OnDestroy();

	virtual LRESULT OnNotifyReflect(WPARAM wparam, LPARAM lparam);
	virtual LRESULT OnNotify(WPARAM wparam, LPARAM lparam);

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
	LRESULT OnGetFont(UINT msg, WPARAM wparam, LPARAM lparam);

private:
	void Draw (CDC& dc);

private:
    int m_cxClientMax;
    int m_cyClientMax;

private:
	view_scroll_helper m_ViewScrollHelper;

private:
	property_list* m_Model;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramPropertyDockContainer : public CDockContainer
{
public:
	CGWDiagramPropertyDockContainer(); 
	~CGWDiagramPropertyDockContainer() {}

private:
	CGWDiagramPropertyDockerWnd m_Wnd;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================      
class CGWDiagramPropertyDocker : public CDocker
{
public:
	CGWDiagramPropertyDocker(); 
	virtual ~CGWDiagramPropertyDocker() {}

private:
	CGWDiagramPropertyDockContainer m_DockContainer;
};

