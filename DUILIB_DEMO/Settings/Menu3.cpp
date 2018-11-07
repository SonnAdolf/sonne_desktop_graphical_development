#include "Menu3.h"
#include "my_including.h"
#include "page_info.h"
#include "cert_manage.h"
#include "finger_manage.h"

//extern c_page_info upload_user_page_info;
//extern user_sel_ret* upload_user_arr;

CUploadUserMenuWnd::CUploadUserMenuWnd( LPCTSTR pszXMLPath, int tag) 
: CXMLWnd(pszXMLPath){
	this->tag = tag;
	this->iNewWinNum = 0;
}

CUploadUserMenuWnd::~CUploadUserMenuWnd(){
}

void CUploadUserMenuWnd::Init( HWND hWndParent, POINT ptPos ){
    Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    ::ClientToScreen(hWndParent, &ptPos);
    ::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CUploadUserMenuWnd::OnFinalMessage( HWND /*hWnd*/ ) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CUploadUserMenuWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) {
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

void CUploadUserMenuWnd::Notify( TNotifyUI& msg ) {
	int num;
	string user_id;
	string username;
    if( msg.sType == _T("itemclick") )  {
		string click_menu_option = msg.pSender->GetName().ToString();
#if 0
		if( !click_menu_option.compare(_T("load_one"))) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				num = upload_user_page_info.get_begin_index() + this->tag;
				//user_id = upload_user_arr[num].id;
				int cert_num;
				SW_CERT* certs = MYSQL_INTERFACES::select_certs_of_user("", user_id, &cert_num);
				int f_num = 0;
				sel_finger_ret2* fingers = MYSQL_INTERFACES::select_fingers_of_user2("",upload_user_arr[num].id,&f_num);
				//load_user(certs,fingers,upload_user_arr[num].name,upload_user_arr[num].id,cert_num, f_num);
				//create_cert_manage_win(user_id);
			}
			iNewWinNum++;
		}
#endif
	}
	__super::Notify(msg); 
}

LRESULT CUploadUserMenuWnd::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
    Close();
	
    bHandled = FALSE;
    return __super::OnKillFocus(uMsg, wParam, lParam, bHandled); 
}
