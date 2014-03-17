#ifndef __DREIMAGE_H__
#define __DREIMAGE_H__

#include "DreIOSystemDeclaration.h"

#include "DrePixelFormat.h"

namespace dream
{

	class DRE_EXPORT_CLASS Image
	{
	public:
		/** 构造函数
		*/
		Image(u32 width, u32 height, DRE_PIXEL_FORMAT format, bool isCopy = false);

		/** 虚析构函数
		* @remark	当图片数据被复制到在构造函数中的动态分配
		*			的内存时就通过delete释放内存
		*/
		virtual ~Image() {}

		/** 获取图片宽度
		*/
		u32 GetWidth() const { return mWidth; }

		/** 获取图片高度
		*/
		u32 GetHeight() const { return mHeight; }

		/** 获取图片内部数据
		*/
		virtual const u8* GetDataPtr() const = 0;

		virtual ImagePtr Copy() const = 0;

		/** 获取像素数量
		*/
		u32 GetPixelNums() const { return mWidth * mHeight; }

		/** 获取图片大小
		*/
		u32 GetSize() const { return mWidth * mHeight * PixelUtil::GetPixelFormatBpp(mFormat); }

		/** 获取图片像素格式
		*/
		DRE_PIXEL_FORMAT GetPixelFormat() const { return mFormat; }

	protected:	
		/// 图片宽度，以像素为单位
		u32 mWidth;
		/// 图片高度，以像素为单位
		u32 mHeight;
		/// 像素格式
		DRE_PIXEL_FORMAT mFormat;
		/// 是否已把数据复制到类内部
		bool mIsCopy;
	};	// end class Image

}	// end namespace dream

#endif	// end __DREIMAGE_H__