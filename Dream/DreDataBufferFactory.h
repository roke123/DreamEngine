#ifndef __DREDATABUFFERFACTORY_H__
#define __DREDATABUFFERFACTORY_H__

#include "DreIOSystemDeclaration.h"

namespace dream
{
	class DRE_EXPORT_CLASS DataBufferFactory
	{
	public:
		/** ���ļ�file����Ϊ֮����һ��FileReadBuffer
		*/
		static ReadBufferPtr CreateFileReadBuffer(const char* file);

		/** ���ļ�file����Ϊ֮����һ��FileReadBuffer
		*/
		static ReadBufferPtr CreateFileReadBuffer(const string& file);

		/** ���ļ�file����Ϊ֮����һ��FileWriteBuffer
		* @param option		��ʾ�Ժ��ַ�ʽд�ļ�
		*/
		static WriteBufferPtr CreateFileWriteBuffer(const char* file, DRE_WRITE_FILE_OPTION option);

		/** ���ļ�file����Ϊ֮����һ��FileWriteBuffer
		* @param option		��ʾ�Ժ��ַ�ʽд�ļ�
		*/
		static WriteBufferPtr CreateFileWriteBuffer(const string& file, DRE_WRITE_FILE_OPTION option);

		/** Ϊһ��buffer����MemoryReadBuffer
		*/
		static ReadBufferPtr CreateMemoryReadBuffer(u8Array buffer, u32 size);

		/** Ϊһ��buffer����MemoryWriteBuffer
		*/
		static WriteBufferPtr CreateMemoryWriteBuffer(u8Array buffer, u32 size);

		/** Ϊһ��buffer����MemoryReadBuffer
		*/
		static ReadBufferPtr CreateMemoryReadBuffer(void* buffer, u32 size);

		/** Ϊһ��buffer����MemoryWriteBuffer
		*/
		static MemoryWriteBufferPtr CreateMemoryWriteBuffer(void* buffer, u32 size);

		/** Ϊһ��buffer����BaseMemoryReadBuffer
		*/
		static ReadBufferPtr CreateBaseMemoryReadBuffer(void* buffer, u32 size);

		/** Ϊһ��buffer����BaseMemoryWriteBuffer
		*/
		static WriteBufferPtr CreateBaseMemoryWriteBuffer(void* buffer, u32 size);

	};	// end class DataBufferFactory

}	// end namespace dream

#endif	// end __DREDATABUFFERFACTORY_H__