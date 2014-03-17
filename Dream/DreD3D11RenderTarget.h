#ifndef __DRED3D11RENDERTARGET_H__
#define __DRED3D11RENDERTARGET_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreRenderTarget.h"

namespace dream
{

	class D3D11RenderTarget final : public RenderTarget
	{
		friend class D3D11RenderSystem;
	private:
		/// d3d11渲染设备
		ID3D11DevicePtr mD3D11Device;
		/// D3D11渲染设备内容
		ID3D11DeviceContextPtr mD3D11Context;
		/// D3D11渲染目标
		ID3D11RenderTargetViewPtr mD3D11RenderTarget;
		/// D3D11深度模板缓冲
		ID3D11DepthStencilViewPtr mD3D11DepthStencilView;

	private:
		/** 构造函数
		* @param		/		width			渲染目标宽度
		* @param		/		height			渲染目标长度
		* @param	optional	hasDepth		是否带有深度缓冲
		* @param	optional	hasStencil		是否带有模板缓冲
		* @param	optional	fsaa			多重采样次数
		* @param	optional	fassQuality		多重采样质量
		*
		* @remark	当hasDepth为true，hasStencil为false时，自创建深度缓冲，以DirectX11为例
		*			创建格式为DXGI_FORMAT_D32_FLOAT，否则为DXGI_FORMAT_D24_UNORM_S8_UINT
		*/
		D3D11RenderTarget(
			ID3D11RenderTargetViewPtr renderTarget, ID3D11DepthStencilViewPtr depthBuffer,
			ID3D11DevicePtr d3dDevice, u32 width, u32 height,
			bool hasDepth = false, bool hasStencil = false,
			u32 fsaa = 1, u32 fassQuality = 0);

	public:
		/** 虚析构函数
		*/
		~D3D11RenderTarget() override;

		/** 重置RenderTarget
		* @param		/		width			渲染目标宽度
		* @param		/		height			渲染目标长度
		* @param	optional	hasDepth		是否带有深度缓冲
		* @param	optional	hasStencil		是否带有模板缓冲
		*
		* @remark	重载RenderTarget后会使源RenderTarget失效需要重新绑定到RenderSystem
		*/
		void ResizeRenderTarget(u32 width, u32 height) override;

		/** 把渲染目标导出成静态纹理
		*/
		TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) override;

		/** 把渲染目标导出成动态纹理
		*/
		TexturePtr ExportAsDynamicTexture() override;

		ID3D11RenderTargetViewPtr GetRenderTarget() { return mD3D11RenderTarget; }

		ID3D11DepthStencilViewPtr GetDepthStencil() { return mD3D11DepthStencilView; }

	};	// end class D3D11RenderTarget

}	// end namespace dream

#endif	// end __DRED3D11RENDERTARGET_H__