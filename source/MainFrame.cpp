/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 0
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif


#if 0
IDW_MAIN                BITMAP                  "./toolbar.bmp"

    POPUP "&Options"
    BEGIN
        MENUITEM "MDI Tabs at Top",             IDM_TABBEDMDI_TOP, CHECKED
        MENUITEM "Container Tabs at Top",       IDM_CONTAINER_TOP, CHECKED
        MENUITEM "Hide Single Container Tab",   IDM_HIDE_SINGLE_TAB, CHECKED
    END
    POPUP "&Layout"
    BEGIN
        MENUITEM "&Default Layout",             IDM_DEFAULT_LAYOUT
        MENUITEM "Close All &Containers",       IDM_CLOSE_DOCKERS
        MENUITEM "Close All &MDI Children",     IDM_CLOSE_MDIS
    END
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
cx::bool_t ImageList_Add_Resource_PNG (HIMAGELIST hImagelist, cx::char_t* name)
{
	HBITMAP hBitmap = NULL;
	 
	CGdiPlusBitmapResource gdibmp;


	if (gdibmp.Load(name, _T("PNG"), NULL))
	{
		gdibmp.m_pBitmap->GetHBITMAP(Gdiplus::Color::Transparent, &hBitmap);
		ImageList_AddMasked(hImagelist, hBitmap, 0);

		return true;
	}


	return false;
}


	
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CMainFrame::CMainFrame() :
	m_isContainerTabsAtTop(FALSE),
	m_isHideSingleTab     (TRUE),
	m_isMDITabsAtTop      (TRUE), 
	m_pActiveDocker(NULL)
{
	// Constructor for CMainFrame. Its called after CFrame's constructor

	// Set m_MyTabbedMDI as the view window of the frame
	SetView(m_MyTabbedMDI);

	// Set the registry key name, and load the initial window position
	// Use a registry key name like "CompanyName\\Application"
#if 0
	LoadRegistrySettings(_T("cx\\gw"));
#endif

	m_DiagramStencilDocker  = CX_NULL_POINTER;
	m_DiagramPropertyDocker = CX_NULL_POINTER;
}

CMainFrame::~CMainFrame()
{
	// Destructor for CMainFrame.
}

//===========================================================================
void CMainFrame::LoadDefaultDockers()
{
	CDocker* pDockTop   ;
	CDocker* pDockRight ;
	CDocker* pDockBottom;
	CDocker* pDockLeft  ;


	pDockTop   	= NULL;
	pDockRight 	= NULL;
	pDockBottom	= NULL;
	pDockLeft  	= NULL;


	// Note: The  DockIDs are used for saving/restoring the dockers state in the registry
	DWORD style;

	style = 0;//DS_CLIENTEDGE; // The style added to each docker

	
	// Add the parent dockers
	CGWDiagramStencilDocker*  pDiagramStencilDocker;
	CGWDiagramPropertyDocker* pDiagramPropertyDocker  ;

//	CX_DEBUG_ASSERT(CX_NULL_POINTER==m_DiagramStencilDocker );
//	CX_DEBUG_ASSERT(CX_NULL_POINTER==m_DiagramPropertyDocker);

	pDiagramStencilDocker  = new CGWDiagramStencilDocker ();
	pDiagramPropertyDocker = new CGWDiagramPropertyDocker();

	pDockLeft  = AddDockedChild(pDiagramStencilDocker , DS_DOCKED_LEFT  | style, 200, ID_DOCKER_DIAGRAMSTENCIL );
	pDockRight = AddDockedChild(pDiagramPropertyDocker, DS_DOCKED_RIGHT | style, 400, ID_DOCKER_DIAGRAMPROPERTY);

	// Add the remaining dockers
//	pDockLeft->AddDockedChild(new CEventMessageDocker (), DS_DOCKED_CONTAINER | style, 400, ID_DOCKER_EVENTMESSAGE );
}

void CMainFrame::LoadDefaultMDIs()
{
//	m_MyTabbedMDI.GetTab().SetPadding(500,100);
	
	// Add some MDI tabs
//	m_MyTabbedMDI.AddMDIChild(new CGWControlFormView() , _T("ControlForm") , ID_MDI_VIEW_FORM );
	m_MyTabbedMDI.AddMDIChild(new CGWDiagramEditorView() , _T("도표") , ID_MDI_VIEW_DIAGRAMEDITOR);


	if (m_MyTabbedMDI.IsWindow())
	{
		m_MyTabbedMDI.SetActiveMDITab(0);
	}
}

