#ifndef __DRENODE_H__
#define __DRENODE_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	/** 基本节点
	*/
	class Node
	{
	public:
		/** 析构函数
		*/
		virtual ~Node() {}; 
		
		/** 取得最终坐标 */
		virtual Vector3 _GetFinalPosition() = 0;;
		/** 取得最终方向 */
		virtual Quaternion _GetFinalOrientation() = 0;
		/** 取得最终Scale */
		virtual Vector3 _GetFinalScale() = 0;

		/** 获取转换矩阵 */
		virtual Matrix4 GetWorldMatrix() = 0;

		/** 通知父节点需要更新 */
		virtual void _NotifyNeedUpdate() = 0;

		/** 渲染流程前更新节点，计算当前节点属性 */
		virtual void _PreRenderUpdate() = 0;

		/** 渲染流程后更新节点，计算当前节点属性 */
		virtual void _PostRenderUpdate() = 0;

		/** 逻辑更新节点 */
		virtual void _FixedUpdate() = 0;

		/** 取得碰撞盒 */
		virtual AABB3 GetBoundBox() const = 0;

		/** 查找可见元素
		* @param
		*/
		virtual void _FindVisibleObject(const CameraPtr& camera) = 0;

	};	// end class Node

}	// end namespace Node

#endif	// end __DRENODE_H__