#include "admins.h"

CListUI* admins_lst;
extern HINSTANCE g_hInst;
CAdminManageWnd *g_admin_win;
HWND g_admin_hwnd;
extern wchar_t * input_usrname;
sel_admin_ret3 admins;
int g_iAdminsNum;

CAdminManageWnd::CAdminManageWnd( LPCTSTR pszXMLPath)
	: CXMLWnd(pszXMLPath) {
}

void CAdminManageWnd::init_data() {
	// ³õÊ¼»¯CListUI¿Ø¼þ
	CDuiString str;
	admins_lst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	admins_lst->RemoveAll();
	//admins = MYSQL_INTERFACES::sel_admins("");
	//sel_admin_ret3 admins;
	selAllAdminsToShowInList(&admins);

	g_iAdminsNum = admins.num;


	for (int i = 0; i < g_iAdminsNum; i++) {
		CListTextElementUI* ele = new CListTextElementUI;
		ele->SetTag(i);
		admins_lst->Add(ele);

		str.Format(_T("%d"), i);
		//name2 = CA2W(admins.usrnames[i].c_str(), CP_UTF8);
		//chName = STROPERATION::WcharToChar(name2.c_str());
		ele->SetText(0, admins.usrnames[i].c_str());
		ele->SetText(1, admins.dates[i].c_str());
		//free(chName);
	}
}


void CAdminManageWnd::InitWindow() {
	CenterWindow();
	this->init_data();
}


void CAdminManageWnd::Notify( TNotifyUI& msg ) {
	if(msg.sType == _T("itemclick"))  {  
		int i_index = msg.pSender->GetTag();
		POINT pt = {msg.ptMouse.x, msg.ptMouse.y};
        CMenuWnd4 *p_menu = new CMenuWnd4(_T("Menu/menu4.xml"), i_index);
		p_menu->Init(g_admin_hwnd, pt);
        p_menu->ShowWindow(TRUE);
	}  
	if(msg.sType == _T("click")) {
		//if (msg.pSender->GetName() == _T("search_btn"))  {
		//	CControlUI* ctrl = m_PaintManager.FindControl(_T("search_txt"));
		//	string  str = ctrl->GetText().ToString();
		//}
		if (msg.pSender->GetName() == _T("register_btn")) {
			createAddAdminWin();
		}
	}
	__super::Notify(msg);
}


CControlUI* CAdminManageWnd::CreateControl( LPCTSTR pstrClassName ) {
	return NULL;
}


void  create_usrmanage_win() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	g_admin_win = new CAdminManageWnd(_T("admins.xml"));
	g_admin_hwnd = g_admin_win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	g_admin_win->ShowModal();
	delete g_admin_win;
	g_admin_win = NULL;
	::CoUninitialize();
}