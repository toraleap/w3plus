// w3plus.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "common.h"
#include "w3plus.h"
#include "w3plusDlg.h"

char* ConfigFileString[] = {"DisableKeyboard", "DisableMouse", "EnableNotifyIcon", "ConfirmOnQuit", "IgnoreContinousWheel", "DiscardWinKey",
	"ShowLifeBar", "ShowEnemyLifeBar", "ShowAllyLifeBar", "EnableWindowFunc", "SkipWindowModeDetect", "EnableClipCursor", "EnableLockRatio", "EnableAuxFunc", "EnableInputCheck", "EnableInputCheck122", "EnableInputCheck123", "EnableInputCheck124", "EnableRestrict", "RestrictMiniMapRClick", "RestrictMiniMapButtons",
	"KeyAllToggle", "KeyAuxTempDisable",
	"EnableItemFunction", "KeyItem7", "KeyItem8", "KeyItem4", "KeyItem5", "KeyItem1", "KeyItem2",
	"EnableMouseFunction", "KeySelPortrait", "KeyContinuousClick", "KeyAutocastToggle",
	"KeyMouseSkill1", "KeyMouseSkill2", "KeyMouseSkill3", "KeyMouseSkill4", "KeyMouseSkill5", "KeyMouseSkill6", "KeyMouseSkill7",
	"ReplayPause", "ReplaySpeedup", "ReplaySlowdown", "ReplayReload", 
	"EnableKaelFunction", "KaelDotA6.54Later", "EnableKaelDblpressCast", "KeyKael0", "KeyKael1", "KeyKael2", "KeyKael3", "KeyKael4", "KeyKael5", "KeyKael6", "KeyKael7", "KeyKael8", "KeyKael9",
	"EnableChatFunction", "KeyChat0", "KeyChat1", "KeyChat2", "KeyChat3", "KeyChat4", "KeyChat5", "KeyChat6", "KeyChat7", "KeyChat8", "KeyChat9",
	"ChatTarget0", "ChatTarget1", "ChatTarget2", "ChatTarget3", "ChatTarget4", "ChatTarget5", "ChatTarget6", "ChatTarget7", "ChatTarget8", "ChatTarget9"};

char* ConfigFileGroup[] = {"SYSTEM", "SYSTEM", "SYSTEM", "SYSTEM", "SYSTEM", "SYSTEM",
	"GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME", "GAME",
	"KEYDEFINITION", "KEYDEFINITION",
	"ITEM", "ITEM", "ITEM", "ITEM", "ITEM", "ITEM", "ITEM",
	"MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE", "MOUSE",
	"MOUSE", "MOUSE", "MOUSE", "MOUSE",
	"KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL", "KAEL",
	"CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT",
	"CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT", "CHAT"};

char* ChatDefaults[] = {"ȫ�������Ｏ�ϣ�", "�Ų�ס�ˣ�����", "Σ�գ��ٶ���", "ע�⣬����������", "���������", "�ٶȰ��۲���", "������·Ӣ�۲�����", "DPS��Ǯ��������һ��ȥ��", "һ������ Roshan", "��Ѫ�ˣ������д�ͷ�"};

// Cw3plusApp

// Cw3plusApp ����
Cw3plusApp::Cw3plusApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


HHOOK hookKB = 0;										// ȫ�ּ��̹���handle
HHOOK hookMS = 0;										// ȫ����깳��handle
HANDLE event;
BOOL bLiteMode = FALSE;

// Ψһ��һ�� Cw3plusApp ����
Cw3plusApp theApp;
Cw3plusDlg dlg;

// ���ܴ���ģ��
const BYTE SearchPriority[] = {KAELTOGGLE, KAEL0, KAEL1, KAEL2, KAEL3, KAEL4, KAEL5, KAEL6, KAEL7, KAEL8, KAEL9,
						CHATTOGGLE, CHAT0, CHAT1, CHAT2, CHAT3, CHAT4, CHAT5, CHAT6, CHAT7, CHAT8, CHAT9,
						ITEMTOGGLE, ITEM0, ITEM1, ITEM2, ITEM3, ITEM4, ITEM5,
						MOUSETOGGLE, SELPORTRAITKEY, CONTINUOUSCLICK, AUTOCASTKEY,
						MOUSESKILL1, MOUSESKILL2, MOUSESKILL3, MOUSESKILL4, MOUSESKILL5, MOUSESKILL6, MOUSESKILL7,
						REPLAYPAUSE, REPLAYSPEEDUP, REPLAYSLOWDOWN, REPLAYRELOAD};
const BYTE ItemKeyList[] = {VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD1, VK_NUMPAD2};
const BYTE KaelCastKeyList[] = {'D', 'B', 'X', 'C', 'T', 'V', 'F', 'R', 'G', 'Z'/*6.54orLater*/, 'D', 'B', 'X', 'C', 'T', 'V', 'F', 'R', 'G', 'Z'};
const unsigned char KaelComboKeyList[][5] = {"EEWR", "QWER", "WWQR", "WWER", "EEER", "QQWR", "EEQR", "QQQR", "QQER", "WWWR"/*6.54orLater*/, "EEWR", "QWER", "WWQR", "WWWR", "EEER", "QQWR", "EEQR", "QQQR", "QQER", "WWER"};
const unsigned long InputModeAddress[] = {0x0045CB8C, 0x6FABDFE0, 0x6FAD6E30, 0x6FAE8450};
const unsigned int mouseACPosX[] = {815, 871, 927, 983, 871, 927, 983};
const unsigned int mouseACPosY[] = {734, 734, 734, 734, 678, 678, 678};
const unsigned int mouseRepPosX[] = {810, 855, 900, 945};
const unsigned int mouseRepPosY[] = {740, 740, 740, 740};
const unsigned int mouseSPPosX = 327;
const unsigned int mouseSPPosY = 692;
const unsigned int mouseMMPosX[] = {10, 190};
const unsigned int mouseMMPosY[] = {580, 760};
const unsigned int mouseMBPosX[] = {197, 230};
const unsigned int mouseMBPosY[] = {580, 735};
char sConfigProfile[MAX_PATH] = "default";
unsigned int KeyMappingTable[100];
CString ChatPresets[10];
BOOL bNotifyIconExists = FALSE;
BOOL bDOMReady = FALSE;
BOOL bDiscardKeyUp[257];
BOOL AsyncKeyState[257];
BOOL bBusy = FALSE;
BOOL bBarShowing = FALSE;
BOOL bContinuousClick = FALSE;
BOOL bCursorClipped = FALSE;
BOOL bWar3Windowed = FALSE;
BOOL bWar3Foreground = FALSE;
HWND hWar3 = 0;
unsigned long MEMADDR_NICKNAME = 0;
unsigned long MEMADDR_HOSTNAME = 0;
unsigned int iKeyMonitor = 0;
unsigned char iAuxKey = 0;
unsigned long keyCount = 0;
unsigned long keyProceedCount = 0;
unsigned long allDelay = 0;
unsigned long maxDelay = 0;
unsigned long timerCount = 0;
unsigned long allTimerDelay = 0;
unsigned long maxTimerDelay = 0;
unsigned int lastKey = 0;
unsigned long lastKeyTick = 0;
unsigned int lastKaelCmd = 0;
unsigned long lastKaelCmdTick = 0;
unsigned int lastSeatCount = 0;
POINT ContinuousClickPos;

