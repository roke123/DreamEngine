////////////////////////////////////////////////////////////////////////////////////////////////
//
// author	：	roke
// date		：	2013/5/15
// describe	：	define some math constant
// 
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DreMath_H__
#define __DreMath_H__

#include <cmath>

#include "DreTypes.h"
#include "DreComplieConfig.h"
#include "DreException.h"

namespace dream
{
	//// 定义数值常量/////////////////////////////////////////////////////////////////////////////////////////////////////
	// 定义各个数值类型的最大最小值
	const u8 MAX_U8		= UCHAR_MAX;
	const u8 MIN_U8		= 0;
	const s8 MAX_S8		= SCHAR_MAX;
	const s8 MIN_S8		= SCHAR_MIN;
	const u16 MAX_U16	= USHRT_MAX;
	const u16 MIN_U16	= 0;
	const s16 MAX_S16	= SHRT_MAX;
	const s16 MIN_S16	= SHRT_MIN;
	const u32 MAX_U32	= UINT_MAX;
	const u32 MIN_U32	= 0;
	const s32 MAX_S32	= INT_MAX;
	const s32 MIN_S32	= INT_MIN;
	const f32 MAX_F32	= FLT_MAX;
	const f32 MIN_F32	= FLT_MIN;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// 定义几何常量//////////////////////////////////////////////////////////////////////////////////////////////////////
	// PI_F
	const f32 PI_F = 3.141592f;
	// PI_F * 2
	const f32 DOUBLE_PI_F = 2 * PI_F;
	// PI_F的倒数.
	const f32 RECIPROCAL_PI_F = 1 / PI_F;
	// PI_F / 2
	const f32 HALF_PI_F = PI_F / 2;
	// 从弧度转角度
	const f32 DEGTORAD_F = 180 / PI_F;
	// 从角度转弧度
	const f32 RADTODEG_F = PI_F / 180;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////定义常用数值函数///////////////////////////////////////////////////////////////////////////////////////////////////

	template< class T >
	inline T Min( const T a, const T b )
	{
		return a < b ? a : b;
	}

	template<>
	inline f32 Min( const f32 a, const f32 b )
	{
		return a - b < 0.0f ? a : b;
	}

	template< class T >
	inline T Max( const T a, const T b )
	{
		return a > b ? a : b;
	}

	template<>
	inline f32 Max( const f32 a, const f32 b )
	{
		return a - b > 0.0f ? a : b;
	}

	template< class T >
	inline T Min( const T a, const T b, const T c )
	{
		return a < b ? Min( a, c ) : Min( b, c );
	}

	template< class T >
	inline T Max( const T a, const T b, const T c )
	{
		return a > b ? Max( a, c ) : Max( b, c );
	}

	template< class T >
	inline void Swap( T& a, T& b )
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template< class T >
	inline T Abs( const T a )
	{
		return a < 0 ? -a : a;
	}

	template< class T >
	inline T Lerp( const T a, const T b, const f32 t )
	{
		return (T)( a * ( 1.0f - t ) + b * t );
	}

	template< class T >
	inline T Clamp (const T value, const T low, const T& high)
	{
		return Min( Max( value, low ), high);
	}

	inline void Srand( u32 seed )
	{
		return srand( seed );
	}

	inline u32 Rand_U32()
	{
		return rand();
	}

	inline f32 Rand_F32()
	{
		return f32( Rand_U32() )/ f32( RAND_MAX );
	}

	inline f32 SymmetricRandom_F32()
	{
		return -1.0f + 2.0f * f32( Rand_U32() ) / f32( RAND_MAX );
	}

	inline f32 Sqrt( f32 value )
	{
		return f32(sqrt(value));
	}

	//是否二的倍数
	inline bool IsPowerOf2( s32 value )
	{
		if (!value)
			return false;

		return ( value & ( value - 1 ) ) == 0;
	}

	inline u32 FastLog( u32 num )
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

	inline f32 FastInvSqrt( f32 value )
	{
		f32 half = 0.5f*value;
		s32 i  = *(s32*) & value;

		i = 0x5f3759df - ( i >> 1 );
		value = * (f32*)&i;
		value = value * ( 1.5f - half * value * value );

		return value;
	}

