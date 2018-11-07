#include "add_admin.h"

extern HINSTANCE g_hInst;
extern int g_iAdminsNum;
extern CListUI* admins_lst;
extern char g_chLoginAdminName[255];
extern bool g_bIs1stAdmin;
string g_strInptName;
CAddAdminWnd *p_cAddAdminWin;
extern CAdminManageWnd *g_admin_win;
bool bIsAddingAdmin = false;

DWORD WINAPI register_thread(LPVOID lpParameter) {
	char *buf = new char[1024 * 1024];
	admin_start_register(buf, NULL);

	char date[20];
	STROPERATION::getDateString(date);

	FILE_OPERATION::writeDataHex((unsigned char*)buf, 17328, "test.dat");

	WCHAR wcharBuf[50];
	// sqlite使用utf-8编码，汉字需要转
	string strUtf8Name = STROPERATION::ASCII2UTF_8(g_strInptName);
	writeAdminSqlite(buf, (char*)strUtf8Name.c_str(), date);

	if (g_bIs1stAdmin) {
		MessageBox(NULL, "登记成功，程序将自动关闭，若需要再使用请先登录", NULL, MB_TOPMOST);
	}
	else {
		g_admin_win->InitWindow();
	}
	char limited_manager_name[10];
	STROPERATION::str_len_limit(limited_manager_name, g_strInptName.c_str());
	char str_log[100] = "create manager [";
	strcat(str_log, limited_manager_name);
	strcat(str_log, "].");
	MYLOG::write_log(str_log, 2, g_chLoginAdminName);
	if (g_bIs1stAdmin) {
		TGCloseDev();
		g_bIs1stAdmin = false;
	}
	delete[] buf;
	p_cAddAdminWin->Close(IDOK);
	bIsAddingAdmin = false;
	return TRUE;
}


VOID register_admin_finger(HINSTANCE hInstance) {
	CreateThread(NULL, NULL, register_thread, NULL, NULL, NULL);
	return;
}


CAddAdminWnd::CAddAdminWnd(LPCTSTR pszXMLPath)
	: CXMLWnd(pszXMLPath) {
}


void CAddAdminWnd::InitWindow() {
	CenterWindow();
}


void CAddAdminWnd::OnFinalMessage(HWND hWnd) {
	__super::OnFinalMessage(hWnd);
}


void CAddAdminWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("add")) {
			if (bIsAddingAdmin)
				return;
			bIsAddingAdmin = true;
			// 获取输入的证书名
			CEditUI* inpt_name
				= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
			 g_strInptName = inpt_name->GetText().ToString();
			int iInptStrLen = g_strInptName.length();

			if (iInptStrLen == 0) {
				MessageBox(NULL, "请输入用户名", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (STROPERATION::isStrIllegal2(g_strInptName.c_str())) {
				MessageBox(NULL, "输入的用户名中含有非法字符", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (iInptStrLen > MAX_USERNAME_LEN) {
				MessageBox(NULL, "您输入的用户名超过长度限制", NULL, MB_SYSTEMMODAL);
				return;
			}

			if (checkIfAdminOfNameExists((char*)g_strInptName.c_str())) {
				MessageBox(NULL, "您输入的用户名已存在", NULL, MB_SYSTEMMODAL);
				return;
			}
			register_admin_finger(g_hInst);
		}
	}
	__super::Notify(msg);
}


CControlUI* CAddAdminWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


void  createAddAdminWin() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	p_cAddAdminWin = new CAddAdminWnd(_T("add_admin.xml"));
	p_cAddAdminWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	p_cAddAdminWin->ShowModal();
	delete p_cAddAdminWin;
	p_cAddAdminWin = NULL;
	::CoUninitialize();
}