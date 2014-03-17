#ifndef __MATRIX3X2_H__
#define __MATRIX3X2_H__

#include "DreMathDeclaration.h"

#include "Vector2.h"

namespace dream
{

		//2D变换矩阵
		class Matrix3x2
		{
		public:
		//标准操作
			inline void Identity()
			{
				m_[0][0] = 1.0f; m_[0][1] = 0.0f; 
				m_[1][0] = 0.0f; m_[1][1] = 1.0f; 
				m_[2][0] = 0.0f; m_[2][1] = 0.0f; 
			}

			inline void ZeroTranslation()
			{
				m_[2][0] = m_[2][1] = 0.0f;
			}

			//计算左上2x2行列式
			inline f32 Determinant() const
			{
				return m_[0][0] * m_[1][1] - m_[0][1] * m_[1][0];
			}

			bool Inverse( Matrix3x2 * m ) const
			{
				f32 det = Determinant();
				
				//无逆矩阵
				if( Abs(det) > 0.000001f )
					return false;

				f32 oneOverDet = 1.0f / det;

				m->m_[0][0] = m_[1][1] * oneOverDet; 
				m->m_[0][1] = -m_[1][0] * oneOverDet;  

				m->m_[1][0] = -m_[0][1] * oneOverDet; 
				m->m_[1][1] = m_[0][0] * oneOverDet;  

				m->m_[2][0] = -(m_[2][0]*m->m_[0][0] + m_[2][1]*m->m_[1][0]); 
				m->m_[1][1] = -(m_[2][0]*m->m_[0][1] + m_[2][1]*m->m_[1][1]); 

				return true;
			}

		//标准操作数
			Matrix3x2 operator * ( f32 a ) const
			{
				Matrix3x2 temp;

				temp.m_[0][0] = m_[0][0] * a;
				temp.m_[0][1] = m_[0][1] * a;
				temp.m_[1][0] = m_[1][0] * a;
				temp.m_[1][1] = m_[1][1] * a;

				return temp;
			}

			Matrix3x2 operator *= ( f32 a )
			{
				m_[0][0] *= a;
				m_[0][1] *= a;
				m_[1][0] *= a;
				m_[1][1] *= a;

				return *this;
			}

			Matrix3x2 operator * ( const Matrix3x2& a ) const 
			{
				Matrix3x2 temp;

				temp.m_[0][0] = m_[0][0]*a.m_[0][0] + m_[0][1]*a.m_[1][0];
				temp.m_[0][1] = m_[0][0]*a.m_[0][1] + m_[0][1]*a.m_[1][1];
				temp.m_[1][0] = m_[1][0]*a.m_[0][0] + m_[1][1]*a.m_[1][0];
				temp.m_[1][1] = m_[1][0]*a.m_[0][1] + m_[1][1]*a.m_[1][1];
				temp.m_[2][0] = m_[2][0]*a.m_[0][0] + m_[2][1]*a.m_[1][0] + a.m_[2][0];
				temp.m_[2][1] = m_[2][0]*a.m_[0][1] + m_[2][1]*a.m_[1][1] + a.m_[2][1];
			}

			Matrix3x2 operator *= ( const Matrix3x2& a )
			{
				Matrix3x2 temp = *this;

				m_[0][0] = temp.m_[0][0]*a.m_[0][0] + temp.m_[0][1]*a.m_[1][0];
				m_[0][1] = temp.m_[0][0]*a.m_[0][1] + temp.m_[0][1]*a.m_[1][1];
				m_[1][0] = temp.m_[1][0]*a.m_[0][0] + temp.m_[1][1]*a.m_[1][0];
				m_[1][1] = temp.m_[1][0]*a.m_[0][1] + temp.m_[1][1]*a.m_[1][1];
				m_[2][0] = temp.m_[2][0]*a.m_[0][0] + temp.m_[2][1]*a.m_[1][0] + a.m_[2][0];
				m_[2][1] = temp.m_[2][0]*a.m_[0][1] + temp.m_[2][1]*a.m_[1][1] + a.m_[2][1];

				return *this;
			}

