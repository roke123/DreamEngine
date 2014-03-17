#ifndef __DREPIXELCOnVERT_H__
#define __DREPIXELCONVERT_H__

#include "DrePixelFormat.h"
#include "DreException.h"

namespace dream
{
	//---------------------------------------------------���ػ�����λ---------------------------------------------//
	// ���ص�λ
	template<int pixelFormat>
	struct PixelUnit
	{
		typedef u8 Type;
	};
	// DRE_PIXEL_FORMAT_L_8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_L_8>
	{
		typedef u8 Type;
	};
	// DRE_PIXEL_FORMAT_L_16�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_L_16>
	{
		typedef u16 Type;
	};
	// DRE_PIXEL_FORMAT_L_16�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_A_8>
	{
		typedef u8 Type;
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		typedef u16 Type;
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		typedef u16 Type;
	};
	// DRE_PIXEL_FORMAT_R5G6B5�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_R5G6B5>
	{
		typedef u16 Type;
	};
	struct R8G8B8 { 
		R8G8B8(u8 r, u8 g, u8 b) : R(r), G(g), B(b) {}
		// ע�������ɵ͵�ַ����ߵ�ַ
		u8 B, G, R; 
	};
	// DRE_PIXEL_FORMAT_R8G8B8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_R8G8B8>
	{
		typedef R8G8B8 Type;
	};
	struct B8G8R8 { 
		B8G8R8(u8 b, u8 g, u8 r) : R(r), G(g), B(b) {}
		// ע�������ɵ͵�ַ����ߵ�ַ
		u8 R, G, B;
	};
	// DRE_PIXEL_FORMAT_B8G8R8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_B8G8R8>
	{
		typedef B8G8R8 Type;
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		typedef u32 Type;
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		typedef u32 Type;
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		typedef u32 Type;
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8�����ص�λ
	template<>
	struct PixelUnit<DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		typedef u32 Type;
	};

#	define GetPixelConvertID(src, dest) src << 8 | dest

	// ����ת����ģ��
	template<DRE_PIXEL_FORMAT U, DRE_PIXEL_FORMAT V>
	struct PixelConvertBase
	{
		typedef typename PixelUnit<U>::Type		SrcType;
		typedef typename PixelUnit<V>::Type		DestType;
		enum : int
		{
			SrcFormat							= U,
			DestFormat							= V,
		};
		enum { ID = GetPixelConvertID(SrcFormat, DestFormat) };
		static DestType Do(SrcType src)
		{
			DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "���ܽ��д����͵�����ת��", "PixelConvert::Do");
		}
	};
	

//------------------------------------------------DRE_PIXEL_FORMAT_L_8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_A_8
	struct L8ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			// ֱ�ӷ���8λ����
			return src;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_L_16
	struct L8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8ת��ΪL_16��8λ
			return static_cast<DestType>(src) << 8;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct L8ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8����λת����R5G5B5A1��Redλ
			return static_cast<DestType>(src) << 8 & 0xf800;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct L8ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8����λת����A1R5G5B5��Redλ
			return static_cast<DestType>(src) << 7 & 0x7c00;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_R5G6B5
	struct L8ToR5G6B5: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_R5G6B5>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8����λת����R5G6B5��Redλ
			return static_cast<DestType>(src) << 8 & 0xf800;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_R8G8B8
	struct L8ToR8G8B8: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8����λת����R8G8B8��Redλ
			return  DestType(src, 0, 0);
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_B8G8R8
	struct L8ToB8G8R8: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8����λת����B8G8R8��Redλ
			return  DestType(0, 0, src);
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct L8ToA8R8G8B8: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8ת����A8R8G8B8��Redλ
			return static_cast<DestType>(src) << 16;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct L8ToA8B8G8R8: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8ת����A8B8G8R8��Redλ
			return static_cast<DestType>(src);
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct L8ToB8G8R8A8: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8ת����B8G8R8A8��Redλ
			return static_cast<DestType>(src) << 8;
		}
	};
	// DRE_PIXEL_FORMAT_L_8 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct L8ToR8G8B8A8: public PixelConvertBase<DRE_PIXEL_FORMAT_L_8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_8ת����R8G8B8A8��Redλ
			return static_cast<DestType>(src) << 24;
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_L_16----------------------------------------------------//

	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_L_8
	struct L16ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪL_8
			return static_cast<DestType>(src >> 8);
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_A_8
	struct L16ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪA_8
			return static_cast<DestType>(src >> 8);
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct L16ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�5λת��ΪR5G5B5A1��redλ
			return static_cast<DestType>(src) & 0xf800;
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct L16ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�5λת��ΪA1R5G5B5��redλ
			return static_cast<DestType>(src) & 0x7c00;
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_R5G6B5
	struct L16ToR5G6B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_R5G6B5>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�5λת��ΪR5G6B5��redλ
			return static_cast<DestType>(src) & 0xf800;
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_R8G8B8
	struct L16ToR8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪR8G8B8��redλ
			return DestType(src >> 8, 0, 0);
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_B8G8R8
	struct L16ToB8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪB8G8R8��redλ
			return DestType(0, 0, src >> 8);
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct L16ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪR8G8B8A8��redλ
			return static_cast<DestType>(src >> 8) << 16;
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct L16ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪB8G8R8A8��redλ
			return static_cast<DestType>(src & 0x0000ff00);
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct L16ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪB8G8R8A8��redλ
			return static_cast<DestType>(src & 0x0000ff00);
		}
	};
	// DRE_PIXEL_FORMAT_L_16 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct L16ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_L_16, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{
			// ��L_16�ĸ�8λת��ΪR8G8B8A8��redλ
			return static_cast<DestType>(src >> 8) << 24;
		}
	};
	
