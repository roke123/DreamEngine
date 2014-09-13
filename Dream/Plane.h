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
	//构造函数
		//默认为xz平面
		Plane() : n_( 0, 1, 0 ), d_(0)
		{
			//留空
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
			//判断e1,e2是否共线
			Assert( Float::IsEqual( e1.mX / e2.mX, e1.mY / e2.mY ) )

			//计算法向量和d
			n_ = Cross( e1, e2 );
			d_ = Dot( n_, n1 );

			//正则化
			f32 oneOverLength = 1.0f / n_.Length();

			n_ *= oneOverLength;
			d_ *= oneOverLength;
		}

	//设置内容
		inline void Set( const Vector3& n, f32 d )
		{
			f32 oneOverLength = 1.0f / n_.Length();

			n_ = n * oneOverLength;
			d_ = d * oneOverLength;
		}

		inline void Set( const Vector3& n1, const Vector3& n2, const Vector3& n3 )
		{
			Vector3 e1 = n1 - n2, e2 = n1 - n3;
			//判断e1,e2是否共线
			Assert( Float::IsEqual( e1.mX / e2.mX, e1.mY / e2.mY ) )

			//计算法向量和d
			n_ = Cross( e1, e2 );
			d_ = Dot( n_, n1 );

			//正则化
			f32 oneOverLength = 1.0f / n_.Length();

			n_ *= oneOverLength;
			d_ *= oneOverLength;
		}

		inline void SetD( f32 d ) { d_ = d; }

	//标准操作
		inline bool operator == ( const Plane& p ) const { return n_ == p.n_ && Float::IsEqual( d_, p.d_ ); }

		inline bool operator != ( const Plane& p ) const { return !Float::IsEqual( d_, p.d_ ) || n_ != p.n_; }

		inline Plane operator + ( f32 d ) const { return Plane( n_, d_ + d ); }

		inline Plane operator += ( f32 d ){ d_ += d; return *this; }

		inline Plane operator - ( f32 d ) const { return Plane( n_, d_ - d ); }

		inline Plane operator -= ( f32 d ) { d_ -= d; return *this; }

	// 基本操作
		// 取得平面内的一点
		inline Vector3 GetPointInPlane() const
		{
			return n_ * d_;
		}

		// 取得点到平面的距离
		inline f32 GetDistance( const Vector3& v ) const
		{
			return Dot( v, n_ ) - d_;
		}

	//包含测试
		// 点是否在平面内
		// 可选param - returnState, 点在平面前返回1,平面后返回-1,与平面相交返回0
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

		// 检测射线与平面碰撞
		bool RayIntersect( const Line3& l, Vector3 * returnNormal = NULL )
		{
			Vector3 v = l.GetVector();

			// 直线上某点可表示为 : start + t * v ( 0.0f < t < 1.0f ), 假设
			// 该点在平面上，可得 ( start + t * v ) * n_ = d_ =>
			// t = ( d_ - start * n_ ) / ( v * n_ );

			f32 t = ( d_ - Dot( l.start_, n_ ) ) / Dot( v, n_ ); 
				
			// t不在直线上
			if( t < 0.0f || t > 1.0f )
				return false;

			// t在直线上
			if( returnNormal != NULL ) *returnNormal = l.start_ + v * t;
			return true;
		}

		Vector3 n_;

		f32 d_;
	};	// end class Plane

}	// end namespace dream

#endif	// end __PLANE_H__