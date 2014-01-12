#pragma once

namespace shlib {
namespace common {

/**
 * ����֧�֣����߱��̰߳�ȫ
 * @author CaoShuhao
 * @date 2013-11-21
 */
template <typename T>
class SingletonSupport {
public:
	/**
	 * ��ȡ��������ָ�룬�û������ͷ�
	 * @return ��������ָ��
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
	 * �ͷŵ�������
	 * @author CaoShuhao
	 * @date 2013-11-21
	 */
	static void Release() {
		delete Instance;
		Instance = NULL;
	}

protected:
	// ����ֱ�ӹ���
	SingletonSupport() { }
	
	virtual ~SingletonSupport() { }

	// �����������ΪDLL�����࣬���������Ӵ���
	// ���ÿ������졢��ֵ������
	//SingletonSupport(const SingletonSupport&);

	//SingletonSupport& operator= (const SingletonSupport&);

private:
	static T* Instance;
};

} // namespace common
} // namespace shlib

// �ڵ��������������Ӵ˺�
// �����������ΪDLL�����࣬������Ӵ�����
#define SHLIB_COMMON_SINGLETON_SUPPORT_DECLARE(ClassName) friend class \
shlib::common::SingletonSupport<ClassName>;

// �ڵ������cpp�ļ�����Ӵ˺�
#define SHLIB_COMMON_SINGLETON_SUPPORT_IMPLEMENT(ClassName) template <>	\
ClassName* shlib::common::SingletonSupport<ClassName>::Instance = NULL;