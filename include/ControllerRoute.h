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
	static std::hash_map<HWND, InternalControllerBase<ModelT>*> routeMap;

	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static std::hash_map<HWND, WNDPROC> originWndProcMap;
};

template <typename ModelT> std::hash_map<HWND, InternalControllerBase<ModelT>*> ControllerRoute<ModelT>::routeMap;

template <typename ModelT> std::hash_map<HWND, WNDPROC> ControllerRoute<ModelT>::originWndProcMap;

template <typename ModelT> template<typename ViewDataT> void ControllerRoute<ModelT>::addRoute(
		ViewBase<ModelT, ViewDataT>* view, ControllerBase<ModelT, ViewDataT>* controller, IModelFactory<ModelT>* factory) {
	CWnd* viewWnd = dynamic_cast<CWnd*>(view);
	
	assert(viewWnd && controller);
	assert(!routeMap[viewWnd->GetSafeHwnd()]);
	routeMap[viewWnd->GetSafeHwnd()] = controller;
	
	originWndProcMap[viewWnd->GetSafeHwnd()] = reinterpret_cast<WNDPROC>(::SetWindowLong(
		viewWnd->GetSafeHwnd(), GWL_WNDPROC, reinterpret_cast<LONG>(ControllerRoute::wndProc)));

	ModelT* model = factory->getModel();
	view->setModel(model);
	controller->setModel(model);
	
	controller->setViewData(view);
}

template <typename ModelT> LRESULT CALLBACK ControllerRoute<ModelT>::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	WNDPROC originProc = originWndProcMap[hwnd];
	LRESULT result = ::CallWindowProc(originProc, hwnd, msg, wparam, lparam);
	if (msg == WM_DESTROY) {
		routeMap.erase(hwnd);		
		::SetWindowLong(hwnd, GWL_WNDPROC, reinterpret_cast<LONG>(originProc));
		originWndProcMap.erase(hwnd);
	} else {
		InternalControllerBase<ModelT>* controller = routeMap[hwnd];
		assert(controller);
		controller->accept(msg, wparam, lparam);
	}
	return result;
}