	inline f32 FastSqrt( f32 value )
	{
		return FastInvSqrt( value ) * value;
	}
	
	inline f32 Exp( f32 value)
	{
		return f32( exp( value ) );
	}

	inline f32 Floor( f32 value)
	{
		return f32( floor( value ) );
	}

	inline f32 Fmod( f32 numerator, f32 denominator)
	{
		return f32( fmod( numerator, denominator ) );
	}

	inline f32 Log( f32 value)
	{
		return f32( logf( value ) );
	}

	inline f32 Pow( f32 base, f32 exponent)
	{
		return f32( pow( base, exponent ) );
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

////几何图形数学函数//////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline f32 ACos( f32 value )
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

	inline f32 ASin( f32 value)
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

	inline f32 ATan( f32 value )
	{
		return f32( atan( value ) );
	}

	inline f32 ATan2( f32 numerator, f32 denominator )
	{
		return f32( atan2( numerator, denominator ) );
	}

	inline f32 Cos( f32 radians )
	{
		return f32( cos( radians ) );
	}

	inline f32 Sin( f32 radians )
	{
		return f32( sin( radians ) );
	}

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

	
	////////////////////////////////////////// imp /////////////////////////////////////////////////
	// 转换float到int操作
	#if defined(C99)
	#define _fval_to_ival(fval) *(int*)&(fval)
	#define _ival_to_fval(ival) *(float*)&(ival)
	#else
	#define _fval_to_ival(fval,ival) memcpy(&ival,&fval,sizeof(float)) // these are safer, but perhaps slower
	#define _ival_to_fval(ival,fval) memcpy(&fval,&ival,sizeof(int))   // C99 does not make the *(int*)& types well-defined
	#endif

	// 计算符号位蒙版，c++为保证移位为乘除2操作，右移位补充空位是使用符号位
	#if defined(_SIGNED_SHIFT)
	#define SIGNMASK(i) ((i)>>31) 
	#else
	#define SIGNMASK(i) (~((((unsigned int)(i))>>31)-1))
	#endif

		f32 Float::_MakeFloat(int sign, int exp, int mantissa)
		{
			int iVal = sign | exp | mantissa;
			return _ival_to_fval(iVal);
		}

		void Float::_SplitFloat(f32 val, int* sign, int* exp, int* mantissa)
		{
			int iVal = _fval_to_ival(val);
			*sign = iVal & 0x80000000;
			*exp = iVal & 0x7f800000;
			*mantissa = iVal & 0x007fffff;
		}

		bool Float::IsNaN(f32 val)
		{
			int sign = 0, exp = 0, mantissa = 0;
			_SplitFloat(val, &sign, &exp, &mantissa);
			return (exp == 0x7F800000) && (mantissa != 0x00000000);
		}

		bool Float::IsValid(f32 val)
		{
			int sign = 0, exp = 0, mantissa = 0;
			_SplitFloat(val, &sign, &exp, &mantissa);
			return exp != 0x7F800000;
		}

		bool Float::IsInfinity(f32 val)
		{
			int sign = 0, exp = 0, mantissa = 0;
			_SplitFloat(val, &sign, &exp, &mantissa);
			return (exp == 0x7F800000) && (mantissa == 0x00000000);
		}

		bool Float::IsZero(f32 val)
		{
			int ival = _fval_to_ival(val) << 1;
			return ival == 0;
		}

		bool Float::IsDenormalized(f32 val)
		{
			int sign = 0, exp = 0, mantissa = 0;
			_SplitFloat(val, &sign, &exp, &mantissa);
			return (exp == 0x00000000) && (mantissa != 0x00000000);
		}

		bool Float::LessThanZero(f32 val)
		{
			int iVal = _fval_to_ival(val);
			// 转为无符号数比较，即符号位为1，且尾数不为0
			return iVal > 0x80000000u;
		}

		bool Float::GreaterThanZero(f32 val)
		{
			int iVal = _fval_to_ival(val);
			return iVal > 0;
		}

		bool Float::LessOrEqualZero(f32 val)
		{
			int iVal = _fval_to_ival(val);
			return iVal <= 0;
		}

		bool Float::GreaterOrEqualZero(f32 val)
		{
			int iVal = _fval_to_ival(val);
			// 转为无符号数比较，即符号位为0
			return iVal <= 0x80000000u;
		}

		f32 Float::ClampZeroToOne(f32 val)
		{
			int iVal = _fval_to_ival(val);
			// 如小于0，mark = 0xffffffff，大于零mark=0x00000000
			int mark = SIGNMASK(iVal);
			// 如iVal小于0，清零，如大于0，保留原值
			iVal &= ~mark;

			f32 fval = 1.0f - _ival_to_fval(iVal);
			iVal = _fval_to_ival(fval);
			// 如小于0，mark = 0xffffffff，大于零mark=0x00000000
			mark = SIGNMASK(iVal);
			// 如iVal小于0，清零，如大于0，保留原值
			iVal &= ~mark;

			return 1.0f - _ival_to_fval(iVal);
		}

		bool Float::IsEqual(f32 a, f32 b, int maxDiff /* = DiffDefault */)
		{
			int iValA = _fval_to_ival(a);
			int iValB = _fval_to_ival(b);
			int mark = SIGNMASK(iValA ^ iValB);
			int diff = ((0x80000000 - iValA) & mark) | (iValA & ~mark) - iValB;

			int v1 = maxDiff + diff;
			int v2 = maxDiff - diff;

			return (v1 | v2) >= 0;
		}

		bool Float::GreaterThan(f32 a, f32 b)
		{
			int iValA = _fval_to_ival(a);
			int iValB = _fval_to_ival(b);
			// 检查是否A、B都为负数
			int test = (iValA & iValB) & 0x80000000;
			if (test)
			{
				// 为负数时，int较大的数较小
				return iValB > iValA;
			}
			return iValA > iValB;
		}

		bool Float::LessThan(f32 a, f32 b)
		{
			int iValA = _fval_to_ival(a);
			int iValB = _fval_to_ival(b);
			// 检查是否A、B都为负数
			int test = (iValA & iValB) & 0x80000000;
			if (test)
			{
				// 为负数时，int较大的数较小
				return iValB < iValA;
			}
			return iValA < iValB;
		}

		bool Float::GreaterEqual(f32 a, f32 b)
		{
			if (IsEqual(a, b))
				return true;

			return GreaterThan(a, b);
		}

		bool Float::LessEqual(f32 a, f32 b)
		{
			if (IsEqual(a, b))
				return true;

			return GreaterThan(a, b);
		}

		f32 Float::ClampAToB(f32 val, f32 A, f32 B)
		{
			DreAssert(A < B, "");
			val -= A;
			val /= (B - A);
			val = ClampZeroToOne(val);
			val *= (B - A);
			val += A;
			DreAssert((A <= val) && (val <= B), "");
			return val;
		}

		f32 Float::ClampNonnegative(f32 val)
		{
			int iVal = _fval_to_ival(val);
			int mark = SIGNMASK(iVal);
			iVal = iVal & ~mark;
			return _ival_to_fval(iVal);
		}

		f32 Float::InvSqrt(f32 val)
		{
			DreAssert(val > 0, "");

			f32 valHalf = val * 0.5f;
			int i = _fval_to_ival(val);
			i = 0x5f375a86 - (i >> 1);
			val = _ival_to_fval(i);
			val = val * (1.5f - valHalf * val * val);
			return val;
		}

		f32 Float::FastSqrt(f32 val)
		{
			DreAssert(val >= 0, "");

			int ival = _fval_to_ival(val);
			// 对于0和非规范数都返回0
			if (0 == ((ival >> 23) & 255))
				return 0;
			return val * InvSqrt(val);
		}

		void Float::Swap(f32& a, f32& b)
		{
			int iValA = _fval_to_ival(a);
			int iValB = _fval_to_ival(b);
			iValA ^= iValB;
			iValB ^= iValA;
			iValA ^= iValB;
			a = _ival_to_fval(iValA);
			b = _ival_to_fval(iValB);
		}

	#undef OPEN_FLOAT_OP	
	#undef C99				
	#undef _SIGNED_SHIFT			
	#undef _fval_to_ival
	#undef _ival_to_fval
	#undef SIGNMASK
	////////////////////////////////////////////////////////////////////////////////////////////////

}	// namespace dream

#endif // !__DreMath_H__