//===========================================================================
void CMainFrame::SetContainerTabsAtTop(BOOL atTop)
{
	m_isContainerTabsAtTop = atTop;


	//-----------------------------------------------------------------------
	std::vector<DockPtr>::const_iterator iter;

	// Set the Tab position for each container
	for (iter = GetAllDockChildren().begin(); iter < GetAllDockChildren().end(); ++iter)
	{
		CDockContainer* pContainer = (*iter)->GetContainer();
		if (pContainer && pContainer->IsWindow())
		{
			pContainer->SetTabsAtTop(atTop);
		}
	}
}

void CMainFrame::HideSingleContainerTab(BOOL hideSingle)
{
	m_isHideSingleTab = hideSingle;


	//-----------------------------------------------------------------------
	std::vector<DockPtr>::const_iterator iter;

	// Set the Tab position for each container
	for (iter = GetAllDockChildren().begin(); iter < GetAllDockChildren().end(); ++iter)
	{
		CDockContainer* pContainer = (*iter)->GetContainer();
		if (pContainer && pContainer->IsWindow())
		{
			pContainer->SetHideSingleTab(hideSingle);
		}
	}
}

void CMainFrame::SetMDITabsAtTop(BOOL atTop)
{
	m_isMDITabsAtTop = atTop;

	
	//-----------------------------------------------------------------------
	m_MyTabbedMDI.GetTab().SetTabsAtTop(atTop);
}

//===========================================================================
BOOL CMainFrame::OnDefaultLayout()
{
	SetRedraw(FALSE);

	
	CloseAllDockers();
//	m_DiagramStencilDocker  = CX_NULL_POINTER;
//	m_DiagramPropertyDocker = CX_NULL_POINTER;

	m_MyTabbedMDI.CloseAllMDIChildren();
	
	
	LoadDefaultDockers();
	LoadDefaultMDIs();

	SetContainerTabsAtTop (m_isContainerTabsAtTop);
	HideSingleContainerTab(m_isHideSingleTab);
	SetMDITabsAtTop       (m_isMDITabsAtTop);
	

	SetRedraw(TRUE);
	

	RedrawWindow();

	return TRUE;
}

BOOL CMainFrame::OnCloseDockers()
{
	CloseAllDockers();
//	m_DiagramStencilDocker  = CX_NULL_POINTER;
//	m_DiagramPropertyDocker = CX_NULL_POINTER;

	return TRUE;
}

BOOL CMainFrame::OnCloseMDIs()
{
	m_MyTabbedMDI.CloseAllMDIChildren();
	return TRUE;
}

//===========================================================================
BOOL CMainFrame::OnContainerTabsAtTop()
// Reposition the tabs in the containers
{
	SetContainerTabsAtTop(!m_isContainerTabsAtTop);
	return TRUE;
}

BOOL CMainFrame::OnHideSingleTab()
{
	HideSingleContainerTab(!m_isHideSingleTab);
	return TRUE;
}

BOOL CMainFrame::OnMDITabsAtTop()
// Reposition TabbedMDI's tabs
{
	SetMDITabsAtTop(!m_isMDITabsAtTop);
	return TRUE;
}

//===========================================================================
BOOL CMainFrame::OnFileExit()
{
	// Issue a close request to the frame
	PostMessage(WM_CLOSE);
	return TRUE;
}

BOOL CMainFrame::OnFileNew()
{
//	m_MyTabbedMDI.AddMDIChild(new CGWControlFormView() , _T("ControlForm") , v++ );
	m_MyTabbedMDI.AddMDIChild(new CGWDiagramEditorView() , _T("도표") , ID_MDI_VIEW_DIAGRAMEDITOR);


	if (m_MyTabbedMDI.IsWindow())
		m_MyTabbedMDI.SetActiveMDITab(0);

	return TRUE;
}

//===========================================================================
CDocker* CMainFrame::NewDockerFromID(int dockID)
{
	CDocker* pDocker = NULL;


	switch (dockID)
	{
	case ID_DOCKER_DIAGRAMSTENCIL:
		pDocker = new CGWDiagramStencilDocker();
		break;

	case ID_DOCKER_DIAGRAMPROPERTY:
		pDocker = new CGWDiagramPropertyDocker();
		break;

	case ID_DOCKER_EVENTMESSAGE:
		pDocker = new CEventMessageDocker();
		break;

	default:
		CX_DEBUG_TRACEF(TW_THISCODE, "Unknown Dock ID");
		break;
	}

	return pDocker;
}

//===========================================================================
BOOL CMainFrame::SaveRegistrySettings()
{
#if 0
	CDockFrame::SaveRegistrySettings();
#endif

#if 0
	// Save the docker settings
	SaveDockRegistrySettings(GetRegistryKeyName());

	// Save the tabbedMDI settings
	m_MyTabbedMDI.SaveRegistrySettings(GetRegistryKeyName());
#endif

	return TRUE;
}

