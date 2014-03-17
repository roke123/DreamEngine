#ifndef __DREVIEWPORT_H__
#define __DREVIEWPORT_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	struct DRE_EXPORT_CLASS Viewport
	{
		f32 mTopLeftX;
		f32 mTopLeftY;
		f32 mWidth;
		f32 mHeight;
		f32 mMinDepth;
		f32 mMaxDepth;
	};	// end class Viewport

}	// end namespace dream

#endif	// end __DREVIEWPORT_H__