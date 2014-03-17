#ifndef __DRETEXTURE_H__
#define __DRETEXTURE_H__

#include "DreRenderDeclaration.h"

#include "DreHardwareBuffer.h"

namespace dream
{

	class DRE_EXPORT_CLASS Texture : public HardwareBuffer
	{
	public:
		/** 构造函数，不能构造空纹理，只能通过Image创建，
		* @remark 如要创建渲染目标纹理可通过把Texture生成RenderTarget
		*/
		Texture(u32 sizeInByte, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) :
		HardwareBuffer(sizeInByte, usage)
		{
			// 留空
		}

	private:
		Texture(const Texture&);
		Texture& operator = (const Texture&);
		    
	public:

		/** 虚析构函数
		*/ 
		virtual ~Texture() {};

		/** 把纹理导出成独立的Image
		*/
		virtual ImagePtr ExportAsImage() = 0;

		f32 GetGammaValue() { return mGammaValue; }
		u32 GetFASS() { return mFSAA; }
		u32 GetFASSQuality() { return mFSAAQuality; }
		u32 GetWidth() { return mWidth; }
		u32 GetHeight() { return mHeight; }
		DRE_PIXEL_FORMAT GetFormat() { return mFormat; }

		/** 对数据进行Gamma校正
		*/
		static void ApplyGamma(u8Array data, f32 gammaValue);

	protected:

		/** 设置源图像生成资源后的属性
		*/
		void SetFinalAtrributes(u32 width, u32 height, DRE_PIXEL_FORMAT format)
		{
			mWidth = width;
			mHeight = height;
			mFormat = format;
		}

	private:
		/// Gamma校正值
		f32 mGammaValue;
		/// 转换源图像生成资源后的长宽
		u32 mWidth, mHeight;
		/// 转换源图像生成资源后的像素格式
		DRE_PIXEL_FORMAT mFormat;
		/// 多重取样次数，Full Sence Anti-aliasing
		u32 mFSAA;
		/// 多重采样质量
		u32 mFSAAQuality;
		/// 是否透明通道图，对DRE_FORMAT_L8有效，把灰度图转换为透明通道图
		bool mIsTransparentFigure;
	};	// end class Texture

}	// end namespace dream

#endif	// end of __DRETEXTURE_H__