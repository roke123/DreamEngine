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
				// ����
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
		/** ˽�й��캯������ֹ�ⲿ����
		*/
		FreeImageLoader(FREE_IMAGE_FORMAT fif);

	public:
		virtual ~FreeImageLoader() {};

		/** �����ļ�������ͼƬ
		*/
		ImagePtr Load_Impl(const char* file) override;

		/** ���ڴ�������ͼƬ
		* @param	data		���ݻ�����
		* @param	sizeInbyte	���ݻ���������
		*/
		ImagePtr Load_Impl(u8Array data, u32 sizeInByte) override;

		/** ����ͼƬ���ļ���
		* @param	image		ͼƬָ��
		* @param	file		�ļ���
		*/
		u32 Save_Impl(ImagePtr image, const char* file) override;

		/** ��װFreeImageLoader
		*/
		static void StartUp();

		/** ж��FreeImageLoader
		*/
		static void ShutDown();

	private:
		/** ��image���а�mFIF��ʽ����
		*/
		FIBITMAP* Encode(ImagePtr image);

	private:
		/// ��ͼƬ��������ͼƬ��ʽ
		FREE_IMAGE_FORMAT mFIF;
	};

}	// end namespace dream

#endif	// end __DREFREEIMAGELOADER_H__