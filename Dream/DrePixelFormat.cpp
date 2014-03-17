#include "DrePixelFormat.h"
#include "DrePixelConvert.h"

#include "DreMath.h"

namespace dream
{
	
	const PixelFormatDesc pixelFormatDescSet[] =
	{
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_UNKNOWN",
			0,
			0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_L_8",
			DRE_PIXEL_FORMAT_FLAG_HASLUMINANCE,
			8,
			8, 0, 0, 0,
			0, 0, 0, 0,
			0xff, 0x00, 0x00, 0x00
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_L_16",
			DRE_PIXEL_FORMAT_FLAG_HASLUMINANCE,
			16,
			16, 0, 0, 0,
			0, 0, 0, 0,
			0xffff, 0x0000, 0x0000, 0x0000,
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_A_8",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			8,
			0, 0, 0, 8,
			0, 0, 0, 0,
			0x00, 0x00, 0x00, 0xff, 
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_R5G5B5A1",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			16,
			5, 5, 5, 1,
			11, 6, 1, 0,
			0xf800, 0x07c0, 0x003e, 0x0001
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_A1R5G5B5",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			16,
			5, 5, 5, 1,
			10, 5, 0, 15,
			0x7c00, 0x03e0, 0x001f, 0x8000
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_R5G6B5",
			0,
			16,
			5, 6, 5, 0,
			11, 5, 0, 0,
			0xf800, 0x07e0, 0x001f, 0x0000
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_R8G8B8",
			0,
			24,
			8, 8, 8, 0,
			16, 8, 0, 0,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_B8G8R8",
			0,
			24,
			8, 8, 8, 0,
			0, 8, 16, 0,
			0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_A8R8G8B8",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			32,
			8, 8, 8, 8,
			16, 8, 0, 24,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_A8B8G8R8",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			32,
			8, 8, 8, 8,
			0, 8, 16, 24,
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_B8G8R8A8",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			32,
			8, 8, 8, 8,
			8, 16, 24, 0,
			0x0000ff00, 0x00ff0000, 0xff000000, 0x000000ff
		},
		//------------------------------------
		{
			"DRE_PIXEL_FORMAT_R8G8B8A8",
			DRE_PIXEL_FORMAT_FLAG_HASALPHA,
			32,
			8, 8, 8, 8,
			24, 16, 8, 0,
			0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff
		},
	};

	const char* PixelUtil::GetPixelFormatName(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].formatName;
	}

	// 取得像素格式位宽
	u8 PixelUtil::GetPixelFormatBpp(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].formatWidth;
	}

	// 取得像素格式每颜色位宽
	u8 PixelUtil::GetPixelFormatRedWidth(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].rwidth;
	}
	u8 PixelUtil::GetPixelFormatGreenWidth(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].gwidth;
	}
	u8 PixelUtil::GetPixelFormatBlueWidth(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].bwidth;
	}

	// 取得像素格式每颜色位移
	u8 PixelUtil::GetPixelFormatRedShift(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].rshift;
	}
	u8 PixelUtil::GetPixelFormatGreenShift(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].gshift;
	}
	u8 PixelUtil::GetPixelFormatBlueShift(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].bshift;
	}

	// 取得像素格式每颜色蒙版
	u32 PixelUtil::GetPixelFormatRedMark(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].rmarks;
	}
	u32 PixelUtil::GetPixelFormatGreenMark(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].gmarks;
	}
	u32 PixelUtil::GetPixelFormatBlueMark(DRE_PIXEL_FORMAT format)
	{
		return pixelFormatDescSet[format].bmarks;
	}

	void PixelUtil::ApplyGamma(u8Array& source, DRE_PIXEL_FORMAT srcFormat, u32 srcSize,
		f32 gamma)
	{
		if(Equal(gamma, 1.0f))
			return;

		// stride = bpp / 8，每像素的字节数
		u32 stride = PixelUtil::GetPixelFormatBpp(srcFormat) >> 3;
		u32 i = 0;

		const f32 rangeMult = 255.0f;
		const f32 rangeMultInv = 1.0f / rangeMult;
		const f32 gammaValue = 1.0f / gamma;

		switch (srcFormat)
		{
		case dream::DRE_PIXEL_FORMAT_UNKNOWN:
		case dream::DRE_PIXEL_FORMAT_L_8:
		case dream::DRE_PIXEL_FORMAT_L_16:
		case dream::DRE_PIXEL_FORMAT_A_8:
		case dream::DRE_PIXEL_FORMAT_R5G5B5A1:
		case dream::DRE_PIXEL_FORMAT_A1R5G5B5:
		case dream::DRE_PIXEL_FORMAT_R5G6B5:
			break;

		case dream::DRE_PIXEL_FORMAT_R8G8B8:
		case dream::DRE_PIXEL_FORMAT_B8G8R8:
		case dream::DRE_PIXEL_FORMAT_B8G8R8A8:
		case dream::DRE_PIXEL_FORMAT_R8G8B8A8:
			{
				u8* src = &source[0];
				for(i = 0; i < srcSize;)
				{
					f32 r = rangeMultInv * src[0];
					f32 g = rangeMultInv * src[1];
					f32 b = rangeMultInv * src[2];

					Pow(r, gammaValue);
					Pow(g, gammaValue);
					Pow(b, gammaValue);

					src[0] = (u8)(r * rangeMult);
					src[1] = (u8)(g * rangeMult);
					src[2] = (u8)(b * rangeMult);

					// 跳至下一像素
					src += stride;
				}
			}
			break;

		case dream::DRE_PIXEL_FORMAT_A8R8G8B8:
		case dream::DRE_PIXEL_FORMAT_A8B8G8R8:
			{
				u8* src = &source[0];
				for( i = 0; i * stride < srcSize; ++ i)
				{
					f32 r = rangeMultInv * src[1];
					f32 g = rangeMultInv * src[2];
					f32 b = rangeMultInv * src[3];

					Pow(r, gammaValue);
					Pow(g, gammaValue);
					Pow(b, gammaValue);

					src[1] = (u8)(r * rangeMult);
					src[2] = (u8)(g * rangeMult);
					src[3] = (u8)(b * rangeMult);

					// 跳至下一像素
					src += stride;
				}
			}
			break;
	
		default:
			break;
		}
	}

	template<class T>
	void PixelUtil::Convert_Impl(const u8* src, u32 numPixel, u8* dest)
	{
		T::DestType* destStream = (T::DestType*)dest;
		T::SrcType* srcStream = (T::SrcType*)src;

		for(u32 i = 0; i < numPixel; ++ i)
		{
			destStream[i] = T::Do(srcStream[i]);
		}
	}