//===========================================================================
void CMainFrame::PreCreate(CREATESTRUCT& cs)
{
	// Call the base class function first
	CDockFrame::PreCreate(cs);

	// Hide the window initially by removing the WS_VISIBLE style
	cs.style &= ~WS_VISIBLE;

//	cs.dwExStyle |= WS_EX_CLIENTEDGE;
}

void CMainFrame::SetupMenuIcons()
{
	// Load the defualt set of icons from the toolbar
	// CDockFrame::SetupMenuIcons();

	// Add some extra icons for menu items
}

void CMainFrame::UpdateMenu()
{
	CWnd* pView = NULL;
		
		
	// Get the pointer to the active view
	if (m_pActiveDocker)
	{
		pView = m_pActiveDocker->GetActiveView();
	}


	CMyView* pMyView;
	CGWDiagramEditorView* pGWDiagramEditorView;


	UINT flags_copy           = MF_GRAYED;
	UINT flags_cut            = MF_GRAYED;
	UINT flags_paste          = MF_GRAYED;
	UINT flags_delete         = MF_GRAYED;
	UINT flags_undo           = MF_GRAYED;
	UINT flags_redo           = MF_GRAYED;
	UINT flags_bring_to_top   = MF_GRAYED;
	UINT flags_send_to_bottom = MF_GRAYED;


	pMyView = dynamic_cast<CMyView*>(pView);	
	if (pMyView)
	{
		if (pMyView->GetViewType()=="GWDiagramEditorView")
		{
			pGWDiagramEditorView = (CGWDiagramEditorView*)pMyView;

			flags_copy           = pGWDiagramEditorView->GetModel()->can_copy           () ? MF_ENABLED : MF_GRAYED;
			flags_cut            = pGWDiagramEditorView->GetModel()->can_cut            () ? MF_ENABLED : MF_GRAYED;
			flags_paste          = pGWDiagramEditorView->GetModel()->can_paste          () ? MF_ENABLED : MF_GRAYED;
			flags_delete         = pGWDiagramEditorView->GetModel()->can_remove         () ? MF_ENABLED : MF_GRAYED;

			flags_undo           = pGWDiagramEditorView->GetModel()->can_undo           () ? MF_ENABLED : MF_GRAYED;
			flags_redo           = pGWDiagramEditorView->GetModel()->can_redo           () ? MF_ENABLED : MF_GRAYED;

			flags_bring_to_top   = pGWDiagramEditorView->GetModel()->can_bring_to_top   () ? MF_ENABLED : MF_GRAYED;
			flags_send_to_bottom = pGWDiagramEditorView->GetModel()->can_send_to_bottom () ? MF_ENABLED : MF_GRAYED;
		}
	}


	CMenu editMenu = GetFrameMenu().GetSubMenu(1);


	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_COPY           , MF_BYCOMMAND | flags_copy            );
	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_CUT            , MF_BYCOMMAND | flags_cut             );
	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_PASTE          , MF_BYCOMMAND | flags_paste           );
	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_DELETE         , MF_BYCOMMAND | flags_delete          );

	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_UNDO           , MF_BYCOMMAND | flags_undo            );
	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_REDO           , MF_BYCOMMAND | flags_redo            );

	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_BRING_TO_TOP   , MF_BYCOMMAND | flags_bring_to_top    );
	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_SEND_TO_BOTTOM , MF_BYCOMMAND | flags_send_to_bottom );

	editMenu.EnableMenuItem(IDM_DIAGRAM_EDIT_SELECT_ALL     , MF_BYCOMMAND | MF_ENABLED            );
}

