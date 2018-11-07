
#include "sel_user_impt.h"

using namespace std;

extern HINSTANCE g_hInst;
c_page_info cPageUsersOfNoDevInfo;
list<user_sel_ret> selUserOfNoDevlist;
HWND hwndSelUsersImpt;
//SW_CERT2* pCertsOfDev;
user_sel_ret* usersOfNoDev;
extern char g_chLoginAdminName[255];
CControlUI * btnSelUserImptOk;
//bool g_bIsCertManage = FALSE;
bool bIsImptUsers = false;
CProgressUI* g_pUiProgress;

/**
*   sonne 2018-09-13
*   create a window to select user to import into device.
*/
void  createSelUsersImptWin() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	CSelUserImptWnd *win = new CSelUserImptWnd(_T("sel_user_impt.xml"));
	hwndSelUsersImpt = win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	win->ShowModal();

	delete win;
	::CoUninitialize();
}


CSelUserImptWnd::CSelUserImptWnd(LPCTSTR xml_path)
	: CXMLWnd(xml_path) {
}


void CSelUserImptWnd::set_checkbox_visible(int n, bool visible) {
	char str[20] = "CheckBox";
	char str_num[10];
	itoa(n, str_num, 10);
	strcat(str, str_num);
	CCheckBoxUI* checkbox1 = static_cast<CCheckBoxUI*> (m_PaintManager.FindControl(str));
	if (visible)
		checkbox1->SetVisible(true);
	else
		checkbox1->SetVisible(false);
}


void CSelUserImptWnd::set_checkbox(int n, char* str_val) {
	char str[20] = "CheckBox";
	char str_num[10];
	itoa(n, str_num, 10);
	strcat(str, str_num);
	CCheckBoxUI* checkbox1 = static_cast<CCheckBoxUI*> (m_PaintManager.FindControl(str));
	checkbox1->Selected(false);
	if (str_val == NULL)
		return;
	if (str_val[0] == '\0')
		return;
	if (strlen(str_val) == 0)
		return;
	checkbox1->SetText(str_val);
	checkbox1->SetVisible(true);
}


void CSelUserImptWnd::init_data() {
	int num = getNumOfNoDevUsers();
	cPageUsersOfNoDevInfo = c_page_utils::create_page(18, num, 1);
	selUsersOfNoDev(&usersOfNoDev, cPageUsersOfNoDevInfo);
	selUserOfNoDevlist.clear();
	g_pUiProgress = static_cast<CProgressUI*>(m_PaintManager.FindControl(_T("PROGRESS")));
	//pProgress->SetValue(0);
	btnSelUserImptOk = m_PaintManager.FindControl(_T("ok"));;
	int iUserNumPage
		= cPageUsersOfNoDevInfo.get_total_count() - cPageUsersOfNoDevInfo.get_begin_index();
	if (iUserNumPage > 18)
		iUserNumPage = 18;
	for (int i = 0; i < 18; i++) {
		if (i < iUserNumPage)
			// 设置界面上checkbox值
			set_checkbox(i + 1, usersOfNoDev[i].name);
		// 删除界面上多余的UI
		if (i >= iUserNumPage) {
			set_checkbox_visible(i + 1, false);
		}
	}
}


void CSelUserImptWnd::init_data_after_flip_page() {
	selUsersOfNoDev(&usersOfNoDev, cPageUsersOfNoDevInfo);
	int iUserNumPage
		= cPageUsersOfNoDevInfo.get_total_count() - cPageUsersOfNoDevInfo.get_begin_index();
	if (iUserNumPage > 18)
		iUserNumPage = 18;
	for (int i = 0; i < 18; i++) {
		if (i < iUserNumPage) {
			// 设置界面上checkbox值
			set_checkbox(i + 1, usersOfNoDev[i].name);
			set_checkbox_visible(i + 1, true);
		}
		// 删除界面上多余的UI
		if (i >= iUserNumPage) {
			set_checkbox_visible(i + 1, false);
		}
	}
}


void CSelUserImptWnd::InitWindow() {
	CenterWindow();
	init_data();
}


void removeUserLstByName(const char* name) {
	// 遍历、查找、删除
	for (list<user_sel_ret>::iterator iter = selUserOfNoDevlist.begin(); iter != selUserOfNoDevlist.end(); iter++) {
		if (!strcmp(iter->name, name)) {
			selUserOfNoDevlist.erase(iter);
			break;
		}
	}
}


