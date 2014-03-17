#ifndef __DREEVENT_H__
#define __DREEVENT_H__

#include "DreTypes.h"
#include "DreContainer.h"
#include "DreComplieConfig.h"

#include <functional>

namespace dream
{
	using std::function;
	using std::bind;
	using namespace std::placeholders;

	template<class Handler>
	class DRE_EXPORT_CLASS Event
	{
	public:
		typedef typename list<Handler*>::iterator			HandlerIte;
		typedef typename list<Handler*>::const_iterator		HandlerConstIte;

	public:
		/** 构造函数
		* @param	name		事件名
		*/
		explicit Event(const string& name);

		/** 析构函数
		*/
		virtual ~Event();

		/** 取得事件名
		*/
		string GetEventName();

		/** 添加一个事件处理器
		*/
		void Insert(Handler* handler);

		/** 删除一个事件处理器
		*/
		void Remove(Handler* handler);

	private:
		/** 禁用复制构造函数
		*/
		// Event(const Event&) = delete; 暂不支持该语法
		Event(const Event&);
		
		/** 禁用复制操作符
		*/
		// Event operator = (const Event&) = delete; 暂不支持该语法
		Event operator = (const Event&);

	protected:
		/// 事件名
		string mEventName;

		/// 事件处理器列表
		list<Handler*> mHandlerList;
	};

	#include "DreEvent_Imp.h"

}	// end namespace dream

#endif	// end __DREEVENT_H__