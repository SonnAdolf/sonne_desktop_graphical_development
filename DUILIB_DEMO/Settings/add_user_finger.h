#pragma once

#include <windows.h>
#include "my_including.h"
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "my_log.h"
#include "sqlite_utils.h"
#include "finger_manage.h"
#include "user_manage.h"

class CAddFingerWnd: public CXMLWnd {
public:
    explicit CAddFingerWnd(LPCTSTR xml_path,string user_id,string username);

    virtual void InitWindow();
    virtual void Notify(TNotifyUI& msg);
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void OnFinalMessage(HWND hWnd);
	//static DWORD WINAPI add_user_thread(LPVOID lpParameter);
	//static CAddFingerWnd* class_p;
private:
	string user_id;
	string username;
	//HWND hwnd;
};

void  create_add_user_finger_win(string user_id,string username);