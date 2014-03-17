#include "DreReadBuffer.h"
#include "DreMath.h"

namespace dream
{

	string ReadBuffer::GetLine(const string& delim  /* = "\n" */ )
	{
		bool isLF = false;
		// ȷ��delim�Ƿ��з�
		if (delim == "\n")
		{
			isLF = true;
		}

		u8Array tempData(TEMP_DATA_SIZE, 0);
		string returnString = "";
		u32 readLength = 0;

		while ((readLength = Read(tempData, TEMP_DATA_SIZE - 1))!= 0)
		{
			// �Զ�ȡ�ַ�����ӽ�����
			tempData[readLength] = '\0';

			// ���ҵ�һ��delim
            size_t pos = strcspn((c8*)&tempData[0], delim.c_str());

			// �ڵ�ǰ�ַ������ҵ�delim
			if (pos < readLength)
			{
				// ����ָ����ǻ��з�
				if (isLF)
				{
					// �ж��Ƿ�ΪCR/LF��ʽ�Ļ��з�
					if(pos != 0 && tempData[pos - 1] == '\r')
					{
						// ��ȥ'\r'
						-- pos;
					}
				}

				// �����ַ���
				tempData[pos] = '\0';
				// ��ǰ����������
				Seek(pos - readLength, DRE_BUFFER_CUR);
				// �����ַ���
				returnString += (c8*)&tempData[0];

				break;
			}

			returnString += (c8*)&tempData[0];
		}

		return returnString;
	}

	u32 ReadBuffer::ReadLine(u8Array& buffer, u32 maxCount, const string delim /* = "\n" */)
	{
		// ȷ��tempDataSize������maxCount
		u32 tempDataSize = Min(TEMP_DATA_SIZE - 1, maxCount);

		bool isLF = false;
		// ȷ��delim�Ƿ��з�
		if (delim == "\n")
		{
			isLF = true;
		}

		u8Array tempData(TEMP_DATA_SIZE, 0);
		u32 readLength = 0;
		u32 totalLength = 0;

		while ((readLength = Read(tempData, tempDataSize))!= 0)
		{
			// �Զ�ȡ�ַ�����ӽ�����
			tempData[readLength] = '\0';

			// ���ҵ�һ��delim
            size_t pos = strcspn((c8*)&tempData[0], delim.c_str());

			if(pos + totalLength > maxCount)
			{
				memcpy(&buffer[totalLength], &tempData[0], maxCount - totalLength);
				totalLength = maxCount;
				break;
			}

			// �ڵ�ǰ�ַ������ҵ�delim
			if (pos < readLength)
			{
				// ����ָ����ǻ��з�
				if (isLF)
				{
					// �ж��Ƿ�ΪCR/LF��ʽ�Ļ��з�
					if(pos != 0 && tempData[pos - 1] == '\r')
					{
						// ��ȥ'\r'
						-- pos;
					}
				}

				// �����ַ���
				tempData[pos] = '\0';
				// ��ǰ����������
				Seek(pos - readLength, DRE_BUFFER_CUR);
				// �����ַ���
				memcpy(&buffer[totalLength], &tempData[0], pos);
				totalLength += pos;

				break;
			}

			// �����ַ���
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
		// ȷ��delim�Ƿ��з�
		if (delim == "\n")
		{
			isLF = true;
		}

		u8Array tempData(TEMP_DATA_SIZE, 0);
		u32 readLength = 0;

		while ((readLength = Read(tempData, TEMP_DATA_SIZE - 1))!= 0)
		{
			// �Զ�ȡ�ַ�����ӽ�����
			tempData[readLength] = '\0';

			// ���ҵ�һ��delim
            size_t pos = strcspn((c8*)&tempData[0], delim.c_str());

			// �ڵ�ǰ�ַ������ҵ�delim
			if (pos < readLength)
			{
				// ����ָ����ǻ��з�
				if (isLF)
				{
					// �ж��Ƿ�ΪCR/LF��ʽ�Ļ��з�
					if(pos != 0 && tempData[pos - 1] == '\r')
					{
						// ��ȥ'\r'
						-- pos;
					}
				}

				// �����ַ���
				tempData[pos] = '\0';
				// ��ǰ����������
				Seek(pos - readLength, DRE_BUFFER_CUR);

				break;
			}
		}
	}

}	// end namespace dream