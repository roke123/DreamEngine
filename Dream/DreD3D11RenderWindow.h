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
		/// ������
		IDXGISwapChainPtr mD3D11SwapChain;		
		/// D3D11��Ⱦ�豸
		ID3D11DevicePtr mD3D11Device;
		/// D3D11��Ⱦ����
		ID3D11DeviceContextPtr mD3D11Context;
		/// ��ȾĿ�� 
		ID3D11RenderTargetViewPtr mD3D11RenderTarget;
		/// ��Ȼ���
		ID3D11DepthStencilViewPtr mD3D11DepthStencil;
		/// ���ھ��
		HWND mHWindow;

	private:
		/** ���캯��
		*/
		D3D11RenderWindow(
			IDXGISwapChainPtr swapChain, HWND hwnd, ID3D11DevicePtr d3dDevice,
			ID3D11RenderTargetViewPtr renderTarget, ID3D11DepthStencilViewPtr depthStencil,
			u32 width, u32 height, bool isFullScreen,
			bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality);

	public:
		/** ����������
		*/
		~D3D11RenderWindow();

		/** ����RenderWindow��С
		* @param	width			��ȾĿ����
		* @param	height			��ȾĿ�곤��
		*/
		void ResizeRenderWindow(u32 width, u32 height) override;

		/** ���ݴ��ڴ�С����RenderWindow��С
		* @param	width			��ȾĿ����
		* @param	height			��ȾĿ�곤��
		*/
		void ResizeRenderWindow() override;

		/** ����RenderWindow�Ĳ�����
		* @param	fsaa			��������
		* @param	fassQuality		��������
		*/
		void ResetRenderWindow(u32 width, u32 height, u32 fsaa, u32 fassQuality,
			bool hasDepth, bool hasStencil) override;

		/** ʹRenderWindowȫ��
		*/
		void SetFullscreenState(bool enabled) override;

		/** ����ȾĿ�굼���ɾ�̬����
		*/
		TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) override;

		/** ����ȾĿ�굼���ɶ�̬����
		*/
		TexturePtr ExportAsDynamicTexture() override;

		HWND GetWindowHandle() override;

		ID3D11RenderTargetViewPtr	GetRenderTarget() { return mD3D11RenderTarget; }

		ID3D11DepthStencilViewPtr	GetDepthStencil() { return mD3D11DepthStencil; }

		IDXGISwapChainPtr			GetSwapChain() { return mD3D11SwapChain; }

	};	// end class D3D11RenderWindow

}	// end namespace dream

#endif	// end __DRED3D11RENDERWINDOW_H__