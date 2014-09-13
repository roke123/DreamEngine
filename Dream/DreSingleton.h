///////////////////////////////////////
// date: 2014/9/9 11:48
// author: zoulei
///////////////////////////////////////

#ifndef __DRESINGLETON_H__
#define __DRESINGLETON_H__

#include "DreException.h"

namespace dream
{

	template <typename T> class Singleton
	{
	private:
		/** 禁止复制操作*/
		Singleton(const Singleton<T> &);
		Singleton& operator=(const Singleton<T> &);

	protected:
		static T* mInstance;

	public:
		Singleton(void)
		{
			DreAssert(!mInstance, "单体对象在构造前已有值");
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
			mInstance = (T*)((int)this + offset);
#else
			mInstance = static_cast< T* >(this);
#endif
		}
		~Singleton(void)
		{
			DreAssert(mInstance, "单体对象在析构前已置空");
			mInstance = nullptr;
		}
		
		static T& GetInstance(void)
		{
			assert(mInstance, "单体对象未初始化"); return (*mInstance);
		}

		static T* GetInstancePtr(void)
		{
			assert(mInstance, "单体对象未初始化"); return mInstance;
		}
	};

}

#endif	// end of __DRESINGLETON_H__