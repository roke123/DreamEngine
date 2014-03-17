#include "DreSceneRootNode.h"

#include "DreSceneNode.h"

namespace dream
{

	SceneRootNode::SceneRootNode(const Vector3& initialPosition, const Vector3& initialScale,
			const Quaternion& initialOrientation) :
	//--------------------------------------------------------------------------------------
	mFinalPosition(initialPosition), mFinalScale(initialScale), mFinalOrientation(initialOrientation)
	{
		// 留空
	}

	/** 绑定一个子节点
	* @param	name		子节点名
	* @param	child		子节点指针
	*/
	void SceneRootNode::AttachChildNode(const string& name, SceneNodePtr& child)
	{
		mNodeSet.insert(child);
		
		// 设置子节点名
		child->_SetNodeName(name);
		// 设置父节点
		child->_SetParent(shared_from_this());

		// 通知父节点
		_NotifyChanged();
	}

	/** 解除子节点的绑定
	* @param	name		子节点名
	* @return				返回子节点的右值引用
	*/
	SceneNodePtr SceneRootNode::DetachChildNode(const string& name)
	{
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(new SceneNode(name)));
		DreAssert(ite == mNodeSet.end(), "SceneNode中不存在同名子节点");

		SceneNodePtr ret = *ite;
		mNodeSet.erase(ite);

		// 设置子节点名
		ret->_SetNodeName("");
		// 设置子节点需要更新
		ret->_SetParent(shared_from_this());
		// 设置父节点
		ret->_SetParent(nullptr);

		// 通知父节点
		_NotifyChanged();
		return ret;
	}

	/** 获取一个节点名为name的节点(包括检索子节点，如有)
	*/
	SceneNodePtr SceneRootNode::FindSubNodeByName(const string& name)
	{
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(new SceneNode(name)));
		if(ite != mNodeSet.end())
			return *ite;

		ite = mNodeSet.begin();
		for(; ite != mNodeSet.end(); ++ ite)
		{
			SceneNodePtr SceneNode = nullptr;
			SceneNode = (*ite)->FindSubNodeByName(name);
			if(SceneNode != nullptr)
				return SceneNode;
		}

		return nullptr;
	}

	/** 更新碰撞盒 */
	void SceneRootNode::_UpdateBoundBox()
	{
		SceneNodeSetIte ite = mNodeSet.begin();
		for(; ite != mNodeSet.end(); ++ ite)
		{
			mBoundsBox.AddAABB3((*ite)->GetBoundBox());
		}
	}

	/** 更新节点，计算当前节点属性 */
	void SceneRootNode::_Update()
	{
		// 如果该节点未更新
		if(!mIsUpdated)
		{
			// 本节点状态更新，即标志其子节点未更新
			mIsChildrenUpdated = false;
			SceneNodeSetIte ite = mNodeSet.begin();
			for(; ite != mNodeSet.end(); ++ ite)
			{
				(*ite)->_NeedUpdate();
			}
		}

		// 如果子节点存在未更新节点
		if(!mIsChildrenUpdated)
		{
			SceneNodeSetIte ite = mNodeSet.begin();
			for(; ite != mNodeSet.end(); ++ ite)
			{
				(*ite)->_Update();
			}
		}

		_UpdateBoundBox();
	}

}	// end namespace dream