#include "DreException.h"

#include <assert.h>
#include <iostream>

namespace dream
{

	DRE_EXPORT_CLASS void DreAssert_Impl(bool condition, const string& message, const char* filename, int line)
	{
#		if defined(DEBUG) || defined(_DEBUG)
			if(!condition)
			{
				std::cerr << "File: " << filename << " Line: " << line << " Error: "<< message.c_str() << std::endl;
				assert(condition && message.c_str());
			}	
#		endif
	}

	DRE_EXPORT_CLASS void DreAssert_Impl(bool condition, const c8* message, const char* filename, int line)
	{
#		if defined(DEBUG) || defined(_DEBUG)
			if(!condition)
			{
				std::cerr << "File: " << filename << " Line: " << line << " Error: "<< message << std::endl;
				assert(condition && message);
			}
#		endif
	}

}	// end namespace dream