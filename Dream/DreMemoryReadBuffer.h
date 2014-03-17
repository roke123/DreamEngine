#ifndef __DREMEMORYREADBUFFER_H__
#define __DREMEMORYREADBUFFER_H__

#include "DreIOSystemDeclaration.h"

#include "DreReadBuffer.h"

namespace dream
{
	class MemoryReadBuffer : public ReadBuffer
	{
		friend class DataBufferFactory;

	private:
		MemoryReadBuffer(u8Array data, u32 size) :
		//-----------------------------------------------------
		mBuffer(data), mStart(0), mEnd(size), mCur(0)
		{
			// 留空
		}

	public:
		/** 虚析构函数
		*/
		virtual ~MemoryReadBuffer() {}

		u32 Read(u8Array& buffer, u32 sizeInByte)
		{
			DreAssert(buffer->size() >= sizeInByte, "输入数据缓冲区长度必须大于读入长度");

			if (mCur + sizeInByte >= mEnd)
			{
				// 如果要求读取长度超过数据流的剩余长度
				u32 readLength = mEnd - mCur - 1;
				memcpy(&buffer[0], &mBuffer[mCur], readLength);
				SetEOF();
				return readLength;
			}
			else
			{
				memcpy(&buffer[0], &mBuffer[mCur], sizeInByte);
				Skip(sizeInByte);
				return sizeInByte;
			}
		}

		/** 读取数据
		* @param buffer			数据缓冲区
		* @param sizeInByte		数据长度
		* @return				读取的数据长度
		*/
		u32 Read(u8* buffer, u32 sizeInByte) override
		{
			DreAssert(buffer != nullptr, "输入数据缓冲区不能为空")

			if (mCur + sizeInByte >= mEnd)
			{
				// 如果要求读取长度超过数据流的剩余长度
				u32 readLength = mEnd - mCur - 1;
				memcpy(buffer, &mBuffer[mCur], readLength);
				SetEOF();
				return readLength;
			}
			else
			{
				memcpy(buffer, &mBuffer[mCur], sizeInByte);
				Skip(sizeInByte);
				return sizeInByte;
			}
		}

		/** 跳转到文件某个位置
		* @param offset			相对给出位置的偏移
		* @param pos			文件相对位置
		*/
		void Seek(s32 offset, DRE_BUFFER_POSITION pos)
		{
			u32 position = 0;

			switch (pos)
			{
			case DRE_BUFFER_BEG:
				position = mStart;
				break;

			case DRE_BUFFER_CUR:
				position = mCur;
				break;

			case DRE_BUFFER_END:
				position = mEnd - 1;
				break;
			}
			mCur = position + offset;

			DreAssert(mCur >= mStart && mCur < mEnd, "数据流当前位置越界");
		}

		/** 返回缓冲区长度
		* @return 文件长度
		*/
		u32 Size() const { return mEnd; }

		/** 返回缓冲区当前位置
		* @return 返回缓冲区当前位置
		*/
		u32 Tell(void) { return mCur - mStart; }

		/** 返回是否到达缓冲区结束位置
		*/
		bool IsEOF(void) { return mCur == mEnd; }

		const u8* GetDataPtr() const { return &mBuffer[0]; }

	private:
		/** 设置MemoryReadBuffer已经到达EOF处
		*/
		void SetEOF(void)
		{
			mCur = mEnd;
		}

	private:
		/// 数据块
		u8Array mBuffer;
		/// 数据块前端指针
		u32 mStart;
		/// 数据块末端指针
		u32 mEnd;
		/// 数据块当前指针
		u32 mCur;
		/// 数据块长度
		u32 mMemorySize;
	};	// end class MemoryReadBuffer

}	// end namespace dream

#endif	// end __DREMEMORYREADBUFFER_H__