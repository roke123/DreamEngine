#ifndef __DREPIXELFORMAT_H__
#define __DREPIXELFORMAT_H__

#include "DreTypes.h"
#include "DreComplieConfig.h"

namespace dream
{
	/// 像素格式标志位
	enum DRE_PIXEL_FORMAT_FLAGS
	{
		/// 带透明度标志
		DRE_PIXEL_FORMAT_FLAG_HASALPHA		= 0x00000001,
		/// float格式标志
		DRE_PIXEL_FORMAT_FLAG_FLOATTYPE		= 0x00000002,
		/// 带灰度标志
		DRE_PIXEL_FORMAT_FLAG_HASLUMINANCE	= 0x00000004,
		/// 压缩格式标志
		DRE_PIXEL_FORMAT_FLAG_COMPRESSED	= 0x00000008,
	};

	/// 像素格式
	enum DRE_PIXEL_FORMAT
	{
		/// 未知格式
		/// @note DirectX11
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_UNKNOWN				= 0,
		/// 8位灰度图
		/// @note DirectX11					对应DXGI_FORMAT_R8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_L_8					= DRE_PIXEL_FORMAT_UNKNOWN + 1,
		/// 16位灰度图（DirectX11中对应DXGI_FORMAT_R16_UNORM）
		/// @note DirectX11
		/// @note DirextX9
		DRE_PIXEL_FORMAT_L_16					= DRE_PIXEL_FORMAT_L_8 + 1,
		/// 8位透明通道图
		/// @note DirectX11					对应DXGI_FORMAT_A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_A_8					= DRE_PIXEL_FORMAT_L_16 + 1,
		/// 16位带透明度位图，R5G5B5A1
		/// @note DirectX11					无对应格式
		/// @note DirextX9				
		DRE_PIXEL_FORMAT_R5G5B5A1				= DRE_PIXEL_FORMAT_A_8 + 1,
		/// 16位带透明度标准位图，R5G5B5A1
		/// @note DirectX11					无对应格式
		/// @note DirextX9				
		DRE_PIXEL_FORMAT_A1R5G5B5				= DRE_PIXEL_FORMAT_R5G5B5A1 + 1,
		/// 16位不带透明度位图，R5G6B5
		/// @note DirectX11					无对应格式
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_R5G6B5					= DRE_PIXEL_FORMAT_A1R5G5B5 + 1,	
		/// 24位标准位图格式，(for big endian == RGB, for little endian == BGR)
		/// @note DirectX11					对应DXGI_FORMAT_B8G8R8A8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_R8G8B8				= DRE_PIXEL_FORMAT_R5G6B5 + 1,
		/// 24位标准位图格式，(for big endian == BGR, for little endian == RGB)
		/// @note DirectX11					对应DXGI_FORMAT_R8G8B8A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_B8G8R8				= DRE_PIXEL_FORMAT_R8G8B8 + 1,
		/// 32位标准位图格式，(for little endian == BGR[A])
		/// @note DirectX11					对应DXGI_FORMAT_B8G8R8A8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_A8R8G8B8				= DRE_PIXEL_FORMAT_B8G8R8 + 1,
		/// 32位标准位图格式，(for little endian == RGB[A])
		/// @note DirectX11					对应DXGI_FORMAT_B8G8R8A8_UNORM
		/// @note DirextX9 
		DRE_PIXEL_FORMAT_A8B8G8R8				= DRE_PIXEL_FORMAT_A8R8G8B8 + 1,
		/// 32位标准位图格式，(for big endian == BGR[A])
		/// @note DirectX11					对应DXGI_FORMAT_R8G8B8A8_UNORM
		/// @note DirextX9
		DRE_PIXEL_FORMAT_B8G8R8A8				= DRE_PIXEL_FORMAT_A8B8G8R8 + 1,
		/// 32位标准位图格式，(for big endian == RGB[A])
		/// @note DirectX11					对应DXGI_FORMAT_R8G8B8A8_UNORM
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

//---------------------------------------------------像素格式的描述---------------------------------------------//

	/** 对像素格式的描述
	*/
	struct PixelFormatDesc
	{
		/// 像素格式名
		const char* formatName;
		/// 像素格式标志位
		u32 formatFlags;
		/// 像素格式位宽
		u8	formatWidth;
		/// 像素每颜色位宽
		u8  rwidth, gwidth, bwidth, awidth;
		/// 像素颜色位移
		u8  rshift, gshift, bshift, ashift;
		/// 像素颜色蒙版
		u32  rmarks, gmarks, bmarks, amarks;
	};

	// 像素常用操作
	class DRE_EXPORT_CLASS PixelUtil
	{
	public:
		// 取得像素格式名
		static const char* GetPixelFormatName(DRE_PIXEL_FORMAT format);

		// 取得像素格式位宽
		static u8 GetPixelFormatBpp(DRE_PIXEL_FORMAT format);

		// 取得像素格式每颜色位宽
		static u8 GetPixelFormatRedWidth(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatGreenWidth(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatBlueWidth(DRE_PIXEL_FORMAT format);

		// 取得像素格式每颜色位宽
		static u8 GetPixelFormatRedShift(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatGreenShift(DRE_PIXEL_FORMAT format);
		static u8 GetPixelFormatBlueShift(DRE_PIXEL_FORMAT format);

		// 取得像素格式每颜色蒙版
		static u32 GetPixelFormatRedMark(DRE_PIXEL_FORMAT format);
		static u32 GetPixelFormatGreenMark(DRE_PIXEL_FORMAT format);
		static u32 GetPixelFormatBlueMark(DRE_PIXEL_FORMAT format);

		/** 进行gamma校正
		* @param	source		进行gamma校正的数据缓冲区
		* @param	srcFormat	源数据像素格式
		* @param	srcSize		源数据长度
		* @param	gamma		gamma校正值
		*/
		static void ApplyGamma(u8Array& source, DRE_PIXEL_FORMAT srcFormat, u32 srcSize,
			f32 gamma);

		/** 转换像素数据
		* @param	src			源数据缓冲区
		* @param	srcFormat	源像素格式
		* @param	srcSize		源数据长度
		* @param	destFormat	目标像素格式
		* @return				目标数据缓冲区
		*/
		static u8Array Convert(const u8Array src, DRE_PIXEL_FORMAT srcForamt, u32 srcSize,
			DRE_PIXEL_FORMAT destFormat);
		
		/** 转换像素数据
		* @param	src			源数据缓冲区
		* @param	srcFormat	源像素格式
		* @param	srcSize		源数据长度
		* @pram		dest		目标数据缓冲区
		* @param	destFormat	目标像素格式
		*/
		static void Convert(const u8* src, DRE_PIXEL_FORMAT srcForamt, u32 srcSize,
			u8* dest, DRE_PIXEL_FORMAT destFormat);

	private:
		template<class T>
		static void Convert_Impl(const u8* src, u32 srcSize, u8* dest);

	};	// end class PixelUtil

}	// end namespace dream

#endif	// end __DREPIXELFORMAT_H__