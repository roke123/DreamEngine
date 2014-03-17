#ifndef __DRESCENENODE_H__
#define __DRESCENENODE_H__

#include "DreSceneManagerDeclaration.h"

#include "DreNode.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "AABB3.h"
#include "DreEvent.h"

namespace dream
{

	class SceneNode : public Node, public std::enable_shared_from_this<SceneNode>
	{
	public:
		/** �ڵ����ȽϺ�������
		*/
		class SceneNodeNameCmp
		{
		public:
			/** �ȽϺ���
			*/
			bool operator() (const SceneNodePtr& lh, const SceneNodePtr& rh) const
			{
				return lh->mNodeName.compare(rh->mNodeName) != 0;
			}
		};	// end class NodeNameCmp

		typedef function<void (SceneNodePtr&, ConvertibleObjectPtr&)> NodeAttchObjectHandler;
		class NodeAttchObjectEvent : Event<NodeAttchObjectHandler>
		{
		public:
			/** ���캯��
			*/
			NodeAttchObjectEvent(const string& name) : Event(name)
			{
				// ����
			}

			/** ֪ͨ����������
			*/
			void _Notify(SceneNodePtr& node, ConvertibleObjectPtr& object)
			{
				HandlerIte ite = mHandlerList.begin();
				for(; ite != mHandlerList.end(); ++ ite)
				{
					(*ite)->operator()(node, object);
				}
			}
		};	// end class NodeAttchObjectEvent

		
		/** �ڵ㴦���¼�
		*/
		typedef function<void (SceneNodePtr&)> SceneNodeEventHandler;
		class SceneNodeEvent : public Event<SceneNodeEventHandler>
		{
		public:
			/** ���캯��
			*/
			SceneNodeEvent(const string& name) : Event(name)
			{
				// ����
			}

			/** ֪ͨ����������
			*/
			void _Notify(SceneNodePtr& Node)
			{
				HandlerIte ite = mHandlerList.begin();
				for(; ite != mHandlerList.end(); ++ ite)
				{
					(*ite)->operator()(Node);
				}
			}
		};	// end class NodeEvent

		
		/** ��ChildSceneNode�¼�
		*/
		typedef function<void (SceneNodePtr&, SceneNodePtr&)> ChildSceneNodeEventHandler;
		class ChildSceneNodeEvent : public Event<ChildSceneNodeEventHandler>
		{
		public:
			/** ���캯��
			*/
			ChildSceneNodeEvent(const string& name) : Event(name)
			{
				// ����
			}

			/** ֪ͨ����������
			*/
			void _Notify(SceneNodePtr& node, SceneNodePtr& childNode)
			{
				HandlerIte ite = mHandlerList.begin();
				for(; ite != mHandlerList.end(); ++ ite)
				{
					(*ite)->operator()(node, childNode);
				}
			}
		}; // end class ChildNodeEvent

	public:
		/** ˽�й��캯�������ڹ���һ��ֻ�����ֵ�SceneNode */
		explicit SceneNode(const string& name);
	
		/** ���캯�� */
		explicit SceneNode(const Vector3& initialPosition, const Vector3& initialScale,
			const Quaternion& initialOrientation);

		/** ����ڵ�ǰλ��ƽ��һ�ξ���
		* @param	x		��X�᷽���ƽ�ƾ���
		* @param	y		��Y�᷽���ƽ�ƾ���
		* @param	z		��Z�᷽���ƽ�ƾ���
		*/
		void SetAbsoluteTranslation(f32 x, f32 y, f32 z) { _NeedUpdate(); mLocalPosition = Vector3(x, y, z); }
		void SetAbsoluteTranslation(const Vector3& tranlation) { _NeedUpdate(); mLocalPosition = tranlation; }
		/** ȡ������ڵ�ǰλ�õ�ƽ�ƾ��� */
		Vector3 GetAbsolutionTranslation() const { return mLocalPosition; }

		/** ����ڵ�ǰģ�ʹ�С�ķŴ���
		* @param	x		��X�᷽��ķŴ���
		* @param	y		��Y�᷽��ķŴ���
		* @param	z		��Z�᷽��ķŴ���
		*/
		void SetAbsoluteScale(f32 x, f32 y, f32 z) { _NeedUpdate(); mLocalScale = Vector3(x, y, z); }
		void SetAbsoluteScale(const Vector3& scale) { _NeedUpdate(); mLocalScale = scale; }
		/** ȡ������ڵ�ǰģ�ʹ�С�ķŴ��� */
		Vector3 GetAbsolutionScale() const { return mLocalScale; }

		/** ����ڵ�ǰģ�ͷ������ת���� */
		void SetAbsoluteRotation(const Quaternion& orientation) { _NeedUpdate(); mLocalOrientation = orientation; }
		/** ȡ������ڵ�ǰģ�ͷ������ת���� */
		Quaternion GetAbsolutionRotation() const { return mLocalOrientation; }

		/** ����ڸ��ڵ�ƽ��һ�ξ���
		* @param	x		��X�᷽���ƽ�ƾ���
		* @param	y		��Y�᷽���ƽ�ƾ���
		* @param	z		��Z�᷽���ƽ�ƾ���
		*/
		void SetRelativeTranslation(f32 x, f32 y, f32 z) { _NeedUpdate(); mRelativePosition = Vector3(x, y, z); }
		void SetRelativeTranslation(const Vector3& tranlation) { _NeedUpdate(); mRelativePosition = tranlation; }
		/** ȡ������ڸ��ڵ��ƽ�ƾ��� */
		Vector3 GetRelativeTranslation() const { return mRelativePosition; }

