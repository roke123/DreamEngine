#ifndef __DRERENDERWINDOW_H__
#define __DRERENDERWINDOW_H__

#include "DreRenderDeclaration.h"

#include <Windows.h>

namespace dream
{

	class DRE_EXPORT_CLASS RenderWindow
	{
	public:
		RenderWindow(u32 width, u32 height, bool isFullScreen = false,
			bool hasDepth = false, bool hasStencil = false, 
			u32 fsaa = 1, u32 fassQuality = 0) :
		mWidth(width), mHeight(height), mIsFullScreen(isFullScreen),
			mHasDepthBuffer(hasDepth), mHasStencilBuffer(hasStencil),
			mFASSCount(fsaa), mFASSQuality(fassQuality)
		{
			// 留空
		}

	private:
		RenderWindow(const Texture&);
		RenderWindow& operator = (const Texture&);
		    
	public:

		/** 虚析构函数
		*/
		virtual ~RenderWindow() {};

		/** 重置RenderWindow大小
		* @param	width			渲染目标宽度
		* @param	height			渲染目标长度
		*/
		virtual void ResizeRenderWindow(u32 width, u32 height) = 0;

		/** 根据窗口大小重置RenderWindow大小
		* @param	width			渲染目标宽度
		* @param	height			渲染目标长度
		*/
		virtual void ResizeRenderWindow() = 0;

		/** 重置RenderWindow的采样率
		* @param	fsaa			采样次数
		* @param	fassQuality		采样质量
		*/
		virtual void ResetRenderWindow(u32 width, u32 height, u32 fsaa, u32 fassQuality,
			bool hasDepth, bool hasStencil) = 0;

		/** 使RenderWindow全屏
		*/
		virtual void SetFullscreenState(bool enabled) = 0;

		/** 把渲染目标导出成静态纹理
		*/
		virtual TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) = 0;

		/** 把渲染目标导出成动态纹理
		*/
		virtual TexturePtr ExportAsDynamicTexture() = 0;

		virtual HWND GetWindowHandle() = 0;

		u32 GetWidth() { return mWidth; }
		u32 GetHeight() { return mHeight; }
		u32 GetFASSCount() { return mFASSCount; }
		u32 GetFASSQuality() { return mFASSQuality; }
		bool HasDepthBuffer() { return mHasDepthBuffer; }
		u32 GetDepthBits() { return mDepthBits; }
		bool HasStencilBuffer() { return mHasStencilBuffer; }
		bool IsFullScreen() { return mIsFullScreen; }

	protected:
		void SetWidth(u32 width) { mWidth = width; }
		void SetHeight(u32 height) { mHeight = height; }
		void SetFASSCount(u32 fsaa) { mFASSCount = mFASSCount; }
		void SetFASSQuality(u32 fassQuality) { mFASSQuality = fassQuality; }
		void SetDepthBuffer(bool enabled) { mHasDepthBuffer = enabled; }
		void SetDepthBits(u32 bits) { mDepthBits = bits; }
		void SetStencilBuffer(bool enabled) { mHasStencilBuffer = enabled; }
		void SetFullScreen(bool enabled) { mIsFullScreen = enabled; }

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
		/// 是否有Stencil缓冲
		bool mHasStencilBuffer;
		/// 是否全屏
		bool mIsFullScreen;
		/// 是否有Depth缓冲
		bool mHasDepthBuffer;
	};	// end class RenderWindow

}	// end namespace dream

#endif	// end __DRERENDERWINDOW_H__