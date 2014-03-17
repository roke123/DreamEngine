#include "DreCamera.h"

namespace dream
{

	Camera::Camera(const string& name, const Vector3& position, const Vector3& orientation, const Vector3 upVector,
		f32 aspect, f32 near, f32 far, Radian fov) :
	//----------------------------------------------------------------------------------------------
	ConvertibleObject(name),
		mIsShowFrustum(false), 
		mRecaleViewMatrix(false), mPosition(position), mOrientation(orientation), mUpVector(upVector),
		mFrustum(aspect, near, far, fov),
		mRenderTarget(nullptr)
	{
		mOrientation.Normalize();
		mUpVector.Normalize();
	}

	/** 取得相机变换矩阵 */
	Matrix4	Camera::GetViewMatrix()
	{
		if(mRecaleViewMatrix)
		{
			// 重新计算相机变换矩阵
			_CalculateViewMatrix(mPosition, mOrientation, mUpVector);
			mRecaleViewMatrix = false;
		}
		return mViewMatrix;
	}

	const Matrix4 Camera::GetViewMatrix() const
	{
		if(mRecaleViewMatrix)
		{
			// 重新计算相机变换矩阵
			_CalculateViewMatrix(mPosition, mOrientation, mUpVector);
			mRecaleViewMatrix = false;
		}
		return mViewMatrix;
	}

	/** 设置相机坐标 */
	void Camera::SetCameraPosition(const Vector3& position)
	{
		mRecaleViewMatrix = true;
		mPosition = position;
	}

	/** 设置相机方向 */
	void Camera::SetCameraOrientation(const Vector3& orientation)
	{
		mRecaleViewMatrix = true;
		mOrientation = orientation;
		mOrientation.Normalize();
	}

	/** 设置相机顶方向 */
	void Camera::SetCameraUpVector(const Vector3& upVector)
	{
		mRecaleViewMatrix = true;
		mUpVector = upVector;
		mUpVector.Normalize();
	}

	/** 取得相机投影变换矩阵 */
	Matrix4	Camera::GetProjectionMatrix()
	{
		return mFrustum.GetProjectionMatrix();
	}

	bool Camera::TestInFrustum(const Vector3& position, int* clipPlanes = nullptr)
	{
		if (mRecaleViewMatrix || mRecaleProjectionMatrix)
		{
			mViewProjectionMatrix = GetViewMatrix() * GetProjectionMatrix();
		}

		Vector3 transfrom = position * mViewProjectionMatrix;
		int clipFlag = Frustum::NONR_CLIP;

		if (Float::LessThan(transfrom.mX, -position.mZ))
			clipFlag |= Frustum::LEFT_CLIP;
		else if (Float::GreaterThan(transfrom.mX, position.mZ))
			clipFlag |= Frustum::RIGHT_CLIP;

		if (Float::LessThan(transfrom.mY, -position.mZ))
			clipFlag |= Frustum::BUTTOM_CLIP;
		else if (Float::GreaterThan(transfrom.mY, position.mZ))
			clipFlag |= Frustum::TOP_CLIP;

		if (Float::LessThan(transfrom.mZ, -position.mZ))
			clipFlag |= Frustum::NEAR_CLIP;
		else if (Float::GreaterThan(transfrom.mZ, position.mZ))
			clipFlag = Frustum::FAR_CLIP;

		if (clipPlanes != nullptr)
			*clipPlanes = clipFlag;

		if(clipFlag == Frustum::NONR_CLIP)
			return true;

		return false;
	}

	bool Camera::TestInFrustum(const AABB3& boundBox, int* clipPlanes = nullptr)
	{
		bool flag = false;

		// flag = this->TestInFrustum(boundBox.GetMin(), clipPlane) && this->TestInFrustum(boundBox.GetMax(), clipPlane)
		// 防止短路求值

		flag = this->TestInFrustum(boundBox.GetMin(), clipPlane);
		flag = this->TestInFrustum(boundBox.GetMax(), clipPlane) && flag;

		return flag;
	}
}