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
			// ����
		}

	public:
		/** ����������
		*/
		virtual ~FileWriteBuffer()
		{
			mFileStreamPtr->close();
		}

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		void Write(const u8Array buffer, u32 sizeInByte) 
		{
			DreAssert(buffer->size() >= sizeInByte, "�������ݻ������������д�볤��");
			mFileStreamPtr->write((c8*)&buffer[0], sizeInByte);
		}

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		void Write(const u8* buffer, u32 sizeInByte)
		{
			DreAssert(buffer != nullptr, "��������ָ�벻��Ϊ��");
			mFileStreamPtr->write((c8*)buffer, sizeInByte);
		}

		/** ��ת��������ĳ��λ��
		* @param offset			��Ը���λ�õ�ƫ��
		* @param pos			�ļ����λ��
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
				DRE_EXCEPT(DRE_EXCEPTION_INVALID_STATE, "��������������", "FileReadBuffer::Seek");
			}
		}

		/** ���ػ���������
		* @return ����������
		*/
		u32 Size() const
		{
			return mFileLength;
		}

		/** ���ػ�������ǰλ��
		* @return ���ػ�������ǰλ��
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
		/// �ļ���ָ��
		ofstreamPtr mFileStreamPtr;
		/// �ļ�������
		u32 mFileLength;
	};	// end class FileWriteBuffer

}	// end namespace dream 

#endif	// end __DREFILEWRITEBUFFER_H__