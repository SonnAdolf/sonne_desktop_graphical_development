#pragma once

#include <windows.h>
#include "user_manage.h"
#include "page_utils.h"


class CCertManageWnd: public CXMLWnd {
public:
    explicit CCertManageWnd(LPCTSTR xml_path,string user_id);
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
 *   sonne 2018-03-13
 *   create a window to manage certs of a user.
 */
void  create_cert_manage_win(string user_id);