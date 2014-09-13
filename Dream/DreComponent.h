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

	/** 挂载于Scene Node上的组件用于实现各种功能
	*/
	class Component : public std::enable_shared_from_this<Component>
	{
	protected:
		/// 组件类型
		COMPONENT_TYPE mComponentType;

		/// 当前挂载的Scene Node
		SceneNodePtr mParentNode;

		/// 组件是否有效
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
		/// 取得绑定的SceneNode
		SceneNodePtr GetSceneNode() { return mParentNode; }

		/** 复制组件到其他场景节点 
		* @param
		*	sceneNode		SceneNodePtr		新绑定的场景节点
		*/
		void CloneTo(SceneNodePtr& sceneNode);

		/// 组件是否有效
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

		/// 开启组件操作
		virtual void _OnEnable() {};

		/// 关闭组件操作
		virtual void _OnDisable() {};

		/// 渲染前更新组件
		virtual void _PreRenderUpdate() {}

		/// 渲染后更新组件
		virtual void _PostRenderUpdate() {}

		/// 逻辑更新组件
		virtual void _FixedUpdate() {};
	};

}

#endif	// end of __DRECOMPONENT_H__