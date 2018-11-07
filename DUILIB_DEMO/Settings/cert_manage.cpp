#include "my_duilib.h"
#include "cert_manage.h"
#include "add_cert.h"

extern HINSTANCE g_hInst;
c_page_info cPageCertsOfDevInfo;
list<SW_CERT2> selCertsLst;
HWND hwndCertManage;
SW_CERT2* pCertsOfDev;
extern char g_chLoginAdminName[255];
extern CUsrManageWnd *g_uiUserManageWin;

/**
 *   sonne 2018-03-13
 *   create a window to manage certs of a user.
 */
void  create_cert_manage_win(string user_id) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);

	CCertManageWnd *win = new CCertManageWnd(_T("sel_certs_of_user.xml"), user_id);
	hwndCertManage = win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	win->ShowModal();

	delete win;
	::CoUninitialize();
}


CCertManageWnd::CCertManageWnd( LPCTSTR xml_path,string user_id)
	: CXMLWnd(xml_path) {
	this->user_id = user_id;
}


void CCertManageWnd::set_checkbox_visible(int n, bool visible) {
	char str[20] = "CheckBox";
	char str_num[10];
	itoa(n, str_num, 10);
	strcat(str, str_num);
	CCheckBoxUI* checkbox1 = static_cast<CCheckBoxUI*> (m_PaintManager.FindControl(str));
	if (visible)
		checkbox1->SetVisible(true);
	else
		checkbox1->SetVisible(false);
}


void CCertManageWnd::set_checkbox(int n, char* str_val) {
	char str[20] = "CheckBox";
	char str_num[10];
	itoa(n, str_num, 10);
	strcat(str, str_num);
	CCheckBoxUI* checkbox1 = static_cast<CCheckBoxUI*> (m_PaintManager.FindControl(str));
	checkbox1->Selected(false);
	if (str_val == NULL)
		return;
	if (str_val[0] == '\0')
		return;
	if (strlen(str_val) == 0) 
		return ;
	checkbox1->SetText(str_val);
	checkbox1->SetVisible(true);
	for (list<SW_CERT2>::iterator iter = selCertsLst.begin(); iter != selCertsLst.end(); iter++) {
		if (!strcmp(iter->wszName, str_val)) {
			checkbox1->Selected(true);
			break;
		}
	}
}


void CCertManageWnd::init_data() {
	//int num = MYSQL_INTERFACES::search_cert_of_dev_num();
	int num = getNumOfCerts();
	cPageCertsOfDevInfo = c_page_utils::create_page(18, num, 1);
	//pCertsOfDev = MYSQL_INTERFACES::select_pCertsOfDev("", cPageCertsOfDevInfo);
	//selAllCertsOfCurDev(&pCertsOfDev, cPageCertsOfDevInfo);
	selAllCertsWithPage(&pCertsOfDev, cPageCertsOfDevInfo);
	selCertsLst.clear();
	//MYSQL_INTERFACES::init_certs_lst(this->user_id, &selCertsLst);
	initCertsList(this->user_id, &selCertsLst);
	int how_manay_this_page
		= cPageCertsOfDevInfo.get_total_count() - cPageCertsOfDevInfo.get_begin_index();
	if (how_manay_this_page > 18)
		how_manay_this_page = 18;
	for (int i = 0; i < 18; i++) {
		if (i < how_manay_this_page)
			// 设置界面上checkbox值
			set_checkbox(i + 1, pCertsOfDev[i].wszName);
		// 删除界面上多余的UI
		if (i >= how_manay_this_page) {
			set_checkbox_visible(i + 1,false);
		}
	}
}


void CCertManageWnd::init_data_after_flip_page() {
	SW_CERT2* pCertsOfDev;// = MYSQL_INTERFACES::select_pCertsOfDev("", cPageCertsOfDevInfo);
	//selAllCertsOfCurDev(&pCertsOfDev, cPageCertsOfDevInfo);
	selAllCertsWithPage(&pCertsOfDev, cPageCertsOfDevInfo);
	int how_manay_this_page
		= cPageCertsOfDevInfo.get_total_count() - cPageCertsOfDevInfo.get_begin_index();
	if (how_manay_this_page > 18)
		how_manay_this_page = 18;
	for (int i = 0; i < 18; i++) {
		if (i < how_manay_this_page) {
			// 设置界面上checkbox值
			set_checkbox(i + 1, pCertsOfDev[i].wszName);
			set_checkbox_visible(i + 1, true);
		}
		// 删除界面上多余的UI
		if (i >= how_manay_this_page) {
			set_checkbox_visible(i + 1,false);
		}
	}
}


