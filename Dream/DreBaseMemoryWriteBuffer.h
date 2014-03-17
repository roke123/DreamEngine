#ifndef __BASEMEMORYWRITEBUFFER_H__
#define __BASEMEMORYWRITEBUFFER_H__

#include "DreIOSystemDeclaration.h"

#include "DreWriteBuffer.h"

namespace dream
{	

	class BaseMemoryWriteBuffer : public WriteBuffer
	{
		friend class DataBufferFactory;

	private:
		BaseMemoryWriteBuffer(void* buffer, u32 size) :	
			mBuffer((u8*)buffer), mStart((u8*)buffer), mEnd((u8*)buffer), mCur((u8*)buffer),
			mMemorySize(size)
		{
			// 留空
		}

	public:
		/** 虚析构函数
		*/
		virtual ~BaseMemoryWriteBuffer() {}

		/** 向写缓冲区写入数据
		* @param	buffer			写入数据
		* @param	sizeInByte		数据长度
		*/
		void Write(const u8Array buffer, u32 sizeInByte) override
		{
			DreAssert(sizeInByte >= 0, "写入长度不能为负数");
			DreAssert(buffer->size() >= sizeInByte,  "输入数据缓冲区必须大于写入长度");
			DreAssert(Tell() + sizeInByte <= mMemorySize, "写入数据长度超出剩余空间");

			memcpy(mCur, &buffer[0], sizeInByte);
			WriteAdjust(sizeInByte);
		}

		/** 向写缓冲区写入数据
		* @param	buffer			写入数据
		* @param	sizeInByte		数据长度
		*/
		void Write(const u8* buffer, u32 sizeInByte) override
		{
			DreAssert(sizeInByte >= 0, "写入长度不能为负数");
			DreAssert(buffer != nullptr, "输入数据指针不能为空");
			DreAssert(Tell() + sizeInByte <= mMemorySize, "写入数据长度超出剩余空间");

			memcpy(mCur, &buffer[0], sizeInByte);
			WriteAdjust(sizeInByte);
		}

		/** 跳转到缓冲区某个位置
		* @param offset			相对给出位置的偏移
		* @param pos			文件相对位置
		*/
		void Seek(s32 offset, DRE_BUFFER_POSITION pos)
		{
			u8* position = nullptr;

			switch (pos)
			{
			case DRE_BUFFER_BEG:
				position = mStart;
				break;

			case DRE_BUFFER_CUR:
				position = mCur;
				break;

			case DRE_BUFFER_END:
				position = mEnd;
				break;
			}
			mCur = position + offset;

			DreAssert(mCur >= mStart && mCur < mEnd, "数据流当前位置越界");
		}

		/** 返回缓冲区长度
		* @return 缓冲区长度
		*/
		u32 Size() const { return mEnd - mStart; }

		/** 返回缓冲区当前位置
		* @return 返回缓冲区当前位置
		*/
		u32 Tell(void) { return mCur - mStart; }

	private:
		/** 根据写入数据的长度调整数据流
		*/
		void WriteAdjust(u32 sizeInByte)
		{
			mCur += sizeInByte;
			if(mCur > mEnd)
				mEnd = mCur;
		}

		/// 数据块
		u8* mBuffer;
		/// 数据块前端指针
		u8* mStart;
		/// 数据块末端指针
		u8* mEnd;
		/// 数据块当前指针
		u8* mCur;
		/// 数据块长度
		u32 mMemorySize;

	};	// end class MemoryWriteBuffer

}	// end namespace dream

#endif	// end __MEMORYREADBUFFER_H__