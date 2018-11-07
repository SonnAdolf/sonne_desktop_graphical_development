#include "CurUserManageMenuWnd.h"

extern c_page_info page_info;
//extern user_sel_ret* user_arr;
extern CUsrManageWnd *g_uiUserManageWin; 
extern char g_chLoginAdminName[255];

CCurUserManageMenuWnd::CCurUserManageMenuWnd(LPCTSTR pszXMLPath, int tag, PSW_USER pUsers, FINAL_PSW_CERT pCerts, int iUserNum, int iCertNum, USER_INFO usersFingersInfo)
	: CXMLWnd(pszXMLPath) {
	this->tag = tag;
	this->iNewWinNum = 0;
	this->usersFingersInfo = usersFingersInfo;
	this->pCerts = pCerts;
	this->pUsers = pUsers;
	this->iUserNum = iUserNum;
	this->iCertNum = iCertNum;
}

CCurUserManageMenuWnd::~CCurUserManageMenuWnd() {
}

void CCurUserManageMenuWnd::Init(HWND hWndParent, POINT ptPos) {
	Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CCurUserManageMenuWnd::OnFinalMessage(HWND /*hWnd*/) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CCurUserManageMenuWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		break;


	default:
		bHandled = FALSE;
	}

	if (bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}



//DWORD writeCertsUsers2(LPVOID lpParameter) {
//	DWORD iWritingRet;
//	int ret
//		= MessageBoxA(NULL, "确认写入证书和用户？写入过程需要几秒钟，写入完成前请不要关闭界面。", "写入", MB_OKCANCEL | MB_SYSTEMMODAL);
//	if (ret == IDOK) {
//		//btnClose->SetEnabled(false);
//		iWritingRet = CEncryptionUtils::write_user_certs();
//		//btnClose->SetEnabled(true);
//	}
//	if (iWritingRet == OK)
//		g_uiUserManageWin->InitWindow();
//	else
//		MessageBoxA(NULL, "写入错误", "写入", MB_SYSTEMMODAL);
//	return iWritingRet;
//}


void CCurUserManageMenuWnd::Notify(TNotifyUI& msg) {
	int num;
	string user_id;
	string username;
	if (msg.sType == _T("itemclick")) {
		num = this->tag;
		string click_menu_option = msg.pSender->GetName().ToString();
		if (!click_menu_option.compare(_T("check_certs"))) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				//num = page_info.get_begin_index() + this->tag;
				//create_cur_cert_manage_win();
				createCurDevCertsWin(this->pUsers[num],this->pCerts,this->iCertNum);
			}
			iNewWinNum++;
		}
		if (!click_menu_option.compare(_T("check_fingers"))) {
			if (iNewWinNum == 0) {
				createCheckCurDevFingersWin(this->usersFingersInfo);
			}
			iNewWinNum++;
		}
		if (!click_menu_option.compare(_T("delete"))) {
			if (iNewWinNum == 0) {
			}
			iNewWinNum++;
		}
#if 0
		num = this->tag;
		//user_id = user_arr[num].id;
		//username = user_arr[num].name;

		//if (!MYSQL_INTERFACES::ifUserOfDevExits(user_id)) {
		//	if (iNewWinNum == 0) {
		//		MessageBox(NULL, "非当前设备用户，无法操作", NULL, NULL);
		//		iNewWinNum++;
		//		return;
		//	}
		//}
		string click_menu_option = msg.pSender->GetName().ToString();
		if (!click_menu_option.compare(_T("check_certs"))) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				//num = page_info.get_begin_index() + this->tag;
				create_cert_manage_win(user_id);
			}
			iNewWinNum++;
		}
#if 0
		if (!click_menu_option.compare(_T("check_devs"))) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				num = page_info.get_begin_index() + this->tag;
				user_id = user_arr[num].id;
				devs = MYSQL_INTERFACES::select_devs_of_user("", &dev_num, user_id);
				// 显示该用户设备列表
				create_usr_dev_lst_win(dev_num, devs);
			}
			iNewWinNum++;
		}
#endif
		if (!click_menu_option.compare(_T("check_fingers"))) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				//num = page_info.get_begin_index() + this->tag;

				create_finger_manage_win(user_id, username);
			}
			iNewWinNum++;
		}
		//if( !click_menu_option.compare(_T("edit")) ) {
		//	cout << "hh";//MessageBox(NULL, msg.pSender->GetName(), NULL, NULL);
		//}
		if (!click_menu_option.compare(_T("delete"))) {
			if (iNewWinNum == 0) {
				int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "删除用户", MB_OKCANCEL | MB_SYSTEMMODAL);
				if (ret == IDOK) {
					//if (MYSQL_INTERFACES::deleteUserWithFingers(user_id) != OK) {
					if (!deleteUserWithFingers(user_id)) {
						MessageBox(NULL, "删除失败，删除用户表失败", "删除用户", NULL);
						return;
					}
					//if (MYSQL_INTERFACES::deleteUserCertByUserId(user_id) != OK) {
					if (!deleteUserCertByUserId(user_id)) {
						MessageBox(NULL, "删除失败，删除用户证书关系表失败", "删除用户", NULL);
						return;
					}
					//CEncryptionUtils::write_user_certs();
					//CreateThread(NULL, NULL, writeCertsUsers, NULL, NULL, NULL);
					//if (delUserFingers((char*)user_id.c_str())!=OK) {
					//	MessageBox(NULL, "删除失败，删除设备指静脉失败", "删除用户", NULL);
					//	return;
					//}
					//MessageBox(NULL, "删除完成", "删除用户", NULL);
					char str_log[300] = "delete user";
					strcat(str_log, username.c_str());
					MYLOG::write_log(str_log, DEL_USER_LOG, g_chLoginAdminName);
				}
			}
			iNewWinNum++;
		}
#endif
	}
	__super::Notify(msg);
}

LRESULT CCurUserManageMenuWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	Close();

	bHandled = FALSE;
	return __super::OnKillFocus(uMsg, wParam, lParam, bHandled);
}
