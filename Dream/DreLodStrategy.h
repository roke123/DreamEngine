#ifndef __DRE_LOD_STRATEGY_H__
#define __DRE_LOD_STRATEGY_H__

#include "DreSceneManagerDeclaration.h"

#include "DreComponent.h"

namespace dream
{

	class LodStrategy : public Component
	{
	private:
		typedef vector<u32>						LodValueList;
		typedef LodValueList::iterator			LodValueListIte;
		typedef LodValueList::const_iterator	LodValueListConstIte;

	public:
		LodStrategy(SceneNodePtr& sceneNode) : Component(sceneNode, COMPONENT_LOD_STRATEGY)
		{
			// Áô¿Õ
		}

		void InsertLodValue(u16 lodLevel, u32 lodValue)
		{
		}

	private:
		LodValueList			mLodValueList;

	};	// end of class LodStrategy

}

#endif	//