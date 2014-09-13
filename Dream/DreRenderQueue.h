#ifndef __DRERENDERQUEUE_H__
#define	__DRERENDERQUEUE_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	

	enum RENDER_QUEUE_GROUP_ID : u16
	{
		/// 背景渲染层
		RENDER_QUEUE_BACKGROUND = 1000,
		/// 默认渲染层，没有指定渲染层的 renderable 均属于此渲染层
		RENDER_QUEUE_DEFALUT = 2000,
		/// 透明度测试
		RENDER_QUEUE_ALPHA_TEST = 3000,
		/// after RENDER_QUEUE_ALPHA_TEST
		RENDER_QUEUE_GEOMETRY = 4000,
		/// 透明层，在除了 RENDER_QUEUE_OVERLAY 渲染队列中的对象渲染后渲染
		RENDER_QUEUE_TRANSPARENT = 5000,
		/// 覆盖层，在其他所有对象渲染以后在进行渲染，可用于UI
		RENDER_QUEUE_OVERLAY = 6000,
	};

	class RenderQueue
	{
	public:
		typedef map<u16, RenderQueueGroup>				RenderQueueGroupMap;
		typedef RenderQueueGroupMap::iterator			GourpMapIte;
		typedef	RenderQueueGroupMap::const_iterator		GroupMapConstIte;

	protected:
		RenderQueueGroupMap								mGroups;

	public:
		/** 虚析构函数 */
		virtual ~RenderQueue() {}

		/** 清空渲染队列 */
		void Clear();

		/** 取得渲染队列
		* @ param
		*	qid		u16		渲染队列ID
		*/
		RenderQueueGroup* GetQueueGroup(u16 qid);

		/** 向渲染队列中添加一个Renderable对象
		* @param	
		*	pRend	RenderablePtr	可渲染对象指针
		* @param
		*	groupID		u16			渲染组ID，内建ID参考 RENDER_QUEUE_GROUP_ID
		* @note
		*	groupID参数可选，默认值为 RENDER_QUEUE_DEFALUT
		*/
		void AddRenderable(RenderablePtr pRend, u16 groupID = RENDER_QUEUE_DEFALUT);

		/** 取 GroupMap 初始迭代器，用于遍历RenderQueue */
		RenderQueue::GourpMapIte begin(void);
		RenderQueue::GroupMapConstIte begin(void) const;

		/** 取 GroupMap 终止迭代器，用于遍历RenderQueue */
		RenderQueue::GourpMapIte end(void);
		RenderQueue::GroupMapConstIte end(void) const;

		/** Sets whether or not the queue will split passes by their lighting type,
		ie ambient, per-light and decal.
		*/
		void setSplitPassesByLightingType(bool split);

		/** Gets whether or not the queue will split passes by their lighting type,
		ie ambient, per-light and decal.
		*/
		bool getSplitPassesByLightingType(void) const;

		/** Sets whether or not the queue will split passes which have shadow receive
		turned off (in their parent material), which is needed when certain shadow
		techniques are used.
		*/
		void setSplitNoShadowPasses(bool split);

		/** Gets whether or not the queue will split passes which have shadow receive
		turned off (in their parent material), which is needed when certain shadow
		techniques are used.
		*/
		bool getSplitNoShadowPasses(void) const;

		/** Sets whether or not objects which cast shadows should be treated as
		never receiving shadows.
		*/
		void setShadowCastersCannotBeReceivers(bool ind);

		/** Gets whether or not objects which cast shadows should be treated as
		never receiving shadows.
		*/
		bool getShadowCastersCannotBeReceivers(void) const;

		/** Set a renderable listener on the queue.
		@remarks
		There can only be a single renderable listener on the queue, since
		that listener has complete control over the techniques in use.
		*/
		void setRenderableListener(RenderableListener* listener)
		{
			mRenderableListener = listener;
		}

		RenderableListener* getRenderableListener(void) const
		{
			return mRenderableListener;
		}

		/** Merge render queue.
		*/
		void merge(const RenderQueue* rhs);
		/** Utility method to perform the standard actions associated with
		getting a visible object to add itself to the queue. This is
		a replacement for SceneManager implementations of the associated
		tasks related to calling MovableObject::_updateRenderQueue.
		*/
		void processVisibleObject(MovableObject* mo,
			Camera* cam,
			bool onlyShadowCasters,
			VisibleObjectsBoundsInfo* visibleBounds);
	};	// end class RenderGroup

}	// end namespace dream

#endif // end __DRERENDERQUEUE_H__
