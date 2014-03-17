#include "DreConvertibleObject.h"

namespace dream
{

	ConvertibleObject::ConvertibleObject(const string& name) : 
		mName(name),
		OnObjectAttached("ConvertibleObject::OnObjectAttached"),
		OnObjectDetached("ConvertibleObject::OnObjectAttached")
	{
		// 留空
	}

	/** 把对象绑定到某个节点 */
	void ConvertibleObject::_AttachedToSceneNode(SceneNodePtr& node) 
	{
		DreAssert(!IsBoundToSceneNode(), "该对象已绑定到节点");

		mBindingNode = node; 
		OnObjectAttached._Notify(shared_from_this(), mBindingNode); 
	}

	/** 把对象从绑定节点上解除绑定 */
	void ConvertibleObject::_DetachedToSceneNode() 
	{
		DreAssert(!IsBoundToSceneNode(), "该对象已绑定到节点");

		mBindingNode = nullptr; 
		OnObjectDetached._Notify(shared_from_this(), mBindingNode); 
	}

}	// end namespace dream