//------------------------------------------------DRE_PIXEL_FORMAT_A_8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_L_8
	struct A8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ֱ�ӷ���8λ͸����
			return src;
		}
	};
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_L_16
	struct A8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ��͸����ת��ΪL_16��8λ
			return static_cast<DestType>(src) << 8;
		}
	};
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct A8ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			if(src == 0)
				return 0x0000;
			else
				return 0x0001;
		}
	};
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct A8ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			if(src == 0)
				return 0x0000;
			else
				return 0x8000;
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_B8G8R8>
	{
	};*/
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct A8ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			// ��͸����ֱ����ΪBGRA͸����
			return static_cast<DestType>(src) << 24;
		}
	};
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct A8ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			// ��͸����ֱ����ΪBGRA͸����
			return static_cast<DestType>(src) << 24;
		}
	};
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_B8R8G8A8
	struct A8ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{
			// ��͸����ֱ����ΪBGRA͸����
			return static_cast<DestType>(src);
		}
	};
	// DRE_PIXEL_FORMAT_A_8 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct A8ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A_8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{
			// ��͸����ֱ����ΪRGBA͸����
			return static_cast<DestType>(src);
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_R5G5B5A1----------------------------------------------------//

	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_L_8
	struct R5G5B5A1ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡR5G5B5A1��redλ��ΪL8�ĸ���λ
			return static_cast<DestType>(src & 0xf800 >> 8);
		}
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_L_16
	struct R5G5B5A1ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡR5G5B5A1��redλ��ΪL16�ĸ���λ
			return static_cast<DestType>(src & 0xf800);
		}
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_A_8
	struct R5G5B5A1ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			if(src & 0x0001)
				return 0xff;
			else
				return 0x00;
		}
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct R5G5B5A1ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			return static_cast<DestType>(src & 0xfffe >> 1) | static_cast<DestType>(src << 15);
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_B8G8R8>
	{
	};*/
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct R5G5B5A1ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x0001)
				alpha = 0xff000000;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0xf800) << 8 |	// red
				static_cast<DestType>(src & 0x07c0) << 5 |	// green
				static_cast<DestType>(src & 0x003e) << 2 |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct R5G5B5A1ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x0001)
				alpha = 0xff000000;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0xf800) >> 8 |	// red
				static_cast<DestType>(src & 0x07c0) << 5 |	// green
				static_cast<DestType>(src & 0x003e) << 18 |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct R5G5B5A1ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x0001)
				alpha = 0x000000ff;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0xf800) |	// red
				static_cast<DestType>(src & 0x07c0) << 13 |	// green
				static_cast<DestType>(src & 0x003e) << 26 |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_R5G5B5A1 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct R5G5B5A1ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G5B5A1, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x0001)
				alpha = 0x000000ff;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0xf800) << 16 |	// red
				static_cast<DestType>(src & 0x07c0) << 13 |	// green
				static_cast<DestType>(src & 0x003e) << 10 |		// blue
				alpha;	
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_A1R5G5B5----------------------------------------------------//

	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_L_8
	struct A1R5G5B5ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡA1R5G5B5��redλ��ΪL8�ĸ���λ
			return static_cast<DestType>(src & 0x7c00 >> 7);
		}
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_L_16
	struct A1R5G5B5ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡA1R5G5B5��redλ��ΪL16�ĸ���λ
			return static_cast<DestType>(src & 0x7c00) << 1;
		}
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_A_8
	struct A1R5G5B5ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			if(src & 0x0001)
				return 0xff;
			else
				return 0x00;
		}
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct A1R5G5B5ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			return static_cast<DestType>(src & 0x7fff << 1) | static_cast<DestType>(src >> 15);
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_B8G8R8>
	{
	};*/
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct A1R5G5B5ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x8000)
				alpha = 0xff000000;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0x7c00) << 9 |	// red
				static_cast<DestType>(src & 0x03e0) << 6 |	// green
				static_cast<DestType>(src & 0x001f) << 3 |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct A1R5G5B5ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x8000)
				alpha = 0xff000000;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0x7c00) >> 7 |	// red
				static_cast<DestType>(src & 0x03e0) << 6 |	// green
				static_cast<DestType>(src & 0x001f) << 19 |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct A1R5G5B5ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x8000)
				alpha = 0x000000ff;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0x7c00) << 1 |	// red
				static_cast<DestType>(src & 0x03e0) << 14 |	// green
				static_cast<DestType>(src & 0x001f) << 27 |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A1R5G5B5 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct A1R5G5B5ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A1R5G5B5, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x00000000;
			if(src & 0x8000)
				alpha = 0x000000ff;
			else
				alpha = 0x00000000;
					
			return 
				static_cast<DestType>(src & 0x7c00) << 17 |	// red
				static_cast<DestType>(src & 0x03e0) << 14 |	// green
				static_cast<DestType>(src & 0x001f) << 11 |		// blue
				alpha;	
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_R5G6B5----------------------------------------------------//

	// DRE_PIXEL_FORMAT_R5G6B5 to DRE_PIXEL_FORMAT_L_8
	struct R5G6B5ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡR5G6B5��redλ��ΪL8�ĸ���λ
			return static_cast<DestType>(src & 0xf800 >> 8);
		}
	};
	// DRE_PIXEL_FORMAT_R5G6B5 to DRE_PIXEL_FORMAT_L_16
	struct R5G6B5ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡR5G6B5��redλ��ΪL8�ĸ���λ
			return static_cast<DestType>(src & 0xf800);
		}
	};
	/*DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת��
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_A_8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
	};*/
	struct R5G6B5ToR8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_R8G8B8>	
	{
		static DestType Do(SrcType src)
		{
			return DestType(
				static_cast<u8>(src & 0xf800 >> 8),
				static_cast<u8>(src & 0x07e0 >> 3),
				static_cast<u8>(src & 0x001f << 3));
		}
	};
	struct R5G6B5ToB8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_B8G8R8>	
	{
		static DestType Do(SrcType src)
		{
			return DestType(
				static_cast<u8>(src & 0x001f << 3),
				static_cast<u8>(src & 0x07e0 >> 3),
				static_cast<u8>(src & 0xf800 >> 8));
		}
	};
	/*struct R5G6B5ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
	};
	struct R5G6R5ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
	};
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
	};
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R5G6B5, DRE_PIXEL_FORMAT_R8G8B8A8>
		 : public PixelConvertBase<DRE_PIXEL_FORDRE_PIXEL_FORMAT_RGB_16MAT_RGBA_16, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
	};*/

