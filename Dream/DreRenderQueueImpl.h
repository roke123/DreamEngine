#ifndef __DRERENDERQUEUEIMPL_H__
#define __DRERENDERQUEUEIMPL_H__

#include "DreSceneManager.h"

namespace dream
{
	/** ��Ⱦ���л�ģ��
	* @template			Enum		ʹ��ƥ��һ��enum���ͣ���ΪBaseRenderQueue��˳������
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
			assert(false || "��Ӧ��ΪRenderQueueָ����enum����ֵ");
		}

		static RenderQueueImpl* warming;
	};

	template<typename T>
	RenderQueueImpl<T, false>* RenderQueueImpl<T, false>::warming = new RenderQueueImpl<T, false>();

}	// end namespace dream

#endif // !__DRERENDERQUEUEIMP_H__

	