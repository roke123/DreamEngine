#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "DreMathDeclaration.h"

#include "Plane.h"
#include "Vector3.h"
#include "Angle.h"

namespace dream
{

	//3D变换矩阵
	class Matrix4
	{
	public:
		/** 默认构造函数 */
		Matrix4()
		{
			// 留空
		}

		/** 复制构造函数 */
		Matrix4(const Matrix4& rh)
		{
			memcpy_s(this->_mM, sizeof(this->_mM), rh._mM, sizeof(rh._mM));
		}

	public:
	//标准操作
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

		// 计算是否存在 面翻转情况（前面变为背面，背面变为前面）
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
				
			//无逆矩阵
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

	//标准操作
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

	//构造缩放矩阵
		//按坐标轴缩放
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

		//按任意轴缩放
		static Matrix4 SetScaleByAxis(const Vector3& axis, f32 x, f32 y, f32 z);
		
	//构造切变矩阵
		//沿X轴切变
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

	//构造反射矩阵
		//按任意过原点的平面反射，平面垂直于axis
		static Matrix4 SetReflect(const Vector3& axis)
		{
			// 检查axis是否已正规化
			Assert(Abs(Dot(axis, axis)) - 1.0f < 0.01f);

			Matrix4 ret;

			f32 ax = -2.0f * axis.mX;
			f32 ay = -2.0f * axis.mY;
			f32 az = -2.0f * axis.mZ;

			// 公式：newpoint = point - 2 * (point在平面法线上的分量)
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

		//按xoy平面反射
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


	//构造平移矩阵
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

	// 构造旋转矩阵，使用弧度制
		// 绕X轴旋转
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

		// 绕Y轴旋转
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

		// 绕Z轴旋转
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

		// 绕任意轴旋转,旋转轴过原点
		static Matrix4 SetRotationByAxis(const Vector3& axis, f32 radiens);

	// 透视变换
		// widthOfViewVolume,heightOfViewVolume:近裁剪面的长宽
		 static Matrix4 SetPerspectiveMatrixLH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(widthOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(heightOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// 此时顶点已经经过相机矩阵的转换，认为相机在原点，顶点在相机坐标系中

			Matrix4 ret;

			// d * zNear/(widthOfViewVolume / 2)
			// d为视距默认为1
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

		// widthOfViewVolume,heightOfViewVolume:近裁剪面的长宽
		 static Matrix4 SetPerspectiveMatrixRH(f32 widthOfViewVolume, f32 heightOfViewVolume, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(widthOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(heightOfViewVolume, 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// 此时顶点已经经过相机矩阵的转换，认为相机在原点，顶点在相机坐标系中

			Matrix4 ret;

			// 以zNear为视距
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

		// fieldOfViewRadians:垂直视角，aspectRatio： X/Y
		static Matrix4 SetPerspectiveFovMatrixLH(Radian fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(aspectRatio, 0.f)); //divide by zero
			Assert(Float::IsEqual(fieldOfViewRadians.GetValue(), 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// 默认视距为1
			f32 h = 1.0f / tan(fieldOfViewRadians.GetValue() / 2);		
			f32 w = h / aspectRatio;
				

			// 此时顶点已经经过相机矩阵的转换，认为相机在原点，顶点在相机坐标系中

			Matrix4 ret;

			// d * zNear/(widthOfViewVolume / 2)
			// d为视距默认为1
			ret.mM[0][0] = w;
			ret.mM[1][0] = 0.0f;
			ret.mM[2][0] = 0.0f;
			ret.mM[3][0] = 0.0f;

			ret.mM[0][1] = 0.0f;
			ret.mM[1][1] = h;
			ret.mM[2][1] = 0.0f;
			ret.mM[3][1] = 0.0f;

			// 通过w = x * zFar / (zFar - zNear) + x * zNear * zFar / (zNear - zFar)，使得当顶点的z如果小于zNear
			// 其得到的w < -z,
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

		// fieldOfViewRadians:垂直视角，aspectRatio： X/Y
		 static Matrix4 SetPerspectiveFovMatrixRH(f32 fieldOfViewRadians, f32 aspectRatio, f32 zNear, f32 zFar)
		{
			Assert(Float::IsEqual(aspectRatio, 0.f)); //divide by zero
			Assert(Float::IsEqual(fieldOfViewRadians, 0.f)); //divide by zero
			Assert(Float::IsEqual(zNear, zFar)); //divide by zero

			// 默认视距d = 1
			f32 h = 1.0f / tan(fieldOfViewRadians / 2);		// 当前视角的视景体左右裁剪面与视角为90时左右裁剪面的截面宽度之比，
														// 实际公式为(d * tan(fieldOfViewRadians / 2)) / 
														// (d * tan(90 / 2))
			f32 w = h / aspectRatio;					// 根据比例计算当前视角的视景体上下裁剪面与视角为90时上下裁剪面的截面高度之比。
				

			// 此时顶点已经经过相机矩阵的转换，认为相机在原点，顶点在相机坐标系中

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

	// 正交投影
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

	// 阴影矩阵
		// 光源为点光源
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

		// 光源为平行光源
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

	// 相机坐标系转换
		//param - position	: 相机坐标
		//param - target	: 看着的目标点
		//param - upVector	: 垂直向量
		static Matrix4 SetCameraLookAtMatrixLH(
				const Vector3& position,
				const Vector3& target,
				const Vector3& upVector);

		static Matrix4 SetCameraLookAtMatrixRH(
				const Vector3& position,
				const Vector3& target,
				const Vector3& upVector);

		//param - position		: 相机坐标
		//param - orientation	: 看着的目标点
		//param - upVector		: 垂直向量
		static Matrix4 SetCameraOrientationMatrixLH(
				const Vector3& position,
				const Vector3& orientation,
				const Vector3& upVector);

		static Matrix4 SetCameraOrientationMatrixRH(
				const Vector3& position,
				const Vector3& orientation,
				const Vector3& upVector);

		static Matrix4 SetMatrixForNode(const Vector3& position, const Vector3& rotation, const Quaternion& orientation);

	//转换四元数与欧拉角
		EulerAngles Matrix4ToEulerAngles() const;

		Quaternion Matrix4ToQuaternion() const ;

		/// 第一列为X轴，第二列为Y轴，第三列为Z轴，第四列为W轴
		union 
		{
			f32 mM[4][4];
			f32 _mM[16];
		};
		
	};	// end class Matrix4

	extern const Matrix4 IdentityMatrix;

}	// end namespace dream

#endif	// end __MATRIX4_H__