//------------------------------------------------DRE_PIXEL_FORMAT_R8G8B8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_R8G8B8 to DRE_PIXEL_FORMAT_L_8
	struct R8G8B8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡR8G8B8��redλ��ΪL8
			return static_cast<DestType>(src.R);
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8 to DRE_PIXEL_FORMAT_L_16
	struct R8G8B8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡR8G8B8��redλ��ΪL16�ĸ�8λ
			return static_cast<DestType>(src.R) << 8;
		}
	};
	/*DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת��
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_A_8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
	};*/
	struct R8G8B8ToR5G6B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_R5G6B5>	
	{
		static DestType Do(SrcType src)
		{
			return 
				static_cast<DestType>(src.R & 0xf800) |
				static_cast<DestType>(src.G & 0xf800) >> 5 |
				static_cast<DestType>(src.B & 0xf800) >> 11;
		}
	};
	struct R8G8B8ToB8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_B8G8R8>	
	{
		static DestType Do(SrcType src)
		{
			return DestType(src.B, src.G, src.R);
		}
	};
	struct R8G8B8ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{
			return 
				0xff000000							|
				static_cast<DestType>(src.R) << 16	|
				static_cast<DestType>(src.G) << 8	|
				static_cast<DestType>(src.B);
		}
	};
	struct R8G8B8ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{
			return 
				0xff000000							|
				static_cast<DestType>(src.B) << 16	|
				static_cast<DestType>(src.G) << 8	|
				static_cast<DestType>(src.R);
		}
	};
	struct R8G8B8ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{
			return 
				0x000000ff							|
				static_cast<DestType>(src.B) << 24	|
				static_cast<DestType>(src.G) << 16	|
				static_cast<DestType>(src.B) << 8;
		}
	};
	struct R8G8B8ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{
			return 
				0xff000000							|
				static_cast<DestType>(src.R) << 24	|
				static_cast<DestType>(src.G) << 16	|
				static_cast<DestType>(src.B) << 8;
		}
	};

	//------------------------------------------------DRE_PIXEL_FORMAT_B8G8R8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_B8G8R8 to DRE_PIXEL_FORMAT_L_8
	struct B8G8R8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡB8G8R8��redλ��ΪL8
			return static_cast<DestType>(src.R);
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8 to DRE_PIXEL_FORMAT_L_16
	struct B8G8R8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡB8G8R8��redλ��ΪL16�ĸ�8λ
			return static_cast<DestType>(src.R) << 8;
		}
	};
	/*DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת��
	struct PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_A_8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
	};*/
	struct B8G8R8ToR5G6B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_R5G6B5>	
	{
		static DestType Do(SrcType src)
		{
			return 
				static_cast<DestType>(src.R & 0xf800) |
				static_cast<DestType>(src.G & 0xf800) >> 5 |
				static_cast<DestType>(src.B & 0xf800) >> 11;
		}
	};
	struct B8G8R8ToR8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_R8G8B8>	
	{
		static DestType Do(SrcType src)
		{
			return DestType(src.R, src.G, src.B);
		}
	};
	struct B8G8R8ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{				
			return	
				0xff000000							| 
				static_cast<DestType>(src.R) << 16	|
				static_cast<DestType>(src.G) << 8	|
				static_cast<DestType>(src.B);
		}
	};
	struct B8G8R8ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{				
			return	
				0xff000000							| 
				static_cast<DestType>(src.B) << 16	|
				static_cast<DestType>(src.G) << 8	|
				static_cast<DestType>(src.R);
		}
	};
	struct B8G8R8ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{				
			return	
				0x000000ff							| 
				static_cast<DestType>(src.R) << 16	|
				static_cast<DestType>(src.G) << 8	|
				static_cast<DestType>(src.B);
		}
	};
	struct B8G8R8ToR8G8B8A8 : PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{				
			return	
				0x000000ff							| 
				static_cast<DestType>(src.R) << 24	|
				static_cast<DestType>(src.G) << 16	|
				static_cast<DestType>(src.B) << 8;
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_A8R8G8B8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_L_8
	struct A8R8G8B8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡA8R8G8B8��redλ��ΪL8
			return static_cast<DestType>(src & 0x00ff0000 >> 16);
		}
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_L_16
	struct A8R8G8B8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡA8R8G8B8��redλ��ΪL16�ĸ�8λ
			return static_cast<DestType>(src & 0x00ff0000 >> 8) ;
		}
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_A_8
	struct A8R8G8B8ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			return static_cast<DestType>(src >> 24);
		}
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct A8R8G8B8ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0xff000000)
				alpha = 0x0001;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0x00f80000 >> 8) |			// red
				static_cast<DestType>(src & 0x0000f800 >> 5) |		// green
				static_cast<DestType>(src & 0x000000f8 >> 2) |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct A8R8G8B8ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0xff000000)
				alpha = 0x1000;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0x00f80000 >> 9) |			// red
				static_cast<DestType>(src & 0x0000f800 >> 6) |		// green
				static_cast<DestType>(src & 0x000000f8 >> 3) |		// blue
				alpha;												// alpha
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_B8G8B8>
	{
	};*/
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct A8R8G8B8ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x000000ff << 16	|	// red
				src & 0x0000ff00		|	// green
				src & 0x00ff0000 >> 16	|	// blue
				src & 0xff0000;			// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct A8R8G8B8ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x00ff0000 >> 8	|	// red
				src & 0x0000ff00 << 8	|	// green
				src & 0x000000ff << 24	|	// blue
				src & 0xff000000 >> 24;			// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A8R8G8B8 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct A8R8G8B8ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8R8G8B8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x00ffffff << 8	|	
				src & 0xff000000 >> 24;			// alpha
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_A8B8G8R8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_L_8
	struct A8B8G8R8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡA8B8G8R8��redλ��ΪL8
			return static_cast<DestType>(src);
		}
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_L_16
	struct A8B8G8R8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡA8B8G8R8��redλ��ΪL16�ĸ�8λ
			return static_cast<DestType>(src & 0x000000ff << 8) ;
		}
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_A_8
	struct A8B8G8R8ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			return static_cast<DestType>(src >> 24);
		}
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct A8B8G8R8ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0xff000000)
				alpha = 0x0001;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0x000000f8 << 8) |			// red
				static_cast<DestType>(src & 0x0000f800 >> 5) |		// green
				static_cast<DestType>(src & 0x00f80000 >> 18) |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct A8B8G8R8ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0xff000000)
				alpha = 0x1000;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0x000000f8 << 7) |			// red
				static_cast<DestType>(src & 0x0000f800 >> 6) |		// green
				static_cast<DestType>(src & 0x00f80000 >> 19) |		// blue
				alpha;												// alpha
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_B8G8B8>
	{
	};*/
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct A8B8G8R8ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x000000ff << 16	|	// red
				src & 0x0000ff00		|	// green
				src & 0x00ff0000 >> 16	|	// blue
				src & 0xff000000;			// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct A8B8G8R8ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x00ffffff << 8	|
				src & 0xff000000 >> 24;			// alpha
		}
	};
	// DRE_PIXEL_FORMAT_A8B8G8R8 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct A8B8G8R8ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_A8B8G8R8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x000000ff << 24|
				src & 0x0000ff00 << 8 |
				src & 0x00ff0000 >> 8 |
				src & 0xff000000 >> 24;			// alpha
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_B8G8R8A8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_L_8
	struct B8G8R8A8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡB8G8R8A8��redλ��ΪL8
			return static_cast<DestType>(src & 0x0000ff00 >> 8);
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_L_16
	struct B8G8R8A8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡB8G8R8A8��redλ��ΪL16�ĸ�8λ
			return static_cast<DestType>(src & 0x0000ff00);
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_A_8
	struct B8G8R8A8ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			return static_cast<DestType>(src);
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct B8G8R8A8ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0x000000ff)
				alpha = 0x0001;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0x0000f800) |		// red
				static_cast<DestType>(src & 0x00f80000 >> 13) |		// green
				static_cast<DestType>(src & 0xf8000000 >> 26) |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct B8G8R8A8ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0x000000ff)
				alpha = 0x1000;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0x0000f800 >> 1) |		// red
				static_cast<DestType>(src & 0x00f80000 >> 14) |		// green
				static_cast<DestType>(src & 0xf8000000 >> 27) |		// blue
				alpha;												// alpha
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_R5G6B5>
	 	: public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_B8G8R8>
	{
	};*/
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct B8G8R8A8ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0xff000000 >> 24	|	// red
				src & 0x00ff0000 >> 8	|	// green
				src & 0x0000ff00 << 8	|	// blue
				src & 0x000000ff << 24;			// alpha	
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct B8G8R8A8ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0xffffff00 >> 8	|	// red
				src & 0x000000ff << 24;			// alpha	
		}
	};
	// DRE_PIXEL_FORMAT_B8G8R8A8 to DRE_PIXEL_FORMAT_R8G8B8A8
	struct B8G8R8A8ToR8G8B8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_B8G8R8A8, DRE_PIXEL_FORMAT_R8G8B8A8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0x0000ff00 << 16	|	// red
				src & 0x00ff0000	 	|	// green
				src & 0xff000000 >> 16	|	// blue
				src & 0x000000ff;			// alpha	
		}
	};

