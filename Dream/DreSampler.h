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

	/** �������ֻ࣬��Ϊ���ṩͳһ����
	*/
	class Sampler {
	private:
		SamplerDesc  mSamplerDesc;

	public:
		Sampler(SamplerDesc desc) : mSamplerDesc(desc)
		{
			// ��
		}

		virtual ~Sampler() {}

		/// ȡ����������
		DRE_FILTER_OPTION GetFilter() { return mSamplerDesc.filter; }
		/// ����u����Ѱַ��ʽ
		DRE_TEXTURE_ADDRESS_MODE GetAddressU() { return mSamplerDesc.addressU; }
		/// ����u����Ѱַ��ʽ
		DRE_TEXTURE_ADDRESS_MODE GetAddressV() { return mSamplerDesc.addressV; }
		/// ����mip����������ƫ��
		f32 GetMipLODBias() { return mSamplerDesc.mipLODBias; }
		/// ���������Բ���ֵ
		u32 GetMaxAnisotropy() { return mSamplerDesc.maxAnisotropy; }
		/// ��С�ɽ���������
		f32 GetMinLOD() { return mSamplerDesc.minLOD; }
		/// ���ɽ���������
		f32 GetMaxLOD() { return mSamplerDesc.maxLOD; }
	};

}	// end namespace dream

#endif	// end of __DRESAMPLER_H__