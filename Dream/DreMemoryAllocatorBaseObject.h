/////////////////////////////////////
// date: 2014/9/10 15:31
// author: zou lei
////////////////////////////////////

#ifndef __DRE_MEMORY_ALLOCATOR_BASE_OBJECT_H__
#define __DRE_MEMORY_ALLOCATOR_BASE_OBJECT_H__

#include "DreComplieConfig.h"

namespace dream
{
	/** \addtogroup Core
	*  @{
	*/

	/** \addtogroup Memory
	*  @{
	*/

	

	template<class Alloc>
	class DRE_EXPORT_CLASS_TEMPLATE MemoryAllocatorBase
	{
	public:
		explicit MemoryAllocatorBase() { }

		/// 虚析构函数
		virtual ~MemoryAllocatorBase() { }

		/// 带调试信息的内存分配操作
		void* operator new(size_t sz, const char* file, int line, const char* func)
		{
			return Alloc::allocateBytes(sz, file, line, func);
		}

		void* operator new(size_t sz)
		{
			return Alloc::allocateBytes(sz);
		}

		void* operator new(size_t sz, void* ptr)
		{
			(void)sz;
			return ptr;
		}

		/// 带调试信息的数组内存分配操作
		void* operator new[](size_t sz, const char* file, int line, const char* func)
		{
			return Alloc::allocateBytes(sz, file, line, func);
		}

		void* operator new[](size_t sz)
		{
			return Alloc::allocateBytes(sz);
		}

		void operator delete(void* ptr)
		{
			Alloc::deallocateBytes(ptr);
		}

		void operator delete(void* ptr, void*)
		{
			Alloc::deallocateBytes(ptr);
		}

		void operator delete(void* ptr, const char*, int, const char*)
		{
			Alloc::deallocateBytes(ptr);
		}

		void operator delete[](void* ptr)
		{
			Alloc::deallocateBytes(ptr);
		}

		void operator delete[](void* ptr, const char*, int, const char*)
		{
			Alloc::deallocateBytes(ptr);
		}
	};

	/** @} */
	/** @} */

}

#endif	// end of __DRE_MEMORY_ALLOCATOR_BASE_OBJECT_H__