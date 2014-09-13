#ifndef __DREUTILITY_H__
#define __DREUTILITY_H__

namespace dream
{
	
#define SafeDelete(ptr)					if(ptr != nullptr) { delete ptr; ptr = nullptr; }
#define SafeDeleteArray(ptr)			if(ptr != nullptr) { delete [] ptr; ptr = nullptr; }

#define IgnoreParameter(param)			(void)param;

}

#endif	// end __DRETILITY_H__