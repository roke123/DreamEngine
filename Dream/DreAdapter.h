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

		/** 虚析构函数
		*/
		virtual ~Adapter(){};

		/** 返回设备名
		* @return 设备名
		*/
		virtual string DriverName() const = 0;
		
		/** 返回设备描述
		* @return 设备描述
		*/
		virtual string DriverDescription() const = 0;

	};	// end class Adpter

}	// end namespace dream

#endif	// end of __DREADPTER_H__