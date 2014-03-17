#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "DreMathDeclaration.h"

#include "Angle.h"
#include "Matrix4.h"

namespace dream
{
	/** 截头椎体，用于进行视椎体计算，视距为1 */
	class Frustum
	{
	public:
		/** Frustum的六个面分为27各部分 */
		enum ClipPlane
		{
			NONR_CLIP	= 0x000000000,
			/// LEFT_CLIP与RIGHT_CLIP互斥
			LEFT_CLIP	= 0x000000001,		// 在Frustum左侧
			RIGHT_CLIP	= 0x000000002,		// 在Frustum右侧
			/// LEFT_CLIP与RIGHT_CLIP互斥
			BUTTOM_CLIP = 0x000000004,		// 在Frustum下侧
			TOP_CLIP	= 0x000000008,		// 在Frustum上侧
			/// LEFT_CLIP与RIGHT_CLIP互斥
			NEAR_CLIP	= 0x000000010,		// 在Frustum前侧
			FAR_CLIP	= 0x000000020,		// 在Frustum后侧

			ALL_CLIP	= LEFT_CLIP | RIGHT_CLIP | BUTTOM_CLIP | TOP_CLIP | NEAR_CLIP | FAR_CLIP,
		};

	public:
		/** 构造函数 */
		Frustum(f32 aspect, f32 near, f32 far, Radian fov) :
		//-------------------------------------------------------
		mAspect(aspect), mNearDist(near), mFarDist(far), mFov(fov),
			mRecaleProjectionMatrix(true)
		{
			// 留空
		}

		/** 获取视平面长宽比
		* @param	Aspect		= width / height
		*/
		f32 GetAspect() const { return mAspect; }
		/** 设置视平面长宽比
		* @param	Aspect		= width / height
		*/
		void SetAspect(f32 apsect) 
		{ 
			mRecaleProjectionMatrix = true; 
			mAspect = apsect; 
		}

		/** 获取近截面到视平面距离 */
		f32 GetNearClipDistance() const { return mNearDist; }
		/** 设置近截面到视平面距离 */
		void SetNearClipDistance(f32 nearDist) 
		{ 
			mRecaleProjectionMatrix = true; 
			mNearDist = nearDist; 
		}
		
		/** 获取远截面到视平面距离 */
		f32 GetFarClipDistance() const { return mFarDist; }
		/** 设置远截面到视平面距离 */
		void SetFarClipDistance(f32 farDist) 
		{ 
			mRecaleProjectionMatrix = true; 
			mFarDist = farDist; 
		}
		
		/** 获取视野 */
		Radian GetFieldOfView() const { return mFov; }
		/** 设置视野 */
		void SetFieldOfView(const Radian& fov) 
		{ 
			mRecaleProjectionMatrix = true; 
			mFov = fov; 
		}

		/** 获取投影变换矩阵 */
		Matrix4 GetProjectionMatrix() const 
		{
			_CalculateProjectionMatrix();
			return mProjectionMatrix;
		}

		/** 测试某点坐标是否在Frustum内 */
		bool TestInFrustum(const Vector3& position, int* clipPlanes = nullptr)
		{
			_CalculateProjectionMatrix();
			
			Vector3 transfrom = position * mProjectionMatrix;
			int clipFlag = NONR_CLIP;

			if (Float::LessThan(transfrom.mX, -position.mZ))
				clipFlag |= LEFT_CLIP;
			else if (Float::GreaterThan(transfrom.mX, position.mZ))
				clipFlag |= RIGHT_CLIP;

			if (Float::LessThan(transfrom.mY, -position.mZ))
				clipFlag |= BUTTOM_CLIP;
			else if (Float::GreaterThan(transfrom.mY, position.mZ))
				clipFlag |= TOP_CLIP;

			if (Float::LessThan(transfrom.mZ, -position.mZ))
				clipFlag |= NEAR_CLIP;
			else if (Float::GreaterThan(transfrom.mZ, position.mZ))
				clipFlag = FAR_CLIP;

			if (clipPlanes != nullptr)
				*clipPlanes = clipFlag;

			if(clipFlag == NONR_CLIP)
				return true;

			return false;
		}

		/** 测试某碰撞盒是否在Frustum内 */
		bool TestInFrustum(const AABB3& boundBox, int* clipPlane = nullptr)
		{
			_CalculateProjectionMatrix();
			
			bool flag = false;

			// flag = this->TestInFrustum(boundBox.GetMin(), clipPlane) && this->TestInFrustum(boundBox.GetMax(), clipPlane)
			// 防止短路求值

			flag = this->TestInFrustum(boundBox.GetMin(), clipPlane);
			flag = this->TestInFrustum(boundBox.GetMax(), clipPlane) && flag;

			return flag;
		}

	private:
		void _CalculateProjectionMatrix() const
		{
			if (mRecaleProjectionMatrix)
			{
				mProjectionMatrix = Matrix4::SetPerspectiveFovMatrixLH(mFov, mAspect, mNearDist, mFarDist);
				mRecaleProjectionMatrix = false;
			}
		}

	private:
		/// 视野长宽比
		f32						mAspect;
		/// 远截面到视平面距离
		f32						mFarDist;
		/// 近截面到视平面距离
		f32						mNearDist;
		/// 视野
		Radian					mFov;
		/// 是否重新计算投影矩阵
		mutable bool			mRecaleProjectionMatrix;
		/// 投影矩阵
		mutable Matrix4			mProjectionMatrix;
	};	// end class Frustum

}	// end namespace dream

#endif // end __FRUSTUM_H__
