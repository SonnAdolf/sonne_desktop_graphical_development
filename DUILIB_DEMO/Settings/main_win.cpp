#include "main_win.h"


HWND main_hwnd;

CControlUI * btnManageUser;
CControlUI* btnManageDev;
CControlUI* btnManageCert;
CControlUI* btnManageManager;
CControlUI*	uiInptDevId;
//CControlUI* btnClearDev;
CControlUI* btnManageCurDev;

extern char g_chLoginAdminName[255];
bool gIsManageCurDev = false;
bool gNewWinAvailable = true;

DWORD getDevStatAndBtnSettings(LPVOID lpParameter) {
	int ret, mode = 0;
	do {
		if (!g_is_conn){
			btnManageUser->SetEnabled(false);
			btnManageDev->SetEnabled(false);
			btnManageCert->SetEnabled(false);
			btnManageManager->SetEnabled(false);
			//btnClearDev->SetEnabled(false);
			uiInptDevId->SetText(SHOW_AFTER_CONN_DEV_STR);
			btnManageCurDev->SetEnabled(false);
		}
	} while (1);
}


CMainWnd::CMainWnd(LPCTSTR pszXMLPath)
	: CXMLWnd(pszXMLPath) {
}


void CMainWnd::InitWindow() {
	CenterWindow();
	btnManageUser = m_PaintManager.FindControl(_T("MANAGE_USER"));
	btnManageDev = m_PaintManager.FindControl(_T("MANAGE_DEV"));
	btnManageCert = m_PaintManager.FindControl(_T("MANAGE_CERT"));
	btnManageManager = m_PaintManager.FindControl(_T("MANAGE_MANAGER"));
	//btnClearDev = m_PaintManager.FindControl(_T("CLEAR_DEV"));
	uiInptDevId = m_PaintManager.FindControl(_T("dev_id"));
	btnManageCurDev = m_PaintManager.FindControl(_T("CUR_DEV_USER_MANAGEMENT"));
	if (!g_is_conn) {
		btnManageUser->SetEnabled(false);
		btnManageDev->SetEnabled(false);
		btnManageCert->SetEnabled(false);
		btnManageManager->SetEnabled(false);
		//btnClearDev->SetEnabled(false);
		uiInptDevId->SetText(SHOW_AFTER_CONN_DEV_STR);
		btnManageCurDev->SetEnabled(false);
	}
	else {
		uiInptDevId->SetText(g_sn);
	}

	//CreateThread(NULL, NULL, synchThread2, NULL, NULL, NULL);
}

void CMainWnd::OnFinalMessage(HWND hWnd) {
	TGCloseDev();
	__super::OnFinalMessage(hWnd);
}

CControlUI* CMainWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


void getFinalCertsFromCerts(FINAL_PSW_CERT fpc, PSW_CERT pc, int num) {
	WCHAR wch[100];
	//char hex_buf[32];
	for (int i = 0; i < num; i++) {
		fpc[i].dwFlags = pc[i].dwFlags;
		fpc[i].dwReserved = pc[i].dwReserved;
		fpc[i].ftCreateDate = pc[i].ftCreateDate;
		fpc[i].ftExpireDate = pc[i].ftExpireDate;
		STROPERATION::StrToHex2(fpc[i].byKey, (unsigned char*)pc[i].byKey, 32);
		memset(wch, 0, 100 * sizeof(WCHAR));
		STROPERATION::charToWchar(pc[i].wszName, wch);
		wcscpy(fpc[i].wszName, wch);
	}
}

void writeData(unsigned char * my_array, int length, char *string) {
	int i = 0;
	FILE *fp;
	fp = fopen(string, "wb+");
	if (NULL == fp) {
		printf("file open Fail!\n");
	}

	while (i < length) {
		fwrite(&my_array[i], sizeof(unsigned char), 1, fp);
		i++;
	}

	fclose(fp);
}


