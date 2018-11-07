#pragma once

#include <windows.h>
#include <iostream>
#include <list>
#include "sqlite_utils.h"
#include "my_duilib.h"
#include "page_utils.h"
#include "str_utils.h"
#include "VM661JTcpDLL.h"
#include "my_including.h"


class CSelUserImptWnd : public CXMLWnd {
public:
	explicit CSelUserImptWnd(LPCTSTR xml_path);
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
private:
	void init_data();
	void init_data_after_flip_page();
	string user_id;
	void set_checkbox(int n, char* str_val);
	void  set_checkbox_visible(int n, bool visible);
	void checkbox_notify_func(int n, const char * msg_name);
};

/**
*   sonne 2018-09-13
*   create a window to select user to import into device.
*/
void  createSelUsersImptWin();