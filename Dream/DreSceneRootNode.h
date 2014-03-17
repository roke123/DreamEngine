#ifndef __DRESCENEROOTNODE_H__
#define __DRESCENEROOTNODE_H__

#include "DreSceneManagerDeclaration.h"

#include "DreNode.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "AABB3.h"
#include "DreSceneNode.h"

namespace dream
{

	class SceneRootNode : public Node, public std::enable_shared_from_this<SceneRootNode>
	{
	public:
		/** 构造函数 */
		explicit SceneRootNode(const Vector3& initialPosition, const Vector3& initialScale,
			const Quaternion& initialOrientation);

		/** 设置最终坐标 */
		void SetFinalPosition(const Vector3& position) { _NeedUpdate(); mFinalPosition = position; };
		/** 取得最终坐标
		* @note override by Node
		*/
		virtual Vector3 _GetFinalPosition() const override { return mFinalPosition; };

		/** 设置最终坐标 */
		void SetFinalOrientation(const Quaternion& orientation) { _NeedUpdate(); mFinalOrientation = orientation; };
		/** 取得最终方向
		* @note override by Node
		*/
		virtual Quaternion _GetFinalOrientation() const override { return mFinalOrientation; };
		
		/** 设置最终坐标 */
		void SetFinalScale(const Vector3& scale) { _NeedUpdate(); mFinalScale = scale; };
		/** 取得最终Scale
		* @note override by Node
		*/
		virtual Vector3 _GetFinalScale() const override { return mFinalScale; };

		/** 更新节点，计算当前节点属性
		* @note override by Node
		*/
		virtual void _Update() override;

		/** 取得碰撞盒
		* @note override by Node
		*/
		virtual AABB3 GetBoundBox() const override { return mBoundsBox; }

		/** 绑定一个子节点
		* @param	name		子节点名
		* @param	child		子节点指针
		*/
		void AttachChildNode(const string& name, SceneNodePtr& child);
		/** 解除子节点的绑定
		* @param	name		子节点名
		* @return				返回子节点的右值引用
		*/
		SceneNodePtr DetachChildNode(const string& name);				
		/** 获取一个节点名为name的节点(包括检索子节点，如有)
		*/
		SceneNodePtr FindSubNodeByName(const string& name);

	private:
		/** 标志节点需要更新 */
		void _NeedUpdate() { mRecaleWorldMatrix = true; mIsUpdated = true; };

		/** 更新碰撞盒 */
		void _UpdateBoundBox();

	private:
		/// 经相对坐标转换和绝对坐标转换后的最终坐标
		Vector3					mFinalPosition;
		/// 经相对坐标转换和绝对坐标转换后的放大倍数
		Vector3					mFinalScale;
		/// 经相对坐标转换和绝对坐标转换后的模型方向
		Quaternion				mFinalOrientation;

		/// 本节点属性已更新
		bool				mIsUpdated;
		/// 节点下的子节点已更新
		bool				mIsChildrenUpdated;
		///	是否重新计算世界变换矩阵
		mutable bool		mRecaleWorldMatrix;

		/// 碰撞盒
		AABB3				mBoundsBox;
		/// 世界变换矩阵
		mutable Matrix4		mWorldMatrix;

		typedef set<SceneNodePtr, SceneNode::SceneNodeNameCmp>			SceneNodeSet;
		typedef SceneNodeSet::iterator									SceneNodeSetIte;
		typedef SceneNodeSet::const_iterator							SceneNodeSetConstIte;
		/// 子节点集
		SceneNodeSet			mNodeSet;

	};	// end class SceneRootNode

}	// end namespace dream

#endif // end __DRESCENEROOTNODE_H__
