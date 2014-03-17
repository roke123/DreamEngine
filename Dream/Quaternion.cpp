#include "Quaternion.h"

#include "EulerAngles.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace dream
{
	const Quaternion Quaternion::UnitQuaternion = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

	void Quaternion::SetToRotateAxis(const Vector3& axis, f32 theta)
	{
		f32 thetaOver2 = theta * 0.5f;
		f32 sinThetaOver2 = Sin(thetaOver2);

		mW = Cos(thetaOver2);
		mX = axis.mX * sinThetaOver2;
		mY = axis.mY * sinThetaOver2;
		mZ = axis.mZ * sinThetaOver2;
	}

	Vector3 Quaternion::GetRotationAxis() const
	{
		//����sin^2(theta/2),mW = cos^2(thera/2)
		float sinThetaOver2Sp = 1.0f - mW*mW;

		//�������
		if(sinThetaOver2Sp <= 0.0f)
		{
			//����������
			return Vector3(0.0f, 0.0f, 0.0f);
		}

		float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sp);

		return Vector3(mX * oneOverSinThetaOver2, mY * oneOverSinThetaOver2, 
			mZ * oneOverSinThetaOver2);
	}

	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, f32 t)
	{
		if(t <= 0.0f) return q0;
		if(t >= 1.0f) return q1;

		f32 cosOmega = Dot(q0, q1);

		//������Ԫ��������б�׼��Ϊ��λ��Ԫ����������˱�С��1.0f
		Assert(Equal(1.0f - cosOmega, 0.0f));

		//������Ϊ����ʹ��-q1
		//��Ԫ��q��-q��������ͬ����ת�������ܲ�����ͬ��slerp����,����Ҫѡ����ȷ��һ���Ա������
		//������ת

		f32 q1w = q1.mW;
		f32 q1x = q1.mX;
		f32 q1y = q1.mY;
		f32 q1z = q1.mZ;
		if(cosOmega < 0.0f)
		{
			q1w = -q1w;
			q1x = -q1x;
			q1y = -q1y;
			q1z = -q1z;
			cosOmega = -cosOmega;
		}

		f32 k0 = 0.0f, k1 = 0.0f;
		if(cosOmega > 0.99f)
		{
			//����ת��ǳ��ӽ�ʱ�����Բ�ֵ
			k0 = 1.0f - t;
			k1 = t;
		}
		else
		{
			//ƽ����ֵ
			//��������Ԫ����нǵ�sin
			f32 sinOmage = Sqrt(1.0f - cosOmega * cosOmega);

			//ͨ��sinֵ��cosֵ����Ƕ�
			f32 omage = ATan2(sinOmage, cosOmega);

			//�����ĸ�ĵ���
			f32 oneOverSinOmage = 1.0f / sinOmage;
			
			//�����ֵ
			k0 = Sin((1.0f - t) * omage) * oneOverSinOmage;
			k1 = Sin(t * omage) * oneOverSinOmage;
		}

		Quaternion temp;
		temp.mW = k0 * q0.mW + k1 * q1.mW;
		temp.mX = k0 * q0.mX + k1 * q1.mX;
		temp.mY = k0 * q0.mY + k1 * q1.mY;
		temp.mZ = k0 * q0.mZ + k1 * q1.mZ;
		
		return temp;
	}

	EulerAngles Quaternion::QuaternionToEularAngles() const
	{
		EulerAngles temp;

		//����sin��pitch��
		f32 sp = -2.0f * (mY*mZ + mW*mX);
			
		//���������
		if(Abs(sp) > 0.999f)
		{
			temp.pitch_ = HALF_PI_F * sp;

			//����������,��bank��ת��ת�Ƶ�heading
			temp.bank_ = 0.0f;
			temp.heading_ = ATan2(-mX*mZ - mW*mY, 0.5f - mY*mY - mZ*mZ);
		}
		else
		{
			temp.pitch_ = ASin(sp);
			temp.heading_ = ATan2(mX*mZ - mW*mY, 0.5f - mX*mX - mY*mY);
			temp.bank_ = ATan2(mX*mY - mW*mZ, 0.5f - mX*mX - mZ*mZ);
		}

		return temp;
	}

	Matrix4 Quaternion::QuaternionToMatrix4() const
	{
		Matrix4 temp;

		temp.mM[0][0] = 1.0f - 2.0f*mY*mY - 2.0f*mZ*mZ; 
		temp.mM[0][1] = 2.0f*mX*mY + 2.0f*mW*mZ;
		temp.mM[0][2] = 2.0f*mX*mZ - 2.0f*mW*mY;

		temp.mM[1][0] = 2.0f*mX*mY - 2.0f*mW*mZ; 
		temp.mM[1][1] = 1.0f - 2.0f*mX*mX - 2.0f*mZ*mZ;
		temp.mM[1][2] = 2.0f*mY*mZ + 2.0f*mW*mX;

		temp.mM[2][0] = 2.0f*mX*mZ + 2.0f*mW*mY;
		temp.mM[2][1] = 2.0f*mY*mZ - 2.0f*mW*mX;
		temp.mM[2][2] = 1.0f - 2.0f*mX*mX - 2.0f*mY*mY;

		temp.mM[3][0] = temp.mM[3][1] = temp.mM[3][2] = 0.0f; 
		
		return temp;
	}

	//���
	f32 Dot(const Quaternion& l, const Quaternion& r)
	{
		return l.mW*r.mW + l.mX*r.mX + l.mY*r.mY + l.mZ*r.mZ;
	}
		
	//���
	Quaternion Cross(const Quaternion& l, const Quaternion& r)
	{
		Quaternion temp;

		temp.mW = l.mW*r.mW - l.mX*r.mX - l.mY*r.mY - l.mZ*r.mZ;
		temp.mX = l.mW*r.mX + l.mX*r.mW + l.mZ*r.mY - l.mY*r.mZ;
		temp.mY = l.mW*r.mY + l.mY*r.mW + l.mX*r.mZ - l.mZ*r.mX;
		temp.mZ = l.mW*r.mZ + l.mZ*r.mW + l.mY*r.mX - l.mX*r.mY;

		return temp;
	}

}	// end namespace dream