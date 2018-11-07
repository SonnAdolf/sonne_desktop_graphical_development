#pragma once

#include <windows.h>

#include "my_duilib.h"
#include "sqlite_utils.h"
#include "sel_user_impt.h"
//#include "MenuWnd2.h"
#include "add_user1.h"
#include "page_utils.h"
#include "CurUserManageMenuWnd.h"

/**
 *  sonne
 *  2018-9
 *  查看当前设备用户列表（没有同步过）
 */
class CCurUsrManageWnd : public CXMLWnd {
private:
	HINSTANCE hinstance;
	void init_data();
	PSW_USER pUsers;
	FINAL_PSW_CERT pCerts;
	int iUserNum;
	int iCertNum;
	P_USER_INFO pUsersFingersInfo;
	int iUsersFingersInfoNum;
public:
	explicit CCurUsrManageWnd(LPCTSTR pszXMLPath, HINSTANCE hInstance, PSW_USER pUsers, FINAL_PSW_CERT pCerts, int iUserNum, int iCertNum, P_USER_INFO pUsersFingersInfo, int iUsersFingersInfoNum);

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
};

/**
*  sonne
*  2018-9
*  查看当前设备用户列表（没有同步过）
*/
void  createCurDevManageWin(HINSTANCE hInstance, HWND par_hwnd, PSW_USER pUsers, FINAL_PSW_CERT pCerts, int iUserNum,
	int iCertNum, P_USER_INFO pUsersFingersInfo, int iUsersFingersInfoNum);