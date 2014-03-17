#ifndef __DRESAMPLER_H__
#define __DRESAMPLER_H__

#include "DreContainer.h"
#include "DreTypes.h"
#include "DreRenderSystemEnums.h"

namespace dream
{

	struct SamplerDesc
	{
		/// ���������ʽ������������Բ�����
		DRE_FILTER_OPTION			filter;
		/// ����u����Ѱַ��ʽ
		DRE_TEXTURE_ADDRESS_MODE	addressU;
		/// ����u����Ѱַ��ʽ
		DRE_TEXTURE_ADDRESS_MODE	addressV;
		/// ����mip����������ƫ��
		f32							mipLODBias;
		/// ���������Բ���ֵ
		u32							maxAnisotropy;
		/// ��С�ɽ���������
		f32							minLOD;
		/// ���ɽ���������
		f32							maxLOD;
	};

}	// end namespace dream

#endif	// end of __DRESAMPLER_H__