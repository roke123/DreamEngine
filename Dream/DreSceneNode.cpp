#include "DreSceneNode.h"

#include "DreException.h"
#include "DreMemoryAllocatorConfig.h"

#include "DreSceneManager.h"
#include "DreComponent.h"

namespace dream
{
	/** 构造函数 */
	SceneNode::SceneNode(
		const string& name, u16 tagID, u16 layerID,
		const Vector3& initialPosition,
		const Vector3& initialScale,
		const Quaternion& initialOrientation) :
	//-------------------------------------------------------------------------------
	mNodeName(name), mTagID(tagID), mLayerID(layerID),
		mLocalPosition(initialPosition), mLocalScale(initialScale), mLocalOrientation(initialOrientation),
		mIsEnable(true), mTransformUpdated(false), mChildrenTransformUpdated(true), mRecaleWorldMatrix(false),
		mParentNode(nullptr),
		OnAttachObject("Node::OnAttachObject"),
		OnUpdateNode("Node::OnUpdateNode"),
		OnRenderNode("Node::OnRenderNode"),
		OnDetachObject("Node::OnDetachObject"),
		OnAttachChildNode("Node::OnAttachChildNode"),
		OnDetachChildNode("Node::OnDetachChildNode")
	{
		// 留空
	}

	/** 绑定一个子节点
	* @param	name		子节点名
	* @param	child		子节点指针
	*/
	void SceneNode::AttachChildNode(const string& name, SceneNodePtr& child)
	{
		mNodeSet.insert(child);
		
		// 设置子节点名
		child->_SetNodeName(name);
		// 设置子节点需要更新
		child->mIsEnable = false;
		// 设置父节点
		child->_SetParent(shared_from_this());

		// 通知父节点
		_NotifyChanged();
		// 发出OnAttachChildNode事件
		OnAttachChildNode._Notify(shared_from_this(), child);
	}

	/** 解除子节点的绑定
	* @param	name		子节点名
	* @return				返回子节点的右值引用
	*/
	SceneNodePtr SceneNode::DetachChildNode(const string& name)
	{
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(DREAM_NEW SceneNode(name)));
		DreAssert(ite == mNodeSet.end(), "SceneNode中不存在同名子节点");

		SceneNodePtr ret = *ite;
		mNodeSet.erase(ite);

		// 设置子节点名
		ret->_SetNodeName("");
		// 设置子节点需要更新
		ret->mIsEnable = true;
		// 设置父节点
		ret->_SetParent(nullptr);

		// 通知父节点
		_NotifyChanged();
		// 发出OnDetachChildNode事件
		OnDetachChildNode._Notify(shared_from_this(), ret);
		return ret;
	}

	/** 获取一个节点名为name的节点(包括检索子节点，如有)
	*/
	SceneNodePtr SceneNode::FindSubNodeByName(const string& name)
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

	/** 获取转换矩阵 */
	Matrix4 SceneNode::GetWorldMatrix() const
	{
		if(mRecaleWorldMatrix)
		{
			mWorldMatrix = Matrix4::SetMatrixForNode(mFinalPosition, mFinalScale, mFinalOrientation);
			mRecaleWorldMatrix = false;
		}
		return mWorldMatrix;
	}

	/** 更新节点，计算当前节点属性
	*/
	void SceneNode::_PreRenderUpdate()
	{
		_TransformUpdate();

		// 更新所有组件
		ComponentMapIte ite = mComponentMap.begin();
		for (; ite != mComponentMap.end(); ++ite) {
			ite->second->_PreRenderUpdate();
		}

		//OnUpdateNode._Notify(shared_from_this());
	}

	/** 渲染后更新节点，计算当前节点属性
	* @note override by Node
	*/
	void SceneNode::_PostRenderUpdate()
	{
		// 更新所有组件
		ComponentMapIte ite = mComponentMap.begin();
		for (; ite != mComponentMap.end(); ++ite) {
			ite->second->_PostRenderUpdate();
		}

		//OnUpdateNode._Notify(shared_from_this());
	}

	/** 逻辑更新节点
	* @note override by Node
	*/
	void SceneNode::_FixedUpdate()
	{
		// 更新所有组件
		ComponentMapIte ite = mComponentMap.begin();
		for (; ite != mComponentMap.end(); ++ite) {
			ite->second->_FixedUpdate();
		}
	}

	/** 更新当前节点的transform属性， 更新后会标志其子节点为未更新，并在子节点的_PreRenderUpdate中更新*/
	void SceneNode::_TransformUpdate()
	{
		// 如果该节点未更新
		if (!mTransformUpdated)
		{
			// 计算相对位移
			mFinalPosition = mRelativePosition + mParentNode->_GetFinalPosition();
			// 计算相对缩放
			Vector3 mParentScale = mParentNode->_GetFinalPosition();
			mFinalScale.Set(
				mRelativeScale.mX * mParentScale.mX,
				mRelativeScale.mY * mParentScale.mY,
				mRelativeScale.mZ * mParentScale.mZ);
			// 计算相对旋转
			mFinalOrientation = Cross(mRelativeOrientation, mParentNode->_GetFinalOrientation());

			// 计算最终位移
			mFinalPosition += mLocalPosition;
			// 计算最终缩放
			mFinalScale.Set(
				mFinalScale.mX * mLocalScale.mX,
				mFinalScale.mY * mLocalScale.mY,
				mFinalScale.mZ * mLocalScale.mZ);
			// 计算最终旋转
			mFinalOrientation = Cross(mLocalOrientation, mFinalOrientation);

			// 标志其子节点未更新
			SceneNodeSetIte ite = mNodeSet.begin();
			for (; ite != mNodeSet.end(); ++ite)
			{
				(*ite)->_NeedUpdate();
			}

		}
	}

	/** 通知父节点子节点以改变需要更新，debug状态下会检查是否存在同名节点
	*/
	void SceneNode::_NotifyChanged()
	{
		// 标志子节点需要更新
		this->mTransformUpdated = false;
		if(mParentNode != nullptr)
		{
			// 继续通知上一节点
			this->mParentNode->_NotifyChanged();
		}
	}

	SceneNodePtr SceneNode::GetParent() const
	{
		if (mParentNode.get() == (Node*)SceneManager::GetInstance().GetRootNode())
			return nullptr;

		return static_pointer_cast<SceneNode>(mParentNode);
	};

	/** 更新碰撞盒
	*/
	/*void SceneNode::_UpdateBoundBox()
	{
		mBoundsBox.Empty();

		ConvertibleObjectSetIte objectIte = mObjectSet.begin();
		for(; objectIte != mObjectSet.end(); ++ objectIte)
		{
			// 更新碰撞盒
			mBoundsBox.AddAABB3((*objectIte)->GetBoundBox());
		}

		mBoundsBox *= GetWorldMatrix();

		SceneNodeSetIte ite = mNodeSet.begin();
		for(; ite != mNodeSet.end(); ++ ite)
		{
			mBoundsBox.AddAABB3((*ite)->mBoundsBox);
		}
	}*/

}	// end namespace dream