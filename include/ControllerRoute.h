#pragma once

#include <hash_map>
#include "ControllerBase.h"
#include "ViewBase.h"
#include "IModelFactory.h"

template <typename ModelT> class ControllerRoute {
public:
	template <typename ViewDataT> static void addRoute(
		ViewBase<ModelT, ViewDataT>* view, ControllerBase<ModelT, ViewDataT>* controller, IModelFactory<ModelT>* factory);
	
private:
	static std::hash_map<HWND, HWND> routeMap;

	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static std::hash_map<HWND, WNDPROC> originWndProcMap;
};

template <typename ModelT> std::hash_map<HWND, HWND> ControllerRoute<ModelT>::routeMap;

template <typename ModelT> std::hash_map<HWND, WNDPROC> ControllerRoute<ModelT>::originWndProcMap;

template <typename ModelT> template<typename ViewDataT> void ControllerRoute<ModelT>::addRoute(
		ViewBase<ModelT, ViewDataT>* view, ControllerBase<ModelT, ViewDataT>* controller, IModelFactory<ModelT>* factory) {
	CWnd* viewWnd = dynamic_cast<CWnd*>(view);
	CWnd* controllerWnd = dynamic_cast<CWnd*>(controller);
	
	assert(viewWnd && controller);
	assert(!routeMap[viewWnd->GetSafeHwnd()]);
	routeMap[viewWnd->GetSafeHwnd()] = controllerWnd->GetSafeHwnd();
	
	originWndProcMap[viewWnd->GetSafeHwnd()] = reinterpret_cast<WNDPROC>(::SetWindowLong(
		viewWnd->GetSafeHwnd(), GWL_WNDPROC, reinterpret_cast<LONG>(ControllerRoute::wndProc)));

	ModelT* model = factory->getModel();
	view->setModel(model);
	controller->setModel(model);
	
	controller->setViewData(view);
}

template <typename ModelT> LRESULT CALLBACK ControllerRoute<ModelT>::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	// UNDONE: 优化，针对WM_DESTROY消息移除哈希表项
	HWND controller = routeMap[hwnd];
	WNDPROC originProc = originWndProcMap[hwnd];
	LRESULT result = ::CallWindowProc(originProc, hwnd, msg, wparam, lparam);
	assert(controller);
	::SendMessage(controller, msg, wparam, lparam);
	return result;
}