#	define CasePixelConvert1(convert) case convert::ID: Convert_Impl<convert>(&src[0], numPixel, &dest[0]); break;

	// 转换像素数据
	u8Array PixelUtil::Convert(const u8Array src, DRE_PIXEL_FORMAT srcForamt, u32 numPixel,
		DRE_PIXEL_FORMAT destFormat)
	{
		u8Array dest(numPixel * GetPixelFormatBpp(destFormat));

		// 格式相同就直接复制
		if(destFormat == srcForamt)
		{
			memcpy(&dest[0], &src[0], numPixel * GetPixelFormatBpp(destFormat));
		}

		switch (GetPixelConvertID(srcForamt, destFormat))
		{
			CasePixelConvert1(L8ToL16);
			CasePixelConvert1(L8ToA8);
			CasePixelConvert1(L8ToR5G5B5A1);
			CasePixelConvert1(L8ToA1R5G5B5);
			CasePixelConvert1(L8ToR5G6B5);
			CasePixelConvert1(L8ToR8G8B8);
			CasePixelConvert1(L8ToB8G8R8);
			CasePixelConvert1(L8ToA8R8G8B8);
			CasePixelConvert1(L8ToA8B8G8R8);
			CasePixelConvert1(L8ToB8G8R8A8);
			CasePixelConvert1(L8ToR8G8B8A8);

			CasePixelConvert1(L16ToL8);
			CasePixelConvert1(L16ToA8);
			CasePixelConvert1(L16ToR5G5B5A1);
			CasePixelConvert1(L16ToA1R5G5B5);
			CasePixelConvert1(L16ToR5G6B5);
			CasePixelConvert1(L16ToR8G8B8);
			CasePixelConvert1(L16ToB8G8R8);
			CasePixelConvert1(L16ToA8R8G8B8);
			CasePixelConvert1(L16ToA8B8G8R8);
			CasePixelConvert1(L16ToB8G8R8A8);
			CasePixelConvert1(L16ToR8G8B8A8);

			CasePixelConvert1(A8ToL8);
			CasePixelConvert1(A8ToL16);
			CasePixelConvert1(A8ToR5G5B5A1);
			CasePixelConvert1(A8ToA1R5G5B5);
			CasePixelConvert1(A8ToA8R8G8B8);
			CasePixelConvert1(A8ToA8B8G8R8);
			CasePixelConvert1(A8ToB8G8R8A8);
			CasePixelConvert1(A8ToR8G8B8A8);

			CasePixelConvert1(R5G5B5A1ToL8);
			CasePixelConvert1(R5G5B5A1ToL16);
			CasePixelConvert1(R5G5B5A1ToA8);	
			CasePixelConvert1(R5G5B5A1ToA1R5G5B5);
			CasePixelConvert1(R5G5B5A1ToA8R8G8B8);
			CasePixelConvert1(R5G5B5A1ToA8B8G8R8);
			CasePixelConvert1(R5G5B5A1ToB8G8R8A8);
			CasePixelConvert1(R5G5B5A1ToR8G8B8A8);

			CasePixelConvert1(A1R5G5B5ToL8);
			CasePixelConvert1(A1R5G5B5ToL16);
			CasePixelConvert1(A1R5G5B5ToA8);
			CasePixelConvert1(A1R5G5B5ToR5G5B5A1);
			CasePixelConvert1(A1R5G5B5ToA8R8G8B8);
			CasePixelConvert1(A1R5G5B5ToA8B8G8R8);
			CasePixelConvert1(A1R5G5B5ToB8G8R8A8);
			CasePixelConvert1(A1R5G5B5ToR8G8B8A8);

			CasePixelConvert1(R5G6B5ToL8);
			CasePixelConvert1(R5G6B5ToL16);
			CasePixelConvert1(R5G6B5ToR8G8B8);
			CasePixelConvert1(R5G6B5ToB8G8R8);

			CasePixelConvert1(R8G8B8ToL8);
			CasePixelConvert1(R8G8B8ToL16);
			CasePixelConvert1(R8G8B8ToR5G6B5);
			CasePixelConvert1(R8G8B8ToB8G8R8);
			CasePixelConvert1(R8G8B8ToA8R8G8B8);
			CasePixelConvert1(R8G8B8ToA8B8G8R8);
			CasePixelConvert1(R8G8B8ToB8G8R8A8);
			CasePixelConvert1(R8G8B8ToR8G8B8A8);

			CasePixelConvert1(B8G8R8ToL8);
			CasePixelConvert1(B8G8R8ToL16);
			CasePixelConvert1(B8G8R8ToR5G6B5);
			CasePixelConvert1(B8G8R8ToR8G8B8);
			CasePixelConvert1(B8G8R8ToA8R8G8B8);
			CasePixelConvert1(B8G8R8ToA8B8G8R8);
			CasePixelConvert1(B8G8R8ToR8G8B8A8);
			CasePixelConvert1(B8G8R8ToB8G8R8A8)

			CasePixelConvert1(A8R8G8B8ToL8);
			CasePixelConvert1(A8R8G8B8ToL16);
			CasePixelConvert1(A8R8G8B8ToA8);
			CasePixelConvert1(A8R8G8B8ToR5G5B5A1);
			CasePixelConvert1(A8R8G8B8ToA1R5G5B5);			
			CasePixelConvert1(A8R8G8B8ToA8B8G8R8);
			CasePixelConvert1(A8R8G8B8ToB8G8R8A8);
			CasePixelConvert1(A8R8G8B8ToR8G8B8A8);

			CasePixelConvert1(A8B8G8R8ToL8);
			CasePixelConvert1(A8B8G8R8ToL16);
			CasePixelConvert1(A8B8G8R8ToA8);
			CasePixelConvert1(A8B8G8R8ToR5G5B5A1);
			CasePixelConvert1(A8B8G8R8ToA1R5G5B5);
			CasePixelConvert1(A8B8G8R8ToA8R8G8B8);
			CasePixelConvert1(A8B8G8R8ToB8G8R8A8);
			CasePixelConvert1(A8B8G8R8ToR8G8B8A8);

			CasePixelConvert1(B8G8R8A8ToL8);
			CasePixelConvert1(B8G8R8A8ToL16);
			CasePixelConvert1(B8G8R8A8ToA8);
			CasePixelConvert1(B8G8R8A8ToR5G5B5A1);
			CasePixelConvert1(B8G8R8A8ToA1R5G5B5);
			CasePixelConvert1(B8G8R8A8ToA8R8G8B8);
			CasePixelConvert1(B8G8R8A8ToA8B8G8R8);
			CasePixelConvert1(B8G8R8A8ToR8G8B8A8);

			CasePixelConvert1(R8G8B8A8ToL8);
			CasePixelConvert1(R8G8B8A8ToL16);
			CasePixelConvert1(R8G8B8A8ToA8);
			CasePixelConvert1(R8G8B8A8ToR5G5B5A1);
			CasePixelConvert1(R8G8B8A8ToA1R5G5B5);
			CasePixelConvert1(R8G8B8A8ToA8R8G8B8);
			CasePixelConvert1(R8G8B8A8ToA8B8G8R8);
			CasePixelConvert1(R8G8B8A8ToB8G8R8A8);

		default:
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND,
				string("不能进行从")
				.append(GetPixelFormatName(srcForamt))
				.append("到")
				.append(GetPixelFormatName(destFormat))
				.append("的转换"),
				"PixelUtil::Convert");
			break;
		}

		return dest;
	}

