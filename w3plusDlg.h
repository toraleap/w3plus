#pragma once

#include "ExtView.h"

class Cw3plusDlg : public CDialog
{
public:
	Cw3plusDlg(CWnd* pParent = NULL);
	CExtView m_Browser;
	NOTIFYICONDATA idata;
	enum { IDD = IDD_w3plus_DIALOG };

protected:
	HICON m_hIcon;

protected:
	virtual BOOL OnInitDialog();
	void OnCancel();
	void OnOK();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuShow();
	afx_msg void OnMenuPause();
	afx_msg void OnMenuExit();
};