BOOL bAllEnabled = TRUE;

// ����������
BOOL MouseSimulationEvent(const unsigned int EntryIndex);
BOOL FastChatMessageEvent(const unsigned int EntryIndex);
void ConvertGBKToUtf8(char* strGBK);

void SendKey(const BYTE vkCode)
{
	keybd_event(vkCode, 0, 0, 0);
	keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
}

void SendKeySequence(const unsigned char* bpvkCodes, unsigned int size)
{
	for (unsigned int i=0; i<size; i++)
		SendKey(bpvkCodes[i]);
}

BOOL DetectAuxkey(const BYTE vkCode)
{
	return (vkCode == 0)?TRUE:AsyncKeyState[vkCode];
}

// ��ȡ�������̵�������
void GetCmdLine(DWORD dwPID,TCHAR* pCmdLine,DWORD dwBufLen)
{
	#define BUFFER_LEN    512        //reading buffer for the commandline
	theApp.ElevatePrivileges();
	HANDLE hProc = OpenProcess(PROCESS_VM_READ,FALSE,dwPID);
    if (hProc)
    {
		DWORD dwAddr = *(DWORD*)((DWORD)GetCommandLine + 1);//��2���ֽڿ�ʼ��������Ҫ���ĵ�ַ
		TCHAR tcBuf[BUFFER_LEN] = {0};
		DWORD dwRead = 0;
        if(ReadProcessMemory(hProc,(LPVOID)dwAddr,&dwAddr,4,&dwRead))
        {
            if(ReadProcessMemory(hProc,(LPVOID)dwAddr,tcBuf,BUFFER_LEN,&dwRead))
            {
                _tcsncpy_s(pCmdLine,BUFFER_LEN,tcBuf,dwBufLen);    //��ü��һ��dwRead��dwBufLen�Ĵ�С��ʹ�ý�С���Ǹ�
            }
        }        
    }
}

HWND GetWar3Hwnd()
{
	DWORD pId;
	char buffer[512];
	HWND hwnd = FindWindow("Warcraft III", "Warcraft III");
	if (hwnd != hWar3)
	{
		if (KeyMappingTable[ENABLEWINDOWFUNC])
		{
			if (KeyMappingTable[SKIPWINDOWMODEDETECT])
			{
				bWar3Windowed = true;
			}
			else
			{
				GetWindowThreadProcessId(hwnd, &pId);
				GetCmdLine(pId, buffer, 512);
				bWar3Windowed = (strstr(buffer, "-window")>0);
			}
		}
		hWar3 = hwnd;
		MEMADDR_NICKNAME = 0;
		MEMADDR_HOSTNAME = 0;
		if (bDOMReady) dlg.m_Browser.CallJScript("RefreshStatus", NULL);
	}
	return hwnd;
}

void WINAPI ContinuousClickThread()
{
	POINT mousePos;
	HWND handle = GetWar3Hwnd();
	GetCursorPos(&mousePos);
	while(bContinuousClick && abs(mousePos.x - ContinuousClickPos.x) < 10 && abs(mousePos.y - ContinuousClickPos.y) < 10)
	{
		SendMessage(handle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(ContinuousClickPos.x, ContinuousClickPos.y)); 
		SendMessage(handle, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(ContinuousClickPos.x, ContinuousClickPos.y)); 
		Sleep(10);
		if ((handle = GetWar3Hwnd()) == 0) bContinuousClick = FALSE;
		GetCursorPos(&mousePos);
	}
	bContinuousClick = FALSE;
}

void AllToggle()
{
	bAllEnabled = !bAllEnabled;
	if (bCursorClipped)
	{
		ClipCursor(NULL);
		bCursorClipped = false;
	}
	bBarShowing = FALSE;
	if (bNotifyIconExists)
	{
		dlg.idata.hIcon = AfxGetApp()->LoadIcon(bAllEnabled?IDI_ENABLED:IDI_DISABLED);
		strcpy_s(dlg.idata.szTip, 128, bAllEnabled?"w3plus(������) ˫����ʾ������":"w3plus(����ͣ) ˫����ʾ������");
		strcpy_s(dlg.idata.szInfo, 256, bAllEnabled?"w3plus �������ٴ����á�\n������С���������ڣ�˫����������ٴ���ʾ��":"w3plus �����ѱ���ͣ��\n������С���������ڣ�˫����������ٴ���ʾ��");
		Shell_NotifyIcon(NIM_MODIFY, &dlg.idata);
	}
}

