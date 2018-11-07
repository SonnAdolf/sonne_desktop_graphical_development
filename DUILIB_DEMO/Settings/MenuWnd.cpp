#include "MenuWnd.h"

extern c_page_info dev_page_info;
extern dev_sel_ret* dev_arr;
extern HINSTANCE g_hInst;
extern HWND g_dev_manage_win_hwnd;
extern int is_delete;
extern CDevManageWnd *g_dev_win;

CMenuWnd::CMenuWnd( LPCTSTR pszXMLPath , int tag) 
: CXMLWnd(pszXMLPath){
	this->iNewWinNum = 0;
	this->tag = tag;
}

CMenuWnd::~CMenuWnd() {

}

void CMenuWnd::Init( HWND hWndParent, POINT ptPos ) {
    Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    ::ClientToScreen(hWndParent, &ptPos);
    ::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CMenuWnd::OnFinalMessage( HWND /*hWnd*/ ) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CMenuWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;

    switch( uMsg ){
    case WM_KILLFOCUS:    
        lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); 
        break; 

    default:
        bHandled = FALSE;
    }

    if(bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) 
        return lRes;

    return __super::HandleMessage(uMsg, wParam, lParam);
}

void CMenuWnd::Notify( TNotifyUI& msg ) {
	int num;
    if( msg.sType == _T("itemclick") )  {
#if 0 
		if( msg.pSender->GetName() == _T("menu_check") ) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				num = dev_page_info.get_begin_index() + this->tag;
				
				//MessageBox(NULL, msg.pSender->GetName(), NULL, NULL);
			}
			iNewWinNum++; 
		}
#endif
		num = dev_page_info.get_begin_index() + this->tag;
		dev_sel_ret dev = dev_arr[num];
        if( msg.pSender->GetName() == _T("menu_edit") ) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				//create_edit_dev_win(&dev);
			}
			iNewWinNum++; 
		}
        if( msg.pSender->GetName() == _T("menu_delete") ) {
#if 0
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "É¾³ýÉè±¸", MB_OKCANCEL | MB_SYSTEMMODAL);
				if (ret == IDOK) {
					MYSQL_INTERFACES::delete_dev(dev.id);
					g_dev_win->init_data();
				}
			}
			iNewWinNum++; 
#endif
		}
	}
}

LRESULT CMenuWnd::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
    Close();
    bHandled = FALSE;
    return __super::OnKillFocus(uMsg, wParam, lParam, bHandled); 
}
