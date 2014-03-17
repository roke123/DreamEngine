#include "Matrix4.h"

#include "Quaternion.h"
#include "EulerAngles.h"

namespace dream
{

	Matrix4 Matrix4::SetScaleByAxis( const Vector3& axis, f32 x, f32 y, f32 z )
	{
		Matrix4 ret;

		f32 xSubOneMulAxisX = ( x - 1 ) * axis.mX;
		ret.mM[0][0] = 1 + xSubOneMulAxisX * axis.mX;
		ret.mM[0][1] = xSubOneMulAxisX * axis.mY;
		ret.mM[0][2] = xSubOneMulAxisX * axis.mZ;

		f32 ySubOneMulAxisY = ( y - 1 ) * axis.mY;
		ret.mM[1][0] = ySubOneMulAxisY * axis.mX;
		ret.mM[1][1] = 1 + ySubOneMulAxisY * axis.mY;
		ret.mM[1][2] = ySubOneMulAxisY * axis.mZ;

		f32 zSubOneMulAxisZ = ( z - 1 ) * axis.mZ;
		ret.mM[2][0] = zSubOneMulAxisZ * axis.mX;
		ret.mM[2][1] = zSubOneMulAxisZ * axis.mY;
		ret.mM[2][2] = 1 + zSubOneMulAxisZ * axis.mZ;
				
		ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;

		return ret;
	}

	Matrix4 Matrix4::SetRotationByAxis( const Vector3& axis, f32 radiens )
	{
		Matrix4 ret;

		f32 sinR = Sin( radiens );
		f32 cosR = Cos( radiens );
		f32 oneSubSinR = 1.0f - sinR;
		f32 oneSubCosR = 1.0f - cosR;

		f32 xMulOneSubCosR = axis.mX * oneSubCosR;
		ret.mM[0][0] = axis.mX*xMulOneSubCosR + cosR;
		ret.mM[0][1] = axis.mY*xMulOneSubCosR + axis.mZ*sinR;
		ret.mM[0][2] = axis.mZ*xMulOneSubCosR - axis.mY*sinR;
			
		f32 yMulOneSubCosR = axis.mY * oneSubCosR;
		ret.mM[1][0] = axis.mX*yMulOneSubCosR - axis.mZ*sinR;
		ret.mM[1][1] = axis.mY*yMulOneSubCosR + cosR;
		ret.mM[1][2] = axis.mZ*yMulOneSubCosR + axis.mX*sinR;
			
		f32 zMulOneSubCosR = axis.mZ * oneSubCosR;
		ret.mM[2][0] = axis.mX*zMulOneSubCosR + axis.mY*sinR; 
		ret.mM[2][1] = axis.mY*zMulOneSubCosR - axis.mX*sinR; 
		ret.mM[2][2] = axis.mZ*zMulOneSubCosR + cosR;
			
		ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;

		return ret;
	}

	Matrix4 Matrix4::SetCameraLookAtMatrixLH(
				const Vector3& position,
				const Vector3& target,
				const Vector3& upVector)
	{
		Matrix4 ret;

		Vector3 axisZ = target - position;
		axisZ.Normalize();

		Vector3 axisX = Cross( upVector, axisZ );
		axisX.Normalize();

		Vector3 axisY = Cross( axisZ, axisX );

		ret.mM[0][0] = axisX.mX;
		ret.mM[0][1] = axisY.mX;
		ret.mM[0][2] = axisZ.mX;

		ret.mM[1][0] = axisX.mY;
		ret.mM[1][1] = axisY.mY;
		ret.mM[1][2] = axisZ.mY;
			
		ret.mM[2][0] = axisX.mZ;
		ret.mM[2][1] = axisY.mZ;
		ret.mM[2][2] = axisZ.mZ;

		ret.mM[3][0] = Dot( axisX, position );
		ret.mM[3][1] = Dot( axisY, position );
		ret.mM[3][2] = Dot( axisZ, position );

		ret.mM[3][3] = 1.0f;
		ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;

		return ret;
	}

	Matrix4 Matrix4::SetCameraLookAtMatrixRH(
			const Vector3& position,
			const Vector3& target,
			const Vector3& upVector)
	{
		Matrix4 ret;

		Vector3 axisZ = position - target;
		axisZ.Normalize();

		Vector3 axisX = Cross( upVector, axisZ );
		axisX.Normalize();

		Vector3 axisY = Cross( axisZ, axisX );

		ret.mM[0][0] = axisX.mX;
		ret.mM[0][1] = axisY.mX;
		ret.mM[0][2] = axisZ.mX;

		ret.mM[1][0] = axisX.mY;
		ret.mM[1][1] = axisY.mY;
		ret.mM[1][2] = axisZ.mY;
			
		ret.mM[2][0] = axisX.mZ;
		ret.mM[2][1] = axisY.mZ;
		ret.mM[2][2] = axisZ.mZ;

		ret.mM[3][0] = Dot( axisX, position );
		ret.mM[3][1] = Dot( axisY, position );
		ret.mM[3][2] = Dot( axisZ, position );

		ret.mM[3][3] = 1.0f;
		ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;

		return ret;
	}

	//param - position		: 相机坐标
	//param - orientation	: 看着的目标点
	//param - upVector		: 垂直向量
	Matrix4 Matrix4::SetCameraOrientationMatrixLH(
			const Vector3& position,
			const Vector3& orientation,
			const Vector3& upVector)
	{
		Matrix4 ret;

		Vector3 axisX = Cross( upVector, orientation );
		axisX.Normalize();

		Vector3 axisY = Cross( orientation, axisX );

		ret.mM[0][0] = axisX.mX;
		ret.mM[0][1] = axisY.mX;
		ret.mM[0][2] = orientation.mX;

		ret.mM[1][0] = axisX.mY;
		ret.mM[1][1] = axisY.mY;
		ret.mM[1][2] = orientation.mY;
			
		ret.mM[2][0] = axisX.mZ;
		ret.mM[2][1] = axisY.mZ;
		ret.mM[2][2] = orientation.mZ;

		ret.mM[3][0] = Dot( axisX, position );
		ret.mM[3][1] = Dot( axisY, position );
		ret.mM[3][2] = Dot( orientation, position );

		ret.mM[3][3] = 1.0f;
		ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;

		return ret;
	}

