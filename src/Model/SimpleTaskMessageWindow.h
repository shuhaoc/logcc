#pragma once

typedef std::function<void ()> SimpleTask;

class SimpleTaskMessageWindow {
public:
	SimpleTaskMessageWindow();
	
	~SimpleTaskMessageWindow();

	void post(SimpleTask* task) {
		::PostMessage(internalWnd, InternalMessageId, reinterpret_cast<WPARAM>(task), 0);
	}

	static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static WNDCLASS WndClass;

private:
	static UINT InternalMessageId;

	HWND internalWnd;
};