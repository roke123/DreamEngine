#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "DreMathDeclaration.h"

#include "Plane.h"
#include "Vector3.h"
#include "Angle.h"

namespace dream
{

	//3D�任����
	class Matrix4
	{
	public:
		/** Ĭ�Ϲ��캯�� */
		Matrix4()
		{
			// ����
		}

		/** ���ƹ��캯�� */
		Matrix4(const Matrix4& rh)
		{
			memcpy_s(this->_mM, sizeof(this->_mM), rh._mM, sizeof(rh._mM));
		}

	public:
	//��׼����
		void Identity()
		{
			mM[0][0] = 1.0f; mM[0][1] = 0.0f; mM[0][2] = 0.0f; mM[0][3] = 0.0f;
			mM[1][0] = 0.0f; mM[1][1] = 1.0f; mM[1][2] = 0.0f; mM[1][3] = 0.0f;
			mM[2][0] = 0.0f; mM[2][1] = 0.0f; mM[2][2] = 1.0f; mM[2][3] = 0.0f;
			mM[3][0] = 0.0f; mM[3][1] = 0.0f; mM[3][2] = 0.0f; mM[3][3] = 1.0f;
		}

		void ZeroTranslation()
		{
			mM[3][0] = mM[3][1] = mM[3][2] = 0.0f;
		}

		// �����Ƿ���� �淭ת�����ǰ���Ϊ���棬�����Ϊǰ�棩
		f32 Determinant() const
		{
			return (mM[0][0] * mM[1][1] - mM[0][1] * mM[1][0]) * (mM[2][2] * mM[3][3] - mM[2][3] * mM[3][2]) -
				(mM[0][0] * mM[1][2] - mM[0][2] * mM[1][0]) * (mM[2][1] * mM[3][3] - mM[2][3] * mM[3][1]) +
				(mM[0][0] * mM[1][3] - mM[0][3] * mM[1][0]) * (mM[2][1] * mM[3][2] - mM[2][2] * mM[3][1]) +
				(mM[0][1] * mM[1][2] - mM[0][2] * mM[1][1]) * (mM[2][0] * mM[3][3] - mM[2][3] * mM[3][0]) -
				(mM[0][1] * mM[1][3] - mM[0][3] * mM[1][1]) * (mM[2][0] * mM[3][2] - mM[2][2] * mM[3][0]) +
				(mM[0][2] * mM[1][3] - mM[0][3] * mM[1][2]) * (mM[2][0] * mM[3][1] - mM[2][1] * mM[3][0]);
		}

