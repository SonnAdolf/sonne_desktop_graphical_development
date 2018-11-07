#include "add_cert.h"

extern CCertsWnd *g_uiCertsWnd;
extern HINSTANCE g_hInst;
extern CListUI* g_all_certs_lst;
extern int g_selected_certs_num2;
extern char g_chLoginAdminName[255];

CAddCertWnd::CAddCertWnd( LPCTSTR pszXMLPath, string user_id)
: CXMLWnd(pszXMLPath) {
	this->user_id = user_id;
}


void CAddCertWnd::InitWindow() {
	CenterWindow();
	inptDateUI
		= static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("date_inpt")));
	inptContentUI = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("content")));
	inptNameUI
		= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
	inptDateUI->SetText("2030-01-01");
}


void CAddCertWnd::OnFinalMessage(HWND hWnd) {
     __super::OnFinalMessage(hWnd);
}


bool CAddCertWnd::is_ch_hex(const char ch) {
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4'
		|| ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ||
		ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' ||
		ch == 'f' || ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' ||
		ch == 'E' || ch == 'F')
		return true;
	return false;
}


int CAddCertWnd::check_input(const char *input) {
	const char *p = input;
	int count_len = 0;
	while (*p != '\0') {
		if (!is_ch_hex(*p))
			return INPUTED_CH_NOT_HEX;
		count_len++;
		p++;
	}
	if (count_len != 64)
		return LEN_OF_CODE_WRONG;
	return INPUT_RIGHT;
}



void CAddCertWnd::Notify( TNotifyUI& msg ) {
    if( msg.sType == _T("click") ) {
        if( msg.pSender->GetName() == _T("add") ) {
			int iCurDevCertNum = 0;
#ifdef _TEST_OUTO_CREATE_CERT
			char* content = new char[40];
			// 与设备交互 获取 证书密钥（随机数）
			char* str_content = new char[100];
			if (RET_ERROR == get_cert_content_func(content)) {
				MessageBox(NULL, "设备生成设备失败", NULL, MB_TOPMOST);
				return;
			}
			STROPERATION::HexToStr((unsigned char*)str_content, (unsigned char*)content, 32);
#else
			string strInptContent = inptContentUI->GetText().ToString();
			int ret_check = check_input(strInptContent.c_str());
			if (ret_check == LEN_OF_CODE_WRONG) {
				MessageBox(NULL, "请输入64个16进制字符", NULL, MB_TOPMOST);
				return;
			}
			if (ret_check == INPUTED_CH_NOT_HEX) {
				MessageBox(NULL, "输入的字符中有字符非16进制数", NULL, MB_TOPMOST);
				return;
			}
#endif
			iCurDevCertNum  =  getNumOfCurDevCerts();
			if (iCurDevCertNum > 64) {
				MessageBox(NULL,"该设备证书数已达最大值", NULL, MB_TOPMOST);
				return;
			}
			// 获取输入的证书名
			string strInptName = inptNameUI->GetText().ToString();
			// sqlite使用utf-8编码，汉字需要转
			string strUtf8Name = STROPERATION::ASCII2UTF_8(strInptName);

			string strInptDate = inptDateUI->GetText().ToString();

			char today[40];
			STROPERATION::getDateString(today);

			// 用户输入的日期，必须晚于当日
			int iDateCompareRet = STROPERATION::dateComparing(today, strInptDate.c_str());
			if (iDateCompareRet != LATER_THAN_TODAY) {
				MessageBox(NULL, "请输入合适的证书有效期", NULL, MB_TOPMOST);
				return;
			}

			// 获取证书类型
		    CComboUI* pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo1")));
            int nsel = pCombox->GetCurSel();
			string type;
			if (nsel == 0)
				type = DYNAMIC_KEYT;
			else
				type = PACK_KEYT;
#ifdef _TEST_OUTO_CREATE_CERT
			if (FALSE == addCert(strInptDate, str_content, this->user_id, type, strUtf8Name)) {
#else
			// 插入证书到数据库
			if (FALSE == addCert(strInptDate, strInptContent, this->user_id, type, strInptName)) {
#endif
				MessageBox(NULL, "证书数据库存储失败", NULL, MB_TOPMOST);
				return;
			}

			// 添加日志
			char str_log[100] = "add cert";
			MYLOG::write_log(str_log, 6, g_chLoginAdminName);

			// 添加证书以后 选择的用户列表清空
			//sel_users_list.clear(); 
			g_uiCertsWnd->InitWindow();
#if 0
			//添加用户后将新添加证书显示到证书列表
			CListTextElementUI* p_lst_element = new CListTextElementUI;
			p_lst_element->SetTag(g_selected_certs_num2);
			g_all_certs_lst->Add(p_lst_element);
			p_lst_element->SetText(0, strInptName.c_str());
			if (nsel == 0)
				p_lst_element->SetText(1,"动态加密密钥");
			else
				p_lst_element->SetText(1,"打包加密密钥");
#ifdef _TEST_OUTO_CREATE_CERT
			p_lst_element->SetText(2, str_content);
#else
			p_lst_element->SetText(2, strInptContent.c_str());
#endif
#endif

			//MYLOG::write_log("add a cert", ADD_CERT_LOG, g_chLoginAdminName);
#ifdef _TEST_OUTO_CREATE_CERT
			delete []content;
			delete []str_content;
			content = NULL;
			str_content = NULL;
#endif

			Close(IDOK);
		}
    }
	__super::Notify(msg);
}


CControlUI* CAddCertWnd::CreateControl( LPCTSTR pstrClassName ) {
    return NULL;
}


void  create_add_cert_win(string user_id,HWND par_hwnd) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
#ifdef _TEST_OUTO_CREATE_CERT
	CAddCertWnd *win = new CAddCertWnd(_T("add_cert2.xml"), user_id);
#else
	CAddCertWnd *win = new CAddCertWnd(_T("add_cert.xml"),user_id);
#endif
	HWND hwnd =  win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	win->ShowModal(); 
	delete win;
	win = NULL;
	::CoUninitialize();
}