void CMainFrame::UpdateToolBar()
{
	CWnd* pView = NULL;
		
		
	// Get the pointer to the active view
	if (m_pActiveDocker)
	{
		pView = m_pActiveDocker->GetActiveView();
	}


	CMyView* pMyView;
	CGWDiagramEditorView* pGWDiagramEditorView;


	UINT flags_copy           = 0u;
	UINT flags_cut            = 0u;
	UINT flags_paste          = 0u;
	UINT flags_delete         = 0u;
	UINT flags_undo           = 0u;
	UINT flags_redo           = 0u;
	UINT flags_bring_to_top   = 0u;
	UINT flags_send_to_bottom = 0u;


	pMyView = dynamic_cast<CMyView*>(pView);	
	if (pMyView)
	{
		if (pMyView->GetViewType()=="GWDiagramEditorView")
		{
			pGWDiagramEditorView = (CGWDiagramEditorView*)pMyView;

			flags_copy           = pGWDiagramEditorView->GetModel()->can_copy           () ? TBSTATE_ENABLED : 0u;
			flags_cut            = pGWDiagramEditorView->GetModel()->can_cut            () ? TBSTATE_ENABLED : 0u;
			flags_paste          = pGWDiagramEditorView->GetModel()->can_paste          () ? TBSTATE_ENABLED : 0u;
			flags_delete         = pGWDiagramEditorView->GetModel()->can_remove         () ? TBSTATE_ENABLED : 0u;
			flags_undo           = pGWDiagramEditorView->GetModel()->can_undo           () ? TBSTATE_ENABLED : 0u;
			flags_redo           = pGWDiagramEditorView->GetModel()->can_redo           () ? TBSTATE_ENABLED : 0u;
			flags_bring_to_top   = pGWDiagramEditorView->GetModel()->can_bring_to_top   () ? TBSTATE_ENABLED : 0u;
			flags_send_to_bottom = pGWDiagramEditorView->GetModel()->can_send_to_bottom () ? TBSTATE_ENABLED : 0u;
		}
	}

	GetToolBar()        .SetButtonState(IDM_DIAGRAM_EDIT_COPY           , flags_copy   );
	GetToolBar()        .SetButtonState(IDM_DIAGRAM_EDIT_CUT            , flags_cut    );
	GetToolBar()        .SetButtonState(IDM_DIAGRAM_EDIT_PASTE          , flags_paste  );
	GetToolBar()        .SetButtonState(IDM_DIAGRAM_EDIT_DELETE         , flags_delete );
															            
	m_DiagramEditToolBar.SetButtonState(IDM_DIAGRAM_EDIT_UNDO           , flags_undo );
	m_DiagramEditToolBar.SetButtonState(IDM_DIAGRAM_EDIT_REDO           , flags_redo );

	m_DiagramEditToolBar.SetButtonState(IDM_DIAGRAM_EDIT_BRING_TO_TOP   , flags_bring_to_top   );
	m_DiagramEditToolBar.SetButtonState(IDM_DIAGRAM_EDIT_SEND_TO_BOTTOM , flags_send_to_bottom );

	m_DiagramEditToolBar.SetButtonState(IDM_DIAGRAM_EDIT_SELECT_ALL     , TBSTATE_ENABLED );
}

void CMainFrame::SetupToolBar()
{
    m_ToolBarImage.Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);

    ImageList_Add_Resource_PNG(m_ToolBarImage, "file_new.png");
    ImageList_Add_Resource_PNG(m_ToolBarImage, "file_open.png");
    ImageList_Add_Resource_PNG(m_ToolBarImage, "file_save.png");
    ImageList_Add_Resource_PNG(m_ToolBarImage, "edit_cut.png");
    ImageList_Add_Resource_PNG(m_ToolBarImage, "edit_copy.png");
    ImageList_Add_Resource_PNG(m_ToolBarImage, "edit_paste.png");
    ImageList_Add_Resource_PNG(m_ToolBarImage, "help_about.png");
	GetToolBar().SetImageList(m_ToolBarImage);
	GetToolBar().SetHotImageList(0);
	GetToolBar().SetDisableImageList(0);

	/*
//    SetTBImageList(GetToolBar(),    m_ToolBarImage, 0, 0);
    if (GetReBar().IsWindow())
    {
        SIZE MaxSize = GetToolBar().GetMaxSize();
        GetReBar().SendMessage(UWM_TBRESIZE, (WPARAM)(GetToolBar().GetHwnd()),
            (LPARAM)(&MaxSize));
    }

    SetTBImageListHot(GetToolBar(), m_ToolBarImage, 0, 0);
    SetTBImageListDis(GetToolBar(), m_ToolBarImage, 0, 0);
	*/

	// Set the Resource IDs for the toolbar buttons
	AddToolBarButton( IDM_FILE_NEW   );
	AddToolBarButton( IDM_FILE_OPEN,  TRUE );
	AddToolBarButton( IDM_FILE_SAVE,  TRUE );

	AddToolBarButton( 0 );  // Separator
	AddToolBarButton( IDM_EDIT_CUT,   TRUE );
	AddToolBarButton( IDM_EDIT_COPY,  TRUE );
	AddToolBarButton( IDM_EDIT_PASTE, TRUE );

	AddToolBarButton( 0 );  // Separator
	AddToolBarButton( IDM_HELP_ABOUT);

#if 0
	AddToolBarButton( IDM_HELP_ABOUT, TRUE, "About");


	DWORD style;


	style = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_NODIVIDER | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_LIST;
	GetToolBar().SetStyle(style);
	GetToolBar().SetButtonStyle(IDM_HELP_ABOUT, TBSTYLE_AUTOSIZE);
