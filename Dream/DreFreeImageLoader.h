#ifndef __DREFREEIMAGELOADER_H__
#define __DREFREEIMAGELOADER_H__

#include "DreIOSystemDeclaration.h"

#include "DreImage.h"
#include "DreImageLoader.h"
#include "DreNormalImage.h"

#include <FreeImage.h>

namespace dream
{

	class FreeImageLoader : public ImageLoader
	{
	private:
		class FreeImage : public Image
		{
		public:
			FreeImage(FIBITMAP* fiBitmap, u32 mWidth, u32 mHeight, DRE_PIXEL_FORMAT format) :
			//-------------------------------------------------------------------------------
			Image(mWidth, mHeight, format),
				mFiBitmap(fiBitmap)
			{
				// 留空
			}

			~FreeImage()
			{
				FreeImage_Unload(mFiBitmap);
			}

			const u8* GetDataPtr() const
			{
				return static_cast<u8*>(mFiBitmap->data);
			}

			ImagePtr Copy() const
			{
				u8Array data(this->GetSize());
				memcpy(&data[0], mFiBitmap->data, this->GetSize());

				return ImagePtr(
					new NormalImage(
						data, mWidth, mHeight, mFormat, false
					)
				);
			}

		private:
			FIBITMAP* mFiBitmap;
		};

	private:
		/** 私有构造函数，防止外部构造
		*/
		FreeImageLoader(FREE_IMAGE_FORMAT fif);

	public:
		virtual ~FreeImageLoader() {};

		/** 根据文件名载入图片
		*/
		ImagePtr Load_Impl(const char* file) override;

		/** 从内存中载入图片
		* @param	data		数据缓冲区
		* @param	sizeInbyte	数据缓冲区长度
		*/
		ImagePtr Load_Impl(u8Array data, u32 sizeInByte) override;

		/** 保存图片到文件中
		* @param	image		图片指针
		* @param	file		文件名
		*/
		u32 Save_Impl(ImagePtr image, const char* file) override;

		/** 安装FreeImageLoader
		*/
		static void StartUp();

		/** 卸载FreeImageLoader
		*/
		static void ShutDown();

	private:
		/** 对image进行按mFIF格式编码
		*/
		FIBITMAP* Encode(ImagePtr image);

	private:
		/// 与图片加载器的图片格式
		FREE_IMAGE_FORMAT mFIF;
	};

}	// end namespace dream

#endif	// end __DREFREEIMAGELOADER_H__