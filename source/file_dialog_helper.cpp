/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "stdafx.h"
#include "Application.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1
#define TW_THISCODE cx::debug::get_null_trace_writer()
#else
#define TW_THISCODE cx::debug::get_app_normal_trace_writer()
#endif



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
char _ofn_open_szFile      [MAX_PATH];
char _ofn_open_szFileTitle [MAX_PATH];  
char _ofn_open_szFilter    [4096    ] = "json File(*.json\0*.json\0All Files(*.*)\0*.*\0";
char _ofn_open_szDefExt    [MAX_PATH] = ".json";
char _ofn_open_szInitialDir[MAX_PATH] = "D:\\test";
char _ofn_open_szTitle     [MAX_PATH] = "File Open";

char _ofn_save_szFile      [MAX_PATH];  
char _ofn_save_szFileTitle [MAX_PATH];  
char _ofn_save_szFilter    [4096    ] = "json File(*.json\0*.json\0All Files(*.*)\0*.*\0";
char _ofn_save_szDefExt    [MAX_PATH] = ".json";
char _ofn_save_szInitialDir[MAX_PATH] = "D:\\test";
char _ofn_save_szTitle     [MAX_PATH] = "File Save";



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::string get_system_my_document_folder_path (void)
{
	TCHAR szPath[MAX_PATH];


	ZeroMemory(szPath, sizeof(szPath));

	SHGetSpecialFolderPath(NULL, szPath, CSIDL_PERSONAL, FALSE);


	std::string s;


	s = szPath;

	return s;
}

//===========================================================================
static cx::uint_t get_common_dialog_extended_error(void)
{
	DWORD error;


	error = CommDlgExtendedError();
    switch(error)
	{
    case CDERR_DIALOGFAILURE:   CX_DEBUG_TRACEF(CX_TWA_NORMAL, "ERR: CDERR_DIALOGFAILURE");   break;
    case CDERR_FINDRESFAILURE:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_FINDRESFAILURE");       break;
    case CDERR_INITIALIZATION:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_INITIALIZATION");       break;
    case CDERR_LOADRESFAILURE:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_LOADRESFAILURE");       break;
    case CDERR_LOADSTRFAILURE:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_LOADSTRFAILURE");       break;
    case CDERR_LOCKRESFAILURE:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_LOCKRESFAILURE");       break;
    case CDERR_MEMALLOCFAILURE: CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_MEMALLOCFAILURE");      break;
    case CDERR_MEMLOCKFAILURE:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_MEMLOCKFAILURE");       break;
    case CDERR_NOHINSTANCE:     CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_NOHINSTANCE");          break;
    case CDERR_NOHOOK:          CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_NOHOOK");               break;
    case CDERR_NOTEMPLATE:      CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_NOTEMPLATE");           break;
    case CDERR_STRUCTSIZE:      CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CDERR_STRUCTSIZE");           break;
    case FNERR_BUFFERTOOSMALL:  CX_DEBUG_TRACEF(CX_TWA_NORMAL, "FNERR_BUFFERTOOSMALL");       break;
    case FNERR_INVALIDFILENAME: CX_DEBUG_TRACEF(CX_TWA_NORMAL, "FNERR_INVALIDFILENAME");      break;
    case FNERR_SUBCLASSFAILURE: CX_DEBUG_TRACEF(CX_TWA_NORMAL, "FNERR_SUBCLASSFAILURE");      break;
	default:
		break;
    }

	return error;
}



//===========================================================================
//typedef UINT_PTR (CALLBACK *LPOFNHOOKPROC) (HWND, UINT, WPARAM, LPARAM);


//===========================================================================
// http://www.equestionanswers.com/vcpp/file-open-dialog.php
/*
	-------------------------------------------------------------------------
	IDD_DIALOGBAR DIALOGEX 0, 0, 269, 26
	STYLE WS_CHILD
	FONT 8, "MS Sans Serif"
	BEGIN
		LTEXT           "Customized File open",IDC_STATIC_HINT,7,7,222,12,0, WS_EX_STATICEDGE
		PUSHBUTTON      "Play",IDC_PLAYPREVIEW,231,7,31,12
	END

	-------------------------------------------------------------------------
	ofn.lpTemplateName = MAKEINTRESOURCE(IDD_DIALOGBAR);
	ofn.Flags |= OFN_ENABLETEMPLATE;
*/

