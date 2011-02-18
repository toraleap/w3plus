// stdafx.cpp : 只包括标准包含文件的源文件
// w3plus.pch 将是预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

#include <comdef.h>

CString GetAppPath();
BOOL IsLeapYear(int year);
int GetMonthDays(int year,int month);
CString ToStr(_variant_t var);

CString GetAppPath()
{
	CString strRet;
	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, szBuff, _MAX_PATH));
	strRet=szBuff;
	int pos=strRet.ReverseFind('\\');
	strRet=strRet.Left(pos);
	return strRet;
}

int GetMonthDays(int year,int month)
{
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
	   month == 10 || month == 12)
	   return 31;
	else if(month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if(month == 2)
		return (IsLeapYear(year)?29:28);

	ASSERT(FALSE);
	return -1;
}

BOOL IsLeapYear(int year)
{
	return ((((year%4==0)&&(year%100!=0))||(year%400 == 0))?TRUE:FALSE);
}

CString ToStr(_variant_t var)
{
	CString strValue;
	_variant_t var_t;
	_bstr_t bst_t;
	COleCurrency var_currency;
	COleDateTime dt;
	switch(var.vt)
	{
		case VT_EMPTY:strValue=_T("");break;
		case VT_UI1:strValue.Format ("%d",var.bVal);break;
		case VT_UI2:strValue.Format ("%d",var.uiVal);break;
		case VT_UI4:strValue.Format ("%d",var.ulVal);break;
		case VT_UINT:strValue.Format("%d",var.uintVal);break;
		case VT_I2:strValue.Format ("%d",var.iVal );break;
		case VT_I4:strValue.Format ("%d",var.lVal);break;
		case VT_R4:strValue.Format ("%f",var.fltVal);break;
		case VT_R8:strValue.Format ("%f",var.dblVal);break;
		case VT_INT:strValue.Format ("%d",var.intVal);break;
		case VT_DECIMAL:
			{
				VARIANT newvar;
				VariantInit(&newvar);
				VariantChangeType(&newvar,&var,VARIANT_NOVALUEPROP,VT_BSTR);
				return ToStr(newvar);
			}
			break;
		case VT_CY:
			var_currency=var;
			strValue=var_currency.Format(0);
			break;
		case VT_BSTR:
			var_t=var;
			bst_t=var_t;
			strValue.Format ("%s",(const char*)bst_t);
			break;
		case VT_NULL: strValue=_T(""); break;
		case VT_DATE:
			dt = COleDateTime(var.date);
			strValue.Format("%d年%d月%d日%d时%d分%d秒",dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(), dt.GetSecond());
			break;
		case VT_BOOL: strValue.Format ("%d",var.boolVal ); break;
		default:
			ASSERT(FALSE);
			strValue=_T("");
			break;
	}
	//ASSERT(!strValue.IsEmpty());
	return strValue;
}