// �ж��Ƿ�������״̬
BOOL IsInputState()
{
	int pValue = 0;
	int inputCheckVer = KeyMappingTable[ENABLEINPUTCHECK] ? 0 : (KeyMappingTable[ENABLEINPUTCHECK122] ? 1 : (KeyMappingTable[ENABLEINPUTCHECK123] ? 2 : (KeyMappingTable[ENABLEINPUTCHECK124] ? 3 : -1)));
	if (inputCheckVer >= 0)
	{
		HANDLE pHandle;
		DWORD pId;
		theApp.ElevatePrivileges();
		GetWindowThreadProcessId(GetWar3Hwnd(), &pId);
		pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
		if (pHandle)
		{
			ReadProcessMemory(pHandle, (LPCVOID)InputModeAddress[inputCheckVer], &pValue, 4, 0);
			CloseHandle(pHandle);
		}
	}
	return (pValue==1);
}

BOOL FunctionDispatch(DWORD vkCode)
{
	// �ж�ǰ̨�����Ƿ�ħ��
	if (GetWar3Hwnd() != GetForegroundWindow()) return FALSE;

	// �����ʱ���ø�����
	if (vkCode == HIBYTE(KeyMappingTable[TEMPAUXKEY]))
	{
		if (bWar3Windowed && bCursorClipped)
		{
			ClipCursor(NULL);
			bCursorClipped = false;
		}
		return TRUE;
	}
	if (HIBYTE(KeyMappingTable[TEMPAUXKEY])!=0 && DetectAuxkey(HIBYTE(KeyMappingTable[TEMPAUXKEY]))) return FALSE;

	// �ж��Ƿ�������״̬
	if (IsInputState()) return FALSE;

	// �����������춨
	if (vkCode > 0xF0 && KeyMappingTable[IGNOREWHEEL] && lastKey == vkCode && GetTickCount() - lastKeyTick < 250) return TRUE;

	// ALLTOGGLE���
	if (DetectAuxkey(HIBYTE(KeyMappingTable[ALLTOGGLE])) && vkCode == LOBYTE(KeyMappingTable[ALLTOGGLE]))
	{
		AllToggle();
		return TRUE;
	}
	if (!bAllEnabled) return FALSE;

	// �жϰ��������ݸ���Ӧ�Ĵ�����
	for (int i=0; i<sizeof(SearchPriority)/sizeof(BYTE); i++)
	{
		int FunctionID = SearchPriority[i];
		if ((LOBYTE(KeyMappingTable[FunctionID])) == vkCode)
		{
			//��Ʒ��ݼ�����
			if (KeyMappingTable[ITEMTOGGLE]) switch(FunctionID)
			{
				case ITEM0:
				case ITEM1:
				case ITEM2:
				case ITEM3:
				case ITEM4:
				case ITEM5:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
					{
						SendKey(ItemKeyList[FunctionID-ITEM0]);
						return TRUE;
					}
			}
			//�����ģ�⹦��
			if (KeyMappingTable[MOUSETOGGLE]) switch(FunctionID)
			{
				case CONTINUOUSCLICK:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
					{
						GetCursorPos(&ContinuousClickPos);
						bContinuousClick = !bContinuousClick;
						::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ContinuousClickThread, NULL, 0, NULL);
						return TRUE;
					}
				case SELPORTRAITKEY:
				case AUTOCASTKEY:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
					{
						return MouseSimulationEvent(FunctionID - SELPORTRAITKEY);
					}
				case MOUSESKILL1:
				case MOUSESKILL2:
				case MOUSESKILL3:
				case MOUSESKILL4:
				case MOUSESKILL5:
				case MOUSESKILL6:
				case MOUSESKILL7:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
					{
						return MouseSimulationEvent(FunctionID - MOUSESKILL1 + 3);
					}
					break;
				case REPLAYPAUSE:
				case REPLAYSPEEDUP:
				case REPLAYSLOWDOWN:
				case REPLAYRELOAD:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
					{
						return MouseSimulationEvent(FunctionID - MOUSESKILL1 + 3);
					}
					break;
			}
			//��������
			if (KeyMappingTable[KAELTOGGLE]) switch(FunctionID)
			{
				case KAEL0:
				case KAEL1:
				case KAEL2:
				case KAEL3:
				case KAEL4:
				case KAEL5:
				case KAEL6:
				case KAEL7:
				case KAEL8:
				case KAEL9:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
					{
						if (KeyMappingTable[KAELCAST] && lastKaelCmd == FunctionID && GetTickCount() - lastKaelCmdTick < 20000)
							SendKey(KaelCastKeyList[KeyMappingTable[KAELVERSION]*10+FunctionID-KAEL0]);
						else
							SendKeySequence(KaelComboKeyList[KeyMappingTable[KAELVERSION]*10+FunctionID-KAEL0], 4);
						lastKaelCmd = FunctionID;
						lastKaelCmdTick = GetTickCount();
						return TRUE;
					}
			}
			//�������칦��
			if (KeyMappingTable[CHATTOGGLE]) switch(FunctionID)
			{
				case CHAT0:
				case CHAT1:
				case CHAT2:
				case CHAT3:
				case CHAT4:
				case CHAT5:
				case CHAT6:
				case CHAT7:
				case CHAT8:
				case CHAT9:
					if (DetectAuxkey(HIBYTE(KeyMappingTable[FunctionID])))
						return FastChatMessageEvent(FunctionID - CHAT0);
			}
		}
	}

	// ����Win��
	if ((vkCode == VK_LWIN || vkCode == VK_RWIN) && KeyMappingTable[DISCARDWIN]) return TRUE;
	return FALSE;
}

BOOL FunctionDispatchStatics(DWORD vkCode)
{
	// ͳ������ʼ
	BOOL bRet = FALSE;
	unsigned long tStart = GetTickCount();
	keyCount++;
	if (!bBusy)
	{
		bBusy = true;
		bRet = FunctionDispatch(vkCode);
		if (bRet) keyProceedCount++;
		bBusy = false;
	}
	unsigned long tEnd = GetTickCount();
	allDelay += tEnd - tStart;
	if (tEnd - tStart > maxDelay) maxDelay = tEnd - tStart;
	return bRet;
}

