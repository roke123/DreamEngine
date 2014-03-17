#ifndef __DRETEXTURE_H__
#define __DRETEXTURE_H__

#include "DreRenderDeclaration.h"

#include "DreHardwareBuffer.h"

namespace dream
{

	class DRE_EXPORT_CLASS Texture : public HardwareBuffer
	{
	public:
		/** ���캯�������ܹ��������ֻ��ͨ��Image������
		* @remark ��Ҫ������ȾĿ�������ͨ����Texture����RenderTarget
		*/
		Texture(u32 sizeInByte, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) :
		HardwareBuffer(sizeInByte, usage)
		{
			// ����
		}

	private:
		Texture(const Texture&);
		Texture& operator = (const Texture&);
		    
	public:

		/** ����������
		*/ 
		virtual ~Texture() {};

		/** ���������ɶ�����Image
		*/
		virtual ImagePtr ExportAsImage() = 0;

		f32 GetGammaValue() { return mGammaValue; }
		u32 GetFASS() { return mFSAA; }
		u32 GetFASSQuality() { return mFSAAQuality; }
		u32 GetWidth() { return mWidth; }
		u32 GetHeight() { return mHeight; }
		DRE_PIXEL_FORMAT GetFormat() { return mFormat; }

		/** �����ݽ���GammaУ��
		*/
		static void ApplyGamma(u8Array data, f32 gammaValue);

	protected:

		/** ����Դͼ��������Դ�������
		*/
		void SetFinalAtrributes(u32 width, u32 height, DRE_PIXEL_FORMAT format)
		{
			mWidth = width;
			mHeight = height;
			mFormat = format;
		}

	private:
		/// GammaУ��ֵ
		f32 mGammaValue;
		/// ת��Դͼ��������Դ��ĳ���
		u32 mWidth, mHeight;
		/// ת��Դͼ��������Դ������ظ�ʽ
		DRE_PIXEL_FORMAT mFormat;
		/// ����ȡ��������Full Sence Anti-aliasing
		u32 mFSAA;
		/// ���ز�������
		u32 mFSAAQuality;
		/// �Ƿ�͸��ͨ��ͼ����DRE_FORMAT_L8��Ч���ѻҶ�ͼת��Ϊ͸��ͨ��ͼ
		bool mIsTransparentFigure;
	};	// end class Texture

}	// end namespace dream

#endif	// end of __DRETEXTURE_H__