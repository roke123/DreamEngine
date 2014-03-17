#ifndef __DRERENDERSYSTEMFACTORY_H__
#define __DRERENDERSYSTEMFACTORY_H__

#include "DreRenderDeclaration.h"

namespace dream
{
	class DRE_EXPORT_CLASS RenderSystemFactory
	{
	public:
		static RenderSystemPtr CreateD3D11RenderSystem(AdapterPtr adapter);

		/** ȡD3D11��Ⱦ�豸
		* @param	index		��Ⱦ�豸����
		* @remark	�������޶�Ӧ��Ⱦ�豸
		*/
		static AdapterPtr GetD3D11RenderAdapter(u32 index);
	};

}	// end namespace dream

#endif	// end __DRERENDERSYSTEMFACTORY_H__