// Win32Html.cpp : 定义应用程序的入口点
#include "stdafx.h"
#include "Win32Html.h"
#include "New.h"

#include <htmlayout.h>
#include "behaviors/notifications.h"
#include <htmlayout_behavior.hpp>

#pragma comment(lib,"HTMLayout.lib")
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// 父窗口句柄
HWND hWnd;

#include "New.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32HTML, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32HTML));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//  作者: sonne
//  日期: 2017-03-23
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32HTML));
	wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_WIN32HTML);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//   作者: sonne
//   日期: 2017-03-23
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass,  NULL, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_POPUP/*WS_OVERLAPPED*/,
			CW_USEDEFAULT, 0, 1000, 1000, NULL, NULL, hInstance, NULL);
   
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void OnButtonClick(HELEMENT button);

struct DOMEventsHandlerType: htmlayout::event_handler
{
      DOMEventsHandlerType(): event_handler(0xFFFFFFFF) {}
      virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params ) 
      { 
        switch( params.cmd )
        {
        case BUTTON_CLICK:              OnButtonClick(params.heTarget); break;// click on button
        case BUTTON_PRESS:              break;// mouse down or key down in button
        case BUTTON_STATE_CHANGED:      break;
        case EDIT_VALUE_CHANGING:       break;// before text change
        case EDIT_VALUE_CHANGED:        break;//after text change
        case SELECT_SELECTION_CHANGED:  break;// selection in <select> changed
        case SELECT_STATE_CHANGED:      break;// node in select expanded/collapsed, heTarget is the node
        case POPUP_REQUEST: 
                                        break;// request to show popup just received, 
                                              //     here DOM of popup element can be modifed.
        case POPUP_READY:               break;// popup element has been measured and ready to be shown on screen,
                                              //     here you can use functions like ScrollToView.
        case POPUP_DISMISSED:           break;// popup element is closed,
                                              //     here DOM of popup element can be modifed again - e.g. some items can be removed
                                              //     to free memory.
        case MENU_ITEM_ACTIVE:                // menu item activated by mouse hover or by keyboard
             break;
        case MENU_ITEM_CLICK:                 // menu item click 
             break;


            // "grey" event codes  - notfications from behaviors from this SDK 
        case HYPERLINK_CLICK:           break;// hyperlink click
        case TABLE_HEADER_CLICK:        break;// click on some cell in table header, 
                                              //     target = the cell, 
                                              //     reason = index of the cell (column number, 0..n)
        case TABLE_ROW_CLICK:           break;// click on data row in the table, target is the row
                                              //     target = the row, 
                                              //     reason = index of the row (fixed_rows..n)
        case TABLE_ROW_DBL_CLICK:       break;// mouse dbl click on data row in the table, target is the row
                                              //     target = the row, 
                                              //     reason = index of the row (fixed_rows..n)

        case ELEMENT_COLLAPSED:         break;// element was collapsed, so far only behavior:tabs is sending these two to the panels
        case ELEMENT_EXPANDED:          break;// element was expanded,

        }
        return FALSE; 
      }
 
} DOMEventsHandler;

LRESULT CALLBACK HTMLayoutNotifyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LPVOID vParam)
{
  // all HTMLayout notification are comming here.
  NMHDR*  phdr = (NMHDR*)lParam;

  switch(phdr->code)
  {
      case HLN_CREATE_CONTROL:    break; //return OnCreateControl((LPNMHL_CREATE_CONTROL) lParam);
      case HLN_CONTROL_CREATED:   break; //return OnControlCreated((LPNMHL_CREATE_CONTROL) lParam);
      case HLN_DESTROY_CONTROL:   break; //return OnDestroyControl((LPNMHL_DESTROY_CONTROL) lParam);
      case HLN_LOAD_DATA:         break;
      case HLN_DATA_LOADED:       break; //return OnDataLoaded((LPNMHL_DATA_LOADED)lParam);
      case HLN_DOCUMENT_COMPLETE: break; //return OnDocumentComplete();
      case HLN_ATTACH_BEHAVIOR:   break;
  }
  return 0;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//  作者: sonne
//  日期: 2017-03-23
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	LRESULT lResult;
    BOOL    bHandled;

    // HTMLayout +
	// HTMLayout could be created as separate window 
	// using CreateWindow API.
	// But in this case we are attaching HTMLayout functionality
	// to the existing window delegating windows message handling to 
	// HTMLayoutProcND function.
	lResult = HTMLayoutProcND(hWnd,message,wParam,lParam, &bHandled);
	if(bHandled)
		return lResult;
	
	// 相对路径
	char* chRelativePath = "htmlayoutDemo.htm";
	WCHAR wsRelativePath[256]; 

    switch (message)  
	{
        case WM_CREATE:  
		{
            // Normally HTMLayout sends its notifications
            // to its parent. 
            // In this particular case we are using callback function to receive and
            // and handle notification. Don't bother the desktop window (parent of this window)
            // by our notfications.
            HTMLayoutSetCallback(hWnd,&HTMLayoutNotifyHandler,0);

            // attach DOM events handler so we will be able to receive DOM events like BUTTON_CLICK, HYPERLINK_CLICK, etc.
			htmlayout::attach_event_handler(hWnd, &DOMEventsHandler);

			memset(wsRelativePath,0,sizeof(wsRelativePath));
			//char* 转LPCWSTR
			MultiByteToWideChar(CP_ACP, 0, chRelativePath, strlen(chRelativePath)+1, wsRelativePath,
				      sizeof(wsRelativePath)/sizeof(wsRelativePath[0]));

			//使用绝对路径
			WCHAR wsPath[MAX_PATH];
			GetCurrentDirectoryW(2048,wsPath);
			wcscat(wsPath,L"\\");
			wcscat(wsPath,wsRelativePath);

			HTMLayoutLoadFile(hWnd,wsPath); 

			SetWindowText(hWnd,"身份认证系统");
			SetForegroundWindow( hWnd );

			//窗口初始化
			DWORD dWidth = HTMLayoutGetMinWidth(hWnd);
			DWORD dHeight = HTMLayoutGetMinHeight(hWnd,dWidth);
			int cx = GetSystemMetrics(SM_CXSCREEN);
			int cy = GetSystemMetrics(SM_CYSCREEN);
			SetWindowPos(hWnd,HWND_TOPMOST,cx/2-dWidth/2,cy/2-dHeight/2,dWidth,dHeight,SWP_NOZORDER);
			HRGN hRgn;
			RECT rect;
			GetWindowRect(hWnd,&rect);
			hRgn = CreateRoundRectRgn(0,0,rect.right-rect.left,rect.bottom-rect.top,20,20);
			SetWindowRgn(hWnd,hRgn,TRUE);
		}
		break;  
    case WM_COMMAND:  
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//************************************
// 作      者:	sonne
// 函  数  名:  OnButtonClick
// 功      能:  按钮响应事件
// 完  整  名:  OnButtonClick
// 访  问  权:  public 
// 返回值类型:  VOID
// 方法限定符: 	
//************************************
void OnButtonClick(HELEMENT button)
{
	htmlayout::dom::element cBut = button;
	if (!wcscmp(cBut.get_attribute("id"),L"button1"))
	{
		 NEW::InitInstance(hInst, 0, hWnd, szWindowClass);
	}
	//关闭按钮
	if (!wcscmp(cBut.get_attribute("id"),L"button2"))
	{
		PostMessage(hWnd,WM_DESTROY,NULL,NULL);
	}
}