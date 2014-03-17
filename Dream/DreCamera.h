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
		/** ���캯��
		* @param		name			�����
		*
		* @param		position		�����������
		* @param		orientation		�������
		* @param		upVector		���������
		* 
		* @param		aspect			��Ұ��߱�
		* @param		near			������
		* @param		far				Զ����
		* @param		fov				�ӽ�
		*/
		Camera(const string& name, const Vector3& position, const Vector3& orientation, const Vector3 upVector,
			f32 aspect, f32 near, f32 far, Radian fov);

		/** ���������� */
		virtual ~Camera() {};

		/** ȡ������任���� */
		Matrix4	GetViewMatrix();
		const Matrix4 GetViewMatrix() const;
		
		/** ȡ��������� */
		Vector3 GetCameraPosition() { return mPosition; };
		const Vector3 GetCameraPosition() const { return mPosition; };
		/** ����������� */
		void SetCameraPosition(const Vector3& position);

		/** ȡ��������� */
		Vector3 GetCameraOrientation() { return mOrientation; };
		const Vector3 GetCameraOrientation() const { return mOrientation; };
		/** ����������� */
		void SetCameraOrientation(const Vector3& orientation);

		/** ȡ����������� */
		Vector3 GetCameraUpVector() { return mUpVector; };
		const Vector3 GetCameraUpVector() const { return mUpVector; };
		/** ������������� */
		void SetCameraUpVector(const Vector3& upVector);

		/** ȡ�����ͶӰ�任���� */
		Matrix4	GetProjectionMatrix();
		
		/** ȡ���������� */
		f32 GetCameraAspect() { return mFrustum.GetAspect(); };
		const f32 GetCameraAspect() const { return mFrustum.GetAspect(); };
		/** ������������ */
		void SetCameraAspect(f32 aspect) { mRecaleProjectionMatrix = true; mFrustum.SetAspect(aspect); };

		/** ȡ����������� */
		f32 GetCameraNearPlane() { return mFrustum.GetNearClipDistance(); };
		const f32 GetCameraNearPlane() const { return mFrustum.GetNearClipDistance(); };
		/** ������������� */
		void SetCameraNearPlane(f32 near){ mRecaleProjectionMatrix = true; mFrustum.SetNearClipDistance(near); };

		/** ȡ�����Զ���� */
		f32 GetCameraFarClipDistance() { return mFrustum.GetFarClipDistance(); };
		const f32 GetCameraFarClipDistance() const { return mFrustum.GetFarClipDistance(); };
		/** ���������Զ���� */
		void SetCameraFarPlane(f32 far){ mRecaleProjectionMatrix = true; mFrustum.SetFarClipDistance(far); };

		/** ȡ������ӽ� */
		Radian GetCameraFieldOfView() { return mFrustum.GetFieldOfView(); };
		const Radian GetCameraFieldOfView() const { return mFrustum.GetFieldOfView(); };
		/** ��������ӽ� */
		void SetCameraFieldOfView(const Radian& fov){ mRecaleProjectionMatrix = true; mFrustum.SetFieldOfView(fov); };

		/** ����������� */
		virtual void _UpdateCamera() = 0;

		/** ����ĳ��ײ���Ƿ���Camera�� */
		bool TestInFrustum(const Vector3& position, int* clipPlanes = nullptr);

		/** ����ĳ��ײ���Ƿ���Camera�� */
		bool TestInFrustum(const AABB3& boundBox, int* clipPlanes = nullptr);

		/** ��һ��RenderTarget��Camera�� */
		void BindRenderTargetToCamera(RenderTargetPtr& renderTarget) { mRenderTarget = renderTarget; };

		/** ȡ��Camera�ϰ󶨵�RenderTarget */
		RenderTargetPtr GetBindRenderTarget() { return mRenderTarget; };

	protected:
		/** ��������任���� */
		virtual void _CalculateViewMatrix(const Vector3& position, const Vector3& orientation,
			const Vector3& upVector) const = 0;

		/** ����ͶӰ�任���� */
		virtual void _CalculateProjectionMatrix(const Frustum& frustum) const = 0;

	protected:
		/// �Ƿ���ʾ��׵��
		bool					mIsShowFrustum;
		
		/// �Ƿ����¼�������任����
		mutable bool			mRecaleViewMatrix;
		/// �������
		Vector3					mPosition;
		/// �������
		Vector3					mOrientation;
		/// ���������
		Vector3					mUpVector;
		/// ����任����
		mutable Matrix4			mViewMatrix;

		/// �Ƿ����¼���ProjectionMatrix
		bool					mRecaleProjectionMatrix;
		/// ����任���� * ͶӰ�任����
		mutable Matrix4			mViewProjectionMatrix;
		
		/// ��׵��
		Frustum					mFrustum;

		/// ��ȾĿ��
		RenderTargetPtr			mRenderTarget;
	};	// end class DreCamera

}	// end namespace dream

#endif	//	end __DRECAMERA_H__