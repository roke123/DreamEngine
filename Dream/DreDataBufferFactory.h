#ifndef __DREDATABUFFERFACTORY_H__
#define __DREDATABUFFERFACTORY_H__

#include "DreIOSystemDeclaration.h"

namespace dream
{
	class DRE_EXPORT_CLASS DataBufferFactory
	{
	public:
		/** 打开文件file，并为之生成一个FileReadBuffer
		*/
		static ReadBufferPtr CreateFileReadBuffer(const char* file);

		/** 打开文件file，并为之生成一个FileReadBuffer
		*/
		static ReadBufferPtr CreateFileReadBuffer(const string& file);

		/** 打开文件file，并为之生成一个FileWriteBuffer
		* @param option		表示以何种方式写文件
		*/
		static WriteBufferPtr CreateFileWriteBuffer(const char* file, DRE_WRITE_FILE_OPTION option);

		/** 打开文件file，并为之生成一个FileWriteBuffer
		* @param option		表示以何种方式写文件
		*/
		static WriteBufferPtr CreateFileWriteBuffer(const string& file, DRE_WRITE_FILE_OPTION option);

		/** 为一个buffer生成MemoryReadBuffer
		*/
		static ReadBufferPtr CreateMemoryReadBuffer(u8Array buffer, u32 size);

		/** 为一个buffer生成MemoryWriteBuffer
		*/
		static WriteBufferPtr CreateMemoryWriteBuffer(u8Array buffer, u32 size);

		/** 为一个buffer生成MemoryReadBuffer
		*/
		static ReadBufferPtr CreateMemoryReadBuffer(void* buffer, u32 size);

		/** 为一个buffer生成MemoryWriteBuffer
		*/
		static MemoryWriteBufferPtr CreateMemoryWriteBuffer(void* buffer, u32 size);

		/** 为一个buffer生成BaseMemoryReadBuffer
		*/
		static ReadBufferPtr CreateBaseMemoryReadBuffer(void* buffer, u32 size);

		/** 为一个buffer生成BaseMemoryWriteBuffer
		*/
		static WriteBufferPtr CreateBaseMemoryWriteBuffer(void* buffer, u32 size);

	};	// end class DataBufferFactory

}	// end namespace dream

#endif	// end __DREDATABUFFERFACTORY_H__