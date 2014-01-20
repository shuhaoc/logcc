#include "stdafx.h"
#include "SimpleTaskMessageWindow.h"

UINT SimpleTaskMessageWindow::InternalMessageId = ::RegisterWindowMessage(_T("{B4DACDED-4AC4-4636-9BCC-EEFB76E24538}"));

SimpleTaskMessageWindow::SimpleTaskMessageWindow() {
	internalWnd = ::CreateWindow(WndClass.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL,
		WndClass.hInstance, 0);
}

SimpleTaskMessageWindow::~SimpleTaskMessageWindow() {
	::DestroyWindow(internalWnd);
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