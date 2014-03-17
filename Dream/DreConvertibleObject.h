#ifndef __DRECONVERTIBLEOBJECT_H__
#define __DRECONVERTIBLEOBJECT_H__

#include "DreSceneManagerDeclaration.h"

#include "DreEvent.h"
#include "DreAttribution.h"
#include "AABB3.h"

namespace dream
{

	/** 可变换对象，指地图中可受玩家行为发生变化的实体对象，可绑定到一个Node上
	*/
	class ConvertibleObject : public std::enable_shared_from_this<ConvertibleObject>
	{
		friend class ConvertibleObjectNameCmp;

	public:
		/// 处理ConvertibleObjectEvent的函数格式
		typedef function<void (ConvertibleObjectPtr, SceneNodePtr&)> BindingObjectToNodeEventHandler;
		class BindingObjectToNodeEvent : public Event<BindingObjectToNodeEventHandler>
		{
		public:
			BindingObjectToNodeEvent(const string& name) : Event(name)
			{
				// 留空
			}

			void _Notify(ConvertibleObjectPtr object, SceneNodePtr& node)
			{
				HandlerIte ite = mHandlerList.begin();
				for(; ite != mHandlerList.end(); ++ ite)
				{
					// 调用处理函数
					(*ite)->operator()(object, node);
				}
			}
		};

	public:
		/** 构造函数
		*/
		explicit ConvertibleObject(const string& name);

		/** 虚析构函数 */
		virtual ~ConvertibleObject() { /** 留空 */ }

	private:
		/** 禁止复制构造函数
		* ConvertibleObject(const ConvertibleObject&) = delete; 不支持该语法
		*/
		ConvertibleObject(const ConvertibleObject&);

	public:
		virtual void UpdateRenderQueue(RenderQueue* renderQueue) {};

		template<typename ValueType>
		void InsertAttribution(const string& attrName, const ValueType& value)
		{
			// Debug状态下检查是否有相同属性名
#			if defined(DEBUG) || defined(_DEBUG)
			AttributionMapIte ite = mAttributions.find(attrName);
			DreAssert(ite == mAttributions.end(), "ConvertibleObject中存在相同属性名");
#			endif
			mAttributions.insert(make_pair(attrName, Attribution(value)));
		}

		template<typename ValueType>
		void RemoveAttribution(const string& attrName)
		{
			AttributionMapIte ite = mAttributions.find(attrName);
			mAttributions.erase(ite);
		}

		template<typename ValueType>
		void SetAttribution(const string& attrName, const ValueType& value)
		{
			AttributionMapIte ite = mAttributions.find(attrName);
			// 检查是否有相同属性名		
			DreAssert(ite != mAttributions.end(), "ConvertibleObject中不存在相同属性名");

			ite->second = value;
		}

		template<typename ValueType>
		ValueType GetAttribution(const string& attrName)
		{
			AttributionMapIte ite = mAttributions.find(attrName);
			// 检查是否有相同属性名	
			DreAssert(ite != mAttributions.end(), "ConvertibleObject中不存在相同属性名");

			return ite->second.Get<ValueType>();
		}

		/** 取得对象名 */
		string GetName() const { return mName; }

		/** 取得绑定的Node */
		SceneNodePtr GetBindingNode() { return mBindingNode; }

		/** 取得绑定的Node */
		const SceneNodePtr GetBindingNode() const { return mBindingNode; }

		/** 是否被绑定到某个Node */
		bool IsBoundToSceneNode() const { return mBindingNode != nullptr; }

		/** 把对象绑定到某个节点 */
		virtual void _AttachedToSceneNode(SceneNodePtr& node);

		/** 把对象从绑定节点上解除绑定 */
		virtual void _DetachedToSceneNode();

		/** 取得ConvertibleObject的BoundingBox */
		virtual AABB3 GetBoundBox() const { return AABB3::EmptyAABB3; };

	private:
		/// 对象名
		string mName;
		/// 绑定到的Node节点
		SceneNodePtr mBindingNode;
		/// 自定义属性集
		AttributionMap mAttributions;

	public:
		/// ConvertibleObject绑定到Node事件
		BindingObjectToNodeEvent		OnObjectAttached;
		/// ConvertibleObject绑定到Node事件
		BindingObjectToNodeEvent		OnObjectDetached;
	};

	class ConvertibleObjectNameCmp
	{
	public:
		bool operator () (const ConvertibleObjectPtr& lh, const ConvertibleObjectPtr& rh) const
		{
			return lh->mName.compare(rh->mName) != 0;
		}
	};

}	// end of namespace dream

#endif	// end of __DRECONNVERTIBLEOBJECT_H__