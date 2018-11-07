#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "add_cert.h"
#include "MenuCertManage.h"
#include "sqlite_utils.h"

class CCertsWnd : public CXMLWnd {
public:
	explicit CCertsWnd(LPCTSTR xml_path);
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
private:
	void init_data();
	string user_id;
	int cert_num;
};

/**
*   sonne 2018-05-17
*   create a window to manage certs.
*/
void  create_certs_win();
