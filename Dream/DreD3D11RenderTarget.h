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
		/// d3d11��Ⱦ�豸
		ID3D11DevicePtr mD3D11Device;
		/// D3D11��Ⱦ�豸����
		ID3D11DeviceContextPtr mD3D11Context;
		/// D3D11��ȾĿ��
		ID3D11RenderTargetViewPtr mD3D11RenderTarget;
		/// D3D11���ģ�建��
		ID3D11DepthStencilViewPtr mD3D11DepthStencilView;

	private:
		/** ���캯��
		* @param		/		width			��ȾĿ����
		* @param		/		height			��ȾĿ�곤��
		* @param	optional	hasDepth		�Ƿ������Ȼ���
		* @param	optional	hasStencil		�Ƿ����ģ�建��
		* @param	optional	fsaa			���ز�������
		* @param	optional	fassQuality		���ز�������
		*
		* @remark	��hasDepthΪtrue��hasStencilΪfalseʱ���Դ�����Ȼ��壬��DirectX11Ϊ��
		*			������ʽΪDXGI_FORMAT_D32_FLOAT������ΪDXGI_FORMAT_D24_UNORM_S8_UINT
		*/
		D3D11RenderTarget(
			ID3D11RenderTargetViewPtr renderTarget, ID3D11DepthStencilViewPtr depthBuffer,
			ID3D11DevicePtr d3dDevice, u32 width, u32 height,
			bool hasDepth = false, bool hasStencil = false,
			u32 fsaa = 1, u32 fassQuality = 0);

	public:
		/** ����������
		*/
		~D3D11RenderTarget() override;

		/** ����RenderTarget
		* @param		/		width			��ȾĿ����
		* @param		/		height			��ȾĿ�곤��
		* @param	optional	hasDepth		�Ƿ������Ȼ���
		* @param	optional	hasStencil		�Ƿ����ģ�建��
		*
		* @remark	����RenderTarget���ʹԴRenderTargetʧЧ��Ҫ���°󶨵�RenderSystem
		*/
		void ResizeRenderTarget(u32 width, u32 height) override;

		/** ����ȾĿ�굼���ɾ�̬����
		*/
		TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) override;

		/** ����ȾĿ�굼���ɶ�̬����
		*/
		TexturePtr ExportAsDynamicTexture() override;

		ID3D11RenderTargetViewPtr GetRenderTarget() { return mD3D11RenderTarget; }

		ID3D11DepthStencilViewPtr GetDepthStencil() { return mD3D11DepthStencilView; }

	};	// end class D3D11RenderTarget

}	// end namespace dream

#endif	// end __DRED3D11RENDERTARGET_H__