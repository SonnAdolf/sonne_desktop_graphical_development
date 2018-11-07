#include "EditUser.h"

extern HINSTANCE g_hInst;
string g_strInptEditName;
CEditUserWnd *p_cEditUserWin;


CEditUserWnd::CEditUserWnd(LPCTSTR pszXMLPath, string strUsername, string strUserId)
	: CXMLWnd(pszXMLPath) {
	this->strUserId = strUserId;
	this->strUsername = strUsername;
}


void CEditUserWnd::InitWindow() {
	CenterWindow();
	CEditUI* inpt_name
		= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
	inpt_name->SetText(this->strUsername.c_str());
}


void CEditUserWnd::OnFinalMessage(HWND hWnd) {
	__super::OnFinalMessage(hWnd);
}


void CEditUserWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("EDIT")) {
			// 获取输入的证书名
			CEditUI* inpt_name
				= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
			g_strInptEditName = inpt_name->GetText().ToString();
			int iInptStrLen = g_strInptEditName.length();

			if (iInptStrLen == 0) {
				MessageBox(NULL, "请输入用户名", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (STROPERATION::isStrIllegal2(g_strInptEditName.c_str())) {
				MessageBox(NULL, "输入的用户名中含有非法字符", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (iInptStrLen > MAX_USERNAME_LEN) {
				MessageBox(NULL, "您输入的用户名超过长度限制", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (checkIfUserOfNameExsit(g_strInptEditName)) {
				MessageBox(NULL, "您输入的用户名已存在", NULL, MB_SYSTEMMODAL);
				return;
			}
			editUserName(STROPERATION::ASCII2UTF_8(g_strInptEditName),this->strUserId);
			this->Close();
		}
	}
	__super::Notify(msg);
}


CControlUI* CEditUserWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


void  createEditUserWin(string strUsername, string strUserId) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	p_cEditUserWin = new CEditUserWnd(_T("edit_user.xml"), strUsername, strUserId);
	p_cEditUserWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	p_cEditUserWin->ShowModal();
	delete p_cEditUserWin;
	p_cEditUserWin = NULL;
	::CoUninitialize();
}