		bool Inverse(Matrix4 * m) const
		{
			f32 det = Determinant();
				
			//�������
			if(Abs(det) < 0.000001f)
				return false;

			f32 oneOverDet = 1.0f / det;

				
			m->mM[0][0] = det * (
					mM[1][1] * (mM[2][2] * mM[3][3] - mM[2][3] * mM[3][2]) +
					mM[1][2] * (mM[2][3] * mM[3][1] - mM[2][1] * mM[3][3]) +
					mM[1][3] * (mM[2][1] * mM[3][2] - mM[2][2] * mM[3][1]));
			m->mM[0][1] = det * (
					mM[2][1] * (mM[0][2] * mM[3][3] - mM[0][3] * mM[3][2]) +
					mM[2][2] * (mM[0][3] * mM[3][1] - mM[0][1] * mM[3][3]) +
					mM[2][3] * (mM[0][1] * mM[3][2] - mM[0][2] * mM[3][1]));
			m->mM[0][2] = det * (
					mM[3][1] * (mM[0][2] * mM[1][3] - mM[0][3] * mM[1][2]) +
					mM[3][2] * (mM[0][3] * mM[1][1] - mM[0][1] * mM[1][3]) +
					mM[3][3] * (mM[0][1] * mM[1][2] - mM[0][2] * mM[1][1]));
			m->mM[0][3] = det * (
					mM[0][1] * (mM[1][3] * mM[2][2] - mM[1][2] * mM[2][3]) +
					mM[0][2] * (mM[1][1] * mM[2][3] - mM[1][3] * mM[2][1]) +
					mM[0][3] * (mM[1][2] * mM[2][1] - mM[1][1] * mM[2][2]));
			m->mM[1][0] = det * (
					mM[1][2] * (mM[2][0] * mM[3][3] - mM[2][3] * mM[3][0]) +
					mM[1][3] * (mM[2][2] * mM[3][0] - mM[2][0] * mM[3][2]) +
					mM[1][0] * (mM[2][3] * mM[3][2] - mM[2][2] * mM[3][3]));
			m->mM[1][1] = det * (
					mM[2][2] * (mM[0][0] * mM[3][3] - mM[0][3] * mM[3][0]) +
					mM[2][3] * (mM[0][2] * mM[3][0] - mM[0][0] * mM[3][2]) +
					mM[2][0] * (mM[0][3] * mM[3][2] - mM[0][2] * mM[3][3]));
			m->mM[1][2] = det * (
					mM[3][2] * (mM[0][0] * mM[1][3] - mM[0][3] * mM[1][0]) +
					mM[3][3] * (mM[0][2] * mM[1][0] - mM[0][0] * mM[1][2]) +
					mM[3][0] * (mM[0][3] * mM[1][2] - mM[0][2] * mM[1][3]));
			m->mM[1][3] = det * (
					mM[0][2] * (mM[1][3] * mM[2][0] - mM[1][0] * mM[2][3]) +
					mM[0][3] * (mM[1][0] * mM[2][2] - mM[1][2] * mM[2][0]) +
					mM[0][0] * (mM[1][2] * mM[2][3] - mM[1][3] * mM[2][2]));
			m->mM[2][0] = det * (
					mM[1][3] * (mM[2][0] * mM[3][1] - mM[2][1] * mM[3][0]) +
					mM[1][0] * (mM[2][1] * mM[3][3] - mM[2][3] * mM[3][1]) +
					mM[1][1] * (mM[2][3] * mM[3][0] - mM[2][0] * mM[3][3]));
			m->mM[2][1] = det * (
					mM[2][3] * (mM[0][0] * mM[3][1] - mM[0][1] * mM[3][0]) +
					mM[2][0] * (mM[0][1] * mM[3][3] - mM[0][3] * mM[3][1]) +
					mM[2][1] * (mM[0][3] * mM[3][0] - mM[0][0] * mM[3][3]));
			m->mM[2][2] = det * (
					mM[3][3] * (mM[0][0] * mM[1][1] - mM[0][1] * mM[1][0]) +
					mM[3][0] * (mM[0][1] * mM[1][3] - mM[0][3] * mM[1][1]) +
					mM[3][1] * (mM[0][3] * mM[1][0] - mM[0][0] * mM[1][3]));
			m->mM[2][3] = det * (
					mM[0][3] * (mM[1][1] * mM[2][0] - mM[1][0] * mM[2][1]) +
					mM[0][0] * (mM[1][3] * mM[2][1] - mM[1][1] * mM[2][3]) +
					mM[0][1] * (mM[1][0] * mM[2][3] - mM[1][3] * mM[2][0]));
			m->mM[3][0] = det * (
					mM[1][0] * (mM[2][2] * mM[3][1] - mM[2][1] * mM[3][2]) +
					mM[1][1] * (mM[2][0] * mM[3][2] - mM[2][2] * mM[3][0]) +
					mM[1][2] * (mM[2][1] * mM[3][0] - mM[2][0] * mM[3][1]));
			m->mM[3][1] = det * (
					mM[2][0] * (mM[0][2] * mM[3][1] - mM[0][1] * mM[3][2]) +
					mM[2][1] * (mM[0][0] * mM[3][2] - mM[0][2] * mM[3][0]) +
					mM[2][2] * (mM[0][1] * mM[3][0] - mM[0][0] * mM[3][1]));
			m->mM[3][2] = det * (
					mM[3][0] * (mM[0][2] * mM[1][1] - mM[0][1] * mM[1][2]) +
					mM[3][1] * (mM[0][0] * mM[1][2] - mM[0][2] * mM[1][0]) +
					mM[3][2] * (mM[0][1] * mM[1][0] - mM[0][0] * mM[1][1]));
			m->mM[3][3] = det * (
					mM[0][0] * (mM[1][1] * mM[2][2] - mM[1][2] * mM[2][1]) +
					mM[0][1] * (mM[1][2] * mM[2][0] - mM[1][0] * mM[2][2]) +
					mM[0][2] * (mM[1][0] * mM[2][1] - mM[1][1] * mM[2][0]));

			return true;
		}

