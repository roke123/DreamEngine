#include "DreSceneNode.h"

#include "DreException.h"
#include "DreMemoryAllocatorConfig.h"

#include "DreSceneManager.h"
#include "DreComponent.h"

namespace dream
{
	/** ���캯�� */
	SceneNode::SceneNode(
		const string& name, u16 tagID, u16 layerID,
		const Vector3& initialPosition,
		const Vector3& initialScale,
		const Quaternion& initialOrientation) :
	//-------------------------------------------------------------------------------
	mNodeName(name), mTagID(tagID), mLayerID(layerID),
		mLocalPosition(initialPosition), mLocalScale(initialScale), mLocalOrientation(initialOrientation),
		mIsEnable(true), mTransformUpdated(false), mChildrenTransformUpdated(false),
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
	void SceneNode::AttachChildNode(string name, SceneNodePtr child)
	{
		mNodeMap.insert(make_pair<string, SceneNodePtr>(std::move(name), std::move(child)));
		
		// �����ӽڵ���
		child->_SetNodeName(name);
		// �����ӽڵ���Ҫ����
		child->_MarkNeedUpdate();
		// ���ø��ڵ�
		child->_SetParent(shared_from_this());

		// ֪ͨ���ڵ�
		this->_NotifyTransformChanged();
		// ����OnAttachChildNode�¼�
		OnAttachChildNode._Notify(shared_from_this(), child);
	}

	/** ����ӽڵ�İ�
	* @param	name		�ӽڵ���
	* @return				�����ӽڵ����ֵ����
	*/
	SceneNodePtr SceneNode::DetachChildNode(const string& name)
	{
		SceneNodeSetIte ite = mNodeMap.find(name);
		DreAssert(ite == mNodeMap.end(), "SceneNode�в�����ͬ���ӽڵ�");

		SceneNodePtr ret = ite->second;
		mNodeMap.erase(ite);

		// �����ӽڵ���Ҫ����
		ret->mIsEnable = true;
		// ���ø��ڵ�
		ret->_SetParent(nullptr);

		// ֪ͨ���ڵ�
		this->_NotifyTransformChanged();
		// ����OnDetachChildNode�¼�
		OnDetachChildNode._Notify(shared_from_this(), ret);
		return ret;
	}

	/** ��ȡһ���ڵ���Ϊname�Ľڵ�(���������ӽڵ㣬����)
	*/
	SceneNodePtr SceneNode::FindSubNodeByName(const string& name)
	{
		SceneNodeSetIte ite = mNodeMap.find(name);
		if (ite != mNodeMap.end())
			return ite->second;

		ite = mNodeMap.begin();
		for (; ite != mNodeMap.end(); ++ite)
		{
			SceneNodePtr SceneNode = nullptr;
			SceneNode = ite->second->FindSubNodeByName(name);
			if(SceneNode != nullptr)
				return SceneNode;
		}

		return nullptr;
	}

	/** ��ȡת������ */
	Matrix4 SceneNode::GetWorldMatrix()
	{
		if (!mTransformUpdated)
		{
			_ForceUpwardTransformUpdate();

			mWorldMatrix = Matrix4::SetMatrixForNode(mFinalPosition, mFinalScale, mFinalOrientation);
		}
		return mWorldMatrix;
	}

	/** ���½ڵ㣬���㵱ǰ�ڵ�����
	*/
	void SceneNode::_PreRenderUpdate()
	{
		_TransformUpdate();

		// �����������
		ComponentMapIte ite = mComponentMap.begin();
		for (; ite != mComponentMap.end(); ++ite) {
			ite->second->_PreRenderUpdate();
		}

		//OnUpdateNode._Notify(shared_from_this());
	}

	/** ��Ⱦ����½ڵ㣬���㵱ǰ�ڵ�����
	* @note override by Node
	*/
	void SceneNode::_PostRenderUpdate()
	{
		// �����������
		ComponentMapIte ite = mComponentMap.begin();
		for (; ite != mComponentMap.end(); ++ite) {
			ite->second->_PostRenderUpdate();
		}

		//OnUpdateNode._Notify(shared_from_this());
	}

	/** �߼����½ڵ�
	* @note override by Node
	*/
	void SceneNode::_FixedUpdate()
	{
		// �����������
		ComponentMapIte ite = mComponentMap.begin();
		for (; ite != mComponentMap.end(); ++ite) {
			ite->second->_FixedUpdate();
		}
	}

	/** ���µ�ǰ�ڵ��transform���ԣ� ���º���־���ӽڵ�Ϊδ���£������ӽڵ��_PreRenderUpdate�и���*/
	void SceneNode::_TransformUpdate()
	{
		// ����ýڵ�δ����
		if (!mTransformUpdated)
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

			// ��־���ӽڵ�δ����
			SceneNodeSetIte ite = mNodeMap.begin();
			for (; ite != mNodeMap.end(); ++ite)
			{
				ite->second->_MarkNeedUpdate();
			}

		}
	}

	void SceneNode::_ForceUpwardTransformUpdate()
	{
		if (this->GetParent() != nullptr)
			this->GetParent()->_ForceUpwardTransformUpdate();

		_TransformUpdate();
	}

	/** ֪ͨ���ڵ㱾�ڵ����Ըı���Ҫ���£�debug״̬�»����Ƿ����ͬ���ڵ�
	* @note override by Node
	*/
	void SceneNode::_NotifyNeedUpdate()
	{
		this->mChildrenTransformUpdated = false;

		if (mParentNode != nullptr)
			mParentNode->_NotifyNeedUpdate();
	}

	/** ֪ͨ���ڵ㱾�ڵ�� transform ���Է����ı� */
	void SceneNode::_NotifyTransformChanged()
	{
		// ��־���ڵ���Ҫ����
		this->mTransformUpdated = false;
		// ֪ͨ���ڵ���Ҫ����
		this->mParentNode->_NotifyNeedUpdate();
	}

	SceneNodePtr SceneNode::GetParent() const
	{
		if (mParentNode.get() == (Node*)SceneManager::GetInstance().GetRootNode())
			return nullptr;

		return static_pointer_cast<SceneNode>(mParentNode);
	};

	/** ������ײ��
	*/
	/*void SceneNode::_UpdateBoundBox()
	{
		mBoundsBox.Empty();

		ConvertibleObjectSetIte objectIte = mObjectSet.begin();
		for(; objectIte != mObjectSet.end(); ++ objectIte)
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
	}*/

}	// end namespace dream