		/** ����ڸ��ڵ��С�ķŴ���
		* @param	x		��X�᷽��ķŴ���
		* @param	y		��Y�᷽��ķŴ���
		* @param	z		��Z�᷽��ķŴ���
		*/
		void SetRelativeScale(f32 x, f32 y, f32 z) { _NeedUpdate(); mRelativeScale = Vector3(x, y, z); }
		void SetRelativeScale(const Vector3& scale) { _NeedUpdate(); mRelativeScale = scale; }
		/** ȡ������ڸ��ڵ��С�ķŴ��� */
		Vector3 GetRelativeScale() const { return mRelativeScale; }

		/** ����ڸ��ڵ㷽�����ת���� */
		void SetRelativeRotation(const Quaternion& orientation) { _NeedUpdate(); mRelativeOrientation = orientation; }
		/** ȡ������ڸ��ڵ㷽�����ת����*/
		Quaternion GetRelativeRotation() const { return mRelativeOrientation; }
		
		/** ȡ����������
		* @note override by Node
		*/
		Vector3 _GetFinalPosition() const override { return mFinalPosition; };
		/** ȡ�����շ���
		* @note override by Node
		*/
		Quaternion _GetFinalOrientation() const override { return mFinalOrientation; };
		/** ȡ������Scale
		* @note override by Node
		*/
		Vector3 _GetFinalScale() const override { return mFinalScale; };

		/** ��ȡת������
		* @note override by Node
		*/
		Matrix4 GetWorldMatrix() const override;

		/** ���½ڵ㣬���㵱ǰ�ڵ�����
		* @note override by Node
		*/
		void _Update() override;

		/** ȡ����ײ��
		* @note override by Node
		*/
		AABB3 GetBoundBox() const override { return mBoundsBox; }

		/** ֪ͨ���ڵ����һ��ʵ��
		* @note override by Node
		*/
		void _NotifyChanged() override;

		/** ���ҿɼ�Ԫ��
		* @note override by Node
		*/
		void _FindVisibleObject(const CameraPtr& camera) override = 0;
		
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
		
		/** ���øýڵ��Ƿ�ɼ� */
		void SetVisiable(bool enable = true) { mIsVisiable = enable; }
		/** �жϸýڵ��Ƿ�ɼ� */
		bool IsVisible() const { return mIsVisiable; }

		/** ��ȡ���ڵ�ָ�� */
		NodePtr GetParent() const { return mParentNode; };

		/** ��һ��ConvertibleObject
		*/
		void AttachConvertibleObject(ConvertibleObjectPtr& object);

		/** ���һ��ConvertibleObject
		*/
		void DetachConvertibleObject(const string& name);

		/** ��ȡ�ڵ��� */
		string GetNodeName() const { return mNodeName; }

		/** ���ýڵ��� */
		void _SetNodeName(const string& nodeName) { mNodeName = nodeName; }

		/** ���ø��ڵ�ָ�� */
		void _SetParent(const NodePtr& parent) { _NeedUpdate(); mParentNode = parent; }
		
		/** ��־�ڵ���Ҫ���� */
		void _NeedUpdate() { mIsUpdated = false; mRecaleWorldMatrix = true; };

	protected:
		/** ������ײ�� */
		void _UpdateBoundBox();

	private:
		
		/// ���������ת���;�������ת�������������
		Vector3					mFinalPosition;
		/// ���������ת���;�������ת����ķŴ���
		Vector3					mFinalScale;
		/// ���������ת���;�������ת�����ģ�ͷ���
		Quaternion				mFinalOrientation;

		/// ģ�ͱ�������(�������һλ��)
		Vector3					mLocalPosition;
		/// ģ�ͱ��طŴ���(�������һ�Ŵ���)
		Vector3					mLocalScale;
		/// ģ�ͱ��ط���(�������һ����)
		Quaternion				mLocalOrientation;

		/// ģ���������(����ڸ��ڵ�λ��)
		Vector3					mRelativePosition;
		/// ģ����ԷŴ���(����ڸ��ڵ�Ŵ���)
		Vector3					mRelativeScale;
		/// ģ����Է���(����ڸ��ڵ㷽��)
		Quaternion				mRelativeOrientation;

		/// �ڵ���
		string				mNodeName;

		/// ��ʾ�ýڵ��Ƿ����ʾ�ı�־
		bool				mIsVisiable;
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

		typedef set<SceneNodePtr, SceneNodeNameCmp>			SceneNodeSet;
		typedef SceneNodeSet::iterator					SceneNodeSetIte;
		typedef SceneNodeSet::const_iterator			SceneNodeSetConstIte;
		/// �ӽڵ㼯
		SceneNodeSet			mNodeSet;
		/// ���ڵ�
		NodePtr					mParentNode;

		typedef set<ConvertibleObjectPtr, ConvertibleObjectNameCmp>		ConvertibleObjectSet;
		typedef ConvertibleObjectSet::iterator							ConvertibleObjectSetIte;
		typedef ConvertibleObjectSet::const_iterator					ConvertibleObjectSetConstIte;
		/// �󶨶���
		ConvertibleObjectSet	mObjectSet;

	public:
		/// ��ʵ���¼�
		NodeAttchObjectEvent	OnAttachObject;
		/// �ڵ�����¼�
		SceneNodeEvent			OnUpdateNode;
		/// �ڵ���Ⱦ�¼�
		SceneNodeEvent			OnRenderNode;
		/// �ڵ���ʵ���¼�
		NodeAttchObjectEvent	OnDetachObject;
		/// �ڵ���ӽڵ��¼�
		ChildSceneNodeEvent		OnAttachChildNode;
		/// �ڵ����ӽڵ��¼�
		ChildSceneNodeEvent		OnDetachChildNode;
	};	// end class SceneNode

}	// end namespace dream

#endif // end __DRESCENENODE_H__
