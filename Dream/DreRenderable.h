#ifndef __DRERENDERABLE_H__
#define __DRERENDERABLE_H__

/// render system
#include "DreRenderDeclaration.h"

#include "DreEvent.h"
#include "DreComponent.h"

namespace dream
{
	typedef function<void (RenderSystem& renderSystem, Renderable& object)> RenderEventHandler;

	/** ����һ�����������Ⱦ��λ */
	class Renderable : public Component
	{
		class RenderEvent final : public Event<RenderEventHandler>
		{
		public:
			/** ���캯��
			*/
			RenderEvent(const string& name) : Event(name) {}

			void _Notify(RenderSystem& renderSystem, Renderable& object)
			{
				HandlerIte ite = mHandlerList.begin();
				for(; ite != mHandlerList.end(); ++ ite)
				{
					(*ite)->operator()(renderSystem, object);
				}
			}
		};

	public:
		/** ���캯��
		*/
		Renderable();

		/** ��������
		*/
		virtual ~Renderable() {};

		virtual void _FillRenderParameters(RenderSystem* renderSystem);

		/** ȡ��Renderable����ײ��
		*/
		virtual const AABB3& GetBoundBox() = 0;

		/** ��Ⱦ�¼�����˳��
		* ͨ��OnPrePassRender�����޸���Ⱦ˳��
		* ͨ��OnPreRender�����޸���Ⱦ����
		* ͨ��OnPastRender���Իָ�ԭ��Ⱦ����
		* ͨ��OnPastPassRender�����ظ���Ⱦͬһ��Ⱦ����
		* OnPrePassRender -> OnPreRender -> Render -> OnPastRender -> OnPastPassRender 
		*/
		/// ��Ⱦǰ�¼�
		RenderEvent OnPreRender;
		/// ��Ⱦ���¼�
		RenderEvent OnPastRender;
	};

}	// end namespace dream

#endif	// end __DRERENDERABLE_H__