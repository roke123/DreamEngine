#ifndef __DRED3D11RENDERDECLARATION_H__
#define __DRED3D11RENDERDECLARATION_H__

#include <d3d11.h>
#include <DxErr.h>
#include <DXGI.h>
#include <d3d11shader.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>

// ∑¿÷π”Îstlport≥ÂÕª
#undef __in_range

#define D3D11_MIP_LEVELS				10
#define D3D11_MOST_DETAILED_MIP			10

#define D3D11_RENDER_TARGET_FORMAT		DXGI_FORMAT_R8G8B8A8_UNORM

#define D3D11_DOUBLE_SWAP_BUFFER		2
#define D3D11_TRIPLE_SWAP_BUFFER		3

#define D3D11_REFRESH_RATE				60

#define D3D11_MAX_RENDER_TARGET_NUM		8
#define D3D11_MAX_RENDER_WINDOW_NUM		8

#define D3D11_MAX_SAMPLER_NUM			D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT
#define D3D11_MAX_TEXTURE_NUM			D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT 

#define D3D11_IF_FAILED_THROW(hr, source)											\
	if (FAILED(hr))																	\
	{																				\
		DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, DXGetErrorDescription(hr),		\
			source);																\
	}

#include "DreRenderDeclaration.h"

#include "DreD3D11ComPtr.h"

namespace dream
{
	
	typedef D3D11ComPtr<ID3D11Buffer>				ID3D11BufferPtr;
	typedef D3D11ComPtr<IDXGIAdapter>				IDXGIAdapterPtr;
	typedef D3D11ComPtr<IDXGIFactory>				IDXGIFactoryPtr;
	typedef D3D11ComPtr<ID3D11Device>				ID3D11DevicePtr;
	typedef D3D11ComPtr<ID3D11RasterizerState>		ID3D11RasterizerStatePtr;
	typedef D3D11ComPtr<ID3D11BlendState>			ID3D11BlendStatePtr;
	typedef D3D11ComPtr<ID3D11DepthStencilState>	ID3D11DepthStencilStatePtr;
	typedef D3D11ComPtr<ID3D11DeviceContext>		ID3D11DeviceContextPtr;
	typedef D3D11ComPtr<IDXGISwapChain>				IDXGISwapChainPtr;
	typedef D3D11ComPtr<ID3D11RenderTargetView>		ID3D11RenderTargetViewPtr;
	typedef D3D11ComPtr<ID3D11DepthStencilView>		ID3D11DepthStencilViewPtr;
	typedef D3D11ComPtr<ID3D11Texture2D>			ID3D11Texture2DPtr;
	typedef D3D11ComPtr<ID3D11ShaderResourceView>	ID3D11ShaderResourceViewPtr;
	typedef D3D11ComPtr<ID3D10Blob>					ID3D10BlobPtr;
	typedef D3D11ComPtr<ID3D11VertexShader>			ID3D11VertexShaderPtr;
	typedef D3D11ComPtr<ID3D11PixelShader>			ID3D11PixelShaderPtr;
	typedef D3D11ComPtr<ID3D11DomainShader>			ID3D11DomainShaderPtr;
	typedef D3D11ComPtr<ID3D11HullShader>			ID3D11HullShaderPtr;
	typedef D3D11ComPtr<ID3D11GeometryShader>		ID3D11GeometryShaderPtr;
	typedef D3D11ComPtr<ID3D11ShaderReflection>		ID3D11ShaderReflectionPtr;
	typedef D3D11ComPtr<ID3D11SamplerState>			ID3D11SamplerStatePtr;
	typedef D3D11ComPtr<ID3D11InputLayout>			ID3D11InputLayoutPtr;
	typedef map<string, ID3D11BufferPtr>			ID3D11BufferPtrMap;
	
	class D3D11RenderSystem;
	typedef shared_ptr<D3D11RenderSystem>			D3D11RenderSystemPtr;

	class D3D11Adapter;
	typedef shared_ptr<D3D11Adapter>				D3D11AdapterPtr;

	class D3D11Texture;
	typedef shared_ptr<D3D11Texture>				D3D11TexturePtr;
	typedef map<string, D3D11TexturePtr>			D3D11TexturePtrMap;				

	class D3D11RenderTarget;
	typedef shared_ptr<D3D11RenderTarget>			D3D11RenderTargetPtr;
	typedef list<D3D11RenderTarget>					D3D11RenderTargetList;

	class D3D11Shader;
	typedef shared_ptr<D3D11Shader>					D3D11ShaderPtr;

	class D3D11Sampler;
	typedef shared_ptr<D3D11Sampler>				D3D11SamplerPtr;
	typedef map<string, D3D11SamplerPtr>			D3D11SamplerPtrMap;

	class D3D11Material;
	typedef shared_ptr<D3D11Material>				D3D11MaterialPtr;

	class D3D11HardwareVertexBuffer;
	typedef shared_ptr<D3D11HardwareVertexBuffer>	D3D11HardwareVertexBufferPtr;

	class D3D11HardwareIndexBuffer;
	typedef shared_ptr<D3D11HardwareIndexBuffer>	D3D11HardwareIndexBufferPtr;

	class D3D11RenderWindow;
	typedef shared_ptr<D3D11RenderWindow>			D3D11RenderWindowPtr;
	typedef list<D3D11RenderWindow>					D3D11RenderWindowtList;

}	// end namespace dream

#endif	// end __DRED3D11RENDERDECLARATION_H__