#pragma once

#include <windows.h>
#include "MenuWnd3.h"
#include "my_duilib.h"
#include "add_admin.h"
#include "atlbase.h" 
#include "atlstr.h"

class CAdminManageWnd: public CXMLWnd {
private:
	HINSTANCE hinstance;
	void init_data();
public:
    explicit CAdminManageWnd(LPCTSTR pszXMLPath);
    virtual void InitWindow();
    virtual void Notify(TNotifyUI& msg);
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
};

void  create_usrmanage_win();