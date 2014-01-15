#pragma once

#include <list>
#include <functional>
#include <algorithm>

namespace mrl {
namespace common {

/**
 * 通知者支持
 * @author CaoShuhao
 * @date 2014-1-15
 */
template <typename ObserverT> class ObserverContainer {
public:
	/**
	 * 注册观察者
	 * @param observer [in] 观察者
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	void registerObserver(ObserverT* observer) {
		observerList.push_back(observer);
	}

	/**
	 * 注销观察者
	 * @param observer [in] 观察者
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	void unregisterObserver(ObserverT* observer) {
		observerList.erase(std::remove(observerList.begin(), observerList.end(), observer), observerList.end());
	}

	/**
	 * 遍历观察者
	 * @param f [in] 回调函数对象
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	void forEachObserver(std::function<void (ObserverT*)> f) {
		std::for_each(observerList.begin(), observerList.end(), [f] (ObserverT* p) { f(p); });
	}

private:
	/** 观察者列表 */
	std::list<ObserverT*> observerList;
};

} // namespace common
} // namespace mrl