	//��׼����
		Matrix4 operator * (const Matrix4& a) const 
		{
			Matrix4 temp;

			temp.mM[0][0] = mM[0][0]*a.mM[0][0] + mM[0][1]*a.mM[1][0] + mM[0][2]*a.mM[2][0] + mM[0][3]*a.mM[3][0];
			temp.mM[0][1] = mM[0][0]*a.mM[0][1] + mM[0][1]*a.mM[1][1] + mM[0][2]*a.mM[2][1] + mM[0][3]*a.mM[3][1];
			temp.mM[0][2] = mM[0][0]*a.mM[0][2] + mM[0][1]*a.mM[1][2] + mM[0][2]*a.mM[2][2] + mM[0][3]*a.mM[3][2];
			temp.mM[0][3] = mM[0][0]*a.mM[0][2] + mM[0][1]*a.mM[1][2] + mM[0][2]*a.mM[2][2] + mM[0][3]*a.mM[3][3];
			temp.mM[1][0] = mM[1][0]*a.mM[0][0] + mM[1][1]*a.mM[1][0] + mM[1][2]*a.mM[2][0] + mM[1][3]*a.mM[3][0];
			temp.mM[1][1] = mM[1][0]*a.mM[0][1] + mM[1][1]*a.mM[1][1] + mM[1][2]*a.mM[2][1] + mM[1][3]*a.mM[3][1];
			temp.mM[1][2] = mM[1][0]*a.mM[0][2] + mM[1][1]*a.mM[1][2] + mM[1][2]*a.mM[2][2] + mM[1][3]*a.mM[3][2];
			temp.mM[1][3] = mM[1][0]*a.mM[0][2] + mM[1][1]*a.mM[1][2] + mM[1][2]*a.mM[2][2] + mM[1][3]*a.mM[3][3];
			temp.mM[2][0] = mM[2][0]*a.mM[0][0] + mM[2][1]*a.mM[1][0] + mM[2][2]*a.mM[2][0] + mM[2][3]*a.mM[3][0];
			temp.mM[2][1] = mM[2][0]*a.mM[0][1] + mM[2][1]*a.mM[1][1] + mM[2][2]*a.mM[2][1] + mM[2][3]*a.mM[3][1];
			temp.mM[2][2] = mM[2][0]*a.mM[0][2] + mM[2][1]*a.mM[1][2] + mM[2][2]*a.mM[2][2] + mM[2][3]*a.mM[3][2];
			temp.mM[2][2] = mM[2][0]*a.mM[0][2] + mM[2][1]*a.mM[1][2] + mM[2][2]*a.mM[2][2] + mM[2][3]*a.mM[3][3];
			temp.mM[3][0] = mM[3][0]*a.mM[0][0] + mM[3][1]*a.mM[1][0] + mM[3][2]*a.mM[2][0] + mM[2][3]*a.mM[3][0];
			temp.mM[3][1] = mM[3][0]*a.mM[0][1] + mM[3][1]*a.mM[1][1] + mM[3][2]*a.mM[2][1] + mM[2][3]*a.mM[3][1];
			temp.mM[3][2] = mM[3][0]*a.mM[0][2] + mM[3][1]*a.mM[1][2] + mM[3][2]*a.mM[2][2] + mM[2][3]*a.mM[3][2];
			temp.mM[3][3] = mM[3][0]*a.mM[0][2] + mM[3][1]*a.mM[1][2] + mM[3][2]*a.mM[2][2] + mM[2][3]*a.mM[3][3];

			return temp;
		}

		Matrix4 operator *= (const Matrix4& a)
		{
			Matrix4 temp = *this;

			mM[0][0] = temp.mM[0][0]*a.mM[0][0] + temp.mM[0][1]*a.mM[1][0] + temp.mM[0][2]*a.mM[2][0] + temp.mM[0][3]*a.mM[3][0];
			mM[0][1] = temp.mM[0][0]*a.mM[0][1] + temp.mM[0][1]*a.mM[1][1] + temp.mM[0][2]*a.mM[2][1] + temp.mM[0][3]*a.mM[3][1];
			mM[0][2] = temp.mM[0][0]*a.mM[0][2] + temp.mM[0][1]*a.mM[1][2] + temp.mM[0][2]*a.mM[2][2] + temp.mM[0][3]*a.mM[3][2];
			mM[0][3] = temp.mM[0][0]*a.mM[0][2] + temp.mM[0][1]*a.mM[1][2] + temp.mM[0][2]*a.mM[2][2] + temp.mM[0][3]*a.mM[3][3];
			mM[1][0] = temp.mM[1][0]*a.mM[0][0] + temp.mM[1][1]*a.mM[1][0] + temp.mM[1][2]*a.mM[2][0] + temp.mM[1][3]*a.mM[3][0];
			mM[1][1] = temp.mM[1][0]*a.mM[0][1] + temp.mM[1][1]*a.mM[1][1] + temp.mM[1][2]*a.mM[2][1] + temp.mM[1][3]*a.mM[3][1];
			mM[1][2] = temp.mM[1][0]*a.mM[0][2] + temp.mM[1][1]*a.mM[1][2] + temp.mM[1][2]*a.mM[2][2] + temp.mM[1][3]*a.mM[3][2];
			mM[1][3] = temp.mM[1][0]*a.mM[0][2] + temp.mM[1][1]*a.mM[1][2] + temp.mM[1][2]*a.mM[2][2] + temp.mM[1][3]*a.mM[3][3];
			mM[2][0] = temp.mM[2][0]*a.mM[0][0] + temp.mM[2][1]*a.mM[1][0] + temp.mM[2][2]*a.mM[2][0] + temp.mM[2][3]*a.mM[3][0];
			mM[2][1] = temp.mM[2][0]*a.mM[0][1] + temp.mM[2][1]*a.mM[1][1] + temp.mM[2][2]*a.mM[2][1] + temp.mM[2][3]*a.mM[3][1];
			mM[2][2] = temp.mM[2][0]*a.mM[0][2] + temp.mM[2][1]*a.mM[1][2] + temp.mM[2][2]*a.mM[2][2] + temp.mM[2][3]*a.mM[3][2];
			mM[2][2] = temp.mM[2][0]*a.mM[0][2] + temp.mM[2][1]*a.mM[1][2] + temp.mM[2][2]*a.mM[2][2] + temp.mM[2][3]*a.mM[3][3];
			mM[3][0] = temp.mM[3][0]*a.mM[0][0] + temp.mM[3][1]*a.mM[1][0] + temp.mM[3][2]*a.mM[2][0] + temp.mM[2][3]*a.mM[3][0];
			mM[3][1] = temp.mM[3][0]*a.mM[0][1] + temp.mM[3][1]*a.mM[1][1] + temp.mM[3][2]*a.mM[2][1] + temp.mM[2][3]*a.mM[3][1];
			mM[3][2] = temp.mM[3][0]*a.mM[0][2] + temp.mM[3][1]*a.mM[1][2] + temp.mM[3][2]*a.mM[2][2] + temp.mM[2][3]*a.mM[3][2];
			mM[3][3] = temp.mM[3][0]*a.mM[0][2] + temp.mM[3][1]*a.mM[1][2] + temp.mM[3][2]*a.mM[2][2] + temp.mM[2][3]*a.mM[3][3];
			
			return *this;
		}

