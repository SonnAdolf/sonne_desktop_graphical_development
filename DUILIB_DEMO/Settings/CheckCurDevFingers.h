#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "add_cert.h"
#include "add_user_finger.h"
#include "MenuFingerManage.h"
#include "sqlite_utils.h"

class CCheckCurDevFingersWnd : public CXMLWnd {
public:
	explicit CCheckCurDevFingersWnd(LPCTSTR xml_path,USER_INFO usersFingersInfo);
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
private:
	void init_data();
	string user_id;
	string username;
	USER_INFO usersFingersInfo;
};

/**
*   sonne 2018-03-14
*   create a window to manage fingers of a user.
*/
void  createCheckCurDevFingersWin(USER_INFO pUsersFingersInfo);