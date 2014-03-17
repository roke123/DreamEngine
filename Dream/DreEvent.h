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
		/** ���캯��
		* @param	name		�¼���
		*/
		explicit Event(const string& name);

		/** ��������
		*/
		virtual ~Event();

		/** ȡ���¼���
		*/
		string GetEventName();

		/** ���һ���¼�������
		*/
		void Insert(Handler* handler);

		/** ɾ��һ���¼�������
		*/
		void Remove(Handler* handler);

	private:
		/** ���ø��ƹ��캯��
		*/
		// Event(const Event&) = delete; �ݲ�֧�ָ��﷨
		Event(const Event&);
		
		/** ���ø��Ʋ�����
		*/
		// Event operator = (const Event&) = delete; �ݲ�֧�ָ��﷨
		Event operator = (const Event&);

	protected:
		/// �¼���
		string mEventName;

		/// �¼��������б�
		list<Handler*> mHandlerList;
	};

	#include "DreEvent_Imp.h"

}	// end namespace dream

#endif	// end __DREEVENT_H__