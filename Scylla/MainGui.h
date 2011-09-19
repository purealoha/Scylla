#pragma once

#include <windows.h>
#include "resource.h"

// WTL
#include <atlbase.h>       // base ATL classes
#include <atlapp.h>        // base WTL classes
#include <atlwin.h>        // ATL GUI classes
#include <atlmisc.h>       // WTL utility classes like CString
#include <atlcrack.h>      // WTL enhanced msg map macros
#include <atlctrls.h>      // WTL controls

//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

#include <cstdio>

#include "Logger.h"
#include "ProcessLister.h"
#include "IATSearch.h"
#include "PickDllGui.h"
#include "ImportsHandling.h"

class MainGui : public CDialogImpl<MainGui>
{
public:
	enum { IDD = IDD_DLG_MAIN };

	BEGIN_MSG_MAP(MainGui)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_GETMINMAXINFO(OnGetMinMaxInfo)
		MSG_WM_SIZING(OnSizing)
		MSG_WM_CONTEXTMENU(OnContextMenu)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_COMMAND(OnCommand)

		//MSG_WM_ENTERSIZEMOVE(OnEnterSizeMove)
		//MSG_WM_EXITSIZEMOVE(OnExitSizeMove)

		NOTIFY_HANDLER_EX(IDC_TREE_IMPORTS, NM_CLICK, OnTreeImportsClick)
		NOTIFY_HANDLER_EX(IDC_TREE_IMPORTS, NM_DBLCLK, OnTreeImportsDoubleClick)
		NOTIFY_HANDLER_EX(IDC_TREE_IMPORTS, NM_RCLICK, OnTreeImportsRightClick)
		NOTIFY_HANDLER_EX(IDC_TREE_IMPORTS, NM_RDBLCLK, OnTreeImportsRightDoubleClick)

		COMMAND_HANDLER_EX(IDC_CBO_PROCESSLIST, CBN_DROPDOWN, OnProcessListDrop)
		COMMAND_HANDLER_EX(IDC_CBO_PROCESSLIST, CBN_SELENDOK, OnProcessListSelected)

		COMMAND_ID_HANDLER_EX(IDC_BTN_PICKDLL, OnPickDLL)
		COMMAND_ID_HANDLER_EX(IDC_BTN_OPTIONS, OnOptions)
		COMMAND_ID_HANDLER_EX(IDC_BTN_DUMP, OnDump)
		COMMAND_ID_HANDLER_EX(IDC_BTN_FIXDUMP, OnFixDump)
		COMMAND_ID_HANDLER_EX(IDC_BTN_PEREBUILD, OnPERebuild)
		COMMAND_ID_HANDLER_EX(IDC_BTN_DLLINJECT, OnDLLInject)
		COMMAND_ID_HANDLER_EX(IDC_BTN_IATAUTOSEARCH, OnIATAutoSearch)
		COMMAND_ID_HANDLER_EX(IDC_BTN_GETIMPORTS, OnGetImports)
		COMMAND_ID_HANDLER_EX(IDC_BTN_INVALIDIMPORTS, OnInvalidImports)
		COMMAND_ID_HANDLER_EX(IDC_BTN_SUSPECTIMPORTS, OnSuspectImports)
		COMMAND_ID_HANDLER_EX(IDC_BTN_CLEARIMPORTS, OnClearImports)

		COMMAND_ID_HANDLER_EX(ID_FILE_DUMP, OnDump)
		COMMAND_ID_HANDLER_EX(ID_FILE_PEREBUILD, OnPERebuild)
		COMMAND_ID_HANDLER_EX(ID_FILE_FIXDUMP, OnFixDump)
		COMMAND_ID_HANDLER_EX(ID_FILE_EXIT, OnExit)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_SHOWINVALID, OnInvalidImports)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_SHOWSUSPECT, OnSuspectImports)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_INVALIDATESELECTED, OnInvalidateSelected)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_CUTSELECTED, OnCutSelected)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_CLEARIMPORTS, OnClearImports)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_SAVETREE, OnSaveTree)
		COMMAND_ID_HANDLER_EX(ID_IMPORTS_LOADTREE, OnLoadTree)
		COMMAND_ID_HANDLER_EX(ID_TRACE_AUTOTRACE, OnAutotrace)
		COMMAND_ID_HANDLER_EX(ID_MISC_DLLINJECTION, OnDLLInject)
		COMMAND_ID_HANDLER_EX(ID_MISC_OPTIONS, OnOptions)
		COMMAND_ID_HANDLER_EX(ID_HELP_ABOUT, OnAbout)

		COMMAND_ID_HANDLER_EX(IDCANCEL, OnExit)
	END_MSG_MAP()

	MainGui();

	//Output Window
	void addTextToOutputLog(const WCHAR * text);

