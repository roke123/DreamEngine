#ifndef __AABB3_H__
#define __AABB3_H__

#include "DreMathDeclaration.h"

#include "Matrix4.h"
#include "Vector3.h"
#include "Plane.h"
#include "Line3.h"

namespace dream
{
	enum DRE_AABB3_TYPE
	{
		AABB3_NULL_TYPE,
		AABB3_FINITE_TYPE,
		AABB3_INFINITE_TYPE,
	};

	class AABB3
	{
	public:
	//���캯��
		AABB3() : mMin(0, 0, 0), mMax(0, 0, 0), mType(AABB3_NULL_TYPE)
		{
			// ����
		}

		AABB3(const Vector3& min, const Vector3& max) : 
			mMin(min), mMax(max), mType(AABB3_FINITE_TYPE)
		{
			// ����
		}

		AABB3(void*) : 
			mMin(MIN_F32, MIN_F32, MIN_F32),
			mMax(MAX_F32, MAX_F32, MAX_F32),
			mType(AABB3_INFINITE_TYPE)
		{
			// ����
		}

	//Debug����
		inline bool IsLegal() const
		{
			return mMin.mX < mMax.mX && mMin.mY < mMax.mY && mMin.mZ < mMax.mZ;
		}

	// ��������
		// ������С��
		inline void SetMin(f32 x, f32 y, f32 z)
		{
			mMin.mX = x; mMin.mY = y; mMin.mZ = z;
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		// ������С��
		inline void SetMin(const Vector3& min)
		{
			mMin = min;
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		/** ��ȡ��С�� */
		inline Vector3 GetMin() const { return mMin; };

		// ��������
		inline void SetMax(f32 x, f32 y, f32 z)
		{
			mMax.mX = x; mMax.mY = y; mMax.mZ = z;
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		// ��������
		inline void SetMax(const Vector3& max)
		{
			mMax = max; 
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		/** ��ȡ��С�� */
		inline Vector3 GetMax() const { return mMax; };

		inline void Infinite()
		{
			mMin.mX = mMin.mY = mMin.mZ = MIN_F32;
			mMax.mX = mMax.mY = mMax.mZ = MAX_F32; 
			mType = AABB3_INFINITE_TYPE;
		}

		// �����ײ��
		inline void Empty()
		{
			mMin.mX = mMin.mY = mMin.mZ = 0;
			mMax.mX = mMax.mY = mMax.mZ = 0; 
			mType = AABB3_NULL_TYPE;
		}

		// �ж���ײ���Ƿ�յ�
		inline bool IsEmpty() const
		{
			return mType == AABB3_NULL_TYPE;
		}

		// �ж���ײ��Ϊ���޴��
		inline bool IsInfinite() const
		{
			return mType == AABB3_INFINITE_TYPE;
		}

		// ����ײ���м���һ����
		inline void AddPoint(const Vector3& v)
		{
			if(v.mX < mMin.mX) mMin.mX = v.mX;
			if(v.mX > mMax.mX) mMax.mX = v.mX;
			if(v.mY < mMin.mY) mMin.mY = v.mY;
			if(v.mY > mMax.mY) mMax.mY = v.mY;
			if(v.mZ < mMin.mZ) mMin.mZ = v.mZ;
			if(v.mZ > mMax.mZ) mMax.mZ = v.mZ;

			mType = AABB3_FINITE_TYPE;
		}

		// ����ײ����������ײ��
		inline void AddAABB3(const AABB3& box)
		{
			if(box.IsEmpty() || IsInfinite())
				return;
			if(box.IsInfinite()) {
				this->Infinite();
				return;
			}
			if(IsEmpty()) {
				mMin.mX = box.mMin.mX; mMin.mY = box.mMin.mY; mMin.mZ = box.mMin.mZ;
				mMax.mX = box.mMax.mX; mMax.mY = box.mMax.mY; mMax.mZ = box.mMax.mZ;
				mType = AABB3_INFINITE_TYPE;
				return;
			}

			mType = AABB3_FINITE_TYPE;

			if(box.mMin.mX < mMin.mX) mMin.mX = box.mMin.mX;
			if(box.mMax.mX > mMax.mX) mMax.mX = box.mMax.mX;
			if(box.mMin.mY < mMin.mY) mMin.mY = box.mMin.mY;
			if(box.mMax.mY > mMax.mY) mMax.mY = box.mMax.mY;
			if(box.mMin.mZ < mMin.mZ) mMin.mZ = box.mMin.mZ;
			if(box.mMax.mZ > mMax.mZ) mMax.mZ = box.mMax.mZ;
		}

		// ������ײ�����ĵ�
		inline Vector3 Center() const
		{
			return (mMin + mMax) / 2;
		}

		// ���ذ˸�����������һ��,ʹ������������
		//
		// AABB::GetPoint
		//
		//
		//
		//	     6----------------------7
		//	     /|                   /|
		//	    / |				     / |
		//	   /  |                 /  |  
		//	  /	  | 			   /   |
		//	 /    |				  /    |
		//	2----------------------3   |
		//	 |    |               |	   |
		//	 |    |               |    |  
		//	 |    |               |    |  
		//	 |   4----------------------5
		//	 |    /               |    /
		//	 |   /                |   /
		//	 |  /                 |  /
		//	 | /                  | /
		//	 |/                   |/
		//	 ----------------------
		//	 0                    1
		//
		//
		//
		inline Vector3 GetPoint(u32 i) const
		{
			Assert(i >= 0);
			Assert(i <= 7);

			return Vector3(
				// ���Ҳ໹�������
				(i & 1) ? mMax.mX : mMin.mX,
				// ���ϲ໹�����²�
				(i & 2) ? mMax.mY : mMin.mY,
				// �ں�໹��ǰ��
				(i & 4) ? mMax.mZ : mMin.mZ
				);
		}

	// ��ײ/�������
		// ���Ե��Ƿ��������ײ����
		inline bool PointIntersect(const Vector3& v) const
		{
			return (v.mX >= mMin.mX) && (v.mX <= mMax.mX) &&
				(v.mY >= mMin.mY) && (v.mY <= mMax.mY) &&
				(v.mZ >= mMin.mZ) && (v.mZ <= mMax.mZ);
		}

		// ����������ײ���Ƿ��ཻ,��ѡ������ײ���ཻ����
		inline bool AABBIntersect(const AABB3& box, AABB3* returnBox = NULL) const
		{
			if(IsEmpty() || box.IsEmpty())
				return false;
			if(IsInfinite())
			{
				if(returnBox != nullptr) *returnBox = box;
				return true;
			}
			if(box.IsInfinite())
			{
				if(returnBox != nullptr) *returnBox = *this;
				return true;
			}

			if(mMin.mX > box.mMax.mX) return false;
			if(mMin.mY > box.mMax.mY) return false;
			if(mMin.mZ > box.mMax.mZ) return false;
			if(mMax.mX < box.mMin.mX) return false;
			if(mMax.mY < box.mMin.mY) return false;
			if(mMax.mZ < box.mMin.mZ) return false;

			if(returnBox != NULL)
			{
				returnBox->mMin.mX = Max(mMin.mX, box.mMin.mX);
				returnBox->mMin.mY = Max(mMin.mY, box.mMin.mY);
				returnBox->mMin.mZ = Max(mMin.mZ, box.mMin.mZ);
				returnBox->mMax.mX = Min(mMax.mX, box.mMax.mX);
				returnBox->mMax.mY = Min(mMax.mY, box.mMax.mY);
				returnBox->mMax.mZ = Min(mMax.mZ, box.mMax.mZ);
			}
		}

		// ������ײ���Ƿ���ƽ���ཻ,
		// ��ѡparam - returnState��ײ����ƽ��ǰ����1��ƽ��󷵻�-1����ƽ���ཻ����0
		bool PlaneIntersect(const Plane& p, int* returnState = NULL) const
		{
			if(IsEmpty())
				return false;
			if(IsInfinite())
			{
				if(returnState != nullptr) *returnState = 0;
				return true;
			}

			// minD��ײ������ƽ�淨���������ϽϺ��
			//maxD��ײ������ƽ�淨���������Ͻ�ǰ��
			Vector3 minD, maxD;

			if(p.n_.mX > 0.0f) { 
				minD.mX = mMin.mX; maxD.mX = mMax.mX; 
			}
			else {
				maxD.mX = mMin.mX; minD.mX = mMax.mX; 
			}

			if(p.n_.mY > 0.0f) {
				minD.mY = mMin.mY; maxD.mY = mMax.mY; 
			}
			else {
				maxD.mY = mMin.mY; minD.mY = mMax.mY; 
			}

			if(p.n_.mZ > 0.0f) {
				minD.mZ = mMin.mZ; maxD.mZ = mMax.mZ; 
			}
			else {
				maxD.mZ = mMin.mZ; minD.mZ = mMax.mZ; 
			}

			if (Dot(p.n_, minD) > p.d_)
			{
				if(returnState != NULL)
					*returnState = 1;

				return false;
			}

			if (Dot(p.n_, maxD) < p.d_)
			{
				if(returnState != NULL)
					*returnState = -1;

				return false;
			}

			if(returnState != NULL)
					*returnState = 0;

			return true;
		}

		// ���������Ƿ�����ײ���ཻ,param - returnNormal��ѡ�����ڷ����ཻ��
		// ��returnNormal0��ѡ�ã�����ֵ�����¼��ֿ���
		// 1�� return - false, returnNormal - ԭֵ �������������ײ����
		// 2�� return - true , returnNormal - ԭֵ �������������ײ����
		// 3�� return - true , retrunNormal - ��ԭֵ �������������ײ���ཻ��һ��
		//			retrunNormal0 - ����start, returnNormal1 - ����end
		bool RayIntersect(const Line3& l, Vector3* returnNormal = NULL) const
		{
			if(IsEmpty())
				return false;
			if(IsInfinite())
				return true;

			bool inside = true;
			f32 rayLenght = l.GetLength();

			// ������ײ���������ࣨX�ᣩ
			f32 xt = 0.0f;
			// start������ײ�����
			if(l.start_.mX < mMin.mX) {
				// ��������ײ����
				if(l.end_.mX < mMin.mX)
					return false;

				// ��������浽start�ľ��������߾���ı�ֵ
				xt = (mMin.mX - l.start_.mX) / rayLenght;
				// ˵��ֱ�߲�����ײ����
				inside = false;
			}
			else if(l.start_.mX > mMax.mX) {
				if(l.end_.mX > mMax.mX)
					return false;

				xt = (mMax.mX - l.start_.mX) / rayLenght;
				inside = false;
			}
			else {
				xt = -1.0f;
			}

			// ������ײ���������ࣨY�ᣩ
			f32 yt;
			if(l.start_.mY < mMin.mY) {
				if(l.end_.mY < mMin.mY)
					return false;

				yt = (mMin.mY - l.start_.mY) / rayLenght;
				inside = false;
			}
			else if(l.start_.mY > mMax.mY) {
				if(l.end_.mY > mMax.mY)
					return false;

				yt = (mMax.mY - l.start_.mY) / rayLenght;
				inside = false;
			}
			else {
				yt = -1.0f;
			}

			// ������ײ��ǰ�����ࣨZ�ᣩ
			f32 zt;
			if(l.start_.mZ < mMin.mZ) {
				if(l.end_.mZ < mMin.mZ)
					return false;

				zt = (mMin.mZ - l.start_.mZ) / rayLenght;
			}
			else if(l.start_.mZ > mMax.mZ) {
				if(l.end_.mZ > mMax.mZ)
					return false;

				zt = (mMax.mZ - l.start_.mZ) / rayLenght;
				inside = false;
			}
			else {
				zt = -1.0f;
			}

			//�Ƿ�����ײ����
			if(inside)
				return true;


			//ѡ����Զƽ�� - �����ཻ�ĵط�
			int which = 0;
			float t = xt;
			if(yt > t)
			{
				which = 1;
				t = yt;
			}
			if(zt > t)
			{
				which = 2;
				t = zt;
			}

			switch(which)
			{
				// ��yzƽ���ཻ
				case 0 :
				{
					f32 y = l.start_.mY + rayLenght * t;
					if(y < mMin.mY && y > mMax.mY)
						return false;
					f32 z = l.start_.mZ + rayLenght * t;
					if(z < mMin.mZ && z > mMax.mZ)
						return false;
					if(returnNormal != NULL)
					{
						returnNormal->mX = l.start_.mX + rayLenght * t;
						returnNormal->mY = y;
						returnNormal->mZ = z;
					}
				}
				break;

				// ��xzƽ���ཻ
				case 1 :
				{
					f32 x = l.start_.mX + rayLenght * t;
					if(x < mMin.mX && x > mMax.mX)
						return false;
					f32 z = l.start_.mZ + rayLenght * t;
					if(z < mMin.mZ && z > mMax.mZ)
						return false;
					if(returnNormal != NULL)
					{
						returnNormal->mX = x;
						returnNormal->mY = l.start_.mY + rayLenght * t;
						returnNormal->mZ = z;
					}
				}
				break;

				// ��xyƽ���ཻ
				case 2 :
				{
					f32 x = l.start_.mX + rayLenght * t;
					if(x < mMin.mX && x > mMax.mX)
						return false;
					f32 y = l.start_.mY + rayLenght * t;
					if(y < mMin.mY && y > mMax.mZ)
						return false;
					if(returnNormal != NULL)
					{
						returnNormal->mX = x;
						returnNormal->mY = y;
						returnNormal->mZ = l.start_.mZ + rayLenght * t;
					}
				}
				break;
			}

			return true;
		}

	// ��׼����
		inline bool operator == (const AABB3& box) const
		{
			if(mType == AABB3_FINITE_TYPE && mType == AABB3_FINITE_TYPE)
				return mMin == box.mMin && mMax == box.mMax;
			else
				return mType == box.mType;
		}

		inline bool operator != (const AABB3& box) const
		{
			if(mType == AABB3_FINITE_TYPE && mType == AABB3_FINITE_TYPE)
				return mMin != box.mMin || mMax != box.mMax;
			else
				return mType != box.mType;
		}

		inline AABB3 operator * (const Matrix4& m) const
		{
			if(IsEmpty())
				return EmptyAABB3;
			if(IsInfinite())
				return InfiniteAABB3;

			AABB3 temp(mMin * m, mMax * m);
			return temp;
		}

		inline AABB3 operator *= (const Matrix4& m)
		{
			if(IsEmpty())
				return EmptyAABB3;
			if(IsInfinite())
				return InfiniteAABB3;

			mMin *= m;
			mMax *= m;

			return *this;
		}

	private:
		Vector3 mMin, mMax;
		/// AABB3������
		DRE_AABB3_TYPE mType;

	public:
		static const AABB3 EmptyAABB3;
		static const AABB3 InfiniteAABB3;

	};	// end class AABB3

}

#endif	// end _AABB3_H__