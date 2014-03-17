#ifndef __LINE3_H__
#define __LINE3_H__

#include "DreMathDeclaration.h"

#include "Vector3.h"

namespace dream
{

	class Line3
	{
	public:
	//构造函数
		Line3() : start_( MIN_F32, MIN_F32, MIN_F32 ), end_( MAX_F32, MAX_F32, MAX_F32 )
		{
			//留空
		}

		Line3( const Vector3& start, const Vector3& end ) : start_( start ), end_( end )
		{
			//留空
		}

	//设置内容
		void Set( const Vector3& start, const Vector3& end )
		{
			start_ = start; end_ = end;
		}

		void SetStart( const Vector3& start )
		{
			start_ = start;
		}

		void SetEnd( const Vector3& end )
		{
			end_ = end;
		}

	//标准操作
		inline bool operator == ( const Line3& l ) const
		{
			return start_ == l.start_ && end_ == l.end_;
		}

		inline bool operator != ( const Line3& l ) const
		{
			return start_ != l.start_ || end_ != l.end_;
		}

		inline Line3 operator + ( const Vector3& v ) const
		{
			return Line3( start_ + v, end_ + v);
		}

		inline Line3 operator += ( const Vector3& v )
		{
			start_ += v;
			end_ += v;
			return *this;
		}

		inline Line3 operator - ( const Vector3& v ) const
		{
			return Line3( start_ - v, end_ - v);
		}

		inline Line3 operator -= ( const Vector3& v )
		{
			start_ -= v;
			end_ -= v;
			return *this;
		}

	//基本操作
		inline Vector3 getCenter() const
		{
			return ( end_ + start_ ) / 2;
		}

		inline f32 GetLength() const
		{
			return Distance( start_, end_ );
		}

		// 返回标准化向量
		inline Vector3 GetVector() const
		{
			Vector3 temp = start_ - end_;
			temp.Normalize();
			return temp;;
		}

	//包含检测
		bool PointContain( const Vector3& v ) const
		{
			Line3 t1( start_, v ), t2( v, end_ );

			return t1.GetVector() == t2.GetVector();
		}

		Vector3 start_, end_;
	};	// end class Line3

}	// end namespace dream

#endif	// end __LINE3_H__