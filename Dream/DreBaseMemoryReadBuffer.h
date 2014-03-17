#ifndef __DREBASEMEMORYREADBUFFER_H__
#define __DREBASEMEMORYREADBUFFER_H__

#include "DreIOSystemDeclaration.h"

#include "DreReadBuffer.h"

namespace dream
{
	class BaseMemoryReadBuffer : public ReadBuffer
	{
		friend class DataBufferFactory;

	private:
		BaseMemoryReadBuffer(void* data, u32 size) :
		//-----------------------------------------------------
		mBuffer((u8*)data), mStart((u8*)data), mEnd((u8*)data + size), mCur((u8*)data),
			mMemorySize(size)
		{
			// ����
		}

	public:
		/** ����������
		*/
		virtual ~BaseMemoryReadBuffer() {}

		u32 Read(u8Array& buffer, u32 sizeInByte)
		{
			DreAssert(buffer->size() >= sizeInByte, "�������ݻ��������ȱ�����ڶ��볤��");
			
			if (mCur + sizeInByte >= mEnd)
			{
				// ���Ҫ���ȡ���ȳ�����������ʣ�೤��
				u32 readLength = mEnd - mCur - 1;
				memcpy(&buffer[0], mCur, readLength);
				SetEOF();
				return readLength;
			}
			else
			{
				memcpy(&buffer[0], &mCur, sizeInByte);
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
				memcpy(buffer, mCur, readLength);
				SetEOF();
				return readLength;
			}
			else
			{
				memcpy(buffer, mCur, sizeInByte);
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
				position = mEnd - 1;
				break;
			}
			mCur = position + offset;

			DreAssert(mCur >= mStart && mCur < mEnd, "��������ǰλ��Խ��");
		}

		/** ���ػ���������
		* @return �ļ�����
		*/
		u32 Size() const {return mMemorySize; }

		/** ���ػ�������ǰλ��
		* @return ���ػ�������ǰλ��
		*/
		u32 Tell(void) { return mCur - mStart; }

		/** �����Ƿ񵽴ﻺ��������λ��
		*/
		bool IsEOF(void) { return mCur == mEnd; }

		const u8* GetDataPtr() const { return mBuffer; }

	private:
		/** ����MemoryReadBuffer�Ѿ�����EOF��
		*/
		void SetEOF(void)
		{
			mCur = mEnd;
		}

	private:
		/// ���ݿ�
		u8* mBuffer;
		/// ���ݿ�ǰ��ָ��
		u8* mStart;
		/// ���ݿ�ĩ��ָ��
		u8* mEnd;
		/// ���ݿ鵱ǰָ��
		u8* mCur;
		/// ���ݿ鳤��
		u32 mMemorySize;
	};	// end class MemoryReadBuffer

}	// end namespace dream

#endif	// end __DREMEMORYREADBUFFER_H__