//�����ģ�⴦����
BOOL MouseSimulationEvent(const unsigned int EntryIndex)
{
	int resX = 0, resY = 0, offX = 0, offY = 0;
	HWND handle = GetWar3Hwnd();
	if (!bWar3Windowed)
	{
		resX=GetSystemMetrics(SM_CXSCREEN);       
		resY=GetSystemMetrics(SM_CYSCREEN);    
	}
	else
	{
		RECT rect;
		POINT point;
		GetClientRect(hWar3, &rect);
		point.x = rect.left;
		point.y = rect.top;
		ClientToScreen(hWar3, &point);
		resX = rect.right - rect.left;
		resY = rect.bottom - rect.top;
		offX = point.x;
		offY = point.y;
	}
	struct tagPOINT pos;
	GetCursorPos(&pos);
	if (EntryIndex == 0)
	{
		mouse_event(MOUSEEVENTF_ABSOLUTE + MOUSEEVENTF_MOVE, (offX+mouseSPPosX*resX/1024)*65535/GetSystemMetrics(SM_CXSCREEN), (offY+mouseSPPosY*resY/768)*65535/GetSystemMetrics(SM_CYSCREEN), NULL, NULL);
		SendMessage(handle, WM_MOUSEMOVE, NULL, MAKELONG((mouseSPPosX*resX/1024), (mouseSPPosY*resY/768))); 
		Sleep(10);
		SendMessage(handle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG((mouseSPPosX*resX/1024), (mouseSPPosY*resY/768)));   
		SendMessage(handle, WM_LBUTTONUP, MK_LBUTTON, MAKELONG((mouseSPPosX*resX/1024), (mouseSPPosY*resY/768)));   
		SetCursorPos(pos.x, pos.y);
	}
	else if (EntryIndex == 2)
	{
		for (int i=0; i<4; i++)
		{
			mouse_event(MOUSEEVENTF_ABSOLUTE + MOUSEEVENTF_MOVE, (offX+mouseACPosX[i]*resX/1024)*65535/GetSystemMetrics(SM_CXSCREEN), (offY+mouseACPosY[i]*resY/768)*65535/GetSystemMetrics(SM_CYSCREEN), NULL, NULL);
			SendMessage(handle, WM_MOUSEMOVE, NULL, MAKELONG(mouseACPosX[i]*resX/1024, mouseACPosY[i]*resY/768)); 
			SendMessage(handle, WM_RBUTTONDOWN, MK_RBUTTON, MAKELONG(mouseACPosX[i]*resX/1024, mouseACPosY[i]*resY/768));   
			SendMessage(handle, WM_RBUTTONUP, MK_RBUTTON, MAKELONG(mouseACPosX[i]*resX/1024, mouseACPosY[i]*resY/768));   
		}
		SetCursorPos(pos.x, pos.y);
	}
	else if (EntryIndex >= 3 && EntryIndex <= 9)
	{
		mouse_event(MOUSEEVENTF_ABSOLUTE + MOUSEEVENTF_MOVE, (offX+mouseACPosX[EntryIndex-3]*resX/1024)*65535/GetSystemMetrics(SM_CXSCREEN), (offY+mouseACPosY[EntryIndex-3]*resY/768)*65535/GetSystemMetrics(SM_CYSCREEN), NULL, NULL);
		SendMessage(handle, WM_MOUSEMOVE, NULL, MAKELONG(mouseACPosX[EntryIndex-3]*resX/1024, mouseACPosY[EntryIndex-3]*resY/768)); 
		SendMessage(handle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(mouseACPosX[EntryIndex-3]*resX/1024, mouseACPosY[EntryIndex-3]*resY/768));   
		SendMessage(handle, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(mouseACPosX[EntryIndex-3]*resX/1024, mouseACPosY[EntryIndex-3]*resY/768));   
		SetCursorPos(pos.x, pos.y);
	}
	else if (EntryIndex >= 10 && EntryIndex <= 13)
	{
		mouse_event(MOUSEEVENTF_ABSOLUTE + MOUSEEVENTF_MOVE, (offX+mouseRepPosX[EntryIndex-11]*resX/1024)*65535/GetSystemMetrics(SM_CXSCREEN), (offY+mouseRepPosY[EntryIndex-11]*resY/768)*65535/GetSystemMetrics(SM_CYSCREEN), NULL, NULL);
		SendMessage(handle, WM_MOUSEMOVE, NULL, MAKELONG(mouseRepPosX[EntryIndex-11]*resX/1024, mouseRepPosY[EntryIndex-11]*resY/768)); 
		SendMessage(handle, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(mouseRepPosX[EntryIndex-11]*resX/1024, mouseRepPosY[EntryIndex-11]*resY/768));   
		SendMessage(handle, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(mouseRepPosX[EntryIndex-11]*resX/1024, mouseRepPosY[EntryIndex-11]*resY/768));   
		SetCursorPos(pos.x, pos.y);
	}
	return TRUE;
}

//�������촦����
BOOL FastChatMessageEvent(const unsigned int EntryIndex)
{
	//���������
	if(OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, 255);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy_s(buffer, 255, LPCSTR(ChatPresets[EntryIndex]));
		ConvertGBKToUtf8(buffer);
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
		if (KeyMappingTable[CHATTARGET0 + EntryIndex])
		{
			keybd_event(VK_SHIFT, 0, 0, 0);
			SendKey(VK_RETURN);
			keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
		}
		else
			SendKey(VK_RETURN);
		keybd_event(VK_CONTROL, 0, 0, 0);
		SendKey('V');
		keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
		SendKey(VK_RETURN);
	}
	return TRUE;
}

