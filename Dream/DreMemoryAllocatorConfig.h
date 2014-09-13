////////////////////////////////////////////
// date: 2014/9/10 15:16
// author: zou lei
////////////////////////////////////////////

#ifndef __DRE_MEMORY_ALLOCATOR_CONFIG_H__
#define __DRE_MEMORY_ALLOCATOR_CONFIG_H__

#include "DreMemoryStdAlloc.h"

namespace dream
{

	template <MemoryCategory Cat> class CategorisedAllocPolicy : public StdAllocPolicy{};
	template <MemoryCategory Cat, size_t align = 0> class CategorisedAlignAllocPolicy : public StdAlignedAllocPolicy<align>{};

#	define DREAM_NEW			new //(__FILE__, __LINE__, __FUNCTION__)
#	define DREAM_DELETE			delete

}	// end of namespace dream

#endif	// end of __DRE_MEMORY_ALLOCATOR_CONFIG_H__