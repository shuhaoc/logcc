#include "stdafx.h"
#include "common/utility/wm_task_handler.h"

using namespace common::utility;

wm_task::wm_task(std::function<void ()> func) : _func(func) {
	_executed = ::CreateEvent(NULL, FALSE, FALSE, NULL);
}

wm_task::~wm_task() {
	::CloseHandle(_executed);
}

void wm_task::execute() {
	_func();
}

void wm_task::signal() {
	::SetEvent(_executed);
}

void wm_task::wait(unsigned ms /*= INFINITE*/) {
	::WaitForSingleObject(_executed, ms);
}

UINT wm_task_handler::InternalMessageId = ::RegisterWindowMessage(_T("{B4DACDED-4AC4-4636-9BCC-EEFB76E24538}"));

WNDCLASS wm_task_handler::WndClass;

void wm_task_handler::ginit(HINSTANCE module) {
	wm_task_handler::WndClass.style = 0;
	wm_task_handler::WndClass.lpfnWndProc = reinterpret_cast<WNDPROC>(wm_task_handler::WndProc); 
	wm_task_handler::WndClass.cbClsExtra = 0;
	wm_task_handler::WndClass.cbWndExtra = 0;
	wm_task_handler::WndClass.hInstance = module;
	wm_task_handler::WndClass.hIcon = NULL;
	wm_task_handler::WndClass.hCursor = NULL;
	wm_task_handler::WndClass.hbrBackground = NULL;
	wm_task_handler::WndClass.lpszMenuName = NULL;
	wm_task_handler::WndClass.lpszClassName = _T("{A42CE85C-6121-4CA5-B39C-6B0864234E9B}");
	::RegisterClass(&wm_task_handler::WndClass);
}

void wm_task_handler::guninit() {
	::UnregisterClass(wm_task_handler::WndClass.lpszClassName,
		wm_task_handler::WndClass.hInstance);
}

LRESULT wm_task_handler::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	if (message == InternalMessageId) {
		wm_task* task = reinterpret_cast<wm_task*>(wparam);
		task->execute();
		task->signal();
		delete task;
		return 0;
	} else {
		return ::DefWindowProc(hwnd, message, wparam, lparam);
	}
}

wm_task_handler::wm_task_handler() {
	_internalWnd = ::CreateWindow(WndClass.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL,
		WndClass.hInstance, 0);
}

wm_task_handler::~wm_task_handler() {
	::DestroyWindow(_internalWnd);
}

wm_task* wm_task_handler::post(wm_task* task) {
	::PostMessage(_internalWnd, InternalMessageId, reinterpret_cast<WPARAM>(task), 0);
	return task;
}