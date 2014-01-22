#pragma once

#include <functional>
#include <mrl/MrlExport.h>

namespace mrl {
namespace utility {

/**
 * 无参数无返回值函数的封装，带有事件
 * @author CaoShuhao
 * @date 2014-1-22
 */
class SimpleTask : private boost::noncopyable {
public:
	MRL_EXPORT SimpleTask(std::function<void ()> func);

	MRL_EXPORT ~SimpleTask();
	
	/**
	 * 执行函数体
	 * @author CaoShuhao
	 * @date 2014-1-22
	 */
	MRL_EXPORT void execute();
	
	/**
	 * 设置执行完毕事件
	 * @author CaoShuhao
	 * @date 2014-1-22
	 */
	MRL_EXPORT void signal();
	
	/**
	 * 等待执行完毕事件
	 * @param ms 毫秒数
	 * @author CaoShuhao
	 * @date 2014-1-22
	 */
	MRL_EXPORT void wait(unsigned ms = INFINITE);

private:
	std::function<void ()> func;
	HANDLE executed;
};

/**
 * 封装用于在UI线程执行函数对象的纯消息窗口
 * @author CaoShuhao
 * @date 2014-1-22
 */
class SimpleTaskMessageWindow {
public:
	MRL_EXPORT SimpleTaskMessageWindow();
	
	MRL_EXPORT ~SimpleTaskMessageWindow();
	
	/**
	 * 添加异步任务
	 * @param task 函数对象包装
	 * @author CaoShuhao
	 * @date 2014-1-22
	 */
	MRL_EXPORT SimpleTask* post(SimpleTask* task);
	
	/**
	 * 类初始化，请在模块（exe或dll）加载时调用
	 * @param module 模块句柄
	 * @author CaoShuhao
	 * @date 2014-1-22
	 */
	MRL_EXPORT static void globalInit(HINSTANCE module);
	
	/**
	 * 类释放资源，请在模块（exe或dll）卸载时调用
	 * @author CaoShuhao
	 * @date 2014-1-22
	 */
	MRL_EXPORT static void globalUninit();

private:
	static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static WNDCLASS WndClass;

	static UINT InternalMessageId;

private:
	HWND internalWnd;
};

} // namespace utility
} // namespace mrl