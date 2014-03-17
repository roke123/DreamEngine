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
		// ��Ӧ���ڹ��캯�����׳��쳣����Ϊ������ʹ�����������ò������ã����ܻᵼ���ڴ�й¶
		
		/** ˽�й��캯������ֹ�ⲿ����
		*/
		FileReadBuffer(ifstreamPtr fileStream, u32 length)
			: mFileStreamPtr(fileStream), mFileLength(length)
		{
			// ����
		}

	public:

		/** ����������
		*/
		virtual ~FileReadBuffer() 
		{
			mFileStreamPtr->close();
		}

		/** ��ȡ����
		* @param buffer			���ݻ�����
		* @param sizeInByte		���ݳ���
		* @return				��ȡ�����ݳ���
		*/
		u32 Read(u8Array& buffer, u32 sizeInByte)
		{
			u32 begin = this->Tell();
			mFileStreamPtr->read((c8*)&buffer[0], sizeInByte);
			return this->Tell() - begin;
		}

		/** ��ȡ����
		* @param buffer			���ݻ�����
		* @param sizeInByte		���ݳ���
		* @return				��ȡ�����ݳ���
		*/
		u32 Read(u8* buffer, u32 sizeInByte) override
		{
			DreAssert(buffer != nullptr, "�������ݻ���������Ϊ��");

			u32 begin = this->Tell();
			mFileStreamPtr->read((c8*)buffer, sizeInByte);
			return this->Tell() - begin;
		}

		/** ��ת���ļ�ĳ��λ��
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

			mFileStreamPtr->seekg(offset, position);

			if (mFileStreamPtr->fail())
			{
				DRE_EXCEPT(DRE_EXCEPTION_IO, "��������������", "FileReadBuffer::Seek");
			}
		}

		/** ���ػ���������
		* @return �ļ�����
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
			return (u32)mFileStreamPtr->tellg();
		}

		/** �����Ƿ񵽴ﻺ��������λ��
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
		// �ļ���ָ��
		ifstreamPtr mFileStreamPtr;
		// �ļ�������
		u32 mFileLength;

	};	// end class FileReadBuffer

}	// end namespace dream

#endif	// end __DREFLEREADBUFFER_H__