//------------------------------------------------DRE_PIXEL_FORMAT_R8G8B8A8----------------------------------------------------//

	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_L_8
	struct R8G8B8A8ToL8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_L_8>
	{
		static DestType Do(SrcType src)
		{
			// ȡR8G8B8A8��redλ��ΪL8
			return static_cast<DestType>(src & 0xff000000 >> 24);
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_L_16
	struct R8G8B8A8ToL16 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_L_16>
	{
		static DestType Do(SrcType src)
		{
			// ȡR8G8B8A8��redλ��ΪL16�ĸ�8λ
			return static_cast<DestType>(src & 0xff000000 >> 16);
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_A_8
	struct R8G8B8A8ToA8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_A_8>
	{
		static DestType Do(SrcType src)
		{
			return static_cast<DestType>(src);
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_R5G5B5A1
	struct R8G8B8A8ToR5G5B5A1 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_R5G5B5A1>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0x000000ff)
				alpha = 0x0001;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0xf8000000 >> 16) |		// red
				static_cast<DestType>(src & 0x00f80000 >> 13) |		// green
				static_cast<DestType>(src & 0x0000f800 >> 10) |		// blue
				alpha;												// alpha
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_A1R5G5B5
	struct R8G8B8A8ToA1R5G5B5 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_A1R5G5B5>
	{
		static DestType Do(SrcType src)
		{
			DestType alpha = 0x0000;
			if(src & 0x000000ff)
				alpha = 0x1000;
			else
				alpha = 0x0000;
					
			return 
				static_cast<DestType>(src & 0xf8000000 >> 17) |		// red
				static_cast<DestType>(src & 0x00f80000 >> 14) |		// green
				static_cast<DestType>(src & 0x0000f800 >> 11) |		// blue
				alpha;												// alpha
		}
	};
	/* DRE_PIXEL_FORMAT_R5G6B5��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_R5G6B5>
	 	: public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_R5G6B5>
	{
	};*/
	/* DRE_PIXEL_FORMAT_R8G8B8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_R8G8B8>
	{
	};*/
	/* DRE_PIXEL_FORMAT_B8G8R8��͸���Ȳ���ת
	struct PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_B8G8R8>
	{
	};*/
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_A8R8G8B8
	struct R8G8B8A8ToA8R8G8B8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_A8R8G8B8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0xffffff00 >> 8	|	// red
				src & 0x000000ff << 24;			// alpha	
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_A8B8G8R8
	struct R8G8B8A8ToA8B8G8R8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_A8B8G8R8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0xff000000 >> 24	|	// red
				src & 0x00ff0000 >> 8	|	// green
				src & 0x0000ff00 << 8	|	// blue
				src & 0x000000ff << 24;			// alpha	
		}
	};
	// DRE_PIXEL_FORMAT_R8G8B8A8 to DRE_PIXEL_FORMAT_B8G8R8A8
	struct R8G8B8A8ToB8G8R8A8 : public PixelConvertBase<DRE_PIXEL_FORMAT_R8G8B8A8, DRE_PIXEL_FORMAT_B8G8R8A8>
	{
		static DestType Do(SrcType src)
		{				
			return 
				src & 0xff000000 >> 16	|	// red
				src & 0x00ff0000	 	|	// green
				src & 0x0000ff00 << 16	|	// blue
				src & 0x000000ff;			// alpha	
		}
	};

};	// end namespace dream

#endif	// end __DREPIXELCONVERT_H__