//	SetToolBarImages(RGB(192,192,192), IDB_TOOLBAR_NORM, IDB_TOOLBAR_HOT, IDB_TOOLBAR_DIS);


/*
	// Use larger buttons with seperate imagelists for normal, hot and disabled buttons.
	SetToolBarImages(RGB(192,192,192), IDB_TOOLBAR_NORM, IDB_TOOLBAR_HOT, IDB_TOOLBAR_DIS);



	// Configure the "New" toolbar button to bring up a menu
	// Setting this style requires comctl32.dll version 4.72 or later
	if (GetComCtlVersion() >= 472)
	{
		GetToolBar().SetButtonStyle(IDM_FILE_NEW, BTNS_WHOLEDROPDOWN);
	}
*/
#endif
}

LRESULT CMainFrame::WndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
//  switch (msg)
//  {
//  
//  }

	// Always pass unhandled messages on to WndProcDefault
	return WndProcDefault(msg, wparam, lparam);
}

//===========================================================================
LRESULT CMainFrame::OnDockActivated(UINT msg, WPARAM wparam, LPARAM lparam)
// Called when a docker is activated.
// Store the active docker in preparation for menu input. Excludes active 
// docker change for undocked dockers when using the menu.
{
	CPoint pt = GetCursorPos();
	if (WindowFromPoint(pt) != GetMenuBar())
		m_pActiveDocker = GetActiveDocker();


	if (m_pActiveDocker)
	{
		int id = m_pActiveDocker->GetDockID();

		CX_DEBUG_TRACEF(TW_THISCODE, "id = %d", id);
	}


	UpdateToolBar();

	return CDockFrame::OnDockActivated(msg, wparam, lparam);
}

LRESULT CMainFrame::OnDockDestroyed(UINT msg, WPARAM wparam, LPARAM lparam)
{
	CDocker* pDocker = reinterpret_cast<CDocker*>(wparam);

	int id = pDocker->GetDockID();

	CX_DEBUG_TRACEF(TW_THISCODE, "id = %d", id);

	if (id==ID_DOCKER_DIAGRAMSTENCIL)
	{
//		m_DiagramStencilDocker = CX_NULL_POINTER;
	}
	if (id==ID_DOCKER_DIAGRAMPROPERTY)
	{
//		m_DiagramPropertyDocker = CX_NULL_POINTER;
	}

	return CDockFrame::OnDockDestroyed(msg, wparam, lparam);
}

