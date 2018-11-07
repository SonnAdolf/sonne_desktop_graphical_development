// ScreenSnap.cpp : 定义应用程序的入口点。
//

#include <commctrl.h>
#include <windowsx.h>
#pragma comment(lib, "comctl32.lib")

#include "resource.h"

#define MAX_LOADSTRING 100
#define IDC_BTN_SNAP	0x1001

typedef struct tagSCREENINFO
{
	int left;
	int top;
	int width;
	int height;
} SCREENINFO, *LPSCREENINO;

// 全局变量:
HINSTANCE hInst;								// 当前实例
//TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
//TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND g_hMainWnd;
HWND g_hButton;
HWND g_hMaskDlg;

HDC g_hMemDC;
HBITMAP g_hMemBitmap1;
HBITMAP g_hBmResult; //截图结果
SIZE	g_ResultSize;

SCREENINFO scrInfo;

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MaskDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void DestroyMainWnd(HWND hWnd);
void BeginSnap(HWND hWnd);


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "Snap";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow("Snap", "截图", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 300, 300, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hMainWnd = hWnd;
	g_hButton = CreateWindowEx(0, WC_BUTTON,
		_T("开始截屏"),
		BS_PUSHBUTTON | BS_TEXT | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 
		32, 32, 128, 32,
		hWnd,
		(HMENU)(IDC_BTN_SNAP),
		hInst,
		0);

	//
	scrInfo.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
	scrInfo.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
	scrInfo.width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	scrInfo.height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//创建内存位图
	HDC hdc = GetDC(hWnd);
	g_hMemDC = CreateCompatibleDC(hdc);
	g_hMemBitmap1 = CreateCompatibleBitmap(hdc, scrInfo.width, scrInfo.height);
	ReleaseDC(hWnd, hdc);

	g_hMaskDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_MASK), 
		hWnd,  //父窗口应该为NULL，这样在MainWnd隐藏时它才能显示出来
		(DLGPROC)MaskDlgProc, 0);

	//设置图层窗口属性
	DWORD dwExStyle = (DWORD)GetWindowLongPtr(g_hMaskDlg, GWL_EXSTYLE);
	SetWindowLongPtr(g_hMaskDlg, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED);
	SetLayeredWindowAttributes(g_hMaskDlg, RGB(255, 0, 255), 0x80, LWA_COLORKEY | LWA_ALPHA);
	SetWindowPos(g_hMaskDlg, HWND_TOPMOST, 
		scrInfo.left, scrInfo.top, scrInfo.width, scrInfo.height,
		SWP_NOREDRAW | SWP_NOSENDCHANGING);

	//-------------------------------
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDC_BTN_SNAP:
			BeginSnap(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if(g_hBmResult != NULL)
		{
			HGDIOBJ hOldObj = SelectObject(g_hMemDC, g_hBmResult);
			BitBlt(hdc, 0, 0, g_ResultSize.cx, g_ResultSize.cy, g_hMemDC, 0, 0, SRCCOPY);
			SelectObject(g_hMemDC, hOldObj);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DestroyMainWnd(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Mask DlgProc:
LRESULT CALLBACK MaskDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT ptDown, ptLast;
	static BOOL bMouseDown;
	static int left, top, right, bottom, width, height;
	static int lineSize, halfLineSize;
	static HBRUSH hRedBrush;

	switch (message)
	{
	case WM_INITDIALOG:
		bMouseDown = FALSE;
		lineSize = 2;
		halfLineSize = max(1, lineSize / 2);
		lineSize = halfLineSize * 2;
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		return TRUE;

	case WM_PAINT:
		{
			RECT rcClient;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hDlg, &ps);
			HBRUSH hStockBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

			GetClientRect(hDlg, &rcClient);

			if(width > 0 || height > 0)
			{
				//把截图外面的部分填充灰色
				HRGN hRgn1 = CreateRectRgn(rcClient.left, 
					rcClient.top, 
					rcClient.right, 
					rcClient.bottom);

				HRGN hRgn2 = CreateRectRgn(left - halfLineSize, 
					top - halfLineSize, 
					right + halfLineSize, 
					bottom + halfLineSize);

				HRGN hRgn3 = CreateRectRgn(left + halfLineSize, 
					top + halfLineSize, 
					right - halfLineSize, 
					bottom - halfLineSize);

				CombineRgn(hRgn1, hRgn1, hRgn2, RGN_DIFF);
				CombineRgn(hRgn2, hRgn2, hRgn3, RGN_DIFF);

				FillRgn(hdc, hRgn1, hStockBrush);
				FillRgn(hdc, hRgn2, hRedBrush);
				DeleteObject(hRgn1);
				DeleteObject(hRgn2);
				DeleteObject(hRgn3);

				HGDIOBJ hOldObj = SelectObject(g_hMemDC, g_hMemBitmap1);
				BitBlt(hdc, 
					left + halfLineSize, 
					top + halfLineSize, 
					width - lineSize, 
					height - lineSize,

					g_hMemDC, 
					left + halfLineSize, 
					top + halfLineSize, 
					SRCCOPY);
				SelectObject(g_hMemDC, hOldObj);
			}
			else
			{
				FillRect(hdc, &rcClient, hStockBrush);
			}
			EndPaint(hDlg, &ps);
		}
		break;

	case WM_ERASEBKGND:
		return TRUE;

	case WM_LBUTTONDOWN:
		ptDown.x = GET_X_LPARAM(lParam);
		ptDown.y = GET_Y_LPARAM(lParam);
		bMouseDown = TRUE;
		SetCapture(hDlg);
		break;

	case WM_MOUSEMOVE:
		{
			if(!bMouseDown)
				return FALSE;

			RECT rc0 = { left - halfLineSize, top - halfLineSize, right + halfLineSize, bottom + halfLineSize };

			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);

			ptLast.x = x;
			ptLast.y = y;
			
			left = min(ptDown.x, ptLast.x);
			top = min(ptDown.y, ptLast.y);
			right = max(ptDown.x, ptLast.x);
			bottom = max(ptDown.y, ptLast.y);

			width = right - left;
			height = bottom - top;	

			RECT rc1 = { left - halfLineSize, top - halfLineSize, right + halfLineSize, bottom + halfLineSize };
			RECT rcResult;
			UnionRect(&rcResult, &rc0, &rc1);
			InvalidateRect(hDlg, &rcResult, FALSE);
		}
		break;

	case WM_LBUTTONUP:
		{
			bMouseDown = FALSE;
			ReleaseCapture();

			//保存截图结果
			if(g_hBmResult != NULL)
				DeleteObject(g_hBmResult);

			g_ResultSize.cx = width;
			g_ResultSize.cy = height;

			if(g_ResultSize.cx > 0 && g_ResultSize.cy > 0)
			{
				HDC hdc = GetDC(g_hMainWnd);
				HDC hMemDC = CreateCompatibleDC(hdc);
				g_hBmResult = CreateCompatibleBitmap(hdc, width, height);
				ReleaseDC(g_hMainWnd, hdc);

				HGDIOBJ hOldObj0 = SelectObject(g_hMemDC, g_hMemBitmap1);
				HGDIOBJ hOldObj1 = SelectObject(hMemDC, g_hBmResult);

				BitBlt(hMemDC, 0, 0, width, height, g_hMemDC, left, top, SRCCOPY);
				SelectObject(g_hMemDC, hOldObj0);
				SelectObject(hMemDC, hOldObj1);
				DeleteDC(hMemDC);
			}

			//把 width 和 height 清零可以使下次截屏时，清除本次截屏的残留红色边框等。
			width = 0;
			height = 0;

			SetWindowPos(hDlg, NULL, -1000000, -1000000, 0, 0, 
				SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_NOZORDER);

			ShowWindow(hDlg, SW_HIDE);
			ShowWindow(g_hMainWnd, SW_SHOW);
		}
		break;

	case WM_DESTROY:
		DeleteObject(hRedBrush);
		return TRUE;
	}
	return FALSE;
}

