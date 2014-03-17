#ifndef __DREIMAGE_H__
#define __DREIMAGE_H__

#include "DreIOSystemDeclaration.h"

#include "DrePixelFormat.h"

namespace dream
{

	class DRE_EXPORT_CLASS Image
	{
	public:
		/** ���캯��
		*/
		Image(u32 width, u32 height, DRE_PIXEL_FORMAT format, bool isCopy = false);

		/** ����������
		* @remark	��ͼƬ���ݱ����Ƶ��ڹ��캯���еĶ�̬����
		*			���ڴ�ʱ��ͨ��delete�ͷ��ڴ�
		*/
		virtual ~Image() {}

		/** ��ȡͼƬ���
		*/
		u32 GetWidth() const { return mWidth; }

		/** ��ȡͼƬ�߶�
		*/
		u32 GetHeight() const { return mHeight; }

		/** ��ȡͼƬ�ڲ�����
		*/
		virtual const u8* GetDataPtr() const = 0;

		virtual ImagePtr Copy() const = 0;

		/** ��ȡ��������
		*/
		u32 GetPixelNums() const { return mWidth * mHeight; }

		/** ��ȡͼƬ��С
		*/
		u32 GetSize() const { return mWidth * mHeight * PixelUtil::GetPixelFormatBpp(mFormat); }

		/** ��ȡͼƬ���ظ�ʽ
		*/
		DRE_PIXEL_FORMAT GetPixelFormat() const { return mFormat; }

	protected:	
		/// ͼƬ��ȣ�������Ϊ��λ
		u32 mWidth;
		/// ͼƬ�߶ȣ�������Ϊ��λ
		u32 mHeight;
		/// ���ظ�ʽ
		DRE_PIXEL_FORMAT mFormat;
		/// �Ƿ��Ѱ����ݸ��Ƶ����ڲ�
		bool mIsCopy;
	};	// end class Image

}	// end namespace dream

#endif	// end __DREIMAGE_H__