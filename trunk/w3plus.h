// w3plus.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号

#define APP_STRING "w3plus 1.13 Build 100228"
#define APPVER 0x1007

#define WM_KBHOOK WM_USER + 0x20
#define WM_MSHOOK WM_USER + 0x21

// Cw3plusApp:
// 有关此类的实现，请参阅 w3plus.cpp
//

class Cw3plusApp : public CWinApp
{
public:
	Cw3plusApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现
	void ManageKeyboardHook();
	void ManageMouseHook();
	void ElevatePrivileges();
	void ProcessCommandLine();
	void UpdateSettings();
	void LoadSettings();
	void SaveSettings();

};

void WINAPI HookThread();
extern Cw3plusApp theApp;
extern DWORD idht;
