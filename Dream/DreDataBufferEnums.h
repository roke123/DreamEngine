#ifndef __DREDATABUFFERENUMS_H__
#define __DREDATABUFFERENUMS_H__

namespace dream
{

	enum DRE_BUFFER_POSITION
	{
		/// �ļ���ǰλ��
		DRE_BUFFER_CUR = 0,
		/// �ļ���ʼλ��
		DRE_BUFFER_BEG = 1,
		/// �ļ�����λ��
		DRE_BUFFER_END = 2,
	};

	enum DRE_WRITE_FILE_OPTION
	{
		/// �Ը��ӷ�ʽд�ļ����ļ��������׳��쳣
		DRE_WRITE_FILE_APPEND				= 0,
		/// �ԽضϷ�ʽд�ļ����ļ��������׳��쳣
		DRE_WRITE_FILE_TRUNC				= 1,
		/// ���ļ�������ʱ�����ļ�
		DRE_WRITE_FILE_CREATE				= 2,
		/// ���ļ�����ʱ�Ը��ӷ�ʽд�ļ���������ʱ�����ļ�
		DRE_WRITE_FILE_APPEND_OR_CREATE		= 3,
	};

}	// end namespace dream

#endif	// end __DREDATABUFFERENUMS_H__