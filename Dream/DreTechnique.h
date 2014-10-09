/////////////////////////////////////
// date: 2014/9/11 17:24
// author: zou lei
/////////////////////////////////////

#ifndef __DRE_TECHNIQUE_H__
#define __DRE_TECHNIQUE_H__

#include "DreSceneManagerDeclaration.h"

#include "DreMaterial.h"

namespace dream
{

	class Technique
	{
	private:
		Materail* mParent;

	public:
		Material* GetMaterial();
	};	// end of class Technique

}	// end of namespace dream

#endif	// end of __DRE_TECHNIQUE_H__