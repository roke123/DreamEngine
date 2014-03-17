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
	/** ����RenderQueue��Ⱦ˳���Ĭ��enum��
    */
    enum RenderQueueDefualtOrder
    {
		/// ������Ⱦ˳��
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

		/// Screen֮ǰ����Ⱦ
		RENDER_QUEUE_ORDER_BEFORE_SCREEN		= RENDER_QUEUE_ORDER_3,
		/// Screen����Ⱦ
		RENDER_QUEUE_ORDRE_SCREEN				= RENDER_QUEUE_ORDER_5,
		/// Screen֮�����Ⱦ					
		RENDER_QUEUE_ORDER_AFTRE_SCREEN			= RENDER_QUEUE_ORDER_7,
        /// �����������Ⱦ������background
		RENDER_QUEUE_ORDER_BACKGROUND			= RENDER_QUEUE_ORDER_0,
        /// First queue (after backgrounds), used for skyboxes if rendered first
		RENDER_QUEUE_ORDER_SKIES_EARLY			= RENDER_QUEUE_ORDER_1,
        /// Penultimate queue(before overlays), used for skyboxes if rendered last
		RENDER_QUEUE_SKIES_LATE					= RENDER_QUEUE_ORDER_9,
        /// ����һ���������Ⱦ�Ķ���
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
