// w3plus.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������

#define APP_STRING "w3plus 1.13 Build 100228"
#define APPVER 0x1007

#define WM_KBHOOK WM_USER + 0x20
#define WM_MSHOOK WM_USER + 0x21

// Cw3plusApp:
// �йش����ʵ�֣������ w3plus.cpp
//

class Cw3plusApp : public CWinApp
{
public:
	Cw3plusApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��
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
