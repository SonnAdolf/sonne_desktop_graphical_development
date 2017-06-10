#include "stdafx.h"
#include "SonneDemo.h"

#include "usrname_input.h"

HINSTANCE g_hInst;
HWND g_win_hwnd;


ATOM NewMyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= NewWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SONNEDEMO));
	wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)COLOR_WINDOW;
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDI_SONNEDEMO);
	wcex.lpszClassName	= L"usrname_inpt";
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
BOOL NewInitInstance(HINSTANCE hInstance, HWND hWndPar, int nCmdShow)
{
	HWND hWnd;

	g_hInst = hInstance; // 将实例句柄存储在全局变量中

	NewMyRegisterClass(hInstance);

	hWnd = CreateWindow(L"usrname_inpt", L"77676",   
		WS_OVERLAPPEDWINDOW, 100, 80, 600, 400, hWndPar, NULL, hInstance, NULL); 
	g_win_hwnd = hWnd;
	// hWnd=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_FORMVIEW1),NULL,0);  
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, 5);  
	UpdateWindow(hWnd);  
	// 消息循环  
	MSG msg;  
	while(GetMessage(&msg,NULL,0,0))  {  
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}  

	return TRUE;
}


// 处理对话框消息  
INT_PTR CALLBACK NewDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)  
{ 
	int ret_num;
	HWND hwnd;
	WCHAR buff[32];
	switch (msg)  
	{  
	case WM_COMMAND:  
		{  
			switch(LOWORD(wParam))  { 
			case IDC_BUTTON3: 

				ret_num = GetDlgItemText(hdlg,IDC_EDIT1,buff,32);

				//注释部分是另一种获取文本框文本的写法
				hwnd = GetDlgItem(hdlg,IDC_EDIT1); 
				ret_num = GetWindowText(hwnd, buff, 32 );

				MessageBox(hdlg, buff, L"提示", MB_OK | MB_ICONINFORMATION); 

				SendMessage(g_win_hwnd, WM_CLOSE, 0, 0);
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
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (message)
	{
	case WM_CREATE:  
		{  
			// 创建对话框  
			HWND hdlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_FORMVIEW1), hWnd, (DLGPROC)NewDlgProc);  
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
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, NewAbout);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		//	case WM_PAINT:
		//		hdc = BeginPaint(hWnd, &ps);
		//		// TODO: 在此添加任意绘图代码...
		//		EndPaint(hWnd, &ps);
		//		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK NewAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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