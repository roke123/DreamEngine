#ifndef __S3DVEXTER_H__
#define __S3DVEXTER_H__

#include "DreComplieConfig.h"
#include "DreTypes.h"
#include "Vector3.h"
#include "Vector2.h"
#include "SColor.h"

namespace dream
{

	namespace video
	{
		// ENUM_VEXTER_DATA_DESC，顶点属性描述
		enum  EVEXTERDATADESC
		{
			EVDD_XYZ = 0,					// 3D坐标，f32 x 3
			EVDD_NORMAL,						// 法线，f32 x 2
			EVDD_COLOR,						// 光线反射颜色， u32 x 1
			EVDD_TEX0,						// 0-8纹理坐标，f32 x 2
			EVDD_TEX1,						// 同上
			EVDD_TEX2,						// 同上
			EVDD_TEX3,						// 同上
			EVDD_TEX4,						// 同上
			EVDD_TEX5,						// 同上
			EVDD_TEX6,						// 同上
			EVDD_TEX7,						// 同上
			EVDD_TANGENT,					// 切线，用于凹凸映射, f32 x 2
			EVDD_BINORMAL,					// 副法线，用于凹凸映射，f32 x 2
			EVDD_USER = 0x7fffffff			// 用户自定义属性，数据格式未定
		};	// end enum EVEXTERDATADESC

		// ENUM_VEXTER_DATA_FMT，描述顶点属性数据格式
		enum EVEXTERDATAFMT
		{
			EVDF_16X1,				// 16位数据1个			
			EVDF_16X2,				// 16位数据2个	
			EVDF_16X3,				// 16位数据3个	
			EVDF_16X4,				// 16位数据4个	
			EVDF_32X1,				// 32位数据1个	
			EVDF_32X2,				// 32位数据2个	
			EVDF_32X3,				// 32位数据3个	
			EVDF_32X4				// 32位数据4个	
		};	// end enum EVEXTERDATAFMT

		//上述属性对应于HLSL的名称
		const char * EVEXTER_DATA_DESC_NAME [] = 
		{
			"POSITION",				// 坐标
			"NORMAL",				// 法向量
			"COLOR",				// 光线反射颜色
			"TEXCROOD",				// 代表TEX0-8的FMT_NAME
			"TANGENT",				// 切线
			"BINORMAL",				// 副法线
		};

		// 顶点数据格式描述
		struct VEXTER_DATA_DESC
		{
			// 顶点数据的描述
			EVEXTERDATADESC dataDesc;			

			// 顶点数据的描述名,当dataDesc!=EVDD_USER时，必须为零,
			// 当dataDesc==EVDD_USER时，需设置但不能带有数字
			const char * verterFmtName;				

			// 与前一项顶点数据的偏移量
			u32 offset;							

			// 顶点数据的格式
			EVEXTERDATAFMT dataFmt;					
		};	// end struct VEXTER_DATA_DESC

		struct S3DStandardVexter
		{
			core::Vector3 pos;						// 坐标
			core::Vector2 normal;					// 法向量
			SColor color;							// 颜色
			core::Vector2 tex0Crood;				// 对应第一张纹理的坐标

			static VEXTER_DATA_DESC vexterDataDesc[];
		};	// end struct S3DStandardVexter

		VEXTER_DATA_DESC S3DStandardVexter::vexterDataDesc[] = 
		{
			{ EVDD_XYZ, 0, 0, EVDF_32X3 },
			{ EVDD_NORMAL, 0, 12, EVDF_32X2 },
			{ EVDD_COLOR, 0, 20, EVDF_32X1 },
			{ EVDD_TEX0, 0, 24, EVDF_32X2 }
		};


	}	// end namespace video

}	// end namespace dream

#endif	// end __S3DVEXTER_H__