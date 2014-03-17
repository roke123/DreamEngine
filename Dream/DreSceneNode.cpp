#include "DreSceneNode.h"

#include "DreException.h"


namespace dream
{
	/** 私有构造函数，用于构造一个只有名字的SceneNode */
	SceneNode::SceneNode(const string& name) :
	//-------------------------------------------------------------------------------
		mNodeName(name),
		OnAttachObject(""),
		OnUpdateNode(""),
		OnRenderNode(""),
		OnDetachObject(""),
		OnAttachChildNode(""),
		OnDetachChildNode("")
	{
		// 留空
	}

	/** 构造函数 */
	SceneNode::SceneNode(const Vector3& initialPosition, const Vector3& initialScale,
		const Quaternion& initialOrientation) :
	//-------------------------------------------------------------------------------
		mIsVisiable(true), mIsUpdated(false), mIsChildrenUpdated(true), mRecaleWorldMatrix(false),
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
		child->mIsUpdated = false;
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
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(new SceneNode(name)));
		DreAssert(ite == mNodeSet.end(), "SceneNode中不存在同名子节点");

		SceneNodePtr ret = *ite;
		mNodeSet.erase(ite);

		// 设置子节点名
		ret->_SetNodeName("");
		// 设置子节点需要更新
		ret->mIsUpdated = true;
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
	void SceneNode::_Update()
	{
		// 如果该节点未更新
		if(!mIsUpdated)
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

		OnUpdateNode._Notify(shared_from_this());
	}

	/** 通知父节点子节点以改变需要更新，debug状态下会检查是否存在同名节点
	*/
	void SceneNode::_NotifyChanged()
	{
		// 标志子节点需要更新
		this->mIsChildrenUpdated = false;
		if(mParentNode != nullptr)
		{
			// 继续通知上一节点
			this->mParentNode->_NotifyChanged();
		}
	}

	/** 更新碰撞盒
	*/
	void SceneNode::_UpdateBoundBox()
	{
		mBoundsBox.Empty();

		ConvertibleObjectSetIte objectIte = mObjectSet.begin();
		for(; objectIte != mObjectSet.end(); ++ objectIte;)
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
	}

	/** 绑定一个ConvertibleObject
	*/
	void SceneNode::AttachConvertibleObject(ConvertibleObjectPtr& object)
	{
#		if defined(DEBUG) || defined(_DEBUG)
		ConvertibleObjectSetIte ite = mObjectSet.find(object);
		DreAssert(ite == mObjectSet.end(), "SceneNode中绑定了同名对象");
#			endif

		mObjectSet.insert(object);
		object->_AttachedToSceneNode(shared_from_this());
		OnAttachObject._Notify(shared_from_this(), object);
	}

	/** 解绑定一个ConvertibleObject
	*/
	void SceneNode::DetachConvertibleObject(const string& name)
	{
		ConvertibleObjectSetIte ite = mObjectSet.find(ConvertibleObjectPtr(new ConvertibleObject(name)));
		DreAssert(ite != mObjectSet.end(), "SceneNode中不存在同名对象");

		ConvertibleObjectPtr object = *ite;
		mObjectSet.erase(ite);
		(*ite)->_AttachedToSceneNode(shared_from_this());
		OnAttachObject._Notify(shared_from_this(), object);
	}

}	// end namespace dream