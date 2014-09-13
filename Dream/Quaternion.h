#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "DreMathDeclaration.h"

#include "Matrix4.h"

namespace dream
{

	class Quaternion
	{
	public:
		static const Quaternion UnitQuaternion;
	public:
	//构造函数
		Quaternion() : mX(0.0f), mY(0.0f), mZ(0.0f), mW(1.0f)
		{
			//留空
		}

		Quaternion(f32 x, f32 y, f32 z, f32 w = 1.0f) :
			mX(x), mY(y), mZ(z), mW(w)
		{
			//留空
		}

	//标准操作
		bool operator == (const Quaternion& a) const
		{
			return Float::IsEqual(mX, a.mX) &&
				Float::IsEqual(mY, a.mY) &&
				Float::IsEqual(mZ, a.mZ) &&
				Float::IsEqual(mW, a.mW);
		}
			
		bool operator != (const Quaternion& a) const
		{
			return this->operator == (a);
		}

	//置零
		inline void Identity() { mW = 1.0f, mX = mY = mZ = 0.0f; }

	//构造旋转四元数
		inline void SetToRotateX(f32 theta)
		{
			//计算半角
			f32 thetaOver2 = theta * 0.5f;

			mW = Cos(thetaOver2);
			mX = Sin(thetaOver2);
			mY = 0.0f;
			mZ = 0.0f;
		}

		inline void SetToRotateY(f32 theta)
		{
			f32 thetaOver2 = theta * 0.5f;

			mW = Cos(thetaOver2);
			mX = 0.0f;
			mY = Sin(thetaOver2);
			mZ = 0.0f;
		}

		inline void SetToRotateZ(f32 theta)
		{
			f32 thetaOver2 = theta * 0.5f;

			mW = Cos(thetaOver2);
			mX = 0.0f;
			mY = 0.0f;
			mZ = Sin(thetaOver2);
		}

		//按旋转轴设置四元数
		void SetToRotateAxis(const Vector3& axis, f32 theta);

	//四元数共轭
		Quaternion Conjugate() const
		{
			return Quaternion(-mX, -mY, -mZ, mW);
		}

	//正则化
		inline void Normalize()
		{
			//防止误差扩大使用精度高的Sqrt而不是FastSqrt;
			f32 mag = Sqrt(mW*mW + mX*mX + mY*mY + mZ*mZ);

			if(mag > 0.0f)
			{
				//正则化
				f32 oneOverMag = 1.0f / mag;
				mW *= oneOverMag;
				mX *= oneOverMag;
				mY *= oneOverMag;
				mZ *= oneOverMag;
			}
			else
			{
				//误差增大
				Assert(false);

				//release版本中转换为单位四元数
				Identity();
			}
		}

	//转换四元数
		//返回旋转角
		inline f32 GetRotationAngle() const
		{
			f32 theraOver2 = ACos(mW);

			return theraOver2 * 2.0f;
		}

		//返回旋转轴
		Vector3 GetRotationAxis() const;

		//转换欧拉角
		EulerAngles QuaternionToEularAngles() const;

		//转换到4x3矩阵
		Matrix4 QuaternionToMatrix4() const;

		f32 mX, mY, mZ, mW;
	};

	f32 Dot(const Quaternion& l, const Quaternion& r);

	Quaternion Cross(const Quaternion& l, const Quaternion& r);

	//球面线性插值，两个四元数必须先标准化
	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, f32 t);

}	// end namespace dream

#endif	// end __QUATERNION_H__