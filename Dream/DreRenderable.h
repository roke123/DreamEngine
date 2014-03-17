#ifndef __DRERENDERABLE_H__
#define __DRERENDERABLE_H__

#include "DreSceneManagerDeclaration.h"

#include "DreRenderDeclaration.h"
#include "DreEvent.h"

namespace dream
{
	typedef function<void (RenderSystem& renderSystem, Renderable& object)> RenderEventHandler;

	class Renderable
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

		/** ��Ⱦ��Renderable
		*/
		virtual void Render(RenderSystemPtr& renderSystem) = 0;

		/** ȡ��Renderable����ײ��
		*/
		virtual const AABB3& GetBoundBox() = 0;

		/** ����Renderable���������
		*/
		virtual void SetWorldMatrix(const Matrix4& worldMatrix4) = 0;

		/** ȡ��Renderable���������
		*/
		virtual Matrix4 GetWorldMatrix() = 0;

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