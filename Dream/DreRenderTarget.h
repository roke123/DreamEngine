#ifndef __DRERENDERTARGET_H__
#define __DRERENDERTARGET_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS RenderTarget
	{
	public:
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
		RenderTarget(u32 width, u32 height, bool hasDepth = false, bool hasStencil = false,
			u32 depthBits = 0, u32 fsaa = 1, u32 fassQuality = 0) :
		mWidth(width), mHeight(height), mHasDepthBuffer(hasDepth), mHasStencilBuffer(hasStencil),
			mFASSCount(fsaa), mFASSQuality(fassQuality), mDepthBits(depthBits)
		{
			// ����
		}

	private:
		RenderTarget(const RenderTarget&);
		RenderTarget& operator = (const RenderTarget&);
		    
	public:

		/** ����������
		*/
		virtual ~RenderTarget() {};

		/** ����RenderTarget
		* @param		/		width			��ȾĿ����
		* @param		/		height			��ȾĿ�곤��
		* @param	optional	hasDepth		�Ƿ������Ȼ���
		* @param	optional	hasStencil		�Ƿ����ģ�建��
		*
		* @remark	����RenderTarget���ʹԴRenderTargetʧЧ��Ҫ���°󶨵�RenderSystem
		*/
		virtual void ResizeRenderTarget(u32 width, u32 height) = 0;

		/** ����ȾĿ�굼���ɾ�̬����
		*/
		virtual TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) = 0;

		/** ����ȾĿ�굼���ɶ�̬����
		*/
		virtual TexturePtr ExportAsDynamicTexture() = 0;

		u32 GetWidth() { return mWidth; }
		u32 GetHeight() { return mHeight; }
		u32 GetFASSCount() { return mFASSCount; }
		u32 GetFASSQuality() { return mFASSQuality; }
		bool HasDepthBuffer() { return mHasDepthBuffer; }
		u32 GetDepthBits() { return mDepthBits; }
		bool HasStencilBuffer() { return mHasStencilBuffer; }

	protected:
		void SetWidth(u32 width) { mWidth = width; }
		void SetHeight(u32 height) { mHeight = height; }
		void SetFASSCount(u32 fsaa) { mFASSCount = mFASSCount; }
		void SetFASSQuality(u32 fassQuality) { mFASSQuality = fassQuality; }
		void SetDepthBuffer(bool enabled) { mHasDepthBuffer = enabled; }
		void SetDepthBits(u32 bits) { mDepthBits = bits; }
		void SetStencilBuffer(bool enabled) { mHasStencilBuffer = enabled; }

	private:
		/// ��ȾĿ����
		u32 mWidth;
		/// ��ȾĿ�곤��
		u32 mHeight;
		/// ��ȾĿ����ز�������
		u32 mFASSCount;
		/// ��ȾĿ����ز�������
		u32 mFASSQuality;
		/// depth�������ʹ��λ��
		u32 mDepthBits;
		/// �Ƿ���Depth����
		bool mHasDepthBuffer;
		/// �Ƿ���Stencil����
		bool mHasStencilBuffer;

	};	// end class RenderTarget

}	// end namespace dream

#endif	// end __DRERENDERTARGET_H__