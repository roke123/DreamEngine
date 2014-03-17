#ifndef __DRESCENEMANAGERDECLARATION_H__
#define __DRESCENEMANAGERDECLARATION_H__

#include "DreComplieConfig.h"
#include "DreContainer.h"
#include "DreTypes.h"
#include "DreException.h"

#include "DreMathDeclaration.h"

namespace dream
{
	class Renderable;

	class Node;
	typedef shared_ptr<Node>							NodePtr;

	class SceneNode;
	typedef shared_ptr<SceneNode>						SceneNodePtr;

	class SceneRootNode;
	typedef	shared_ptr<SceneRootNode>					SceneRootNodePtr;
	
	class EntityNode;
	typedef shared_ptr<EntityNode>						EntityNodePtr;

	class Entity;
	typedef shared_ptr<Entity>							EntityPtr;

	typedef vector<Renderable>							RenderQueue;

	class Animator;

	class Attribution;
	typedef map<string, Attribution>					AttributionMap;
	typedef AttributionMap::iterator					AttributionMapIte;
	typedef AttributionMap::const_iterator				AttributionMapConstIte;

	class ConvertibleObject;
	class ConvertibleObjectNameCmp;
	typedef shared_ptr<ConvertibleObject>				ConvertibleObjectPtr;

	class Camera;
	typedef shared_ptr<Camera>							CameraPtr;

	class DefaultCamera;
	typedef shared_ptr<DefaultCamera>					DefaultCameraPtr;

	enum RenderQueueDefualtOrder;

	template<class T>
	class RenderQueue;

	class RenderGroup;

	template<
		typename T = RenderQueueDefualtOrder
	>
	class ScreenManagerStaticConfig
	{
	public:
		typedef	T							RenderQueueOrder;
		typedef RenderQueue<T>				RenderQueue;
	};

	typedef ScreenManagerStaticConfig<>		SMSC;

}	// end namesapce dream

#endif	// end __DRESCENEMANAGERDECLARATION_H__