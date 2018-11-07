#include "MenuWnd3.h"

extern HINSTANCE g_hInst;
extern int is_delete;
extern HWND g_admin_hwnd;
extern sel_admin_ret3 admins;
extern CAdminManageWnd *g_admin_win;
extern char g_chLoginAdminName[255];	

CMenuWnd4::CMenuWnd4( LPCTSTR pszXMLPath , int tag) 
: CXMLWnd(pszXMLPath){
	this->iNewWinNum = 0;
	this->tag = tag;
}

CMenuWnd4::~CMenuWnd4() {

}

void CMenuWnd4::Init( HWND hWndParent, POINT ptPos ) {
    Create(hWndParent, _T("MenuWnd3"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    ::ClientToScreen(hWndParent, &ptPos);
    ::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CMenuWnd4::OnFinalMessage( HWND /*hWnd*/ ) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CMenuWnd4::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;

    switch( uMsg ) {
    case WM_KILLFOCUS:    
        lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); 
        break; 

    default:
        bHandled = FALSE;
    }

    if(bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

void CMenuWnd4::Notify( TNotifyUI& msg ) {
    if( msg.sType == _T("itemclick") )  {
        if( msg.pSender->GetName() == _T("del") ) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "É¾³ý¹ÜÀíÔ±", MB_OKCANCEL | MB_SYSTEMMODAL);
				if (ret == IDOK) {
					//MYSQL_INTERFACES::delete_admin(admins.usrnames[this->tag]);
					addDevSqlite(admins.usrnames[this->tag]);
					char delete_usr_name[10];
					STROPERATION::str_len_limit(delete_usr_name, admins.usrnames[this->tag].c_str());
					char str_log[100] = "deleted manager [";
					strcat(str_log, delete_usr_name);
					strcat(str_log, "].");
					MYLOG::write_log(str_log, 4, g_chLoginAdminName);
					g_admin_win->InitWindow();
				}
			}
			iNewWinNum++; 
		}
	}
}

LRESULT CMenuWnd4::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
    Close();
    bHandled = FALSE;
    return __super::OnKillFocus(uMsg, wParam, lParam, bHandled); 
}
