#ifndef __DREFILEREADBUFFER_H__
#define __DREFILEREADBUFFER_H__

#include <fstream>

#include "DreReadBuffer.h"
#include "DreException.h"

namespace dream
{

	class FileReadBuffer : public ReadBuffer
	{
		friend class DataBufferFactory;

	private:
		// 不应该在构造函数中抛出异常，因为这样会使其析构函数得不到调用，可能会导致内存泄露
		
		/** 私有构造函数，防止外部构造
		*/
		FileReadBuffer(ifstreamPtr fileStream, u32 length)
			: mFileStreamPtr(fileStream), mFileLength(length)
		{
			// 留空
		}

	public:

		/** 虚析构函数
		*/
		virtual ~FileReadBuffer() 
		{
			mFileStreamPtr->close();
		}

		/** 读取数据
		* @param buffer			数据缓冲区
		* @param sizeInByte		数据长度
		* @return				读取的数据长度
		*/
		u32 Read(u8Array& buffer, u32 sizeInByte)
		{
			u32 begin = this->Tell();
			mFileStreamPtr->read((c8*)&buffer[0], sizeInByte);
			return this->Tell() - begin;
		}

		/** 读取数据
		* @param buffer			数据缓冲区
		* @param sizeInByte		数据长度
		* @return				读取的数据长度
		*/
		u32 Read(u8* buffer, u32 sizeInByte) override
		{
			DreAssert(buffer != nullptr, "输入数据缓冲区不能为空");

			u32 begin = this->Tell();
			mFileStreamPtr->read((c8*)buffer, sizeInByte);
			return this->Tell() - begin;
		}

		/** 跳转到文件某个位置
		* @param offset			相对给出位置的偏移
		* @param pos			文件相对位置
		*/
		void Seek(s32 offset, DRE_BUFFER_POSITION pos)
		{
			std::ios::seekdir position = 0;

			switch (pos)
			{
			case DRE_BUFFER_BEG:
				position = std::ios::beg;
				break;

			case DRE_BUFFER_CUR:
				position = std::ios::cur;
				break;

			case DRE_BUFFER_END:
				position = std::ios::end;
				break;
			}

			mFileStreamPtr->seekg(offset, position);

			if (mFileStreamPtr->fail())
			{
				DRE_EXCEPT(DRE_EXCEPTION_IO, "数据流发生错误", "FileReadBuffer::Seek");
			}
		}

		/** 返回缓冲区长度
		* @return 文件长度
		*/
		u32 Size() const
		{
			return mFileLength;
		}

		/** 返回缓冲区当前位置
		* @return 返回缓冲区当前位置
		*/
		u32 Tell(void)
		{
			return (u32)mFileStreamPtr->tellg();
		}

		/** 返回是否到达缓冲区结束位置
		*/
		bool IsEOF(void)
		{
			return mFileStreamPtr->eof();
		}

		void Close(void) 
		{
			mFileStreamPtr->close();
		}

	private:
		// 文件流指针
		ifstreamPtr mFileStreamPtr;
		// 文件流长度
		u32 mFileLength;

	};	// end class FileReadBuffer

}	// end namespace dream

#endif	// end __DREFLEREADBUFFER_H__