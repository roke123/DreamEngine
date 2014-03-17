#ifndef __DEGREE_H__
#define __DEGREE_H__

#include "DreMathDeclaration.h"

#include "DreMath.h"

namespace dream
{
	/** �Ƕ� */
	class Degree
	{
	public:
		/** ���캯�� */
		explicit Degree(f32 value) : mValue(value) { /** ���� */ }

		/** ����Radin��Degree��ת�� */
		explicit Degree(const Radian& rad);

		/** ��ֵ���� */
		Degree& operator = ( const Degree& r ) { mValue = r.mValue; return *this; }

		f32 GetValue() const { return mValue; }
		f32 GetValueUnit() const 
		{
			f32 value = 0.0f;
			if(Float::GreaterThanZero(mValue))
			{
				value = mValue - (int)(mValue / 360.0f) * 360.0f;
			}
			else
			{
				value = mValue - ((int)(mValue / 360.0f) + 1) * 360.0f;
			}
			return value;
		}

		/** �ӷ����� */
		const Degree& operator + () const { return *this; }
		Degree operator + ( const Degree& r ) const { return Degree ( mValue + r.mValue ); }
		Degree& operator += ( const Degree& r ) { mValue += r.mValue; return *this; }
		/** �������� */
		Degree operator - () const { return Degree(-mValue); }
		Degree operator - ( const Degree& r ) const { return Degree ( mValue - r.mValue ); }
		Degree& operator -= ( const Degree& r ) { mValue -= r.mValue; return *this; }
		/** �˷����� */
		Degree operator * ( f32 value ) const { return Degree ( mValue * value ); }
		Degree& operator *= ( f32 value ) { mValue *= value; return *this; }
		/** �������� */
		Degree operator / ( f32 value ) const { return Degree ( mValue / value ); }
		Degree& operator /= ( f32 value ) { mValue /= value; return *this; }

		/** �Ƚ����� */
		bool operator <  ( const Degree& r ) const { return mValue <  r.mValue; }
		bool operator <= ( const Degree& r ) const { return mValue <= r.mValue; }
		bool operator == ( const Degree& r ) const { return mValue == r.mValue; }
		bool operator != ( const Degree& r ) const { return mValue != r.mValue; }
		bool operator >= ( const Degree& r ) const { return mValue >= r.mValue; }
		bool operator >  ( const Degree& r ) const { return mValue >  r.mValue; }

		/** ���滯����ΧΪ0��~ 360�� */
		void Normalize()
		{
			if(Float::GreaterThanZero(mValue))
			{
				mValue = mValue - (int)(mValue / 360.0f) * 360.0f;
			}
			else
			{
				mValue = mValue - ((int)(mValue / 360.0f) + 1) * 360.0f;
			}
		}

	private:
		f32 mValue;
	};	// end class Degree

	/** ���� */
	class Radian
	{
	public:
		/** ���캯�� */
		explicit Radian(f32 value) : mValue(value) { /** ���� */ }

		/** ����Radin��Degree��ת�� */
		explicit Radian(const Degree& rad)
		{
			mValue = rad.GetValue() * Math::DEGTORAD_F;
		}

		/** ��ֵ���� */
		Radian& operator = ( const Radian& r ) { mValue = r.mValue; return *this; }

		f32 GetValue() const { return mValue; }
		f32 GetValueUnit() const 
		{
			f32 value = 0.0f;
			if(Float::GreaterThanZero(mValue))
			{
				value = mValue - (int)(mValue / 360.0f) * 360.0f;
			}
			else
			{
				value = mValue - ((int)(mValue / 360.0f) + 1) * 360.0f;
			}
			return value;
		}

		/** �ӷ����� */
		const Radian& operator + () const { return *this; }
		Radian operator + ( const Radian& r ) const { return Radian ( mValue + r.mValue ); }
		Radian& operator += ( const Radian& r ) { mValue += r.mValue; return *this; }
		/** �������� */
		Radian operator - () const { return Radian(-mValue); }
		Radian operator - ( const Radian& r ) const { return Radian ( mValue - r.mValue ); }
		Radian& operator -= ( const Radian& r ) { mValue -= r.mValue; return *this; }
		/** �˷����� */
		Radian operator * ( f32 value ) const { return Radian ( mValue * value ); }
		Radian& operator *= ( f32 value ) { mValue *= value; return *this; }
		/** �������� */
		Radian operator / ( f32 value ) const { return Radian ( mValue / value ); }
		Radian& operator /= ( f32 value ) { mValue /= value; return *this; }

		/** �Ƚ����� */
		bool operator <  ( const Radian& r ) const { return mValue <  r.mValue; }
		bool operator <= ( const Radian& r ) const { return mValue <= r.mValue; }
		bool operator == ( const Radian& r ) const { return mValue == r.mValue; }
		bool operator != ( const Radian& r ) const { return mValue != r.mValue; }
		bool operator >= ( const Radian& r ) const { return mValue >= r.mValue; }
		bool operator >  ( const Radian& r ) const { return mValue >  r.mValue; }

		/** ���滯����ΧΪ0~ 2PI */
		void Normalize()
		{
			if(Float::GreaterThanZero(mValue))
			{
				mValue = mValue - (int)(mValue / Math::DOUBLE_PI_F) * Math::DOUBLE_PI_F;
			}
			else
			{
				mValue = mValue - ((int)(mValue / Math::DOUBLE_PI_F) + 1) * Math::DOUBLE_PI_F;
			}
		}

	private:
		f32 mValue;
	};	// end class Degree

}	// end namespace dream

#endif // end __DEGREE_H__
