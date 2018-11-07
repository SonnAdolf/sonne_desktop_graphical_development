#include "EditCert.h"

extern HINSTANCE g_hInst;
extern HWND hwndCerts;
CEditCertWnd *p_cEditCertWin;


CEditCertWnd::CEditCertWnd(LPCTSTR pszXMLPath, string id, string name, string content, string date, string type)
	: CXMLWnd(pszXMLPath) {
	this->id = id;
	this->name = name;
	this->date = date;
	this->type = type;
}


void CEditCertWnd::InitWindow() {
	CenterWindow();
	CEditUI* inpt_name
		= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
	inpt_name->SetText(this->name.c_str());

	CDateTimeUI* inptDateUI = static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("date_inpt")));
	inptDateUI->SetText(this->date.c_str());

	CComboUI* combox = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo1")));
	CListLabelElementUI *item_ele;
	if (!this->type.compare("1")) {
		item_ele = (CListLabelElementUI *)combox->GetItemAt(1);
		item_ele->Select();
	}
	else {
		item_ele = (CListLabelElementUI *)combox->GetItemAt(0);
		item_ele->Select();
	}
}


void CEditCertWnd::OnFinalMessage(HWND hWnd) {
	__super::OnFinalMessage(hWnd);
}


void CEditCertWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("EDIT")) {
			// 获取输入的证书名
			CEditUI* uiName
				= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
			string strInptName = uiName->GetText().ToString();
			int iInptStrLen = strInptName.length();
			CDateTimeUI* inptDateUI = static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("date_inpt")));
			string strInptDate = inptDateUI->GetText().ToString();
			// 获取证书类型
			CComboUI* pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo1")));
			int nsel = pCombox->GetCurSel();
			string type;
			if (nsel == 0)
				type = DYNAMIC_KEYT;
			else
				type = PACK_KEYT;

			if (iInptStrLen == 0) {
				MessageBox(NULL, "请输入指静脉名", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (iInptStrLen > MAX_USERNAME_LEN) {
				MessageBox(NULL, "您输入的指静脉名超过长度限制", NULL, MB_SYSTEMMODAL);
				return;
			}

			editCert(this->id, strInptName, strInptDate, type);
			this->Close();
		}
	}
	__super::Notify(msg);
}


CControlUI* CEditCertWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


void  createEditCertWin(string id, string name,string content,string date,string type) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	p_cEditCertWin = new CEditCertWnd(_T("edit_cert.xml"),id,name,content,date,type);
	p_cEditCertWin->Create(hwndCerts, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	p_cEditCertWin->ShowModal();
	delete p_cEditCertWin;
	p_cEditCertWin = NULL;
	::CoUninitialize();
}