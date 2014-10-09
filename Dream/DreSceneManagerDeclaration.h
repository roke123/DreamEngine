#ifndef __DRESCENEMANAGERDECLARATION_H__
#define __DRESCENEMANAGERDECLARATION_H__

#include "DreComplieConfig.h"
#include "DreContainer.h"
#include "DreTypes.h"
#include "DreException.h"

#include "DreMathDeclaration.h"
#include "DreRenderDeclaration.h"

namespace dream
{
	class Renderable;

	class Node;
	typedef shared_ptr<Node>							NodePtr;

	class SceneNode;
	typedef shared_ptr<SceneNode>						SceneNodePtr;

	class Component;
	typedef shared_ptr<Component>						ComponentPtr;
	typedef map<u16, Component>							ComponentMap;
	typedef ComponentMap::iterator						ComponentMapIte;

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
	typedef shared_ptr<ConvertibleObject>				ConvertibleObjectPtr;

	class Camera;
	typedef shared_ptr<Camera>							CameraPtr;

	class DefaultCamera;
	typedef shared_ptr<DefaultCamera>					DefaultCameraPtr;

	class RenderQueue;
	typedef shared_ptr<RenderQueue>						RenderQueuePtr;

	class RenderQueueGroup;
	typedef shared_ptr<RenderQueueGroup>				RenderQueueGroupPtr;

	class RenderLayerGroup;
	typedef shared_ptr<RenderLayerGroup>				RenderLayerGroupPtr;

	class QueuedRenderableCollection;
	typedef shared_ptr<QueuedRenderableCollection>		QeuueRenderableCollectionPtr;

	class VertexData;
	typedef shared_ptr<VertexData>						VertexDataPtr;

	class IndexData;
	typedef shared_ptr<IndexData>						IndexDataPtr;

	class QueuedRenderableVisitor;

	typedef u16											TagID;
	typedef u16											LayerID;
	typedef list<LayerID>								LayerIDList;

	/*template<class T>
	class RenderQueue;

	template<
		typename T = RenderQueueDefualtOrder
	>
	class ScreenManagerStaticConfig
	{
	public:
		typedef	T							RenderQueueOrder;
		typedef RenderQueue<T>				RenderQueue;
	};*/

	//typedef ScreenManagerStaticConfig<>		SMSC;

}	// end namesapce dream

#endif	// end __DRESCENEMANAGERDECLARATION_H__