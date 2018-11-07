#include "add_user1.h"


CAddUserWnd::CAddUserWnd(LPCTSTR pszXMLPath)
	: CXMLWnd(pszXMLPath) {
}


void CAddUserWnd::InitWindow() {
	CenterWindow();
}


void CAddUserWnd::OnFinalMessage(HWND hWnd) {
	__super::OnFinalMessage(hWnd);
}


void CAddUserWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("add")) {
			// 获取输入的证书名
			CEditUI* inpt_name
				= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
			strInptUserName = inpt_name->GetText().ToString();
			int iInptStrLen = strInptUserName.length();

			if (iInptStrLen == 0) {
				MessageBox(NULL, "请输入用户名", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (STROPERATION::isStrIllegal2(strInptUserName.c_str())) {
				MessageBox(NULL, "输入的用户名中含有非法字符", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (iInptStrLen > MAX_USERNAME_LEN) {
				MessageBox(NULL, "您输入的用户名超过长度限制", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (checkIfUserOfNameExsit(strInptUserName)) {
				MessageBox(NULL, "您输入的用户名已存在", NULL, MB_SYSTEMMODAL);
				return;
			}
			char chLimitedFingerName[10];
			char str_log[100] = "add user[";
			STROPERATION::str_len_limit(chLimitedFingerName, strInptUserName.c_str());
			strcat(str_log, chLimitedFingerName);
			strcat(str_log, "].");
			MYLOG::write_log(str_log, ADD_USER_LOG, g_chLoginAdminName);
			//MYSQL_INTERFACES::add_user(strInptUserName);
			addUser(strInptUserName);
			Close(IDOK);
		}
	}
	__super::Notify(msg);
}


CControlUI* CAddUserWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


void  createAddUserWin() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	CAddUserWnd *p_cAddUserWin = new CAddUserWnd(_T("add_user.xml"));
	HWND hwnd = p_cAddUserWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	p_cAddUserWin->ShowModal();
	//delete p_cAddUserWin;
	//p_cAddUserWin = NULL;
	::CoUninitialize();
}