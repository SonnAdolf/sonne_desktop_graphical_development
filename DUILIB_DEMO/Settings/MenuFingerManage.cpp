#include "MenuFingerManage.h"

extern CFingerManageWnd *g_uiFingerManageWin;
extern char g_chLoginAdminName[255];
extern bool gIsManageCurDev;

CMenuFingerManageWnd::CMenuFingerManageWnd(LPCTSTR pszXMLPath, string id, string name, string userId)
	: CXMLWnd(pszXMLPath) {
	this->iNewWinNum = 0;
	this->id = id;
	this->name = name;
	this->userId = userId;
}

CMenuFingerManageWnd::~CMenuFingerManageWnd() {

}

void CMenuFingerManageWnd::Init(HWND hWndParent, POINT ptPos) {
	Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CMenuFingerManageWnd::OnFinalMessage(HWND /*hWnd*/) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CMenuFingerManageWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
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

void CMenuFingerManageWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("itemclick")) {
		if (msg.pSender->GetName() == _T("menu_edit")) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				createEditFingerNameWin(this->id,this->name);
				g_uiFingerManageWin->InitWindow();
			}
			iNewWinNum++;
		}
		if (msg.pSender->GetName() == _T("menu_delete")) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "删除用户指静脉", MB_OKCANCEL| MB_SYSTEMMODAL);
				if (ret == IDOK) {
					string userAndFingerId = userId.append("_").append(name);
					// 如果是管理当前设备用户，则同时删除设备指静脉
					if (gIsManageCurDev) 
						ret = del_single_finger(userAndFingerId.c_str());
					deleteFinger(id);
					MessageBox(NULL, "删除指静脉成功", "结果", MB_TOPMOST);
					char chLimitedFingerName[10];
					STROPERATION::str_len_limit(chLimitedFingerName, this->name.c_str());
					char str_log[100] = "delete finger[";
					strcat(str_log, chLimitedFingerName);
					strcat(str_log, "].");
					MYLOG::write_log(str_log, DEL_FINGER_LOG, g_chLoginAdminName);

					g_uiFingerManageWin->InitWindow();
				}
			}
			iNewWinNum++;
		}
	}
}

LRESULT CMenuFingerManageWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	Close();
	bHandled = FALSE;
	return __super::OnKillFocus(uMsg, wParam, lParam, bHandled);
}