//===========================================================================
int CMainFrame::OnCreate(CREATESTRUCT& cs)
{
	//-----------------------------------------------------------------------
	// OnCreate controls the way the frame is created.
	// Overriding CFrame::OnCreate is optional.

	// A menu is added if the IDW_MAIN menu resource is defined.
	// Frames have all options enabled by default. 
	// Use the following functions to disable options.

	// UseIndicatorStatus(FALSE);    // Don't show keyboard indicators in the StatusBar
	// UseMenuStatus(FALSE);         // Don't show menu descriptions in the StatusBar
	// UseReBar(FALSE);              // Don't use a ReBar
	// UseStatusBar(FALSE);          // Don't use a StatusBar
	UseThemes(FALSE);             // Don't use themes
	// UseToolBar(FALSE);            // Don't use a ToolBar


	//-----------------------------------------------------------------------
	// call the base class function
	/*return*/ CDockFrame::OnCreate(cs);

	
	//-----------------------------------------------------------------------
    DWORD style; 
	
	
	//-----------------------------------------------------------------------
	style = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_NODIVIDER | RBS_VARHEIGHT;
//	m_ReBar.CreateEx(0, REBARCLASSNAME, 0, style, CRect(0,0,0,0), *this, 0);


	//-----------------------------------------------------------------------
    m_DiagramEditToolBarImage.Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);
    ImageList_Add_Resource_PNG(m_DiagramEditToolBarImage, "edit_undo.png");
    ImageList_Add_Resource_PNG(m_DiagramEditToolBarImage, "edit_redo.png");
    ImageList_Add_Resource_PNG(m_DiagramEditToolBarImage, "diagram_edit_select_all.png");
    ImageList_Add_Resource_PNG(m_DiagramEditToolBarImage, "diagram_edit_send_to_bottom.png");
    ImageList_Add_Resource_PNG(m_DiagramEditToolBarImage, "diagram_edit_bring_to_top.png");


	//-----------------------------------------------------------------------
	style = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_NODIVIDER | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_LIST ;
    m_DiagramEditToolBar.CreateEx(0, TOOLBARCLASSNAME, 0, style, CRect(0,0,0,0), GetReBar(), 0);
    m_DiagramEditToolBar.SetImageList(m_DiagramEditToolBarImage);

	TBBUTTON buttonInfo[] =
    {
        { 0, IDM_DIAGRAM_EDIT_UNDO           , TBSTATE_ENABLED, TBSTYLE_AUTOSIZE|TBSTYLE_BUTTON, {0}, 0, 0 },
        { 1, IDM_DIAGRAM_EDIT_REDO           , TBSTATE_ENABLED, TBSTYLE_AUTOSIZE|TBSTYLE_BUTTON, {0}, 0, 0 },
        { 2, IDM_DIAGRAM_EDIT_SELECT_ALL     , TBSTATE_ENABLED, TBSTYLE_AUTOSIZE|TBSTYLE_BUTTON, {0}, 0, 0 },
        { 3, IDM_DIAGRAM_EDIT_SEND_TO_BOTTOM , TBSTATE_ENABLED, TBSTYLE_AUTOSIZE|TBSTYLE_BUTTON, {0}, 0, 0 },
        { 4, IDM_DIAGRAM_EDIT_BRING_TO_TOP   , TBSTATE_ENABLED, TBSTYLE_AUTOSIZE|TBSTYLE_BUTTON, {0}, 0, 0 }
    };  
    m_DiagramEditToolBar.AddButtons(5, buttonInfo);
	m_DiagramEditToolBar.SetButtonText(IDM_DIAGRAM_EDIT_UNDO           , "Undo");
	m_DiagramEditToolBar.SetButtonText(IDM_DIAGRAM_EDIT_REDO           , "Redo");
	m_DiagramEditToolBar.SetButtonText(IDM_DIAGRAM_EDIT_SELECT_ALL     , "Select All");
	m_DiagramEditToolBar.SetButtonText(IDM_DIAGRAM_EDIT_SEND_TO_BOTTOM , "Send to Bottom");
	m_DiagramEditToolBar.SetButtonText(IDM_DIAGRAM_EDIT_BRING_TO_TOP   , "Bring to Top");
	
	SetWrapState(&m_DiagramEditToolBar, TRUE);


	//-----------------------------------------------------------------------
    REBARBANDINFO rbbi;


    ZeroMemory(&rbbi, sizeof(REBARBANDINFO));
    rbbi.fMask      = RBBIM_CHILD |RBBIM_CHILDSIZE| RBBIM_ID | RBBIM_SIZE | RBBIM_STYLE;
    rbbi.fStyle     = RBBS_BREAK;
    rbbi.hwndChild  = m_DiagramEditToolBar.GetHwnd();
    rbbi.wID        = 9999;
    rbbi.cyMinChild = m_DiagramEditToolBar.GetMaxSize().cy+1;
    GetReBar().InsertBand(-1, rbbi);

	return 0;
}

// Note: Vertical toolbars require each button to have TBSTATE_WRAP, set for group buttons to work.
//       Horizontal toolbars require the TBSTATE_WRAP removed.
void CMainFrame::SetWrapState(CToolBar* pToolBar, BOOL isWrapped)
{
    for (int i = 0; i < m_DiagramEditToolBar.GetButtonCount(); ++i)
    {
        int id = pToolBar->GetCommandID(i);
        pToolBar->SetButtonState(id, TBSTATE_ENABLED | (isWrapped ? TBSTATE_WRAP : 0));
    }
}

void CMainFrame::RecalcLayout()
// Override CFrame::RecalcLayout to add the positioning of our rebar
{
    // Resize the status bar
    if (GetStatusBar().IsWindow() && GetStatusBar().IsWindowVisible())
    {
        GetStatusBar().SetWindowPos(NULL, 0, 0, 0, 0, SWP_SHOWWINDOW);
        GetStatusBar().Invalidate();
        if (IsUsingMenuStatus())
            GetStatusBar().SetWindowText(GetStatusText());

        SetStatusIndicators();
    }

    // Resize the rebar or toolbar
    if (GetReBar().IsWindow())
    {
        GetReBar().SendMessage(WM_SIZE, 0, 0);
        GetReBar().Invalidate();
    }
    else if (GetToolBar().IsWindow() && GetToolBar().IsWindowVisible())
        GetToolBar().SendMessage(TB_AUTOSIZE, 0, 0);

    // Position the additional rebar at the top, left, right or bottom of the view.
    if (m_ReBar.IsWindow())
        SetReBarPos();

    // Position the view window
    CDockFrame::RecalcLayout();

    // Adjust rebar bands
    if (GetReBar().IsWindow())
    {
        if (GetReBarTheme().UseThemes && GetReBarTheme().BandsLeft)
            GetReBar().MoveBandsLeft();

        if (GetMenuBar().IsWindow())
            SetMenuBarBandSize();
    }
}

