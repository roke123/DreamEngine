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
		mIsEnable(true), mTransformUpdated(false), mChildrenTransformUpdated(true), mRecaleWorldMatrix(false),
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
		child->mIsEnable = false;
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
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(DREAM_NEW SceneNode(name)));
		DreAssert(ite == mNodeSet.end(), "SceneNode�в�����ͬ���ӽڵ�");

		SceneNodePtr ret = *ite;
		mNodeSet.erase(ite);

		// �����ӽڵ���
		ret->_SetNodeName("");
		// �����ӽڵ���Ҫ����
		ret->mIsEnable = true;
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
			SceneNodeSetIte ite = mNodeSet.begin();
			for (; ite != mNodeSet.end(); ++ite)
			{
				(*ite)->_NeedUpdate();
			}

		}
	}

	/** ֪ͨ���ڵ��ӽڵ��Ըı���Ҫ���£�debug״̬�»����Ƿ����ͬ���ڵ�
	*/
	void SceneNode::_NotifyChanged()
	{
		// ��־�ӽڵ���Ҫ����
		this->mTransformUpdated = false;
		if(mParentNode != nullptr)
		{
			// ����֪ͨ��һ�ڵ�
			this->mParentNode->_NotifyChanged();
		}
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