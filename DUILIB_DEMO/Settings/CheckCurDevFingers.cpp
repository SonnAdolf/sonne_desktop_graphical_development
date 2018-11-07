#include "CheckCurDevFingers.h"

extern HINSTANCE g_hInst;
CListUI* g_curDevFingersLst;
HWND hwndCurDevFingerManage;
CCheckCurDevFingersWnd *g_uiCheckCurDevFingerWin;

/**
*   sonne 2018-03-14
*   create a window to manage fingers of a user.
*/
void    createCheckCurDevFingersWin(USER_INFO pUsersFingersInfo) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	g_uiCheckCurDevFingerWin = new CCheckCurDevFingersWnd(_T("check_cur_dev_user_fingers.xml"), pUsersFingersInfo);
	hwndCurDevFingerManage = g_uiCheckCurDevFingerWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);//WS_EX_WINDOWEDGE);//WS_EX_TOPMOST);
	g_uiCheckCurDevFingerWin->ShowModal();
	delete g_uiCheckCurDevFingerWin;
	g_uiCheckCurDevFingerWin = NULL;
	::CoUninitialize();
}


CCheckCurDevFingersWnd::CCheckCurDevFingersWnd(LPCTSTR xml_path, USER_INFO usersFingersInfo)
	: CXMLWnd(xml_path) {
	this->user_id = user_id;
	this->username = username;
	this->usersFingersInfo = usersFingersInfo;
}

void CCheckCurDevFingersWnd::init_data() {
	//int how_many_users = MYSQL_INTERFACES::search_user_num();

	// ³õÊ¼»¯CListUI¿Ø¼þ
	CDuiString str;
	g_curDevFingersLst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	g_curDevFingersLst->RemoveAll();

	for (int i = 0; i < this->usersFingersInfo.fnum; i++) {
		CListTextElementUI* p_lst_element = new CListTextElementUI;
		p_lst_element->SetTag(i);
		g_curDevFingersLst->Add(p_lst_element);

		str.Format(_T("%d"), i);
		p_lst_element->SetText(0, usersFingersInfo.fdata[i].finger_name);
		//p_lst_element->SetText(1, finger_arr[i].date);
		//delete p_lst_element;
	}
}


void CCheckCurDevFingersWnd::InitWindow() {
	CenterWindow();
	init_data();
}


void CCheckCurDevFingersWnd::Notify(TNotifyUI& msg) {
	//if (msg.sType == _T("itemclick")) {
	//	POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
	//	UINT_PTR i_index = msg.pSender->GetTag();
	//	CMenuFingerManageWnd* menu = new CMenuFingerManageWnd(_T("Menu/MenuFingerManage.xml"), finger_arr[i_index].id, finger_arr[i_index].name, this->user_id);
	//	menu->Init(hwndFingerManage, pt);
	//}
	//if (msg.sType == _T("click")) {
	//	if (msg.pSender->GetName() == _T("add")) {
	//		create_add_user_finger_win(this->user_id, this->username);
	//	}
	//}
	__super::Notify(msg);
}


CControlUI* CCheckCurDevFingersWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}