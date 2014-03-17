#ifndef __DREFILEWRITEBUFFER_H__
#define __DREFILEWRITEBUFFER_H__

#include "DreIOSystemDeclaration.h"

#include "DreWriteBuffer.h"

namespace dream
{

	class FileWriteBuffer : public WriteBuffer
	{
		friend class DataBufferFactory;

	private:
		FileWriteBuffer(ofstreamPtr fileStream, u32 length)
			: mFileStreamPtr(fileStream), mFileLength(length)
		{
			// 留空
		}

	public:
		/** 虚析构函数
		*/
		virtual ~FileWriteBuffer()
		{
			mFileStreamPtr->close();
		}

		/** 向写缓冲区写入数据
		* @param	buffer			写入数据
		* @param	sizeInByte		数据长度
		*/
		void Write(const u8Array buffer, u32 sizeInByte) 
		{
			DreAssert(buffer->size() >= sizeInByte, "输入数据缓冲区必须大于写入长度");
			mFileStreamPtr->write((c8*)&buffer[0], sizeInByte);
		}

		/** 向写缓冲区写入数据
		* @param	buffer			写入数据
		* @param	sizeInByte		数据长度
		*/
		void Write(const u8* buffer, u32 sizeInByte)
		{
			DreAssert(buffer != nullptr, "输入数据指针不能为空");
			mFileStreamPtr->write((c8*)buffer, sizeInByte);
		}

		/** 跳转到缓冲区某个位置
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

			mFileStreamPtr->seekp(offset, position);

			if (mFileStreamPtr->fail())
			{
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_STATE, "数据流发生错误", "FileReadBuffer::Seek");
			}
		}

		/** 返回缓冲区长度
		* @return 缓冲区长度
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
			return (u32)mFileStreamPtr->tellp();
		}

		void Close(void) 
		{
			mFileStreamPtr->close();
		}

	private:
		/// 文件流指针
		ofstreamPtr mFileStreamPtr;
		/// 文件流长度
		u32 mFileLength;
	};	// end class FileWriteBuffer

}	// end namespace dream 

#endif	// end __DREFILEWRITEBUFFER_H__