//�޸���Ϸ�����
void ModifyWar3Nickname(char* nickname)
{
	HANDLE pHandle;
	DWORD pId;
	int i=0;
	char buffer[100];
	theApp.ElevatePrivileges();
	GetWindowThreadProcessId(GetWar3Hwnd(), &pId);
	if (pId)
	{
		pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
		if (pHandle)
		{
			ConvertGBKToUtf8(nickname);
			if (!MEMADDR_NICKNAME)
			{
				char regname[]="Software\\Blizzard Entertainment\\Warcraft III\\String"; 
				char findID[30];
				HKEY hkResult; 
				DWORD type=REG_SZ;
				DWORD len=MAX_PATH; 
				int ret=RegOpenKey(HKEY_CURRENT_USER,regname,&hkResult); 
				ret=RegQueryValueEx(hkResult,"UserLocal",NULL,&type,(LPBYTE)findID,&len); 
				if  (!ret)
				{
					for (i=0;i<=0xFF;i++)
					{
						ReadProcessMemory(pHandle, (LPVOID)(0x00E54120+i*0x10000), buffer, 100, NULL);
						if (strstr(buffer, findID))
						{
							MEMADDR_NICKNAME = 0x00E54120+i*0x10000;
							break;
						}
					}
				}
				else
				{
					MessageBox(NULL, "ħ��ע�����Ϣ��ȡʧ�ܣ�", "����", MB_ICONERROR);
				}
			}
			if (!MEMADDR_NICKNAME) MessageBox(NULL, "û���ҵ��ڴ��е�ħ�������������ʧ�ܣ�", "����", MB_ICONERROR);
			else WriteProcessMemory(pHandle, (LPVOID)(MEMADDR_NICKNAME), nickname, strlen(nickname) + 1, NULL);
			CloseHandle(pHandle);
		}
		else
		{
			MessageBox(NULL, "��ħ�޽���ʧ�ܣ�", "����", MB_ICONERROR);
		}
	}
	else
	{
		MessageBox(NULL, "û���ҵ�ħ�޽��̣�", "����", MB_ICONERROR);
	}
}

//�޸�ħ��������
void ModifyWar3Hostname(char* hostname)
{
	HANDLE pHandle;
	DWORD pId;
	int i=0;
	char buffer[100];
	theApp.ElevatePrivileges();
	GetWindowThreadProcessId(GetWar3Hwnd(), &pId);
	if (pId)
	{
		pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
		if (pHandle)
		{
			ConvertGBKToUtf8(hostname);
			if (!MEMADDR_HOSTNAME)
			{
				for (i=0;i<=0xFF;i++)
				{
					ReadProcessMemory(pHandle, (LPVOID)(0x02005268+i*0x10000), buffer, 100, NULL);
					if (strstr(buffer, "%s"))
					{
						MEMADDR_HOSTNAME = 0x02005268+i*0x10000;
						break;
					}
				}
			}
			if (!MEMADDR_HOSTNAME) MessageBox(NULL, "û���ҵ��ڴ��е�ħ��������������ʧ�ܣ�", "����", MB_ICONERROR);
			else WriteProcessMemory(pHandle, (LPVOID)(MEMADDR_HOSTNAME), hostname, strlen(hostname) + 1, NULL);
			CloseHandle(pHandle);
		}
		else
		{
			MessageBox(NULL, "��ħ�޽���ʧ�ܣ�", "����", MB_ICONERROR);
		}
	}
	else
	{
		MessageBox(NULL, "û���ҵ�ħ�޽��̣�", "����", MB_ICONERROR);
	}
}

//��ʱ��������
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	unsigned long tStart = GetTickCount();
	timerCount++;
	if (GetWar3Hwnd() == GetForegroundWindow())
	{
		//ħ���л�ִ�й���:����4:3���ڱ���
		if (bAllEnabled && bWar3Windowed && KeyMappingTable[ENABLEWINDOWFUNC] && KeyMappingTable[ENABLELOCKRATIO])
		{
			RECT rect, rectW;
			GetClientRect(hWar3, &rect);
			GetWindowRect(hWar3, &rectW);
			if ((rect.bottom - rect.top)/3 > (rect.right - rect.left)/4)
			{
				rectW.bottom += (rect.right - rect.left) * 3 / 4 + rect.top - rect.bottom;
				SetWindowPos(hWar3, NULL, 0, 0, rectW.right - rectW.left, rectW.bottom - rectW.top, SWP_NOMOVE);
				bCursorClipped = FALSE;
			}
			else if  ((rect.bottom - rect.top)/3 < (rect.right - rect.left)/4)
			{
				rectW.right += (rect.bottom - rect.top) * 4 / 3 + rect.left - rect.right;
				SetWindowPos(hWar3, NULL, 0, 0, rectW.right - rectW.left, rectW.bottom - rectW.top, SWP_NOMOVE);
				bCursorClipped = FALSE;
			}
		}
		//ħ��ǰִ̨�й���:���ڻ�������귶Χ
		if (bAllEnabled && bWar3Windowed && KeyMappingTable[ENABLEWINDOWFUNC] && KeyMappingTable[ENABLECLIPCURSOR] && !bCursorClipped)
		{
			RECT rect;
			POINT point;
			GetClientRect(hWar3, &rect);
			point.x = rect.left;
			point.y = rect.top;
			ClientToScreen(hWar3, &point);
			OffsetRect(&rect, point.x, point.y);
			GetCursorPos(&point);
			if (point.x > rect.left + 50 && point.x < rect.right - 50 && point.y > rect.top + 50 && point.y < rect.bottom - 50)
			{
				ClipCursor(&rect);
				bCursorClipped = true;
			}
		}
		//ħ��ǰִ̨�й���:Ѫ����ʾ
		if (bAllEnabled && KeyMappingTable[SHOWLIFEBAR] && !bBarShowing)
		{
			bBusy = true;
			if (KeyMappingTable[SHOWENEMYBAR])
			{
				keybd_event(VK_OEM_6, 0, 0, 0);
				SendKey(VK_BACK);
			}
			if (KeyMappingTable[SHOWALLYBAR])
			{
				keybd_event(VK_OEM_4, 0, 0, 0);
				SendKey(VK_BACK);
			}
			bBusy = false;
			bBarShowing = true;
		}
		bWar3Foreground = TRUE;
	}
	else
	{
		//ħ�޺�ִ̨�й���:���ڻ��ͷ��������
		if (bCursorClipped)
		{
			ClipCursor(NULL);
			bCursorClipped = false;
		}
		//ħ�޺�ִ̨�й���:Ѫ����ʾ����
		bBarShowing = false;
		////ħ�޺�ִ̨�й���:������ʾ
		//int pValue = 0;
		//unsigned long temp=0x453B8000;
		//if (bAllEnabled && KeyMappingTable[ENABLEAUXFUNC] && KeyMappingTable[ENABLEFULLNOTIFY])
		//{
		//	HANDLE pHandle;
		//	DWORD pId;
		//	theApp.ElevatePrivileges();
		//	GetWindowThreadProcessId(GetWar3Hwnd(), &pId);
		//	pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
		//	if (pHandle)
		//	{
		//		ReadProcessMemory(pHandle, (LPCVOID)0x04D1FE34/*0525F600*/, &pValue, 4, 0);
		//		//WriteProcessMemory(pHandle, (LPVOID)0x6F0FDF7E, &temp, 4, NULL);
		//		CloseHandle(pHandle);
		//	}
		//	if (pValue != lastSeatCount && pValue == 1) 
		//	{
		//		lastSeatCount = pValue;
		//		MessageBox(NULL, "��ʾ���������������Կ�ʼ��Ϸ��\n\nEnjoy~", "w3plus", MB_ICONINFORMATION|MB_SYSTEMMODAL);
		//	}
		//	else
		//	{
		//		lastSeatCount = pValue;
		//	}
		//}
		bWar3Foreground = FALSE;
	}
	unsigned long tEnd = GetTickCount();
	allTimerDelay += tEnd - tStart;
	if (tEnd - tStart > maxTimerDelay) maxTimerDelay = tEnd - tStart;
}

