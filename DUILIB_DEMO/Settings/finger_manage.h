#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "add_cert.h"
#include "add_user_finger.h"
#include "MenuFingerManage.h"
#include "sqlite_utils.h"

class CFingerManageWnd: public CXMLWnd {
public:
    explicit CFingerManageWnd(LPCTSTR xml_path,string user_id,string username);
    virtual void InitWindow();
    virtual void Notify(TNotifyUI& msg);
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
private:
	void init_data();
	string user_id;
	string username;
};

/**
 *   sonne 2018-03-14
 *   create a window to manage fingers of a user.
 */
void  create_finger_manage_win(string user_id, string username);