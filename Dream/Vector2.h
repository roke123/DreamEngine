#ifndef __VECTOR2_H__
#define __VECTOR2_H__

namespace dream
{

	class Vector2
	{
	public:
	//���캯��
		Vector2() : x_(0.0f), y_(0.0f)
		{
			//����
		}

		Vector2( f32 x, f32 y ) : x_(x), y_(y)
		{
			//����
		}

	//��׼�������
		//����operator ==
		inline bool operator == ( const Vector2& a )
		{
			return Equal( x_, a.x_) && Equal( y_, a.y_ );
		}

		//����operator !=
		inline bool operator != ( const Vector2& a )
		{
			return ! this->operator == ( a );
		}

		Vector2 operator - () const
		{
			return Vector2( -x_, -y_ );
		}

		Vector2 operator + ( const Vector2& a ) const
		{
			return Vector2( x_ + a.x_, y_ + a.y_ );
		}

		Vector2 operator += ( const Vector2& a )
		{
			x_ += a.x_, y_ += a.y_;

			return *this;
		}

		Vector2 operator - ( const Vector2& a ) const
		{
			return Vector2( x_ - a.x_, y_ - a.y_ );
		}

		Vector2 operator -= ( const Vector2& a ) 
		{
			x_ -= a.x_, y_ -= a.y_;

			return *this;
		}

		Vector2 operator * ( f32 a ) const
		{
			return Vector2( x_ * a, y_ * a );
		}

		Vector2 operator *= ( f32 a )
		{
			x_ *= a; y_ *= a;

			return *this;
		}

		Vector2 operator * ( const Matrix3x2& m ) const;

		Vector2 operator *= ( const Matrix3x2& m );

		Vector2 operator / ( f32 a ) const
		{
			f32 oneOverA = 1.0f / a;

			return Vector2( x_ * oneOverA, y_ * oneOverA );
		}

		Vector2 operator /= ( f32 a )
		{
			f32 oneOverA = 1.0f / a;
			x_ *= oneOverA, y_ *= oneOverA;

			return *this;
		}

		void Set( f32 x, f32 y )
		{
			x_ = x, y_ = y;
		}

	//��������
		//����
		inline void Zero() { x_ = y_ = 0.0f; }
			
		//��׼��
		inline void Normalize() 
		{
			f32 magSp = x_*x_ + y_*y_;

			if( magSp > 0.0f )	//����������
			{
				f32 oneOverMag = 1.0f / magSp;

				x_ *= oneOverMag;
				y_ *= oneOverMag;
			}
		}

		inline f32 Length()
		{
			return Sqrt( x_*x_ + y_*y_ );
		}

		inline f32 GetLengthPow2()
		{
			return x_*x_ + y_*y_;
		}

		f32 x_, y_, z_;
	};

	//�ǳ�Ա����
	inline f32 Dot( const Vector2& l, const Vector2& r )
	{
		return l.x_ * r.x_ + l.y_ * r.y_;
	}

	inline f32 Distance( const Vector2& l, const Vector2& r )
	{
		f32 dx = l.x_ - r.x_;
		f32 dy = l.y_ - r.y_;

		return Sqrt( dx*dx + dy*dy );
	}

	extern const Vector2 kZeroVector2;

}	// end namespace dream

#endif	// end of __VECTOR2_H__