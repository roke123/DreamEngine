#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "DreMathDeclaration.h"

#include "Angle.h"
#include "Matrix4.h"

namespace dream
{
	/** ��ͷ׵�壬���ڽ�����׵����㣬�Ӿ�Ϊ1 */
	class Frustum
	{
	public:
		/** Frustum���������Ϊ27������ */
		enum ClipPlane
		{
			NONR_CLIP	= 0x000000000,
			/// LEFT_CLIP��RIGHT_CLIP����
			LEFT_CLIP	= 0x000000001,		// ��Frustum���
			RIGHT_CLIP	= 0x000000002,		// ��Frustum�Ҳ�
			/// LEFT_CLIP��RIGHT_CLIP����
			BUTTOM_CLIP = 0x000000004,		// ��Frustum�²�
			TOP_CLIP	= 0x000000008,		// ��Frustum�ϲ�
			/// LEFT_CLIP��RIGHT_CLIP����
			NEAR_CLIP	= 0x000000010,		// ��Frustumǰ��
			FAR_CLIP	= 0x000000020,		// ��Frustum���

			ALL_CLIP	= LEFT_CLIP | RIGHT_CLIP | BUTTOM_CLIP | TOP_CLIP | NEAR_CLIP | FAR_CLIP,
		};

	public:
		/** ���캯�� */
		Frustum(f32 aspect, f32 near, f32 far, Radian fov) :
		//-------------------------------------------------------
		mAspect(aspect), mNearDist(near), mFarDist(far), mFov(fov),
			mRecaleProjectionMatrix(true)
		{
			// ����
		}

		/** ��ȡ��ƽ�泤���
		* @param	Aspect		= width / height
		*/
		f32 GetAspect() const { return mAspect; }
		/** ������ƽ�泤���
		* @param	Aspect		= width / height
		*/
		void SetAspect(f32 apsect) 
		{ 
			mRecaleProjectionMatrix = true; 
			mAspect = apsect; 
		}

		/** ��ȡ�����浽��ƽ����� */
		f32 GetNearClipDistance() const { return mNearDist; }
		/** ���ý����浽��ƽ����� */
		void SetNearClipDistance(f32 nearDist) 
		{ 
			mRecaleProjectionMatrix = true; 
			mNearDist = nearDist; 
		}
		
		/** ��ȡԶ���浽��ƽ����� */
		f32 GetFarClipDistance() const { return mFarDist; }
		/** ����Զ���浽��ƽ����� */
		void SetFarClipDistance(f32 farDist) 
		{ 
			mRecaleProjectionMatrix = true; 
			mFarDist = farDist; 
		}
		
		/** ��ȡ��Ұ */
		Radian GetFieldOfView() const { return mFov; }
		/** ������Ұ */
		void SetFieldOfView(const Radian& fov) 
		{ 
			mRecaleProjectionMatrix = true; 
			mFov = fov; 
		}

		/** ��ȡͶӰ�任���� */
		Matrix4 GetProjectionMatrix() const 
		{
			_CalculateProjectionMatrix();
			return mProjectionMatrix;
		}

		/** ����ĳ�������Ƿ���Frustum�� */
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

		/** ����ĳ��ײ���Ƿ���Frustum�� */
		bool TestInFrustum(const AABB3& boundBox, int* clipPlane = nullptr)
		{
			_CalculateProjectionMatrix();
			
			bool flag = false;

			// flag = this->TestInFrustum(boundBox.GetMin(), clipPlane) && this->TestInFrustum(boundBox.GetMax(), clipPlane)
			// ��ֹ��·��ֵ

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
		/// ��Ұ�����
		f32						mAspect;
		/// Զ���浽��ƽ�����
		f32						mFarDist;
		/// �����浽��ƽ�����
		f32						mNearDist;
		/// ��Ұ
		Radian					mFov;
		/// �Ƿ����¼���ͶӰ����
		mutable bool			mRecaleProjectionMatrix;
		/// ͶӰ����
		mutable Matrix4			mProjectionMatrix;
	};	// end class Frustum

}	// end namespace dream

#endif // end __FRUSTUM_H__
