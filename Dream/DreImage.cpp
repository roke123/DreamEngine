#include "DreImage.h"

namespace dream
{

	Image::Image(u32 width, u32 height, DRE_PIXEL_FORMAT format, bool isCopy /* = false */) :
		mWidth(width), mHeight(height), mFormat(format), mIsCopy(isCopy)
	{
		// Áô¿Õ
	}

}	// end namespace dream