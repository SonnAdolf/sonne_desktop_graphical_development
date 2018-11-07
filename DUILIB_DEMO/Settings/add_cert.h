#pragma once

#include <windows.h>
#include "my_including.h"
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "my_log.h"
//#include "sel_users_of_cert.h"
#include "my_including.h"
#include "sqlite_utils.h"
#include "certs.h"



class CAddCertWnd: public CXMLWnd {
public:
    explicit CAddCertWnd(LPCTSTR xml_path,string user_id);

    virtual void InitWindow();
    virtual void Notify(TNotifyUI& msg);
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void OnFinalMessage(HWND hWnd);
private:
	int check_input(const char *input);
	bool is_ch_hex(const char ch);
	string user_id;
	CEditUI* inptNameUI;
	CEditUI* inptContentUI;
	CDateTimeUI* inptDateUI;
};

void  create_add_cert_win(string user_id,HWND par_hwnd);