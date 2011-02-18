document.onselectstart=new Function('return false');
$(document).ready(function(){
	$("#configtrigger").click(function(){
		$("div.configlist").get(0).style.top = $("span.config").get(0).offsetTop + 20;
		$("div.configlist").get(0).style.left = $("span.config").get(0).offsetLeft;
		$("div.configlist").slideToggle(100);});
	$("#configtrigger").mouseleave(function(){
		$("div.configlist").slideUp(100);});
	$(".litab").click(function(){
		$(".litab").removeClass("licur");
		$(this).addClass("licur");
		$(".tabContent").slideUp("fast");
		$("#tabContent"+jQuery.inArray(this, $(".litab"))).slideDown();
	});
	$("#TableHelp tr td.group").parent().click(function(){
		$(this).next().children().children().slideToggle("fast");
		$("#TableHelp div:not(:animated)").slideUp("fast");
	});
	$(".litab a").focus(function(){this.blur()});
	$('#configprofile').html("("+external.GetCurrentConfigFile()+")");
	RefreshConfigList();
	InitMappingTable();
	RefreshStatus();
	external.DOMReadyCallback();
	setInterval('RefreshStatus();',30000);
});
// ���Ҫʹ�ýű���ֹ��ҳԪ�ص�ѡȡ��������伴��
var cList = new Array("���ü��̼�ع���", "��������ع���", "����֪ͨ��ͼ�� (�´��������ʱ��Ч)", "�˳����ʱ����ȷ�Ͽ�", "����ͬ�������ֽ�ʶ��һ��", "��������Win��", "����Ѫ����ʾ����", "��ʾ�з�Ѫ��", "��ʾ����Ѫ��", "ħ�޴��ڻ���ع���", "��������ģʽ���", "���ڻ�ʱ�����������", "�̶����ڱ���Ϊ4:3", "�ض��汾��������(��ѡ������Ϊ׼)", "����ʱ��ͣ�ļ�(1.20/1.21)", "����ʱ��ͣ�ļ�(1.22)", "����ʱ��ͣ�ļ�(1.23)", "����ʱ��ͣ�ļ�(1.24)", "��Ϸ�в�������", "����С��ͼ��������Ҽ�", "����С��ͼ�Ҳఴť", "���й����ܿ��ؼ�", "��ʱ�ָ�������", "������Ʒ��ݼ�����", "��Ʒ��λ1 (С����7)", "��Ʒ��λ2 (С����8)", "��Ʒ��λ3 (С����4)", "��Ʒ��λ4 (С����5)", "��Ʒ��λ5 (С����1)", "��Ʒ��λ6 (С����2)", "����ģ�����������", "�����λФ��λ��", "�������������", "�����Զ��ͷ��л�", "ģ����ʹ�ü���(����1)", "ģ����ʹ�ü���(����2)", "ģ����ʹ�ü���(����3)", "ģ����ʹ�ü���(����4)", "ģ����ʹ�ü���(����2)", "ģ����ʹ�ü���(����3)", "ģ����ʹ�ü���(����4)", "�ۿ�¼�� - ��ͣ", "�ۿ�¼�� - ����", "�ۿ�¼�� - ����", "�ۿ�¼�� - ���¿�ʼ�ۿ�", "������������", "DotA6.54���Ժ�汾", "��ʱ�����ٴΰ���ʹ�ü���", "������ʯ EEW[D]", "�������� QWE[B]", "ǿϮ쫷� WWQ[X]", "������� WWE[C] (WWW[C])", "���׳�� EEE[T]", "�������� QQW[V]", "��¯���� EEQ[F]", "������ȴ QQQ[R]", "����֮ǽ QQE[G]", "�鶯Ѹ�� WWW[Z] (WWE[Z])", "�����������칦��", "Ԥ��Ի�0", "Ԥ��Ի�1", "Ԥ��Ի�2", "Ԥ��Ի�3", "Ԥ��Ի�4", "Ԥ��Ի�5", "Ԥ��Ի�6", "Ԥ��Ի�7", "Ԥ��Ի�8", "Ԥ��Ի�9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
var cTip = new Array("�������������õİ�����ݼ���ʧЧ", "�������������õ�����ݼ���ʧЧ", "���������½ǵ�ͼ�꣬�����´�������������ʱ��Ч", "��ֹ���˳�����������Ի���ȷ���˳�", "��250ms�ڶ����ͬ�������ֶ����ᱻ����", "���¼����ϵ�Win�������ᵯ����Ϸ", "������ģ������ϵ�[]��������Ѫ", "��ʾ�з�Ѫ��", "��ʾ����Ѫ��", "ͨ�����-window�����ж�ħ���Ƿ��ڴ���ģʽ����", "ǿ�������Ϊħ�����������ڴ���ģʽ������ⲻ��ħ�޴��ڴ���ģʽ���", "ħ�޴��ڻ���������λ�ڴ����ڲ���߽�����50pxʱ�Ž���������ڴ����ڣ�����������ڴ�С", "����ħ�޴��ڴ�Сʱ�������ڲ������ȹ̶�Ϊ4:3", "�����ħ�ް汾ѡ�������¹���", "����ʱ���ļ���������ħ��1.20/1.21�汾", "����ʱ���ļ���������ħ��1.22�汾", "����ʱ���ļ���������ħ��1.23�汾", "����ʱ���ļ���������ħ��1.24�汾", "������Ϸ�е�һЩ�����ò�������ֹ���", "����ʹ������Ҽ����С��ͼ���ɱ�������ʱ�����ͷ�����", "���Ƶ��С��ͼ�Ҳ�İ�ť����ֹ�����ı�С��ͼ״̬", "���¿��ر���������й���", "��ס����ʱ�ָ�����������ԭ�й���", "������ģ��С�������ּ�ʹ����Ʒ", "��Ʒ��λ1 (С����7)", "��Ʒ��λ2 (С����8)", "��Ʒ��λ3 (С����4)", "��Ʒ��λ4 (С����5)", "��Ʒ��λ5 (С����1)", "��Ʒ��λ6 (С����2)", "������ģ����궯�����ڼ価�������˹�����", "����·���λФ��", "ģ�����������ƶ����볬��10px���Զ�ȡ��", "ģ������Ҽ�����ײ��ĸ�������", "ģ���������������ͼ��(���ŵ�һ��)", "ģ���������������ͼ��(���ŵڶ���)", "ģ���������������ͼ��(���ŵ�����)", "ģ���������������ͼ��(���ŵ��ĸ�)", "ģ���������������ͼ��(���ŵڶ���)", "ģ���������������ͼ��(���ŵ�����)", "ģ���������������ͼ��(���ŵ��ĸ�)", "ģ�������������ͣ/��ʼ¼��", "ģ������������ӿ첥���ٶ�", "ģ��������������������ٶ�", "ģ��������������¿�ʼ¼��", "�������һ���л���������", "DotA6.54���Ժ󿨶����������䶯������ȷѡ��", "20s���ٴΰ����ϴεļ��ܿ�ݼ���ʹ�øü��ܣ�Ҳ����˵�����������õĿ�ݼ����л�����ʹ�øü��ܡ�����ݾ��������ӳٵ�������������ļ����", "������ʯ EEW[D]", "�������� QWE[B]", "ǿϮ쫷� WWQ[X]", "������� WWE[C] (WWW[C])", "���׳�� EEE[T]", "�������� QQW[V]", "��¯���� EEQ[F]", "������ȴ QQQ[R]", "����֮ǽ QQE[G]", "�鶯Ѹ�� WWW[Z] (WWE[Z])", "���ü����弰���̲�������Ϸ�з��ͶԻ�", "Ԥ��Ի�0", "Ԥ��Ի�1", "Ԥ��Ի�2", "Ԥ��Ի�3", "Ԥ��Ի�4", "Ԥ��Ի�5", "Ԥ��Ի�6", "Ԥ��Ի�7", "Ԥ��Ի�8", "Ԥ��Ի�9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
//cType: 000000(0)����ʾ��000001(1)��׼������000010(2)��������001100(12)�����鿪�أ�000100(4)��ѡ��ѡ�010001(17)��׼����+�����ı���
var cType = new Array(4,4,4,4,4,4,12,4,4,12,4,4,4,12,4,4,4,4,12,4,4,1,2,12,1,1,1,1,1,1,12,1,1,1,1,1,1,1,1,1,1,1,1,1,1,12,4,4,1,1,1,1,1,1,1,1,1,1,12,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0);
var cValue = new Array(cList.length);
var ChatPresets = new Array(10);
//defines
var ChatTargetsBeginsAt = 0;
//init
var MonitorCellIndex = -1;
var DefaultNickname = "����";
var DefaultHostname = "DotA RDSPģʽ(%s)";
var CharTable = new Array(/*0*/ "", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "BackSpace", "Tab", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "Enter", "�޷�ʶ��", "�޷�ʶ��",
					 /*1*/ "Shift", "Ctrl", "Alt", "Pause", "CapsLock", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "Esc", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��",
					 /*2*/ "Space", "PageUp", "PageDn", "End", "Home", "Left", "Up", "Right", /*8*/ "Down", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "PrtScr", "Insert", "Delete", "�޷�ʶ��",
					 /*3*/ "0", "1", "2", "3", "4", "5", "6", "7", /*8*/ "8", "9", "0", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��",
					 /*4*/ "�޷�ʶ��", "A", "B", "C", "D", "E", "F", "G", /*8*/ "H", "I", "J", "K", "L", "M", "N", "O",
					 /*5*/ "P", "Q", "R", "S", "T", "U", "V", "W", /*8*/ "X", "Y", "Z", "LWin", "RWin", "App", "�޷�ʶ��", "�޷�ʶ��",
					 /*6*/ "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", /*8*/ "Num8", "Num9", "Num*", "Num+", "�޷�ʶ��", "Num-", "�޷�ʶ��", "Num/",
					 /*7*/ "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", /*8*/ "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16",
					 /*8*/ "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", /*8*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��",
					 /*9*/ "NumLock", "ScrLock", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "", "", "", "", "", "", "", "",
					 /*A*/ "LShift", "RShift", "LCtrl", "RCtrl", "LAlt", "RAlt", "", "", /*8*/ "", "", "", "", "", "", "", "",
					 /*B*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "�޷�ʶ��", "�޷�ʶ��", ";", "=", ",", "-", ".", "/",
					 /*C*/ "`", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��",
					 /*D*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "[", "\\", "]", "'", "�޷�ʶ��",
					 /*E*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��",
					 /*F*/ "����м�", "��������", "��������", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", /*8*/ "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��", "�޷�ʶ��");

function InitMappingTable()
{
	var tableId = 1;
	var chatId = 0;
	for (i=0;i<cList.length;i++) cValue[i] = external.GetEntrySetting(i);
	for (i=0;i<cList.length;i++) {
		if (i == 5 || i == 21/*MappingTablePageIndex*/) tableId++;
		if (cType[i] > 0)
		{
		    $("#cTable" + tableId).append("<tr><td title='" + cTip[i] + "' " + ((cType[i] & 16)?("id='chat"+chatId+"' onclick='OnChatClick(" + chatId + ");' "):"") + "class=" + ((cType[i] & 8)?"'group'":"'itemcaption'") + ((cType[i] & 4)?" colspan='2' onclick='OnCellClick(" + i + ");' id='cell" + i + "'><span class='" + (cValue[i]?"unchecked":"checked") + "'></span>":">") + cList[i] + "</td>" + ((cType[i] & 1||cType[i] & 2)?"<td onclick='OnCellClick(" + i + ");' id='cell" + i + "' class='itemproperty' width='170px'></td>":"") + "</tr>");
	  	    if (cType[i] & 16)
	  	    {
	  	        if (ChatTargetsBeginsAt == 0) ChatTargetsBeginsAt = i + 10;
		        ChatPresets[chatId] = external.GetChatMessage(chatId);
		        RefreshChat(chatId);
		        chatId++;
   	  	    }
		    RefreshCell(i);
		}
	}
}

function RefreshCell(CellIndex)
{
	if (cType[CellIndex] & 1 || cType[CellIndex] & 2)
	{
		$("#cell" + CellIndex).html(((cValue[CellIndex]&0xFF00)?("["+CharTable[(cValue[CellIndex]&0xFF00)>>8]+"]"):"") + ((cValue[CellIndex]!=0)?(" "+CharTable[cValue[CellIndex]&0x00FF]):"δ����"));
	}
	else
		if (cValue[CellIndex]) $("#cell" + CellIndex + " span").addClass("checked").removeClass("unchecked");
		else $("#cell" + CellIndex + " span").addClass("unchecked").removeClass("checked");
}

function RefreshChat(ChatIndex)
{
	$("#chat" + ChatIndex).html("(<a href='#' onclick='return UpdateChatTarget(" + ChatIndex + ");'>" + (cValue[ChatTargetsBeginsAt + ChatIndex]?"ȫ��":"����") + "</a>)" + ChatPresets[ChatIndex]);
}

function UpdateChatTarget(ChatIndex)
{
    cValue[ChatTargetsBeginsAt + ChatIndex] = 1 - cValue[ChatTargetsBeginsAt + ChatIndex];
    external.SetEntrySetting(ChatTargetsBeginsAt + ChatIndex, cValue[ChatTargetsBeginsAt + ChatIndex]);
    RefreshChat(ChatIndex);
    return false;
}

function OnCellClick(CellIndex)
{
	external.CancelKeyMonitor();
	if (cType[CellIndex] & 3)
	{
		showTip("<b>" + cList[CellIndex] + (cValue[CellIndex]==0?"</b><br><br>":"</b><br>") + (cType[CellIndex]==2?"�밴��һ����������Ϊ������":"�밴����ϼ��򲦶�������") + (cValue[CellIndex]==0?"":"<br><a href=# onclick='external.CancelKeyMonitor();PerformMonitor(0);'>���ߵ������ȡ�������õİ���</a>"));
		MonitorCellIndex = CellIndex;
		external.BeginKeyMonitor();
	}
	else 
	{
		cValue[CellIndex] = 1 - cValue[CellIndex];
		external.SetEntrySetting(CellIndex, cValue[CellIndex]);
		RefreshCell(CellIndex);
		RefreshStatus();
	}
}

function OnChatClick(ChatIndex)
{
	var ChatMsg = prompt("������Ԥ��Ի�" + ChatIndex + "������", ChatPresets[ChatIndex]);
	if (ChatMsg != null)
	{
	    ChatPresets[ChatIndex] = ChatMsg;
	    external.SetChatMessage(ChatIndex, ChatMsg);
	}
	RefreshChat(ChatIndex);
}

function PrePerformMonitor(vkCode)
{
	showTip(CharTable[vkCode] + "<br>�ȴ���һ����������");
}

function PerformMonitor(vkCombo)
{
	if (cType[MonitorCellIndex] & 3)
	{
		cValue[MonitorCellIndex] = (cType[MonitorCellIndex]&1)?vkCombo:(vkCombo & 0x00FF) * 256;
		external.SetEntrySetting(MonitorCellIndex, cValue[MonitorCellIndex]);
		hideTip();
		RefreshCell(MonitorCellIndex);
		MonitorCellIndex = -1;
	}
}

function RefreshStatus()
{
	appVer.innerHTML = external.QueryAppVersion();
	runStat.innerHTML = external.QueryRunningState()?"<a href=# onclick='external.SwitchRunningState();RefreshStatus();'>������</a>":"<a href=# onclick='external.SwitchRunningState();RefreshStatus();'>����ͣ</a>";
	kbHook.innerHTML = external.QueryKeyboardHook()?"<a href=# onclick='external.SetEntrySetting(0,1);RefreshStatus();cValue[0]=1;RefreshCell(0);'>�Ѽ���</a>":"<a href=# onclick='external.SetEntrySetting(0,0);RefreshStatus();cValue[0]=0;RefreshCell(0);'>δʹ��</a>";
	msHook.innerHTML = external.QueryMouseHook()?"<a href=# onclick='external.SetEntrySetting(1,1);RefreshStatus();cValue[1]=1;RefreshCell(1);'>�Ѽ���</a>":"<a href=# onclick='external.SetEntrySetting(1,0);RefreshStatus();cValue[1]=0;RefreshCell(1);'>δʹ��</a>";
	warStat.innerHTML = external.QueryWar3State();//?"��⵽war3.exe����������":"δ��⵽war3.exe����";
	msgCount.innerHTML = external.QueryPerformance(0);
	prcCount.innerHTML = external.QueryPerformance(1);
	avgDelay.innerHTML = external.QueryPerformance(2);
	maxDelay.innerHTML = external.QueryPerformance(3);
	timerCount.innerHTML = external.QueryPerformance(4);
	avgTimerDelay.innerHTML = external.QueryPerformance(5);
	maxTimerDelay.innerHTML = external.QueryPerformance(6);
}

function RefreshConfigList()
{
	$("td.configitem").parent().remove();
	var cfArray = external.GetConfigFiles().split("|");
	for (i=0;i<cfArray.length;i++)
		$("#configlist").prepend("<tr><td class='configitem'><a href='#' onclick=\"ChangeConfigProfile('"+ cfArray[i] +"')\">�л���: "+cfArray[i]+"</a></td></tr>");
}

function ChangeConfigProfile(filename)
{
	if(external.SetConfigFile(filename)){
		$('#configprofile').html("("+filename+")");
		for (i=0;i<cList.length;i++){
			cValue[i] = external.GetEntrySetting(i);
			if (cType[i] > 0) RefreshCell(i);
		}
		for (i=0;i<10;i++){
		    ChatPresets[i] = external.GetChatMessage(i);
			RefreshChat(i);
		}
		RefreshStatus();
	}
	$("div.configlist").slideToggle("fast");
}

function ConfigProfileSaveAs()
{
	var NewFilename = prompt("�����������������������", "");
	if (NewFilename != null && NewFilename != "")
	{
	    external.DuplicateConfigFile(NewFilename);
		RefreshConfigList();
		ChangeConfigProfile(NewFilename);
	}
}

function ModifyNickname()
{
	var NewNickname = prompt("���������������,����ʹ������,ת����UTF8�󳤶�����15�ֽ�\nħ��Ӧ�����˵����淽����Ч", DefaultNickname);
	if (NewNickname != null && NewNickname != "")
	{
	    DefaultNickname = NewNickname;
	    external.ModifyNickname(NewNickname);
	}
}

function ModifyHostname()
{
	var NewHostname = prompt("����������������,ת����UTF8�󳤶�����23�ֽ�\n��%s�����û�ID,��\"���ؾ���������Ϸ (%s)\"", DefaultHostname);
	if (NewHostname != null && NewHostname != "")
	{
	    DefaultHostname = NewHostname;
	    external.ModifyHostname(NewHostname);
	}
}

function showTip(message)
{
	tipContent.innerHTML = message;
	maskDiv.style.visibility = "visible";
	tipDiv.style.visibility = "visible";
}

function hideTip()
{
	maskDiv.style.visibility = "hidden";
	tipDiv.style.visibility = "hidden";
}