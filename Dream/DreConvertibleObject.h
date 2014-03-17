#ifndef __DRECONVERTIBLEOBJECT_H__
#define __DRECONVERTIBLEOBJECT_H__

#include "DreSceneManagerDeclaration.h"

#include "DreEvent.h"
#include "DreAttribution.h"
#include "AABB3.h"

namespace dream
{

	/** �ɱ任����ָ��ͼ�п��������Ϊ�����仯��ʵ����󣬿ɰ󶨵�һ��Node��
	*/
	class ConvertibleObject : public std::enable_shared_from_this<ConvertibleObject>
	{
		friend class ConvertibleObjectNameCmp;

	public:
		/// ����ConvertibleObjectEvent�ĺ�����ʽ
		typedef function<void (ConvertibleObjectPtr, SceneNodePtr&)> BindingObjectToNodeEventHandler;
		class BindingObjectToNodeEvent : public Event<BindingObjectToNodeEventHandler>
		{
		public:
			BindingObjectToNodeEvent(const string& name) : Event(name)
			{
				// ����
			}

			void _Notify(ConvertibleObjectPtr object, SceneNodePtr& node)
			{
				HandlerIte ite = mHandlerList.begin();
				for(; ite != mHandlerList.end(); ++ ite)
				{
					// ���ô�����
					(*ite)->operator()(object, node);
				}
			}
		};

	public:
		/** ���캯��
		*/
		explicit ConvertibleObject(const string& name);

		/** ���������� */
		virtual ~ConvertibleObject() { /** ���� */ }

	private:
		/** ��ֹ���ƹ��캯��
		* ConvertibleObject(const ConvertibleObject&) = delete; ��֧�ָ��﷨
		*/
		ConvertibleObject(const ConvertibleObject&);

	public:
		virtual void UpdateRenderQueue(RenderQueue* renderQueue) {};

		template<typename ValueType>
		void InsertAttribution(const string& attrName, const ValueType& value)
		{
			// Debug״̬�¼���Ƿ�����ͬ������
#			if defined(DEBUG) || defined(_DEBUG)
			AttributionMapIte ite = mAttributions.find(attrName);
			DreAssert(ite == mAttributions.end(), "ConvertibleObject�д�����ͬ������");
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
			// ����Ƿ�����ͬ������		
			DreAssert(ite != mAttributions.end(), "ConvertibleObject�в�������ͬ������");

			ite->second = value;
		}

		template<typename ValueType>
		ValueType GetAttribution(const string& attrName)
		{
			AttributionMapIte ite = mAttributions.find(attrName);
			// ����Ƿ�����ͬ������	
			DreAssert(ite != mAttributions.end(), "ConvertibleObject�в�������ͬ������");

			return ite->second.Get<ValueType>();
		}

		/** ȡ�ö����� */
		string GetName() const { return mName; }

		/** ȡ�ð󶨵�Node */
		SceneNodePtr GetBindingNode() { return mBindingNode; }

		/** ȡ�ð󶨵�Node */
		const SceneNodePtr GetBindingNode() const { return mBindingNode; }

		/** �Ƿ񱻰󶨵�ĳ��Node */
		bool IsBoundToSceneNode() const { return mBindingNode != nullptr; }

		/** �Ѷ���󶨵�ĳ���ڵ� */
		virtual void _AttachedToSceneNode(SceneNodePtr& node);

		/** �Ѷ���Ӱ󶨽ڵ��Ͻ���� */
		virtual void _DetachedToSceneNode();

		/** ȡ��ConvertibleObject��BoundingBox */
		virtual AABB3 GetBoundBox() const { return AABB3::EmptyAABB3; };

	private:
		/// ������
		string mName;
		/// �󶨵���Node�ڵ�
		SceneNodePtr mBindingNode;
		/// �Զ������Լ�
		AttributionMap mAttributions;

	public:
		/// ConvertibleObject�󶨵�Node�¼�
		BindingObjectToNodeEvent		OnObjectAttached;
		/// ConvertibleObject�󶨵�Node�¼�
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