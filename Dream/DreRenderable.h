#ifndef __DRERENDERABLE_H__
#define __DRERENDERABLE_H__

/// scene manager
#include "DreSceneManagerDeclaration.h"
#include "DreComponent.h"
#include "DreEvent.h"

/// render system
#include "DreRenderDeclaration.h"

namespace dream
{
	typedef function<void (RenderSystem& renderSystem, Renderable& object)> RenderEventHandler;

	class Renderable : public Component
	{
		class RenderEvent final : public Event<RenderEventHandler>
		{
		public:
			/** 构造函数
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

	private:
		

	public:
		/** 构造函数
		*/
		Renderable();

		/** 析构函数
		*/
		virtual ~Renderable() {};

		/** 渲染该Renderable
		*/
		virtual void Render(RenderSystemPtr& renderSystem) = 0;

		/** 取得Renderable的碰撞盒
		*/
		virtual const AABB3& GetBoundBox() = 0;

		/** 渲染事件发生顺序
		* 通过OnPrePassRender可以修改渲染顺序
		* 通过OnPreRender可以修改渲染属性
		* 通过OnPastRender可以恢复原渲染属性
		* 通过OnPastPassRender可以重复渲染同一渲染对象
		* OnPrePassRender -> OnPreRender -> Render -> OnPastRender -> OnPastPassRender 
		*/
		/// 渲染前事件
		RenderEvent OnPreRender;
		/// 渲染后事件
		RenderEvent OnPastRender;
	};

}	// end namespace dream

#endif	// end __DRERENDERABLE_H__