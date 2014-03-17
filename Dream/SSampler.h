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

		// ��������������Ѱַ��ʽ
		enum ETEXTUREADDRESS
		{
			ETA_WRAP = 1,
			ETA_MIRROR = 2,
			ETA_CLAMP = 3,
			ETA_BORDER = 4,
			ETA_MIRRORONCE = 5,

			//��ֹ��������enum����Ϊ��32λֵ
			ETA_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff,
		};

		// ������������ʽ
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

			//��ֹ��������enum����Ϊ��32λֵ
			ETFILTER_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff,
		};

		struct SSampler
		{
			//Ĭ�Ϲ��캯��
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

			// �����������ز�����ʽ��Ĭ��ֵΪETFILTER_MIN_MAG_MIP_LINEAR
			ETEXTUREFILTER filter_;

			// ����u�����ƥ�䷽ʽ��Ĭ��ֵΪETA_WARP
			ETEXTUREADDRESS addressU_;

			// ����v�����ƥ�䷽ʽ��Ĭ��ֵΪETA_WARP
			ETEXTUREADDRESS addressV_;

			// ����w�����ƥ�䷽ʽ,����3D��������һ�㲻����
			// ETEXTUREADDRESS addressW_;

			// ����mipLevelֵƫ������Ĭ��ֵΪ0
			u32 mipLODBias_;

			// ����������ֵ��ֵΪ1 - 16��Ĭ��ֵΪ0
			u32 maxAnisotropy_;

			// DirectX11���ж��²���ֵ��θ��Ǿɲ���ֵ�ı�
			// �Ϻ�����һ��ΪNEVER����ʹ�ã�����������ֱ�Ӳ�ʹ�����ֵ
			//D3D11_COMPARISON_FUNC ComparisonFunc;
			
			// ��addressU��addressVΪETA_BORDERʱ�����õ���ɫֵ��Ĭ��Ϊ0x000000
			SColor borderColor_;

			// ע��ԭ����ͼmiplevelΪ�㣬miplevelԽ��ϸ��Խ��
			
			// �ɱ����ܵ���Сmiplevel����ֵ��DirectX9�������壬Ĭ��ֵΪ0
			f32 minLOD_;

			// �ɱ����ܵ����miplevel��Ĭ��ֵΪMAX_F32
			f32 maxLOD_;

			core::Matrix4 textureMatrix_;

		};	// end struct SSampler

		typedef std::tr1::shared_ptr< SSampler > SSamplerPtr;

	}	// end namespace video

}	// end namespace dream

#endif	// end __ISAMPLE_H__