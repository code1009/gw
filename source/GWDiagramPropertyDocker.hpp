#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef std::map<std::string,property_accessor*> named_property_accessor_pointer_container_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramPropertyDockerWnd : public CWnd
{
private:
	int m_cxClientMax;
	int m_cyClientMax;

public:
	UINT m_PropGridCtlID;
	HWND m_hPropGridCtl;

public:
	typedef enum _activated_property_t
	{
		ACTIVATED_PROPERTY_NONE,
		ACTIVATED_PROPERTY_VIEW,
		ACTIVATED_PROPERTY_DIAGRAM
	} activated_property_t;

	activated_property_t m_ActivatedProperty;

public:
	gw::view*  m_View;
	cx::bool_t m_ViewPropertyChanged;

public:
	gw::dgrm::diagram* m_Diagram;
	cx::bool_t m_DiagramPropertyChanged;

public:
	named_property_accessor_pointer_container_t m_EntryContainer;
	view_property_accessor*                     m_ViewPropertyAccessor;

public:
	cx::uint_t m_DialogFlag;

public:
	CGWDiagramPropertyDockerWnd();
	virtual ~CGWDiagramPropertyDockerWnd();

public:
	virtual void PreCreate(CREATESTRUCT& cs);

public:
	virtual int OnCreate(CREATESTRUCT& cs);
	virtual void OnDestroy();

	virtual LRESULT OnNotify(WPARAM wparam, LPARAM lparam);

public:
	virtual LRESULT WndProc(UINT msg, WPARAM wparam, LPARAM lparam);

private:
	LRESULT OnMouseActivate(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnSize(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnTimer(UINT msg, WPARAM wparam, LPARAM lparam);

public:
	void OnCloseView           (gw::view* view_pointer);
	void OnActivatedView       (gw::view* view_pointer);
	void OnViewPropertyChanged (gw::view* view_pointer);

public:
	void LoadViewPropertyToControl (void);
	void SetViewPropertyToControl  (void);
	void SetViewPropertyFromControl(cx::int_t index, LPPROPGRIDITEM item);

public:
	void OnSelectChanged         (gw::dgrm::diagram* diagram_pointer);
	void OnDiagramPropertyChanged(gw::dgrm::diagram* diagram_pointer);

public:
	void LoadDiagramPropertyToControl (void);
	void SetDiagramPropertyToControl  (void);
	void SetDiagramPropertyFromControl(cx::int_t index, LPPROPGRIDITEM item);

public:
	void LoadEntry (void);

public:
	named_property_accessor_pointer_container_t& GetEntryContainer(void);

	void DeleteEntryContainer (void);

public:
	property_accessor* FindEntry (std::string name);
	cx::bool_t         AddEntry  (std::string name, property_accessor* e);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class CGWDiagramPropertyDockContainer : public CDockContainer
{
public:
	CGWDiagramPropertyDockContainer(); 
	virtual ~CGWDiagramPropertyDockContainer();

public:
	CGWDiagramPropertyDockerWnd m_Wnd;
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================      
class CGWDiagramPropertyDocker : public CDocker
{
public:
	CGWDiagramPropertyDocker(); 
	virtual ~CGWDiagramPropertyDocker();

public:
	CGWDiagramPropertyDockContainer m_DockContainer;
};


