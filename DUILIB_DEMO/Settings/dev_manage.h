#pragma once

#include <windows.h>
#include "my_including.h"
#include "my_duilib.h"
#include "MenuWnd.h"
#include "page_utils.h"
#include "sqlite_utils.h"

class CDevManageWnd : public CXMLWnd {
public:
	virtual void init_data();
	explicit CDevManageWnd(LPCTSTR pszXMLPath);

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void init_data_after_flip_page();
};

/**
*   sonne 2018-02-26
*   create a window to manage devices.
*/
void  create_devmanage_win(HINSTANCE hInstance);