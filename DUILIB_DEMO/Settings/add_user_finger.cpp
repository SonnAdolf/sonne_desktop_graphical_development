#include "add_user_finger.h"

extern HINSTANCE g_hInst;
 HWND g_adduser_hwnd;
 extern CListUI* g_fingers_lst;
 extern int g_fingers_num;
 extern char g_chLoginAdminName[255];
 extern CFingerManageWnd *g_uiFingerManageWin;
 bool bIsAddingFinger = false;
 extern CUsrManageWnd *g_uiUserManageWin;

 extern bool gIsManageCurDev;

CAddFingerWnd::CAddFingerWnd( LPCTSTR pszXMLPath, string user_id, string username)
: CXMLWnd(pszXMLPath) {
	this->user_id = user_id;
	this->username = username;
}


void CAddFingerWnd::InitWindow() {
	CenterWindow();
}


void CAddFingerWnd::OnFinalMessage(HWND hWnd) {
     __super::OnFinalMessage(hWnd);
}


string  f_name;
int add_f_c_num;
char *add_f_buf;
SW_CERT* add_f_certs;
string add_f_username;
string add_f_userid;
CAddFingerWnd* class_p;


DWORD WINAPI add_user_thread(LPVOID lpParameter) {
	// 本demo只展示界面，该函数内容屏蔽
	return TRUE;
}


void CAddFingerWnd::Notify( TNotifyUI& msg ) {
    if( msg.sType == _T("click") ) {
        if( msg.pSender->GetName() == _T("add") ) {
			if (bIsAddingFinger)
				return;
			bIsAddingFinger = true;
			CControlUI* ctrl = m_PaintManager.FindControl(_T("content"));

			// 全局变量初始化，用于做回调函数，参数
			f_name = ctrl->GetText().ToString();
			if (f_name.empty()) {
				MessageBox(NULL, "请输入指静脉名", NULL, MB_SYSTEMMODAL);
				return;
			}
			if (STROPERATION::isStrIllegal2(f_name.c_str())) {
				MessageBox(NULL, "输入的指静脉名中含有非法字符", NULL, MB_SYSTEMMODAL);
				return;
			}
			if (f_name.length() > 20) {
				MessageBox(NULL, "输入的指静脉名称过长", NULL, MB_SYSTEMMODAL);
				return;
			}
			if (searchUserFingersNum(this->user_id) > 8) {
				MessageBox(NULL, "该用户注册指静脉数已达上限8", NULL, MB_SYSTEMMODAL);
				return;
			}
			//if (MYSQL_INTERFACES::inptFingerNameExits(f_name.c_str())) {
			//	MessageBox(NULL, "输入的指静脉名称已存在", NULL, MB_SYSTEMMODAL);
			//	return;
			//}
			//add_f_certs = MYSQL_INTERFACES::select_certs_of_user("", this->user_id, &add_f_c_num);
			//selCertsOfUser(&add_f_certs, this->user_id, &add_f_c_num);
			add_f_username = this->username;
			add_f_userid = this->user_id;
			class_p = this;
			//is_add_f_thread_end = FALSE;

			CreateThread(NULL, NULL, add_user_thread, NULL, NULL, NULL);
		}
    }
	__super::Notify(msg);
}


CControlUI* CAddFingerWnd::CreateControl( LPCTSTR pstrClassName ) {
    return NULL;
}



void  create_add_user_finger_win(string user_id,string username) {
   ::CoInitialize(NULL);
    CPaintManagerUI::SetInstance(g_hInst);

    CAddFingerWnd *pFrame = new CAddFingerWnd(_T("add_finger.xml"),user_id,username);
    g_adduser_hwnd = pFrame->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG,WS_EX_TOPMOST);//WS_EX_WINDOWEDGE);// WS_EX_TOPMOST);
    pFrame->ShowModal();
	delete pFrame;
    ::CoUninitialize();
}