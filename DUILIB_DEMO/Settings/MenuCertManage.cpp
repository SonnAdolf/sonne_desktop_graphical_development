#include "MenuCertManage.h"

extern CCertsWnd *g_uiCertsWnd;
extern char g_chLoginAdminName[255];


CMenuCertManageWnd::CMenuCertManageWnd(LPCTSTR pszXMLPath, string id, string name, string content, string date, string type)
	: CXMLWnd(pszXMLPath) {
	this->iNewWinNum = 0;
	this->id = id;
	this->name = name;
	this->content = content;
	this->date = date;
	this->type = type;
}

CMenuCertManageWnd::~CMenuCertManageWnd() {
}

void CMenuCertManageWnd::Init(HWND hWndParent, POINT ptPos) {
	Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CMenuCertManageWnd::OnFinalMessage(HWND /*hWnd*/) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CMenuCertManageWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch (uMsg) {
	case WM_KILLFOCUS:
		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		break;

	default:
		bHandled = FALSE;
	}

	if (bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		return lRes;

	return __super::HandleMessage(uMsg, wParam, lParam);
}


//DWORD writeCertsUsers_Certs(LPVOID lpParameter) {
//	DWORD iWritingRet;
//	int ret
//		= MessageBoxA(NULL, "确认写入证书和用户？写入过程需要几秒钟，写入完成前请不要关闭界面。", "写入", MB_OKCANCEL | MB_SYSTEMMODAL);
//	if (ret == IDOK) {
//		//btnClose->SetEnabled(false);
//		iWritingRet = CEncryptionUtils::write_user_certs();
//		//btnClose->SetEnabled(true);
//	}
//	if (iWritingRet == OK) {
//		//MessageBox(NULL, "删除证书成功", "结果", MB_TOPMOST);
//		g_uiCertsWnd->InitWindow();
//	}
//	else {
//		MessageBox(NULL, "写入失败结果",NULL, MB_TOPMOST);
//	}
//	return iWritingRet;
//}


void CMenuCertManageWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("itemclick")) {
		if (msg.pSender->GetName() == _T("menu_edit")) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				createEditCertWin(this->id,this->name,this->content,this->date,this->type);
				g_uiCertsWnd->InitWindow();
			}
			iNewWinNum++;
		}
		if (msg.pSender->GetName() == _T("menu_delete")) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "删除用户证书", MB_OKCANCEL | MB_SYSTEMMODAL);
				if (ret == IDOK) {
					//ret = MYSQL_INTERFACES::deleteCert(id);
					//ret = deleteCert(id);
#if 0
					if (deleteCert(id)) {
						//CEncryptionUtils::write_user_certs();
						CreateThread(NULL, NULL, writeCertsUsers_Certs, NULL, NULL, NULL);

						char str_log[100] = "delete cert ";
						strcat(str_log, this->name.c_str());

						MYLOG::write_log(str_log, DEL_CERT_LOG, g_chLoginAdminName);
					}
					else
						MessageBox(NULL, "删除证书失败", "结果", MB_TOPMOST);
#endif
					deleteCert(id);
					g_uiCertsWnd->InitWindow();
					char str_log[100] = "delete cert ";
					strcat(str_log, this->name.c_str());

					MYLOG::write_log(str_log, DEL_CERT_LOG, g_chLoginAdminName);
				}
			}
			iNewWinNum++;
		}
	}
}

LRESULT CMenuCertManageWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	Close();
	bHandled = FALSE;
	return __super::OnKillFocus(uMsg, wParam, lParam, bHandled);
}
