#pragma once

#include <list>
#include <functional>
#include <algorithm>

namespace common {

/**
 * 通知者支持
 * @author CaoShuhao
 * @date 2014-1-15
 */
template <typename ObserverT> class observer_list {
public:
	/**
	 * 注册观察者
	 * @param observer [in] 观察者
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	void regist(ObserverT* observer) {
		_list.push_back(observer);
	}

	/**
	 * 注销观察者
	 * @param observer [in] 观察者
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	void unregister(ObserverT* observer) {
		_list.erase(std::remove(_list.begin(), _list.end(), observer), _list.end());
	}

	/**
	 * 遍历观察者
	 * @param f [in] 回调函数对象
	 * @author CaoShuhao
	 * @date 2014-1-15
	 */
	void each_observer(std::function<void (ObserverT*)> f) const {
		std::for_each(_list.begin(), _list.end(), [f] (ObserverT* p) { f(p); });
	}

private:
	/** 观察者列表 */
	std::list<ObserverT*> _list;
};

} // namespace common
