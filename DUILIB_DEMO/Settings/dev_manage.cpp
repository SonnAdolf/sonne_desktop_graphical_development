
#include "my_duilib.h"
//#include "dev_manage_win.h"
#include "dev_manage.h"


HWND g_dev_manage_win_hwnd;
CDevManageWnd *g_dev_win;


c_page_info dev_page_info;
CListUI* p_dev_lst;
extern char g_sn[32];
dev_sel_ret* dev_arr;
//extern HWND g_dev_manage_win_hwnd;

CDevManageWnd::CDevManageWnd(LPCTSTR pszXMLPath)
	: CXMLWnd(pszXMLPath) {
}


void CDevManageWnd::init_data() {
	//int how_many_devs = MYSQL_INTERFACES::search_dev_num();
	int how_many_devs = searchDevNum();
	// 分页信息
	dev_page_info = c_page_utils::create_page(19, how_many_devs, 1);

	// 初始化CListUI控件
	CDuiString str;
	p_dev_lst = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	p_dev_lst->RemoveAll();

	//dev_arr = MYSQL_INTERFACES::select_devs("", dev_page_info);
	select_devs(&dev_arr, dev_page_info);

	int num;
	int total = dev_page_info.get_total_count();
	int every_page = dev_page_info.get_every_page();
	if (total > every_page)
		num = every_page;
	else
		num = total;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* lst_element = new CListTextElementUI;
		lst_element->SetTag(i);
		p_dev_lst->Add(lst_element);

		str.Format(_T("%d"), i);
		lst_element->SetText(0, dev_arr[i].id);
		if (strcmp(dev_arr[i].status, "1") == 0)
			lst_element->SetText(1, "使用中");
		else
			lst_element->SetText(1, "废弃");
		lst_element->SetText(2, dev_arr[i].date);
		//lst_element->SetText(3, dev_arr[i].date);
	}

}

void CDevManageWnd::InitWindow() {
	CenterWindow();
	this->init_data();
}


void CDevManageWnd::init_data_after_flip_page() {
	CDuiString str;
	p_dev_lst->RemoveAll();

	//dev_sel_ret*  dev_arr = MYSQL_INTERFACES::select_devs("", dev_page_info);
	//dev_sel_ret*  dev_arr;
	select_devs(&dev_arr, dev_page_info);

	int num = dev_page_info.get_total_count() - dev_page_info.get_begin_index();
	if (num > 19)
		num = 19;
	for (int i = 0; i < num; i++) {
		CListTextElementUI* lst_element = new CListTextElementUI;
		lst_element->SetTag(i);
		p_dev_lst->Add(lst_element);

		//str.Format(_T("%d"), i);
		lst_element->SetText(0, dev_arr[i].name);
		if (dev_arr[i].status[0] == '1')
			lst_element->SetText(1, "废弃");
		else
			lst_element->SetText(1, "使用中");
		lst_element->SetText(2, dev_arr[i].id);
		lst_element->SetText(3, dev_arr[i].date);
	}
}


void CDevManageWnd::Notify(TNotifyUI& msg) {
#if 0
	// 双击事件
	if (msg.sType == _T("itemactivate")) {
		int iIndex = msg.pSender->GetTag();
		CDuiString sMessage = _T("Click: ");;
		//sMessage += domain[iIndex].c_str();  

		::MessageBox(NULL, sMessage.GetData(), _T("提示(by tojen)"), MB_OK);
	}
#endif
	if (msg.sType == _T("itemclick")) {
#if 0
		UINT_PTR i_index = msg.pSender->GetTag();
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		//POINT pt = {0,0};
		CMenuWnd *pMenu = new CMenuWnd(_T("Menu/menu.xml"), i_index);

		pMenu->Init(*this, pt);
		pMenu->ShowWindow(TRUE);
#endif
	}
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("search_btn")) {
		}
		if (msg.pSender->GetName() == _T("btnMenu")) {
			UINT_PTR i_index = msg.pSender->GetTag();
			POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
			//POINT pt = {0,0};
			CMenuWnd *pMenu = new CMenuWnd(_T("Menu/menu.xml"), i_index);

			pMenu->Init(*this, pt);
			pMenu->ShowWindow(TRUE);
		}
		if (msg.pSender->GetName() == _T("first_page_btn")) {
			c_page_utils::get_first_page(&dev_page_info);
			this->init_data_after_flip_page();
		}
		if (msg.pSender->GetName() == _T("pre_page_btn")) {
			c_page_utils::get_pre_page(&dev_page_info);
			this->init_data_after_flip_page();
		}
		if (msg.pSender->GetName() == _T("next_page_btn")) {
			c_page_utils::get_next_page(&dev_page_info);
			this->init_data_after_flip_page();
		}
		if (msg.pSender->GetName() == _T("last_page_btn")) {
			c_page_utils::get_last_page(&dev_page_info);
			this->init_data_after_flip_page();
		}
	}
	__super::Notify(msg);
}


CControlUI* CDevManageWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


/**
*   sonne 2018-02-26
*   create a window to manage devices.
*/
void  create_devmanage_win(HINSTANCE hInstance) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(hInstance);

	g_dev_win = new CDevManageWnd(_T("xx.xml"));
	g_dev_manage_win_hwnd = g_dev_win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	g_dev_win->ShowModal();
	delete g_dev_win;
	g_dev_win = NULL;
	::CoUninitialize();
}