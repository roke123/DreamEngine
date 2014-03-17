#ifndef __DREPIXELFORMAT_H__
#define __DREPIXELFORMAT_H__

#include "DreTypes.h"
#include "DreComplieConfig.h"

namespace dream
{
	/// ���ظ�ʽ��־λ
	enum DRE_PIXEL_FORMAT_FLAGS
	{
		/// ��͸���ȱ�־
		DRE_PIXEL_FORMAT_FLAG_HASALPHA		= 0x00000001,
		/// float��ʽ��־
		DRE_PIXEL_FORMAT_FLAG_FLOATTYPE		= 0x00000002,
		/// ���Ҷȱ�־
		DRE_PIXEL_FORMAT_FLAG_HASLUMINANCE	= 0x00000004,
		/// ѹ����ʽ��־
		DRE_PIXEL_FORMAT_FLAG_COMPRESSED	= 0x00000008,
	};

	/// ���ظ�ʽ
	enum DRE_PIXEL_FORMAT
	{
		/// δ֪��ʽ
		/// @note DirectX11
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_UNKNOWN				= 0,
		/// 8λ�Ҷ�ͼ
		/// @note DirectX11					��ӦDXGI_FORMAT_R8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_L_8					= DRE_PIXEL_FORMAT_UNKNOWN + 1,
		/// 16λ�Ҷ�ͼ��DirectX11�ж�ӦDXGI_FORMAT_R16_UNORM��
		/// @note DirectX11
		/// @note DirextX9
		DRE_PIXEL_FORMAT_L_16					= DRE_PIXEL_FORMAT_L_8 + 1,
		/// 8λ͸��ͨ��ͼ
		/// @note DirectX11					��ӦDXGI_FORMAT_A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_A_8					= DRE_PIXEL_FORMAT_L_16 + 1,
		/// 16λ��͸����λͼ��R5G5B5A1
		/// @note DirectX11					�޶�Ӧ��ʽ
		/// @note DirextX9				
		DRE_PIXEL_FORMAT_R5G5B5A1				= DRE_PIXEL_FORMAT_A_8 + 1,
		/// 16λ��͸���ȱ�׼λͼ��R5G5B5A1
		/// @note DirectX11					�޶�Ӧ��ʽ
		/// @note DirextX9				
		DRE_PIXEL_FORMAT_A1R5G5B5				= DRE_PIXEL_FORMAT_R5G5B5A1 + 1,
		/// 16λ����͸����λͼ��R5G6B5
		/// @note DirectX11					�޶�Ӧ��ʽ
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_R5G6B5					= DRE_PIXEL_FORMAT_A1R5G5B5 + 1,	
		/// 24λ��׼λͼ��ʽ��(for big endian == RGB, for little endian == BGR)
		/// @note DirectX11					��ӦDXGI_FORMAT_B8G8R8A8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_R8G8B8				= DRE_PIXEL_FORMAT_R5G6B5 + 1,
		/// 24λ��׼λͼ��ʽ��(for big endian == BGR, for little endian == RGB)
		/// @note DirectX11					��ӦDXGI_FORMAT_R8G8B8A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_B8G8R8				= DRE_PIXEL_FORMAT_R8G8B8 + 1,
		/// 32λ��׼λͼ��ʽ��(for little endian == BGR[A])
		/// @note DirectX11					��ӦDXGI_FORMAT_B8G8R8A8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_A8R8G8B8				= DRE_PIXEL_FORMAT_B8G8R8 + 1,
		/// 32λ��׼λͼ��ʽ��(for little endian == RGB[A])
		/// @note DirectX11					��ӦDXGI_FORMAT_B8G8R8A8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_A8B8G8R8				= DRE_PIXEL_FORMAT_A8R8G8B8 + 1,
		/// 32λ��׼λͼ��ʽ��(for big endian == BGR[A])
		/// @note DirectX11					��ӦDXGI_FORMAT_R8G8B8A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_B8G8R8A8				= DRE_PIXEL_FORMAT_A8B8G8R8 + 1,
		/// 32λ��׼λͼ��ʽ��(for big endian == RGB[A])
		/// @note DirectX11					��ӦDXGI_FORMAT_R8G8B8A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_R8G8B8A8				= DRE_PIXEL_FORMAT_B8G8R8A8 + 1,

#if		DRE_ENDIAN == DRE_ENDIAN_BIG
		/// 3 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue
		DRE_PIXEL_FORMAT_RGB = DRE_PIXEL_FORMAT_R8G8B8,
		/// 3 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red
		DRE_PIXEL_FORMAT_BGR = DRE_PIXEL_FORMAT_B8G8R8,
		/// 4 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red and one byte for alpha
		DRE_PIXEL_FORMAT_BGRA = DRE_PIXEL_FORMAT_B8G8R8A8,
		/// 4 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue, and one byte for alpha
		DRE_PIXEL_FORMAT_RGBA = DRE_PIXEL_FORMAT_R8G8B8A8,
#else
		/// 3 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue
		DRE_PIXEL_FORMAT_RGB = DRE_PIXEL_FORMAT_B8G8R8,
		/// 3 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red
		DRE_PIXEL_FORMAT_BGR = DRE_PIXEL_FORMAT_R8G8B8,
		/// 4 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red and one byte for alpha
		DRE_PIXEL_FORMAT_BGRA = DRE_PIXEL_FORMAT_A8R8G8B8,
		/// 4 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue, and one byte for alpha
		DRE_PIXEL_FORMAT_RGBA = DRE_PIXEL_FORMAT_A8B8G8R8,
#endif        
	};

//---------------------------------------------------���ظ�ʽ������---------------------------------------------//

