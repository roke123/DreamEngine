#ifndef __SSAMPLE_H__
#define __SSAMPLE_H__

#include "DreComplieConfig.h"
#include "DreTypes.h"
#include "DreMath.h"
#include "SColor.h"
#include "Matrix4.h"

namespace dream
{

	namespace video
	{

		// 采样器纹理坐标寻址方式
		enum ETEXTUREADDRESS
		{
			ETA_WRAP = 1,
			ETA_MIRROR = 2,
			ETA_CLAMP = 3,
			ETA_BORDER = 4,
			ETA_MIRRORONCE = 5,

			//防止编译器把enum编译为非32位值
			ETA_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff,
		};

		// 采样器采样方式
		enum ETEXTUREFILTER
		{
			ETFILTER_MIN_MAG_MIP_POINT = 1,
			ETFILTER_MIN_MAG_POINT_MIP_LINEAR = 2,
			ETFILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 3,
			ETFILTER_MIN_POINT_MAG_MIP_LINEAR = 4,
			ETFILTER_MIN_LINEAR_MAG_MIP_POINT = 5,
			ETFILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 6,
			ETFILTER_MIN_MAG_LINEAR_MIP_POINT = 7,
			ETFILTER_MIN_MAG_MIP_LINEAR = 8,
			ETFILTER_ANISOTROPIC = 9,

			//防止编译器把enum编译为非32位值
			ETFILTER_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff,
		};

		struct SSampler
		{
			//默认构造函数
			SSampler() : 
				filter_( ETFILTER_MIN_MAG_MIP_LINEAR ),
				addressU_( ETA_WRAP ),
				addressV_( ETA_WRAP ),
				mipLODBias_(0),
				maxAnisotropy_(0),
				borderColor_( 0x000000 ),
				minLOD_( 0.0f ),
				maxLOD_( core::MAX_F32 ),
				textureMatrix_( core::IdentityMatrix )
			{
			}

			bool operator == ( const SSampler& s )
			{
				return filter_ == s.filter_ &&
					addressU_ == s.addressU_ &&
					addressV_ == s.addressV_ &&
					mipLODBias_ == s.mipLODBias_ &&
					maxAnisotropy_ == s.maxAnisotropy_ &&
					borderColor_ == s.borderColor_ &&
					minLOD_ == s.minLOD_ &&
					maxLOD_ == s.maxLOD_ &&
					textureMatrix_ == s.textureMatrix_;
			}

			bool operator != ( const SSampler& s )
			{
				return filter_ != s.filter_ ||
					addressU_ != s.addressU_ ||
					addressV_ != s.addressV_ ||
					mipLODBias_ != s.mipLODBias_ ||
					maxAnisotropy_ != s.maxAnisotropy_ ||
					borderColor_ != s.borderColor_ ||
					minLOD_ != s.minLOD_ ||
					maxLOD_ != s.maxLOD_ ||
					textureMatrix_ != s.textureMatrix_;
			}

			// 采样器的像素采样方式，默认值为ETFILTER_MIN_MAG_MIP_LINEAR
			ETEXTUREFILTER filter_;

			// 纹理u坐标的匹配方式，默认值为ETA_WARP
			ETEXTUREADDRESS addressU_;

			// 纹理v坐标的匹配方式，默认值为ETA_WARP
			ETEXTUREADDRESS addressV_;

			// 纹理w坐标的匹配方式,用于3D纹理坐标一般不考虑
			// ETEXTUREADDRESS addressW_;

			// 纹理mipLevel值偏移量，默认值为0
			u32 mipLODBias_;

			// 最大各向异性值，值为1 - 16，默认值为0
			u32 maxAnisotropy_;

			// DirectX11中判断新采样值如何覆盖旧采样值的比
			// 较函数，一般为NEVER（不使用），这里我们直接不使用这个值
			//D3D11_COMPARISON_FUNC ComparisonFunc;
			
			// 当addressU或addressV为ETA_BORDER时所采用的颜色值，默认为0x000000
			SColor borderColor_;

			// 注意原纹理图miplevel为零，miplevel越大细节越少
			
			// 可被接受的最小miplevel，此值在DirectX9中无意义，默认值为0
			f32 minLOD_;

			// 可被接受的最大miplevel，默认值为MAX_F32
			f32 maxLOD_;

			core::Matrix4 textureMatrix_;

		};	// end struct SSampler

		typedef std::tr1::shared_ptr< SSampler > SSamplerPtr;

	}	// end namespace video

}	// end namespace dream

#endif	// end __ISAMPLE_H__