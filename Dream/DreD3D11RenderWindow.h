#ifndef __DRED3D11RENDERWINDOW_H__
#define __DRED3D11RENDERWINDOW_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreRenderWindow.h"

namespace dream
{
	struct D3D11_RENDER_WINDOW_DESC
	{
		u32			width;
		u32			height;
		bool		hasDepth;
		bool		hasStencil;
		u32			fsaa;
		u32			fassQuality;
		HINSTANCE	hInstance;
	};

	class D3D11RenderWindow final : public RenderWindow
	{
		friend class D3D11RenderSystem;
	private:
		/// 交换链
		IDXGISwapChainPtr mD3D11SwapChain;		
		/// D3D11渲染设备
		ID3D11DevicePtr mD3D11Device;
		/// D3D11渲染内容
		ID3D11DeviceContextPtr mD3D11Context;
		/// 渲染目标 
		ID3D11RenderTargetViewPtr mD3D11RenderTarget;
		/// 深度缓冲
		ID3D11DepthStencilViewPtr mD3D11DepthStencil;
		/// 窗口句柄
		HWND mHWindow;

	private:
		/** 构造函数
		*/
		D3D11RenderWindow(
			IDXGISwapChainPtr swapChain, HWND hwnd, ID3D11DevicePtr d3dDevice,
			ID3D11RenderTargetViewPtr renderTarget, ID3D11DepthStencilViewPtr depthStencil,
			u32 width, u32 height, bool isFullScreen,
			bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality);

	public:
		/** 虚析构函数
		*/
		~D3D11RenderWindow();

		/** 重置RenderWindow大小
		* @param	width			渲染目标宽度
		* @param	height			渲染目标长度
		*/
		void ResizeRenderWindow(u32 width, u32 height) override;

		/** 根据窗口大小重置RenderWindow大小
		* @param	width			渲染目标宽度
		* @param	height			渲染目标长度
		*/
		void ResizeRenderWindow() override;

		/** 重置RenderWindow的采样率
		* @param	fsaa			采样次数
		* @param	fassQuality		采样质量
		*/
		void ResetRenderWindow(u32 width, u32 height, u32 fsaa, u32 fassQuality,
			bool hasDepth, bool hasStencil) override;

		/** 使RenderWindow全屏
		*/
		void SetFullscreenState(bool enabled) override;

		/** 把渲染目标导出成静态纹理
		*/
		TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) override;

		/** 把渲染目标导出成动态纹理
		*/
		TexturePtr ExportAsDynamicTexture() override;

		HWND GetWindowHandle() override;

		ID3D11RenderTargetViewPtr	GetRenderTarget() { return mD3D11RenderTarget; }

		ID3D11DepthStencilViewPtr	GetDepthStencil() { return mD3D11DepthStencil; }

		IDXGISwapChainPtr			GetSwapChain() { return mD3D11SwapChain; }

	};	// end class D3D11RenderWindow

}	// end namespace dream

#endif	// end __DRED3D11RENDERWINDOW_H__