bool RestrictMiniMapRClick()
{
	int resX = 0, resY = 0, offX = 0, offY = 0;
	HWND handle = GetWar3Hwnd();
	if (!bWar3Windowed)
	{
		resX=GetSystemMetrics(SM_CXSCREEN);       
		resY=GetSystemMetrics(SM_CYSCREEN);    
	}
	else
	{
		RECT rect;
		POINT point;
		GetClientRect(hWar3, &rect);
		point.x = rect.left;
		point.y = rect.top;
		ClientToScreen(hWar3, &point);
		resX = rect.right - rect.left;
		resY = rect.bottom - rect.top;
		offX = point.x;
		offY = point.y;
	}
	struct tagPOINT pos;
	GetCursorPos(&pos);
	if (pos.x>(offX+mouseMMPosX[0]*resX/1024) && pos.x<(offX+mouseMMPosX[1]*resX/1024) && pos.y>(offY+mouseMMPosY[0]*resY/768) && pos.y<(offY+mouseMMPosY[1]*resY/768)) return true; else return false;
}

bool RestrictMiniMapButtons()
{
	int resX = 0, resY = 0, offX = 0, offY = 0;
	HWND handle = GetWar3Hwnd();
	if (!bWar3Windowed)
	{
		resX=GetSystemMetrics(SM_CXSCREEN);       
		resY=GetSystemMetrics(SM_CYSCREEN);    
	}
	else
	{
		RECT rect;
		POINT point;
		GetClientRect(hWar3, &rect);
		point.x = rect.left;
		point.y = rect.top;
		ClientToScreen(hWar3, &point);
		resX = rect.right - rect.left;
		resY = rect.bottom - rect.top;
		offX = point.x;
		offY = point.y;
	}
	struct tagPOINT pos;
	GetCursorPos(&pos);
	if (pos.x>(offX+mouseMBPosX[0]*resX/1024) && pos.x<(offX+mouseMBPosX[1]*resX/1024) && pos.y>(offY+mouseMBPosY[0]*resY/768) && pos.y<(offY+mouseMBPosY[1]*resY/768)) return true; else return false;
}

// ȫ����� HOOK ������
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	BOOL bCancelMouse = FALSE;
	if (nCode == HC_ACTION) 
	{
		PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT) lParam;
		switch (wParam)
		{
		case WM_MBUTTONDOWN:
			AsyncKeyState[0xF0] = TRUE;
			if (iKeyMonitor == 0)
			{
				bCancelMouse = FunctionDispatchStatics(0xF0);
				bDiscardKeyUp[0xF0] = bCancelMouse;
			}
			else if (iKeyMonitor == 1)
			{
				iKeyMonitor = 2;
				iAuxKey = 0xF0;
				dlg.m_Browser.CallJScript("PrePerformMonitor", _variant_t(0xF0));
				bCancelMouse = TRUE;
				bDiscardKeyUp[0xF0] = bCancelMouse;
			}
			else if (iKeyMonitor == 2)
			{
				if (iAuxKey == 0xF0)
				{
					bCancelMouse = TRUE;
					bDiscardKeyUp[0xF0] = bCancelMouse;
				}
				{
					iKeyMonitor = 0;
					dlg.m_Browser.CallJScript("PerformMonitor", _variant_t(MAKEWORD(0xF0,iAuxKey)));
					bCancelMouse = TRUE;
					bDiscardKeyUp[0xF0] = bCancelMouse;
				}
			}
			break;
		case WM_MBUTTONUP: 
			AsyncKeyState[0xF0] = FALSE;
			lastKey = 0xF0;
			lastKeyTick = GetTickCount();
			if (iKeyMonitor == 2)
			{
				if (iAuxKey == 0xF0)
				{
					dlg.m_Browser.CallJScript("PerformMonitor", _variant_t(0xF0));
					bCancelMouse = TRUE;
				}
			}
			if (bDiscardKeyUp[0xF0])
			{
				bDiscardKeyUp[0xF0] = FALSE;
				bCancelMouse = TRUE;
			}
			break;
		case WM_MOUSEWHEEL:
			if (iKeyMonitor == 0)
			{
				bCancelMouse = FunctionDispatchStatics(0xF1+((short)HIWORD(p->mouseData)>0?0:1));
				lastKey = (unsigned int)(0xF1+((short)HIWORD(p->mouseData)>0?0:1));
				lastKeyTick = GetTickCount();
			}
			else if (iKeyMonitor == 1)
			{
				iKeyMonitor = 0;
				dlg.m_Browser.CallJScript("PerformMonitor", _variant_t(0xF1+((short)HIWORD(p->mouseData)>0?0:1)));
				bCancelMouse = TRUE;
			}
			else if (iKeyMonitor == 2)
			{
				iKeyMonitor = 0;
				dlg.m_Browser.CallJScript("PerformMonitor", _variant_t(MAKEWORD(0xF1+((short)HIWORD(p->mouseData)>0?0:1),iAuxKey)));
				bCancelMouse = TRUE;
			}
			break;
		case WM_LBUTTONDOWN:
			if (KeyMappingTable[ENABLERESTRICT] && KeyMappingTable[RESTRICTMINIMAPBUTTONS] && GetWar3Hwnd() == GetForegroundWindow()) bCancelMouse = RestrictMiniMapButtons();
			break;
		case WM_LBUTTONUP:
			if (KeyMappingTable[ENABLERESTRICT] && KeyMappingTable[RESTRICTMINIMAPBUTTONS] && GetWar3Hwnd() == GetForegroundWindow()) bCancelMouse = RestrictMiniMapButtons();
			break;
		case WM_RBUTTONDOWN:
			if (KeyMappingTable[ENABLERESTRICT] && KeyMappingTable[RESTRICTMINIMAPBUTTONS] && GetWar3Hwnd() == GetForegroundWindow()) bCancelMouse = RestrictMiniMapButtons();
			if (KeyMappingTable[ENABLERESTRICT] && KeyMappingTable[RESTRICTMINIMAPRCLICK] && GetWar3Hwnd() == GetForegroundWindow()) bCancelMouse |= RestrictMiniMapRClick();
			break;
		case WM_RBUTTONUP:
			if (KeyMappingTable[ENABLERESTRICT] && KeyMappingTable[RESTRICTMINIMAPBUTTONS] && GetWar3Hwnd() == GetForegroundWindow()) bCancelMouse = RestrictMiniMapButtons();
			if (KeyMappingTable[ENABLERESTRICT] && KeyMappingTable[RESTRICTMINIMAPRCLICK] && GetWar3Hwnd() == GetForegroundWindow()) bCancelMouse |= RestrictMiniMapRClick();
			break;
		}
	}
	return(bCancelMouse?TRUE:CallNextHookEx(NULL, nCode, wParam, lParam));
}

