#pragma once

#include <windows.h>
#include "my_including.h"
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "my_log.h"
#include "sqlite_utils.h"
#include "atlbase.h" 
#include "atlstr.h"
#include "str_utils.h"

class CEditUserWnd : public CXMLWnd {
public:
	explicit CEditUserWnd(LPCTSTR xml_path, string strUsername, string strUserId);

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void OnFinalMessage(HWND hWnd);
private:
	string strUsername;
	string strUserId;
};

void  createEditUserWin(string strUsername, string strUserId);