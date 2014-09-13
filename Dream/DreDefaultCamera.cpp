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
		// 留空
	}

	/** 更新相机属性
	* @note			override by class Camera
	*/
	void DefaultCamera::_UpdateCamera()
	{
		if(mRecaleViewMatrix)
		{
			// 重新计算相机变换矩阵
			_CalculateViewMatrix(mPosition, mOrientation, mUpVector);
			mRecaleViewMatrix = false;
		}

		/*if(mRecaleProjectMatrix)
		{
			// 重新计算投影变换矩阵
			_CalculateProjectMatrix(mFrustum);
			mRecaleProjectMatrix = false;
		}*/
	}

	/** 把对象绑定到某个节点 */
	void DefaultCamera::_AttachedToSceneNode(SceneNodePtr& node) 
	{
		// 添加Node的
		node->OnUpdateNode.Insert(&mSceneNodeUpdateHandler);
		Camera::_AttachedToSceneNode(node);
	}

	/** 把对象从绑定节点上解除绑定 */
	void DefaultCamera::_DetachedToSceneNode() 
	{
		GetBindingNode()->OnUpdateNode.Remove(&mSceneNodeUpdateHandler);
		Camera::_DetachedToSceneNode();
	}

	void DefaultCamera::_HandleSceneNodeUpdate(SceneNodePtr& node)
	{
		Matrix4 worldMatrix = node->GetWorldMatrix();
		// 转换相机属性
		this->SetCameraPosition(this->GetCameraPosition() * worldMatrix);
		this->SetCameraOrientation(this->GetCameraOrientation() * worldMatrix);
		this->SetCameraUpVector(this->GetCameraUpVector() * worldMatrix);
	}

}	// end namespace dream