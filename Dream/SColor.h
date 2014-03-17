#ifndef __SCOLOR_H__
#define __SCOLOR_H__

#include "DreComplieConfig.h"
#include "DreTypes.h"
#include "DreMath.h"

namespace dream
{

	namespace video
	{
		enum ECOLORFMT
		{
			// 带透明度的32位色
			ECF_A8R8G8B8 = 0,

			// 不带透明度的32位色
			ECF_X8R8G8B8,
			
			// 带透明度的16位色
			ECF_A1R5G5B5,

			// 不带透明度的16位色
			ECF_R5G6B5,

			// 不明的颜色，用于读入时确定颜色
			ECF_UNKNOWN
		};

		//class SColor16
		//{
		//public:
		//	//构造函数
		//	SColor16() : color16_(0)
		//	{
		//	}

		//	SColor16( u32 a, u32 r, u32 g, u32 b ) : 
		//	{
		//	}

		//	u16 color16_;
		//};	// end class SColor16

		class SColor
		{
		public:
		//构造函数
			SColor() : color_(0)
			{
				//留空
			}

			SColor( u32 a, u32 r, u32 g, u32 b ) :
				color_( (a & 0xff)<<24 | (r & 0xff)<<16 | (g & 0xff)<<8 | (b & 0xff) )
			{
				// 留空
			}

			SColor( u32 color ) : color_( color )
			{
				// 留空
			}

		// 标注操作
			inline bool operator == ( const SColor& c ) const
			{
				return color_ == c.color_;
			}

			inline bool operator != ( const SColor& c ) const
			{
				return color_ != c.color_;
			}

			inline SColor operator + ( const SColor& c ) const
			{
				// 检查颜色相加是否溢出
				Assert( c.color_ < 0xffffffff - color_ );

				return SColor( color_ + c.color_ );
			}

			inline SColor operator += ( const SColor& c )
			{
				// 检查颜色相加是否溢出
				Assert( c.color_ < 0xffffffff - color_ );

				color_ += c.color_;
				return *this;
			}

			inline SColor operator - ( const SColor& c ) const
			{
				// 检查颜色相减是否溢出
				Assert( c.color_ < color_ );

				return SColor( color_ - c.color_ );
			}

			inline SColor operator -= ( const SColor& c )
			{
				// 检查颜色相减是否溢出
				Assert( c.color_ < color_ );

				color_ -= c.color_;
				return *this;
			}

			inline SColor operator * ( f32 d ) const
			{
				Assert( d < 0.0f || d > 1.0f );

				return SColor( (u32)(GetAlpha() * d), (u32)(GetRed() * d), (u32)(GetGreen() * d), (u32)(GetBlue() * d) );
			}

			inline SColor operator *= ( f32 d )
			{
				Assert( d < 0.0f || d > 1.0f );

				SetAlpha( (u32)(GetAlpha() * d) );
				SetRed( (u32)(GetRed() * d) );
				SetGreen( (u32)(GetGreen() * d) );
				SetBlue( (u32)(GetBlue() * d) );

				return *this;
			}

		// 基本操作
			// 取得RGBA和颜色的值
			inline u32 GetRed() const { return ( color_ >> 16 ) & 0xff; }
			inline u32 GetGreen() const { return ( color_ >> 8 ) & 0xff; }
			inline u32 GetBlue() const { return color_ & 0xff; }
			inline u32 GetAlpha() const { return ( color_ >> 24 ) & 0xff; }
			inline u32 Get() const { return color_; }

			// 设置RGBA和颜色的值
			inline void SetRed( u32 r ) { color_ |= ( (r & 0xff) << 16 ); }
			inline void SetGreen( u32 g ) { color_ |= ( (g & 0xff) << 8 ); }
			inline void SetBlue( u32 b ) { color_ |= (b & 0xff); }
			inline void SetAlpha( u32 a ) { color_ |= ( (a & 0xff) << 24 ); }
			inline void Set( u32 color ) { color_ = color; }
			inline void Set( u32 a, u32 r, u32 g, u32 b)
			{
				color_ = (((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
			}

			// 取得亮度
			f32 getLightness() const
			{
				return 0.5f * ( Max( Max( GetRed(), GetGreen() ), GetBlue() ) 
					+ Min( Min( GetRed(), GetGreen() ), GetBlue() ) );
			}

			// 取得纯度 
			f32 getLuminance() const
			{
				return 0.3f * GetRed() + 0.59f * GetGreen() + 0.11f * GetBlue();
			}

			// 取得平均颜色
			u32 getAverage() const
			{
				return ( GetRed() + GetGreen() + GetBlue() ) / 3;
			}

			//转换为OpenGL颜色
			inline void ToOpenGlColor( u8 * dest ) const 
			{
				*dest =   (u8)GetRed();
				*++dest = (u8)GetGreen();
				*++dest = (u8)GetBlue();
				*++dest = (u8)GetAlpha();
			}

			u32 color_;

		};	// end class SColor

		extern const SColor WHITE;
		extern const SColor BLACK;
		extern const SColor RED;
		extern const SColor GREEN;
		extern const SColor BLUE;
		extern const SColor YELLOW;
		extern const SColor GRAY;
	}	// end 

}	// end namespace dream

#endif	// end __SCOLOR_H__