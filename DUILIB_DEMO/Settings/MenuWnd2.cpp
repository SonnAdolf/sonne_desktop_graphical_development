#include "MenuWnd2.h"

extern c_page_info page_info;
extern P_USER_INFO_SEL pUserSelArr;
extern CUsrManageWnd *g_uiUserManageWin;
extern char g_chLoginAdminName[255];

CUserManageMenuWnd::CUserManageMenuWnd( LPCTSTR pszXMLPath, int tag) 
: CXMLWnd(pszXMLPath){
	this->tag = tag;
	this->iNewWinNum = 0;
}

CUserManageMenuWnd::~CUserManageMenuWnd(){
}

void CUserManageMenuWnd::Init( HWND hWndParent, POINT ptPos ){
    Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    ::ClientToScreen(hWndParent, &ptPos);
    ::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CUserManageMenuWnd::OnFinalMessage( HWND /*hWnd*/ ) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CUserManageMenuWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;

    switch( uMsg )
    {
    case WM_KILLFOCUS:    
        lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); 
        break; 


    default:
        bHandled = FALSE;
    }

    if(bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) 
    {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}


//DWORD writeCertsUsers(LPVOID lpParameter) {
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


void CUserManageMenuWnd::Notify(TNotifyUI& msg) {
	int num;
	string user_id;
	string username;
	if (msg.sType == _T("itemclick")) {
		num = page_info.get_begin_index() + this->tag;
		user_id = pUserSelArr[num].id;
		username = pUserSelArr[num].name;

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
		if( !click_menu_option.compare(_T("edit")) ) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				createEditUserWin(username,user_id);
				g_uiUserManageWin->InitWindow();
			}
			iNewWinNum++;
		}

		/*
		 *  删除数据库中该用户数据，包括指静脉和与证书关系
		 */
		if (!click_menu_option.compare(_T("delete"))) {
			if (iNewWinNum == 0) {
				int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "删除用户", MB_OKCANCEL | MB_SYSTEMMODAL);
				if (ret == IDOK) {
					if (!deleteUserWithFingers(user_id)) {
						MessageBox(NULL, "删除失败，删除用户表失败", "删除用户", NULL);
						return;
					}
					if (!deleteUserCertByUserId(user_id)) {
						MessageBox(NULL, "删除失败，删除用户证书关系表失败", "删除用户", NULL);
						return;
					}
					char str_log[300] = "delete user";
					strcat(str_log, username.c_str());
					MYLOG::write_log(str_log, DEL_USER_LOG, g_chLoginAdminName);
					g_uiUserManageWin->InitWindow();
				}
			}
			iNewWinNum++;
		}
	}
	__super::Notify(msg);
}

LRESULT CUserManageMenuWnd::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
    Close();
	
    bHandled = FALSE;
    return __super::OnKillFocus(uMsg, wParam, lParam, bHandled); 
}
