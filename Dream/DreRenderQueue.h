#ifndef __DRERENDERQUEUE_H__
#define	__DRERENDERQUEUE_H__

#include "DreSceneManagerDeclaration.h"

namespace dream
{
	

	enum RENDER_QUEUE_GROUP_ID : u16
	{
		/// ������Ⱦ��
		RENDER_QUEUE_BACKGROUND = 1000,
		/// Ĭ����Ⱦ�㣬û��ָ����Ⱦ��� renderable �����ڴ���Ⱦ��
		RENDER_QUEUE_DEFALUT = 2000,
		/// ͸���Ȳ���
		RENDER_QUEUE_ALPHA_TEST = 3000,
		/// after RENDER_QUEUE_ALPHA_TEST
		RENDER_QUEUE_GEOMETRY = 4000,
		/// ͸���㣬�ڳ��� RENDER_QUEUE_OVERLAY ��Ⱦ�����еĶ�����Ⱦ����Ⱦ
		RENDER_QUEUE_TRANSPARENT = 5000,
		/// ���ǲ㣬���������ж�����Ⱦ�Ժ��ڽ�����Ⱦ��������UI
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
		/** ���������� */
		virtual ~RenderQueue() {}

		/** �����Ⱦ���� */
		void Clear();

		/** ȡ����Ⱦ����
		* @ param
		*	qid		u16		��Ⱦ����ID
		*/
		RenderQueueGroup* GetQueueGroup(u16 qid);

		/** ����Ⱦ���������һ��Renderable����
		* @param	
		*	pRend	RenderablePtr	����Ⱦ����ָ��
		* @param
		*	groupID		u16			��Ⱦ��ID���ڽ�ID�ο� RENDER_QUEUE_GROUP_ID
		* @note
		*	groupID������ѡ��Ĭ��ֵΪ RENDER_QUEUE_DEFALUT
		*/
		void AddRenderable(RenderablePtr pRend, u16 groupID = RENDER_QUEUE_DEFALUT);

		/** ȡ GroupMap ��ʼ�����������ڱ���RenderQueue */
		RenderQueue::GourpMapIte begin(void);
		RenderQueue::GroupMapConstIte begin(void) const;

		/** ȡ GroupMap ��ֹ�����������ڱ���RenderQueue */
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
