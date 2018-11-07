#include "my_duilib.h"
#include "user_manage.h"
#include "MenuWnd2.h"
#include "add_user1.h"
#include "page_utils.h"

HWND g_usr_manage_win_hwnd;
CListUI* pList;
// 分页信息 
c_page_info page_info;
P_USER_INFO_SEL pUserSelArr = NULL;
extern HWND g_usr_manage_win_hwnd;
CUsrManageWnd *g_uiUserManageWin;

extern bool gIsManageCurDev;
//CContainerUI* root;
//CContainerUI* imgUI;

CUsrManageWnd::CUsrManageWnd(LPCTSTR pszXMLPath, HINSTANCE hInstance, bool bIsCurrentUsersManage)
	: CXMLWnd(pszXMLPath) {
	this->hinstance = hInstance;
	this->bIsCurrentUsersManage = bIsCurrentUsersManage;
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

void CUsrManageWnd::init_data() {
	if (pUserSelArr != NULL) {
		delete [] pUserSelArr;
		pUserSelArr = NULL;
	}
	int how_many_users = 0;
	how_many_users = getNumOfUsers();
	// 分页信息
	page_info = c_page_utils::create_page(19, how_many_users, 1);
	char temp[30];

	// 初始化CListUI控件
	CDuiString str;
	pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	pList->RemoveAll();

	selUsers(&pUserSelArr, page_info);

	int num;
	int total = page_info.get_total_count();
	int every_page = page_info.get_every_page();
	if (total > every_page)
		num = every_page;
	else
		num = total;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* ele = new CListTextElementUI;
		ele->SetTag(i);
		pList->Add(ele);

		str.Format(_T("%d"), i);
		ele->SetText(0, pUserSelArr[i].id);
		ele->SetText(1, pUserSelArr[i].name);
		itoa(pUserSelArr[i].fingerNum, temp, 10);
		ele->SetText(2, pUserSelArr[i].dev_name);
		ele->SetText(3, temp);
		itoa(pUserSelArr[i].certNum, temp, 10);
		ele->SetText(4, temp);
	}

	gIsManageCurDev = false;
}


void CUsrManageWnd::init_data_after_flip_page() {
	CDuiString str;
	pList->RemoveAll();

	//user_sel_ret* user_arr;
	if (pUserSelArr != NULL) {
		delete[] pUserSelArr;
		pUserSelArr = NULL;
	}

	selUsers(&pUserSelArr, page_info);

	char temp[30];
	if (pUserSelArr != NULL) {
		int num = page_info.get_total_count() - page_info.get_begin_index();
		if (num > 19)
			num = 19;
		for (int i = 0; i < num; i++) {
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(i);
			pList->Add(pListElement);

			str.Format(_T("%d"), i);
			pListElement->SetText(0, pUserSelArr[i].id);
			pListElement->SetText(1, pUserSelArr[i].name);
			pListElement->SetText(2, pUserSelArr[i].dev_name);
			itoa(pUserSelArr[i].fingerNum, temp, 10);
			pListElement->SetText(3, temp);
			itoa(pUserSelArr[i].certNum, temp, 10);
			pListElement->SetText(4, temp);
		}
	}
}


void CUsrManageWnd::init_data_after_search(const char* username) {
#if 0
	CDuiString str;
	pList->RemoveAll();

	user_arr = MYSQL_INTERFACES::select_users_of_name("", username);
	if (user_arr != NULL) {
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(0);
		pList->Add(pListElement);

		pListElement->SetText(0, user_arr[0].id);
		pListElement->SetText(1, user_arr[0].name);
		pListElement->SetText(2, user_arr[0].dev_name);
		c_page_utils::set_page_info(&page_info, 19, 1, 1);
	}
	else {
		c_page_utils::set_page_info(&page_info, 19, 0, 1);
		init_data();
	}
#endif
}


void CUsrManageWnd::InitWindow() {
	CenterWindow();
	this->init_data();
}



void CUsrManageWnd::Notify(TNotifyUI& msg) {
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
		int clicked_user_num = i_index + page_info.get_begin_index();

		// 如果是当前设备的用户，则运行操作
		//if (!strcmp(user_arr[clicked_user_num].dev_name, g_dev_name.c_str())) {
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		CUserManageMenuWnd *p_menu = new CUserManageMenuWnd(_T("Menu/menu2.xml"), i_index);
		p_menu->Init(g_usr_manage_win_hwnd, pt);
		p_menu->ShowWindow(TRUE);
		//}
		//else {
		//	MessageBox(NULL, "非当前设备用户，无法操作", NULL, NULL);
		//}
	}
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("search_btn")) {
			CControlUI* ctrl = m_PaintManager.FindControl(_T("search_txt"));
			string  str = ctrl->GetText().ToString();
			init_data_after_search(str.c_str());
#if 0
			pList->RemoveAll();
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(0);
			pList->Add(pListElement);

			pListElement->SetText(0, str.c_str());
			pListElement->SetText(1, str.c_str());
#endif
		}
		if (msg.pSender->GetName() == _T("register_btn")) {
			createAddUserWin();
			this->init_data();
		}
		if (msg.pSender->GetName() == _T("first_page_btn")) {
			if (page_info.is_has_pre_page()) {
				c_page_utils::get_first_page(&page_info);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("pre_page_btn")) {
			if (page_info.is_has_pre_page()) {
				c_page_utils::get_pre_page(&page_info);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("next_page_btn")) {
			if (page_info.is_has_next_page()) {
				c_page_utils::get_next_page(&page_info);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("last_page_btn")) {
			if (page_info.is_has_next_page()) {
				c_page_utils::get_last_page(&page_info);
				this->init_data_after_flip_page();
			}
		}
	}
	__super::Notify(msg);
}


CControlUI* CUsrManageWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}

/**
 *   sonne 2018-03-07
 *   create a window to manage users.
 */
void  create_usrmanage_win(HINSTANCE hInstance,HWND par_hwnd,bool bIsCurrentUsersManage) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(hInstance);

	g_uiUserManageWin = new CUsrManageWnd(_T("user_manage.xml"), hInstance, bIsCurrentUsersManage);
	g_usr_manage_win_hwnd = g_uiUserManageWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	g_uiUserManageWin->ShowModal();
	delete g_uiUserManageWin;
	if (pUserSelArr != NULL) {
		delete[] pUserSelArr;
		pUserSelArr = NULL;
	}
	::CoUninitialize();
}