#ifndef __DREDEFAULTCAMERA_H__
#define __DREDEFAULTCAMERA_H__

#include "DreSceneManagerDeclaration.h"

#include "DreCamera.h"
#include "DreSceneNode.h"

namespace dream
{

	class DefaultCamera : public Camera
	{
		// ����ֵ����
#		define DEFAULT_ASPECT				800.0f / 600.0f
#		define DEFALUT_NEAR_DIST			100.0f
#		define DEFALUT_FAR_DIST				1000.0f

	public:
		/** ���캯��
		* @param		name			�����
		*
		* @param		position		�����������
		* @param		orientation		�������
		* @param		upVector		���������
		* 
		* @param		aspect			��Ұ��߱�
		* @param		near			�����棬Ĭ��ֵΪ100
		* @param		far				Զ���棬Ĭ��ֵΪ1000
		* @param		fov				�ӽǣ�Ĭ��ֵΪ90��
		*/
		DefaultCamera(const string& name, const Vector3& position, const Vector3& orientation, const Vector3 upVector,
			Radian fov, f32 aspect = DEFAULT_ASPECT, f32 near = DEFALUT_NEAR_DIST, f32 far = DEFALUT_FAR_DIST);

		/** �����������
		* @note			override by class Camera
		*/
		virtual void _UpdateCamera() override;

		/** �Ѷ���󶨵�ĳ���ڵ� */
		virtual void _AttachedToSceneNode(SceneNodePtr& node) override;

		/** �Ѷ���Ӱ󶨽ڵ��Ͻ���� */
		virtual void _DetachedToSceneNode() override;

	private:
		void _HandleSceneNodeUpdate(SceneNodePtr& node);

	protected:
		/** ��������任����
		* @note			override by class Camera
		*/
		virtual void _CalculateViewMatrix(const Vector3& position, const Vector3& orientation,
			const Vector3& upVector) const override
		{
			mViewMatrix = Matrix4::SetCameraOrientationMatrixLH(position, orientation, upVector);
		}

		/** ����ͶӰ�任����
		* @note			override by class Camera
		*/
		virtual void _CalculateProjectionMatrix(const Frustum& frustum) const override
		{
			frustum.GetProjectionMatrix();
		}

	private:
		SceneNode::SceneNodeEventHandler	mSceneNodeUpdateHandler;
	};	// end class DefaultCamera

}	// end namespace dream

#endif // end __DREDEFAULTCAMERA_H__
