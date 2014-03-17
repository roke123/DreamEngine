#ifndef __DREWRITEBUFFER_H__
#define __DREWRITEBUFFER_H__

#include "DreTypes.h"
#include "DreDataBufferEnums.h"

namespace dream
{

	class WriteBuffer
	{
	public:
		/** ����������
		*/
		virtual ~WriteBuffer() {};

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		virtual void Write(const u8Array buffer, u32 sizeInByte) = 0;

		/** ��д������д������
		* @param	buffer			д������
		* @param	sizeInByte		���ݳ���
		*/
		virtual void Write(const u8* buffer, u32 sizeInByte) = 0;

		/** ��ת��������ĳ��λ��
		* @param offset			��Ը���λ�õ�ƫ��
		* @param pos			�ļ����λ��
		*/
		virtual void Seek(s32 offset, DRE_BUFFER_POSITION pos) = 0;

		/** ���ػ���������
		* @return ����������
		*/
		virtual u32 Size() const = 0;

		/** ���ػ�������ǰλ��
		* @return ���ػ�������ǰλ��
		*/
		virtual u32 Tell(void) = 0;	

		/** �ر�������
		*/
		virtual void Close(void) {}

	};	// end class WriteBuffer

}	// end namespace dream

#endif	// end __DREWRITEBUFFER_H__