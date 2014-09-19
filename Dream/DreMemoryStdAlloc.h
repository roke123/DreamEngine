/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2012 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef __MemoryStdAlloc_H__
#define __MemoryStdAlloc_H__

#include <memory>
#include <limits>

#include "DreComplieConfig.h"

namespace dream
{

	/** \addtogroup Core
	*  @{
	*/

	/** \addtogroup Memory
	*  @{
	*/

	/**	“标准”分配策略，使用默认分配方式 malloc/free */
	class DRE_EXPORT_CLASS StdAllocPolicy
	{
	public:
		static inline void* allocateBytes(size_t count, const char* file = 0, int line = 0, const char* func = 0)
		{
			void* ptr = malloc(count);
			return ptr;
		}

		static inline void deallocateBytes(void* ptr)
		{
			free(ptr);
		}

		/// 取得最大可分配长度
		static inline size_t GetMaxAllocationSize()
		{
			return std::numeric_limits<size_t>::max();
		}

	private:
		/// 禁止产生实体对象
		StdAllocPolicy() { }
	
	};	// end of class StdAllocPolicy


	/**	“标准”分配策略，使用默认分配方式 malloc/free
	* @param
	*	Alignment		size_t		字节边界对齐
	* @note
	*	字节边界对齐必须小于等于128，大于0，且为2的倍数*/
	template <size_t Alignment>
	class StdAlignedAllocPolicy
	{
	public:
		/// 运行时检查，字节边界对齐属性是否有效
		typedef int IsValidAlignment
			[Alignment <= 128 && Alignment != 0 &&((Alignment & (Alignment - 1)) == 0) ? +1 : -1];

		static inline void* allocateBytes(size_t count, const char* file = 0, int line = 0, const char* func = 0)
		{
			unsigned char* p = (unsigned char*) (count + Alignment, file, line, func);
			/// 计算多分配的空间偏移
			size_t offset = alignment - (size_t(p) & (alignment - 1));

			/// 取分配的内存空间前段作为空白段，并记录偏移
			unsigned char* result = p + offset;
			result[-1] = (unsigned char)offset;

			return result;
		}

		static inline void deallocateBytes(void* ptr)
		{
			if (ptr)
			{
				unsigned char* mem = (unsigned char*)ptr;
				// 减去偏移值，取得实际分配初始地址
				mem = mem - mem[-1];

				StdAllocPolicy::deallocateBytes(mem);
			}
		}

		/// Get the maximum size of a single allocation
		static inline size_t getMaxAllocationSize()
		{
			return StdAllocPolicy::GetMaxAllocationSize();
		}
	private: 
		StdAlignedAllocPolicy() { }
	
	};	// end of class StdAlignedAllocPolicy

	/** @} */
	/** @} */

}// namespace Ogre

#endif // __MemoryStdAlloc_H__
