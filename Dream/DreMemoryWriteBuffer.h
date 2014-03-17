#ifndef __MEMORYWRITEBUFFER_H__
#define __MEMORYWRITEBUFFER_H__

#include "DreIOSystemDeclaration.h"

#include "DreWriteBuffer.h"

namespace dream
{	

	class MemoryWriteBuffer : public WriteBuffer
	{
		friend class DataBufferFactory;

	private:
		MemoryWriteBuffer(u8Array buffer, u32 size) :	
			mBuffer(buffer), mStart(0), mEnd(0), mCur(0),
			mMemorySize(size)
		{
			// ����
		}

	public:
		/** ����������
		*/
		virtual ~MemoryWriteBuffer() {}

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		void Write(const u8Array buffer, u32 sizeInByte) override
		{
			DreAssert(sizeInByte >= 0, "д�볤�Ȳ���Ϊ����");
			DreAssert(buffer->size() >= sizeInByte,  "�������ݻ������������д�볤��");
			DreAssert(mCur + sizeInByte <= mMemorySize, "д�����ݳ��ȳ���ʣ��ռ�");

			memcpy(&mBuffer[mCur], &buffer[0], sizeInByte);
			WriteAdjust(sizeInByte);
		}

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		void Write(const u8* buffer, u32 sizeInByte) override
		{
			DreAssert(sizeInByte >= 0, "д�볤�Ȳ���Ϊ����");
			DreAssert(buffer != nullptr, "��������ָ�벻��Ϊ��");
			DreAssert(mCur + sizeInByte <= mMemorySize, "д�����ݳ��ȳ���ʣ��ռ�");

			memcpy(&mBuffer[mCur], buffer, sizeInByte);
			WriteAdjust(sizeInByte);
		}

		/** ��ת��������ĳ��λ��
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
				position = mEnd;
				break;
			}

			mCur = position + offset;

			DreAssert(mCur >= mStart && mCur <= mEnd, "�����������");
		}

		/** ���ػ���������
		* @return ����������
		*/
		u32 Size() const { return mEnd - mStart; }

		/** ���ػ�������ǰλ��
		* @return ���ػ�������ǰλ��
		*/
		u32 Tell(void) { return mCur - mStart; }

	private:
		/** ����д�����ݵĳ��ȵ���������
		*/
		void WriteAdjust(u32 sizeInByte)
		{
			mCur += sizeInByte;
			if(mCur > mEnd)
				mEnd = mCur;
		}

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

	};	// end class MemoryWriteBuffer

}	// end namespace dream

#endif	// end __MEMORYREADBUFFER_H__