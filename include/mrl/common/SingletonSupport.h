#pragma once

namespace mrl {
namespace common {

/**
 * 单件支持，不具备线程安全
 * @author CaoShuhao
 * @date 2013-11-21
 */
template <typename T>
class SingletonSupport {
public:
	/**
	 * 获取单件对象指针，用户不可释放
	 * @return 单件对象指针
	 * @author CaoShuhao
	 * @date 2013-11-21
	 */
	static T* GetInstance() {
		if (!Instance)
		{
			Instance = new T();
		}
		return Instance;
	}

	/**
	 * 释放单件对象
	 * @author CaoShuhao
	 * @date 2013-11-21
	 */
	static void Release() {
		delete Instance;
		Instance = NULL;
	}

protected:
	// 禁用直接构造
	SingletonSupport() { }
	
	virtual ~SingletonSupport() { }

	// 如果单件类作为DLL导出类，将导致链接错误
	// 禁用拷贝构造、赋值操作符
	//SingletonSupport(const SingletonSupport&);

	//SingletonSupport& operator= (const SingletonSupport&);

private:
	static T* Instance;
};

} // namespace common
} // namespace mrl

// 在单件类的声明中添加此宏
// 如果单件类作为DLL导出类，必须添加此声明
#define SHLIB_COMMON_SINGLETON_SUPPORT_DECLARE(ClassName) friend class \
mrl::common::SingletonSupport<ClassName>;

// 在单件类的cpp文件中添加此宏
#define SHLIB_COMMON_SINGLETON_SUPPORT_IMPLEMENT(ClassName) template <>	\
ClassName* mrl::common::SingletonSupport<ClassName>::Instance = NULL;