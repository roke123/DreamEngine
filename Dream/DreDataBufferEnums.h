#ifndef __DREDATABUFFERENUMS_H__
#define __DREDATABUFFERENUMS_H__

namespace dream
{

	enum DRE_BUFFER_POSITION
	{
		/// 文件当前位置
		DRE_BUFFER_CUR = 0,
		/// 文件开始位置
		DRE_BUFFER_BEG = 1,
		/// 文件结束位置
		DRE_BUFFER_END = 2,
	};

	enum DRE_WRITE_FILE_OPTION
	{
		/// 以附加方式写文件，文件不存在抛出异常
		DRE_WRITE_FILE_APPEND				= 0,
		/// 以截断方式写文件，文件不存在抛出异常
		DRE_WRITE_FILE_TRUNC				= 1,
		/// 当文件不存在时创建文件
		DRE_WRITE_FILE_CREATE				= 2,
		/// 当文件存在时以附加方式写文件，不存在时创建文件
		DRE_WRITE_FILE_APPEND_OR_CREATE		= 3,
	};

}	// end namespace dream

#endif	// end __DREDATABUFFERENUMS_H__