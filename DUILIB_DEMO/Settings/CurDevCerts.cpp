#include "CurDevCerts.h"

extern HINSTANCE g_hInst;
//CListUI* g_all_certs_lst;
//int g_selected_certs_num2 = 0;
//cert_sel_ret* gCertsArr;

CCurDevCertsWnd *g_uiCurDevCertsWnd;

/**
*   sonne 2018-05-17
*   create a window to manage certs.
*/
void  createCurDevCertsWin(SW_USER user, FINAL_PSW_CERT certs,int iCertNum) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	g_uiCurDevCertsWnd = new CCurDevCertsWnd(_T("cur_dev_user_certs.xml"),user,certs,iCertNum);
	g_uiCurDevCertsWnd->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	g_uiCurDevCertsWnd->ShowModal();

	delete g_uiCurDevCertsWnd;
	g_uiCurDevCertsWnd = NULL;
	::CoUninitialize();
}


CCurDevCertsWnd::CCurDevCertsWnd(LPCTSTR xml_path, SW_USER user, FINAL_PSW_CERT certs, int iCertNum)
	: CXMLWnd(xml_path) {
	this->user = user;
	this->iCertNum = iCertNum;
	this->pCerts = certs;
}

void CCurDevCertsWnd::init_data() {
	//int how_many_users = MYSQL_INTERFACES::search_user_num();

	// 初始化CListUI控件
	//CDuiString str;
	//g_all_certs_lst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	//g_all_certs_lst->RemoveAll();

	//int num;
	////gCertsArr = MYSQL_INTERFACES::select_certs("", &num);
	//selAllCerts(&num, &gCertsArr);
	//g_selected_certs_num2 = num;
	//for (int i = 0; i < num; i++) {
	//	CListTextElementUI* p_lst_element = new CListTextElementUI;
	//	p_lst_element->SetTag(i);
	//	g_all_certs_lst->Add(p_lst_element);
	//	p_lst_element->SetText(0, gCertsArr[i].name);
	//	if (atoi(gCertsArr[i].type) == 0)
	//		p_lst_element->SetText(1, "动态加密密钥");
	//	else
	//		p_lst_element->SetText(1, "打包加密密钥");
	//	p_lst_element->SetText(2, gCertsArr[i].content);
	//}
	list<FINAL_SW_CERT> cList;
	int temp;
	int i;
	if (iCertNum < 32) {
		for (i = 0; i < iCertNum; i++) {
			temp = STROPERATION::read_bit(this->user.dwCertMap[0],i);
			if (temp == 1) 
				cList.push_back(pCerts[i]);
		}
	}
	if (iCertNum >= 32) {
		for (i = 32; i < iCertNum; i++) {
			temp = STROPERATION::read_bit(this->user.dwCertMap[1], i-32);
			if (temp == 1)
				cList.push_back(pCerts[i]);
		}
	}
	CListUI* certsLst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	certsLst->RemoveAll();
	i = 0;
	string tempStr;
	unsigned char buf[72];
	for (list<FINAL_SW_CERT>::iterator iter = cList.begin(); iter != cList.end(); iter++) {
		CListTextElementUI* element = new CListTextElementUI;
		element->SetTag(i);
		certsLst->Add(element);
		STROPERATION::Wchar_tToString(tempStr, iter->wszName);
		element->SetText(0, tempStr.c_str());
		if (iter->dwFlags == 0)
			element->SetText(1, "动态加密密钥");
		else
			element->SetText(1, "打包加密密钥");
		STROPERATION::HexToStr2(buf, iter->byKey,32);
		element->SetText(2, (char*)buf);
		i++;
	}

}


void CCurDevCertsWnd::InitWindow() {
	CenterWindow();
	init_data();
}


void CCurDevCertsWnd::Notify(TNotifyUI& msg) {
	//if (msg.sType == _T("itemclick")) {
	//	POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
	//	UINT_PTR i_index = msg.pSender->GetTag();
	//	CMenuCertManageWnd* menu = new CMenuCertManageWnd(_T("Menu/MenuCertManage.xml"), gCertsArr[i_index].content, gCertsArr[i_index].name);
	//	menu->Init(hwndCerts, pt);
	//}
	//if (msg.sType == _T("click")) {
	//	if (msg.pSender->GetName() == _T("add")) {
	//		//int num = MYSQL_INTERFACES::search_cert_of_dev_num();
	//		int num = getNumOfCurDevCerts();
	//		if (num >= 64)
	//			MessageBox(NULL, NULL, _T("本设备证书已满（最多64个）"), MB_OK);
	//		else
	//			create_add_cert_win(this->user_id, NULL);
	//	}
	//}
	__super::Notify(msg);
}


CControlUI* CCurDevCertsWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}