protected:

	// Variables

	ProcessLister processLister;
	WCHAR stringBuffer[600];

	ImportsHandling importsHandling;
	ProcessAccessHelp processAccessHelp;
	ApiReader apiReader;

	Process * selectedProcess;

	// File selection stuff

	static const WCHAR filterExe[];
	static const WCHAR filterDll[];
	static const WCHAR filterExeDll[];
	static const WCHAR filterTxt[];

	// Controls

	CTreeViewCtrl TreeImports;
	CComboBox ComboProcessList;
	CEdit EditOEPAddress;
	CEdit EditIATAddress;
	CEdit EditIATSize;
	CListBox ListLog;

	RECT MinSize;

	// Handles

	CIcon hIcon;
	CMenu hMenuImports;
	CMenu hMenuLog;

	static const int MenuImportsOffsetTrace = 2;
	static const int MenuImportsTraceOffsetScylla = 2;
	static const int MenuImportsTraceOffsetImpRec = 4;

protected:

	// Message handlers

	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
	void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void OnSizing(UINT fwSide, RECT* pRect);
	//void OnEnterSizeMove();
	//void OnExitSizeMove();
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnContextMenu(CWindow wnd, CPoint point);
	void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl);

	LRESULT OnTreeImportsClick(const NMHDR* pnmh);
	LRESULT OnTreeImportsDoubleClick(const NMHDR* pnmh);
	LRESULT OnTreeImportsRightClick(const NMHDR* pnmh);
	LRESULT OnTreeImportsRightDoubleClick(const NMHDR* pnmh);

	void OnProcessListDrop(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnProcessListSelected(UINT uNotifyCode, int nID, CWindow wndCtl);

	void OnPickDLL(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnOptions(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnDump(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnFixDump(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnPERebuild(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnDLLInject(UINT uNotifyCode, int nID, CWindow wndCtl);

	void OnIATAutoSearch(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnGetImports(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnInvalidImports(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnSuspectImports(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnClearImports(UINT uNotifyCode, int nID, CWindow wndCtl);

	void OnInvalidateSelected(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnCutSelected(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnSaveTree(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnLoadTree(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnAutotrace(UINT uNotifyCode, int nID, CWindow wndCtl);

	void OnExit(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnAbout(UINT uNotifyCode, int nID, CWindow wndCtl);

	// GUI functions

	bool showFileDialog(WCHAR * selectedFile, bool save, const WCHAR * defFileName, const WCHAR * filter, const WCHAR * defExtension);

	void setIconAndDialogCaption();

	void fillProcessListComboBox(CComboBox& hCombo);

	//static bool displayModuleList(HWND hWndDlg, HWND hList, LRESULT index);

	// Actions

	void pickDllActionHandler();
	void processSelectedActionHandler(int index);
	void showInvalidImportsActionHandler();
	void showSuspectImportsActionHandler();
	void iatAutosearchActionHandler();
	void getImportsActionHandler();
	void appendPluginListToMenu(CMenuHandle hMenuTrackPopup);
	void dumpActionHandler();
	DWORD_PTR getOEPFromGui();
	void peRebuildActionHandler();
	void startDisassemblerGui(CTreeItem selectedTreeNode);
	void dumpFixActionHandler();
	void enableDialogControls(BOOL value);
	void showAboutDialog();
	void dllInjectActionHandler();
	void optionsActionHandler();
	void clearImportsActionHandler();
	void pluginActionHandler(int menuItem);

	// Popup menu functions

	//void DisplayContextMenu(CWindow, CPoint);
	void SetupImportsMenuItems(bool isItem, bool isThunk);
	void DisplayContextMenuImports(CWindow, CPoint);
	void DisplayContextMenuLog(CWindow, CPoint);

	// Misc

	void clearOutputLog();//Output Window
	bool saveLogToFile(const WCHAR * file);

	static DWORD_PTR stringToDwordPtr(const WCHAR * hexString);
};
