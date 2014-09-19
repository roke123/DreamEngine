#ifndef __DRESCENENODE_H__
#define __DRESCENENODE_H__

#include "DreSceneManagerDeclaration.h"

#include "DreNode.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "AABB3.h"
#include "DreEvent.h"

#include "DreConvertibleObject.h"

namespace dream
{
	enum SCENE_NODE_TAG
	{
		SCENE_NODE_TAG_NONE,
		SCENE_NODE_TAG_
	};

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
	
		/** ���캯�� */
		explicit SceneNode(
			const string& name, u16 tagID, u16 layerID,
			const Vector3& initialPosition = Vector3::ZeroVector, 
			const Vector3& initialScale = Vector3::ZeroVector,
			const Quaternion& initialOrientation = Quaternion::UnitQuaternion);

		/** ����ڵ�ǰλ��ƽ��һ�ξ���
		* @param	x		��X�᷽���ƽ�ƾ���
		* @param	y		��Y�᷽���ƽ�ƾ���
		* @param	z		��Z�᷽���ƽ�ƾ���
		*/
		void SetAbsoluteTranslation(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mLocalPosition = Vector3(x, y, z); }
		void SetAbsoluteTranslation(const Vector3& tranlation) { _NotifyTransformChanged(); mLocalPosition = tranlation; }
		/** ȡ������ڵ�ǰλ�õ�ƽ�ƾ��� */
		Vector3 GetAbsolutionTranslation() const { return mLocalPosition; }

		/** ����ڵ�ǰģ�ʹ�С�ķŴ���
		* @param	x		��X�᷽��ķŴ���
		* @param	y		��Y�᷽��ķŴ���
		* @param	z		��Z�᷽��ķŴ���
		*/
		void SetLocalScale(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mLocalScale = Vector3(x, y, z); }
		void SetLocalScale(const Vector3& scale) { _NotifyTransformChanged(); mLocalScale = scale; }
		/** ȡ������ڵ�ǰģ�ʹ�С�ķŴ��� */
		Vector3 GetLocalScale() const { return mLocalScale; }

		/** ����ڵ�ǰģ�ͷ������ת���� */
		void SetLocalRotation(const Quaternion& orientation) { _NotifyTransformChanged(); mLocalOrientation = orientation; }
		/** ȡ������ڵ�ǰģ�ͷ������ת���� */
		Quaternion GetLocalRotation() const { return mLocalOrientation; }

		/** ����ڸ��ڵ�ƽ��һ�ξ���
		* @param	x		��X�᷽���ƽ�ƾ���
		* @param	y		��Y�᷽���ƽ�ƾ���
		* @param	z		��Z�᷽���ƽ�ƾ���
		*/
		void SetRelativeTranslation(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mRelativePosition = Vector3(x, y, z); }
		void SetRelativeTranslation(const Vector3& tranlation) { _NotifyTransformChanged(); mRelativePosition = tranlation; }
		/** ȡ������ڸ��ڵ��ƽ�ƾ��� */
		Vector3 GetRelativeTranslation() const { return mRelativePosition; }

		/** ����ڸ��ڵ��С�ķŴ���
		* @param	x		��X�᷽��ķŴ���
		* @param	y		��Y�᷽��ķŴ���
		* @param	z		��Z�᷽��ķŴ���
		*/
		void SetRelativeScale(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mRelativeScale = Vector3(x, y, z); }
		void SetRelativeScale(const Vector3& scale) { _NotifyTransformChanged(); mRelativeScale = scale; }
		/** ȡ������ڸ��ڵ��С�ķŴ��� */
		Vector3 GetRelativeScale() const { return mRelativeScale; }

		/** ����ڸ��ڵ㷽�����ת���� */
		void SetRelativeRotation(const Quaternion& orientation) { _NotifyTransformChanged(); mRelativeOrientation = orientation; }
		/** ȡ������ڸ��ڵ㷽�����ת����*/
		Quaternion GetRelativeRotation() const { return mRelativeOrientation; }
		
		/** ȡ����������
		* @note override by Node
		*/
		virtual Vector3 _GetFinalPosition() { _ForceUpwardTransformUpdate(); return mFinalPosition; };
		/** ȡ�����շ���
		* @note override by Node
		*/
		virtual Quaternion _GetFinalOrientation() override { _ForceUpwardTransformUpdate(); return mFinalOrientation; };
		/** ȡ������Scale
		* @note override by Node
		*/
		virtual Vector3 _GetFinalScale() override { _ForceUpwardTransformUpdate(); return mFinalScale; };

