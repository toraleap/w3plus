#include "stdafx.h"
#include "LhpHtmlView.h"
#include ".\lhphtmlview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CLhpHtmlView, CHtmlView)

BEGIN_DISPATCH_MAP(CLhpHtmlView, CHtmlView)
END_DISPATCH_MAP()

BEGIN_MESSAGE_MAP(CLhpHtmlView, CHtmlView)
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

CLhpHtmlView::CLhpHtmlView(BOOL isview)
{
	m_ContextMenuMode=DefaultMenu;
	m_DefaultMsgBoxTitle="w3plus";
	m_HostInfoFlag = DOCHOSTUIFLAG_THEME | DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_SCROLL_NO;
	m_IsView = isview;
	m_spDoc = NULL;

	EnableAutomation();
}

CLhpHtmlView::~CLhpHtmlView()
{

}

BOOL CLhpHtmlView::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CWnd* pStatic = pParent->GetDlgItem(nID);
	if(pStatic == NULL )
		return FALSE;

	CRect rc;
	pStatic->GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	pStatic->DestroyWindow();

	if(!CHtmlView::Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), rc, pParent, nID, NULL))
		return FALSE;
	this->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);//去HtmlView的3D边框
	m_IsView = FALSE;

	OnInitialUpdate();

	return TRUE;
}

void CLhpHtmlView::SetHostInfoFlag(DWORD dwFlag)
{
	m_HostInfoFlag = dwFlag;
}

BOOL CLhpHtmlView::CreateControlSite(COleControlContainer * pContainer, COleControlSite ** ppSite, UINT /*nID*/, REFCLSID /*clsid*/)
{
	*ppSite = new CDocHostSite(pContainer, this);// 创建自己的控制站点实例

	return (*ppSite) ? TRUE : FALSE;
}

HRESULT CLhpHtmlView::OnGetHostInfo(DOCHOSTUIINFO * pInfo)
{
	pInfo->cbSize = sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags = m_HostInfoFlag;
	pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

	return S_OK;
}

HRESULT CLhpHtmlView::OnShowContextMenu(DWORD dwID, LPPOINT ppt,LPUNKNOWN pcmdtReserved, LPDISPATCH pdispReserved)
{
	return S_OK;
}

HRESULT CLhpHtmlView::OnGetExternal(LPDISPATCH *lppDispatch)
{
	*lppDispatch = GetIDispatch(TRUE);
	return S_OK;
}

BOOL CLhpHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// 消除窗口闪烁
	cs.style |= WS_CLIPSIBLINGS;
	if(m_IsView)
		cs.dwExStyle |= WS_EX_CLIENTEDGE;

	return CWnd::PreCreateWindow(cs);
}

BOOL CLhpHtmlView::Create(CRect rect, CWnd* pParent, UINT nID)
{
	if(!CHtmlView::Create(NULL, NULL, (WS_CHILD | WS_VISIBLE ), rect, pParent, nID, NULL))
		return FALSE;

	m_IsView = FALSE;

	return TRUE;
}

int CLhpHtmlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHtmlView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CLhpHtmlView::OnDestroy()
{
	if(m_IsView)
        CHtmlView::OnDestroy();
	else
	{
		if (m_pBrowserApp)
		{
			m_pBrowserApp.Release();
			m_pBrowserApp = NULL;
		}
		CWnd::OnDestroy();
	}
}

int CLhpHtmlView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	if(m_IsView)
		return CHtmlView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	else
		return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}



void CLhpHtmlView::PostNcDestroy()
{
	if(m_IsView)
		CHtmlView::PostNcDestroy();
}

void CLhpHtmlView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndBrowser.m_hWnd)) 
	{ 
		CRect rect; 
		GetClientRect(rect); 
		::AdjustWindowRectEx(rect, GetStyle(), FALSE, WS_EX_CLIENTEDGE); 
		m_wndBrowser.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER); 
	} 
}

const CString CLhpHtmlView::GetSystemErrorMessage(DWORD dwError)
{
	CString strError;
	LPTSTR lpBuffer;

	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,  dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
			(LPTSTR) &lpBuffer, 0, NULL))

	{
		strError = "FormatMessage Netive Error" ;
	}
	else
	{
		strError = lpBuffer;
		LocalFree(lpBuffer);
	}
	return strError;
}

CString CLhpHtmlView::GetNextToken(CString& strSrc, const CString strDelim,BOOL bTrim, BOOL bFindOneOf)
{
	CString strToken;
	int idx = bFindOneOf? strSrc.FindOneOf(strDelim) : strSrc.Find(strDelim);
	if(idx != -1)
	{
		strToken  = strSrc.Left(idx);
		strSrc = strSrc.Right(strSrc.GetLength() - (idx + 1) );
	}
	else
	{
		strToken = strSrc;
		strSrc.Empty();
	}
	if(bTrim)
	{
		strToken.TrimLeft();
		strToken.TrimRight();
	}
	return strToken;
}