	/** �����ظ�ʽ������
	*/
	struct PixelFormatDesc
	{
		/// ���ظ�ʽ��
		const char* formatName;
		/// ���ظ�ʽ��־λ
		u32 formatFlags;
		/// ���ظ�ʽλ��
		u8	formatWidth;
		/// ����ÿ��ɫλ��
		u8  rwidth, gwidth, bwidth, awidth;
		/// ������ɫλ��
		u8  rshift, gshift, bshift, ashift;
		/// ������ɫ�ɰ�
		u32  rmarks, gmarks, bmarks, amarks;
	};

	// ���س��ò���
	class DRE_EXPORT_CLASS PixelUtil
	{
	public:
		// ȡ�����ظ�ʽ��
		static const char* GetPixelFormatName(DRE_PIXEL_FORMAT format);

		// ȡ�����ظ�ʽλ��
		static u8 GetPixelFormatBpp(DRE_PIXEL_FORMAT format);

		// ȡ�����ظ�ʽÿ��ɫλ��
		static u8 GetPixelFormatRedWidth(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatGreenWidth(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatBlueWidth(DRE_PIXEL_FORMAT format);

		// ȡ�����ظ�ʽÿ��ɫλ��
		static u8 GetPixelFormatRedShift(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatGreenShift(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatBlueShift(DRE_PIXEL_FORMAT format);

		// ȡ�����ظ�ʽÿ��ɫ�ɰ�
		static u32 GetPixelFormatRedMark(DRE_PIXEL_FORMAT format);
		static u32 GetPixelFormatGreenMark(DRE_PIXEL_FORMAT format);
		static u32 GetPixelFormatBlueMark(DRE_PIXEL_FORMAT format);

		/** ����gammaУ��
		* @param	source		����gammaУ�������ݻ�����
		* @param	srcFormat	Դ�������ظ�ʽ
		* @param	srcSize		Դ���ݳ���
		* @param	gamma		gammaУ��ֵ
		*/
		static void ApplyGamma(u8Array& source, DRE_PIXEL_FORMAT srcFormat, u32 srcSize,
			f32 gamma);

		/** ת����������
		* @param	src			Դ���ݻ�����
		* @param	srcFormat	Դ���ظ�ʽ
		* @param	srcSize		Դ���ݳ���
		* @param	destFormat	Ŀ�����ظ�ʽ
		* @return				Ŀ�����ݻ�����
		*/
		static u8Array Convert(const u8Array src, DRE_PIXEL_FORMAT srcForamt, u32 srcSize,
			DRE_PIXEL_FORMAT destFormat);
		
		/** ת����������
		* @param	src			Դ���ݻ�����
		* @param	srcFormat	Դ���ظ�ʽ
		* @param	srcSize		Դ���ݳ���
		* @pram		dest		Ŀ�����ݻ�����
		* @param	destFormat	Ŀ�����ظ�ʽ
		*/
		static void Convert(const u8* src, DRE_PIXEL_FORMAT srcForamt, u32 srcSize,
			u8* dest, DRE_PIXEL_FORMAT destFormat);

	private:
		template<class T>
		static void Convert_Impl(const u8* src, u32 srcSize, u8* dest);

	};	// end class PixelUtil

}	// end namespace dream

#endif	// end __DREPIXELFORMAT_H__