		/** ȡ��*/
		Vector3 _GetForward() { return Vector3::Forward *_GetFinalOrientation().QuaternionToMatrix4(); }

		/** ��Ⱦǰ���½ڵ㣬���㵱ǰ�ڵ�����
		* @note override by Node
		*/
		virtual void _PreRenderUpdate() override;

		/** ��Ⱦ����½ڵ㣬���㵱ǰ�ڵ�����
		* @note override by Node
		*/
		virtual void _PostRenderUpdate() override;

		/** �߼����½ڵ�
		* @note override by Node
		*/
		virtual void _FixedUpdate() override;

	protected:
		void _TransformUpdate();

		void _ForceUpwardTransformUpdate();

		/** ֪ͨ���ڵ㱾�ڵ�� transform ���Է����ı� */
		void _NotifyTransformChanged();

	public:

		/** ȡ����ײ��
		* @note override by Node
		*/
		virtual AABB3 GetBoundBox() const override { return AABB3::EmptyAABB3; }

		/** ֪ͨ���ڵ㱾�ڵ����Ըı���Ҫ���£�debug״̬�»����Ƿ����ͬ���ڵ�
		* @note override by Node
		*/
		void _NotifyNeedUpdate() override;

		/** ���ҿɼ�Ԫ��
		* @note override by Node
		*/
		void _FindVisibleObject(const CameraPtr& camera) override {};
		
		/** ��һ���ӽڵ�
		* @param	name		�ӽڵ���
		* @param	child		�ӽڵ�ָ��
		*/
		void AttachChildNode(string name, SceneNodePtr child);
		/** ����ӽڵ�İ�
		* @param	name		�ӽڵ���
		* @return				�����ӽڵ����ֵ����
		*/
		SceneNodePtr DetachChildNode(const string& name);				
		/** ��ȡһ���ڵ���Ϊname�Ľڵ�(���������ӽڵ㣬����)
		*/
		SceneNodePtr FindSubNodeByName(const string& name);
		
		/** ���øýڵ��Ƿ�ɼ� */
		void SetEnable(bool enable = true) { mIsEnable = enable; }
		/** �жϸýڵ��Ƿ�ɼ� */
		bool IsEnable() const { return mIsEnable; }

		/** ��ȡ���ڵ�ָ��,ֱ�Ӱ��ڸ��ڵ��µĽڵ�᷵��nullptr */
		SceneNodePtr GetParent() const;

		/** ��ȡ�ڵ��� */
		string GetNodeName() const { return mNodeName; }

		/** ���ýڵ��� */
		void _SetNodeName(const string& nodeName) { mNodeName = nodeName; }

		/** ���ø��ڵ�ָ�� */
		void _SetParent(const NodePtr& parent) { mParentNode = parent; }

		/** ��־���ڵ���Ҫ���� */
		void _MarkNeedUpdate() { mChildrenTransformUpdated = false; mTransformUpdated = false; }

		/** ����������� */
		Matrix4 SceneNode::GetWorldMatrix() const;

		/** ȡ�õ�ǰ�ڵ��ǩID */
		TagID GetTagID() { return mTagID; }
		void SetTagID(TagID id) { mTagID = id;  }

		/** ȡ�õ�ǰ�ڵ��ID */
		LayerID GetLayerID() { return mLayerID; }
		void SetLayerID(LayerID id) { mLayerID = id; }

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
		string					mNodeName;

		/// ��ʾ�ýڵ��Ƿ����
		bool					mIsEnable;
		/// ���ڵ������Ѹ���
		bool					mTransformUpdated;
		/// ���ڵ���ӽڵ��Ƿ��Ѹ���
		bool					mChildrenTransformUpdated;

		typedef map<string, SceneNodePtr, SceneNodeNameCmp>			SceneNodeMap;
		typedef SceneNodeMap::iterator								SceneNodeSetIte;
		typedef SceneNodeMap::const_iterator						SceneNodeSetConstIte;
		/// �ӽڵ㼯
		SceneNodeMap			mNodeMap;
		/// ���ڵ�
		NodePtr					mParentNode;


		/// �������
		Matrix4			mWorldMatrix;

		/// �����
		ComponentMap			mComponentMap;

		/// �ڵ��ǩID
		u16						mTagID;

		/// �ڵ��ID
		u16						mLayerID;

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
