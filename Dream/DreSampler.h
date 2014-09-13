#ifndef __DRESAMPLER_H__
#define __DRESAMPLER_H__

#include "DreContainer.h"
#include "DreTypes.h"
#include "DreRenderSystemEnums.h"

namespace dream
{

	struct SamplerDesc
	{
		/// 纹理采样方式（点采样或线性采样）
		DRE_FILTER_OPTION			filter;
		/// 纹理u坐标寻址方式
		DRE_TEXTURE_ADDRESS_MODE	addressU;
		/// 纹理u坐标寻址方式
		DRE_TEXTURE_ADDRESS_MODE	addressV;
		/// 纹理mip采样纹理级别偏移
		f32							mipLODBias;
		/// 最大各向异性采样值
		u32							maxAnisotropy;
		/// 最小可接受纹理级别
		f32							minLOD;
		/// 最大可接受纹理级别
		f32							maxLOD;
	};

	/** 采样器类，只是为了提供统一基类
	*/
	class Sampler {
	private:
		SamplerDesc  mSamplerDesc;

	public:
		Sampler(SamplerDesc desc) : mSamplerDesc(desc)
		{
			// 空
		}

		virtual ~Sampler() {}

		/// 取过滤器描述
		DRE_FILTER_OPTION GetFilter() { return mSamplerDesc.filter; }
		/// 纹理u坐标寻址方式
		DRE_TEXTURE_ADDRESS_MODE GetAddressU() { return mSamplerDesc.addressU; }
		/// 纹理u坐标寻址方式
		DRE_TEXTURE_ADDRESS_MODE GetAddressV() { return mSamplerDesc.addressV; }
		/// 纹理mip采样纹理级别偏移
		f32 GetMipLODBias() { return mSamplerDesc.mipLODBias; }
		/// 最大各向异性采样值
		u32 GetMaxAnisotropy() { return mSamplerDesc.maxAnisotropy; }
		/// 最小可接受纹理级别
		f32 GetMinLOD() { return mSamplerDesc.minLOD; }
		/// 最大可接受纹理级别
		f32 GetMaxLOD() { return mSamplerDesc.maxLOD; }
	};

}	// end namespace dream

#endif	// end of __DRESAMPLER_H__