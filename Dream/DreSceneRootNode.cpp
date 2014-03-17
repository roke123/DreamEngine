#include "DreSceneRootNode.h"

#include "DreSceneNode.h"

namespace dream
{

	SceneRootNode::SceneRootNode(const Vector3& initialPosition, const Vector3& initialScale,
			const Quaternion& initialOrientation) :
	//--------------------------------------------------------------------------------------
	mFinalPosition(initialPosition), mFinalScale(initialScale), mFinalOrientation(initialOrientation)
	{
		// ����
	}

	/** ��һ���ӽڵ�
	* @param	name		�ӽڵ���
	* @param	child		�ӽڵ�ָ��
	*/
	void SceneRootNode::AttachChildNode(const string& name, SceneNodePtr& child)
	{
		mNodeSet.insert(child);
		
		// �����ӽڵ���
		child->_SetNodeName(name);
		// ���ø��ڵ�
		child->_SetParent(shared_from_this());

		// ֪ͨ���ڵ�
		_NotifyChanged();
	}

	/** ����ӽڵ�İ�
	* @param	name		�ӽڵ���
	* @return				�����ӽڵ����ֵ����
	*/
	SceneNodePtr SceneRootNode::DetachChildNode(const string& name)
	{
		SceneNodeSetIte ite = mNodeSet.find(SceneNodePtr(new SceneNode(name)));
		DreAssert(ite == mNodeSet.end(), "SceneNode�в�����ͬ���ӽڵ�");

		SceneNodePtr ret = *ite;
		mNodeSet.erase(ite);

		// �����ӽڵ���
		ret->_SetNodeName("");
		// �����ӽڵ���Ҫ����
		ret->_SetParent(shared_from_this());
		// ���ø��ڵ�
		ret->_SetParent(nullptr);

		// ֪ͨ���ڵ�
		_NotifyChanged();
		return ret;
	}

	/** ��ȡһ���ڵ���Ϊname�Ľڵ�(���������ӽڵ㣬����)
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

	/** ������ײ�� */
	void SceneRootNode::_UpdateBoundBox()
	{
		SceneNodeSetIte ite = mNodeSet.begin();
		for(; ite != mNodeSet.end(); ++ ite)
		{
			mBoundsBox.AddAABB3((*ite)->GetBoundBox());
		}
	}

	/** ���½ڵ㣬���㵱ǰ�ڵ����� */
	void SceneRootNode::_Update()
	{
		// ����ýڵ�δ����
		if(!mIsUpdated)
		{
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
	}

}	// end namespace dream