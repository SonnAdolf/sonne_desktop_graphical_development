#pragma once

#include <windows.h>
#include "file_utils.h"
#include "my_including.h"
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "my_log.h"
#include "sqlite_utils.h"
#include "atlbase.h" 
#include "atlstr.h"
#include "str_utils.h"
#include "admins.h"

class CAddAdminWnd : public CXMLWnd {
public:
	explicit CAddAdminWnd(LPCTSTR xml_path);

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void OnFinalMessage(HWND hWnd);
};

void  createAddAdminWin();