#pragma once

typedef std::function<void ()> SimpleTask;

class SimpleTaskMessageWindow {
public:
	SimpleTaskMessageWindow();
	
	~SimpleTaskMessageWindow();

	void post(SimpleTask* task);

	static void globalInit(HINSTANCE module);

	static void globalUninit();

private:
	static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static WNDCLASS WndClass;

	static UINT InternalMessageId;

private:
	HWND internalWnd;
};