CRect CMainFrame::GetViewRect() const
{
    CRect rcClient = GetClientRect();

    if (GetStatusBar().IsWindow() && (GetStatusBar().IsWindowVisible()))
        rcClient = ExcludeChildRect(rcClient, GetStatusBar());

    if (IsReBarSupported() && IsUsingReBar() && GetReBar().IsWindow())
        rcClient = ExcludeChildRect(rcClient, GetReBar());
    else
        if (GetToolBar().IsWindow() && GetToolBar().IsWindowVisible())
            rcClient = ExcludeChildRect(rcClient, GetToolBar());

    if (m_ReBar.IsWindow())
        rcClient = ExcludeChildRect(rcClient, m_ReBar);

    return rcClient;
}

void CMainFrame::SetReBarPos(void)
{
    int cxRB = 0;
    for (UINT u = 0 ; u < m_ReBar.GetRowCount(); ++u)
        cxRB += m_ReBar.GetRowHeight(u);

    CRect rc = CDockFrame::GetViewRect();
    int cyRB = MIN(cxRB, rc.Height());

    DWORD style = m_ReBar.GetStyle();
    style &= CCS_VERT | CCS_BOTTOM; // Filter unwanted styles

    switch(style)
    {
    case CCS_LEFT:
        m_ReBar.SetWindowPos(NULL, 0, rc.top, cxRB, rc.Height(), SWP_SHOWWINDOW);
//        m_DiagramEditToolBar.PressButton(IDM_LEFT, TRUE);
        break;
    case CCS_RIGHT:
        m_ReBar.SetWindowPos(NULL, rc.Width() - cxRB, rc.top, cxRB, rc.Height(), SWP_SHOWWINDOW);
//        m_DiagramEditToolBar.PressButton(IDM_RIGHT, TRUE);
        break;
    case CCS_BOTTOM:
        m_ReBar.SetWindowPos(NULL, 0, rc.bottom - cyRB, rc.Width(), cyRB, SWP_SHOWWINDOW);
//        m_DiagramEditToolBar.PressButton(IDM_BOTTOM, TRUE);
        break;
    default:
        m_ReBar.SetWindowPos(NULL, 0, rc.top, rc.Width(), cyRB, SWP_SHOWWINDOW);    
//        m_DiagramEditToolBar.PressButton(IDM_TOP, TRUE);
        break;
    }

    Invalidate();
    m_ReBar.RedrawWindow();     
}

