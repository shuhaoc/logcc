// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "SimpleTaskMessageWindow.h"

WNDCLASS SimpleTaskMessageWindow::WndClass;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// UNDONE: 逻辑抽出
		SimpleTaskMessageWindow::WndClass.style = 0;
		SimpleTaskMessageWindow::WndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(SimpleTaskMessageWindow::WndProc); 
		SimpleTaskMessageWindow::WndClass.cbClsExtra = 0; 
		SimpleTaskMessageWindow::WndClass.cbWndExtra = 0; 
		SimpleTaskMessageWindow::WndClass.hInstance = hModule; 
		SimpleTaskMessageWindow::WndClass.hIcon = NULL;
		SimpleTaskMessageWindow::WndClass.hCursor = NULL;
		SimpleTaskMessageWindow::WndClass.hbrBackground = NULL;
		SimpleTaskMessageWindow::WndClass.lpszMenuName = NULL;
		SimpleTaskMessageWindow::WndClass.lpszClassName = _T("{A42CE85C-6121-4CA5-B39C-6B0864234E9B}");
		::RegisterClass(&SimpleTaskMessageWindow::WndClass);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		::UnregisterClass(SimpleTaskMessageWindow::WndClass.lpszClassName, hModule);
		break;
	}
	return TRUE;
}

