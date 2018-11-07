#pragma once

#include <windows.h>
#include "my_including.h"
#include "my_duilib.h"
#include "page_utils.h"
#include "sqlite_utils.h"

class LogsWnd: public CXMLWnd {
public:
	virtual void init_data();
    explicit LogsWnd(LPCTSTR pszXMLPath);

    virtual void InitWindow();
    virtual void Notify(TNotifyUI& msg);
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void init_data_after_flip_page();
	virtual void init_data_after_search();
private:
	string  name;
	string date_str1;
	string date_str2;
	string type;
};


/**
 *   sonne 2018-04-09
 *   create a window to see logs.
 */
void  create_logs_win();