#include "DreDataBufferFactory.h"
#include "DreReadBuffer.h"
#include "DreWriteBuffer.h"
#include "DreFileReadBuffer.h"
#include "DreFileWriteBuffer.h"
#include "DreMemoryReadBuffer.h"
#include "DreMemoryWriteBuffer.h"
#include "DreBaseMemoryReadBuffer.h"
#include "DreBaseMemoryWriteBuffer.h"

#include <boost\filesystem.hpp>
using namespace boost;

namespace dream
{

	ReadBufferPtr DataBufferFactory::CreateFileReadBuffer(const char* file)
	{
		if (!filesystem::exists(file))
		{
			string desc = "�ļ�";
			desc += file;
			desc += "������";

			DRE_EXCEPT(DRE_EXCEPTION_FILE_NOT_FOUND, desc, "DataBufferFactory::CreateFileReadBuffer");
		}

		// ��ȡ�ļ�����
		u32 fileLength = (u32)filesystem::file_size(file);
		
		// ���ļ�
		ifstreamPtr fileStream(new std::ifstream);
		fileStream->open(file, std::ios::out);
		if (!fileStream->is_open())
		{
			string desc = "���ļ�";
			desc += file;
			desc += "ʧ��";

			DRE_EXCEPT(DRE_EXCEPTION_IO, desc, "���ļ�ʧ��");
		}

		return ReadBufferPtr(new FileReadBuffer(fileStream, fileLength));
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

		// ����ļ��Ƿ����
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
				desc += "�ļ�";
				desc += file;
				desc += "������";
				DRE_EXCEPT(DRE_EXCEPTION_FILE_NOT_FOUND, desc, "DataBufferFactory::CreateFileWriteBuffer");
			}
			mode = std::ios::app;
			break;
		case dream::DRE_WRITE_FILE_TRUNC:
			mode = std::ios::trunc;
			if (!isFileExist)
			{
				desc = "�ļ�";
				desc += file;
				desc += "������";
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

		// ���ļ�
		ofstreamPtr fileStream(new std::ofstream(file));
		if (fileStream->fail())
		{
			string desc = "���ļ�";
			desc += file;
			desc += "ʧ��";

			DRE_EXCEPT(DRE_EXCEPTION_IO, desc, "���ļ�ʧ��");
		}

		return WriteBufferPtr(new FileWriteBuffer(fileStream, fileSize));
	}

	WriteBufferPtr DataBufferFactory::CreateFileWriteBuffer(const string& file, DRE_WRITE_FILE_OPTION option)
	{
		return CreateFileWriteBuffer(file.c_str(), option);
	}

	ReadBufferPtr DataBufferFactory::CreateMemoryReadBuffer(u8Array buffer, u32 size)
	{
		return ReadBufferPtr(new MemoryReadBuffer(buffer, size));
	}

	WriteBufferPtr DataBufferFactory::CreateMemoryWriteBuffer(u8Array buffer, u32 size)
	{
		return WriteBufferPtr(new MemoryWriteBuffer(buffer, size));
	}

	ReadBufferPtr DataBufferFactory::CreateBaseMemoryReadBuffer(void* buffer, u32 size)
	{
		return ReadBufferPtr(new BaseMemoryReadBuffer(buffer, size));
	}

	WriteBufferPtr DataBufferFactory::CreateBaseMemoryWriteBuffer(void* buffer, u32 size)
	{
		return WriteBufferPtr(new BaseMemoryWriteBuffer(buffer, size));
	}
}