// ȫ�ּ��� HOOK ������
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	BOOL bCancelKey = FALSE;

	if (nCode == HC_ACTION) 
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
		switch (wParam) 
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			AsyncKeyState[(unsigned char)p->vkCode] = TRUE;
			if (iKeyMonitor == 0)
			{
				bCancelKey = FunctionDispatchStatics(p->vkCode);
				bDiscardKeyUp[p->vkCode] = bCancelKey;
			}
			else if (iKeyMonitor == 1)
			{
				iKeyMonitor = 2;
				iAuxKey = (byte)p->vkCode;
				dlg.m_Browser.CallJScript("PrePerformMonitor", _variant_t(p->vkCode));
				bCancelKey = TRUE;
				bDiscardKeyUp[p->vkCode] = bCancelKey;
			}
			else if (iKeyMonitor == 2)
			{
				if (iAuxKey == p->vkCode)
				{
					bCancelKey = TRUE;
					bDiscardKeyUp[p->vkCode] = bCancelKey;
				}
				else
				{
					iKeyMonitor = 0;
					dlg.m_Browser.CallJScript("PerformMonitor", _variant_t(MAKEWORD(p->vkCode,iAuxKey)));
					bCancelKey = TRUE;
					bDiscardKeyUp[p->vkCode] = bCancelKey;
				}
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP: 
			AsyncKeyState[(unsigned char)p->vkCode] = FALSE;
			lastKey = (unsigned int)p->vkCode;
			lastKeyTick = GetTickCount();
			if (iKeyMonitor == 2)
			{
				if (iAuxKey == p->vkCode)
				{
					dlg.m_Browser.CallJScript("PerformMonitor", _variant_t(p->vkCode));
					bCancelKey = TRUE;
				}
			}
			if (bDiscardKeyUp[p->vkCode])
			{
				bDiscardKeyUp[p->vkCode] = FALSE;
				bCancelKey = TRUE;
			}
		}
	}
	return(bCancelKey?TRUE:CallNextHookEx(NULL, nCode, wParam, lParam));
}

//GBK��UTF-8����ת������
void ConvertGBKToUtf8(char* strGBK)
{
    int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0);
    WCHAR wszUtf8[256];
    MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL); 
    WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, strGBK, len, NULL,NULL);
}

// ���ܴ���ģ�����

void Cw3plusApp::ManageKeyboardHook()
{
	if (!KeyMappingTable[DISABLEKEYBOARD] && hookKB == 0)
		hookKB = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, m_hInstance, 0); 
	else if (KeyMappingTable[DISABLEKEYBOARD] && hookKB)
	{
		UnhookWindowsHookEx(hookKB);
		hookKB = 0;
	}
}

void Cw3plusApp::ManageMouseHook()
{
	if (!KeyMappingTable[DISABLEMOUSE] && hookMS == 0)
		hookMS = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)LowLevelMouseProc, m_hInstance, 0); 
	else if (KeyMappingTable[DISABLEMOUSE] && hookMS)
	{
		UnhookWindowsHookEx(hookMS);
		hookMS = 0;
	}
}

void WINAPI WaitThread()
{
	while(1)
	{
		WaitForSingleObject(event, INFINITE);
		if (MessageBox(NULL, "w3plus�Ѿ�����Сģʽ�ں�̨���С�ȷ���˳���", "w3plus", MB_ICONQUESTION | MB_YESNO | MB_SETFOREGROUND | MB_SYSTEMMODAL) == IDYES) PostThreadMessage(theApp.m_nThreadID, WM_QUIT, 0, 0);
	}
}

