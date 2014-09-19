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

	/**	����׼��������ԣ�ʹ��Ĭ�Ϸ��䷽ʽ malloc/free */
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

		/// ȡ�����ɷ��䳤��
		static inline size_t GetMaxAllocationSize()
		{
			return std::numeric_limits<size_t>::max();
		}

	private:
		/// ��ֹ����ʵ�����
		StdAllocPolicy() { }
	
	};	// end of class StdAllocPolicy


	/**	����׼��������ԣ�ʹ��Ĭ�Ϸ��䷽ʽ malloc/free
	* @param
	*	Alignment		size_t		�ֽڱ߽����
	* @note
	*	�ֽڱ߽�������С�ڵ���128������0����Ϊ2�ı���*/
	template <size_t Alignment>
	class StdAlignedAllocPolicy
	{
	public:
		/// ����ʱ��飬�ֽڱ߽���������Ƿ���Ч
		typedef int IsValidAlignment
			[Alignment <= 128 && Alignment != 0 &&((Alignment & (Alignment - 1)) == 0) ? +1 : -1];

		static inline void* allocateBytes(size_t count, const char* file = 0, int line = 0, const char* func = 0)
		{
			unsigned char* p = (unsigned char*) (count + Alignment, file, line, func);
			/// ��������Ŀռ�ƫ��
			size_t offset = alignment - (size_t(p) & (alignment - 1));

			/// ȡ������ڴ�ռ�ǰ����Ϊ�հ׶Σ�����¼ƫ��
			unsigned char* result = p + offset;
			result[-1] = (unsigned char)offset;

			return result;
		}

		static inline void deallocateBytes(void* ptr)
		{
			if (ptr)
			{
				unsigned char* mem = (unsigned char*)ptr;
				// ��ȥƫ��ֵ��ȡ��ʵ�ʷ����ʼ��ַ
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