void DestroyMainWnd(HWND hWnd)
{
	DestroyWindow(g_hButton);
	DestroyWindow(g_hMaskDlg);
	DeleteDC(g_hMemDC);
	DeleteObject(g_hMemBitmap1);

	if(g_hBmResult != NULL)
		DeleteObject(g_hBmResult);
}

void BeginSnap(HWND hWnd)
{
	ShowWindow(g_hMainWnd, SW_HIDE);	

	//获取屏幕位图到内存位图
	HDC hdcScreen = GetDC(NULL);
	HGDIOBJ hOldObj = SelectObject(g_hMemDC, g_hMemBitmap1);
	
	BitBlt(g_hMemDC, 0, 0, scrInfo.width, scrInfo.height,
		hdcScreen, scrInfo.left, scrInfo.top, SRCCOPY);

	SelectObject(g_hMemDC, hOldObj);
	ReleaseDC(NULL, hdcScreen);

	//UpdateWindow(g_hMaskDlg);
	SetWindowPos(g_hMaskDlg, NULL, scrInfo.left, scrInfo.top, 0, 0, 
		SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_NOZORDER);

	ShowWindow(g_hMaskDlg, SW_SHOW);
	//接下来等待鼠标按下
}
INT_PTR CALLBACK DialogProc(HWND hwndDlg,
	UINT Message,
	WPARAM wParam,
	LPARAM lParam
	)
{
	HBITMAP hBmp;
	switch (Message)
	{
	case WM_INITDIALOG:
		hBmp = (HBITMAP)lParam;
		break;
	}
}
int APIENTRY ScreenSnap(HINSTANCE hInstance, HBITMAP hBmp)
{
/*	MSG msg;
	HACCEL hAccelTable;

//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadString(hInstance, IDC_SCREENSNAP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, SW_SHOW))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInst, (LPCTSTR)IDR_ACCELERATOR);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
	*/
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SNAP), GetForegroundWindow(), DialogProc, (LPARAM)hBmp);
}