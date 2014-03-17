#include "DreConvertibleObject.h"

namespace dream
{

	ConvertibleObject::ConvertibleObject(const string& name) : 
		mName(name),
		OnObjectAttached("ConvertibleObject::OnObjectAttached"),
		OnObjectDetached("ConvertibleObject::OnObjectAttached")
	{
		// ����
	}

	/** �Ѷ���󶨵�ĳ���ڵ� */
	void ConvertibleObject::_AttachedToSceneNode(SceneNodePtr& node) 
	{
		DreAssert(!IsBoundToSceneNode(), "�ö����Ѱ󶨵��ڵ�");

		mBindingNode = node; 
		OnObjectAttached._Notify(shared_from_this(), mBindingNode); 
	}

	/** �Ѷ���Ӱ󶨽ڵ��Ͻ���� */
	void ConvertibleObject::_DetachedToSceneNode() 
	{
		DreAssert(!IsBoundToSceneNode(), "�ö����Ѱ󶨵��ڵ�");

		mBindingNode = nullptr; 
		OnObjectDetached._Notify(shared_from_this(), mBindingNode); 
	}

}	// end namespace dream