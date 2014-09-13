#include "DreDefaultCamera.h"

#include "DreSceneNode.h"
#include <functional>

namespace dream
{

	DefaultCamera::DefaultCamera(const string& name, const Vector3& position, const Vector3& orientation, const Vector3 upVector,
		Radian fov, f32 aspect, f32 near, f32 far) :
	//---------------------------------------------------------------------------------------------------
	Camera(name, position, orientation, upVector, aspect, near, far, fov),
		mSceneNodeUpdateHandler(bind(&DefaultCamera::_HandleSceneNodeUpdate, this, _1))
	{
		// ����
	}

	/** �����������
	* @note			override by class Camera
	*/
	void DefaultCamera::_UpdateCamera()
	{
		if(mRecaleViewMatrix)
		{
			// ���¼�������任����
			_CalculateViewMatrix(mPosition, mOrientation, mUpVector);
			mRecaleViewMatrix = false;
		}

		/*if(mRecaleProjectMatrix)
		{
			// ���¼���ͶӰ�任����
			_CalculateProjectMatrix(mFrustum);
			mRecaleProjectMatrix = false;
		}*/
	}

	/** �Ѷ���󶨵�ĳ���ڵ� */
	void DefaultCamera::_AttachedToSceneNode(SceneNodePtr& node) 
	{
		// ���Node��
		node->OnUpdateNode.Insert(&mSceneNodeUpdateHandler);
		Camera::_AttachedToSceneNode(node);
	}

	/** �Ѷ���Ӱ󶨽ڵ��Ͻ���� */
	void DefaultCamera::_DetachedToSceneNode() 
	{
		GetBindingNode()->OnUpdateNode.Remove(&mSceneNodeUpdateHandler);
		Camera::_DetachedToSceneNode();
	}

	void DefaultCamera::_HandleSceneNodeUpdate(SceneNodePtr& node)
	{
		Matrix4 worldMatrix = node->GetWorldMatrix();
		// ת���������
		this->SetCameraPosition(this->GetCameraPosition() * worldMatrix);
		this->SetCameraOrientation(this->GetCameraOrientation() * worldMatrix);
		this->SetCameraUpVector(this->GetCameraUpVector() * worldMatrix);
	}

}	// end namespace dream