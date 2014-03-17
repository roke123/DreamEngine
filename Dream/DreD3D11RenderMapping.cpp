#include "DreD3D11RenderMapping.h"
#include "DreException.h"

namespace dream
{
	/// 对应顶点元素语义的语义名
	const char* D3D11VertexElementSemanticsName[] = 
	{
		"POSITION",
		"BLENDWEIGHTS",
		"BLENDINDICES",
		"NORMAL",
		"DIFFUSE",
		"SPECULAR",
		"TEXCOORD",
		"BINORMAL",
		"TANGENT",
		"CUSTOM",
	};	// end string array D3D11VertexElementSemanticsName

	D3D11_BLEND D3D11RenderMapping::Get(DRE_BLEND_COLOR_FACTOR blend) throw()
	{
		D3D11_BLEND ret = D3D11_BLEND_ZERO;

		switch (blend)
		{
		case dream::DRE_BLEND_ZERO_COLOR:
			ret = D3D11_BLEND_ZERO; break;
		case dream::DRE_BLEND_ONE_COLOR:
			ret = D3D11_BLEND_ONE; break;
		case dream::DRE_BLEND_COLOR_FROM_RENDER_TARGET:
			ret = D3D11_BLEND_DEST_COLOR; break;
		case dream::DRE_BLEND_INV_COLOR_FROM_RENDER_TARGET:
			ret = D3D11_BLEND_INV_DEST_COLOR; break;
		case dream::DRE_BLEND_COLOR_FROM_PIXEL_SHADER:
			ret = D3D11_BLEND_SRC_COLOR; break;
		case dream::DRE_BLEND_INV_COLOR_FROM_PIXEL_SHADER:
			ret = D3D11_BLEND_INV_SRC_COLOR; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_BLEND_OP D3D11RenderMapping::Get(DRE_BLEND_OPERATION op) throw()
	{
		D3D11_BLEND_OP ret = D3D11_BLEND_OP_ADD;

		switch (op)
		{
		case dream::DRE_BLEND_ADD_OPERATION:
			ret = D3D11_BLEND_OP_ADD; break;
		case dream::DRE_BLEND_SUBTRACT_OPERATION:
			ret = D3D11_BLEND_OP_SUBTRACT; break;
		case dream::DRE_BLEND_REVERSE_SUBTRACT_OPERATION:
			ret = D3D11_BLEND_OP_REV_SUBTRACT; break;
		case dream::DRE_BLEND_MIN_OPERATION:
			ret = D3D11_BLEND_OP_MIN; break;
		case dream::DRE_BLEND_MAX_OPERATION:
			ret = D3D11_BLEND_OP_MAX; break;
		default:
			break;
		}

		return ret;
	}
	
	D3D11_BLEND D3D11RenderMapping::Get(DRE_BLEND_ALPHA_FACTOR blend) throw()
	{
		D3D11_BLEND ret = D3D11_BLEND_ZERO;

		switch (blend)
		{
		case dream::DRE_BLEND_ZERO_ALPHA:
			ret = D3D11_BLEND_ZERO; break;
		case dream::DRE_BLEND_ONE_ALPHA:
			ret = D3D11_BLEND_ONE; break;
		case dream::DRE_BLEND_ALPHA_FROM_RENDER_TARGET:
			ret = D3D11_BLEND_DEST_COLOR; break;
		case dream::DRE_BLEND_INV_ALPHA_FROM_RENDER_TARGET:
			ret = D3D11_BLEND_INV_DEST_COLOR; break;
		case dream::DRE_BLEND_ALPHA_FROM_PIXEL_SHADER:
			ret = D3D11_BLEND_SRC_COLOR; break;
		case dream::DRE_BLEND_INV_ALPHA_FROM_PIXEL_SHADER:
			ret = D3D11_BLEND_INV_SRC_COLOR; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_COMPARISON_FUNC D3D11RenderMapping::Get(DRE_COMPARISON_FUNC func) throw()
	{
		D3D11_COMPARISON_FUNC ret = D3D11_COMPARISON_ALWAYS;

		switch (func)
		{
		case dream::DRE_COMPARISON_NEVER:
			ret = D3D11_COMPARISON_NEVER; break;
		case dream::DRE_COMPARISON_LESSEQUAL:
			ret = D3D11_COMPARISON_LESS_EQUAL; break;
		case dream::DRE_COMPARISON_EQUAL:
			ret = D3D11_COMPARISON_EQUAL; break;
		case dream::DRE_COMPARISON_LESS:
			ret = D3D11_COMPARISON_LESS; break;
		case dream::DRE_COMPARISON_NOTEQUAL:
			ret = D3D11_COMPARISON_NOT_EQUAL; break;
		case dream::DRE_COMPARISON_GREATEREQUAL:
			ret = D3D11_COMPARISON_GREATER_EQUAL; break;
		case dream::DRE_COMPARISON_GREATER:
			ret = D3D11_COMPARISON_GREATER; break;
		case dream::DRE_COMPARISON_ALWAYS:
			ret = D3D11_COMPARISON_ALWAYS; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_STENCIL_OP D3D11RenderMapping::Get(DRE_STENCIL_OPEARTION op) throw()
	{
		D3D11_STENCIL_OP ret = D3D11_STENCIL_OP_KEEP;

		switch (op)
		{
		case dream::DRE_STENCIL_OPEARTION_KEEP:
			ret = D3D11_STENCIL_OP_KEEP; break;
		case dream::DRE_STENCIL_OPEARTION_ZERO:
			ret = D3D11_STENCIL_OP_ZERO; break;
		case dream::DRE_STENCIL_OPEARTION_REPLACE:
			ret = D3D11_STENCIL_OP_REPLACE; break;
		case dream::DRE_STENCIL_OPEARTION_INCR_SAT:
			ret = D3D11_STENCIL_OP_INCR_SAT; break;
		case dream::DRE_STENCIL_OPEARTION_DECR_SAT:
			ret = D3D11_STENCIL_OP_DECR_SAT; break;
		case dream::DRE_STENCIL_OPEARTION_INVERT:
			ret = D3D11_STENCIL_OP_INVERT; break;
		case dream::DRE_STENCIL_OPEARTION_INCR:
			ret = D3D11_STENCIL_OP_INCR; break;
		case dream::DRE_STENCIL_OPEARTION_DECR:
			ret = D3D11_STENCIL_OP_DECR; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_FILL_MODE D3D11RenderMapping::Get(DRE_FILL_MODE mode) throw()
	{
		D3D11_FILL_MODE ret = D3D11_FILL_SOLID;

		switch (mode)
		{
		case dream::DRE_FILL_WIREFRAME_MODE:
			break;
		case dream::DRE_FILL_SOLID_MODE:
			break;
		default:
			break;
		}

		return ret;
	}

	DRE_FILL_MODE D3D11RenderMapping::Get(D3D11_FILL_MODE mode) throw()
	{
		DRE_FILL_MODE ret = DRE_FILL_SOLID_MODE;

		switch (mode)
		{
		case D3D11_FILL_WIREFRAME:
			ret = DRE_FILL_SOLID_MODE; break;
		case D3D11_FILL_SOLID:
			ret = DRE_FILL_WIREFRAME_MODE; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_CULL_MODE D3D11RenderMapping::Get(DRE_CULL_MODE mode) throw()
	{
		D3D11_CULL_MODE ret = D3D11_CULL_FRONT;

		switch (mode)
		{
		case dream::DRE_CULL_NONE:
			ret = D3D11_CULL_NONE; break;
		case dream::DRE_CULL_FRONT:
			ret = D3D11_CULL_FRONT; break;
		case dream::DRE_CULL_BACK:
			ret = D3D11_CULL_BACK; break;
		default:
			break;
		}

		return ret;
	}

	DRE_CULL_MODE D3D11RenderMapping::Get(D3D11_CULL_MODE mode) throw()
	{
		DRE_CULL_MODE ret = DRE_CULL_FRONT;

		switch (mode)
		{
		case D3D11_CULL_NONE:
			ret = DRE_CULL_NONE; break;
		case D3D11_CULL_FRONT:
			ret = DRE_CULL_FRONT; break;
		case D3D11_CULL_BACK:
			ret = DRE_CULL_BACK; break;
		default:
			break;
		}

		return ret;
	}

	const char*	D3D11RenderMapping::Get(DRE_VERTEX_EMELENT_SEMANTICS semantics) throw()
	{
		return D3D11VertexElementSemanticsName[semantics];
	}

	DXGI_FORMAT	D3D11RenderMapping::Get(DRE_VERTEX_ELEMENT_TYPE type) throw()
	{
		DXGI_FORMAT ret = DXGI_FORMAT_UNKNOWN;

		switch (type)
		{
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT1:
			ret = DXGI_FORMAT_R32_FLOAT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT2:
			ret = DXGI_FORMAT_R32G32_FLOAT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT3:
			ret = DXGI_FORMAT_R32G32B32_FLOAT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT4:
			ret = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT1:
			ret = DXGI_FORMAT_R16_SINT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT2:
			ret = DXGI_FORMAT_R16G16_SINT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT3:
			ret = DXGI_FORMAT_UNKNOWN; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT4:
			ret = DXGI_FORMAT_R16_SINT; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_UBYTE4:
			ret = DXGI_FORMAT_R8G8B8A8_UNORM; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_COLOUR_ARGB:
			ret = DXGI_FORMAT_B8G8R8A8_UNORM;break;
		case dream::DRE_VERTEX_EMELENT_TYPE_COLOUR_ABGR:
			ret = DXGI_FORMAT_UNKNOWN;break;
		default:
			break;
		}

		return ret;
	}

	D3D11_PRIMITIVE_TOPOLOGY D3D11RenderMapping::Get(DRE_PRIMITIVE_TOPOLOGY level) throw()
	{
		D3D11_PRIMITIVE_TOPOLOGY ret = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;

		switch (level)
		{
		case dream::DRE_PRIMITIVE_TOPOLOGY::DRE_PRIMITIVE_TOPOLOGY_UNDEFINED:
			ret = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED; break;
		case dream::DRE_PRIMITIVE_TOPOLOGY::DRE_PRIMITIVE_TOPOLOGY_POINTLIST:
			ret = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST; break;
		case dream::DRE_PRIMITIVE_TOPOLOGY::DRE_PRIMITIVE_TOPOLOGY_LINELIST:
			ret = D3D11_PRIMITIVE_TOPOLOGY_LINELIST; break;
		case dream::DRE_PRIMITIVE_TOPOLOGY::DRE_PRIMITIVE_TOPOLOGY_LINESTRIP:
			ret = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP; break;
		case dream::DRE_PRIMITIVE_TOPOLOGY::DRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
			ret = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
		case dream::DRE_PRIMITIVE_TOPOLOGY::DRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
			ret = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
		default:
			break;
		}

		return ret;
	}
	
	D3D11_MAP D3D11RenderMapping::Get(DRE_LOCK_OPTIONS option) throw()
	{
		D3D11_MAP ret = D3D11_MAP_READ;

		switch (option)
		{
		case dream::DRE_LOCK_READWRITE:
			ret = D3D11_MAP_READ_WRITE; break;
		case dream::DRE_LOCK_DISCARD:
			ret = D3D11_MAP_WRITE_DISCARD; break;
		case dream::HDRE_LOCK_READ_ONLY:
			ret = D3D11_MAP_READ; break;
		case dream::DRE_LOCK_WRITE_ONLY:
			ret = D3D11_MAP_WRITE; break;
		case dream::DRE_LOCK_NO_OVERWRITE:
			ret = D3D11_MAP_WRITE_NO_OVERWRITE; break;
		default:
			break;
		}

		return ret;
	}

	u32 D3D11RenderMapping::GetVertexElementSize(DRE_VERTEX_ELEMENT_TYPE type) throw()
	{
		u32 ret = 0;

		switch (type)
		{
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT1:
			ret = sizeof(f32); break;
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT2:
			ret = sizeof(f32) * 2; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT3:
			ret = sizeof(f32) * 3; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_FLOAT4:
			ret = sizeof(f32) * 4; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT1:
			ret = sizeof(s16); break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT2:
			ret = sizeof(s16) * 2; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT3:
			ret = sizeof(s16) * 3; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_SHORT4:
			ret = sizeof(s16) * 4; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_UBYTE4:
			ret = sizeof(u8) * 4; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_COLOUR_ARGB:
			ret = sizeof(u8) * 4; break;
		case dream::DRE_VERTEX_EMELENT_TYPE_COLOUR_ABGR:
			ret = 0; break;
		default:
			break;
		}

		return ret;
	}

	
	DXGI_FORMAT D3D11RenderMapping::Get(DRE_PIXEL_FORMAT format) throw()
	{
		DXGI_FORMAT ret = DXGI_FORMAT_UNKNOWN;

		switch (format)
		{
		case dream::DRE_PIXEL_FORMAT_UNKNOWN:
			ret = DXGI_FORMAT_UNKNOWN; break;
		case dream::DRE_PIXEL_FORMAT_L_8:
			ret = DXGI_FORMAT_R8_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_L_16:
			ret = DXGI_FORMAT_R16_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_A_8:
			ret = DXGI_FORMAT_A8_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_R5G5B5A1:
			ret = DXGI_FORMAT_UNKNOWN; break;
		case dream::DRE_PIXEL_FORMAT_A1R5G5B5:
			ret = DXGI_FORMAT_B5G5R5A1_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_R5G6B5:
			ret = DXGI_FORMAT_B5G6R5_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_R8G8B8:
			ret = DXGI_FORMAT_UNKNOWN; break;
		case dream::DRE_PIXEL_FORMAT_B8G8R8:
			ret = DXGI_FORMAT_UNKNOWN; break;
		case dream::DRE_PIXEL_FORMAT_A8R8G8B8:
			ret = DXGI_FORMAT_B8G8R8A8_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_A8B8G8R8:
			ret = DXGI_FORMAT_R8G8B8A8_UNORM; break;
		case dream::DRE_PIXEL_FORMAT_B8G8R8A8:
			ret = DXGI_FORMAT_UNKNOWN; break;
		case dream::DRE_PIXEL_FORMAT_R8G8B8A8:
			ret = DXGI_FORMAT_UNKNOWN; break;
		default:
			break;
		}

		return ret;
	}

	DRE_PIXEL_FORMAT D3D11RenderMapping::GetClosestSupportFormat(DRE_PIXEL_FORMAT format) throw()
	{
		DRE_PIXEL_FORMAT ret = DRE_PIXEL_FORMAT_UNKNOWN;

		switch (format)
		{
		case dream::DRE_PIXEL_FORMAT_UNKNOWN:
			ret = DRE_PIXEL_FORMAT_UNKNOWN; break;
		case dream::DRE_PIXEL_FORMAT_L_8:
			ret = DRE_PIXEL_FORMAT_L_8; break;
		case dream::DRE_PIXEL_FORMAT_L_16:
			ret = DRE_PIXEL_FORMAT_L_16; break;
		case dream::DRE_PIXEL_FORMAT_A_8:
			ret = DRE_PIXEL_FORMAT_A_8; break;
		case dream::DRE_PIXEL_FORMAT_A1R5G5B5:
			ret = DRE_PIXEL_FORMAT_A1R5G5B5; break;
		case dream::DRE_PIXEL_FORMAT_A8B8G8R8:
			ret = DRE_PIXEL_FORMAT_A8B8G8R8; break;
		case dream::DRE_PIXEL_FORMAT_A8R8G8B8:
			ret = DRE_PIXEL_FORMAT_A8R8G8B8; break;
		
		case dream::DRE_PIXEL_FORMAT_R5G5B5A1:
		case dream::DRE_PIXEL_FORMAT_R5G6B5:
		case dream::DRE_PIXEL_FORMAT_R8G8B8:
		case dream::DRE_PIXEL_FORMAT_B8G8R8:
		case dream::DRE_PIXEL_FORMAT_B8G8R8A8:
		case dream::DRE_PIXEL_FORMAT_R8G8B8A8:
			ret = DRE_PIXEL_FORMAT_A8B8G8R8; break;
		default:
			break;
		}

		return ret;
	}

	DRE_PIXEL_FORMAT D3D11RenderMapping::Get(DXGI_FORMAT format) throw()
	{
		DRE_PIXEL_FORMAT ret = DRE_PIXEL_FORMAT_UNKNOWN;

		switch (format)
		{
		case DXGI_FORMAT_UNKNOWN:
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
		case DXGI_FORMAT_R32G32B32_TYPELESS:
		case DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT_R32G32B32_UINT:
		case DXGI_FORMAT_R32G32B32_SINT:
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_SINT:
		case DXGI_FORMAT_R32G32_TYPELESS:
		case DXGI_FORMAT_R32G32_FLOAT:
		case DXGI_FORMAT_R32G32_UINT:
		case DXGI_FORMAT_R32G32_SINT:
		case DXGI_FORMAT_R32G8X24_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		case DXGI_FORMAT_R10G10B10A2_UNORM:
		case DXGI_FORMAT_R10G10B10A2_UINT:
		case DXGI_FORMAT_R11G11B10_FLOAT:
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
			ret = DRE_PIXEL_FORMAT_UNKNOWN; break;
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			ret = DRE_PIXEL_FORMAT_A8B8G8R8; break;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
		case DXGI_FORMAT_R16G16_TYPELESS:
		case DXGI_FORMAT_R16G16_FLOAT:
		case DXGI_FORMAT_R16G16_UNORM:
		case DXGI_FORMAT_R16G16_UINT:
		case DXGI_FORMAT_R16G16_SNORM:
		case DXGI_FORMAT_R16G16_SINT:
		case DXGI_FORMAT_R32_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT:
		case DXGI_FORMAT_R32_FLOAT:
		case DXGI_FORMAT_R32_UINT:
		case DXGI_FORMAT_R32_SINT:
		case DXGI_FORMAT_R24G8_TYPELESS:
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		case DXGI_FORMAT_R8G8_TYPELESS:
		case DXGI_FORMAT_R8G8_UNORM:
		case DXGI_FORMAT_R8G8_UINT:
		case DXGI_FORMAT_R8G8_SNORM:
		case DXGI_FORMAT_R8G8_SINT:
		case DXGI_FORMAT_R16_TYPELESS:
		case DXGI_FORMAT_R16_FLOAT:
		case DXGI_FORMAT_D16_UNORM:
			ret = DRE_PIXEL_FORMAT_UNKNOWN; break;
		case DXGI_FORMAT_R16_UNORM:
			ret = DRE_PIXEL_FORMAT_L_16; break;
		case DXGI_FORMAT_R16_UINT:
		case DXGI_FORMAT_R16_SNORM:
		case DXGI_FORMAT_R16_SINT:
		case DXGI_FORMAT_R8_TYPELESS:
			ret = DRE_PIXEL_FORMAT_UNKNOWN; break;
		case DXGI_FORMAT_R8_UNORM:
			ret = DRE_PIXEL_FORMAT_L_8; break;
		case DXGI_FORMAT_R8_UINT:
		case DXGI_FORMAT_R8_SNORM:
		case DXGI_FORMAT_R8_SINT:
			ret = DRE_PIXEL_FORMAT_UNKNOWN; break;
		case DXGI_FORMAT_A8_UNORM:
			ret = DRE_PIXEL_FORMAT_A_8; break;
		case DXGI_FORMAT_R1_UNORM:
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		case DXGI_FORMAT_R8G8_B8G8_UNORM:
		case DXGI_FORMAT_G8R8_G8B8_UNORM:
		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
		case DXGI_FORMAT_BC4_TYPELESS:
		case DXGI_FORMAT_BC4_UNORM:
		case DXGI_FORMAT_BC4_SNORM:
		case DXGI_FORMAT_BC5_TYPELESS:
		case DXGI_FORMAT_BC5_UNORM:
		case DXGI_FORMAT_BC5_SNORM:
		case DXGI_FORMAT_B5G6R5_UNORM:
			ret = DRE_PIXEL_FORMAT_R5G6B5; break;
		case DXGI_FORMAT_B5G5R5A1_UNORM:
			ret = DRE_PIXEL_FORMAT_A1R5G5B5; break;
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			ret = DRE_PIXEL_FORMAT_A8R8G8B8; break;break;
		case DXGI_FORMAT_B8G8R8X8_UNORM:
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		case DXGI_FORMAT_BC6H_TYPELESS:
		case DXGI_FORMAT_BC6H_UF16:
		case DXGI_FORMAT_BC6H_SF16:
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
		case DXGI_FORMAT_FORCE_UINT:
			break;
		default:
			break;
		}

		return ret;
	}

	D3D11_USAGE D3D11RenderMapping::Get(DRE_BUFFER_USAGE usage) throw()
	{
		D3D11_USAGE ret = D3D11_USAGE_DEFAULT;

		switch (usage)
		{
		case dream::DRE_BUFFER_USAGE_DEFAULT:
			ret = D3D11_USAGE_DEFAULT; break;
		case dream::DRE_BUFFER_USAGE_STATIC:
			ret = D3D11_USAGE_STAGING; break;
		case dream::DRE_BUFFER_USAGE_DYNAMIC:
			ret = D3D11_USAGE_DYNAMIC; break;
		case dream::DRE_BUFFER_USAGE_WRITEONLY:
			ret = D3D11_USAGE_DYNAMIC; break;
		case dream::DRE_BUFFER_USAGE_DISCARDABLE:
			ret = D3D11_USAGE_DYNAMIC; break;
		case dream::DRE_BUFFER_USAGE_STATIC_WRITE_ONLY:
			ret = D3D11_USAGE_STAGING; break;
		case dream::DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY:
			ret = D3D11_USAGE_DYNAMIC; break;
		case dream::DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE:
			ret = D3D11_USAGE_DYNAMIC; break;
		default:
			ret = D3D11_USAGE_DYNAMIC; break;
		}

		return ret;
	}

	DRE_BUFFER_USAGE D3D11RenderMapping::Get(D3D11_USAGE usage, u32 flag) throw()
	{
		DRE_BUFFER_USAGE ret = DRE_BUFFER_USAGE_DEFAULT;

		if(flag == 0)
			return ret;

		switch (usage)
		{
		case D3D11_USAGE_DEFAULT:
			ret = DRE_BUFFER_USAGE_DEFAULT; break;
		case D3D11_USAGE_IMMUTABLE:
			ret = DRE_BUFFER_USAGE_DEFAULT; break;
		case D3D11_USAGE_DYNAMIC:
			ret = DRE_BUFFER_USAGE_DYNAMIC;
			break;
		case D3D11_USAGE_STAGING:
			if (!(flag & D3D11_CPU_ACCESS_READ))
				ret = DRE_BUFFER_USAGE_STATIC_WRITE_ONLY;
			else
				ret = DRE_BUFFER_USAGE_STATIC;
			break;
		default:
			break;
		}

		return ret;
	}

	u32 D3D11RenderMapping::GetCPUAccess(DRE_BUFFER_USAGE usage) throw()
	{
		u32 ret = 0;

		switch (usage)
		{
		case dream::DRE_BUFFER_USAGE_DEFAULT:
			ret = 0; break;
		case dream::DRE_BUFFER_USAGE_STATIC:
			ret = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE; break;
		case dream::DRE_BUFFER_USAGE_DYNAMIC:
			ret = D3D11_CPU_ACCESS_WRITE; break;
		case dream::DRE_BUFFER_USAGE_WRITEONLY:
			ret = D3D11_CPU_ACCESS_WRITE; break;
		case dream::DRE_BUFFER_USAGE_DISCARDABLE:
			ret = D3D11_CPU_ACCESS_WRITE; break;
		case dream::DRE_BUFFER_USAGE_STATIC_WRITE_ONLY:
			ret = D3D11_CPU_ACCESS_WRITE; break;
		case dream::DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY:
			ret = D3D11_CPU_ACCESS_WRITE; break;
		case dream::DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE:
			ret = D3D11_CPU_ACCESS_WRITE; break;
		default:
			break;
		}

		return ret;
	}

	DXGI_FORMAT	D3D11RenderMapping::Get(DRE_INDEX_ELEMENT_TYPE type)
	{
		DXGI_FORMAT ret = DXGI_FORMAT_UNKNOWN;

		switch (type)
		{
		case dream::DRE_INDEX_ELEMENT_TYPE_U16:
			ret = DXGI_FORMAT_R16_UINT; break;
		case dream::DRE_INDEX_ELEMENT_TYPE_U32:
			ret = DXGI_FORMAT_R32_UINT; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_TEXTURE_ADDRESS_MODE D3D11RenderMapping::Get(DRE_TEXTURE_ADDRESS_MODE mode) throw()
	{
		D3D11_TEXTURE_ADDRESS_MODE ret = D3D11_TEXTURE_ADDRESS_WRAP;

		switch (mode)
		{
		case dream::DRE_TEXTURE_ADDRESS_WRAP:
			ret = D3D11_TEXTURE_ADDRESS_WRAP; break;
		case dream::DRE_TEXTURE_ADDRESS_MIRROR:
			ret = D3D11_TEXTURE_ADDRESS_MIRROR; break;
		case dream::DRE_TEXTURE_ADDRESS_CLAMP:
			ret = D3D11_TEXTURE_ADDRESS_CLAMP; break;
		case dream::DRE_TEXTURE_ADDRESS_BORDER:
			ret = D3D11_TEXTURE_ADDRESS_BORDER; break;
		case dream::DRE_TEXTURE_ADDRESS_MIRROR_ONCE:
			ret = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE; break;
		default:
			break;
		}

		return ret;
	}

	D3D11_FILTER D3D11RenderMapping::Get(DRE_FILTER_OPTION op) throw()
	{
		D3D11_FILTER ret = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;

		switch (op)
		{
		case dream::DRE_FILTER_MIN_MAG_MIP_POINT:
			ret = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT; break;
		case dream::DRE_FILTER_MIN_MAG_POINT_MIP_LINEAR:
			ret = D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR; break;
		case dream::DRE_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
			ret = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT; break;
		case dream::DRE_FILTER_MIN_POINT_MAG_MIP_LINEAR:
			ret = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR; break;
		case dream::DRE_FILTER_MIN_LINEAR_MAG_MIP_POINT:
			ret = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT; break;
		case dream::DRE_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
			ret = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR; break;
		case dream::DRE_FILTER_MIN_MAG_LINEAR_MIP_POINT:
			ret = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT; break;
		case dream::DRE_FILTER_MIN_MAG_MIP_LINEAR:
			ret = D3D11_FILTER_MIN_MAG_MIP_LINEAR; break;
		case dream::DRE_FILTER_ANISOTROPIC:
			ret = D3D11_FILTER_ANISOTROPIC; break;
		default:
			break;
		}

		return ret;
	}

}	// end namespace dream