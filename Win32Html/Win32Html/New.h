#pragma once

#include <htmlayout.h>
#include "behaviors/notifications.h"
#include <htmlayout_behavior.hpp>

namespace NEW
{
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

    //
	//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
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
  
	    char* path = "newPage.htm";
	    WCHAR wsz[256]; 

        switch (message)  
        { 
		case WM_CREATE: 
			memset(wsz,0,sizeof(wsz));
			MultiByteToWideChar(CP_ACP, 0, path, strlen(path)+1, wsz, sizeof(wsz)/sizeof(wsz[0]));
            HTMLayoutLoadFile(hWnd,wsz); //Hello.htm需要放在和exe同一目录,记得把dll也copy过去  
			break;  
   
        case WM_COMMAND:  
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
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

	//
	//  函数: MyRegisterClass()
	//
	//  目的: 注册窗口类。
	//  作者: sonne
	//  日期: 2017-03-27
	//
	ATOM NewRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)NewWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32HTML));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32HTML);
		wcex.lpszClassName	= "hh";
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassEx(&wcex);
	}

	//
	//   函数: InitInstance(HINSTANCE, int)
	//
	//   目的: 保存实例句柄并创建主窗口
	//
	//   注释:
	//
	//        在此函数中，我们在全局变量中保存实例句柄并
	//        创建和显示主程序窗口。
	//   作者: sonne
	//   日期: 2017-03-27
	//
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND hWndPar, TCHAR szWindowClass[])
	{
		HWND newHWnd;
		hInst = hInstance; // 将实例句柄存储在全局变量中
		htmlayout::dom::element root;
		char szCurrPath[MAX_PATH];
	    GetCurrentDirectory(MAX_PATH,szCurrPath);

		NewRegisterClass(hInst);

		newHWnd = CreateWindow("hh", NULL, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWndPar, NULL, hInst, NULL);

		EnableWindow(hWndPar,FALSE);

	    if (!newHWnd)
	    {
			return FALSE;
		}

	    ShowWindow(newHWnd, 5);
        UpdateWindow(newHWnd);

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
		EnableWindow(hWndPar,TRUE);
		SetForegroundWindow( hWndPar );
		BringWindowToTop(hWndPar);
		root = htmlayout::dom::element::root_element(hWndPar);
		if (root)
		{
			root.refresh();
		}
		SetCurrentDirectory(szCurrPath);
	    return TRUE;
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

}