UINT_PTR CALLBACK ofn_hook_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//	char buffer[2000];

	int i;
//	int idCtrl;

	NMHDR*    pnmh;
	OFNOTIFY* pnot;

	ITEMIDLIST ItemIdlList[4096];


	switch (uMsg)
	{
/*
	case WM_INITDIALOG:
		{
		}
		return TRUE;

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hWnd, LOWORD(wParam));
				return TRUE;
			}
		}
		break;
*/
	/*
	CDM_GETFILEPATH	    Retrieves the path and file name of the selected file.
	CDM_GETFOLDERIDLIST	Retrieves the item identifier list corresponding to the current folder that the dialog box has open. 
						For more information about item identifier lists, see Introduction to the Shell Namespace.
	CDM_GETFOLDERPATH	Retrieves the path of the current folder or directory for the dialog box.
	CDM_GETSPEC	        Retrieves the file name (not including the path) of the file currently selected in the dialog box.
	CDM_HIDECONTROL     Hides the specified control.
	CDM_SETCONTROLTEXT	Sets the text in the specified control.
	CDM_SETDEFEXT	    Sets the default file name extension for the dialog box.
	*/

	case WM_NOTIFY:
		{
			pnot = (OFNOTIFY*)lParam;
			pnmh = &pnot->hdr;
			
			switch(pnmh->code)
			{
			/* Init open dialog */
			case CDN_INITDONE:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_INITDONE:%d", pnmh->code);
				memset (&ItemIdlList, 0, sizeof(ItemIdlList));
				i = CommDlg_OpenSave_GetFolderIDList(hWnd, &ItemIdlList, sizeof(ItemIdlList));
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "CommDlg_OpenSave_GetFolderIDList():%d", i);
				break;

			/* File selection changed */
			case CDN_SELCHANGE:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_SELCHANGE:%d", pnmh->code);
				/*
				hTrueDlg = GetParent(hWnd);
				SendMessage(hTrueDlg, CDM_GETFILEPATH, _MAX_PATH, (LONG)szPathName);
				*/
				break;

			/* Folder selection changed */
			case CDN_FOLDERCHANGE:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_FOLDERCHANGE:%d", pnmh->code);
				/*
				hTrueDlg = GetParent(hWnd);
				SendMessage(hTrueDlg, CDM_GETFOLDERPATH, _MAX_PATH, (LONG)szPathName);
				SetDlgItemText(hWnd, IDC_STATIC_HINT, szPathName);
				*/
				/*
				i = CommDlg_OpenSave_GetFolderPath(hWnd, buffer, 2000);
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "%d->%s", i, buffer);
				*/
				break;

			case CDN_SHAREVIOLATION:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_SHAREVIOLATION:%d", pnmh->code);
				break;

			case CDN_HELP:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_HELP:%d", pnmh->code);
				break;

			/* User selected open */
			case CDN_FILEOK:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_FILEOK:%d", pnmh->code);
				/*
				i = CommDlg_OpenSave_GetFolderPath(hWnd, buffer, 2000);
				*/
				break;

			case CDN_TYPECHANGE:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_TYPECHANGE:%d", pnmh->code);
				break;

			case CDN_INCLUDEITEM:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY-CDN_TYPECHANGE:%d", pnmh->code);
				break;

			default:
				CX_DEBUG_TRACEF(CX_TWA_NORMAL, "WM_NOTIFY:%d", pnmh->code);
				break;
			}
		}
		break;

	default:
		break;
	}

	return 0;
}

