#pragma once


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class diagram_edit : public gw::dgrm::edit
{
private:
	std::string _last_system_clipboard_stream;

public:
	diagram_edit();
	virtual ~diagram_edit();

public:
	virtual cx::bool_t create  (gw::widget_entry_collection* wec);
	virtual void       destroy (void);

public:
	virtual void on_edit_action_diagram_modified (void);
	virtual void on_diagram_property_changed (gw::dgrm::diagram_event* e);
	virtual void on_modified (cx::bool_t modified);
	virtual void on_select_changed (gw::dgrm::edit::select_changed_action_t action);
	virtual void update_system_clipboard (cx::bool_t save);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramEditorView : public CMyView
{
private:
	view_scroll_helper m_ViewScrollHelper;

private:
    int m_cxClientMax;
    int m_cyClientMax;

private:
	diagram_edit* m_Model;

	IDropTarget* m_pDropTarget;

public:
	CGWDiagramEditorView();
	virtual ~CGWDiagramEditorView();

public:
	virtual std::string GetViewType (void) { return "GWDiagramEditorView"; }

public:
    virtual void PreCreate(CREATESTRUCT& cs);

public:
    virtual int OnCreate(CREATESTRUCT& cs);
    virtual void OnDestroy();

public:
	virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam);
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
	LRESULT OnClose(UINT msg, WPARAM wparam, LPARAM lparam);

private:
	void Draw (CDC& dc);

private:
	BOOL OnFileOpen();
	BOOL OnFileSave();

	BOOL OnDiagramEditSelectAll    ();
	BOOL OnDiagramEditBringToTop   ();
	BOOL OnDiagramEditSendToBottom ();
	BOOL OnDiagramEditUndo         ();
	BOOL OnDiagramEditRedo         ();
	BOOL OnDiagramEditCut          ();
	BOOL OnDiagramEditCopy         ();
	BOOL OnDiagramEditPaste        ();
	BOOL OnDiagramEditDelete       ();

public:
	void SetViewPropertyChanged(void);
	diagram_edit* GetModel (void);
};