void CCertManageWnd::InitWindow() {
	CenterWindow();
	init_data();
}


void removeCertListByName(const char* name) {
	// 遍历、查找、删除
	for (list<SW_CERT2>::iterator iter = selCertsLst.begin(); iter != selCertsLst.end(); iter++) {
		if (!strcmp(iter->wszName, name)) {
			selCertsLst.erase(iter);
			break;
		}
	}
}


void CCertManageWnd::checkbox_notify_func(int n, const char* msg_name) {
	char str_checkbox[20] = "CheckBox";
	char str_num[10];
	itoa(n, str_num, 10);
	strcat(str_checkbox, str_num);
	if (!strcmp(msg_name, str_checkbox)) {
		CCheckBoxUI* checkbox1 = static_cast<CCheckBoxUI*> (m_PaintManager.FindControl(str_checkbox));
		if (!checkbox1->IsSelected()) {
			//selCertsLst.push_back(*MYSQL_INTERFACES::select_certs_of_name("", checkbox1->GetText()));
			SW_CERT2* cert;
			select_certs_of_name(&cert, checkbox1->GetText());
			selCertsLst.push_back(*cert);
		}
		else {
			removeCertListByName(std::string(checkbox1->GetText().GetData()).c_str());
		}
	}
}




void CCertManageWnd::Notify( TNotifyUI& msg ) {
	if(msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("add"))  {
			//MessageBox(NULL, NULL, _T("提示(by tojen)"), MB_OK);  
			create_add_cert_win(this->user_id,NULL);
		}
		if (msg.pSender->GetName() == _T("ok")) {
			//MYSQL_INTERFACES::create_certuser_many_to_many(selCertsLst, this->user_id);
			if (selCertsLst.size() > 16) {
				MessageBox(NULL, "最多选择16个证书", NULL, MB_TOPMOST);
				return;
			}
			CreateCertuserMany2Many(selCertsLst, this->user_id);
			char str_log[200] = "configure certs of ";
			strcat(str_log, this->user_id.c_str());
			MYLOG::write_log(str_log, CONFIGURE_CERTS_LOG, g_chLoginAdminName);
			MessageBox(NULL, "配置完成", "证书配置", MB_OK|MB_TOPMOST);
			g_uiUserManageWin->InitWindow();
			//CreateThread(NULL, NULL, CEncryptionUtils::writeCertsUsers, NULL, NULL, NULL);
		}
		if (msg.pSender->GetName() == _T("first_page_btn")) {
			if (cPageCertsOfDevInfo.is_has_pre_page()) {
				c_page_utils::get_first_page(&cPageCertsOfDevInfo);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("pre_page_btn")) {
			if (cPageCertsOfDevInfo.is_has_pre_page()) {
				c_page_utils::get_pre_page(&cPageCertsOfDevInfo);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("next_page_btn")) {
			if (cPageCertsOfDevInfo.is_has_next_page()) {
				c_page_utils::get_next_page(&cPageCertsOfDevInfo);
				this->init_data_after_flip_page();
			}
		}
		if (msg.pSender->GetName() == _T("last_page_btn")) {
			if (cPageCertsOfDevInfo.is_has_next_page()) {
				c_page_utils::get_last_page(&cPageCertsOfDevInfo);
				this->init_data_after_flip_page();
			}
		}
		for (int i = 1; i < 19; i++)
			checkbox_notify_func(i, std::string(msg.pSender->GetName().GetData()).c_str());
	}
	__super::Notify(msg);
}


CControlUI* CCertManageWnd::CreateControl( LPCTSTR pstrClassName ) {
	return NULL;
}