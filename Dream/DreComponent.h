/////////////////////////////////
// date: 2014/9/4 17:38
// author: zou lei
////////////////////////////////

#ifndef __DRECOMPONENT_H__
#define __DRECOMPONENT_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	enum COMPONENT_TYPE
	{
		COMPONENT_LIGHT,
	};

	/** ������Scene Node�ϵ��������ʵ�ָ��ֹ���
	*/
	class Component : public std::enable_shared_from_this<Component>
	{
	protected:
		/// �������
		COMPONENT_TYPE mComponentType;

		/// ��ǰ���ص�Scene Node
		SceneNodePtr mParentNode;

		/// ����Ƿ���Ч
		bool mIsEnable;

	public:
		Component(SceneNodePtr& sceneNode, COMPONENT_TYPE type) : mParentNode(sceneNode), mIsEnable(true), mComponentType(type)
		{
			_OnStartUp();
		}

		virtual ~Component() 
		{
			_OnShutDown();
		}

	private:
		Component(const Component&);
		Component operator = (const Component&);

	public:
		/// ȡ�ð󶨵�SceneNode
		SceneNodePtr GetSceneNode() { return mParentNode; }

		/** ������������������ڵ� 
		* @param
		*	sceneNode		SceneNodePtr		�°󶨵ĳ����ڵ�
		*/
		void CloneTo(SceneNodePtr& sceneNode);

		/// ����Ƿ���Ч
		bool GetEnable() { return mIsEnable; }
		void SetEnable(bool enable) 
		{ 
			mIsEnable = enable; 
			if (mIsEnable) {
				this->_OnEnable();
			}
			else{
				this->_OnDisable();
			}
		}

		LayerID GetLayerID();

		virtual void _OnStartUp() {};

		/// 
		virtual void _OnShutDown() {};

		/// �����������
		virtual void _OnEnable() {};

		/// �ر��������
		virtual void _OnDisable() {};

		/// ��Ⱦǰ�������
		virtual void _PreRenderUpdate() {}

		/// ��Ⱦ��������
		virtual void _PostRenderUpdate() {}

		/// �߼��������
		virtual void _FixedUpdate() {};
	};

}

#endif	// end of __DRECOMPONENT_H__