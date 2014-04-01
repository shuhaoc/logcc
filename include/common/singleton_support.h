#pragma once

namespace common {

/**
 * 单件支持，不具备线程安全
 */
template <typename T> class singleton_support {
public:
	/**
	 * 获取单件对象指针，用户不可释放
	 * @return 单件对象指针
	 */
	static T* GetInstance() {
		if (!Instance) {
			Instance = new T();
		}
		return Instance;
	}

	/**
	 * 释放单件对象
	 */
	static void Release() {
		delete Instance;
		Instance = NULL;
	}

protected:
	// 禁用直接构造
	singleton_support() { }
	
	virtual ~singleton_support() { }

	// 如果单件类作为DLL导出类，将导致链接错误
	// 禁用拷贝构造、赋值操作符
	//singleton_support(const singleton_support&);

	//singleton_support& operator= (const singleton_support&);

private:
	static T* Instance;
};

} // namespace common

// 在单件类的声明中添加此宏
// 如果单件类作为DLL导出类，必须添加此声明
#define COMMON_SINGLETON_SUPPORT_DECLARE(ClassName) friend class \
common::singleton_support<ClassName>;

// 在单件类的cpp文件中添加此宏
#define COMMON_SINGLETON_SUPPORT_IMPLEMENT(ClassName) template <>	\
ClassName* common::singleton_support<ClassName>::Instance = NULL;