//////////////////////////////////////
// date: 2014/9/2 17:35
// author: zoulei
//////////////////////////////////////

#ifndef __DREROOT_H__
#define __DREROOT_H__

#include "DreRenderDeclaration.h"

namespace dream
{
	class StartPoint {
	public:
		static RenderSystemPtr renderSystem;

	public:
		bool StartUp();

		void Run();
	};
}

#endif	// end __DREROOT_H__