		bool operator == (const Matrix4& a) const
		{
			return Float::IsEqual(mM[0][0], a.mM[0][0]) &&
				Float::IsEqual(mM[0][1], a.mM[0][1]) &&
				Float::IsEqual(mM[0][2], a.mM[0][2]) &&
				Float::IsEqual(mM[0][3], a.mM[0][3]) &&
				Float::IsEqual(mM[1][0], a.mM[1][0]) &&
				Float::IsEqual(mM[1][1], a.mM[1][1]) &&
				Float::IsEqual(mM[1][2], a.mM[1][2]) &&
				Float::IsEqual(mM[1][3], a.mM[1][3]) &&
				Float::IsEqual(mM[2][0], a.mM[2][0]) &&
				Float::IsEqual(mM[2][1], a.mM[2][1]) &&
				Float::IsEqual(mM[2][2], a.mM[2][2]) &&
				Float::IsEqual(mM[2][3], a.mM[2][3]) &&
				Float::IsEqual(mM[3][0], a.mM[3][0]) &&
				Float::IsEqual(mM[3][1], a.mM[3][1]) &&
				Float::IsEqual(mM[3][2], a.mM[3][2]) &&
				Float::IsEqual(mM[3][3], a.mM[3][3]);
		}

		bool operator != (const Matrix4& a)
		{
			return !this->operator==(a);
		}

		Matrix4 operator =(const Matrix4& rh) {
			if (&rh == this)
				return;

			memcpy_s(this->_mM, sizeof(this->_mM), rh._mM, sizeof(rh._mM));
		}

	//�������ž���
		//������������
		static Matrix4 SetScale(f32 x, f32 y, f32 z)
		{
			Matrix4 ret;

			ret.mM[0][0] = x;
			ret.mM[1][1] = y;
			ret.mM[2][2] = z;

			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;

			return ret;
		}

		//������������
		static Matrix4 SetScaleByAxis(const Vector3& axis, f32 x, f32 y, f32 z);
		