void CMainFrame::OnInitialUpdate()
{
	SetDockStyle(DS_CLIENTEDGE);

	// Load dock settings
 //	if (!LoadDockRegistrySettings(GetRegistryKeyName()))
	{
		LoadDefaultDockers();
	}

	// Load MDI child settings
 //	if (!m_MyTabbedMDI.LoadRegistrySettings(GetRegistryKeyName()))
	{
		LoadDefaultMDIs();
	}

	// Hide the container's tab if it has just one tab
	HideSingleContainerTab(m_isHideSingleTab);

	// Get a copy of the Frame's menu
	CMenu frameMenu = GetFrameMenu();

	// Modify the menu
	int nMenuPos = frameMenu.GetMenuItemCount() - 1;
	CMenu winMenu = m_MyTabbedMDI.GetListMenu();
	frameMenu.InsertPopupMenu(nMenuPos, MF_BYPOSITION, winMenu, _T("&Window"));

	// Replace the frame's menu with our modified menu
	SetFrameMenu(frameMenu);

	// PreCreate initially set the window as invisible, so show it now.
	ShowWindow(GetInitValues().showCmd);
	RedrawWindow(RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}

LRESULT CMainFrame::OnInitMenuPopup(UINT msg, WPARAM wparam, LPARAM lparam)
{
	// Update the "Window" menu
	m_MyTabbedMDI.GetListMenu();

	return CDockFrame::OnInitMenuPopup(msg, wparam, lparam);
}

void CMainFrame::OnMenuUpdate(UINT id)
// Called when menu items are about to be displayed
{
	// Only for the Menu IDs we wish to modify
	if (id >= IDM_EDIT_UNDO && id <= IDM_EDIT_DELETE)
	{
		UpdateMenu();
	}
	

	UINT check;


	switch (id)
	{
	case IDM_CONTAINER_TOP:
		check = (m_isContainerTabsAtTop) ? MF_CHECKED : MF_UNCHECKED;
		GetFrameMenu().CheckMenuItem(id, check);
		break;

	case IDM_HIDE_SINGLE_TAB:
		check = (m_isHideSingleTab) ? MF_CHECKED : MF_UNCHECKED;
		GetFrameMenu().CheckMenuItem(id, check);
		break;

	case IDM_TABBEDMDI_TOP:
		check = (m_isMDITabsAtTop) ? MF_CHECKED : MF_UNCHECKED;
		GetFrameMenu().CheckMenuItem(id, check);
	}


	CDockFrame::OnMenuUpdate(id);
}

BOOL CMainFrame::OnViewDiagramProperty()
{
	if (NULL!=m_DiagramPropertyDocker)
	{
		return TRUE;
	}


	CDocker* pDockTop   ;
	CDocker* pDockRight ;
	CDocker* pDockBottom;
	CDocker* pDockLeft  ;


	pDockTop   	= NULL;
	pDockRight 	= NULL;
	pDockBottom	= NULL;
	pDockLeft  	= NULL;


	DWORD style;

	style = 0;//DS_CLIENTEDGE; // The style added to each docker

	
	CGWDiagramPropertyDocker* pDiagramPropertyDocker;

	pDiagramPropertyDocker = new CGWDiagramPropertyDocker();

	pDockLeft = AddDockedChild(pDiagramPropertyDocker, DS_DOCKED_RIGHT | style, 400, ID_DOCKER_DIAGRAMPROPERTY);


	return TRUE;
}

BOOL CMainFrame::OnViewDiagramStencil()
{
	if (NULL!=m_DiagramStencilDocker)
	{
		return TRUE;
	}


	CDocker* pDockTop   ;
	CDocker* pDockRight ;
	CDocker* pDockBottom;
	CDocker* pDockLeft  ;


	pDockTop   	= NULL;
	pDockRight 	= NULL;
	pDockBottom	= NULL;
	pDockLeft  	= NULL;


	DWORD style;

	style = 0;//DS_CLIENTEDGE; // The style added to each docker

	
	CGWDiagramStencilDocker* pDiagramStencilDocker;


	pDiagramStencilDocker = new CGWDiagramStencilDocker ();

	pDockLeft  = AddDockedChild(pDiagramStencilDocker, DS_DOCKED_LEFT  | style, 200, ID_DOCKER_DIAGRAMSTENCIL);

	return TRUE;
}

BOOL CMainFrame::OnCommand(WPARAM wparam, LPARAM lparam)
{
	// OnCommand responds to menu and and toolbar input
	UINT id = LOWORD(wparam);
	switch (id)
	{
	case IDM_CLOSE_DOCKERS:     return OnCloseDockers();
	case IDM_CLOSE_MDIS:        return OnCloseMDIs();
	case IDM_DEFAULT_LAYOUT:    return OnDefaultLayout();

	case IDM_CONTAINER_TOP:     return OnContainerTabsAtTop();
	case IDM_HIDE_SINGLE_TAB:   return OnHideSingleTab();
	case IDM_TABBEDMDI_TOP:     return OnMDITabsAtTop();

	case IDM_FILE_NEW:          return OnFileNew();

	case IDM_FILE_EXIT:         return OnFileExit();

	case IDM_HELP_ABOUT:        return OnHelp();

	case IDW_VIEW_STATUSBAR:    return OnViewStatusBar();
	case IDW_VIEW_TOOLBAR:      return OnViewToolBar();

	case IDW_VIEW_DIAGRAM_PROPERTY: return OnViewDiagramProperty();
	case IDW_VIEW_DIAGRAM_STENCIL : return OnViewDiagramStencil();

	case IDW_FIRSTCHILD:
	case IDW_FIRSTCHILD + 1:
	case IDW_FIRSTCHILD + 2:
	case IDW_FIRSTCHILD + 3:
	case IDW_FIRSTCHILD + 4:
	case IDW_FIRSTCHILD + 5:
	case IDW_FIRSTCHILD + 6:
	case IDW_FIRSTCHILD + 7:
	case IDW_FIRSTCHILD + 8:
	{
		int tab = LOWORD(wparam) - IDW_FIRSTCHILD;
		m_MyTabbedMDI.SetActiveMDITab(tab);
		return TRUE;
	}
	case IDW_FIRSTCHILD + 9:
	{
		m_MyTabbedMDI.ShowListDialog();
		return TRUE;
	}

	default:
	{
		// Pass the command on to the view of the active docker
		if (m_pActiveDocker)
		{
			if (m_pActiveDocker->GetActiveView())
			{
				m_pActiveDocker->GetActiveView()->SendMessage(WM_COMMAND, wparam, lparam);
			}
		}
	}
	}

	return FALSE;
}


