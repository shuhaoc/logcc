#pragma once

#include <hash_map>
#include "ControllerBase.h"
#include "IModelFactory.h"

template <typename ModelT> class ControllerRoute {
public:
	static void addRoute(IModelAware<ModelT>* view, IModelAware<ModelT>* controller, IModelFactory<ModelT>* factory);
	
private:
	static std::hash_map<HWND, HWND> routeMap;

	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static WNDPROC originWndProcMap;
};

template <typename ModelT> std::hash_map<HWND, HWND> ControllerRoute<ModelT>::routeMap;

template <typename ModelT> void ControllerRoute<ModelT>::addRoute(IModelAware<ModelT>* view,
		IModelAware<ModelT>* controller, IModelFactory<ModelT>* factory) {
	CWnd* viewWnd = dynamic_cast<CWnd*>(view);
	CWnd* controllerWnd = dynamic_cast<CWnd*>(controller);
	
	assert(viewWnd && controller);
	assert(!routeMap[viewWnd->GetSafeHwnd()]);
	routeMap[viewWnd->GetSafeHwnd()] = controllerWnd->GetSafeHwnd();

	ModelT* model = factory->getModel();
	view->setModel(model);
	controller->setModel(model);
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