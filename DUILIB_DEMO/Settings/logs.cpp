#include "logs.h"
  
extern HINSTANCE g_hInst;
c_page_info log_page_info;
CListUI* p_log_lst;
extern char g_sn[32];
//log_select_ret log_arr;

LogsWnd::LogsWnd( LPCTSTR pszXMLPath )
	: CXMLWnd(pszXMLPath) {
}


void LogsWnd::init_data() {
	//int how_many_logs = MYSQL_INTERFACES::search_log_num();
	int how_many_logs = searchLogNum();
	// 分页信息
	log_page_info = c_page_utils::create_page(19, how_many_logs, 1);

	// 初始化CListUI控件
	CDuiString str;
	p_log_lst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	p_log_lst->RemoveAll();

	//log_arr =  MYSQL_INTERFACES::get_logs("", log_page_info);
	log_select_ret log_arr;
	getLogs(&log_arr, log_page_info);

	int num;
	int total = log_page_info.get_total_count();
	int every_page = log_page_info.get_every_page();
	if (total > every_page)
		num = every_page;
	else
		num = total;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* lst_element = new CListTextElementUI;
		lst_element->SetTag(i);
		p_log_lst->Add(lst_element);

		str.Format(_T("%d"), i);
		lst_element->SetText(0, log_arr.manager_names[i].c_str());
		lst_element->SetText(1, log_arr.contents[i].c_str());
		lst_element->SetText(2, log_arr.times[i].c_str());
		if (strcmp(log_arr.types[i].c_str(),DELETE_ADMIN_LOG)== 0)
			lst_element->SetText(3, "删除管理员");
		if (strcmp(log_arr.types[i].c_str(),ADD_ADMIN_LOG)== 0)
			lst_element->SetText(3, "注册管理员");
		if (strcmp(log_arr.types[i].c_str(),ADMIN_LOGIN)== 0)
			lst_element->SetText(3, "管理员登录");
		if (strcmp(log_arr.types[i].c_str(),ADD_USER)== 0)
			lst_element->SetText(3, "注册用户");
		if (strcmp(log_arr.types[i].c_str(),ADD_USER_FINGER)== 0)
			lst_element->SetText(3, "添加用户指静脉");
		if (strcmp(log_arr.types[i].c_str(),ADD_CERT)== 0)
			lst_element->SetText(3, "添加证书");
		if (strcmp(log_arr.types[i].c_str(),ADD_DEV_LOG)== 0)
			lst_element->SetText(3, "添加设备");
		if (strcmp(log_arr.types[i].c_str(), ADD_CERT_LOG_STR) == 0)
			lst_element->SetText(3, "添加证书");
		if (strcmp(log_arr.types[i].c_str(), ADD_USER_FINGER_LOG_STR) == 0)
			lst_element->SetText(3, "添加用户指静脉");
		if (strcmp(log_arr.types[i].c_str(), DEL_CERT_LOG_STR) == 0)
			lst_element->SetText(3, "删除证书");
		if (strcmp(log_arr.types[i].c_str(), DEL_FINGER_LOG_STR) == 0)
			lst_element->SetText(3, "删除用户指静脉");
		if (strcmp(log_arr.types[i].c_str(), ADD_USER) == 0)
			lst_element->SetText(3, "添加用户");
		if (strcmp(log_arr.types[i].c_str(), CONFIGURE_CERTS_LOG_STR) == 0)
			lst_element->SetText(3, "配置用户证书");
		if (strcmp(log_arr.types[i].c_str(), CLEAR_DEV_LOG_STR) == 0)
			lst_element->SetText(3, "清空设备");
		if (strcmp(log_arr.types[i].c_str(), DEL_USER_LOG_STR) == 0)
			lst_element->SetText(3, "删除用户");
	}

}

void LogsWnd::InitWindow() {
	CenterWindow();
	this->init_data();
}


