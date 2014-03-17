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
		virtual Vector3 _GetFinalPosition() const = 0;;
		/** 取得最终方向 */
		virtual Quaternion _GetFinalOrientation() const = 0;
		/** 取得最终Scale */
		virtual Vector3 _GetFinalScale() const = 0;

		/** 获取转换矩阵 */
		virtual Matrix4 GetWorldMatrix() const = 0;

		/** 通知父节点绑定了一个实体 */
		virtual void _NotifyChanged() = 0;

		/** 更新节点，计算当前节点属性 */
		virtual void _Update() = 0;

		/** 取得碰撞盒 */
		virtual AABB3 GetBoundBox() const = 0;

		/** 查找可见元素 */
		virtual void _FindVisibleObject(const CameraPtr& camera) = 0;

	};	// end class Node

}	// end namespace Node

#endif	// end __DRENODE_H__