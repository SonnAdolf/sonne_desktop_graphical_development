#pragma once

#include "resource.h"


// 此代码模块中包含的函数的前向声明:
ATOM				NewMyRegisterClass(HINSTANCE hInstance);
BOOL				NewInitInstance(HINSTANCE, int);
LRESULT CALLBACK	NewWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	NewAbout(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK NewDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL NewInitInstance(HINSTANCE hInstance, HWND hWndPar, int nCmdShow);