void CMainWnd::Notify(TNotifyUI& msg) {
	int iDevConnectedRet, iMode, iCloseDevRet;
	PSW_USER psw_user = NULL;
	PSW_CERT psw_cert = NULL;
	FINAL_PSW_CERT final_psw_cert = NULL;
	int user_num, cert_num = 0;
	PSW_USERCERTTABLE psw_usercert_table;
	user_sel_ret* users;
	list<SW_CERT> cert_list;
	if (_tcsicmp(msg.sType, _T("itemactivate")) == 0) 
		return;

	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("MANAGE_USER")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				create_usrmanage_win(g_hInst, main_hwnd, false);
				gNewWinAvailable = true;
			}
		}
		if (msg.pSender->GetName() == _T("MANAGE_MANAGER")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				create_usrmanage_win();
				gNewWinAvailable = true;
			}
		}
		if (msg.pSender->GetName() == _T("MANAGE_CERT")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				create_certs_win();
				gNewWinAvailable = true;
			}
		}
		if (msg.pSender->GetName() == _T("MANAGE_DEV")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				create_devmanage_win(g_hInst);
				gNewWinAvailable = true;
			}
		}
		if (msg.pSender->GetName() == _T("LOG")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				create_logs_win();
				gNewWinAvailable = true;
			}
		}

		/*
		*  点击 管理当前设备 按钮
		*/
		if (msg.pSender->GetName() == _T("CUR_DEV_USER_MANAGEMENT")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				//CreateThread(NULL, NULL, synchThread, NULL, NULL, NULL);
				createCurUsrManageSynchronized(g_hInst, main_hwnd);
				gNewWinAvailable = true;
			}
		}

		if (msg.pSender->GetName() == _T("TEST")) {
			if (gNewWinAvailable) {
				selUsersOfCurDev(&users, &user_num);
				selCertsToWrite(users, user_num, &cert_list, &cert_num);
				// 临时certs数组申请空间
				psw_cert = new SW_CERT[cert_num];
				int ii = 0;
				for (list<SW_CERT>::iterator iter = cert_list.begin(); iter != cert_list.end(); iter++) {
					strcpy(psw_cert[ii].byKey, iter->byKey);
					strcpy(psw_cert[ii].wszName, iter->wszName);
					psw_cert[ii].dwFlags = iter->dwFlags;
					psw_cert[ii].ftCreateDate = iter->ftCreateDate;
					psw_cert[ii].ftExpireDate = iter->ftExpireDate;
					ii++;
				}
				int total_len = sizeof(SW_USERCERTTABLE) + sizeof(SW_USER)*user_num + sizeof(FINAL_SW_CERT)* cert_num;
				BYTE* p1 = NULL;
				BYTE* p2 = NULL;
				BYTE* p3 = NULL;
				try {
					p1 = new BYTE[total_len];
					p2 = p1 + sizeof(SW_USERCERTTABLE);
					p3 = p2 + sizeof(SW_USER)*user_num;
					psw_usercert_table = new (p1)SW_USERCERTTABLE;
					psw_user = new (p2)SW_USER;
					final_psw_cert = new (p3)FINAL_SW_CERT;
				}
				catch (const bad_alloc& e) {
					MessageBoxA(NULL, "申请内存失败", "申请内存失败", MB_SYSTEMMODAL);
					return;
				}
				if (psw_usercert_table == NULL || psw_user == NULL || final_psw_cert == NULL) {
					MessageBoxA(NULL, "申请内存失败", "申请内存失败", MB_SYSTEMMODAL);
					return;
				}

				// 得到user结构体数组
				selectUsersForEncryption(psw_cert, psw_user, cert_num, &user_num);
				// cert数组转化为final cert数组
				getFinalCertsFromCerts(final_psw_cert, psw_cert, cert_num);
				delete[] psw_cert;

				// 信息写入user_cert结构体
				psw_usercert_table->dwSize = total_len;
				psw_usercert_table->dwCertTableOffset = sizeof(SW_USERCERTTABLE) + sizeof(SW_USER)*user_num;
				psw_usercert_table->dwUserTableLength = user_num * sizeof(SW_USER);
				psw_usercert_table->dwUserTableOffset = sizeof(SW_USERCERTTABLE);
				psw_usercert_table->dwUserUnitSize = sizeof(SW_USER);
				psw_usercert_table->dwCertTableLength = cert_num * sizeof(FINAL_SW_CERT);

				writeData((unsigned char *)p1, total_len, "writeData.data");
				MessageBoxA(NULL, "写入完成", "完成", MB_SYSTEMMODAL);

				delete[] p1;
				p1 = NULL;
			}
		}
		/*
		* 设备连接\断开按钮对应响应
		*/
		if (msg.pSender->GetName() == _T("dev_conn")) {
			if (gNewWinAvailable) {
				gNewWinAvailable = false;
				// 若当前设备连接则断开
				if (g_is_conn) {
					iDevConnectedRet = TGCloseDev();
					if (iDevConnectedRet == OK) {
						btnManageUser->SetEnabled(false);
						btnManageDev->SetEnabled(false);
						btnManageCert->SetEnabled(false);
						btnManageManager->SetEnabled(false);
						//btnClearDev->SetEnabled(false);
						btnManageCurDev->SetEnabled(false);
						uiInptDevId->SetText(SHOW_AFTER_CONN_DEV_STR);
					}
					else if (iDevConnectedRet == RET_ERROR)
						MessageBox(NULL, CLOSE_DEV_FAIL, NULL, MB_SYSTEMMODAL);
				}
				// 若当前设备断开则连接
				else {
					iDevConnectedRet = TGOpenDev(&iMode);
					if (iDevConnectedRet == OK) {
						g_is_conn = true;
						btnManageUser->SetEnabled(true);
						btnManageDev->SetEnabled(true);
						btnManageCert->SetEnabled(true);
						btnManageManager->SetEnabled(true);
						//btnClearDev->SetEnabled(true);
						btnManageCurDev->SetEnabled(true);
						TGDevGetSN(g_sn);
						if (!checkIfDevExists("", g_sn)) {
							char chDevDate[30];
							STROPERATION::getDateString(chDevDate);
							addDevSqlite("", g_sn, chDevDate, "1");
						}
						uiInptDevId->SetText(g_sn);
						//CreateThread(NULL, NULL, synchThread2, NULL, NULL, NULL);
					}
					else if (iDevConnectedRet == RET_ERROR)
						MessageBox(NULL, OPEN_DEV_FAIL, NULL, MB_SYSTEMMODAL);
				}
				gNewWinAvailable = true;
			}
		}
	}
	__super::Notify(msg);
}


void  create_main_win() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	CMainWnd *win = new CMainWnd(_T("main_win.xml"));
	HWND main_hwnd = win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	CreateThread(NULL, NULL, getDevStatAndBtnSettings, NULL, NULL, NULL);
	win->ShowModal();
	//delete win;
	//win = NULL;
	::CoUninitialize();
}