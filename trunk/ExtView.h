#pragma once

#include "LhpHtmlView.h"

class CExtView : public CLhpHtmlView
{
	DECLARE_DYNCREATE(CExtView)
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP() // ����dispatchӳ����Ա�¶����������

public:
	CExtView();
	virtual ~CExtView();

protected:
	virtual void OnInitialUpdate();

protected:
	void BeginKeyMonitor();
	void CancelKeyMonitor();
	int GetEntrySetting(int entryIndex);
	void SetEntrySetting(int entryIndex, int value);
	BSTR GetChatMessage(int entryIndex);
	void SetChatMessage(int entryIndex, char* msg);
	BSTR GetCurrentConfigFile();
	BSTR GetConfigFiles();
	BOOL SetConfigFile(char* filename);
	BOOL DuplicateConfigFile(char* filename);
	BOOL ModifyNickname(char* nickname);
	BOOL ModifyHostname(char* hostname);
	void SwitchRunningState();
	BSTR CExtView::QueryAppVersion();
	BOOL QueryRunningState();
	BOOL QueryKeyboardHook();
	BOOL QueryMouseHook();
	BSTR QueryWar3State();
	long QueryPerformance(int entryIndex);
	void DOMReadyCallback();
};
