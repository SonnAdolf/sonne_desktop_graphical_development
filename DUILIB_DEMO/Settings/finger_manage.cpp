#include "finger_manage.h"

extern HINSTANCE g_hInst;
extern HWND g_usr_manage_win_hwnd;
CListUI* g_fingers_lst;
sel_finger_ret* finger_arr;
int g_fingers_num = 0;
HWND hwndFingerManage;
CFingerManageWnd *g_uiFingerManageWin; 

/**
 *   sonne 2018-03-14
 *   create a window to manage fingers of a user.
 */
void  create_finger_manage_win(string user_id, string username) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	g_uiFingerManageWin = new CFingerManageWnd(_T("finger_manage.xml"), user_id, username);
	hwndFingerManage = g_uiFingerManageWin->Create(g_usr_manage_win_hwnd, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);//WS_EX_WINDOWEDGE);//WS_EX_TOPMOST);
	g_uiFingerManageWin->ShowModal();
	delete g_uiFingerManageWin;
	g_uiFingerManageWin = NULL;
	::CoUninitialize();
}


CFingerManageWnd::CFingerManageWnd( LPCTSTR xml_path,string user_id,string username)
	: CXMLWnd(xml_path) {
	this->user_id = user_id;
	this->username = username;
}

void CFingerManageWnd::init_data() {
	//int how_many_users = MYSQL_INTERFACES::search_user_num();
	
	// ³õÊ¼»¯CListUI¿Ø¼þ
	CDuiString str;
	g_fingers_lst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	g_fingers_lst->RemoveAll();

	int num;
	//finger_arr =  MYSQL_INTERFACES::select_fingers_of_user("", this->user_id, &num);
	selFingersOfUser(&finger_arr, this->user_id, &num);
	g_fingers_num = num;

	for (int i = 0; i < num; i++) {
		CListTextElementUI* p_lst_element = new CListTextElementUI;
		p_lst_element->SetTag(i);
		g_fingers_lst->Add(p_lst_element);

		str.Format(_T("%d"), i);
		p_lst_element->SetText(0, finger_arr[i].name);
		p_lst_element->SetText(1, finger_arr[i].date);
		//delete p_lst_element;
	}
}


void CFingerManageWnd::InitWindow() {
	CenterWindow();
	init_data();
}


void CFingerManageWnd::Notify( TNotifyUI& msg ) {
	if (msg.sType == _T("itemclick")) {
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		UINT_PTR i_index = msg.pSender->GetTag();
		CMenuFingerManageWnd* menu = new CMenuFingerManageWnd(_T("Menu/MenuFingerManage.xml"), finger_arr[i_index].id, finger_arr[i_index].name, this->user_id);
		menu->Init(hwndFingerManage, pt);
	}
	if(msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("add"))  {
			create_add_user_finger_win(this->user_id,this->username);
		}
	}
	__super::Notify(msg);
}


CControlUI* CFingerManageWnd::CreateControl( LPCTSTR pstrClassName ) {
	return NULL;
}