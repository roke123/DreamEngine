#include "DreDataBufferFactory.h"
#include "DreReadBuffer.h"
#include "DreWriteBuffer.h"
#include "DreFileReadBuffer.h"
#include "DreFileWriteBuffer.h"
#include "DreMemoryReadBuffer.h"
#include "DreMemoryWriteBuffer.h"
#include "DreBaseMemoryReadBuffer.h"
#include "DreBaseMemoryWriteBuffer.h"

#include "DreMemoryAllocatorConfig.h"

#include <boost\filesystem.hpp>
using namespace boost;

namespace dream
{

	ReadBufferPtr DataBufferFactory::CreateFileReadBuffer(const char* file)
	{
		if (!filesystem::exists(file))
		{
			string desc = "文件";
			desc += file;
			desc += "不存在";

			DRE_EXCEPT(DRE_EXCEPTION_FILE_NOT_FOUND, desc, "DataBufferFactory::CreateFileReadBuffer");
		}

		// 获取文件长度
		u32 fileLength = (u32)filesystem::file_size(file);
		
		// 打开文件
		ifstreamPtr fileStream(DREAM_NEW std::ifstream);
		fileStream->open(file, std::ios::out);
		if (!fileStream->is_open())
		{
			string desc = "打开文件";
			desc += file;
			desc += "失败";

			DRE_EXCEPT(DRE_EXCEPTION_IO, desc, "打开文件失败");
		}

		return ReadBufferPtr(DREAM_NEW FileReadBuffer(fileStream, fileLength));
	}

	ReadBufferPtr DataBufferFactory::CreateFileReadBuffer(const string& file)
	{
		return CreateFileReadBuffer(file.c_str());
	}

	WriteBufferPtr DataBufferFactory::CreateFileWriteBuffer(const char* file, DRE_WRITE_FILE_OPTION option)
	{
		std::ios::openmode mode = 0;
		string desc = "";
		u32 fileSize = 0;
		bool isFileExist = false;

		// 检查文件是否存
		if(filesystem::exists(file))
		{
			isFileExist = true;
			fileSize = (u32)filesystem::file_size(file);
		}

		switch (option)
		{
		case dream::DRE_WRITE_FILE_APPEND:
			if (!isFileExist)
			{
				desc += "文件";
				desc += file;
				desc += "不存在";
				DRE_EXCEPT(DRE_EXCEPTION_FILE_NOT_FOUND, desc, "DataBufferFactory::CreateFileWriteBuffer");
			}
			mode = std::ios::app;
			break;
		case dream::DRE_WRITE_FILE_TRUNC:
			mode = std::ios::trunc;
			if (!isFileExist)
			{
				desc = "文件";
				desc += file;
				desc += "不存在";
				DRE_EXCEPT(DRE_EXCEPTION_FILE_NOT_FOUND, desc, "DataBufferFactory::CreateFileWriteBuffer");
			}
			fileSize = 0;
			break;
		case dream::DRE_WRITE_FILE_CREATE:
			mode = std::ios::out;
			break;
		case dream::DRE_WRITE_FILE_APPEND_OR_CREATE:
			mode = std::ios::out | std::ios::app;
			break;
		default:
			break;
		}

		// 打开文件
		ofstreamPtr fileStream(DREAM_NEW std::ofstream(file));
		if (fileStream->fail())
		{
			string desc = "打开文件";
			desc += file;
			desc += "失败";

			DRE_EXCEPT(DRE_EXCEPTION_IO, desc, "打开文件失败");
		}

		return WriteBufferPtr(DREAM_NEW FileWriteBuffer(fileStream, fileSize));
	}

	WriteBufferPtr DataBufferFactory::CreateFileWriteBuffer(const string& file, DRE_WRITE_FILE_OPTION option)
	{
		return CreateFileWriteBuffer(file.c_str(), option);
	}

	ReadBufferPtr DataBufferFactory::CreateMemoryReadBuffer(u8Array buffer, u32 size)
	{
		return ReadBufferPtr(DREAM_NEW MemoryReadBuffer(buffer, size));
	}

	WriteBufferPtr DataBufferFactory::CreateMemoryWriteBuffer(u8Array buffer, u32 size)
	{
		return WriteBufferPtr(DREAM_NEW MemoryWriteBuffer(buffer, size));
	}

	ReadBufferPtr DataBufferFactory::CreateBaseMemoryReadBuffer(void* buffer, u32 size)
	{
		return ReadBufferPtr(DREAM_NEW BaseMemoryReadBuffer(buffer, size));
	}

	WriteBufferPtr DataBufferFactory::CreateBaseMemoryWriteBuffer(void* buffer, u32 size)
	{
		return WriteBufferPtr(DREAM_NEW BaseMemoryWriteBuffer(buffer, size));
	}
}