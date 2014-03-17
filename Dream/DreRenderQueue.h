#ifndef __DRERENDERQUEUE_H__
#define	__DRERENDERQUEUE_H__

#include <type_traits>

#include "DreSceneManagerDeclaration.h"

#include "DreException.h"
#include "DreUtility.h"

#include "DreRenderQueueImpl.h"

#include <functional>

namespace dream
{
	/** 定义RenderQueue渲染顺序的默认enum量
    */
    enum RenderQueueDefualtOrder
    {
		/// 定义渲染顺序
		RENDER_QUEUE_MIN			= -10,
		RENDER_QUEUE_ORDER_0		= 0,
		RENDER_QUEUE_ORDER_1		= 10,
        RENDER_QUEUE_ORDER_2		= 20,
        RENDER_QUEUE_ORDER_3		= 30,
        RENDER_QUEUE_ORDER_4		= 40,
		RENDER_QUEUE_ORDER_5		= 50,
        RENDER_QUEUE_ORDER_6		= 60,
        RENDER_QUEUE_ORDER_7		= 70,
        RENDER_QUEUE_ORDER_8		= 80,
        RENDER_QUEUE_ORDER_9		= 90,
		RENDER_QUEUE_ORDER_10		= 100,
		RENDER_QUEUE_MAX			= 110,

		/// Screen之前的渲染
		RENDER_QUEUE_ORDER_BEFORE_SCREEN		= RENDER_QUEUE_ORDER_3,
		/// Screen的渲染
		RENDER_QUEUE_ORDRE_SCREEN				= RENDER_QUEUE_ORDER_5,
		/// Screen之后的渲染					
		RENDER_QUEUE_ORDER_AFTRE_SCREEN			= RENDER_QUEUE_ORDER_7,
        /// 用于最早的渲染对象，像background
		RENDER_QUEUE_ORDER_BACKGROUND			= RENDER_QUEUE_ORDER_0,
        /// First queue (after backgrounds), used for skyboxes if rendered first
		RENDER_QUEUE_ORDER_SKIES_EARLY			= RENDER_QUEUE_ORDER_1,
        /// Penultimate queue(before overlays), used for skyboxes if rendered last
		RENDER_QUEUE_SKIES_LATE					= RENDER_QUEUE_ORDER_9,
        /// 用于一定在最后渲染的对象
		RENDER_QUEUE_OVERLAY					= RENDER_QUEUE_ORDER_10, 
    };

	template<class T>
	class RenderQueue
	{
	public:
		typedef T RenderQueueOrder;

		RenderQueue()
		{
			pImpl = new RenderQueueImpl<T, std::is_enum<T>::value>();
		}

		~RenderQueue()
		{
			SafeDelete(pImpl);
		}

		RenderQueueImpl<T, std::is_enum<T>::value>* pImpl; 
	};
}	// end namespace dream

#endif // end __DRERENDERQUEUE_H__
