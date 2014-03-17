////////////////////////////////////////////////////////////////////////////////////////////////
//
// author	：	roke
// date		：	2013/5/15
// describe	：	define some math constant
// 
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DreMath_H__
#define __DreMath_H__

#include <math.h>
#include <float.h>

#include "DreTypes.h"
#include "DreComplieConfig.h"
#include "DreException.h"

namespace dream
{
	class Math
	{
	public:
	//// 定义数值常量/////////////////////////////////////////////////////////////////////////////////////////////////////
		// 定义各个数值类型的最大最小值
		static const u8 MAX_U8		= UCHAR_MAX;
		static const u8 MIN_U8		= 0;
		static const s8 MAX_S8		= SCHAR_MAX;
		static const s8 MIN_S8		= SCHAR_MIN;
		static const u16 MAX_U16	= USHRT_MAX;
		static const u16 MIN_U16	= 0;
		static const s16 MAX_S16	= SHRT_MAX;
		static const s16 MIN_S16	= SHRT_MIN;
		static const u32 MAX_U32	= UINT_MAX;
		static const u32 MIN_U32	= 0;
		static const s32 MAX_S32	= INT_MAX;
		static const s32 MIN_S32	= INT_MIN;
		static const f32 MAX_F32;
		static const f32 MIN_F32;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// 定义几何常量//////////////////////////////////////////////////////////////////////////////////////////////////////
		// PI_F
		static const f32 PI_F;
		// PI_F * 2
		static const f32 DOUBLE_PI_F;
		// PI_F的倒数.
		static const f32 RECIPROCAL_PI_F;
		// PI_F / 2
		static const f32 HALF_PI_F;
		// 从弧度转角度
		static const f32 DEGTORAD_F;
		// 从角度转弧度
		static const f32 RADTODEG_F;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////定义常用数值函数///////////////////////////////////////////////////////////////////////////////////////////////////

		template< class T >
		static inline T Min( const T a, const T b )
		{
			return a < b ? a : b;
		}

		template<>
		static inline f32 Min( const f32 a, const f32 b )
		{
			return a - b < 0.0f ? a : b;
		}

		template< class T >
		static inline T Max( const T a, const T b )
		{
			return a > b ? a : b;
		}

		template<>
		static inline f32 Max( const f32 a, const f32 b )
		{
			return a - b > 0.0f ? a : b;
		}

		template< class T >
		static inline T Min( const T a, const T b, const T c )
		{
			return a < b ? Min( a, c ) : Min( b, c );
		}

		template< class T >
		static inline T Max( const T a, const T b, const T c )
		{
			return a > b ? Max( a, c ) : Max( b, c );
		}

		template< class T >
		static inline void Swap( T& a, T& b )
		{
			T temp = a;
			a = b;
			b = temp;
		}

		template< class T >
		static inline T Abs( const T a )
		{
			return a < 0 ? -a : a;
		}

		template< class T >
		static inline T Lerp( const T a, const T b, const f32 t )
		{
			return (T)( a * ( 1.0f - t ) + b * t );
		}

		template< class T >
		static inline T Clamp (const T value, const T low, const T& high)
		{
			return Min( Max( value, low ), high);
		}

		static inline void Srand( u32 seed )
		{
			return srand( seed );
		}

		static inline u32 Rand_U32()
		{
			return rand();
		}

		static inline f32 Rand_F32()
		{
			return f32( Rand_U32() )/ f32( RAND_MAX );
		}

		static inline f32 SymmetricRandom_F32()
		{
			return -1.0f + 2.0f * f32( Rand_U32() ) / f32( RAND_MAX );
		}

		static inline f32 Sqrt( f32 value )
		{
			return f32(sqrt(value));
		}

		//是否二的倍数
		static inline bool IsPowerOf2( s32 value )
		{
			if (!value)
				return false;

			return ( value & ( value - 1 ) ) == 0;
		}

		static inline u32 FastLog( u32 num )
		{
			u32 logNum = 0;
			u32 temp = num >> 1;

			while( temp & 0xffffffff )
			{
				temp >>= 1;
				++logNum;
			}

			return logNum;
		}