#	define CasePixelConvert2(convert) case convert::ID: Convert_Impl<convert>(src, numPixel, dest); break;

	/** 转换像素数据
	* @param	src			源数据缓冲区
	* @param	srcFormat	源像素格式
	* @param	srcSize		源数据长度
	* @pram		dest		目标数据缓冲区
	* @param	destFormat	目标像素格式
	*/
	void PixelUtil::Convert(const u8* src, DRE_PIXEL_FORMAT srcForamt, u32 numPixel,
		u8* dest, DRE_PIXEL_FORMAT destFormat)
	{
		// 格式相同就直接复制
		if(destFormat == srcForamt)
		{
			memcpy(&dest[0], &src[0], numPixel * GetPixelFormatBpp(destFormat) / 8);
			return;
		}

		switch (GetPixelConvertID(srcForamt, destFormat))
		{
			CasePixelConvert2(L8ToL16);
			CasePixelConvert2(L8ToA8);
			CasePixelConvert2(L8ToR5G5B5A1);
			CasePixelConvert2(L8ToA1R5G5B5);
			CasePixelConvert2(L8ToR5G6B5);
			CasePixelConvert2(L8ToR8G8B8);
			CasePixelConvert2(L8ToB8G8R8);
			CasePixelConvert2(L8ToA8R8G8B8);
			CasePixelConvert2(L8ToA8B8G8R8);
			CasePixelConvert2(L8ToB8G8R8A8);
			CasePixelConvert2(L8ToR8G8B8A8);

			CasePixelConvert2(L16ToL8);
			CasePixelConvert2(L16ToA8);
			CasePixelConvert2(L16ToR5G5B5A1);
			CasePixelConvert2(L16ToA1R5G5B5);
			CasePixelConvert2(L16ToR5G6B5);
			CasePixelConvert2(L16ToR8G8B8);
			CasePixelConvert2(L16ToB8G8R8);
			CasePixelConvert2(L16ToA8R8G8B8);
			CasePixelConvert2(L16ToA8B8G8R8);
			CasePixelConvert2(L16ToB8G8R8A8);
			CasePixelConvert2(L16ToR8G8B8A8);

			CasePixelConvert2(A8ToL8);
			CasePixelConvert2(A8ToL16);
			CasePixelConvert2(A8ToR5G5B5A1);
			CasePixelConvert2(A8ToA1R5G5B5);
			CasePixelConvert2(A8ToA8R8G8B8);
			CasePixelConvert2(A8ToA8B8G8R8);
			CasePixelConvert2(A8ToB8G8R8A8);
			CasePixelConvert2(A8ToR8G8B8A8);

			CasePixelConvert2(R5G5B5A1ToL8);
			CasePixelConvert2(R5G5B5A1ToL16);
			CasePixelConvert2(R5G5B5A1ToA8);	
			CasePixelConvert2(R5G5B5A1ToA1R5G5B5);
			CasePixelConvert2(R5G5B5A1ToA8R8G8B8);
			CasePixelConvert2(R5G5B5A1ToA8B8G8R8);
			CasePixelConvert2(R5G5B5A1ToB8G8R8A8);
			CasePixelConvert2(R5G5B5A1ToR8G8B8A8);

			CasePixelConvert2(A1R5G5B5ToL8);
			CasePixelConvert2(A1R5G5B5ToL16);
			CasePixelConvert2(A1R5G5B5ToA8);
			CasePixelConvert2(A1R5G5B5ToR5G5B5A1);
			CasePixelConvert2(A1R5G5B5ToA8R8G8B8);
			CasePixelConvert2(A1R5G5B5ToA8B8G8R8);
			CasePixelConvert2(A1R5G5B5ToB8G8R8A8);
			CasePixelConvert2(A1R5G5B5ToR8G8B8A8);

			CasePixelConvert2(R5G6B5ToL8);
			CasePixelConvert2(R5G6B5ToL16);
			CasePixelConvert2(R5G6B5ToR8G8B8);
			CasePixelConvert2(R5G6B5ToB8G8R8);

			CasePixelConvert2(R8G8B8ToL8);
			CasePixelConvert2(R8G8B8ToL16);
			CasePixelConvert2(R8G8B8ToR5G6B5);
			CasePixelConvert2(R8G8B8ToB8G8R8);
			CasePixelConvert2(R8G8B8ToA8R8G8B8);
			CasePixelConvert2(R8G8B8ToA8B8G8R8);
			CasePixelConvert2(R8G8B8ToB8G8R8A8);
			CasePixelConvert2(R8G8B8ToR8G8B8A8);

			CasePixelConvert2(B8G8R8ToL8);
			CasePixelConvert2(B8G8R8ToL16);
			CasePixelConvert2(B8G8R8ToR5G6B5);
			CasePixelConvert2(B8G8R8ToR8G8B8);
			CasePixelConvert2(B8G8R8ToA8R8G8B8);
			CasePixelConvert2(B8G8R8ToA8B8G8R8);
			CasePixelConvert2(B8G8R8ToR8G8B8A8);
			CasePixelConvert2(B8G8R8ToB8G8R8A8)

			CasePixelConvert2(A8R8G8B8ToL8);
			CasePixelConvert2(A8R8G8B8ToL16);
			CasePixelConvert2(A8R8G8B8ToA8);
			CasePixelConvert2(A8R8G8B8ToR5G5B5A1);
			CasePixelConvert2(A8R8G8B8ToA1R5G5B5);			
			CasePixelConvert2(A8R8G8B8ToA8B8G8R8);
			CasePixelConvert2(A8R8G8B8ToB8G8R8A8);
			CasePixelConvert2(A8R8G8B8ToR8G8B8A8);

			CasePixelConvert2(A8B8G8R8ToL8);
			CasePixelConvert2(A8B8G8R8ToL16);
			CasePixelConvert2(A8B8G8R8ToA8);
			CasePixelConvert2(A8B8G8R8ToR5G5B5A1);
			CasePixelConvert2(A8B8G8R8ToA1R5G5B5);
			CasePixelConvert2(A8B8G8R8ToA8R8G8B8);
			CasePixelConvert2(A8B8G8R8ToB8G8R8A8);
			CasePixelConvert2(A8B8G8R8ToR8G8B8A8);

			CasePixelConvert2(B8G8R8A8ToL8);
			CasePixelConvert2(B8G8R8A8ToL16);
			CasePixelConvert2(B8G8R8A8ToA8);
			CasePixelConvert2(B8G8R8A8ToR5G5B5A1);
			CasePixelConvert2(B8G8R8A8ToA1R5G5B5);
			CasePixelConvert2(B8G8R8A8ToA8R8G8B8);
			CasePixelConvert2(B8G8R8A8ToA8B8G8R8);
			CasePixelConvert2(B8G8R8A8ToR8G8B8A8);

			CasePixelConvert2(R8G8B8A8ToL8);
			CasePixelConvert2(R8G8B8A8ToL16);
			CasePixelConvert2(R8G8B8A8ToA8);
			CasePixelConvert2(R8G8B8A8ToR5G5B5A1);
			CasePixelConvert2(R8G8B8A8ToA1R5G5B5);
			CasePixelConvert2(R8G8B8A8ToA8R8G8B8);
			CasePixelConvert2(R8G8B8A8ToA8B8G8R8);
			CasePixelConvert2(R8G8B8A8ToB8G8R8A8);

		default:
			DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND,
				string("不能进行从")
				.append(GetPixelFormatName(srcForamt))
				.append("到")
				.append(GetPixelFormatName(destFormat))
				.append("的转换"),
				"PixelUtil::Convert");
			break;
		}
	}

}	// end namespace dream