// Cw3plusApp ��ʼ��
BOOL Cw3plusApp::InitInstance()
{
	CWinApp::InitInstance();

	event = CreateEvent(NULL, FALSE, FALSE, "w3plusEvent");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		PulseEvent(event);
		CloseHandle(event);
		return FALSE;
	}

	ProcessCommandLine();
	UpdateSettings();
	LoadSettings();
	// ����ȫ�������̹���
	ManageKeyboardHook();
	ManageMouseHook();
	SetTimer(NULL, NULL, 500, TimerProc); 

	if (!(GetAsyncKeyState(VK_SHIFT) & 0x8000) && !bLiteMode)
	{
		INT_PTR nResponse = dlg.DoModal();
	}
	else
	{
		bLiteMode = TRUE;
		MessageBox(NULL, "��ѡ��������Сģʽ����w3plus��\n�����򽫲��������ý���ȶ������������С�ڴ�ռ�÷�ʽ���С�\n�����˳������ٴ�ִ�б�����", "w3plus", MB_ICONINFORMATION | MB_SETFOREGROUND | MB_SYSTEMMODAL);
		::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WaitThread, NULL, 0, NULL);
		SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
		MSG msg;
		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);   
			DispatchMessage(&msg);   
		}
	}
	if (hookKB) UnhookWindowsHookEx(hookKB);
	if (hookMS) UnhookWindowsHookEx(hookMS);
	SaveSettings();
	CloseHandle(event);
	exit(0);
	return TRUE;
}

void Cw3plusApp::ProcessCommandLine()
{
	char* pos = 0;
	char* cmdline = GetCommandLine();
	if (strstr(cmdline, "-lite")) bLiteMode = TRUE;
	if (pos = strstr(cmdline, "-config:"))
	{
		sscanf_s(pos, "-config:%s", sConfigProfile);
	}
}

//�ڱ�Ҫʱ����������Ȩ��
void Cw3plusApp::ElevatePrivileges()
{
	static bool AlreadyElevated = false;
	if (!AlreadyElevated)
	{
		HANDLE hcurrent=GetCurrentProcess();
		HANDLE hToken;
		BOOL bret=OpenProcessToken(hcurrent,40,&hToken);
		LUID luid;
		bret=LookupPrivilegeValue(NULL,"SeDebugPrivilege",&luid);
		TOKEN_PRIVILEGES NewState,PreviousState;
		DWORD ReturnLength;
		NewState.PrivilegeCount =1;
		NewState.Privileges[0].Luid =luid;
		NewState.Privileges[0].Attributes=2;
		bret=AdjustTokenPrivileges(hToken,FALSE,&NewState,28,&PreviousState,&ReturnLength);
		AlreadyElevated = true;
	}
}

//�����ɰ汾�������ļ�
void Cw3plusApp::UpdateSettings()
{
	char sConfigFilename[MAX_PATH], sNewFilename[MAX_PATH];
	sConfigFilename[GetModuleFileName(NULL, sConfigFilename, MAX_PATH) - 4] = '\0';
	wsprintf(sConfigFilename, "%s%s", sConfigFilename, ".ini");
	if (GetFileAttributes(sConfigFilename) != 0xFFFFFFFF)
	{
		MessageBox(NULL, "��⵽1.10����ǰ�������ļ�������ʽ�����ڻὫ��ת��Ϊdefault�����ļ���", "w3plus", MB_ICONINFORMATION);
		sNewFilename[GetModuleFileName(NULL, sNewFilename, MAX_PATH) - 4] = '\0';
		wsprintf(sNewFilename, "%s%s", sNewFilename, ".default.ini");
		MoveFile(sConfigFilename, sNewFilename);
	}		
}

//�Ӵ����ļ��ж�ȡ����
void Cw3plusApp::LoadSettings()
{
	char sConfigFilename[MAX_PATH];
	char wspBuffer[256];
	long lStrLen = 0;
	sConfigFilename[GetModuleFileName(NULL, sConfigFilename, MAX_PATH) - 3] = '\0';
	wsprintf(sConfigFilename, "%s%s%s", sConfigFilename, sConfigProfile, ".ini");
	long configFileVersion = GetPrivateProfileInt("w3plus", "Version", 0, sConfigFilename);
	if (configFileVersion == 0)
	{
		MessageBox(NULL, "��⵽����Ϊ�״���������������ҳ����������Ҫ�Ĺ��ܲ����úö�Ӧ�İ�����", "w3plus", MB_ICONINFORMATION);
		SaveSettings();
		return;
	}
	else if (configFileVersion < APPVER)
		MessageBox(NULL, "��⵽�ɰ汾�����ļ��������°汾�������ļ��Ľṹ�����иĶ���ʹ��ǰ���ȸ��������Ƿ���ȷ��", "w3plus", MB_ICONINFORMATION);
	for (int i=0; i<sizeof(ConfigFileString)/sizeof(char*); i++)
	{
		KeyMappingTable[i] = GetPrivateProfileInt(ConfigFileGroup[i], ConfigFileString[i], 0, sConfigFilename);
	}
	for (int i=0; i<10; i++)
	{
		wsprintf(wspBuffer, "ChatPreset%d", i);
		GetPrivateProfileString("CHAT", wspBuffer, ChatDefaults[i], wspBuffer, 256, sConfigFilename);
		ChatPresets[i].SetString(wspBuffer);
	}
}

//�����ñ����ڴ����ļ���
void Cw3plusApp::SaveSettings()
{
	char sConfigFilename[MAX_PATH];
	char wspBuffer[256];
	sConfigFilename[GetModuleFileName(NULL, sConfigFilename, MAX_PATH) - 3] = '\0';
	wsprintf(sConfigFilename, "%s%s%s", sConfigFilename, sConfigProfile, ".ini");
	wsprintf(wspBuffer, "%i", APPVER);
	WritePrivateProfileString("w3plus", "Version", wspBuffer, sConfigFilename);
	WritePrivateProfileString("w3plus", "AppString", APP_STRING, sConfigFilename);
	for (int i=0; i<sizeof(ConfigFileString)/sizeof(char*); i++)
	{
		wsprintf(wspBuffer, "%i", KeyMappingTable[i]);
		WritePrivateProfileString(ConfigFileGroup[i], ConfigFileString[i], wspBuffer, sConfigFilename);
	}
	for (int i=0; i<10; i++)
	{
		wsprintf(wspBuffer, "ChatPreset%d", i);
		WritePrivateProfileString("CHAT", wspBuffer, ChatPresets[i], sConfigFilename);
	}
}
