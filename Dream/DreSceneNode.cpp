#include "DreSceneNode.h"

#include "DreException.h"


namespace dream
{
	/** ˽�й��캯�������ڹ���һ��ֻ�����ֵ�SceneNode */
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
		// ����
	}

	/** ���캯�� */
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
		// ����
	}

	/** ��һ���ӽڵ�
	* @param	name		�ӽڵ���
	* @param	child		�ӽڵ�ָ��
	*/
	void SceneNode::AttachChildNode(const string& name, SceneNodePtr& child)
	{
		mNodeSet.insert(child);
		
		// �����ӽڵ���
		child->_SetNodeName(name);
		// �����ӽڵ���Ҫ����
		child->mIsUpdated = false;
		// ���ø��ڵ�
		child->_SetParent(shared_from_this());

		// ֪ͨ���ڵ�
		_NotifyChanged();
		// ����OnAttachChildNode�¼�
		OnAttachChildNode._Notify(shared_from_this(), child);
	}

	/** ����ӽڵ�İ�
	* @param	name		�ӽڵ���
	* @return				�����ӽڵ����ֵ����
	*/
	SceneNodePtr SceneNode::DetachChildNode(const string& name)
	{
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(new SceneNode(name)));
		DreAssert(ite == mNodeSet.end(), "SceneNode�в�����ͬ���ӽڵ�");

		SceneNodePtr ret = *ite;
		mNodeSet.erase(ite);

		// �����ӽڵ���
		ret->_SetNodeName("");
		// �����ӽڵ���Ҫ����
		ret->mIsUpdated = true;
		// ���ø��ڵ�
		ret->_SetParent(nullptr);

		// ֪ͨ���ڵ�
		_NotifyChanged();
		// ����OnDetachChildNode�¼�
		OnDetachChildNode._Notify(shared_from_this(), ret);
		return ret;
	}

	/** ��ȡһ���ڵ���Ϊname�Ľڵ�(���������ӽڵ㣬����)
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

	/** ��ȡת������ */
	Matrix4 SceneNode::GetWorldMatrix() const
	{
		if(mRecaleWorldMatrix)
		{
			mWorldMatrix = Matrix4::SetMatrixForNode(mFinalPosition, mFinalScale, mFinalOrientation);
			mRecaleWorldMatrix = false;
		}
		return mWorldMatrix;
	}

	/** ���½ڵ㣬���㵱ǰ�ڵ�����
	*/
	void SceneNode::_Update()
	{
		// ����ýڵ�δ����
		if(!mIsUpdated)
		{
			// �������λ��
			mFinalPosition = mRelativePosition + mParentNode->_GetFinalPosition();
			// �����������
			Vector3 mParentScale = mParentNode->_GetFinalPosition();
			mFinalScale.Set( 
				mRelativeScale.mX * mParentScale.mX,
				mRelativeScale.mY * mParentScale.mY,
				mRelativeScale.mZ * mParentScale.mZ);
			// ���������ת
			mFinalOrientation = Cross(mRelativeOrientation, mParentNode->_GetFinalOrientation()); 

			// ��������λ��
			mFinalPosition += mLocalPosition;
			// ������������
			mFinalScale.Set( 
				mFinalScale.mX * mLocalScale.mX,
				mFinalScale.mY * mLocalScale.mY,
				mFinalScale.mZ * mLocalScale.mZ);
			// ����������ת
			mFinalOrientation = Cross(mLocalOrientation, mFinalOrientation);

			// ���ڵ�״̬���£�����־���ӽڵ�δ����
			mIsChildrenUpdated = false;
			SceneNodeSetIte ite = mNodeSet.begin();
			for(; ite != mNodeSet.end(); ++ ite)
			{
				(*ite)->_NeedUpdate();
			}

		}

		// ����ӽڵ����δ���½ڵ�
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

	/** ֪ͨ���ڵ��ӽڵ��Ըı���Ҫ���£�debug״̬�»����Ƿ����ͬ���ڵ�
	*/
	void SceneNode::_NotifyChanged()
	{
		// ��־�ӽڵ���Ҫ����
		this->mIsChildrenUpdated = false;
		if(mParentNode != nullptr)
		{
			// ����֪ͨ��һ�ڵ�
			this->mParentNode->_NotifyChanged();
		}
	}

	/** ������ײ��
	*/
	void SceneNode::_UpdateBoundBox()
	{
		mBoundsBox.Empty();

		ConvertibleObjectSetIte objectIte = mObjectSet.begin();
		for(; objectIte != mObjectSet.end(); ++ objectIte;)
		{
			// ������ײ��
			mBoundsBox.AddAABB3((*objectIte)->GetBoundBox());
		}

		mBoundsBox *= GetWorldMatrix();

		SceneNodeSetIte ite = mNodeSet.begin();
		for(; ite != mNodeSet.end(); ++ ite)
		{
			mBoundsBox.AddAABB3((*ite)->mBoundsBox);
		}
	}

	/** ��һ��ConvertibleObject
	*/
	void SceneNode::AttachConvertibleObject(ConvertibleObjectPtr& object)
	{
#		if defined(DEBUG) || defined(_DEBUG)
		ConvertibleObjectSetIte ite = mObjectSet.find(object);
		DreAssert(ite == mObjectSet.end(), "SceneNode�а���ͬ������");
#			endif

		mObjectSet.insert(object);
		object->_AttachedToSceneNode(shared_from_this());
		OnAttachObject._Notify(shared_from_this(), object);
	}

	/** ���һ��ConvertibleObject
	*/
	void SceneNode::DetachConvertibleObject(const string& name)
	{
		ConvertibleObjectSetIte ite = mObjectSet.find(ConvertibleObjectPtr(new ConvertibleObject(name)));
		DreAssert(ite != mObjectSet.end(), "SceneNode�в�����ͬ������");

		ConvertibleObjectPtr object = *ite;
		mObjectSet.erase(ite);
		(*ite)->_AttachedToSceneNode(shared_from_this());
		OnAttachObject._Notify(shared_from_this(), object);
	}

}	// end namespace dream