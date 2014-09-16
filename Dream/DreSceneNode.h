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
		/** 节点名比较函数对象
		*/
		class SceneNodeNameCmp
		{
		public:
			/** 比较函数
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
			/** 构造函数
			*/
			NodeAttchObjectEvent(const string& name) : Event(name)
			{
				// 留空
			}

			/** 通知处理器函数
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

		
		/** 节点处理事件
		*/
		typedef function<void (SceneNodePtr&)> SceneNodeEventHandler;
		class SceneNodeEvent : public Event<SceneNodeEventHandler>
		{
		public:
			/** 构造函数
			*/
			SceneNodeEvent(const string& name) : Event(name)
			{
				// 留空
			}

			/** 通知处理器函数
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

		
		/** 绑定ChildSceneNode事件
		*/
		typedef function<void (SceneNodePtr&, SceneNodePtr&)> ChildSceneNodeEventHandler;
		class ChildSceneNodeEvent : public Event<ChildSceneNodeEventHandler>
		{
		public:
			/** 构造函数
			*/
			ChildSceneNodeEvent(const string& name) : Event(name)
			{
				// 留空
			}

			/** 通知处理器函数
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
	
		/** 构造函数 */
		explicit SceneNode(
			const string& name, u16 tagID, u16 layerID,
			const Vector3& initialPosition = Vector3::ZeroVector, 
			const Vector3& initialScale = Vector3::ZeroVector,
			const Quaternion& initialOrientation = Quaternion::UnitQuaternion);

		/** 相对于当前位置平移一段距离
		* @param	x		在X轴方向的平移距离
		* @param	y		在Y轴方向的平移距离
		* @param	z		在Z轴方向的平移距离
		*/
		void SetAbsoluteTranslation(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mLocalPosition = Vector3(x, y, z); }
		void SetAbsoluteTranslation(const Vector3& tranlation) { _NotifyTransformChanged(); mLocalPosition = tranlation; }
		/** 取得相对于当前位置的平移距离 */
		Vector3 GetAbsolutionTranslation() const { return mLocalPosition; }

		/** 相对于当前模型大小的放大倍数
		* @param	x		在X轴方向的放大倍数
		* @param	y		在Y轴方向的放大倍数
		* @param	z		在Z轴方向的放大倍数
		*/
		void SetLocalScale(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mLocalScale = Vector3(x, y, z); }
		void SetLocalScale(const Vector3& scale) { _NotifyTransformChanged(); mLocalScale = scale; }
		/** 取得相对于当前模型大小的放大倍数 */
		Vector3 GetLocalScale() const { return mLocalScale; }

		/** 相对于当前模型方向的旋转方向 */
		void SetLocalRotation(const Quaternion& orientation) { _NotifyTransformChanged(); mLocalOrientation = orientation; }
		/** 取得相对于当前模型方向的旋转方向 */
		Quaternion GetLocalRotation() const { return mLocalOrientation; }

		/** 相对于父节点平移一段距离
		* @param	x		在X轴方向的平移距离
		* @param	y		在Y轴方向的平移距离
		* @param	z		在Z轴方向的平移距离
		*/
		void SetRelativeTranslation(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mRelativePosition = Vector3(x, y, z); }
		void SetRelativeTranslation(const Vector3& tranlation) { _NotifyTransformChanged(); mRelativePosition = tranlation; }
		/** 取得相对于父节点的平移距离 */
		Vector3 GetRelativeTranslation() const { return mRelativePosition; }

		/** 相对于父节点大小的放大倍数
		* @param	x		在X轴方向的放大倍数
		* @param	y		在Y轴方向的放大倍数
		* @param	z		在Z轴方向的放大倍数
		*/
		void SetRelativeScale(f32 x, f32 y, f32 z) { _NotifyTransformChanged(); mRelativeScale = Vector3(x, y, z); }
		void SetRelativeScale(const Vector3& scale) { _NotifyTransformChanged(); mRelativeScale = scale; }
		/** 取得相对于父节点大小的放大倍数 */
		Vector3 GetRelativeScale() const { return mRelativeScale; }

		/** 相对于父节点方向的旋转方向 */
		void SetRelativeRotation(const Quaternion& orientation) { _NotifyTransformChanged(); mRelativeOrientation = orientation; }
		/** 取得相对于父节点方向的旋转方向*/
		Quaternion GetRelativeRotation() const { return mRelativeOrientation; }
		
		/** 取得最终坐标
		* @note override by Node
		*/
		virtual Vector3 _GetFinalPosition() { _ForceUpwardTransformUpdate(); return mFinalPosition; };
		/** 取得最终方向
		* @note override by Node
		*/
		virtual Quaternion _GetFinalOrientation() override { _ForceUpwardTransformUpdate(); return mFinalOrientation; };
		/** 取得最终Scale
		* @note override by Node
		*/
		virtual Vector3 _GetFinalScale() override { _ForceUpwardTransformUpdate(); return mFinalScale; };

		/** 取得*/
		Vector3 _GetForward() { return Vector3::Forward *_GetFinalOrientation().QuaternionToMatrix4(); }

		/** 渲染前更新节点，计算当前节点属性
		* @note override by Node
		*/
		virtual void _PreRenderUpdate() override;

		/** 渲染后更新节点，计算当前节点属性
		* @note override by Node
		*/
		virtual void _PostRenderUpdate() override;

		/** 逻辑更新节点
		* @note override by Node
		*/
		virtual void _FixedUpdate() override;

	protected:
		void _TransformUpdate();

		void _ForceUpwardTransformUpdate();

		/** 通知父节点本节点的 transform 属性发生改变 */
		void _NotifyTransformChanged();

	public:

		/** 取得碰撞盒
		* @note override by Node
		*/
		virtual AABB3 GetBoundBox() const override { return AABB3::EmptyAABB3; }

		/** 通知父节点本节点属性改变需要更新，debug状态下会检查是否存在同名节点
		* @note override by Node
		*/
		void _NotifyNeedUpdate() override;

		/** 查找可见元素
		* @note override by Node
		*/
		void _FindVisibleObject(const CameraPtr& camera) override {};
		
		/** 绑定一个子节点
		* @param	name		子节点名
		* @param	child		子节点指针
		*/
		void AttachChildNode(string name, SceneNodePtr child);
		/** 解除子节点的绑定
		* @param	name		子节点名
		* @return				返回子节点的右值引用
		*/
		SceneNodePtr DetachChildNode(const string& name);				
		/** 获取一个节点名为name的节点(包括检索子节点，如有)
		*/
		SceneNodePtr FindSubNodeByName(const string& name);
		
		/** 设置该节点是否可见 */
		void SetEnable(bool enable = true) { mIsEnable = enable; }
		/** 判断该节点是否可见 */
		bool IsEnable() const { return mIsEnable; }

		/** 获取父节点指针,直接绑定在根节点下的节点会返回nullptr */
		SceneNodePtr GetParent() const;

		/** 获取节点名 */
		string GetNodeName() const { return mNodeName; }

		/** 设置节点名 */
		void _SetNodeName(const string& nodeName) { mNodeName = nodeName; }

		/** 设置父节点指针 */
		void _SetParent(const NodePtr& parent) { mParentNode = parent; }

		/** 标志本节点需要更新 */
		void _MarkNeedUpdate() { mChildrenTransformUpdated = false; mTransformUpdated = false; }

		/** 计算世界矩阵 */
		Matrix4 SceneNode::GetWorldMatrix() const;

		/** 取得当前节点标签ID */
		TagID GetTagID() { return mTagID; }
		void SetTagID(TagID id) { mTagID = id;  }

		/** 取得当前节点层ID */
		LayerID GetLayerID() { return mLayerID; }
		void SetLayerID(LayerID id) { mLayerID = id; }

	private:
		
		/// 经相对坐标转换和绝对坐标转换后的最终坐标
		Vector3					mFinalPosition;
		/// 经相对坐标转换和绝对坐标转换后的放大倍数
		Vector3					mFinalScale;
		/// 经相对坐标转换和绝对坐标转换后的模型方向
		Quaternion				mFinalOrientation;

		/// 模型本地坐标(相对于上一位置)
		Vector3					mLocalPosition;
		/// 模型本地放大倍数(相对于上一放大倍数)
		Vector3					mLocalScale;
		/// 模型本地方向(相对于上一方向)
		Quaternion				mLocalOrientation;

		/// 模型相对坐标(相对于父节点位置)
		Vector3					mRelativePosition;
		/// 模型相对放大倍数(相对于父节点放大倍数)
		Vector3					mRelativeScale;
		/// 模型相对方向(相对于父节点方向)
		Quaternion				mRelativeOrientation;

		/// 节点名
		string					mNodeName;

		/// 表示该节点是否可用
		bool					mIsEnable;
		/// 本节点属性已更新
		bool					mTransformUpdated;
		/// 本节点的子节点是否已更新
		bool					mChildrenTransformUpdated;

		typedef map<string, SceneNodePtr, SceneNodeNameCmp>			SceneNodeMap;
		typedef SceneNodeMap::iterator								SceneNodeSetIte;
		typedef SceneNodeMap::const_iterator						SceneNodeSetConstIte;
		/// 子节点集
		SceneNodeMap			mNodeMap;
		/// 父节点
		NodePtr					mParentNode;


		/// 世界矩阵
		Matrix4			mWorldMatrix;

		/// 组件集
		ComponentMap			mComponentMap;

		/// 节点标签ID
		u16						mTagID;

		/// 节点层ID
		u16						mLayerID;

	public:
		/// 绑定实体事件
		NodeAttchObjectEvent	OnAttachObject;
		/// 节点更新事件
		SceneNodeEvent			OnUpdateNode;
		/// 节点渲染事件
		SceneNodeEvent			OnRenderNode;
		/// 节点解绑定实体事件
		NodeAttchObjectEvent	OnDetachObject;
		/// 节点绑定子节点事件
		ChildSceneNodeEvent		OnAttachChildNode;
		/// 节点解绑定子节点事件
		ChildSceneNodeEvent		OnDetachChildNode;

	};	// end class SceneNode

}	// end namespace dream

#endif // end __DRESCENENODE_H__
