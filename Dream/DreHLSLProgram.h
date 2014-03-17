#ifndef __DREHLSLPROGRAM_H__
#define __DREHLSLPROGRAM_H__

#include "DreRenderDeclaration.h"

#include "DreRenderParam.h"

namespace dream
{
	struct DRE_HLSLPROGRAM_DESC
	{
		const c8*  VS_EntryPoint;
		const c8*  VS_Verson;
		const c8*  VS_File;
		const c8*  DS_EntryPoint;
		const c8*  DS_Verson;
		const c8*  DS_File;
		const c8*  HS_EntryPoint;
		const c8*  HS_Verson;
		const c8*  HS_File;
		const c8*  GS_EntryPoint;
		const c8*  GS_Verson;
		const c8*  GS_File;
		const c8*  PS_EntryPoint;
		const c8*  PS_Verson;
		const c8*  PS_File;
	};

	class DRE_EXPORT_CLASS HLSLProgram
	{
	private:
		HLSLProgram(const HLSLProgram&);
		HLSLProgram& operator = (const HLSLProgram&);
	
	public:
		HLSLProgram() {}

		virtual ~HLSLProgram() {};

		/** ���һ����Ⱦ����
		* @param paramName ��Ⱦ�ܵ�ʹ�õĲ�����
		* @param param ��Ⱦ����
		*/
		void AddRenderParam(const string& paramName, RenderParamPtr param)
		{
			mRenderParamMap.insert(make_pair<string, RenderParamPtr>(paramName, param));
		}
		
		/** ȡ��һ����Ⱦ����
		*/
		RenderParamPtr GetRenderParam(const string& param)
		{
			return mRenderParamMap.find(param)->second;
		}

		/** �Ƴ�һ����Ⱦ����
		* @param paramName ��Ⱦ����
		*/
		void RemoveRenderParam(const string& paramName)
		{
			mRenderParamMap.erase(paramName);
		}

	private:
		/// ��Ⱦ������
		RenderParamPtrMap mRenderParamMap;

	};	// end class HLSLProgram
	
}	// end namespace dream

#endif	// end of __DREHLSLPROGRAm_H__