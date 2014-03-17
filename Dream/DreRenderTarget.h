#ifndef __DRERENDERTARGET_H__
#define __DRERENDERTARGET_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS RenderTarget
	{
	public:
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
		RenderTarget(u32 width, u32 height, bool hasDepth = false, bool hasStencil = false,
			u32 depthBits = 0, u32 fsaa = 1, u32 fassQuality = 0) :
		mWidth(width), mHeight(height), mHasDepthBuffer(hasDepth), mHasStencilBuffer(hasStencil),
			mFASSCount(fsaa), mFASSQuality(fassQuality), mDepthBits(depthBits)
		{
			// 留空
		}

	private:
		RenderTarget(const RenderTarget&);
		RenderTarget& operator = (const RenderTarget&);
		    
	public:

		/** 虚析构函数
		*/
		virtual ~RenderTarget() {};

		/** 重置RenderTarget
		* @param		/		width			渲染目标宽度
		* @param		/		height			渲染目标长度
		* @param	optional	hasDepth		是否带有深度缓冲
		* @param	optional	hasStencil		是否带有模板缓冲
		*
		* @remark	重载RenderTarget后会使源RenderTarget失效需要重新绑定到RenderSystem
		*/
		virtual void ResizeRenderTarget(u32 width, u32 height) = 0;

		/** 把渲染目标导出成静态纹理
		*/
		virtual TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) = 0;

		/** 把渲染目标导出成动态纹理
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
		/// 渲染目标宽度
		u32 mWidth;
		/// 渲染目标长度
		u32 mHeight;
		/// 渲染目标多重采样次数
		u32 mFASSCount;
		/// 渲染目标多重采样质量
		u32 mFASSQuality;
		/// depth缓冲深度使用位数
		u32 mDepthBits;
		/// 是否有Depth缓冲
		bool mHasDepthBuffer;
		/// 是否有Stencil缓冲
		bool mHasStencilBuffer;

	};	// end class RenderTarget

}	// end namespace dream

#endif	// end __DRERENDERTARGET_H__