#pragma once
#include <htmlayout.h>
#include "behaviors/notifications.h"
#include <htmlayout_behavior.hpp>

namespace MY_MSG
{
	HINSTANCE hInst;								// 当前实例
	HWND hwnd;                                      // 创建窗口句柄
	CHAR txt_arr[100];                              // 保存要显示的字符串

	ATOM				register_my_txt_win_class(HINSTANCE hInstance);
	LRESULT CALLBACK    NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void                OnButtonClick(HELEMENT button);


	/**
	* 作     者：sonne
	* 功     能：char字符串转化为wchar字符串
	*/
	WCHAR * charToWchar(const char *s){
		int w_nlen=MultiByteToWideChar(CP_ACP,0,s,-1,NULL,0);
		WCHAR *ret;
		ret=(WCHAR*) malloc(sizeof(WCHAR)*w_nlen);
		memset(ret,0,sizeof(ret));
		MultiByteToWideChar(CP_ACP,0,s,-1,ret,w_nlen);
		return ret;
	}


    /**
	 * 作      者:	sonne
	 * 函  数  名:  init_my_msg_win
	 * 功      能:  窗口初始化函数
	 */
	VOID init_my_msg_win(HWND hwnd)
	{
		htmlayout::dom::element root;
		htmlayout::dom::element	txt;
		root = htmlayout::dom::element::root_element(hwnd); 
		txt = root.get_element_by_id("txt");
		txt.clear();
		WCHAR *p_wchar_str = charToWchar(txt_arr);
		txt.set_text(p_wchar_str);
		SetWindowText(hwnd,"MY MSG");
	}

	struct DOMEventsHandlerType: htmlayout::event_handler
	{
		DOMEventsHandlerType(): event_handler(0xFFFFFFFF) {}
		virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params ) 
		{ 
			switch( params.cmd )
			{
			case BUTTON_CLICK:              MY_MSG::OnButtonClick(params.heTarget); break;// click on button
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
	//  函数: NewWndProc(HWND, UINT, WPARAM, LPARAM)
	//
	//  目的: 处理主窗口的消息。
	//  作者: sonne
	//  日期: 2017-03-27
	//
	//  WM_COMMAND    - 处理应用程序菜单
	//  WM_PAINT    - 绘制主窗口
	//  WM_DESTROY    - 发送退出消息并返回
	//
	//
	LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		int wmId, wmEvent;
	    PAINTSTRUCT ps;
		HDC hdc;
	    LRESULT lResult;
        BOOL    bHandled;
		lResult = HTMLayoutProcND(hWnd,message,wParam,lParam, &bHandled);
        if(bHandled)
             return lResult;
  
		// 相对路径
		char* chRelativePath = "my_msg.html";
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
				init_my_msg_win(hWnd);

				SetWindowText(hWnd,"nothing");
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
            switch (wmId)
            {
                case IDM_EXIT:
                   DestroyWindow(hWnd);
                   break;
                default:
                   return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
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


	ATOM register_my_txt_win_class(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= NewWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32HTML));
		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_WIN32HTML);
		wcex.lpszClassName	= "66";
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

		return RegisterClassEx(&wcex);
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

	

	void OnButtonClick(HELEMENT button)
	{
	}

	
	/**
	*    作者：sonne
	*    日期：2017-06-27
	*    功能：定时器函数，销毁窗口，并重新设置窗口类hwnd为null。
	*/
	static VOID CALLBACK TimerProc(HWND _hwnd, UINT uMsg, _In_ UINT_PTR idEvent, DWORD dwTime)
	{
		KillTimer(_hwnd, idEvent);
		// 销毁窗口
		PostMessage(hwnd, WM_DESTROY, NULL, NULL);
		hwnd = NULL;

	}

   /**
	*    作者：sonne
	*    日期：2017-06-26
	*    功能：创建窗口线程。
	*/
	DWORD WINAPI create_my_tip_win(LPVOID lpParameter)
	{
		htmlayout::dom::element root;
		char szCurrPath[MAX_PATH];
	    GetCurrentDirectory(MAX_PATH,szCurrPath);

		register_my_txt_win_class(hInst);

		hwnd = CreateWindow("66", NULL, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_POPUP,
			CW_USEDEFAULT, 0, 0, 0, NULL, NULL, hInst, NULL);

	    if (!hwnd)
	    {
			return FALSE;
		}

	    ShowWindow(hwnd, 5);
        UpdateWindow(hwnd);

		MSG msg;
	    HACCEL hAccelTable;
		hAccelTable = LoadAccelerators(hInst, (LPCTSTR)IDR_ACCELERATOR);
	    while (GetMessage(&msg, NULL, 0, 0)) 
	    {
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		    {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		Sleep(100);
		SetCurrentDirectory(szCurrPath);
		return 0;
	}

	/**
	*    作者：sonne
	*    日期：2017-06-26
	*    功能：创建提示窗口。
	*    参数：WCHAR *txt 提示框显示的文字。
	*/
	BOOL create_my_tip(HINSTANCE hInstance, CHAR *txt)
	{
		memcpy(&txt_arr, txt, 100);
		hInst = hInstance; // 将实例句柄存储在全局变量中
		CreateThread(NULL,NULL,create_my_tip_win,NULL,NULL,NULL);
		hwnd = NULL;
		while (NULL == hwnd || (int)hwnd <= 0) {;}
		SetTimer(hwnd, 1, 2000, TimerProc);

		return true;
	}

}

