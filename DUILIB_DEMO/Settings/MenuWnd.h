#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "page_info.h"
#include "dev_manage.h"

class CMenuWnd: public CXMLWnd
{
public:
    explicit CMenuWnd(LPCTSTR pszXMLPath, int tag);

protected:
    virtual ~CMenuWnd();   // 私有化析构函数，这样此对象只能通过new来生成，而不能直接定义变量。就保证了delete this不会出错

public:
    void Init(HWND hWndParent, POINT ptPos);
    virtual void    OnFinalMessage(HWND hWnd);
    virtual LRESULT HandleMessage (UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT OnKillFocus   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify( TNotifyUI& msg );
private:
	int iNewWinNum;
	int tag;
};