			Vector2 operator * ( const Vector2& v ) const;

			Matrix3x2 operator + ( const Matrix3x2& a ) const
			{
				Matrix3x2 temp;

				temp.m_[0][0] = m_[0][0] + a.m_[0][0];
				temp.m_[0][1] = m_[0][1] + a.m_[0][1];
				temp.m_[1][0] = m_[1][0] + a.m_[1][0];
				temp.m_[1][1] = m_[1][1] + a.m_[1][1];

				return temp;
			}

			Matrix3x2 operator += ( const Matrix3x2& a )
			{
				m_[0][0] += a.m_[0][0];
				m_[0][1] += a.m_[0][1];
				m_[1][0] += a.m_[1][0];
				m_[1][1] += a.m_[1][1];

				return *this;
			}

			bool operator == ( const Matrix3x2& a ) const
			{
				return Equal( m_[0][0], a.m_[0][0] ) &&
					Equal( m_[0][1], a.m_[0][1] ) &&
					Equal( m_[1][0], a.m_[1][0] ) &&
					Equal( m_[1][1], a.m_[1][1] );
			}

			bool operator != ( const Matrix3x2& a )
			{
				return !this->operator==( a );
			}

		//构造缩放矩阵
			//按坐标轴缩放
			inline void SetScale( f32 x, f32 y )
			{
				m_[0][0] = x;
				m_[1][1] = y;

				m_[2][0] = m_[2][1] = m_[2][2] = 0.0f;
			}

			//按任意轴缩放
			void SetScaleByAxis( const Vector2& axis, f32 x, f32 y );

		//构造切变矩阵
			//沿X轴切变
			inline void SetShearX( float s )
			{
				m_[0][0] = 1.0f, m_[0][1] = s;
				m_[1][0] = 0.0f, m_[1][1] = 1.0f;
				
				m_[2][0] = m_[2][1] = 0.0f;
			}

			inline void SetShearY( float s )
			{
				m_[0][0] = 1.0f, m_[0][1] = 0.0f;
				m_[1][0] = s, m_[1][1] = 1.0f;
				
				m_[2][0] = m_[2][1] = 0.0f;
			}

		// 构造反射矩阵
			// 按任意过原点的轴反射，反射轴垂直于axis
			void SetReflect( const Vector2& axis )
			{
				//检查是否单位向量
				Assert( Abs( Dot( axis, axis ) ) - 1.0f < 0.01f );

				f32 ax = -2.0f * axis.x_;
				f32 ay = -2.0f * axis.y_;

				m_[0][0] = 1.0f + ax * axis.x_;
				m_[1][1] = 1.0f + ay * axis.y_;

				m_[1][0] = m_[0][1] = ax * axis.y_;

				m_[2][0] = m_[2][1]= 0.0f;
			}

			void SetReflectX()
			{
				m_[0][0] = -1.0f;
				m_[1][1] = 1.0f;
				m_[0][1] = m_[1][0] = 0.0f;

				m_[2][0] = m_[2][1]= 0.0f;
			}

			void SetReflectY()
			{
				m_[1][1] = -1.0f;
				m_[0][0] = 1.0f;
				m_[0][1] = m_[1][0] = 0.0f;

				m_[2][0] = m_[2][1]= 0.0f;
			}


		//构造平移矩阵
			inline void SetTranslation( f32 x, f32 y, f32 z )
			{
				m_[0][0] = m_[0][1] = 0.0f;
				m_[1][0] = m_[1][1] = 0.0f;

				m_[2][0] = x;
				m_[2][1] = y;
			}

		// 构造旋转矩阵，使用弧度制
			// 绕原点旋转
			void SetRotationByAxis( f32 radiens )
			{
				f32 s = Sin(radiens);
				f32 c = Cos(radiens);

				m_[0][0] = c; m_[0][1] = s; 
				m_[1][0] = -s; m_[1][1] = c;

				m_[2][0] = m_[2][1]= 0.0f;
			}

			f32 m_[3][2];
		};	// end class Matrix4x3

}	// end namespace dream

#endif	// end __MATRIX3X2_H__