void LogsWnd::init_data_after_flip_page() {
	CDuiString str;
	p_log_lst->RemoveAll();

	//log_arr =  MYSQL_INTERFACES::get_logs_of_searching("", log_page_info, "", "", "", "");
	log_select_ret log_arr;
	searchLogs(&log_arr, log_page_info, name.c_str(), type.c_str(), date_str1.c_str(), date_str2.c_str());

	int num = log_page_info.get_total_count() - log_page_info.get_begin_index();
	if (num > 19)
		num = 19;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* lst_element = new CListTextElementUI;
		lst_element->SetTag(i);
		p_log_lst->Add(lst_element);
		lst_element->SetText(0, log_arr.manager_names[i].c_str());
		lst_element->SetText(1, log_arr.contents[i].c_str());
		lst_element->SetText(2, log_arr.times[i].c_str());
		if (strcmp(log_arr.types[i].c_str(),DELETE_ADMIN_LOG)== 0)
			lst_element->SetText(3, "删除管理员");
		if (strcmp(log_arr.types[i].c_str(),ADD_ADMIN_LOG)== 0)
			lst_element->SetText(3, "注册管理员");
		if (strcmp(log_arr.types[i].c_str(),ADMIN_LOGIN)== 0)
			lst_element->SetText(3, "管理员登录");
		if (strcmp(log_arr.types[i].c_str(),ADD_USER)== 0)
			lst_element->SetText(3, "注册用户");
		if (strcmp(log_arr.types[i].c_str(),ADD_USER_FINGER)== 0)
			lst_element->SetText(3, "添加用户指静脉");
		if (strcmp(log_arr.types[i].c_str(),ADD_CERT)== 0)
			lst_element->SetText(3, "添加证书");
		if (strcmp(log_arr.types[i].c_str(),ADD_DEV_LOG)== 0)
			lst_element->SetText(3, "添加设备");
		if (strcmp(log_arr.types[i].c_str(), ADD_CERT_LOG_STR) == 0)
			lst_element->SetText(3, "添加证书");
		if (strcmp(log_arr.types[i].c_str(), ADD_USER_FINGER_LOG_STR) == 0)
			lst_element->SetText(3, "添加用户指静脉");
		if (strcmp(log_arr.types[i].c_str(), DEL_CERT_LOG_STR) == 0)
			lst_element->SetText(3, "删除证书");
		if (strcmp(log_arr.types[i].c_str(), DEL_FINGER_LOG_STR) == 0)
			lst_element->SetText(3, "删除用户指静脉");
		if (strcmp(log_arr.types[i].c_str(), ADD_USER) == 0)
			lst_element->SetText(3, "添加用户");
		if (strcmp(log_arr.types[i].c_str(), CONFIGURE_CERTS_LOG_STR) == 0)
			lst_element->SetText(3, "配置用户证书");
		if (strcmp(log_arr.types[i].c_str(), CLEAR_DEV_LOG_STR) == 0)
			lst_element->SetText(3, "清空设备");
		if (strcmp(log_arr.types[i].c_str(), DEL_USER_LOG_STR) == 0)
			lst_element->SetText(3, "删除用户");
	}
}


void LogsWnd::init_data_after_search() {
	CDuiString str;
	p_log_lst->RemoveAll();

	//int how_many_logs = MYSQL_INTERFACES::search_log_num_with_inputs(name, type, date1, date2);
	int how_many_logs = searchLogNumWithInputs(name.c_str(), type.c_str(), date_str1.c_str(), date_str2.c_str());
	// 初始化日志界面，页数为1, 每页12
	log_page_info = c_page_utils::create_page(19, how_many_logs, 1);

	//log_arr =  MYSQL_INTERFACES::get_logs_of_searching("",log_page_info,name, type, date1, date2);
	log_select_ret log_arr;
	searchLogs(&log_arr, log_page_info, name.c_str(), type.c_str(), date_str1.c_str(), date_str2.c_str());

	int num = how_many_logs;
	if (how_many_logs > 19)
		num = 19;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* lst_element = new CListTextElementUI;
		lst_element->SetTag(i);
		p_log_lst->Add(lst_element);
		lst_element->SetText(0, log_arr.manager_names[i].c_str());
		lst_element->SetText(1, log_arr.contents[i].c_str());
		lst_element->SetText(2, log_arr.times[i].c_str());
		if (strcmp(log_arr.types[i].c_str(),DELETE_ADMIN_LOG)== 0)
			lst_element->SetText(3, "删除管理员");
		if (strcmp(log_arr.types[i].c_str(),ADD_ADMIN_LOG)== 0)
			lst_element->SetText(3, "注册管理员");
		if (strcmp(log_arr.types[i].c_str(),ADMIN_LOGIN)== 0)
			lst_element->SetText(3, "管理员登录");
		if (strcmp(log_arr.types[i].c_str(),ADD_USER)== 0)
			lst_element->SetText(3, "注册用户");
		if (strcmp(log_arr.types[i].c_str(),ADD_USER_FINGER)== 0)
			lst_element->SetText(3, "添加用户指静脉");
		if (strcmp(log_arr.types[i].c_str(),ADD_CERT)== 0)
			lst_element->SetText(3, "添加证书");
		if (strcmp(log_arr.types[i].c_str(),ADD_DEV_LOG)== 0)
			lst_element->SetText(3, "添加设备");
		if (strcmp(log_arr.types[i].c_str(), ADD_CERT_LOG_STR) == 0)
			lst_element->SetText(3, "添加证书");
		if (strcmp(log_arr.types[i].c_str(), ADD_USER_FINGER_LOG_STR) == 0)
			lst_element->SetText(3, "添加用户指静脉");
		if (strcmp(log_arr.types[i].c_str(), DEL_CERT_LOG_STR) == 0)
			lst_element->SetText(3, "删除证书");
		if (strcmp(log_arr.types[i].c_str(), DEL_FINGER_LOG_STR) == 0)
			lst_element->SetText(3, "删除用户指静脉");
		if (strcmp(log_arr.types[i].c_str(), ADD_USER) == 0)
			lst_element->SetText(3, "添加用户");
		if (strcmp(log_arr.types[i].c_str(), CONFIGURE_CERTS_LOG_STR) == 0)
			lst_element->SetText(3, "配置用户证书");
		if (strcmp(log_arr.types[i].c_str(), CLEAR_DEV_LOG_STR) == 0)
			lst_element->SetText(3, "清空设备");
		if (strcmp(log_arr.types[i].c_str(), DEL_USER_LOG_STR) == 0)
			lst_element->SetText(3, "删除用户");
	}
