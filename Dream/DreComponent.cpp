////////////////////////////////
// date: 2014/9/10 17:26
// author: zou lei
////////////////////////////////

#include "DreComponent.h"

#include "DreSceneNode.h"

namespace dream
{
	
	LayerID Component::GetLayerID()
	{
		return mParentNode->GetLayerID();
	}

}