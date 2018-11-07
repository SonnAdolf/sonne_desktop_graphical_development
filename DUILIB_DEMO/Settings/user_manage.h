#pragma once

#include <windows.h>
#include "sqlite_utils.h"


class CUsrManageWnd : public CXMLWnd {
private:
	HINSTANCE hinstance;
	void init_data();
	bool bIsCurrentUsersManage;
public:
	explicit CUsrManageWnd(LPCTSTR pszXMLPath, HINSTANCE hInstance, bool bIsCurrentUsersManage);

	virtual void InitWindow();
	virtual void init_data_after_flip_page();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void init_data_after_search(const char* username);
};

/**
*   sonne 2018-03-07
*   create a window to manage users.
*/
void  create_usrmanage_win(HINSTANCE hInstance,HWND par_hwnd, bool bIsCurrentUsersManage);