BOOL CLhpHtmlView::JScriptOK()
{
	return (m_spDoc != NULL); 
}

BOOL CLhpHtmlView::GetJScript(CComPtr<IDispatch>& spDisp)
{
	if( m_spDoc==NULL )
		return FALSE;

	HRESULT hr = m_spDoc->get_Script(&spDisp);
	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

BOOL CLhpHtmlView::GetJScripts(CComPtr<IHTMLElementCollection>& spColl)
{
	if( m_spDoc==NULL )
		return FALSE;

	HRESULT hr = m_spDoc->get_scripts(&spColl);
	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

BOOL CLhpHtmlView::CallJScript(const CString strFunc,_variant_t* pVarResult)
{
	CStringArray paramArray;
	return CallJScript(strFunc,paramArray,pVarResult);
}

BOOL CLhpHtmlView::CallJScript(const CString strFunc,const CString strArg1,_variant_t* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	return CallJScript(strFunc,paramArray,pVarResult);
}

BOOL CLhpHtmlView::CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,_variant_t* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	return CallJScript(strFunc,paramArray,pVarResult);
}

BOOL CLhpHtmlView::CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,const CString strArg3,_variant_t* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	paramArray.Add(strArg3);
	return CallJScript(strFunc,paramArray,pVarResult);
}

BOOL CLhpHtmlView::CallJScript(const CString strFunc, const CStringArray& paramArray,_variant_t* pVarResult)
{
	CComPtr<IDispatch> spScript;
	if(!GetJScript(spScript))
	{
		MessageBox("函数GetJScrip调用失败！");
		return FALSE;
	}
	CComBSTR bstrFunc(strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrFunc,1,
											LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		MessageBox(GetSystemErrorMessage(hr));
		return FALSE;
	}

	INT_PTR arraySize = paramArray.GetSize();

	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = (UINT)arraySize;
	dispparams.rgvarg = new VARIANT[dispparams.cArgs];
	
	for( int i = 0; i < arraySize; i++)
	{
		CComBSTR bstr = paramArray.GetAt(arraySize - 1 - i); // back reading
		bstr.CopyTo(&dispparams.rgvarg[i].bstrVal);
		dispparams.rgvarg[i].vt = VT_BSTR;
	}
	dispparams.cNamedArgs = 0;

	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
   	_variant_t vaResult;
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg
         
	hr = spScript->Invoke(dispid,IID_NULL,0,
							DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);

	delete [] dispparams.rgvarg;
	if(FAILED(hr))
	{
		MessageBox(GetSystemErrorMessage(hr));
		return FALSE;
	}
	
	if(pVarResult)
	{
		*pVarResult = vaResult;
	}
	return TRUE;
}

CString CLhpHtmlView::ScanJScript(CString& strAText, CStringArray& args)
{
	args.RemoveAll();
	CString strDelim(" \n\r\t"),strSrc(strAText);
	BOOL bFound = FALSE;
	while(!strSrc.IsEmpty())
	{
		CString strStart = GetNextToken(strSrc,strDelim);
		if(strStart == "function")
		{
			bFound = TRUE;
			break;
		}
		if(strStart == "/*")
		{
			// Skip comments
			while(!strSrc.IsEmpty())
			{
				CString strStop = GetNextToken(strSrc,strDelim);
				if(strStop == "*/")
				{
					break;
				}
			}
		}
	}

	if(!bFound)
		return "";
	
	CString strFunc = GetNextToken(strSrc,"(",TRUE);
	CString strArgs = GetNextToken(strSrc,")",TRUE);

	// Parse arguments
	CString strArg;
	while(!(strArg = GetNextToken(strArgs,",")).IsEmpty())
		args.Add(strArg);

	strAText= strSrc;
	return strFunc;
}

BOOL CLhpHtmlView::SetScriptDocument()
{
	LPDISPATCH pDisp = GetHtmlDocument();
	if(pDisp==NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	m_spDoc = NULL;

	CComPtr<IDispatch> spDisp = pDisp;

	HRESULT hr = spDisp->QueryInterface(IID_IHTMLDocument2,(void**)&m_spDoc);
	if(FAILED(hr))
	{
		MessageBox("Failed to get HTML document COM object");
		return FALSE;
	}
	return TRUE;
}

void CLhpHtmlView::OnDocumentComplete(LPCTSTR lpszURL)
{
	CHtmlView::OnDocumentComplete(lpszURL);
	SetScriptDocument();
}
