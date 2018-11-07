#include "certs.h"

extern HINSTANCE g_hInst;
CListUI* g_all_certs_lst;
int g_selected_certs_num2 = 0;
HWND hwndCerts;
cert_sel_ret* gCertsArr = NULL;

CCertsWnd *g_uiCertsWnd;

/**
*   sonne 2018-05-17
*   create a window to manage certs.
*/
void  create_certs_win() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	g_uiCertsWnd = new CCertsWnd(_T("certs.xml"));
	hwndCerts = g_uiCertsWnd->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	g_uiCertsWnd->ShowModal();

	delete g_uiCertsWnd;
	g_uiCertsWnd = NULL;
	if (gCertsArr != NULL) {
		delete[] gCertsArr;
		gCertsArr = NULL;
	}
	::CoUninitialize();
}


CCertsWnd::CCertsWnd(LPCTSTR xml_path)
	: CXMLWnd(xml_path) {
}

void CCertsWnd::init_data() {
	//int how_many_users = MYSQL_INTERFACES::search_user_num();

	// 初始化CListUI控件
	CDuiString str;
	g_all_certs_lst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	g_all_certs_lst->RemoveAll();

	int num;
	selAllCerts(&num, &gCertsArr);
	g_selected_certs_num2 = num;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* p_lst_element = new CListTextElementUI;
		p_lst_element->SetTag(i);
		g_all_certs_lst->Add(p_lst_element);
		p_lst_element->SetText(0, gCertsArr[i].name);
		if (atoi(gCertsArr[i].type) == 0)
			p_lst_element->SetText(1, "动态加密密钥");
		else
			p_lst_element->SetText(1, "打包加密密钥");
		p_lst_element->SetText(2, gCertsArr[i].date);
	}
}


void CCertsWnd::InitWindow() {
	CenterWindow();
	init_data();
}


void CCertsWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("itemclick")) {
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		UINT_PTR i_index = msg.pSender->GetTag();
		CMenuCertManageWnd* menu = new CMenuCertManageWnd(_T("Menu/MenuCertManage.xml"), gCertsArr[i_index].content, gCertsArr[i_index].name, gCertsArr[i_index].content, gCertsArr[i_index].date, gCertsArr[i_index].type);
		menu->Init(hwndCerts, pt);
	}
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("add")) {
			//int num = MYSQL_INTERFACES::search_cert_of_dev_num();
			int num = getNumOfCurDevCerts();
			if (num >= 64)
				MessageBox(NULL, NULL, _T("本设备证书已满（最多64个）"), MB_OK);
			else
				create_add_cert_win(this->user_id, NULL);
		}
	}
	__super::Notify(msg);
}


CControlUI* CCertsWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}