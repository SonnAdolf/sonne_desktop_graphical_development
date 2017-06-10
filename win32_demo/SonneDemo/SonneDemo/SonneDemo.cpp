// SonneDemo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "SonneDemo.h"
#include "usrname_input.h"

#define MAX_LOADSTRING 100

// 全局变量:
HWND g_hwnd;
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
WCHAR pic_path[32];                             // 图片路径

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


/**
*   作者：sonne
*   日期：2017-06-09 2017-06-08
*   备注：win32开发demo  文本框获取、图片显示及更改
**/
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//默认图片路径
	WCHAR *pic_tmp_path = L"E:\\Bmp\\Bmp\\2.bmp";
	memcpy(pic_path, pic_tmp_path, 32);

	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SONNEDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SONNEDEMO));

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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SONNEDEMO));
	wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)COLOR_WINDOW;
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDI_SONNEDEMO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	// hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	//   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	hWnd = CreateWindow(szWindowClass, L"无敌风火轮",   
		WS_OVERLAPPEDWINDOW, 100, 80, 600, 400, NULL, NULL, hInstance, NULL); 
	g_hwnd = hWnd;
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

 
// 处理对话框消息  
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)  
{   
	HDC hdc;  
	PAINTSTRUCT ps;  
	HDC hdcMem;  
	HBITMAP hbmp;   //一张位图的句柄  
	BITMAP bmp; 

	WCHAR txt[32];

	//要替换的图片路径
	WCHAR *tmp_path = L"E:\\Bmp\\Bmp\\3.bmp";

	switch (msg)  
	{  
	case WM_INITDIALOG:
		break;
	case WM_PAINT:   
		hdc = BeginPaint(hdlg,&ps); 
		hdcMem  = CreateCompatibleDC(hdc); 

		hbmp = (HBITMAP)LoadImage(NULL, pic_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
		GetObject(hbmp, sizeof(BITMAP), &bmp);  //得到一个位图对象  

		SelectObject(hdcMem, hbmp);  
		BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);        //显示位图  

		DeleteDC(hdcMem);  
		DeleteObject(hbmp);  
		EndPaint(hdlg,&ps); 
		break;
	case WM_COMMAND:  
		{  
			switch(LOWORD(wParam))  {  
			case IDC_BUTTON1:  
				//新窗口，演示文本框
				NewInitInstance( hInst,g_hwnd, 5);
				break;  
			case IDC_BUTTON2:  
				//更换图片（路径）
				memcpy(pic_path, tmp_path, 32);

				//局部（图片），刷新重绘
				RECT        rect;   
				SetRect(&rect, 0, 0, 500, 300); 
				InvalidateRect(hdlg,&rect,true);
				UpdateWindow(hdlg);

				break;  
			default:  
				break;  
			}  
		}  
		return 0;  
	}  
	return (INT_PTR)FALSE;  
} 


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_CREATE:  
		{  
			// 创建对话框  
			HWND hdlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)DlgProc);  
			// 显示对话框  
			ShowWindow(hdlg, SW_SHOWNA);  
		}  
		return 0; 
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
