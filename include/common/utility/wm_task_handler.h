#pragma once

#include <functional>

namespace common {
namespace utility {

/**
 * 无参数无返回值函数的封装，带有事件
 */
class wm_task : private boost::noncopyable {
public:
	wm_task(std::function<void ()> func);

	~wm_task();
	
	/**
	 * 执行函数体
	 */
	void execute();
	
	/**
	 * 设置执行完毕事件
	 */
	void signal();
	
	/**
	 * 等待执行完毕事件
	 * @param ms 毫秒数
	 */
	void wait(unsigned ms = INFINITE);

private:
	std::function<void ()> _func;
	HANDLE _executed;
};

/**
 * 封装用于在UI线程执行函数对象的纯消息窗口
 */
class wm_task_handler {
public:
	wm_task_handler();
	
	~wm_task_handler();
	
	/**
	 * 添加异步任务
	 * @param task 函数对象包装
	 */
	wm_task* post(wm_task* task);
	
	/**
	 * 类初始化，请在模块（exe或dll）加载时调用
	 * @param module 模块句柄
	 */
	static void ginit(HINSTANCE module);
	
	/**
	 * 类释放资源，请在模块（exe或dll）卸载时调用
	 */
	static void guninit();

private:
	static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static WNDCLASS WndClass;

	static UINT InternalMessageId;

private:
	HWND _internalWnd;
};

} // namespace utility
} // namespace common
