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
			// ����
		}

	public:
		/** ����������
		*/
		virtual ~BaseMemoryWriteBuffer() {}

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		void Write(const u8Array buffer, u32 sizeInByte) override
		{
			DreAssert(sizeInByte >= 0, "д�볤�Ȳ���Ϊ����");
			DreAssert(buffer->size() >= sizeInByte,  "�������ݻ������������д�볤��");
			DreAssert(Tell() + sizeInByte <= mMemorySize, "д�����ݳ��ȳ���ʣ��ռ�");

			memcpy(mCur, &buffer[0], sizeInByte);
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
			DreAssert(Tell() + sizeInByte <= mMemorySize, "д�����ݳ��ȳ���ʣ��ռ�");

			memcpy(mCur, &buffer[0], sizeInByte);
			WriteAdjust(sizeInByte);
		}

		/** ��ת��������ĳ��λ��
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
				position = mEnd;
				break;
			}
			mCur = position + offset;

			DreAssert(mCur >= mStart && mCur < mEnd, "��������ǰλ��Խ��");
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
		u8* mBuffer;
		/// ���ݿ�ǰ��ָ��
		u8* mStart;
		/// ���ݿ�ĩ��ָ��
		u8* mEnd;
		/// ���ݿ鵱ǰָ��
		u8* mCur;
		/// ���ݿ鳤��
		u32 mMemorySize;

	};	// end class MemoryWriteBuffer

}	// end namespace dream

#endif	// end __MEMORYREADBUFFER_H__