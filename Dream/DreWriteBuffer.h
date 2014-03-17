#ifndef __DREWRITEBUFFER_H__
#define __DREWRITEBUFFER_H__

#include "DreTypes.h"
#include "DreDataBufferEnums.h"

namespace dream
{

	class WriteBuffer
	{
	public:
		/** 虚析构函数
		*/
		virtual ~WriteBuffer() {};

		/** 向写缓冲区写入数据
		* @param	buffer			写入数据
		* @param	sizeInByte		数据长度
		*/
		virtual void Write(const u8Array buffer, u32 sizeInByte) = 0;

		/** 向写缓冲区写入数据
		* @param	buffer			写入数据
		* @param	sizeInByte		数据长度
		*/
		virtual void Write(const u8* buffer, u32 sizeInByte) = 0;

		/** 跳转到缓冲区某个位置
		* @param offset			相对给出位置的偏移
		* @param pos			文件相对位置
		*/
		virtual void Seek(s32 offset, DRE_BUFFER_POSITION pos) = 0;

		/** 返回缓冲区长度
		* @return 缓冲区长度
		*/
		virtual u32 Size() const = 0;

		/** 返回缓冲区当前位置
		* @return 返回缓冲区当前位置
		*/
		virtual u32 Tell(void) = 0;	

		/** 关闭数据流
		*/
		virtual void Close(void) {}

	};	// end class WriteBuffer

}	// end namespace dream

#endif	// end __DREWRITEBUFFER_H__