//===========================================================================
std::string get_open_file_path (HWND hWnd)
{
	//-----------------------------------------------------------------------
	std::string s;


	//-----------------------------------------------------------------------
	ZeroMemory(_ofn_open_szFile      , sizeof(_ofn_open_szFile      ));
	ZeroMemory(_ofn_open_szFileTitle , sizeof(_ofn_open_szFileTitle ));
	ZeroMemory(_ofn_open_szInitialDir, sizeof(_ofn_open_szInitialDir));
	ZeroMemory(_ofn_open_szTitle     , sizeof(_ofn_open_szTitle     ));

	
	//-----------------------------------------------------------------------
	lstrcpy(_ofn_open_szInitialDir, get_system_my_document_folder_path().c_str());


	//-----------------------------------------------------------------------
	OPENFILENAMEA ofn;


	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize     = sizeof(ofn); 
	ofn.hwndOwner       = hWnd; 
	ofn.lpstrFile       = _ofn_open_szFile; 
	ofn.nMaxFile        = sizeof(_ofn_open_szFile)/ sizeof(*_ofn_open_szFile); 
	ofn.lpstrFileTitle  = _ofn_open_szFileTitle; 
	ofn.nMaxFileTitle   = sizeof(_ofn_open_szFileTitle) / sizeof(_ofn_open_szFileTitle); 
	ofn.Flags           = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_ENABLESIZING | OFN_DONTADDTORECENT | OFN_EXTENSIONDIFFERENT/*lpstrDefExt!=NULL*/ | OFN_ENABLEHOOK;
	ofn.lpstrFilter     = _ofn_open_szFilter; 
	ofn.nFilterIndex    = (ofn.lpstrFilter) ? 1 : 0;;
	ofn.lpstrDefExt     = _ofn_open_szDefExt;
	ofn.lpstrInitialDir = NULL; // _ofn_open_szInitialDir; 
	ofn.lpstrTitle      = NULL; // _ofn_open_szTitle; 
//	ofn.FlagsEx         = OFN_EX_NOPLACESBAR;
	ofn.lpfnHook        = &ofn_hook_proc;


	//-----------------------------------------------------------------------
	if (FALSE==GetOpenFileNameA(&ofn))
	{
		return s;
	}


	//-----------------------------------------------------------------------
	s = _ofn_open_szFile;

	return s;
}

std::string get_save_file_path (HWND hWnd)
{
	//-----------------------------------------------------------------------
	std::string s;


	//-----------------------------------------------------------------------
	ZeroMemory(_ofn_save_szFile      , sizeof(_ofn_save_szFile      ));
	ZeroMemory(_ofn_save_szFileTitle , sizeof(_ofn_save_szFileTitle ));
	ZeroMemory(_ofn_save_szInitialDir, sizeof(_ofn_save_szInitialDir));
	ZeroMemory(_ofn_save_szTitle     , sizeof(_ofn_save_szTitle     ));


	//-----------------------------------------------------------------------
	lstrcpy(_ofn_save_szInitialDir, get_system_my_document_folder_path().c_str());


	//-----------------------------------------------------------------------
	OPENFILENAMEA ofn;


	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize     = sizeof(ofn); 
	ofn.hwndOwner       = hWnd; 
	ofn.lpstrFile       = _ofn_save_szFile; 
	ofn.nMaxFile        = sizeof(_ofn_save_szFile) / sizeof(*_ofn_save_szFile); 
	ofn.lpstrFileTitle  = _ofn_save_szFileTitle; 
	ofn.nMaxFileTitle   = sizeof(_ofn_save_szFileTitle) / sizeof(_ofn_save_szFileTitle); 
	ofn.Flags           = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_ENABLESIZING | OFN_DONTADDTORECENT | OFN_EXTENSIONDIFFERENT/*lpstrDefExt!=NULL*/ | OFN_NOREADONLYRETURN | OFN_ENABLEHOOK;
	ofn.lpstrFilter     = _ofn_save_szFilter; 
	ofn.nFilterIndex    = (ofn.lpstrFilter) ? 1 : 0;
	ofn.lpstrDefExt     = _ofn_save_szDefExt;
	ofn.lpstrInitialDir = NULL; // _ofn_save_szInitialDir; 
	ofn.lpstrTitle      = NULL; // _ofn_save_szTitle; 
//	ofn.FlagsEx         = OFN_EX_NOPLACESBAR;
	ofn.lpfnHook        = &ofn_hook_proc;


	//-----------------------------------------------------------------------
	if (FALSE==GetSaveFileNameA(&ofn))
	{
		return s;
	}


	//-----------------------------------------------------------------------
	s = _ofn_save_szFile;

	return s;
}
