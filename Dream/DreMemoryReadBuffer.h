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
			// ����
		}

	public:
		/** ����������
		*/
		virtual ~MemoryReadBuffer() {}

		u32 Read(u8Array& buffer, u32 sizeInByte)
		{
			DreAssert(buffer->size() >= sizeInByte, "�������ݻ��������ȱ�����ڶ��볤��");

			if (mCur + sizeInByte >= mEnd)
			{
				// ���Ҫ���ȡ���ȳ�����������ʣ�೤��
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

		/** ��ȡ����
		* @param buffer			���ݻ�����
		* @param sizeInByte		���ݳ���
		* @return				��ȡ�����ݳ���
		*/
		u32 Read(u8* buffer, u32 sizeInByte) override
		{
			DreAssert(buffer != nullptr, "�������ݻ���������Ϊ��")

			if (mCur + sizeInByte >= mEnd)
			{
				// ���Ҫ���ȡ���ȳ�����������ʣ�೤��
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

		/** ��ת���ļ�ĳ��λ��
		* @param offset			��Ը���λ�õ�ƫ��
		* @param pos			�ļ����λ��
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

			DreAssert(mCur >= mStart && mCur < mEnd, "��������ǰλ��Խ��");
		}

		/** ���ػ���������
		* @return �ļ�����
		*/
		u32 Size() const { return mEnd; }

		/** ���ػ�������ǰλ��
		* @return ���ػ�������ǰλ��
		*/
		u32 Tell(void) { return mCur - mStart; }

		/** �����Ƿ񵽴ﻺ��������λ��
		*/
		bool IsEOF(void) { return mCur == mEnd; }

		const u8* GetDataPtr() const { return &mBuffer[0]; }

	private:
		/** ����MemoryReadBuffer�Ѿ�����EOF��
		*/
		void SetEOF(void)
		{
			mCur = mEnd;
		}

	private:
		/// ���ݿ�
		u8Array mBuffer;
		/// ���ݿ�ǰ��ָ��
		u32 mStart;
		/// ���ݿ�ĩ��ָ��
		u32 mEnd;
		/// ���ݿ鵱ǰָ��
		u32 mCur;
		/// ���ݿ鳤��
		u32 mMemorySize;
	};	// end class MemoryReadBuffer

}	// end namespace dream

#endif	// end __DREMEMORYREADBUFFER_H__