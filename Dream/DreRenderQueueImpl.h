#ifndef __DRERENDERQUEUEIMPL_H__
#define __DRERENDERQUEUEIMPL_H__

#include "DreSceneManager.h"

namespace dream
{
	/** 渲染队列基模板
	* @template			Enum		使其匹配一个enum类型，作为BaseRenderQueue的顺序依据
	*/ 
	template<typename Enum, bool>
	class RenderQueueImpl;

	template<typename Enum>
	class RenderQueueImpl<Enum, true>
	{
	public:
		typedef Enum			RenderOrder

	private:
		typedef template map<RenderOrder, RenderGroup>::value		RenderGroupMap;
		RenderQueueGroupMap			mRenderGroupMap;
	};

	template<typename NotEnum>
	class RenderQueueImpl<NotEnum, false>
	{
	public:
		RenderQueueImpl()
		{
			assert(false || "不应该为RenderQueue指定非enum类型值");
		}

		static RenderQueueImpl* warming;
	};

	template<typename T>
	RenderQueueImpl<T, false>* RenderQueueImpl<T, false>::warming = new RenderQueueImpl<T, false>();

}	// end namespace dream

#endif // !__DRERENDERQUEUEIMP_H__

	