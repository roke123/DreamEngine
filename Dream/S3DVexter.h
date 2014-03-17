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
		// ENUM_VEXTER_DATA_DESC��������������
		enum  EVEXTERDATADESC
		{
			EVDD_XYZ = 0,					// 3D���꣬f32 x 3
			EVDD_NORMAL,						// ���ߣ�f32 x 2
			EVDD_COLOR,						// ���߷�����ɫ�� u32 x 1
			EVDD_TEX0,						// 0-8�������꣬f32 x 2
			EVDD_TEX1,						// ͬ��
			EVDD_TEX2,						// ͬ��
			EVDD_TEX3,						// ͬ��
			EVDD_TEX4,						// ͬ��
			EVDD_TEX5,						// ͬ��
			EVDD_TEX6,						// ͬ��
			EVDD_TEX7,						// ͬ��
			EVDD_TANGENT,					// ���ߣ����ڰ�͹ӳ��, f32 x 2
			EVDD_BINORMAL,					// �����ߣ����ڰ�͹ӳ�䣬f32 x 2
			EVDD_USER = 0x7fffffff			// �û��Զ������ԣ����ݸ�ʽδ��
		};	// end enum EVEXTERDATADESC

		// ENUM_VEXTER_DATA_FMT�����������������ݸ�ʽ
		enum EVEXTERDATAFMT
		{
			EVDF_16X1,				// 16λ����1��			
			EVDF_16X2,				// 16λ����2��	
			EVDF_16X3,				// 16λ����3��	
			EVDF_16X4,				// 16λ����4��	
			EVDF_32X1,				// 32λ����1��	
			EVDF_32X2,				// 32λ����2��	
			EVDF_32X3,				// 32λ����3��	
			EVDF_32X4				// 32λ����4��	
		};	// end enum EVEXTERDATAFMT

		//�������Զ�Ӧ��HLSL������
		const char * EVEXTER_DATA_DESC_NAME [] = 
		{
			"POSITION",				// ����
			"NORMAL",				// ������
			"COLOR",				// ���߷�����ɫ
			"TEXCROOD",				// ����TEX0-8��FMT_NAME
			"TANGENT",				// ����
			"BINORMAL",				// ������
		};

		// �������ݸ�ʽ����
		struct VEXTER_DATA_DESC
		{
			// �������ݵ�����
			EVEXTERDATADESC dataDesc;			

			// �������ݵ�������,��dataDesc!=EVDD_USERʱ������Ϊ��,
			// ��dataDesc==EVDD_USERʱ�������õ����ܴ�������
			const char * verterFmtName;				

			// ��ǰһ������ݵ�ƫ����
			u32 offset;							

			// �������ݵĸ�ʽ
			EVEXTERDATAFMT dataFmt;					
		};	// end struct VEXTER_DATA_DESC

		struct S3DStandardVexter
		{
			core::Vector3 pos;						// ����
			core::Vector2 normal;					// ������
			SColor color;							// ��ɫ
			core::Vector2 tex0Crood;				// ��Ӧ��һ�����������

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