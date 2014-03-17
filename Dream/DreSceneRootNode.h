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
		/** ���캯�� */
		explicit SceneRootNode(const Vector3& initialPosition, const Vector3& initialScale,
			const Quaternion& initialOrientation);

		/** ������������ */
		void SetFinalPosition(const Vector3& position) { _NeedUpdate(); mFinalPosition = position; };
		/** ȡ����������
		* @note override by Node
		*/
		virtual Vector3 _GetFinalPosition() const override { return mFinalPosition; };

		/** ������������ */
		void SetFinalOrientation(const Quaternion& orientation) { _NeedUpdate(); mFinalOrientation = orientation; };
		/** ȡ�����շ���
		* @note override by Node
		*/
		virtual Quaternion _GetFinalOrientation() const override { return mFinalOrientation; };
		
		/** ������������ */
		void SetFinalScale(const Vector3& scale) { _NeedUpdate(); mFinalScale = scale; };
		/** ȡ������Scale
		* @note override by Node
		*/
		virtual Vector3 _GetFinalScale() const override { return mFinalScale; };

		/** ���½ڵ㣬���㵱ǰ�ڵ�����
		* @note override by Node
		*/
		virtual void _Update() override;

		/** ȡ����ײ��
		* @note override by Node
		*/
		virtual AABB3 GetBoundBox() const override { return mBoundsBox; }

		/** ��һ���ӽڵ�
		* @param	name		�ӽڵ���
		* @param	child		�ӽڵ�ָ��
		*/
		void AttachChildNode(const string& name, SceneNodePtr& child);
		/** ����ӽڵ�İ�
		* @param	name		�ӽڵ���
		* @return				�����ӽڵ����ֵ����
		*/
		SceneNodePtr DetachChildNode(const string& name);				
		/** ��ȡһ���ڵ���Ϊname�Ľڵ�(���������ӽڵ㣬����)
		*/
		SceneNodePtr FindSubNodeByName(const string& name);

	private:
		/** ��־�ڵ���Ҫ���� */
		void _NeedUpdate() { mRecaleWorldMatrix = true; mIsUpdated = true; };

		/** ������ײ�� */
		void _UpdateBoundBox();

	private:
		/// ���������ת���;�������ת�������������
		Vector3					mFinalPosition;
		/// ���������ת���;�������ת����ķŴ���
		Vector3					mFinalScale;
		/// ���������ת���;�������ת�����ģ�ͷ���
		Quaternion				mFinalOrientation;

		/// ���ڵ������Ѹ���
		bool				mIsUpdated;
		/// �ڵ��µ��ӽڵ��Ѹ���
		bool				mIsChildrenUpdated;
		///	�Ƿ����¼�������任����
		mutable bool		mRecaleWorldMatrix;

		/// ��ײ��
		AABB3				mBoundsBox;
		/// ����任����
		mutable Matrix4		mWorldMatrix;

		typedef set<SceneNodePtr, SceneNode::SceneNodeNameCmp>			SceneNodeSet;
		typedef SceneNodeSet::iterator									SceneNodeSetIte;
		typedef SceneNodeSet::const_iterator							SceneNodeSetConstIte;
		/// �ӽڵ㼯
		SceneNodeSet			mNodeSet;

	};	// end class SceneRootNode

}	// end namespace dream

#endif // end __DRESCENEROOTNODE_H__
