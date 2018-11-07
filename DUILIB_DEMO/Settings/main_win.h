#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "user_manage.h"
#include "dev_manage.h"
#include "logs.h"
#include "admins.h"
#include "certs.h"
#include "dev_manage.h"
#include "my_including.h"
#include "sqlite_utils.h"
#include "ManageCurDevNotSynch.h"
#include "ManageCurDevSynch.h"

extern char g_sn[32];
//extern string g_dev_name;
extern bool g_is_conn;
extern HINSTANCE g_hInst;


class CMainWnd : public CXMLWnd {
public:
	explicit CMainWnd(LPCTSTR xml_path);

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void OnFinalMessage(HWND hWnd);
private:

};

void  create_main_win();
