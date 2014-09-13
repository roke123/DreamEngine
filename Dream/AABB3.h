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
	//构造函数
		AABB3() : mMin(0, 0, 0), mMax(0, 0, 0), mType(AABB3_NULL_TYPE)
		{
			// 留空
		}

		AABB3(const Vector3& min, const Vector3& max) : 
			mMin(min), mMax(max), mType(AABB3_FINITE_TYPE)
		{
			// 留空
		}

		AABB3(void*) : 
			mMin(MIN_F32, MIN_F32, MIN_F32),
			mMax(MAX_F32, MAX_F32, MAX_F32),
			mType(AABB3_INFINITE_TYPE)
		{
			// 留空
		}

	//Debug测试
		inline bool IsLegal() const
		{
			return mMin.mX < mMax.mX && mMin.mY < mMax.mY && mMin.mZ < mMax.mZ;
		}

	// 基本操作
		// 设置最小点
		inline void SetMin(f32 x, f32 y, f32 z)
		{
			mMin.mX = x; mMin.mY = y; mMin.mZ = z;
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		// 设置最小点
		inline void SetMin(const Vector3& min)
		{
			mMin = min;
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		/** 获取最小点 */
		inline Vector3 GetMin() const { return mMin; };

		// 设置最大点
		inline void SetMax(f32 x, f32 y, f32 z)
		{
			mMax.mX = x; mMax.mY = y; mMax.mZ = z;
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		// 设置最大点
		inline void SetMax(const Vector3& max)
		{
			mMax = max; 
			mType = AABB3_FINITE_TYPE;

			Assert(IsLegal());
		}
		/** 获取最小点 */
		inline Vector3 GetMax() const { return mMax; };

		inline void Infinite()
		{
			mMin.mX = mMin.mY = mMin.mZ = MIN_F32;
			mMax.mX = mMax.mY = mMax.mZ = MAX_F32; 
			mType = AABB3_INFINITE_TYPE;
		}

		// 清空碰撞盒
		inline void Empty()
		{
			mMin.mX = mMin.mY = mMin.mZ = 0;
			mMax.mX = mMax.mY = mMax.mZ = 0; 
			mType = AABB3_NULL_TYPE;
		}

		// 判断碰撞盒是否空的
		inline bool IsEmpty() const
		{
			return mType == AABB3_NULL_TYPE;
		}

		// 判断碰撞盒为无限大的
		inline bool IsInfinite() const
		{
			return mType == AABB3_INFINITE_TYPE;
		}

		// 向碰撞盒中加入一个点
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

		// 向碰撞盒中增加碰撞盒
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

		// 返回碰撞盒中心点
		inline Vector3 Center() const
		{
			return (mMin + mMax) / 2;
		}

		// 返回八个顶点中其中一个,使用左手坐标轴
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
				// 在右侧还是在左侧
				(i & 1) ? mMax.mX : mMin.mX,
				// 在上侧还是在下侧
				(i & 2) ? mMax.mY : mMin.mY,
				// 在后侧还是前侧
				(i & 4) ? mMax.mZ : mMin.mZ
				);
		}

	// 碰撞/包含检测
		// 测试点是否包含在碰撞盒内
		inline bool PointIntersect(const Vector3& v) const
		{
			return (v.mX >= mMin.mX) && (v.mX <= mMax.mX) &&
				(v.mY >= mMin.mY) && (v.mY <= mMax.mY) &&
				(v.mZ >= mMin.mZ) && (v.mZ <= mMax.mZ);
		}

		// 测试两个碰撞盒是否相交,可选返回碰撞盒相交部分
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

		// 测试碰撞盒是否与平面相交,
		// 可选param - returnState碰撞盒在平面前返回1，平面后返回-1，与平面相交返回0
		bool PlaneIntersect(const Plane& p, int* returnState = NULL) const
		{
			if(IsEmpty())
				return false;
			if(IsInfinite())
			{
				if(returnState != nullptr) *returnState = 0;
				return true;
			}

			// minD碰撞盒上在平面法向量方向上较后点
			//maxD碰撞盒上在平面法向量方向上较前点
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

		// 测试射线是否与碰撞盒相交,param - returnNormal可选，用于返回相交点
		// 如returnNormal0被选用，返回值有以下几种可能
		// 1： return - false, returnNormal - 原值 情况：射线在碰撞盒外
		// 2： return - true , returnNormal - 原值 情况：射线在碰撞盒内
		// 3： return - true , retrunNormal - 非原值 情况：射线与碰撞盒相交于一点
		//			retrunNormal0 - 靠近start, returnNormal1 - 靠近end
		bool RayIntersect(const Line3& l, Vector3* returnNormal = NULL) const
		{
			if(IsEmpty())
				return false;
			if(IsInfinite())
				return true;

			bool inside = true;
			f32 rayLenght = l.GetLength();

			// 计算碰撞盒左右两侧（X轴）
			f32 xt = 0.0f;
			// start点在碰撞盒左侧
			if(l.start_.mX < mMin.mX) {
				// 射线在碰撞盒外
				if(l.end_.mX < mMin.mX)
					return false;

				// 计算左侧面到start的距离与射线距离的比值
				xt = (mMin.mX - l.start_.mX) / rayLenght;
				// 说明直线不在碰撞盒内
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

			// 计算碰撞盒上下两侧（Y轴）
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

			// 计算碰撞盒前后两侧（Z轴）
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

			//是否在碰撞盒内
			if(inside)
				return true;


			//选择最远平面 - 发生相交的地方
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
				// 与yz平面相交
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

				// 与xz平面相交
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

				// 与xy平面相交
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

	// 标准操作
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
		/// AABB3盒类型
		DRE_AABB3_TYPE mType;

	public:
		static const AABB3 EmptyAABB3;
		static const AABB3 InfiniteAABB3;

	};	// end class AABB3

}

#endif	// end _AABB3_H__