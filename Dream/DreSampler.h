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

}	// end namespace dream

#endif	// end of __DRESAMPLER_H__