		static inline f32 FastInvSqrt( f32 value )
		{
			f32 half = 0.5f*value;
			s32 i  = *(s32*) & value;

			i = 0x5f3759df - ( i >> 1 );
			value = * (f32*)&i;
			value = value * ( 1.5f - half * value * value );

			return value;
		}

		static inline f32 FastSqrt( f32 value )
		{
			return FastInvSqrt( value ) * value;
		}
	
		static inline f32 Exp( f32 value)
		{
			return f32( exp( value ) );
		}

		static inline f32 Floor( f32 value)
		{
			return f32( floor( value ) );
		}

		static inline f32 Fmod( f32 numerator, f32 denominator)
		{
			return f32( fmod( numerator, denominator ) );
		}

		inline f32 Log( f32 value)
		{
			return f32( logf( value ) );
		}

		static inline f32 Pow( f32 base, f32 exponent)
		{
			return f32( pow( base, exponent ) );
		}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	////几何图形数学函数//////////////////////////////////////////////////////////////////////////////////////////////////////////
		static inline f32 ACos( f32 value )
		{
			if (-1.0f < value )
			{
				if (value < 1.0f)
					return f32( acos( value ) );
				else
					return 0.0f;
			}
			else
			{
				return PI_F;
			}
		}

		static inline f32 ASin( f32 value)
		{
			if ( -1.0f < value )
			{
				if ( value < 1.0f )
					return f32( asin( value ) );
				else
					return HALF_PI_F;
			}
			else
			{
				return -HALF_PI_F;
			}
		}

		static inline f32 ATan( f32 value )
		{
			return f32( atan( value ) );
		}

		static inline f32 ATan2( f32 numerator, f32 denominator )
		{
			return f32( atan2( numerator, denominator ) );
		}

		static inline f32 Cos( f32 radians )
		{
			return f32( cos( radians ) );
		}

		static inline f32 Sin( f32 radians )
		{
			return f32( sin( radians ) );
		}
	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class DRE_EXPORT_CLASS Float
	{
	private:
		// 检查前置条件
		Float();

		inline static f32 _MakeFloat(int sign, int exp, int mantissa);

		inline static void _SplitFloat(f32 val, int* sign, int* exp, int* mantissa);

	public:
		inline static bool IsNaN(f32 val);

		inline static bool IsValid(f32 val);

		inline static bool IsInfinity(f32 val);

		inline static bool IsZero(f32 val);

		inline static bool IsDenormalized(f32 val);

		inline static bool LessThanZero(f32 val);

		inline static bool GreaterThanZero(f32 val);

		inline static bool LessOrEqualZero(f32 val);

		inline static bool GreaterOrEqualZero(f32 val);

		inline static bool IsEqual(f32 a, f32 b, int maxDiff = DiffDefault);

		inline static bool GreaterThan(f32 a, f32 b);

		inline static bool LessThan(f32 a, f32 b);

		inline static bool GreaterEqual(f32 a, f32 b);

		inline static bool LessEqual(f32 a, f32 b);

		inline static f32 ClampZeroToOne(f32 val);

		inline static f32 ClampAToB(f32 val, f32 A, f32 B);

		inline static f32 ClampNonnegative(f32 val);

		inline static f32 InvSqrt(f32 val);

		inline static f32 FastSqrt(f32 val);

		inline static void Swap(f32& a, f32& b);

	public:
		// 精确到尾数后六位，误差≈0.000002
		static const int DiffSix;
		// 精确到尾数后五位，误差≈0.000015
		static const int DiffFive;
		// 精确到尾数后四位，误差≈0.000122
		static const int DiffFour;
		// 精确到尾数后三位，误差≈0.001953
		static const int DiffThree;
		// 精确到尾数后两位，误差≈0.015625
		static const int DiffTwo;
		// 默认精确位数
		static const int DiffDefault;

		static const f32 NaN;
		static const f32 Zero;
		static const f32 PositiveInfinity;
		static const f32 NegativeInfinity;

	private:
		// 用于执行Float构造函数来检查前置条件
		static Float instance;
	};

#include "DreFloatImpl.h"

}	// namespace dream

#endif // !__DreMath_H__
