#ifndef __D3D11RENDERMAPPING_H__
#define __D3D11RENDERMAPPING_H__

#include "DreD3D11RenderDeclaration.h"

namespace dream
{

	class D3D11RenderMapping
	{
	public:
		static D3D11_BLEND					Get(DRE_BLEND_COLOR_FACTOR blend) throw();

		static D3D11_BLEND_OP				Get(DRE_BLEND_OPERATION op) throw();

		static D3D11_BLEND					Get(DRE_BLEND_ALPHA_FACTOR blend) throw();

		static D3D11_COMPARISON_FUNC		Get(DRE_COMPARISON_FUNC func) throw();

		static D3D11_STENCIL_OP				Get(DRE_STENCIL_OPEARTION op) throw();

		static D3D11_FILL_MODE				Get(DRE_FILL_MODE mode) throw();

		static DRE_FILL_MODE				Get(D3D11_FILL_MODE mode) throw();

		static D3D11_CULL_MODE				Get(DRE_CULL_MODE mode) throw();

		static DRE_CULL_MODE				Get(D3D11_CULL_MODE mode) throw();

		static const char*					Get(DRE_VERTEX_EMELENT_SEMANTICS semantics) throw();

		static DXGI_FORMAT					Get(DRE_VERTEX_ELEMENT_TYPE) throw();

		static D3D11_PRIMITIVE_TOPOLOGY		Get(DRE_PRIMITIVE_TOPOLOGY level) throw();

		static D3D11_MAP					Get(DRE_LOCK_OPTIONS option) throw();

		static u32							GetVertexElementSize(DRE_VERTEX_ELEMENT_TYPE) throw();

		static DXGI_FORMAT					Get(DRE_PIXEL_FORMAT format) throw();

		static DRE_PIXEL_FORMAT				GetClosestSupportFormat(DRE_PIXEL_FORMAT format) throw();

		static DRE_PIXEL_FORMAT				Get(DXGI_FORMAT format) throw();

		static D3D11_USAGE					Get(DRE_BUFFER_USAGE usage) throw();
			
		static DRE_BUFFER_USAGE				Get(D3D11_USAGE usage, u32 flag) throw();

		static u32							GetCPUAccess(DRE_BUFFER_USAGE usage) throw();

		static DXGI_FORMAT					Get(DRE_INDEX_ELEMENT_TYPE type) throw();

		static D3D11_TEXTURE_ADDRESS_MODE	Get(DRE_TEXTURE_ADDRESS_MODE) throw();

		static D3D11_FILTER					Get(DRE_FILTER_OPTION op) throw();

	};	// end class D3D11RenderMapping

}	// end namespace dream

#endif	// end __D3D11RENDERMAPPING_H__