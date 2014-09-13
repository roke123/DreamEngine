#ifndef __DREDEFAULTCAMERA_H__
#define __DREDEFAULTCAMERA_H__

#include "DreSceneManagerDeclaration.h"

#include "DreCamera.h"
#include "DreSceneNode.h"

namespace dream
{

	class DefaultCamera : public Camera
	{
		// 常量值定义
#		define DEFAULT_ASPECT				800.0f / 600.0f
#		define DEFALUT_NEAR_DIST			100.0f
#		define DEFALUT_FAR_DIST				1000.0f

	public:
		/** 构造函数
		* @param		name			相机名
		*
		* @param		position		相机世界坐标
		* @param		orientation		相机方向
		* @param		upVector		相机顶方向
		* 
		* @param		aspect			视野宽高比
		* @param		near			近截面，默认值为100
		* @param		far				远截面，默认值为1000
		* @param		fov				视角，默认值为90°
		*/
		DefaultCamera(const string& name, const Vector3& position, const Vector3& orientation, const Vector3 upVector,
			Radian fov, f32 aspect = DEFAULT_ASPECT, f32 near = DEFALUT_NEAR_DIST, f32 far = DEFALUT_FAR_DIST);

		/** 更新相机属性
		* @note			override by class Camera
		*/
		virtual void _UpdateCamera() override;

		/** 把对象绑定到某个节点 */
		virtual void _AttachedToSceneNode(SceneNodePtr& node) override;

		/** 把对象从绑定节点上解除绑定 */
		virtual void _DetachedToSceneNode() override;

	private:
		void _HandleSceneNodeUpdate(SceneNodePtr& node);

	protected:
		/** 计算相机变换矩阵
		* @note			override by class Camera
		*/
		virtual void _CalculateViewMatrix(const Vector3& position, const Vector3& orientation,
			const Vector3& upVector) const override
		{
			mViewMatrix = Matrix4::SetCameraOrientationMatrixLH(position, orientation, upVector);
		}

		/** 计算投影变换矩阵
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
