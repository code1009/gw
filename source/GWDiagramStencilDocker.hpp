#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_stencil : public gw::ctrl::form
{
public:
	std::vector<gw::ctrl::control*> _control_container;
	std::vector<std::string>        _control_param_container;;

	gw::drag_data_t* _drag_data_pointer;

	IDropSource* _pDropSource;
	IDataObject* _pDataObject;

public:
	diagram_stencil();
	virtual ~diagram_stencil();

public:
	virtual cx::bool_t create  (gw::widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual void on_widget_mouse_clicked   (gw::widget_mouse_event* e);
	virtual void on_widget_mouse_dbclicked (gw::widget_mouse_event* e);
	virtual void on_widget_mouse_pressed   (gw::widget_mouse_event* e);

public:
	void resize_control (cx::int_t window_cx, cx::int_t window_cy);

public:
	void load_diagram(gw::widget_entry_collection* wec);

public:
	void drag_drop (gw::widget_mouse_event* e, std::string name);
};
	


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramStencilWnd : public CWnd
{
public:
	CGWDiagramStencilWnd();
	virtual ~CGWDiagramStencilWnd();

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

private:
	view_scroll_helper m_ViewScrollHelper;

private:
	diagram_stencil* m_Model;

private:
	IDropSource*    m_pDropSource;
	IDataObject*    m_pDataObject;
	gw::drag_data_t m_DragData;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramStencilContainer : public CDockContainer
{
public:
    CGWDiagramStencilContainer(); 
    virtual ~CGWDiagramStencilContainer();

private:
    CGWDiagramStencilWnd m_Wnd;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramStencilDocker : public CDocker
{
public:
    CGWDiagramStencilDocker(); 
    virtual ~CGWDiagramStencilDocker();

private:
    CGWDiagramStencilContainer m_DockContainer;
};


