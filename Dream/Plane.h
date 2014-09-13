#ifndef __PLANE_H__
#define __PLANE_H__

#include "DreMathDeclaration.h"

#include "Line3.h"
#include "Vector3.h"

namespace dream
{

	class Plane
	{
	public:
	//���캯��
		//Ĭ��Ϊxzƽ��
		Plane() : n_( 0, 1, 0 ), d_(0)
		{
			//����
		}

		Plane( const Vector3& n, f32 d )
		{
			f32 oneOverLength = 1.0f / n_.Length();

			n_ = n * oneOverLength;
			d_ = d * oneOverLength;
		}

		Plane( const Vector3& n1, const Vector3& n2, const Vector3& n3 )
		{
			Vector3 e1 = n1 - n2, e2 = n1 - n3;
			//�ж�e1,e2�Ƿ���
			Assert( Float::IsEqual( e1.mX / e2.mX, e1.mY / e2.mY ) )

			//���㷨������d
			n_ = Cross( e1, e2 );
			d_ = Dot( n_, n1 );

			//����
			f32 oneOverLength = 1.0f / n_.Length();

			n_ *= oneOverLength;
			d_ *= oneOverLength;
		}

	//��������
		inline void Set( const Vector3& n, f32 d )
		{
			f32 oneOverLength = 1.0f / n_.Length();

			n_ = n * oneOverLength;
			d_ = d * oneOverLength;
		}

		inline void Set( const Vector3& n1, const Vector3& n2, const Vector3& n3 )
		{
			Vector3 e1 = n1 - n2, e2 = n1 - n3;
			//�ж�e1,e2�Ƿ���
			Assert( Float::IsEqual( e1.mX / e2.mX, e1.mY / e2.mY ) )

			//���㷨������d
			n_ = Cross( e1, e2 );
			d_ = Dot( n_, n1 );

			//����
			f32 oneOverLength = 1.0f / n_.Length();

			n_ *= oneOverLength;
			d_ *= oneOverLength;
		}

		inline void SetD( f32 d ) { d_ = d; }

	//��׼����
		inline bool operator == ( const Plane& p ) const { return n_ == p.n_ && Float::IsEqual( d_, p.d_ ); }

		inline bool operator != ( const Plane& p ) const { return !Float::IsEqual( d_, p.d_ ) || n_ != p.n_; }

		inline Plane operator + ( f32 d ) const { return Plane( n_, d_ + d ); }

		inline Plane operator += ( f32 d ){ d_ += d; return *this; }

		inline Plane operator - ( f32 d ) const { return Plane( n_, d_ - d ); }

		inline Plane operator -= ( f32 d ) { d_ -= d; return *this; }

	// ��������
		// ȡ��ƽ���ڵ�һ��
		inline Vector3 GetPointInPlane() const
		{
			return n_ * d_;
		}

		// ȡ�õ㵽ƽ��ľ���
		inline f32 GetDistance( const Vector3& v ) const
		{
			return Dot( v, n_ ) - d_;
		}

	//��������
		// ���Ƿ���ƽ����
		// ��ѡparam - returnState, ����ƽ��ǰ����1,ƽ��󷵻�-1,��ƽ���ཻ����0
		bool PointContain( const Vector3& v, int * returnState = NULL )
		{
			f32 det = Dot( v, n_ );

			if( det > d_ )
			{
				if( returnState != NULL ) *returnState = 1;
				return false;
			}

			if( det < d_ )
			{
				if( returnState != NULL ) *returnState = -1;
				return false;
			}

			if( returnState != NULL ) *returnState = 0;
			return true;
		}

		// ���������ƽ����ײ
		bool RayIntersect( const Line3& l, Vector3 * returnNormal = NULL )
		{
			Vector3 v = l.GetVector();

			// ֱ����ĳ��ɱ�ʾΪ : start + t * v ( 0.0f < t < 1.0f ), ����
			// �õ���ƽ���ϣ��ɵ� ( start + t * v ) * n_ = d_ =>
			// t = ( d_ - start * n_ ) / ( v * n_ );

			f32 t = ( d_ - Dot( l.start_, n_ ) ) / Dot( v, n_ ); 
				
			// t����ֱ����
			if( t < 0.0f || t > 1.0f )
				return false;

			// t��ֱ����
			if( returnNormal != NULL ) *returnNormal = l.start_ + v * t;
			return true;
		}

		Vector3 n_;

		f32 d_;
	};	// end class Plane

}	// end namespace dream

#endif	// end __PLANE_H__