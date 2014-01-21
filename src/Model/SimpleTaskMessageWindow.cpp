#include "stdafx.h"
#include "SimpleTaskMessageWindow.h"

UINT SimpleTaskMessageWindow::InternalMessageId = ::RegisterWindowMessage(_T("{B4DACDED-4AC4-4636-9BCC-EEFB76E24538}"));

WNDCLASS SimpleTaskMessageWindow::WndClass;

void SimpleTaskMessageWindow::globalInit(HINSTANCE module) {
	SimpleTaskMessageWindow::WndClass.style = 0;
	SimpleTaskMessageWindow::WndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(SimpleTaskMessageWindow::WndProc); 
	SimpleTaskMessageWindow::WndClass.cbClsExtra = 0;
	SimpleTaskMessageWindow::WndClass.cbWndExtra = 0;
	SimpleTaskMessageWindow::WndClass.hInstance = module;
	SimpleTaskMessageWindow::WndClass.hIcon = NULL;
	SimpleTaskMessageWindow::WndClass.hCursor = NULL;
	SimpleTaskMessageWindow::WndClass.hbrBackground = NULL;
	SimpleTaskMessageWindow::WndClass.lpszMenuName = NULL;
	SimpleTaskMessageWindow::WndClass.lpszClassName = _T("{A42CE85C-6121-4CA5-B39C-6B0864234E9B}");
	::RegisterClass(&SimpleTaskMessageWindow::WndClass);
}

void SimpleTaskMessageWindow::globalUninit() {
	::UnregisterClass(SimpleTaskMessageWindow::WndClass.lpszClassName,
		SimpleTaskMessageWindow::WndClass.hInstance);
}

LRESULT SimpleTaskMessageWindow::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	if (message == InternalMessageId) {
		SimpleTask* task = reinterpret_cast<SimpleTask*>(wparam);
		(*task)();
		delete task;
		return 0;
	} else {
		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}
}

SimpleTaskMessageWindow::SimpleTaskMessageWindow() {
	internalWnd = ::CreateWindow(WndClass.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL,
		WndClass.hInstance, 0);
}

SimpleTaskMessageWindow::~SimpleTaskMessageWindow() {
	::DestroyWindow(internalWnd);
}

void SimpleTaskMessageWindow::post(SimpleTask* task) {
	::PostMessage(internalWnd, InternalMessageId, reinterpret_cast<WPARAM>(task), 0);
}