	Matrix4 Matrix4::SetCameraOrientationMatrixRH(
			const Vector3& position,
			const Vector3& orientation,
			const Vector3& upVector)
	{
		Matrix4 ret;

		Vector3 axisX = Cross( upVector, orientation );
		axisX.Normalize();

		Vector3 axisY = Cross( orientation, axisX );

		ret.mM[0][0] = axisX.mX;
		ret.mM[0][1] = axisY.mX;
		ret.mM[0][2] = orientation.mX;

		ret.mM[1][0] = axisX.mY;
		ret.mM[1][1] = axisY.mY;
		ret.mM[1][2] = orientation.mY;
			
		ret.mM[2][0] = axisX.mZ;
		ret.mM[2][1] = axisY.mZ;
		ret.mM[2][2] = orientation.mZ;

		ret.mM[3][0] = Dot( axisX, position );
		ret.mM[3][1] = Dot( axisY, position );
		ret.mM[3][2] = Dot( orientation, position );

		ret.mM[3][3] = 1.0f;
		ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;

		return ret;
	}

	EulerAngles Matrix4::Matrix4ToEulerAngles() const
	{
		EulerAngles temp;

		f32 sp = -mM[2][1];

		if( Abs(sp) > 9.99999f )
		{
			//向正下方或向正上方看
			temp.pitch_ = HALF_PI_F * sp;
			temp.heading_ = ATan2( -mM[1][2], mM[0][0] );
			temp.bank_ = 0.0f;
		}
		else
		{
			temp.heading_ = ATan2( mM[2][0], mM[2][2] );
			temp.pitch_ = asin( sp );
			temp.bank_ = ATan2( mM[0][1], mM[1][1] );
		}

		return temp;
	}

	Matrix4 Matrix4::SetMatrixForNode(const Vector3& position, const Vector3& scale,
		const Quaternion& orientation)
	{
		Matrix4 ret = orientation.QuaternionToMatrix4();

		// rotation -> scale and translate
		ret.mM[0][0] *= scale.mX; ret.mM[0][1] *= scale.mY; ret.mM[0][2] *= scale.mZ; ret.mM[3][0] = position.mX;
		ret.mM[1][0] *= scale.mX; ret.mM[1][1] *= scale.mY;	ret.mM[1][2] *= scale.mZ; ret.mM[3][1] = position.mX;
		ret.mM[2][0] *= scale.mX; ret.mM[2][1] *= scale.mY;	ret.mM[2][2] *= scale.mZ; ret.mM[3][2] = position.mX;

		// no project
		ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f; ret.mM[3][3] = 1.0f;

		return ret;
	}

	Quaternion Matrix4::Matrix4ToQuaternion() const
	{
		Quaternion temp;

		const f32 diag = mM[0][0] + mM[1][1] + mM[2][2] + 1.0f;

		if( diag > 0.0f )
		{
			const f32 scale = Sqrt(diag) * 2.0f; // get scale from diagonal

			// TODO: speed this up
			temp.mX = ( mM[2][1] - mM[1][2] ) / scale;
			temp.mY = ( mM[0][2] - mM[2][0] ) / scale;
			temp.mZ = ( mM[1][0] - mM[0][1] ) / scale;
			temp.mW = 0.25f * scale;
		}
		else
		{
			if ( mM[0][0] > mM[1][1] && mM[0][0] > mM[2][2] )
			{
				// 1st element of diag is greatest value
				// find scale according to 1st element, and double it
				const f32 scale = Sqrt( 1.0f + mM[0][0] - mM[1][1] - mM[2][2] ) * 2.0f;

				// TODO: speed this up
				temp.mX = 0.25f * scale;
				temp.mY = ( mM[0][1] + mM[1][0] ) / scale;
				temp.mZ = ( mM[2][0] + mM[0][2] ) / scale;
				temp.mW = ( mM[2][1] - mM[1][2] ) / scale;
			}
			else if ( mM[1][1] > mM[2][2] )
			{
				// 2nd element of diag is greatest value
				// find scale according to 2nd element, and double it
				const f32 scale = Sqrt( 1.0f + mM[1][1] - mM[0][0] - mM[2][2] ) * 2.0f;

				// TODO: speed this up
				temp.mX = ( mM[0][1] + mM[1][0] ) / scale;
				temp.mY = 0.25f * scale;
				temp.mZ = ( mM[1][2] + mM[2][1] ) / scale;
				temp.mW = ( mM[0][2] - mM[2][0] ) / scale;
			}
			else
			{
				// 3rd element of diag is greatest value
				// find scale according to 3rd element, and double it
				const f32 scale = sqrtf( 1.0f + mM[2][2] - mM[0][0] - mM[1][1] ) * 2.0f;

				// TODO: speed this up
				temp.mX = ( mM[0][2] + mM[2][0] ) / scale;
				temp.mY = ( mM[1][2] + mM[2][1] ) / scale;
				temp.mZ = 0.25f * scale;
				temp.mW = ( mM[1][0] - mM[0][1] ) / scale;
			}
		}

		//标准化修正误差
		temp.Normalize();
		return temp;
	}

	extern const Matrix4 IdentityMatrix = { 1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f };

}	// end namespace dream