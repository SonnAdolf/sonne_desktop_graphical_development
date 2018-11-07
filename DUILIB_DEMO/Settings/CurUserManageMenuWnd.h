#pragma once

#include <windows.h>
#include "my_duilib.h"
#include <iostream>
#include "my_including.h"
#include "page_info.h"
#include "cert_manage.h"
#include "finger_manage.h"
#include "user_manage.h"
#include "CheckCurDevFingers.h"
#include "CurDevCerts.h"

//extern string g_dev_name;

class CCurUserManageMenuWnd : public CXMLWnd {
public:
	explicit CCurUserManageMenuWnd(LPCTSTR pszXMLPath, int tag, PSW_USER pUsers, FINAL_PSW_CERT pCerts, int iUserNum, int iCertNum, USER_INFO pUsersFingersInfo);

protected:
	virtual ~CCurUserManageMenuWnd();   // 私有化析构函数，这样此对象只能通过new来生成，而不能直接定义变量。就保证了delete this不会出错

public:
	void Init(HWND hWndParent, POINT ptPos);
	virtual void    OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify(TNotifyUI& msg);
private:
	int tag;
	int iNewWinNum;
	USER_INFO usersFingersInfo;
	PSW_USER pUsers;
	FINAL_PSW_CERT pCerts;
	int iUserNum;
	int iCertNum;
};
