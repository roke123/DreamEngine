#ifndef __DREREADFILE_H__
#define __DREREADFILE_H__

#include "DreIOSystemDeclaration.h"

namespace dream
{
	class ReadBuffer
	{
	public:
		/** ����������
		*/
		virtual ~ReadBuffer() {};

		/** ��ȡ����
		* @param buffer			���ݻ�����
		* @param sizeInByte		���ݳ���
		* @return				��ȡ�����ݳ���
		*/
		virtual u32 Read(u8Array& buffer, u32 sizeInByte) = 0;

		/** ��ȡ����
		* @param buffer			���ݻ�����
		* @param sizeInByte		���ݳ���
		* @return				��ȡ�����ݳ���
		*/
		virtual u32 Read(u8* buffer, u32 sizeInByte) = 0;

		/** ��ת���ļ�ĳ��λ��
		* @param offset			��Ը���λ�õ�ƫ��
		* @param pos			�ļ����λ��
		*/
		virtual void Seek(s32 offset, DRE_BUFFER_POSITION pos) = 0;

		/** ���ػ���������
		* @return �ļ�����
		*/
		virtual u32 Size() const = 0;

		/** ���ػ�������ǰλ��
		* @return ���ػ�������ǰλ��
		*/
		virtual u32 Tell(void) = 0;

		/** �����Ƿ񵽴ﻺ��������λ��
		*/
		virtual bool IsEOF(void) = 0;

		/** �ر�������
		*/
		virtual void Close(void) {}

		/** ��ȡ������Ϊĳ������
		* @template T			��ȡ����������
		* @param	data		��ȡ������ָ��
		*/
		template<class T>
		u32 ReadAs(T* data)
		{
			u32 sizeInByte = sizeof(T);
			return Read(data, sizeInByte);
		}

		/** ��ȡһ������
		* @param	delim		optional��Ĭ��Ϊ���з�
		*
		* @return	����һ���ַ���
		*/
		string GetLine(const string& delim = "\n");

		/** ��ȡһ������
		* @param	buffer		���ݻ�����
		* @param	maxCount	��󳤶ȣ�һ��Ϊ����������
		* @param	delim		optional��Ĭ��Ϊ���з�
		* @return				��ȡ���ݵĳ���
		*/
		u32 ReadLine(u8Array& buffer, u32 maxCount, const string delim = "\n");

		/** ����length���ֽ�
		* @param	length		���������ݳ���
		*/
		void Skip(u32 length);

		/** ����һ������
		* @param	delim		optional��Ĭ��Ϊ���з�
		*/
		void SkipLine(const string& delim = "\n");

	private:
		const static u32 TEMP_DATA_SIZE = 128;

	};	// end class ReadFile

}	// end namespace dream

#endif	// end __DREREADFILE_H__