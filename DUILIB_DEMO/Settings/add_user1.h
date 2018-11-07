#pragma once

#include <windows.h>
#include "my_including.h"
#include "my_duilib.h"
#include "my_log.h"
#include "sqlite_utils.h"

extern HINSTANCE g_hInst;
extern char g_chLoginAdminName[255];

class CAddUserWnd : public CXMLWnd {
public:
	explicit CAddUserWnd(LPCTSTR xml_path);
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void OnFinalMessage(HWND hWnd);
private:
	string strInptUserName;
};

void  createAddUserWin();