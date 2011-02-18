#include "stdafx.h"
#include "common.h"
#include "w3plus.h"
#include "w3plusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHELLICON WM_USER + 1

extern unsigned int KeyMappingTable[256];
extern BOOL bNotifyIconExists;
extern BOOL bAllEnabled;
extern void AllToggle();

Cw3plusDlg::Cw3plusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cw3plusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ENABLED);
}

BEGIN_MESSAGE_MAP(Cw3plusDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHELLICON, OnTrayNotification)
	ON_COMMAND(ID_SHOW, OnMenuShow)
	ON_COMMAND(ID_PAUSE, OnMenuPause)
	ON_COMMAND(ID_EXIT, OnMenuExit)
END_MESSAGE_MAP()

BOOL Cw3plusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowTextA(APP_STRING);
	m_hIcon = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_ENABLED));
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// 创建NotifyIcon
	if (KeyMappingTable[ENABLENOTIFYICON])
	{
		idata.cbSize = sizeof(NOTIFYICONDATA);
		idata.hIcon = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(IDI_ENABLED));
		idata.hWnd = this->m_hWnd;
		strcpy_s(idata.szTip, 128, "w3plus(已启动) 双击显示主界面");
		strcpy_s(idata.szInfoTitle, 64, APP_STRING);
		strcpy_s(idata.szInfo, 256, "w3plus 已经启动并处于待命状态。\n若您最小化了主窗口，双击这里可以再次显示。");
		idata.uTimeout = 3000;
		idata.uCallbackMessage = WM_SHELLICON;
		idata.uFlags = NIF_MESSAGE|NIF_ICON|NIF_INFO|NIF_TIP;
		idata.dwInfoFlags = NIIF_INFO;
		idata.uID = 0;
		Shell_NotifyIcon(NIM_ADD,&idata);
		bNotifyIconExists = TRUE;
	}

	// 创建浏览器
	m_Browser.CreateFromStatic(IDC_BROWSER, this);

	SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
	return TRUE;
}

//BOOL Cw3plusDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
//{
//	if (nID == ID_SHOW)
//	{
//		ShowWindow(SW_NORMAL);
//		SetForegroundWindow();
//	} else if (nID == ID_PAUSE)
//	{
//	} else if (nID == ID_EXIT)
//		SendMessage(WM_CLOSE, pSubMenu->GetMenuItemID(3), 0);
//	{
//
//	if (CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo)) return TRUE;
//}

void Cw3plusDlg::OnMenuShow() 
{
	if (IsWindowVisible())
	{
		ShowWindow(SW_HIDE);
	} else
	{
		ShowWindow(SW_NORMAL);	
		SetForegroundWindow();
	}
}

void Cw3plusDlg::OnMenuPause() 
{
	AllToggle();
}

void Cw3plusDlg::OnMenuExit() 
{
	OnSysCommand(SC_CLOSE, 0);
}

void Cw3plusDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{ 
	if (nID == SC_MINIMIZE) 
	{
		if (bNotifyIconExists)
		{
			ShowWindow(SW_HIDE); 
		}
		else
		{
			CDialog::OnSysCommand(nID, lParam); 
		}
		SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
		return;
	}
	if (nID == SC_CLOSE) 
	{
		if (KeyMappingTable[CONFIRMONQUIT] && MessageBox("你确认要退出w3plus吗?", "退出确认", MB_ICONQUESTION | MB_YESNO) == IDNO) return;
		else
		{
			if (bNotifyIconExists) Shell_NotifyIcon(NIM_DELETE,&idata);
			CDialog::OnOK();
		}
	}
	CDialog::OnSysCommand(nID, lParam); 
} 

LRESULT Cw3plusDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)   
{   
	if (LOWORD(lParam) == WM_LBUTTONDBLCLK)     
	{
		SendMessage(WM_COMMAND, ID_SHOW, 0);
	} else if (LOWORD(lParam) == WM_RBUTTONUP)
	{
		CPoint   pos;   
		GetCursorPos(&pos);   
		::SetForegroundWindow(this->m_hWnd);       
		CMenu m_PopupMenu;                                
		m_PopupMenu.LoadMenu(IDR_POPMENU);
		::SetMenuDefaultItem(m_PopupMenu.m_hMenu, 0, TRUE); 
		m_PopupMenu.CheckMenuItem(ID_PAUSE, !bAllEnabled);
		m_PopupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pos.x,pos.y,this); 
		m_PopupMenu.Detach();
	}
	return FALSE;
}

void Cw3plusDlg::OnCancel()   
{   
}     


void Cw3plusDlg::OnOK()   
{   
}     