void CSelUserImptWnd::checkbox_notify_func(int n, const char* msg_name) {
	char str_checkbox[20] = "CheckBox";
	char str_num[10];
	itoa(n, str_num, 10);
	strcat(str_checkbox, str_num);
	if (!strcmp(msg_name, str_checkbox)) {
		CCheckBoxUI* checkbox1 = static_cast<CCheckBoxUI*> (m_PaintManager.FindControl(str_checkbox));
		if (!checkbox1->IsSelected()) {
			user_sel_ret* user;
			selectUsersByName(&user, checkbox1->GetText());
			selUserOfNoDevlist.push_back(*user);
		}
		else {
			removeUserLstByName(std::string(checkbox1->GetText().GetData()).c_str());
		}
	}
}


DWORD imptFunc(LPVOID lpParameter) {
	//  导入操作
	setUserListDeiviceId(selUserOfNoDevlist);

	int iUserNum = selUserOfNoDevlist.size();
	P_USER_DATA pUsers = new USER_DATA[iUserNum];
	selUsersFingers(selUserOfNoDevlist, pUsers);
	// 导入用户指静脉
	imptUserFingersBegin(iUserNum);
	int iProgressSize = 100 / iUserNum;
	g_pUiProgress->SetValue(0);
	for (int i = 0; i < iUserNum; i++) {
		imptUsersFingers(&pUsers[i]);
		g_pUiProgress->SetValue(i*iProgressSize);
	}
	imptUserFingersEnd(iUserNum);
	g_pUiProgress->SetValue(100);
	//CEncryptionUtils::writeCertsUsers(0);
	bIsImptUsers = false;
	MessageBoxA(NULL, "导入成功", "成功", MB_SYSTEMMODAL);
	SendMessage(hwndSelUsersImpt, WM_CLOSE, 0, 0);
	return 0;
}


void CSelUserImptWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		//if (msg.pSender->GetName() == _T("add")) {
		//	//MessageBox(NULL, NULL, _T("提示(by tojen)"), MB_OK);  
		//	create_add_cert_win(this->user_id, NULL);
		//}
		if (msg.pSender->GetName() == _T("ok")) {
			//if (selCertsLst.size() > 16) {
			//	MessageBox(NULL, "最多选择16个证书", NULL, MB_TOPMOST);
			//	return;
			//}
			//CreateCertuserMany2Many(selCertsLst, this->user_id);
			//char str_log[200] = "configure certs of ";
			//strcat(str_log, this->user_id.c_str());
			//MYLOG::write_log(str_log, CONFIGURE_CERTS_LOG, g_chLoginAdminName);
			//g_bIsCertManage = TRUE;
			//CreateThread(NULL, NULL, CEncryptionUtils::writeCertsUsers, NULL, NULL, NULL);

			//for (list<user_sel_ret>::iterator iter = selUserOfNoDevlist.begin(); iter != selUserOfNoDevlist.end(); iter++) {
			//	if (!strcmp(iter->name, name)) {
			//		selUserOfNoDevlist.erase(iter);
			//		break;
			//	}
			//}
			if (bIsImptUsers)
				return;
			bIsImptUsers = true;

			if (selUserOfNoDevlist.size() > 0) {
				MessageBox(NULL, "开始导入，导入用户较多时可能需要一段时间，中途请勿关闭界面", "开始导入", MB_TOPMOST);
				////  导入操作
				//setUserListDeiviceId(selUserOfNoDevlist);

				//int iUserNum = selUserOfNoDevlist.size();
				//P_USER_DATA pUsers = new USER_DATA[iUserNum];
				//selUsersFingers(selUserOfNoDevlist, pUsers);
				//// 导入用户指静脉
				//imptUsersFingers(pUsers, iUserNum);
				//CreateThread(NULL, NULL, CEncryptionUtils::writeCertsUsers, NULL, NULL, NULL);
				CreateThread(NULL, NULL, imptFunc, NULL, NULL, NULL);
			}
		}
		if (msg.pSender->GetName() == _T("first_page_btn")) {
			if (cPageUsersOfNoDevInfo.is_has_pre_page()) {
				c_page_utils::get_first_page(&cPageUsersOfNoDevInfo);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("pre_page_btn")) {
			if (cPageUsersOfNoDevInfo.is_has_pre_page()) {
				c_page_utils::get_pre_page(&cPageUsersOfNoDevInfo);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("next_page_btn")) {
			if (cPageUsersOfNoDevInfo.is_has_next_page()) {
				c_page_utils::get_next_page(&cPageUsersOfNoDevInfo);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("last_page_btn")) {
			if (cPageUsersOfNoDevInfo.is_has_next_page()) {
				c_page_utils::get_last_page(&cPageUsersOfNoDevInfo);
				this->init_data_after_flip_page();
			}
		}
		for (int i = 1; i < 19; i++)
			checkbox_notify_func(i, std::string(msg.pSender->GetName().GetData()).c_str());
	}
	__super::Notify(msg);
}


CControlUI* CSelUserImptWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}