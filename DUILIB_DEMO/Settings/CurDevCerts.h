#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "add_cert.h"
#include "MenuCertManage.h"
#include "sqlite_utils.h"

class CCurDevCertsWnd : public CXMLWnd {
public:
	explicit CCurDevCertsWnd(LPCTSTR xml_path, SW_USER user, FINAL_PSW_CERT certs, int iCertNum);
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
private:
	void init_data();
	string user_id;
	int cert_num;
	SW_USER user;
	int iCertNum;
	FINAL_PSW_CERT pCerts;
};

/**
*   sonne 2018-05-17
*   create a window to manage certs.
*/
void  createCurDevCertsWin(SW_USER user, FINAL_PSW_CERT certs, int iCertNum);
