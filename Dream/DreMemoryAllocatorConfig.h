////////////////////////////////////////////
// date: 2014/9/10 15:16
// author: zou lei
////////////////////////////////////////////

#ifndef __DRE_MEMORY_ALLOCATOR_CONFIG_H__
#define __DRE_MEMORY_ALLOCATOR_CONFIG_H__

#include "DreMemoryStdAlloc.h"

namespace dream
{

	class CategorisedAllocPolicy : public StdAllocPolicy {};
	template<size_t align> class CategorisedAlignAllocPolicy : public StdAlignedAllocPolicy<align>{};

#	define DREAM_MALLOC(bytes, category)		CategorisedAllocPolicy::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
#	define DREAM_FREE(ptr, category)			CategorisedAllocPolicy::deallocateBytes((void*)ptr)

#	define DREAM_NEW			new //(__FILE__, __LINE__, __FUNCTION__)
#	define DREAM_DELETE			delete

}	// end of namespace dream

#endif	// end of __DRE_MEMORY_ALLOCATOR_CONFIG_H__