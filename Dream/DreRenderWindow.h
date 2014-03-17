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
			// ����
		}

	private:
		RenderWindow(const Texture&);
		RenderWindow& operator = (const Texture&);
		    
	public:

		/** ����������
		*/
		virtual ~RenderWindow() {};

		/** ����RenderWindow��С
		* @param	width			��ȾĿ����
		* @param	height			��ȾĿ�곤��
		*/
		virtual void ResizeRenderWindow(u32 width, u32 height) = 0;

		/** ���ݴ��ڴ�С����RenderWindow��С
		* @param	width			��ȾĿ����
		* @param	height			��ȾĿ�곤��
		*/
		virtual void ResizeRenderWindow() = 0;

		/** ����RenderWindow�Ĳ�����
		* @param	fsaa			��������
		* @param	fassQuality		��������
		*/
		virtual void ResetRenderWindow(u32 width, u32 height, u32 fsaa, u32 fassQuality,
			bool hasDepth, bool hasStencil) = 0;

		/** ʹRenderWindowȫ��
		*/
		virtual void SetFullscreenState(bool enabled) = 0;

		/** ����ȾĿ�굼���ɾ�̬����
		*/
		virtual TexturePtr ExportAsStaticTexture(DRE_BUFFER_USAGE usage) = 0;

		/** ����ȾĿ�굼���ɶ�̬����
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
		/// �Ƿ���Stencil����
		bool mHasStencilBuffer;
		/// �Ƿ�ȫ��
		bool mIsFullScreen;
		/// �Ƿ���Depth����
		bool mHasDepthBuffer;
	};	// end class RenderWindow

}	// end namespace dream

#endif	// end __DRERENDERWINDOW_H__