#if 0
	if (log_arr != NULL) {
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(0);
		p_log_lst->Add(pListElement);

		pListElement->SetText(0, user_arr[0].id);
		pListElement->SetText(1, user_arr[0].name);
		c_page_utils::set_page_info(&page_info,19,1,1);
	} else {
		c_page_utils::set_page_info(&page_info,19,0,1);
		init_data();
	}
#endif
}


void LogsWnd::Notify( TNotifyUI& msg ) {
#if 0
	// 双击事件
	if( msg.sType == _T("itemactivate") )   {  
		int iIndex = msg.pSender->GetTag();  
		CDuiString sMessage = _T("Click: ");;  
		//sMessage += domain[iIndex].c_str();  

		::MessageBox(NULL, sMessage.GetData(), _T("提示(by tojen)"), MB_OK);  
	}  
#endif
	if(msg.sType == _T("itemclick"))  {  
	}  
	if(msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("search_btn"))  {
			CControlUI* ctrl = m_PaintManager.FindControl(_T("search_txt"));
			name = ctrl->GetText().ToString();
			//init_data_after_search(str.c_str());

			CDateTimeUI* date1 = static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("date_inpt1")));
			date_str1 = date1->GetText().ToString();
			CDateTimeUI* date2 = static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("date_inpt2")));
			date_str2 = date2->GetText().ToString();

		    CComboUI* pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo1")));
            int nsel = pCombox->GetCurSel();
			//string type;
			if (nsel == 0)
				type = ADMIN_LOGIN;
			if (nsel == 1)
				type = DELETE_ADMIN_LOG ;
			if (nsel == 2)
				type = ADD_ADMIN_LOG ;
			if (nsel == 3)
				type = ADD_USER;
			if (nsel == 4)
				type = ADD_CERT;
			if (nsel == 5)
				type = ADD_DEV_LOG ;
			if (nsel == 6)
				type = ADD_USER_FINGER_LOG_STR;
			if (nsel == 7)
				type = DEL_CERT_LOG_STR;
			if (nsel == 8)
				type = DEL_FINGER_LOG_STR;
			if (nsel == 9)
				type = CONFIGURE_CERTS_LOG_STR;
			if (nsel == 10)
				type = CLEAR_DEV_LOG_STR;
			if (nsel == 11)
				type = DEL_USER_LOG_STR;
			if (nsel == 12)
				type = "";
			init_data_after_search();
		}
		if (msg.pSender->GetName() == _T("first_page_btn")) {
			c_page_utils::get_first_page(&log_page_info);
			this->init_data_after_flip_page();
		}
		if (msg.pSender->GetName() == _T("pre_page_btn")) {
			c_page_utils::get_pre_page(&log_page_info);
			this->init_data_after_flip_page();
		}
		if (msg.pSender->GetName() == _T("next_page_btn")) {
			c_page_utils::get_next_page(&log_page_info);
			this->init_data_after_flip_page();
		}
		if (msg.pSender->GetName() == _T("last_page_btn")) {
			c_page_utils::get_last_page(&log_page_info);
			this->init_data_after_flip_page();
		}
	}
	__super::Notify(msg);
}


CControlUI* LogsWnd::CreateControl( LPCTSTR pstrClassName ) {
	return NULL;
}


/**
 *   sonne 2018-04-09
 *   create a window to see logs.
 */
void  create_logs_win() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	LogsWnd win(_T("logs.xml"));
	win.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);//WS_EX_WINDOWEDGE);//WS_EX_TOPMOST);
	win.ShowModal();
	::CoUninitialize();
}