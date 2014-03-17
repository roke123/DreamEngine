#include "DreReadBuffer.h"
#include "DreMath.h"

namespace dream
{

	string ReadBuffer::GetLine(const string& delim  /* = "\n" */ )
	{
		bool isLF = false;
		// 确定delim是否换行符
		if (delim == "\n")
		{
			isLF = true;
		}

		u8Array tempData(TEMP_DATA_SIZE, 0);
		string returnString = "";
		u32 readLength = 0;

		while ((readLength = Read(tempData, TEMP_DATA_SIZE - 1))!= 0)
		{
			// 对读取字符串添加结束符
			tempData[readLength] = '\0';

			// 查找第一个delim
            size_t pos = strcspn((c8*)&tempData[0], delim.c_str());

			// 在当前字符串中找到delim
			if (pos < readLength)
			{
				// 如果分隔符是换行符
				if (isLF)
				{
					// 判断是否为CR/LF格式的换行符
					if(pos != 0 && tempData[pos - 1] == '\r')
					{
						// 除去'\r'
						-- pos;
					}
				}

				// 调整字符串
				tempData[pos] = '\0';
				// 向前调整数据流
				Seek(pos - readLength, DRE_BUFFER_CUR);
				// 整合字符串
				returnString += (c8*)&tempData[0];

				break;
			}

			returnString += (c8*)&tempData[0];
		}

		return returnString;
	}

	u32 ReadBuffer::ReadLine(u8Array& buffer, u32 maxCount, const string delim /* = "\n" */)
	{
		// 确定tempDataSize不大于maxCount
		u32 tempDataSize = Min(TEMP_DATA_SIZE - 1, maxCount);

		bool isLF = false;
		// 确定delim是否换行符
		if (delim == "\n")
		{
			isLF = true;
		}

		u8Array tempData(TEMP_DATA_SIZE, 0);
		u32 readLength = 0;
		u32 totalLength = 0;

		while ((readLength = Read(tempData, tempDataSize))!= 0)
		{
			// 对读取字符串添加结束符
			tempData[readLength] = '\0';

			// 查找第一个delim
            size_t pos = strcspn((c8*)&tempData[0], delim.c_str());

			if(pos + totalLength > maxCount)
			{
				memcpy(&buffer[totalLength], &tempData[0], maxCount - totalLength);
				totalLength = maxCount;
				break;
			}

			// 在当前字符串中找到delim
			if (pos < readLength)
			{
				// 如果分隔符是换行符
				if (isLF)
				{
					// 判断是否为CR/LF格式的换行符
					if(pos != 0 && tempData[pos - 1] == '\r')
					{
						// 除去'\r'
						-- pos;
					}
				}

				// 调整字符串
				tempData[pos] = '\0';
				// 向前调整数据流
				Seek(pos - readLength, DRE_BUFFER_CUR);
				// 复制字符串
				memcpy(&buffer[totalLength], &tempData[0], pos);
				totalLength += pos;

				break;
			}

			// 复制字符串
			memcpy(&buffer[totalLength], &tempData[0], readLength);
			totalLength += readLength;
		}

		return totalLength;
	}

	void ReadBuffer::Skip(u32 length)
	{
		Seek(length, DRE_BUFFER_CUR);
	}

	void ReadBuffer::SkipLine(const string& delim /* = "\n" */)
	{
		bool isLF = false;
		// 确定delim是否换行符
		if (delim == "\n")
		{
			isLF = true;
		}

		u8Array tempData(TEMP_DATA_SIZE, 0);
		u32 readLength = 0;

		while ((readLength = Read(tempData, TEMP_DATA_SIZE - 1))!= 0)
		{
			// 对读取字符串添加结束符
			tempData[readLength] = '\0';

			// 查找第一个delim
            size_t pos = strcspn((c8*)&tempData[0], delim.c_str());

			// 在当前字符串中找到delim
			if (pos < readLength)
			{
				// 如果分隔符是换行符
				if (isLF)
				{
					// 判断是否为CR/LF格式的换行符
					if(pos != 0 && tempData[pos - 1] == '\r')
					{
						// 除去'\r'
						-- pos;
					}
				}

				// 调整字符串
				tempData[pos] = '\0';
				// 向前调整数据流
				Seek(pos - readLength, DRE_BUFFER_CUR);

				break;
			}
		}
	}

}	// end namespace dream