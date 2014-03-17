#ifndef __DRECAMERA_H__
#define __DRECAMERA_H__

#include "DreSceneManagerDeclaration.h"
#include "DreMathDeclaration.h"

#include "DreConvertibleObject.h"
#include "DreMath.h"
#include "Matrix4.h"
#include "Frustum.h"

#include "DreRenderDeclaration.h"

namespace dream
{

	class Camera : public ConvertibleObject
	{
	public:
		/** 构造函数
		* @param		name			相机名
		*
		* @param		position		相机世界坐标
		* @param		orientation		相机方向
		* @param		upVector		相机顶方向
		* 
		* @param		aspect			视野宽高比
		* @param		near			近截面
		* @param		far				远截面
		* @param		fov				视角
		*/
		Camera(const string& name, const Vector3& position, const Vector3& orientation, const Vector3 upVector,
			f32 aspect, f32 near, f32 far, Radian fov);

		/** 虚析构函数 */
		virtual ~Camera() {};

		/** 取得相机变换矩阵 */
		Matrix4	GetViewMatrix();
		const Matrix4 GetViewMatrix() const;
		
		/** 取得相机坐标 */
		Vector3 GetCameraPosition() { return mPosition; };
		const Vector3 GetCameraPosition() const { return mPosition; };
		/** 设置相机坐标 */
		void SetCameraPosition(const Vector3& position);

		/** 取得相机方向 */
		Vector3 GetCameraOrientation() { return mOrientation; };
		const Vector3 GetCameraOrientation() const { return mOrientation; };
		/** 设置相机方向 */
		void SetCameraOrientation(const Vector3& orientation);

		/** 取得相机顶方向 */
		Vector3 GetCameraUpVector() { return mUpVector; };
		const Vector3 GetCameraUpVector() const { return mUpVector; };
		/** 设置相机顶方向 */
		void SetCameraUpVector(const Vector3& upVector);

		/** 取得相机投影变换矩阵 */
		Matrix4	GetProjectionMatrix();
		
		/** 取得相机长宽比 */
		f32 GetCameraAspect() { return mFrustum.GetAspect(); };
		const f32 GetCameraAspect() const { return mFrustum.GetAspect(); };
		/** 设置相机长宽比 */
		void SetCameraAspect(f32 aspect) { mRecaleProjectionMatrix = true; mFrustum.SetAspect(aspect); };

		/** 取得相机近截面 */
		f32 GetCameraNearPlane() { return mFrustum.GetNearClipDistance(); };
		const f32 GetCameraNearPlane() const { return mFrustum.GetNearClipDistance(); };
		/** 设置相机近截面 */
		void SetCameraNearPlane(f32 near){ mRecaleProjectionMatrix = true; mFrustum.SetNearClipDistance(near); };

		/** 取得相机远截面 */
		f32 GetCameraFarClipDistance() { return mFrustum.GetFarClipDistance(); };
		const f32 GetCameraFarClipDistance() const { return mFrustum.GetFarClipDistance(); };
		/** 设置相机顶远截面 */
		void SetCameraFarPlane(f32 far){ mRecaleProjectionMatrix = true; mFrustum.SetFarClipDistance(far); };

		/** 取得相机视角 */
		Radian GetCameraFieldOfView() { return mFrustum.GetFieldOfView(); };
		const Radian GetCameraFieldOfView() const { return mFrustum.GetFieldOfView(); };
		/** 设置相机视角 */
		void SetCameraFieldOfView(const Radian& fov){ mRecaleProjectionMatrix = true; mFrustum.SetFieldOfView(fov); };

		/** 更新相机属性 */
		virtual void _UpdateCamera() = 0;

		/** 测试某碰撞盒是否在Camera内 */
		bool TestInFrustum(const Vector3& position, int* clipPlanes = nullptr);

		/** 测试某碰撞盒是否在Camera内 */
		bool TestInFrustum(const AABB3& boundBox, int* clipPlanes = nullptr);

		/** 绑定一个RenderTarget到Camera上 */
		void BindRenderTargetToCamera(RenderTargetPtr& renderTarget) { mRenderTarget = renderTarget; };

		/** 取得Camera上绑定的RenderTarget */
		RenderTargetPtr GetBindRenderTarget() { return mRenderTarget; };

	protected:
		/** 计算相机变换矩阵 */
		virtual void _CalculateViewMatrix(const Vector3& position, const Vector3& orientation,
			const Vector3& upVector) const = 0;

		/** 计算投影变换矩阵 */
		virtual void _CalculateProjectionMatrix(const Frustum& frustum) const = 0;

	protected:
		/// 是否显示其椎体
		bool					mIsShowFrustum;
		
		/// 是否重新计算相机变换矩阵
		mutable bool			mRecaleViewMatrix;
		/// 相机坐标
		Vector3					mPosition;
		/// 相机方向
		Vector3					mOrientation;
		/// 相机顶方向
		Vector3					mUpVector;
		/// 相机变换矩阵
		mutable Matrix4			mViewMatrix;

		/// 是否重新计算ProjectionMatrix
		bool					mRecaleProjectionMatrix;
		/// 相机变换矩阵 * 投影变换矩阵
		mutable Matrix4			mViewProjectionMatrix;
		
		/// 视椎体
		Frustum					mFrustum;

		/// 渲染目标
		RenderTargetPtr			mRenderTarget;
	};	// end class DreCamera

}	// end namespace dream

#endif	//	end __DRECAMERA_H__