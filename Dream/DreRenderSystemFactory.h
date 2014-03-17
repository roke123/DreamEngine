#ifndef __DRERENDERSYSTEMFACTORY_H__
#define __DRERENDERSYSTEMFACTORY_H__

#include "DreRenderDeclaration.h"

namespace dream
{
	class DRE_EXPORT_CLASS RenderSystemFactory
	{
	public:
		static RenderSystemPtr CreateD3D11RenderSystem(AdapterPtr adapter);

		/** 取D3D11渲染设备
		* @param	index		渲染设备索引
		* @remark	当索引无对应渲染设备
		*/
		static AdapterPtr GetD3D11RenderAdapter(u32 index);
	};

}	// end namespace dream

#endif	// end __DRERENDERSYSTEMFACTORY_H__