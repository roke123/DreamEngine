#include "Vector2.h"

#include "Matrix3x2.h"

namespace dream
{

		Vector2 Vector2::operator * ( const Matrix3x2& m ) const
		{
			Vector2 temp;

			temp.x_ = x_ * m.m_[0][0] + y_ * m.m_[1][0] + m.m_[2][0];
			temp.y_ = x_ * m.m_[0][1] + y_ * m.m_[1][1] + m.m_[2][1];

			return temp;
		}

		Vector2 Vector2::operator *= ( const Matrix3x2& m )
		{
			Vector2 temp = *this;

			x_ = temp.x_ * m.m_[0][0] + temp.y_ * m.m_[1][0] + m.m_[2][0];
			y_ = temp.x_ * m.m_[0][1] + temp.y_ * m.m_[1][1] + m.m_[2][1];

			return *this;
		}

}	// end namespace dream