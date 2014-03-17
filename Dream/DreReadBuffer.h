#ifndef __DREREADFILE_H__
#define __DREREADFILE_H__

#include "DreIOSystemDeclaration.h"

namespace dream
{
	class ReadBuffer
	{
	public:
		/** 虚析构函数
		*/
		virtual ~ReadBuffer() {};

		/** 读取数据
		* @param buffer			数据缓冲区
		* @param sizeInByte		数据长度
		* @return				读取的数据长度
		*/
		virtual u32 Read(u8Array& buffer, u32 sizeInByte) = 0;

		/** 读取数据
		* @param buffer			数据缓冲区
		* @param sizeInByte		数据长度
		* @return				读取的数据长度
		*/
		virtual u32 Read(u8* buffer, u32 sizeInByte) = 0;

		/** 跳转到文件某个位置
		* @param offset			相对给出位置的偏移
		* @param pos			文件相对位置
		*/
		virtual void Seek(s32 offset, DRE_BUFFER_POSITION pos) = 0;

		/** 返回缓冲区长度
		* @return 文件长度
		*/
		virtual u32 Size() const = 0;

		/** 返回缓冲区当前位置
		* @return 返回缓冲区当前位置
		*/
		virtual u32 Tell(void) = 0;

		/** 返回是否到达缓冲区结束位置
		*/
		virtual bool IsEOF(void) = 0;

		/** 关闭数据流
		*/
		virtual void Close(void) {}

		/** 读取数据作为某种类型
		* @template T			读取的数据类型
		* @param	data		读取的数据指针
		*/
		template<class T>
		u32 ReadAs(T* data)
		{
			u32 sizeInByte = sizeof(T);
			return Read(data, sizeInByte);
		}

		/** 读取一行数据
		* @param	delim		optional，默认为换行符
		*
		* @return	返回一个字符串
		*/
		string GetLine(const string& delim = "\n");

		/** 读取一行数据
		* @param	buffer		数据缓冲区
		* @param	maxCount	最大长度，一般为缓冲区长度
		* @param	delim		optional，默认为换行符
		* @return				读取数据的长度
		*/
		u32 ReadLine(u8Array& buffer, u32 maxCount, const string delim = "\n");

		/** 跳过length个字节
		* @param	length		跳过的数据长度
		*/
		void Skip(u32 length);

		/** 跳过一行数据
		* @param	delim		optional，默认为换行符
		*/
		void SkipLine(const string& delim = "\n");

	private:
		const static u32 TEMP_DATA_SIZE = 128;

	};	// end class ReadFile

}	// end namespace dream

#endif	// end __DREREADFILE_H__