#include "ManageCurDevNotSynch.h"


HWND g_curDevWinHwnd;
CCurUsrManageWnd *g_uiCurDevWin;


/**
*  sonne
*  2018-9
*  查看当前设备用户列表（没有同步过）
*/
CCurUsrManageWnd::CCurUsrManageWnd(LPCTSTR pszXMLPath, HINSTANCE hInstance, PSW_USER pUsers, FINAL_PSW_CERT pCerts, int iUserNum, int iCertNum, P_USER_INFO pUsersFingersInfo, int iUsersFingersInfoNum)
	: CXMLWnd(pszXMLPath) {
	this->hinstance = hInstance;
	this->pUsers = pUsers;
	this->pCerts = pCerts;
	this->iUserNum = iUserNum;
	this->iCertNum = iCertNum;
	this->pUsersFingersInfo = pUsersFingersInfo;
	this->iUsersFingersInfoNum = iUsersFingersInfoNum;
}

#if 0
DWORD WINAPI InitUsersThread(LPVOID lpParameter) {
	Sleep(5000);
	root->Remove(imgUI);
	//CContainerUI* p = static_cast<CContainerUI*> (m_PaintManager.GetRoot());
	CListUI *lst = new CListUI;
	root->Add(lst);
	//<List name = "ListDemo1" float = "true" pos = "30,40,0,0" width = "500" height = "415" vscrollbar = "true" hscrollbar = "true" bkcolor = "#FFFFFFFF" itemtextcolor = "#FF000000" itembkcolor = "#FFFFFFFF" itemselectedtextcolor = "#FF000000" itemselectedbkcolor = "#FFC1E3FF" itemhottextcolor = "#FF000000" itemhotbkcolor = "#FFE9F5FF" itemdisabledtextcolor = "#FFCCCCCC" itemdisabledbkcolor = "#FFFFFFFF">
	lst->SetName("ListDemo1");
	lst->SetFloat(true);
	RECT rc = { 30,40,0,0 };
	lst->SetPos(rc);
	lst->SetFixedWidth(500);
	lst->SetFixedHeight(415);
	CListHeaderUI *lstHeader = new CListHeaderUI;
	lst->Add(lstHeader);
	lstHeader->SetBkImage("List/list_header_bg.png");

	CListHeaderItemUI *item1 = new CListHeaderItemUI;
	CListHeaderItemUI *item2 = new CListHeaderItemUI;
	lstHeader->Add(item1);
	item1->SetText("用户ID");
	item1->SetFixedHeight(23);
	item1->SetFixedWidth(300);
	return TRUE;
}
#endif

void CCurUsrManageWnd::init_data() {
	// 初始化CListUI控件
	CDuiString str;
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	pList->RemoveAll();
	string strId,strName;
	for (int i = 0; i < iUserNum; i++) {
		CListTextElementUI* ele = new CListTextElementUI;
		ele->SetTag(i);
		//ele->SetBorderSize(5);
		//ele->SetBorderColor(0xFF000000);
		pList->Add(ele);

		str.Format(_T("%d"), i);
		strId = STROPERATION::GUID2LPCTS(pUsers[i].UserID);
		ele->SetText(0, strId.c_str());
		strName = getNameOfUserId(strId);
		ele->SetText(1, strName.c_str());
		//ele->SetText(2, user_arr[i].dev_name);
	}
}


void CCurUsrManageWnd::InitWindow() {
	CenterWindow();
	this->init_data();
}


void CCurUsrManageWnd::Notify(TNotifyUI& msg) {
	SW_USER user;
	GUID guid;
	USER_INFO userInfo;
#if 0
	// 双击事件
	if (msg.sType == _T("itemactivate")) {
		int iIndex = msg.pSender->GetTag();
		CDuiString sMessage = _T("Click: ");;
		//sMessage += domain[iIndex].c_str();  

		::MessageBox(NULL, sMessage.GetData(), _T("提示(by tojen)"), MB_OK);
	}
#endif
	if (msg.sType == _T("itemclick")) {
		UINT_PTR i_index = msg.pSender->GetTag();
		int clicked_user_num = i_index;
		user = this->pUsers[clicked_user_num];
		GUID tempGuid = user.UserID;
		for (int i = 0; i < this->iUsersFingersInfoNum; i++) {
			STROPERATION::LPCTSR2GUID(this->pUsersFingersInfo[i].user_id, guid);
			if (tempGuid == guid) {
				userInfo = this->pUsersFingersInfo[i];
			}
		}

		// 如果是当前设备的用户，则运行操作
		//if (!strcmp(user_arr[clicked_user_num].dev_name, g_dev_name.c_str())) {
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		CCurUserManageMenuWnd *p_menu = new CCurUserManageMenuWnd(_T("Menu/CurDevMenu.xml"), i_index, this->pUsers,this->pCerts,this->iUserNum,this->iCertNum, userInfo);
		p_menu->Init(g_curDevWinHwnd, pt);
		p_menu->ShowWindow(TRUE);
		//}
		//else {
		//	MessageBox(NULL, "非当前设备用户，无法操作", NULL, NULL);
		//}
	}
	if (msg.sType == _T("click")) {
	
		if (msg.pSender->GetName() == _T("impt_btn")) {
			//createAddUserWin();
			createSelUsersImptWin();
			this->init_data();
		}
	
	}
	__super::Notify(msg);
}


CControlUI* CCurUsrManageWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}

/**
*  sonne
*  2018-9
*  查看当前设备用户列表（没有同步过）
*/
void  createCurDevManageWin(HINSTANCE hInstance, HWND par_hwnd, PSW_USER pUsers, FINAL_PSW_CERT pCerts, int iUserNum,
	           int iCertNum, P_USER_INFO pUsersFingersInfo,int iUsersFingersInfoNum) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(hInstance);

	g_uiCurDevWin = new CCurUsrManageWnd(_T("cur_dev.xml"), hInstance,  pUsers,  pCerts,  iUserNum,  iCertNum, pUsersFingersInfo, iUsersFingersInfoNum);
	g_curDevWinHwnd = g_uiCurDevWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	g_uiCurDevWin->ShowModal();
	delete g_uiCurDevWin;
	::CoUninitialize();
}