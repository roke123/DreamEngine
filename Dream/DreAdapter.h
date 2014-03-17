#ifndef __DREADPTER_H__
#define __DREADPTER_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS Adapter
	{
	private:
		Adapter(const Adapter&);
		Adapter& operator = (const Adapter&);

	public:
		Adapter() {}

		/** ����������
		*/
		virtual ~Adapter(){};

		/** �����豸��
		* @return �豸��
		*/
		virtual string DriverName() const = 0;
		
		/** �����豸����
		* @return �豸����
		*/
		virtual string DriverDescription() const = 0;

	};	// end class Adpter

}	// end namespace dream

#endif	// end of __DREADPTER_H__