#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "DreMathDeclaration.h"

namespace dream
{

	class Vector3
	{
	public:
		static const Vector3 ZeroVector;
	public:
	//���캯��
		Vector3() : mX(0.0f), mY(0.0f), mZ(0.0f)
		{
			//����
		}

		Vector3( f32 x, f32 y, f32 z ) : mX(x), mY(y), mZ(z)
		{
			//����
		}

	//��������
		//����
		inline void Zero() { mX = mY = mZ = 0.0f; }
			
		//��׼��
		inline void Normalize() 
		{
			f32 magSp = mX*mX + mY*mY + mZ*mZ;

			if( magSp > 0.0f )	//����������
			{
				f32 oneOverMag = 1.0f / magSp;

				mX *= oneOverMag;
				mY *= oneOverMag;
				mZ *= oneOverMag;
			}
		}

		inline f32 Length()
		{
			return Sqrt( mX*mX + mY*mY + mZ*mZ );
		}

		inline f32 GetLengthPow2()
		{
			return mX*mX + mY*mY + mZ*mZ;
		}

		void Set( f32 x, f32 y, f32 z )
		{
			mX = x; mY = y; mZ = z;
		}

	//��׼�������
		//����operator ==
		inline bool operator == ( const Vector3& a ) const
		{
			return Equal( mX, a.mX) && Equal( mY, a.mY ) && Equal( mZ, a.mZ );
		}

		//����operator !=
		inline bool operator != ( const Vector3& a ) const
		{
			return ! this->operator == ( a );
		}

		Vector3 operator * ( const Matrix4& m ) const;

		Vector3 operator *= ( const Matrix4& m );

		Vector3 operator - () const
		{
			return Vector3( -mX, -mY, -mZ );
		}

		Vector3 operator + ( const Vector3& a ) const
		{
			return Vector3( mX + a.mX, mY + a.mY, mZ + a.mZ );
		}

		Vector3 operator += ( const Vector3& a )
		{
			mX += a.mX, mY += a.mY, mZ += a.mZ;

			return *this;
		}

		Vector3 operator - ( const Vector3& a ) const
		{
			return Vector3( mX - a.mX, mY - a.mY, mZ - a.mZ );
		}

		Vector3 operator -= ( const Vector3& a ) 
		{
			mX -= a.mX, mY -= a.mY, mZ -= a.mZ;

			return *this;
		}

		Vector3 operator * ( f32 a ) const
		{
			return Vector3( mX * a, mY * a, mZ * a );
		}

		Vector3 operator *= ( f32 a )
		{
			mX *= a, mY *= a, mZ *= a;

			return *this;
		}

		Vector3 operator / ( f32 a ) const
		{
			f32 oneOverA = 1.0f / a;

			return Vector3( mX * oneOverA, mY * oneOverA, mZ * oneOverA );
		}

		Vector3 operator /= ( f32 a )
		{
			f32 oneOverA = 1.0f / a;
			mX *= oneOverA, mY *= oneOverA, mZ *= oneOverA;

			return *this;
		}

		f32 mX, mY, mZ;
	};

	//�ǳ�Ա����
	inline f32 Dot( const Vector3& l, const Vector3& r )
	{
		return l.mX * r.mX + l.mY * r.mY + l.mZ * r.mZ;
	}

	inline Vector3 Cross( const Vector3& l, const Vector3& r )
	{
		return Vector3( l.mY*r.mZ - l.mZ*r.mY,
			l.mX*r.mZ - l.mZ*r.mX,
			l.mX*r.mY - l.mY*r.mX );
	}

	inline f32 Distance( const Vector3& l, const Vector3& r )
	{
		f32 dx = l.mX - r.mX;
		f32 dy = l.mY - r.mY;
		f32 dz = l.mZ - r.mZ;

		return Sqrt( dx*dx + dy*dy + dz*dz );
	}

}	// end namespace dream

#endif	// end __VECTOR3_H__