	//�����б����
		//��X���б�
		static Matrix4 SetShearX(f32 s, f32 t)
		{
			Matrix4 ret;

			ret.mM[0][0] = 1.0f, ret.mM[1][0] = s,	  ret.mM[2][0] = t;
			ret.mM[0][1] = 0.0f, ret.mM[1][1] = 1.0f, ret.mM[2][1] = 0.0f;
			ret.mM[0][2] = 0.0f, ret.mM[1][2] = 0.0f, ret.mM[2][2] = 1.0f;
				
			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

		 static Matrix4 SetShearY(f32 s, f32 t)
		{
			Matrix4 ret;

			ret.mM[0][0] = 1.0f, ret.mM[1][0] = 0.0f, ret.mM[2][0] = 0.0f;
			ret.mM[0][1] = s,	 ret.mM[1][1] = 1.0f, ret.mM[2][1] = t;
			ret.mM[0][2] = 0.0f, ret.mM[1][2] = 0.0f, ret.mM[2][2] = 1.0f;
				
			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

		 static Matrix4 SetShearZ(f32 s, f32 t)
		{
			Matrix4 ret;

			ret.mM[0][0] = 1.0f, ret.mM[1][0] = 0.0f, ret.mM[2][0] = 0.0f;
			ret.mM[0][1] = 0.0f, ret.mM[1][1] = 1.0f, ret.mM[2][1] = 0.0f;
			ret.mM[0][2] = s,	 ret.mM[1][2] = t,    ret.mM[2][2] = 1.0f;
				
			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

	//���췴�����
		//�������ԭ���ƽ�淴�䣬ƽ�洹ֱ��axis
		static Matrix4 SetReflect(const Vector3& axis)
		{
			// ���axis�Ƿ������滯
			Assert(Abs(Dot(axis, axis)) - 1.0f < 0.01f);

			Matrix4 ret;

			f32 ax = -2.0f * axis.mX;
			f32 ay = -2.0f * axis.mY;
			f32 az = -2.0f * axis.mZ;

			// ��ʽ��newpoint = point - 2 * (point��ƽ�淨���ϵķ���)
			//		 {x', y', z'} = { x, y, z } - 2.0 * (x * nx + y * ny + z * nz) * {nx, ny, nz};
			//		  x' = x - 2.0 * (x * nx + y * ny + z * nz) * nx

			ret.mM[0][0] = 1.0f + ax * axis.mX;
			ret.mM[1][1] = 1.0f + ay * axis.mY;
			ret.mM[2][2] = 1.0f + az * axis.mZ;

			ret.mM[1][0] = ret.mM[0][1] = ax * axis.mY;
			ret.mM[2][0] = ret.mM[0][2] = ax * axis.mZ;
			ret.mM[2][1] = ret.mM[1][2] = ay * axis.mZ;

			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

		//��xoyƽ�淴��
		static Matrix4 SetReflectXOY()
		{
			Matrix4 ret;

			ret.mM[0][0] = 1.0f;
			ret.mM[1][1] = 1.0f;
			ret.mM[2][2] = -1.0f;

			ret.mM[1][0] = ret.mM[0][1] = 0.0f;
			ret.mM[2][0] = ret.mM[0][2] = 0.0f;
			ret.mM[2][1] = ret.mM[1][2] = 0.0f;

			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

		static Matrix4 SetReflectXOZ()
		{
			Matrix4 ret;

			ret.mM[0][0] = 1.0f;
			ret.mM[1][1] = -1.0f;
			ret.mM[2][2] = 1.0f;

			ret.mM[1][0] = ret.mM[0][1] = 0.0f;
			ret.mM[2][0] = ret.mM[0][2] = 0.0f;
			ret.mM[2][1] = ret.mM[1][2] = 0.0f;

			ret.mM[3][3] = 1.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

		static Matrix4 SetReflectYOZ()
		{
			Matrix4 ret;

			ret.mM[0][0] = -1.0f;
			ret.mM[1][1] = 1.0f;
			ret.mM[2][2] = 1.0f;

			ret.mM[1][0] = ret.mM[0][1] = 0.0f;
			ret.mM[2][0] = ret.mM[0][2] = 0.0f;
			ret.mM[2][1] = ret.mM[1][2] = 0.0f;

			ret.mM[3][3] = 1.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			
			return ret;
		}


	//����ƽ�ƾ���
		static Matrix4 SetTranslation(f32 x, f32 y, f32 z)
		{
			Matrix4 ret;

			ret.mM[0][0] = ret.mM[1][0] = ret.mM[2][0] = 0.0f;
			ret.mM[0][1] = ret.mM[1][1] = ret.mM[2][1] = 0.0f;
			ret.mM[0][2] = ret.mM[1][2] = ret.mM[2][2] = 0.0f;

			ret.mM[0][3] = x;
			ret.mM[1][3] = y;
			ret.mM[2][3] = z;

			ret.mM[3][3] = 1.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			
			return ret;
		}

	// ������ת����ʹ�û�����
		// ��X����ת
		static Matrix4 SetRotationX(f32 xRadians)
		{
			Matrix4 ret;

			f32 sinX = Sin(xRadians);
			f32 cosX = Cos(xRadians);

			ret.mM[0][0] = 1.0f; ret.mM[1][0] = 0.0f;  ret.mM[2][0] = 0.0f;
			ret.mM[0][1] = 0.0f; ret.mM[1][1] = cosX;  ret.mM[2][1] = sinX;
			ret.mM[0][2] = 0.0f; ret.mM[1][2] = -sinX; ret.mM[2][2] = cosX;
				
			ret.mM[3][3] = 1.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			
			return ret;
		}

		// ��Y����ת
		static Matrix4 SetRotationY(f32 yRadiens)
		{
			Matrix4 ret;

			f32 sinY = Sin(yRadiens);
			f32 cosY = Cos(yRadiens);

			ret.mM[0][0] = cosY; ret.mM[1][0] = 0.0f; ret.mM[2][0] = -sinY;
			ret.mM[0][1] = 0.0f; ret.mM[1][1] = 1.0f; ret.mM[2][1] = 0.0f;
			ret.mM[0][2] = sinY; ret.mM[1][2] = 0.0f; ret.mM[2][2] = cosY;
				
			ret.mM[3][3] = 1.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			
			return ret;
		}

		// ��Z����ת
		static Matrix4 SetRotationZ(f32 zRadiens)
		{
			Matrix4 ret;

			f32 sinZ = Sin(zRadiens);
			f32 cosZ = Cos(zRadiens);

			ret.mM[0][0] = cosZ;  ret.mM[1][0] = sinZ; ret.mM[2][0] = 0.0f;
			ret.mM[0][1] = -sinZ; ret.mM[1][1] = cosZ; ret.mM[2][1] = 0.0f;
			ret.mM[0][2] = 0.0f;  ret.mM[1][2] = 0.0f; ret.mM[2][2] = 1.0f;
				
			ret.mM[3][3] = 1.0f;
			ret.mM[3][0] = ret.mM[3][1] = ret.mM[3][2] = 0.0f;
			ret.mM[0][3] = ret.mM[1][3] = ret.mM[2][3] = 0.0f;
			
			return ret;
		}

		// ����������ת,��ת���ԭ��
		static Matrix4 SetRotationByAxis(const Vector3& axis, f32 radiens);

	// ͸�ӱ任
		// widthOfViewVolume,heightOfViewVolume:���ü���ĳ���
		 static Matrix4 SetPerspectiveMatrixLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(widthOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(heightOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// ��ʱ�����Ѿ�������������ת������Ϊ�����ԭ�㣬�������������ϵ��

			Matrix4 ret;

			// d * zNear/(widthOfViewVolume / 2)
			// dΪ�Ӿ�Ĭ��Ϊ1
			ret.mM[0][0] = 2.0f * zNear / widthOfViewVolume ;
			ret.mM[1][0] = 0;
			ret.mM[2][0] = 0;
			ret.mM[3][0] = 0;
						 
			ret.mM[0][1] = 0;
			ret.mM[1][1] = 2.0f * zNear / heightOfViewVolume;
			ret.mM[2][1] = 0;
			ret.mM[3][1] = 0;
						 
			ret.mM[0][2] = 0;
			ret.mM[1][2] = 0;
			ret.mM[2][2] = zFar / (zFar - zNear);
			ret.mM[3][2] = 1.0f;

			ret.mM[0][3] = 0;
			ret.mM[1][3] = 0;
			ret.mM[2][3] = zNear * zFar / (zNear - zFar);
			ret.mM[3][3] = 0;
			
			return ret;
		}

		// widthOfViewVolume,heightOfViewVolume:���ü���ĳ���
		 static Matrix4 SetPerspectiveMatrixRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(widthOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(heightOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// ��ʱ�����Ѿ�������������ת������Ϊ�����ԭ�㣬�������������ϵ��

			Matrix4 ret;

			// ��zNearΪ�Ӿ�
			ret.mM[0][0] = 2.0f * zNear / widthOfViewVolume;
			ret.mM[1][0] = 0.0f;
			ret.mM[2][0] = 0.0f;
			ret.mM[3][0] = 0.0f;

			ret.mM[0][1] = 0.0f;
			ret.mM[1][1] = 2.0f * zNear / heightOfViewVolume;
			ret.mM[2][1] = 0.0f;
			ret.mM[3][1] = 0.0f;

			ret.mM[0][2] = 0.0f;
			ret.mM[1][2] = 0.0f;
			ret.mM[2][2] = zFar / (zFar - zNear);
			ret.mM[3][2] = -1.0f;

			ret.mM[0][3] = 0.0f;
			ret.mM[1][3] = 0.0f;
			ret.mM[2][3] = zNear * zFar / (zNear - zFar);
			ret.mM[3][3] = 0.0f;
			
			return ret;
		}

		// fieldOfViewRadians:��ֱ�ӽǣ�aspectRatio�� X/Y
		static Matrix4 SetPerspectiveFovMatrixLH(Radian fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(aspectRatio, 0.f)); //divide by zero
			Assert(Float::IsEqual(fieldOfViewRadians.GetValue(), 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// Ĭ���Ӿ�Ϊ1
			f32 h = 1.0f / tan(fieldOfViewRadians.GetValue() / 2);		
			f32 w = h / aspectRatio;
				

			// ��ʱ�����Ѿ�������������ת������Ϊ�����ԭ�㣬�������������ϵ��

			Matrix4 ret;

			// d * zNear/(widthOfViewVolume / 2)
			// dΪ�Ӿ�Ĭ��Ϊ1
			ret.mM[0][0] = w;
			ret.mM[1][0] = 0.0f;
			ret.mM[2][0] = 0.0f;
			ret.mM[3][0] = 0.0f;

			ret.mM[0][1] = 0.0f;
			ret.mM[1][1] = h;
			ret.mM[2][1] = 0.0f;
			ret.mM[3][1] = 0.0f;

			// ͨ��w = x * zFar / (zFar - zNear) + x * zNear * zFar / (zNear - zFar)��ʹ�õ������z���С��zNear
			// ��õ���w < -z,
			ret.mM[0][2]= 0.0f;
			ret.mM[1][2]= 0.0f;
			ret.mM[2][2] = zFar / (zFar - zNear);
			ret.mM[3][2] = 1.0f;

			ret.mM[0][3] = 0.0f;
			ret.mM[1][3] = 0.0f;
			ret.mM[2][3] = zNear * zFar / (zNear - zFar);
			ret.mM[3][3] = 0.0f;
			
			return ret;
		}

		// fieldOfViewRadians:��ֱ�ӽǣ�aspectRatio�� X/Y
		 static Matrix4 SetPerspectiveFovMatrixRH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(aspectRatio, 0.f)); //divide by zero
			Assert(Float::IsEqual(fieldOfViewRadians, 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// Ĭ���Ӿ�d = 1
			f32 h = 1.0f / tan(fieldOfViewRadians / 2);		// ��ǰ�ӽǵ��Ӿ������Ҳü������ӽ�Ϊ90ʱ���Ҳü���Ľ�����֮�ȣ�
														// ʵ�ʹ�ʽΪ(d * tan(fieldOfViewRadians / 2)) / 
														// (d * tan(90 / 2))
			f32 w = h / aspectRatio;					// ���ݱ������㵱ǰ�ӽǵ��Ӿ������²ü������ӽ�Ϊ90ʱ���²ü���Ľ���߶�֮�ȡ�
				

			// ��ʱ�����Ѿ�������������ת������Ϊ�����ԭ�㣬�������������ϵ��

			Matrix4 ret;

			ret.mM[0][0] = w;
			ret.mM[1][0] = 0.0f;
			ret.mM[2][0] = 0.0f;
			ret.mM[3][0] = 0.0f;

			ret.mM[0][1] = 0.0f;
			ret.mM[1][1] = h;
			ret.mM[2][1] = 0.0f;
			ret.mM[3][1] = 0.0f;

			ret.mM[0][2]= 0.0f;
			ret.mM[1][2]= 0.0f;
			ret.mM[2][2] = zFar / (zFar - zNear);
			ret.mM[3][2] = -1.0f;

			ret.mM[0][3] = 0.0f;
			ret.mM[1][3] = 0.0f;
			ret.mM[2][3] = zNear * zFar / (zNear - zFar);
			ret.mM[3][3] = 0.0f;
			
			return ret;
		}

	// ����ͶӰ
		 static Matrix4 SetProjectionOrthoxMatrixLH(
				f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			Assert(widthOfViewVolume == 0.f); //divide by zero
			Assert(heightOfViewVolume == 0.f); //divide by zero
			Assert(zNear == zFar); //divide by zero

			Matrix4 ret;

			ret.mM[0][0] = 2 / widthOfViewVolume;
			ret.mM[1][0] = 0.0f;
			ret.mM[2][0] = 0.0f;
			ret.mM[3][0] = 0.0f;

			ret.mM[0][1] = 0.0f;
			ret.mM[1][1] = 2 / heightOfViewVolume;
			ret.mM[2][1] = 0.0f;
			ret.mM[3][1] = 0.0f;

			ret.mM[0][2] = 0.0f;
			ret.mM[1][2] = 0.0f;
			ret.mM[2][2] = 1 / (zFar - zNear);
			ret.mM[3][2] = 0.0f;

			ret.mM[0][3] = 0.0f;
			ret.mM[1][3] = 0.0f;
			ret.mM[2][3] = zNear / (zNear - zFar);
			ret.mM[3][3] = 1.0f;
			
			return ret;
		}

		 static Matrix4 SetProjectionOrthoMatrixRH(
		f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			Assert(widthOfViewVolume == 0.f); //divide by zero
			Assert(heightOfViewVolume == 0.f); //divide by zero
			Assert(zNear == zFar); //divide by zero

			Matrix4 ret;

			ret.mM[0][0] = 2.0f / widthOfViewVolume;
			ret.mM[1][0] = 0.0f;
			ret.mM[2][0] = 0.0f;
			ret.mM[3][0] = 0.0f;
						 
			ret.mM[0][1] = 0.0f;
			ret.mM[1][1] = 2.0f / heightOfViewVolume;
			ret.mM[2][1] = 0.0f;
			ret.mM[3][1] = 0.0f;
						 
			ret.mM[0][2] = 0.0f;
			ret.mM[1][2] = 0.0f;
			ret.mM[2][2] = 1.0f / (zNear-zFar);
			ret.mM[3][2] = 0.0f;

			ret.mM[0][3] = 0.0f;
			ret.mM[1][3] = 0.0f;
			ret.mM[2][3] = zNear / (zNear - zFar);
			ret.mM[3][3] = -1.0f;
			
			return ret;
		}

	// ��Ӱ����
		// ��ԴΪ���Դ
		static Matrix4 SetPointShadowMatrix(const Vector3& light, const Plane& plane)
		{
			const f32 d = Dot(plane.n_, light);

			Matrix4 ret;

			ret.mM[0][0] = -plane.n_.mX * light.mX + d;
			ret.mM[1][0] = -plane.n_.mX * light.mY;
			ret.mM[2][0] = -plane.n_.mX * light.mZ;
			ret.mM[3][0] = -plane.n_.mX;

			ret.mM[0][1] = -plane.n_.mY * light.mX;
			ret.mM[1][1] = -plane.n_.mY * light.mY + d;
			ret.mM[2][1] = -plane.n_.mY * light.mZ;
			ret.mM[3][1] = -plane.n_.mY;

			ret.mM[0][2] = -plane.n_.mZ * light.mX;
			ret.mM[1][2] = -plane.n_.mZ * light.mY;
			ret.mM[2][2] = -plane.n_.mZ * light.mZ + d;
			ret.mM[3][2] = -plane.n_.mZ;

			ret.mM[0][3] = -plane.d_ * light.mX;
			ret.mM[1][3] = -plane.d_ * light.mY;
			ret.mM[2][3] = -plane.d_ * light.mZ;
			ret.mM[3][3] = -plane.d_ + d;
			
			return ret;
		}

		// ��ԴΪƽ�й�Դ
		static Matrix4 SetParallelShadowMatrix(const Vector3& light, const Plane& plane)
		{
			const f32 d = Dot(plane.n_, light);

			Matrix4 ret;

			ret.mM[0][0] = -plane.n_.mX * light.mX + d;
			ret.mM[1][0] = -plane.n_.mX * light.mY;
			ret.mM[2][0] = -plane.n_.mX * light.mZ;
			ret.mM[3][0] = 0;

			ret.mM[0][1] = -plane.n_.mY * light.mX;
			ret.mM[1][1] = -plane.n_.mY * light.mY + d;
			ret.mM[2][1] = -plane.n_.mY * light.mZ;
			ret.mM[3][1] = 0;

			ret.mM[0][2] = -plane.n_.mZ * light.mX;
			ret.mM[1][2] = -plane.n_.mZ * light.mY;
			ret.mM[2][2] = -plane.n_.mZ * light.mZ + d;
			ret.mM[3][2] = 0;

			ret.mM[0][3] = -plane.d_ * light.mX;
			ret.mM[1][3] = -plane.d_ * light.mY;
			ret.mM[2][3] = -plane.d_ * light.mZ;
			ret.mM[3][3] = d;
			
			return ret;
		}

	// �������ϵת��
		//param - position	: �������
		//param - target	: ���ŵ�Ŀ���
		//param - upVector	: ��ֱ����
		static Matrix4 SetCameraLookAtMatrixLH(
				const Vector3& position,
				const Vector3& target,
				const Vector3& upVector);

		static Matrix4 SetCameraLookAtMatrixRH(
				const Vector3& position,
				const Vector3& target,
				const Vector3& upVector);

		//param - position		: �������
		//param - orientation	: ���ŵ�Ŀ���
		//param - upVector		: ��ֱ����
		static Matrix4 SetCameraOrientationMatrixLH(
				const Vector3& position,
				const Vector3& orientation,
				const Vector3& upVector);

		static Matrix4 SetCameraOrientationMatrixRH(
				const Vector3& position,
				const Vector3& orientation,
				const Vector3& upVector);

		static Matrix4 SetMatrixForNode(const Vector3& position, const Vector3& rotation, const Quaternion& orientation);

	//ת����Ԫ����ŷ����
		EulerAngles Matrix4ToEulerAngles() const;

		Quaternion Matrix4ToQuaternion() const ;

		/// ��һ��ΪX�ᣬ�ڶ���ΪY�ᣬ������ΪZ�ᣬ������ΪW��
		union 
		{
			f32 mM[4][4];
			f32 _mM[16];
		};
		
	};	// end class Matrix4

	extern const Matrix4 IdentityMatrix;

}	// end namespace dream

#endif	// end __MATRIX4_H__