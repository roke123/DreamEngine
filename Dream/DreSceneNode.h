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
		/** 私有构造函数，用于构造一个只有名字的SceneNode */
		explicit SceneNode(const string& name);
	
		/** 构造函数 */
		explicit SceneNode(const Vector3& initialPosition, const Vector3& initialScale,
			const Quaternion& initialOrientation);

		/** 相对于当前位置平移一段距离
		* @param	x		在X轴方向的平移距离
		* @param	y		在Y轴方向的平移距离
		* @param	z		在Z轴方向的平移距离
		*/
		void SetAbsoluteTranslation(f32 x, f32 y, f32 z) { _NeedUpdate(); mLocalPosition = Vector3(x, y, z); }
		void SetAbsoluteTranslation(const Vector3& tranlation) { _NeedUpdate(); mLocalPosition = tranlation; }
		/** 取得相对于当前位置的平移距离 */
		Vector3 GetAbsolutionTranslation() const { return mLocalPosition; }

		/** 相对于当前模型大小的放大倍数
		* @param	x		在X轴方向的放大倍数
		* @param	y		在Y轴方向的放大倍数
		* @param	z		在Z轴方向的放大倍数
		*/
		void SetAbsoluteScale(f32 x, f32 y, f32 z) { _NeedUpdate(); mLocalScale = Vector3(x, y, z); }
		void SetAbsoluteScale(const Vector3& scale) { _NeedUpdate(); mLocalScale = scale; }
		/** 取得相对于当前模型大小的放大倍数 */
		Vector3 GetAbsolutionScale() const { return mLocalScale; }

		/** 相对于当前模型方向的旋转方向 */
		void SetAbsoluteRotation(const Quaternion& orientation) { _NeedUpdate(); mLocalOrientation = orientation; }
		/** 取得相对于当前模型方向的旋转方向 */
		Quaternion GetAbsolutionRotation() const { return mLocalOrientation; }

		/** 相对于父节点平移一段距离
		* @param	x		在X轴方向的平移距离
		* @param	y		在Y轴方向的平移距离
		* @param	z		在Z轴方向的平移距离
		*/
		void SetRelativeTranslation(f32 x, f32 y, f32 z) { _NeedUpdate(); mRelativePosition = Vector3(x, y, z); }
		void SetRelativeTranslation(const Vector3& tranlation) { _NeedUpdate(); mRelativePosition = tranlation; }
		/** 取得相对于父节点的平移距离 */
		Vector3 GetRelativeTranslation() const { return mRelativePosition; }

		/** 相对于父节点大小的放大倍数
		* @param	x		在X轴方向的放大倍数
		* @param	y		在Y轴方向的放大倍数
		* @param	z		在Z轴方向的放大倍数
		*/
		void SetRelativeScale(f32 x, f32 y, f32 z) { _NeedUpdate(); mRelativeScale = Vector3(x, y, z); }
		void SetRelativeScale(const Vector3& scale) { _NeedUpdate(); mRelativeScale = scale; }
		/** 取得相对于父节点大小的放大倍数 */
		Vector3 GetRelativeScale() const { return mRelativeScale; }

		/** 相对于父节点方向的旋转方向 */
		void SetRelativeRotation(const Quaternion& orientation) { _NeedUpdate(); mRelativeOrientation = orientation; }
		/** 取得相对于父节点方向的旋转方向*/
		Quaternion GetRelativeRotation() const { return mRelativeOrientation; }
		
		/** 取得最终坐标
		* @note override by Node
		*/
		Vector3 _GetFinalPosition() const override { return mFinalPosition; };
		/** 取得最终方向
		* @note override by Node
		*/
		Quaternion _GetFinalOrientation() const override { return mFinalOrientation; };
		/** 取得最终Scale
		* @note override by Node
		*/
		Vector3 _GetFinalScale() const override { return mFinalScale; };

		/** 获取转换矩阵
		* @note override by Node
		*/
		Matrix4 GetWorldMatrix() const override;

		/** 更新节点，计算当前节点属性
		* @note override by Node
		*/
		void _Update() override;

		/** 取得碰撞盒
		* @note override by Node
		*/
		AABB3 GetBoundBox() const override { return mBoundsBox; }

		/** 通知父节点绑定了一个实体
		* @note override by Node
		*/
		void _NotifyChanged() override;

		/** 查找可见元素
		* @note override by Node
		*/
		void _FindVisibleObject(const CameraPtr& camera) override = 0;
		
		/** 绑定一个子节点
		* @param	name		子节点名
		* @param	child		子节点指针
		*/
		void AttachChildNode(const string& name, SceneNodePtr& child);
		/** 解除子节点的绑定
		* @param	name		子节点名
		* @return				返回子节点的右值引用
		*/
		SceneNodePtr DetachChildNode(const string& name);				
		/** 获取一个节点名为name的节点(包括检索子节点，如有)
		*/
		SceneNodePtr FindSubNodeByName(const string& name);
		
		/** 设置该节点是否可见 */
		void SetVisiable(bool enable = true) { mIsVisiable = enable; }
		/** 判断该节点是否可见 */
		bool IsVisible() const { return mIsVisiable; }

		/** 获取父节点指针 */
		NodePtr GetParent() const { return mParentNode; };

		/** 绑定一个ConvertibleObject
		*/
		void AttachConvertibleObject(ConvertibleObjectPtr& object);

		/** 解绑定一个ConvertibleObject
		*/
		void DetachConvertibleObject(const string& name);

		/** 获取节点名 */
		string GetNodeName() const { return mNodeName; }

		/** 设置节点名 */
		void _SetNodeName(const string& nodeName) { mNodeName = nodeName; }

		/** 设置父节点指针 */
		void _SetParent(const NodePtr& parent) { _NeedUpdate(); mParentNode = parent; }
		
		/** 标志节点需要更新 */
		void _NeedUpdate() { mIsUpdated = false; mRecaleWorldMatrix = true; };

	protected:
		/** 更新碰撞盒 */
		void _UpdateBoundBox();

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
		string				mNodeName;

		/// 表示该节点是否可显示的标志
		bool				mIsVisiable;
		/// 本节点属性已更新
		bool				mIsUpdated;
		/// 节点下的子节点已更新
		bool				mIsChildrenUpdated;
		///	是否重新计算世界变换矩阵
		mutable bool		mRecaleWorldMatrix;

		/// 碰撞盒
		AABB3				mBoundsBox;
		/// 世界变换矩阵
		mutable Matrix4		mWorldMatrix;

		typedef set<SceneNodePtr, SceneNodeNameCmp>			SceneNodeSet;
		typedef SceneNodeSet::iterator					SceneNodeSetIte;
		typedef SceneNodeSet::const_iterator			SceneNodeSetConstIte;
		/// 子节点集
		SceneNodeSet			mNodeSet;
		/// 父节点
		NodePtr					mParentNode;

		typedef set<ConvertibleObjectPtr, ConvertibleObjectNameCmp>		ConvertibleObjectSet;
		typedef ConvertibleObjectSet::iterator							ConvertibleObjectSetIte;
		typedef ConvertibleObjectSet::const_iterator					ConvertibleObjectSetConstIte;
		/// 绑定对象集
		ConvertibleObjectSet	mObjectSet;

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
