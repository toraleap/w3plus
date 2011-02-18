#pragma once

#include <afxhtml.h>
#include <comdef.h>

#include "DocHostSite.h"

class CLhpHtmlView : public CHtmlView
{
	DECLARE_DYNCREATE(CLhpHtmlView)
	DECLARE_DISPATCH_MAP()
	DECLARE_MESSAGE_MAP()

public:
	CLhpHtmlView(BOOL isview = TRUE);
	virtual ~CLhpHtmlView();

public:
	enum CONTEXT_MENU_MODE		// 上下文菜单
	{
		NoContextMenu,			// 无菜单
		DefaultMenu,			// 默认菜单
		TextSelectionOnly,		// 仅文本选择菜单
		CustomMenu				// 自定义菜单
	};

protected:
	CONTEXT_MENU_MODE m_ContextMenuMode;			// 上下文菜单模式
	CString m_DefaultMsgBoxTitle;					// 默认MessageBox标题
	DWORD	m_HostInfoFlag;							// 浏览器的一些设置如是否有滚动条等
	BOOL	m_IsView;								// 是否是视图

	CComPtr<IHTMLDocument2>	m_spDoc;

public:
	// 更改浏览器的一些设置如是否有滚动条等
	void SetHostInfoFlag(DWORD dwFlag);

public:
	// 当在一个窗体上创建时（当作窗体的一个控件）可以指定一个控件ID按指定的控件大小位置
	BOOL CreateFromStatic(UINT nID, CWnd* pParent);
	BOOL Create(CRect rect, CWnd* pParent, UINT nID);

public:
	virtual BOOL CreateControlSite(COleControlContainer* pContainer,COleControlSite** ppSite, UINT nID, REFCLSID clsid);
	// 定制宿主信息
	virtual HRESULT OnGetHostInfo(DOCHOSTUIINFO * pInfo);
	// 上下文菜单
	virtual HRESULT OnShowContextMenu(DWORD dwID, LPPOINT ppt,LPUNKNOWN pcmdtReserved, LPDISPATCH pdispReserved);
	// 设置脚本扩展
	virtual HRESULT OnGetExternal(LPDISPATCH *lppDispatch);

protected:
	const CString GetSystemErrorMessage(DWORD dwError);
	CString GetNextToken(CString& strSrc, const CString strDelim,BOOL bTrim = FALSE, BOOL bFindOneOf = TRUE);
	BOOL SetScriptDocument();
	const CString GetLastError() const;
	BOOL GetJScript(CComPtr<IDispatch>& spDisp);
	BOOL GetJScripts(CComPtr<IHTMLElementCollection>& spColl);
	CString ScanJScript(CString& strAText, CStringArray& args);

public:
	BOOL JScriptOK();

public:
	BOOL CallJScript(const CString strFunc,_variant_t* pVarResult = NULL);
	BOOL CallJScript(const CString strFunc,const CString strArg1,_variant_t* pVarResult = NULL);
	BOOL CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,_variant_t* pVarResult = NULL);
	BOOL CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,const CString strArg3,_variant_t* pVarResult = NULL);
	BOOL CallJScript(const CString strFunc,const CStringArray& paramArray,_variant_t* pVarResult = NULL);

protected:
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);

public:
	afx_msg void OnDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


