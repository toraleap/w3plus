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
// 如果要使用脚本禁止网页元素的选取用下面语句即可
var cList = new Array("禁用键盘监控功能", "禁用鼠标监控功能", "启用通知区图标 (下次启动软件时生效)", "退出软件时弹出确认框", "连续同向鼠标滚轮仅识别一次", "屏蔽左右Win键", "开启血条显示功能", "显示敌方血条", "显示己方血条", "魔兽窗口化相关功能", "跳过窗口模式检测", "窗口化时智能鼠标锁定", "固定窗口比例为4:3", "特定版本辅助功能(多选以首项为准)", "输入时暂停改键(1.20/1.21)", "输入时暂停改键(1.22)", "输入时暂停改键(1.23)", "输入时暂停改键(1.24)", "游戏中操作屏蔽", "屏蔽小地图区域鼠标右键", "屏蔽小地图右侧按钮", "所有功能总开关键", "临时恢复辅助键", "开启物品快捷键功能", "物品栏位1 (小键盘7)", "物品栏位2 (小键盘8)", "物品栏位3 (小键盘4)", "物品栏位4 (小键盘5)", "物品栏位5 (小键盘1)", "物品栏位6 (小键盘2)", "开启模拟鼠标点击功能", "点击单位肖像位置", "鼠标左键连续点击", "技能自动释放切换", "模拟点击使用技能(底排1)", "模拟点击使用技能(底排2)", "模拟点击使用技能(底排3)", "模拟点击使用技能(底排4)", "模拟点击使用技能(中排2)", "模拟点击使用技能(中排3)", "模拟点击使用技能(中排4)", "观看录像 - 暂停", "观看录像 - 加速", "观看录像 - 减速", "观看录像 - 重新开始观看", "开启卡尔功能", "DotA6.54及以后版本", "短时间内再次按下使用技能", "浑沌陨石 EEW[D]", "超震声波 QWE[B]", "强袭飓风 WWQ[X]", "电磁脉冲 WWE[C] (WWW[C])", "阳炎冲击 EEE[T]", "幽灵漫步 QQW[V]", "熔炉精灵 EEQ[F]", "急速冷却 QQQ[R]", "寒冰之墙 QQE[G]", "灵动迅捷 WWW[Z] (WWE[Z])", "开启快速聊天功能", "预设对话0", "预设对话1", "预设对话2", "预设对话3", "预设对话4", "预设对话5", "预设对话6", "预设对话7", "预设对话8", "预设对话9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
var cTip = new Array("按键配置里设置的按键快捷键将失效", "按键配置里设置的鼠标快捷键将失效", "任务栏右下角的图标，将在下次重新启动程序时生效", "防止误退出软件而弹出对话框确认退出", "在250ms内多次相同的鼠标滚轮动作会被忽略", "按下键盘上的Win键将不会弹出游戏", "本功能模拟键盘上的[]两个键显血", "显示敌方血条", "显示己方血条", "通过检测-window参数判断魔兽是否在窗口模式运行", "强制软件认为魔兽争霸运行于窗口模式，若检测不到魔兽处于窗口模式请打开", "魔兽处于活动窗口且鼠标位于窗口内部距边界至少50px时才将鼠标限制在窗口内，方便调整窗口大小", "调整魔兽窗口大小时将窗口内部横竖比固定为4:3", "请根据魔兽版本选择开启以下功能", "打字时不改键，适用于魔兽1.20/1.21版本", "打字时不改键，适用于魔兽1.22版本", "打字时不改键，适用于魔兽1.23版本", "打字时不改键，适用于魔兽1.24版本", "限制游戏中的一些不常用操作，防止误点", "限制使用鼠标右键点击小地图，可避免逃跑时意外回头的情况", "限制点击小地图右侧的按钮，防止误点击改变小地图状态", "按下开关本软件的所有功能", "按住不放时恢复按键和鼠标的原有功能", "本功能模拟小键盘数字键使用物品", "物品栏位1 (小键盘7)", "物品栏位2 (小键盘8)", "物品栏位3 (小键盘4)", "物品栏位4 (小键盘5)", "物品栏位5 (小键盘1)", "物品栏位6 (小键盘2)", "本功能模拟鼠标动作，期间尽量避免人工操作", "点击下方单位肖像", "模拟过程中鼠标移动距离超过10px将自动取消", "模拟鼠标右键点击底部四个技能栏", "模拟鼠标左键点击技能图标(底排第一个)", "模拟鼠标左键点击技能图标(底排第二个)", "模拟鼠标左键点击技能图标(底排第三个)", "模拟鼠标左键点击技能图标(底排第四个)", "模拟鼠标左键点击技能图标(中排第二个)", "模拟鼠标左键点击技能图标(中排第三个)", "模拟鼠标左键点击技能图标(中排第四个)", "模拟鼠标左键点击暂停/开始录像", "模拟鼠标左键点击加快播放速度", "模拟鼠标左键点击减慢播放速度", "模拟鼠标左键点击重新开始录像", "开启后可一键切换卡尔技能", "DotA6.54及以后卡尔技能有所变动，请正确选择", "20s内再次按下上次的技能快捷键将使用该技能，也就是说连按两下设置的快捷键将切换出并使用该技能。请根据具体网络延迟的情况决定连按的间隔。", "浑沌陨石 EEW[D]", "超震声波 QWE[B]", "强袭飓风 WWQ[X]", "电磁脉冲 WWE[C] (WWW[C])", "阳炎冲击 EEE[T]", "幽灵漫步 QQW[V]", "熔炉精灵 EEQ[F]", "急速冷却 QQQ[R]", "寒冰之墙 QQE[G]", "灵动迅捷 WWW[Z] (WWE[Z])", "利用剪贴板及键盘操作在游戏中发送对话", "预设对话0", "预设对话1", "预设对话2", "预设对话3", "预设对话4", "预设对话5", "预设对话6", "预设对话7", "预设对话8", "预设对话9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
//cType: 000000(0)不显示域；000001(1)标准按键；000010(2)辅助键；001100(12)功能组开关；000100(4)复选框选项；010001(17)标准按键+聊天文本。
var cType = new Array(4,4,4,4,4,4,12,4,4,12,4,4,4,12,4,4,4,4,12,4,4,1,2,12,1,1,1,1,1,1,12,1,1,1,1,1,1,1,1,1,1,1,1,1,1,12,4,4,1,1,1,1,1,1,1,1,1,1,12,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0);
var cValue = new Array(cList.length);
var ChatPresets = new Array(10);
//defines
var ChatTargetsBeginsAt = 0;
//init
var MonitorCellIndex = -1;
var DefaultNickname = "菜鸟";
var DefaultHostname = "DotA RDSP模式(%s)";
var CharTable = new Array(/*0*/ "", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "BackSpace", "Tab", "无法识别", "无法识别", "无法识别", "Enter", "无法识别", "无法识别",
					 /*1*/ "Shift", "Ctrl", "Alt", "Pause", "CapsLock", "无法识别", "无法识别", "无法识别", /*8*/ "无法识别", "无法识别", "无法识别", "Esc", "无法识别", "无法识别", "无法识别", "无法识别",
					 /*2*/ "Space", "PageUp", "PageDn", "End", "Home", "Left", "Up", "Right", /*8*/ "Down", "无法识别", "无法识别", "无法识别", "PrtScr", "Insert", "Delete", "无法识别",
					 /*3*/ "0", "1", "2", "3", "4", "5", "6", "7", /*8*/ "8", "9", "0", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别",
					 /*4*/ "无法识别", "A", "B", "C", "D", "E", "F", "G", /*8*/ "H", "I", "J", "K", "L", "M", "N", "O",
					 /*5*/ "P", "Q", "R", "S", "T", "U", "V", "W", /*8*/ "X", "Y", "Z", "LWin", "RWin", "App", "无法识别", "无法识别",
					 /*6*/ "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", /*8*/ "Num8", "Num9", "Num*", "Num+", "无法识别", "Num-", "无法识别", "Num/",
					 /*7*/ "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", /*8*/ "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16",
					 /*8*/ "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", /*8*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别",
					 /*9*/ "NumLock", "ScrLock", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "", "", "", "", "", "", "", "",
					 /*A*/ "LShift", "RShift", "LCtrl", "RCtrl", "LAlt", "RAlt", "", "", /*8*/ "", "", "", "", "", "", "", "",
					 /*B*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "无法识别", "无法识别", ";", "=", ",", "-", ".", "/",
					 /*C*/ "`", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别",
					 /*D*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "无法识别", "无法识别", "无法识别", "[", "\\", "]", "'", "无法识别",
					 /*E*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别",
					 /*F*/ "鼠标中键", "鼠标滚轮上", "鼠标滚轮下", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", /*8*/ "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别", "无法识别");

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
		$("#cell" + CellIndex).html(((cValue[CellIndex]&0xFF00)?("["+CharTable[(cValue[CellIndex]&0xFF00)>>8]+"]"):"") + ((cValue[CellIndex]!=0)?(" "+CharTable[cValue[CellIndex]&0x00FF]):"未设置"));
	}
	else
		if (cValue[CellIndex]) $("#cell" + CellIndex + " span").addClass("checked").removeClass("unchecked");
		else $("#cell" + CellIndex + " span").addClass("unchecked").removeClass("checked");
}

function RefreshChat(ChatIndex)
{
	$("#chat" + ChatIndex).html("(<a href='#' onclick='return UpdateChatTarget(" + ChatIndex + ");'>" + (cValue[ChatTargetsBeginsAt + ChatIndex]?"全体":"盟友") + "</a>)" + ChatPresets[ChatIndex]);
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
		showTip("<b>" + cList[CellIndex] + (cValue[CellIndex]==0?"</b><br><br>":"</b><br>") + (cType[CellIndex]==2?"请按下一个键以设置为辅助键":"请按下组合键或拨动鼠标滚轮") + (cValue[CellIndex]==0?"":"<br><a href=# onclick='external.CancelKeyMonitor();PerformMonitor(0);'>或者点击这里取消已设置的按键</a>"));
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
	var ChatMsg = prompt("请输入预设对话" + ChatIndex + "的内容", ChatPresets[ChatIndex]);
	if (ChatMsg != null)
	{
	    ChatPresets[ChatIndex] = ChatMsg;
	    external.SetChatMessage(ChatIndex, ChatMsg);
	}
	RefreshChat(ChatIndex);
}

function PrePerformMonitor(vkCode)
{
	showTip(CharTable[vkCode] + "<br>等待下一个按键……");
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
	runStat.innerHTML = external.QueryRunningState()?"<a href=# onclick='external.SwitchRunningState();RefreshStatus();'>运行中</a>":"<a href=# onclick='external.SwitchRunningState();RefreshStatus();'>已暂停</a>";
	kbHook.innerHTML = external.QueryKeyboardHook()?"<a href=# onclick='external.SetEntrySetting(0,1);RefreshStatus();cValue[0]=1;RefreshCell(0);'>已激活</a>":"<a href=# onclick='external.SetEntrySetting(0,0);RefreshStatus();cValue[0]=0;RefreshCell(0);'>未使用</a>";
	msHook.innerHTML = external.QueryMouseHook()?"<a href=# onclick='external.SetEntrySetting(1,1);RefreshStatus();cValue[1]=1;RefreshCell(1);'>已激活</a>":"<a href=# onclick='external.SetEntrySetting(1,0);RefreshStatus();cValue[1]=0;RefreshCell(1);'>未使用</a>";
	warStat.innerHTML = external.QueryWar3State();//?"检测到war3.exe进程运行中":"未检测到war3.exe进程";
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
		$("#configlist").prepend("<tr><td class='configitem'><a href='#' onclick=\"ChangeConfigProfile('"+ cfArray[i] +"')\">切换到: "+cfArray[i]+"</a></td></tr>");
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
	var NewFilename = prompt("请输入欲保存的新配置名称", "");
	if (NewFilename != null && NewFilename != "")
	{
	    external.DuplicateConfigFile(NewFilename);
		RefreshConfigList();
		ChangeConfigProfile(NewFilename);
	}
}

function ModifyNickname()
{
	var NewNickname = prompt("请输入新玩家名称,可以使用中文,转换成UTF8后长度限制15字节\n魔兽应在主菜单界面方可生效", DefaultNickname);
	if (NewNickname != null && NewNickname != "")
	{
	    DefaultNickname = NewNickname;
	    external.ModifyNickname(NewNickname);
	}
}

function ModifyHostname()
{
	var NewHostname = prompt("请输入新主机名称,转换成UTF8后长度限制23字节\n用%s代表用户ID,如\"本地局域网的游戏 (%s)\"", DefaultHostname);
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