#include "stdafx.h"
#include "common.h"
#include "w3plus.h"
#include "ExtView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString GetAppPath();
extern unsigned int iKeyMonitor;
extern unsigned int lastSeatCount;
extern unsigned int KeyMappingTable[256];
extern char sConfigProfile[MAX_PATH];
extern CString ChatPresets[10];
extern unsigned long keyCount;
extern unsigned long keyProceedCount;
extern unsigned long allDelay;
extern unsigned long maxDelay;
extern unsigned long timerCount;
extern unsigned long allTimerDelay;
extern unsigned long maxTimerDelay;
extern BOOL bDOMReady;
extern BOOL bAllEnabled;
extern BOOL bWar3Windowed;
extern HHOOK hookKB;										// 全局键盘钩子handle
extern HHOOK hookMS;										// 全局鼠标钩子handle
extern HWND GetWar3Hwnd();
extern void ManageMouseHook();
extern void AllToggle();
extern void ModifyWar3Nickname(char*);
extern void ModifyWar3Hostname(char*);

IMPLEMENT_DYNCREATE(CExtView, CLhpHtmlView)

BEGIN_MESSAGE_MAP(CExtView, CLhpHtmlView)
	ON_COMMAND(ID_FILE_PRINT, CLhpHtmlView::OnFilePrint)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CExtView, CLhpHtmlView)
	DISP_FUNCTION(CExtView, "BeginKeyMonitor", BeginKeyMonitor, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CExtView, "CancelKeyMonitor", CancelKeyMonitor, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CExtView, "GetEntrySetting", GetEntrySetting, VT_I4, VTS_I4)
	DISP_FUNCTION(CExtView, "SetEntrySetting", SetEntrySetting, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CExtView, "GetChatMessage", GetChatMessage, VT_BSTR, VTS_I4)
	DISP_FUNCTION(CExtView, "SetChatMessage", SetChatMessage, VT_EMPTY, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CExtView, "GetCurrentConfigFile", GetCurrentConfigFile, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CExtView, "GetConfigFiles", GetConfigFiles, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CExtView, "SetConfigFile", SetConfigFile, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CExtView, "DuplicateConfigFile", DuplicateConfigFile, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CExtView, "ModifyNickname", ModifyNickname, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CExtView, "ModifyHostname", ModifyHostname, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CExtView, "SwitchRunningState", SwitchRunningState, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CExtView, "QueryAppVersion", QueryAppVersion, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CExtView, "QueryRunningState", QueryRunningState, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CExtView, "QueryKeyboardHook", QueryKeyboardHook, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CExtView, "QueryMouseHook", QueryMouseHook, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CExtView, "QueryWar3State", QueryWar3State, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CExtView, "QueryPerformance", QueryPerformance, VT_I4, VTS_I4)
	DISP_FUNCTION(CExtView, "DOMReadyCallback", DOMReadyCallback, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

CExtView::CExtView()
{
}

CExtView::~CExtView()
{
}

void CExtView::OnInitialUpdate()
{
	CLhpHtmlView::OnInitialUpdate();

    char lpszFullURL[_MAX_PATH];
	char lpszModule[_MAX_PATH];
	if (GetModuleFileName(theApp.m_hInstance, lpszModule, _MAX_PATH))
    {
		wsprintf(lpszFullURL, "res://%s/%s", lpszModule, "default.htm");
    }
	Navigate2(lpszFullURL,NULL,NULL);
}

void CExtView::BeginKeyMonitor()
{
	iKeyMonitor = 1;
}

void CExtView::CancelKeyMonitor()
{
	iKeyMonitor = 0;
}

int CExtView::GetEntrySetting(int entryIndex)
{
	return KeyMappingTable[entryIndex];
}

void CExtView::SetEntrySetting(int entryIndex, int value)
{
	KeyMappingTable[entryIndex] = value;
	switch(entryIndex)
	{
	case DISABLEKEYBOARD:
		theApp.ManageKeyboardHook();
		break;
	case DISABLEMOUSE:
		theApp.ManageMouseHook();
		break;
	}
}

BSTR CExtView::GetChatMessage(int entryIndex)
{
	return (BSTR)ChatPresets[entryIndex].AllocSysString();
}

void CExtView::SetChatMessage(int entryIndex, char* msg)
{
	ChatPresets[entryIndex].SetString(msg);
}

BSTR CExtView::GetCurrentConfigFile()
{
	CString tmpStr;
	tmpStr.SetString(sConfigProfile);
	return (BSTR)(tmpStr.AllocSysString());
}

BSTR CExtView::GetConfigFiles()
{
	char sSearchFilename[MAX_PATH];
	CString sReturnFilename;
	WIN32_FIND_DATA fd;
	HANDLE hFile;
	sSearchFilename[GetModuleFileName(NULL, sSearchFilename, MAX_PATH) - 3] = '\0';
	wsprintf(sSearchFilename, "%s%s", sSearchFilename, "*.ini");
	hFile = ::FindFirstFile(sSearchFilename, &fd);
	sReturnFilename.SetString(strstr(fd.cFileName, ".") + 1);
	sReturnFilename.Truncate(sReturnFilename.GetLength() - 4);
	while(::FindNextFile(hFile, &fd)) 
	{
		sReturnFilename.Append("|");
		sReturnFilename.Append(strstr(fd.cFileName, ".") + 1);
		sReturnFilename.Truncate(sReturnFilename.GetLength() - 4);
	} 
	return (BSTR)(sReturnFilename.AllocSysString());
}

BOOL CExtView::SetConfigFile(char* filename)
{
	char sConfigFilename[MAX_PATH];
	theApp.SaveSettings();
	sConfigFilename[GetModuleFileName(NULL, sConfigFilename, MAX_PATH) - 3] = '\0';
	wsprintf(sConfigFilename, "%s%s%s", sConfigFilename, sConfigProfile, ".ini");
	if (GetFileAttributes(sConfigFilename) != 0xFFFFFFFF)
	{
		strcpy_s(sConfigProfile, MAX_PATH, filename);
		theApp.LoadSettings();
		theApp.ManageKeyboardHook();
		theApp.ManageMouseHook();
		return true;
	}
	else
	{
		::MessageBox(NULL, "指定的配置文件不存在！", "w3plus", MB_ICONERROR);
		return false;
	}
}

BOOL CExtView::DuplicateConfigFile(char* filename)
{
	theApp.SaveSettings();
	strcpy_s(sConfigProfile, MAX_PATH, filename);
	theApp.SaveSettings();
	return true;
}

BOOL CExtView::ModifyNickname(char* nickname)
{
	ModifyWar3Nickname(nickname);
	return true;
}

BOOL CExtView::ModifyHostname(char* hostname)
{
	ModifyWar3Hostname(hostname);
	return true;
}

void CExtView::SwitchRunningState()
{
	AllToggle();
}

BSTR CExtView::QueryAppVersion()
{
	CString tmpStr;
	tmpStr.SetString(APP_STRING);
	return (BSTR)(tmpStr.AllocSysString());
}

BOOL CExtView::QueryRunningState()
{
	return bAllEnabled;
}

BOOL CExtView::QueryKeyboardHook()
{
	return hookKB!=0;
}

BOOL CExtView::QueryMouseHook()
{
	return hookMS!=0;
}

BSTR CExtView::QueryWar3State()
{
	CString tmpStr;
	tmpStr.Append(GetWar3Hwnd()?(KeyMappingTable[ENABLEWINDOWFUNC]?(bWar3Windowed?"运行中 - 窗口模式":"运行中 - 全屏模式"):"运行中"):"未检测到 Warcraft III 窗口");
	return (BSTR)(tmpStr.AllocSysString());
}

long CExtView::QueryPerformance(int entryIndex)
{
	switch(entryIndex)
	{
	case 0:
		return keyCount;
	case 1:
		return keyProceedCount;
	case 2:
		return keyCount==0?0:allDelay/keyCount;
	case 3:
		return maxDelay;
	case 4:
		return timerCount;
	case 5:
		return timerCount==0?0:allTimerDelay/timerCount;
	case 6:
		return maxTimerDelay;
	}
	return -1;
}

void CExtView::DOMReadyCallback()
{
	bDOMReady = TRUE;
}


/*主机名 026E5268*/