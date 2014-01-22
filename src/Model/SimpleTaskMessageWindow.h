#pragma once

class SimpleTask : private boost::noncopyable {
public:
	SimpleTask(std::function<void ()> func);

	~SimpleTask();

	void execute();

	void signal();

	void wait(unsigned ms = INFINITE);

private:
	std::function<void ()> func;
	HANDLE executed;
};

class SimpleTaskMessageWindow {
public:
	SimpleTaskMessageWindow();
	
	~SimpleTaskMessageWindow();

	SimpleTask* post(SimpleTask* task);

	static void globalInit(HINSTANCE module);

	static void globalUninit();

private:
	static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static WNDCLASS WndClass;

	static UINT InternalMessageId;

private:
	HWND internalWnd;
};