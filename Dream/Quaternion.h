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
	//���캯��
		Quaternion() : mX(0.0f), mY(0.0f), mZ(0.0f), mW(1.0f)
		{
			//����
		}

		Quaternion(f32 x, f32 y, f32 z, f32 w = 1.0f) :
			mX(x), mY(y), mZ(z), mW(w)
		{
			//����
		}

	//��׼����
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

	//����
		inline void Identity() { mW = 1.0f, mX = mY = mZ = 0.0f; }

	//������ת��Ԫ��
		inline void SetToRotateX(f32 theta)
		{
			//������
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

		//����ת��������Ԫ��
		void SetToRotateAxis(const Vector3& axis, f32 theta);

	//��Ԫ������
		Quaternion Conjugate() const
		{
			return Quaternion(-mX, -mY, -mZ, mW);
		}

	//����
		inline void Normalize()
		{
			//��ֹ�������ʹ�þ��ȸߵ�Sqrt������FastSqrt;
			f32 mag = Sqrt(mW*mW + mX*mX + mY*mY + mZ*mZ);

			if(mag > 0.0f)
			{
				//����
				f32 oneOverMag = 1.0f / mag;
				mW *= oneOverMag;
				mX *= oneOverMag;
				mY *= oneOverMag;
				mZ *= oneOverMag;
			}
			else
			{
				//�������
				Assert(false);

				//release�汾��ת��Ϊ��λ��Ԫ��
				Identity();
			}
		}

	//ת����Ԫ��
		//������ת��
		inline f32 GetRotationAngle() const
		{
			f32 theraOver2 = ACos(mW);

			return theraOver2 * 2.0f;
		}

		//������ת��
		Vector3 GetRotationAxis() const;

		//ת��ŷ����
		EulerAngles QuaternionToEularAngles() const;

		//ת����4x3����
		Matrix4 QuaternionToMatrix4() const;

		f32 mX, mY, mZ, mW;
	};

	f32 Dot(const Quaternion& l, const Quaternion& r);

	Quaternion Cross(const Quaternion& l, const Quaternion& r);

	//�������Բ�ֵ��������Ԫ�������ȱ�׼��
	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, f32 t);

}	// end namespace dream

#endif	// end __QUATERNION_H__