#include "Vector3.h"

#include "Matrix4.h"

namespace dream
{
	const Vector3 Vector3::ZeroVector = Vector3(0.0f, 0.0f, 0.0f);

	Vector3 Vector3::operator * ( const Matrix4& m ) const
	{
		Vector3 temp;

		temp.mX = mX*m.mM[0][0] + mY*m.mM[1][0] + mZ *m.mM[2][0] + m.mM[3][0];
		temp.mY = mX*m.mM[0][1] + mY*m.mM[1][1] + mZ *m.mM[2][1] + m.mM[3][1];
		temp.mZ = mX*m.mM[0][2] + mY*m.mM[1][2] + mZ *m.mM[2][2] + m.mM[3][2];

		return temp;
	}

	Vector3 Vector3::operator *= ( const Matrix4& m )
	{
		Vector3 temp;

		mX = temp.mX*m.mM[0][0] + temp.mY*m.mM[1][0] + temp.mZ *m.mM[2][0] + m.mM[3][0];
		mY = temp.mX*m.mM[0][1] + temp.mY*m.mM[1][1] + temp.mZ *m.mM[2][1] + m.mM[3][1];
		mZ = temp.mX*m.mM[0][2] + temp.mY*m.mM[1][2] + temp.mZ *m.mM[2][2] + m.mM[3][2];
		
		return *this;
	}

}	// end namespace dream